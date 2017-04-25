#!/usr/bin/env python3
"""This modules contains a barebones interface to communicate with
a robot. It is not very useful by itself since it only contains
the functional primitives."""

import os
import threading
import struct
import serial
import serial.tools.list_ports
try:
    from cobs import cobs
except ModuleNotFoundError:
    from cobs.cobs import cobs

from .packet_definitions import PACKET_INFO

COBS_EXTRA_BYTES = 2
HEADER_SIZE = 5
VERSION = 1
BYTE_MASK = 0xFF
CONTROL_ADDR = 0x00
CHECKSUM_BYTE_NUMBER = 4


class WrongPacketException(Exception):
    """Custom exception for packets
    Inputs:
        bytes_list: a list of bytes
    """
    def __init__(self, bytes_list):
        byte_str = ":".join("{:02x}".format(c) for c in bytes_list)
        message = "Wrong packet received! The bytes: {}".format(byte_str)
        super(WrongPacketException, self).__init__(message)


class McuCommunicatorBarebones(object):
    """This modules communicates with the communication tower"""
    def __init__(self):
        self.serial_port = None
        # Serial port detection handling for windows
        if os.name == 'nt':
            available_ports = list(
                serial.tools.list_ports.comports())
            available_ports.sort()
            for a_port in available_ports:
                try:
                    serial.serial_port = serial.Serial(a_port[0], timeout=1)
                except Exception:
                    pass
        # Serial port detection handling for Linux
        else:
            available_ports = list(
                serial.tools.list_ports.grep(''))
            available_ports.sort()
            self.serial_port = serial.Serial(available_ports[0].device,
                                             timeout=0.2)
        self.serial_lock = threading.RLock()
        if self.serial_port is None:
            raise Exception("No stm32 serial port was detected!")

    def _send_packet(self, orig_addr, dest_addr, packet_id, payload):
        # generate the header
        packet = bytearray(struct.pack('BBBBB', VERSION, orig_addr,
                                       dest_addr, packet_id, 0))
        # append the payload
        if payload is not None:
            packet.extend(payload)
        # compute and insert the checksum
        checksum_value = self._compute_checksum(packet)

        packet[CHECKSUM_BYTE_NUMBER] = struct.pack('B', checksum_value)[0]

        # transform the packet using COBS
        my_packet = bytearray(cobs.encode(bytearray(packet)))
        my_packet.append(0x00)

        # send the packet
        self.serial_lock.acquire()
        self.serial_port.write(my_packet)
        self.serial_lock.release()

    def _send_receive_packet(self, orig_addr, dest_addr,
                             packet_id, payload):
        # send the first packet
        self.serial_lock.acquire()
        self._send_packet(orig_addr, dest_addr, packet_id, payload)

        # receive the response packet
        packet_to_return = None
        my_packet = bytearray()

        payload_size = struct.calcsize(PACKET_INFO[packet_id][0])
        wanted_id = PACKET_INFO[packet_id][1]

        wanted_byte_number = (payload_size +
                              COBS_EXTRA_BYTES +
                              HEADER_SIZE)

        received_bytes = self.serial_port.read(wanted_byte_number)
        my_packet = bytearray(received_bytes)
        self.serial_lock.release()

        # remove the COBS encoding
        my_packet.pop()  # Remove of the zero byte at the end
        packet_to_return = cobs.decode(my_packet)

        try:
            self._check_packet(packet_to_return, wanted_id)
        except WrongPacketException as my_exception:
            print(my_exception)
            print("Restarting serial port...")
            self.serial_port.close()
            self.__init__()
        return packet_to_return

    @classmethod
    def _check_packet(cls, packet_bytes, wanted_id):
        payload_size = PACKET_INFO[wanted_id][0]
        # check if there is at least enough bytes for the header
        if len(packet_bytes) <= HEADER_SIZE:
            raise Exception("Not enough bytes in packet")
        # check protocol version
        if packet_bytes[0] != VERSION:
            raise Exception("Wrong protocol version on the packet!")
        # check the ID
        if packet_bytes[3] != wanted_id:
            raise WrongPacketException(packet_bytes)
        # check the payload length
        if len(packet_bytes) - HEADER_SIZE != payload_size:
            raise WrongPacketException(packet_bytes)
        # check the checksum
        checksum = cls._compute_checksum(packet_bytes)
        if packet_bytes[4] != checksum:
            raise WrongPacketException(packet_bytes)
        # check the destination
        if packet_bytes[2] != CONTROL_ADDR:
            raise Exception("Wrong destination!")

    @classmethod
    def _compute_checksum(cls, packet):
        checksum_value = sum(int(a_byte)
                             for a_byte in packet) & BYTE_MASK
        return checksum_value
