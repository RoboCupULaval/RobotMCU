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

# Register type
REG_CTRL_LOOP_STATE            = 0x00;
REG_KICK_COMMAND               = 0x01;

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
    #try:
    return cobs.decode(pack)
    #except cobs.DecodeError:
    #    pay = ''
    #    pay += CMD_ERROR
    #    return pay + "Invalid respond from mcu"
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

def createCommandGetStatus():
    return packagePayloadLess(CMD_GET_STATUS)

def create2BytesCommand(id, b0, b1):
    payload = bytes([b0, b1])
    
    return packagePayload(id, payload)

def create3FloatCommand(id, vx, vy, vz):
    vel = [vx, vy, vz]
    payload = struct.pack('%sf' % len(vel), *vel)
    #print("payload len %d data=" % len(payload) + ":".join("{:02x}".format(ord(c)) for c in payload))
    #print 'Raw payload', ":".join("{:02x}".format(ord(c)) for c in payload)
    return packagePayload(id, payload)

