#!/usr/bin/env python3
"""This file contains the definitions for the packets
"""

import enum

# To create a new packet and command, please:
# 1) insert its ID in the enum below
# 2) insert its payload length and return id in the packet_info struct
# 3) create the relevant function in mcu_communicator.py

#TODO: autogenerate this file content from the C code

class PacketID(enum.IntEnum):
    """ The packet IDs for each type of normal command.
    """
    PING_REQUEST = 0x00
    PING_RESPOND = 0x01
    SPEED_MOVE = 0x02
    OPEN_LOOP_COMMAND = 0x2E
    SET_REGISTER = 0x03

# This data structure has the following information
# packet_id :  (pack_string, return_packet_id)
# Note: pack_string may be None if there is no payload
# Note: return_packet_id may be None if there is no expected return packet
# note: See the documention of the struct module for the pack string format


PACKET_INFO = {
    PacketID.PING_REQUEST: (None, PacketID.PING_RESPOND),
    PacketID.PING_RESPOND: (None, None),
    PacketID.SPEED_MOVE: ('fff', None),
    PacketID.OPEN_LOOP_COMMAND: ('ffff', None),
    PacketID.SET_REGISTER: ('BB', None)
    }
