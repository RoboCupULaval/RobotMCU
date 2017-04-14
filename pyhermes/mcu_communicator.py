#!/usr/bin/env python3
"""This module contains an interface to communicate with the robots."""

from mcu_communicator_barebones import mcu_communicator_barebones
from packet_definitions import *

from packet_definitions import *


class mcu_communicator(mcu_communicator_barebones):
    """This module controls one stm32f407 discovery."""

    def ping_robot(self, robot_id):
        """Pings a robot.

        Output:
            Returns True if ping succeeded.
        """
        payload = 
        super()._send_receive_packet()
        return True

    def speed_move(self, speed_x, speed_y):
        """Sets the desired speed for the robot.

        Inputs:
            speed_x -- The x speed as a float in meters per second.
            speed_y -- The y speed as a float in meters per second.

        Note: speed move and speed rotation are mutually exclusive
        in the robot.
        """

        speed_x_integer = int(min(speed_x * CONVERSION_RATIO, 1000000))
        speed_y_integer = int(min(speed_y * CONVERSION_RATIO, 1000000))

        super()._send_packet([PacketID.speed_move,
                               *speed_x_bytes,
                               *speed_y_bytes])
