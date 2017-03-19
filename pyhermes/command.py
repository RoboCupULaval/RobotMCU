from cobs import cobs
import bitstring
import struct

# Command type
CMD_HEART_BEAT_REQUEST         = 0x00
CMD_HEART_BEAT_RESPOND         = 0x01
CMD_MOVEMENT_COMMAND           = 0x02
CMD_SET_REGISTER               = 0x03
CMD_ACK                        = 0x04
CMD_ROBOT_CRASHED_NOTIFICATION = 0x26
CMD_MOVEMENT_COMMAND_OPEN      = 0x2E

# Register type
REG_CTRL_LOOP_STATE            = 0x00
REG_KICK_COMMAND               = 0x01
REG_CHARGE_KICKER_COMMAND      = 0x02
REG_SET_DRIBBLER_SPEED_COMMAND = 0x03

PROTOCOL_VERSION  = 0x01

#address
ADDR_BASE_STATION = 0xFE
ADDR_BROADCAST    = 0xFF
ADDR_ROBOT1    = 0x01
ADDR_ROBOT3    = 0x03
ADDR_ROBOT7    = 0x07


def intToByteString(i):
    if i == 0:
        return '\x00'
    return bitstring.BitString(uint=i, length=(i.bit_length()+7)/8*8).bytes



def unpackagePayload(pack):
    #print "Decode(", pack, ")"
    if pack == "\0":
        return "\0"
    pack = pack[0:-1] # Remove zero byte
    #try:
    return cobs.decode(pack)
    #except cobs.DecodeError:
    #    pay = ''
    #    pay += CMD_ERROR
    #    return pay + "Invalid respond from mcu"
        #print("payload len %d data=" % len(pack) + ":".join("{:02x}".format(ord(c)) for c in pack))

def generateHeader(dest_addres, packet_type):
    header = bytes([PROTOCOL_VERSION,
                    ADDR_BASE_STATION,
                    dest_addres,
                    packet_type,
                    0x00])
    return header

def packagePayloadLess(robot_id, id):
    pay = generateHeader(robot_id, id)
    return cobs.encode(bytes(pay)) + b'\0'

def packagePayload(robot_id, id, payload):
    pay = generateHeader(robot_id, id)
    pay += payload
    return cobs.encode(bytes(pay))  + b'\0'

def createNoArgCommand(robot_id, id):
    return packagePayloadLess(robot_id, id)

def createCommandGetStatus():
    return packagePayloadLess(CMD_GET_STATUS)

def create2BytesCommand(robot_id, id, b0, b1):
    payload = bytes([b0, b1])
    
    return packagePayload(robot_id, id, payload)

def create3FloatCommand(robot_id, id, vx, vy, vz):
    vel = [vx, vy, vz]
    payload = struct.pack('%sf' % len(vel), *vel)
    #print("payload len %d data=" % len(payload) + ":".join("{:02x}".format(ord(c)) for c in payload))
    #print 'Raw payload', ":".join("{:02x}".format(ord(c)) for c in payload)
    return packagePayload(robot_id, id, payload)

def create4FloatCommand(robot_id, id, cmd1, cmd2, cmd3, cmd4):
    vel = [cmd1, cmd2, cmd3, cmd4]
    payload = struct.pack('%sf' % len(vel), *vel)
    return packagePayload(robot_id, id, payload)

