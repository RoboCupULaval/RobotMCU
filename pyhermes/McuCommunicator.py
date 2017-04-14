#!/usr/bin/env python3
"""This module contains an interface to communicate with the robots."""

import struct
from McuCommunicatorBarebones import McuCommunicatorBarebones
from packet_definitions import PacketID, PACKET_INFO

CONTROL_ADDR = 0x00  # The computer's address


class McuCommunicator(McuCommunicatorBarebones):
    """This module controls one stm32f407 discovery."""

    def ping_robot(self, robot_id):
        """Pings a robot.

        Output:
            Returns True if ping succeeded.
        """
        payload = None
        robot_addr = robot_id
        super()._send_receive_packet(CONTROL_ADDR, robot_addr,
                                     PacketID.PING_REQUEST, payload)
        return True

    def speed_move(self, robot_id, speed_x, speed_y, speed_rotation):
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
