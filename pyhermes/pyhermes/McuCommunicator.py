#!/usr/bin/env python3
"""This module contains an interface to communicate with the robots."""

import struct
from .McuCommunicatorBarebones import McuCommunicatorBarebones, WrongPacketException
from .packet_definitions import PacketID, PACKET_INFO
import serial
try:
    from cobs import cobs
except ModuleNotFoundError:
    from cobs.cobs import cobs

CONTROL_ADDR = 0xFE  # The computer's address

KICK_REGISTER = 0x01
CHARGE_REGISTER = 0x02
DRIBBLER_REGISTER = 0x03


class McuCommunicator(McuCommunicatorBarebones):
    """This module controls one stm32f407 discovery."""

    def testHeartBeat(self, robot_id):
        """Pings a robot.

        Output:
            Returns True if ping succeeded.
        """
        payload = None

        try:
            super()._send_receive_packet(CONTROL_ADDR, robot_id,
                                         PacketID.PING_REQUEST, payload)
        except (serial.SerialTimeoutException, cobs.DecodeError, WrongPacketException) as err:
            print("ERROR:", err)
            return False
        return True

    def getBatterie(self, robot_id):
        payload = None
        try:
            packet_response = super()._send_receive_packet(CONTROL_ADDR, robot_id,
                                                           PacketID.GET_BATTERIE, payload)
        except (serial.SerialTimeoutException, cobs.DecodeError, WrongPacketException):
            return False
        batterie_lvl = packet_response[5] / 10.0
        return batterie_lvl


    def getNumRequest(self, robot_id):
        payload = None
        packet_response = super()._send_receive_packet(CONTROL_ADDR, robot_id,
                                                       PacketID.GET_NUM_REQUEST, payload)
        num_request = struct.unpack('I', packet_response[5:9])
        return num_request[0]


    def sendSpeed(self, robot_id, speed_x, speed_y, speed_rotation):
        """Sets the desired speed for the robot.

        Inputs:
            speed_x -- The x speed as a float in meters per second.
            speed_y -- The y speed as a float in meters per second.
            speed_rotation -- The y speed as a float in radians per second.
        """

        packet_id = PacketID.SPEED_MOVE
        struct_string = PACKET_INFO[packet_id][0]
        payload = struct.pack(struct_string,
                              speed_x, speed_y, speed_rotation)

        robot_addr = robot_id

        super()._send_packet(CONTROL_ADDR, robot_addr,
                             packet_id, payload)

    def sendSpeedAdvance(self, robot_id, speed_x, speed_y, speed_rotation, charge=False, kick_force=0, dribbler_speed=0):
        """Sets the desired speed for the robot.

        Inputs:
            speed_x -- The x speed as a float in meters per second.
            speed_y -- The y speed as a float in meters per second.
            speed_rotation -- The y speed as a float in radians per second.
            kick_force -- Number of increment of 0.1ms of the kick pulse (max 25.5ms). Zero mean no kick
            dribbler_speed -- Either 0, 1, 2, 3
        """
        assert 0 <= kick_force <= 255, "kick_force must be in range 0 to 255"
        assert 0 <= dribbler_speed <= 127, "dribbler_speed must be in range 0 to 127"

        packet_id = PacketID.SPEED_MOVE_ADVANCE
        struct_string = PACKET_INFO[packet_id][0]
        payload = struct.pack(struct_string,
                              speed_x, speed_y, speed_rotation, dribbler_speed + 0x80 if charge else 0, kick_force)

        robot_addr = robot_id

        super()._send_packet(CONTROL_ADDR, robot_addr,
                             packet_id, payload)

    def sendOpenLoopSpeed(self, robot_id, wheel_1_cmd,
                          wheel_2_cmd, wheel_3_cmd, wheel_4_cmd):
        """ Sends a speed command in open loop mode.
        Note: Each command must be between 0 and 1.
        """
        packet_id = PacketID.OPEN_LOOP_COMMAND
        struct_string = PACKET_INFO[packet_id][0]
        payload = struct.pack(struct_string, wheel_1_cmd, wheel_2_cmd,
                              wheel_3_cmd, wheel_4_cmd)
        robot_addr = robot_id

        super()._send_packet(CONTROL_ADDR, robot_addr,
                             packet_id, payload)

    def turnOnDribbler(self, robot_id):
        """ Forces the dribbler of the robot to turn on.
        """
        packet_id = PacketID.SET_REGISTER
        struct_string = PACKET_INFO[packet_id][0]
        payload = struct.pack(struct_string, DRIBBLER_REGISTER, 3)
        robot_addr = robot_id

        super()._send_packet(CONTROL_ADDR, robot_addr,
                             packet_id, payload)

    def turnOffDribbler(self, robot_id):
        """ Forces the dribbler of the robot to turn off.
        """
        packet_id = PacketID.SET_REGISTER
        struct_string = PACKET_INFO[packet_id][0]
        payload = struct.pack(struct_string, DRIBBLER_REGISTER, 0)
        robot_addr = robot_id

        super()._send_packet(CONTROL_ADDR, robot_addr,
                             packet_id, payload)

    def kick(self, robot_id, force):
        """ Make the robot kick.
        """
        packet_id = PacketID.SET_REGISTER
        struct_string = PACKET_INFO[packet_id][0]
        payload = struct.pack(struct_string, KICK_REGISTER, force)
        robot_addr = robot_id

        super()._send_packet(CONTROL_ADDR, robot_addr,
                             packet_id, payload)

    def charge(self, robot_id):
        """ Make the robot charge the kicker capacitor.
        """
        packet_id = PacketID.SET_REGISTER
        struct_string = PACKET_INFO[packet_id][0]
        payload = struct.pack(struct_string, CHARGE_REGISTER, 0)
        robot_addr = robot_id

        super()._send_packet(CONTROL_ADDR, robot_addr,
                             packet_id, payload)

    def setRegister(self, robot_id, register_id, value):
        """ to keep"""
        packet_id = PacketID.SET_REGISTER
        struct_string = PACKET_INFO[packet_id][0]
        payload = struct.pack(struct_string, register_id, value)
        robot_addr = robot_id
        super()._send_packet(CONTROL_ADDR, robot_addr,
                             packet_id, payload)
