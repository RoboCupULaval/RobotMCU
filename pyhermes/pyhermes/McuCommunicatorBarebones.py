#!/usr/bin/env python3
"""This modules contains a barebones interface to communicate with
a robot. It is not very useful by itself since it only contains
the functional primitives."""

import os
import time
import threading
import struct
import serial
import serial.tools.list_ports
try:
    from cobs import cobs
except ModuleNotFoundError:
    from cobs.cobs import cobs

from .packet_definitions import PACKET_INFO, get_payload_size

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
    def __init__(self, error_name, bytes_list):
        byte_str = ":".join("{:02x}".format(c) for c in bytes_list)
        message = error_name + " The bytes: {}".format(byte_str)
        super(WrongPacketException, self).__init__(message)


class McuCommunicatorBarebones(object):
    """This modules communicates with the communication tower"""
    def __init__(self, timeout = 1.0):
        self.timeout = timeout
        self.serial_port = None
        # Serial port detection handling for windows
        if os.name == 'nt':
            available_ports = list(
                serial.tools.list_ports.comports())
            available_ports.sort()
            print(available_ports)
            for a_port in available_ports:
                try:
                    serial.serial_port = serial.Serial(a_port[0], timeout=timeout)
                except Exception:
                    pass
        # Serial port detection handling for Linux
        else:
            available_ports = list(
                serial.tools.list_ports.grep(''))
            available_ports.sort()
            print(available_ports)
            if os.path.exists("/dev/ttyBaseStation"):
                device_path = "/dev/ttyBaseStation"
            else:
                try:
                    device_path = available_ports[0].device
                except AttributeError:
                    device_path = available_ports[0][0]
            print("We choose serial port{}".format(device_path))
            while True:
                try:
                    self.serial_port = serial.Serial(device_path, timeout=timeout)
                except serial.serialutil.SerialException:
                    print("Fail to open port, device busy")
                    time.sleep(1)
                    continue
                break
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
        with self.serial_lock:
            self.serial_port.write(my_packet)
        
    def _receive_packet(self, expected_size):
        start_time = time.time()

        byte_left = expected_size
        response = bytearray()
        while byte_left > 0:
            bytes_to_read = self.serial_port.inWaiting()
            if bytes_to_read > 0:
                byte_left -= bytes_to_read
                bytes_receive = self.serial_port.read(bytes_to_read)
                response += bytes_receive
                if '\x00' in list(bytes_receive):
                    return response
            elif (time.time() - start_time) > self.timeout:
                raise serial.SerialTimeoutException("Timeout on serial communication")
        return response


    def _send_receive_packet(self, orig_addr, dest_addr,
                             packet_id, payload):
        # send the first packet
        self.serial_lock.acquire()
        self._send_packet(orig_addr, dest_addr, packet_id, payload)

        # receive the response packet
        packet_to_return = None
        my_packet = bytearray()
        wanted_id = PACKET_INFO[packet_id][1]
        wanted_res_format = PACKET_INFO[wanted_id][0]
        payload_size = struct.calcsize(wanted_res_format) if wanted_res_format is not None else 0

        wanted_byte_number = (HEADER_SIZE +
                              payload_size +
                              COBS_EXTRA_BYTES )
        
        try:
            received_bytes = self._receive_packet(wanted_byte_number)
        except:
            self.serial_lock.release()
            raise

        if received_bytes.count(0) > 1:
            print("Multiple packet response at the same time, only the first is kept")
            received_bytes = received_bytes.split('\x00')[0] + b'\x00'
        my_packet = bytearray(received_bytes)
        self.serial_lock.release()

        #print(received_bytes)

        # remove the COBS encoding
        my_packet.pop()  # Remove of the zero byte at the end
        try:
            packet_to_return = cobs.decode(my_packet)
        except cobs.DecodeError as my_exception:
            print(my_exception)
            raise

        try:
            self._check_packet(packet_to_return, wanted_id)
        except WrongPacketException as my_exception:
            print(my_exception)
            print("Restarting serial port...")
            self.serial_port.close()
            self.__init__()
            raise
        return packet_to_return

    @classmethod
    def _check_packet(cls, packet_bytes, wanted_id):
        payload_size = get_payload_size(wanted_id)
        # check if there is at least enough bytes for the header
        if len(packet_bytes) < HEADER_SIZE:
            raise Exception("Not enough bytes in packet {}<={}".format(len(packet_bytes), HEADER_SIZE))
        # check protocol version
        if packet_bytes[0] != VERSION:
            raise Exception("Wrong protocol version on the packet!")
        # check the ID
        if packet_bytes[3] != wanted_id:
            print("Wrong id")
            raise WrongPacketException("Wrong id", packet_bytes)
        # check the payload length
        if len(packet_bytes) - HEADER_SIZE != payload_size:
            print("Wrong size")
            raise WrongPacketException("Wrong size", packet_bytes)
        # check the checksum
        checksum = cls._compute_checksum(packet_bytes)
        if packet_bytes[4] != checksum:
            print("Wrong checksum, expected {}, received {}".format(checksum, packet_bytes[4]))
            raise WrongPacketException("Wrong checksum, expected {}, received {}".format(packet_bytes[4], checksum), packet_bytes)
        # check the destination
        if packet_bytes[2] != CONTROL_ADDR:
            raise WrongPacketException("Wrong destination!", packet_bytes)

    @classmethod
    def _compute_checksum(cls, packet):
        checksum_value = sum(int(a_byte)
                             for a_byte in packet)
        checksum_value -= packet[4] # remove checksum from total
        return checksum_value & BYTE_MASK
