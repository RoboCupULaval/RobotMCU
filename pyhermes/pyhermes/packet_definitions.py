#!/usr/bin/env python3
"""This file contains the definitions for the packets
"""

import enum
import struct

# To create a new packet and command, please:
# 1) insert its ID in the enum below
# 2) insert its payload length and return id in the packet_info struct
# 3) create the relevant function in mcu_communicator.py

#TODO: autogenerate this file content from the C code


class PacketID(enum.IntEnum):
    """ The packet IDs for each type of normal command.
    """
    PING_REQUEST = 0x00
    PING_RESPONSE = 0x01
    SPEED_MOVE = 0x02
    SET_REGISTER = 0x03
    OPEN_LOOP_COMMAND = 0x04
    GET_BATTERIE = 0x05,
    BATTERIE_RESPONSE = 0x06,
    GET_NUM_REQUEST = 0x07,
    NUM_REQUEST_RESPONSE = 0x08

# This data structure has the following information
# packet_id :  (pack_string, return_packet_id)
# Note: pack_string may be None if there is no payload
# Note: return_packet_id may be None if there is no expected return packet
# note: See the documention of the struct module for the pack string format


PACKET_INFO = {
    PacketID.PING_REQUEST: (None, PacketID.PING_RESPONSE),
    PacketID.PING_RESPONSE: (None, None),
    PacketID.SPEED_MOVE: ('fff', None),
    PacketID.SET_REGISTER: ('BB', None),
    PacketID.OPEN_LOOP_COMMAND: ('ffff', None),
    PacketID.GET_BATTERIE: (None, PacketID.BATTERIE_RESPONSE),
    PacketID.BATTERIE_RESPONSE: ('B', None),
    PacketID.GET_NUM_REQUEST: (None, PacketID.NUM_REQUEST_RESPONSE),
    PacketID.NUM_REQUEST_RESPONSE: ('I', None)
    }
    
def get_payload_size(wanted_id):
    wanted_res_format = PACKET_INFO[wanted_id][0]
    payload_size = struct.calcsize(wanted_res_format) if wanted_res_format != None else 0
    return payload_size