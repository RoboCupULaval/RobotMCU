from cobs import cobs
import bitstring
import struct


CMD_MULTI_PART        = '\x00'
CMD_ACK               = '\x01'
CMD_ERROR             = '\x02'
CMD_NACK              = '\x03'
CMD_ASK_ROBOT_NAME    = '\x04'
CMD_GET_STATUS        = '\x05'
CMD_SET_SPEED         = '\x06'
CMD_SET_MODE          = '\x07'
CMD_GET_MANCHESTER    = '\x08'
CMD_ACTIVATE_MAGNET   = '\x09'
CMD_DEBUG             = '\x0A'
CMD_LIST_COMMANDS     = '\x0B'
CMD_SET_PID           = '\x0C'
CMD_SET_MAGNET        = '\x0D'
CMD_SET_BREAK_TRIGGER = '\x0E'
CMD_SET_MOVE_SERVO    = '\x0F'
CMD_SET_CHARGE        = '\x10'
CMD_FETCH_LETTER      = '\x11'

# Command type
HEART_BEAT_REQUEST_ID         = 0x00
HEART_BEAT_RESPOND_ID         = 0x01
MOVEMENT_COMMAND_ID           = 0x02
ROBOT_CRASHED_NOTIFICATION_ID = 0x26


PROTOCOL_VERSION  = 0x01

#address
ADDR_BASE_STATION = 0xFE
ADDR_BROADCAST    = 0xFF


def intToByteString(i):
    if i == 0:
        return '\x00'
    return bitstring.BitString(uint=i, length=(i.bit_length()+7)/8*8).bytes



def unpackagePayload(pack):
    #print "Decode(", pack, ")"
    if pack == "\0":
        return "\0"
    pack = pack[0:-1] # Remove zero byte
    try:
        return cobs.decode(pack)
    except cobs.DecodeError:
        pay = ''
        pay += CMD_ERROR
        return pay + "Invalid respond from mcu"
        #print("payload len %d data=" % len(pack) + ":".join("{:02x}".format(ord(c)) for c in pack))

def generateHeader(packet_type, dest_addres=ADDR_BROADCAST):
    header = bytes([PROTOCOL_VERSION,
                    ADDR_BASE_STATION,
                    dest_addres,
                    packet_type,
                    0x00])
    return header

def packagePayloadLess(id):
    pay = generateHeader(id)
    return cobs.encode(bytes(pay)) + b'\0'

def packagePayload(id, payload):
    pay = generateHeader(id)
    pay += payload
    return cobs.encode(bytes(pay))  + b'\0'

def createNoArgCommand(id):
    return packagePayloadLess(id)

def createCommandAskRobotName():
    return packagePayloadLess(CMD_ASK_ROBOT_NAME)

def createCommandGetStatus():
    return packagePayloadLess(CMD_GET_STATUS)

def create3FloatCommand(id, vx, vy, vz):
    vel = [vx, vy, vz]
    payload = struct.pack('%sf' % len(vel), *vel)
    #print("payload len %d data=" % len(payload) + ":".join("{:02x}".format(ord(c)) for c in payload))
    #print 'Raw payload', ":".join("{:02x}".format(ord(c)) for c in payload)
    return packagePayload(id, payload)

