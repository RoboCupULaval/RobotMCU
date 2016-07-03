#!/usr/bin/env python
from command import *
import serial
import io
import time
import glob

def getFirstSerialPort():
    #ttyListA = glob.glob('/dev/cu.usb*')
    ttyList = glob.glob('/dev/ttyACM*')
    ttyList +=  glob.glob('/dev/rfcomm*')
    ttyList +=  glob.glob('/dev/ttyUSB*')

    if len(ttyList) == 0:
        print('No serial device found! Exiting...')
        exit()
    elif len(ttyList) == 1:
        print('One serial device found and selected: ' + str(ttyList[0]))
        return ttyList[0]
    else:
        print('Multiple serial devices detected, please select a number:')
        inputNumber = None
        while inputNumber not in range(len(ttyList)):
            for i in range(len(ttyList)):
                print(str(i) + ') ' + ttyList[i])
            try:
                inputNumber = int(input())
            except:
                pass
    return ttyList[inputNumber]

class McuCom(object):
    """Handle communication between the microcontroller and the computer"""
    def __init__(self, port, baudrate, time_out=5):
        self.port = port
        self.baudrate = baudrate
        self.ser = serial.Serial(port, baudrate, timeout=time_out)
        # Set escape caracter to \0

    def testHeartBeat(self):
        cmd = createNoArgCommand(HEART_BEAT_REQUEST_ID)
        print("Cmd ask: ", cmd)
        #self.sendCommandAndWaitAcknowledge(cmd)
        self.sendCommand(cmd)
        try:
            res = self.retreiveRespond()
        except serial.SerialTimeoutException:
            print("No Robot detected")
            return

        if res[3] == HEART_BEAT_RESPOND_ID:
            print("Robot {} is alive".format(res[1]))

        #print 'Header', ":".join("{:02x}".format(ord(c)) for c in res)
        #return res[0] == CMD_ASK_ROBOT_NAME and  res[1] == ROBOT_NAME


    def sendSpeed(self, vx, vy, vz):
        cmd = create3FloatCommand(MOVEMENT_COMMAND_ID, vx, vy, vz)
        #print("Cmd ask: ", cmd)
        #self.sendCommandAndWaitAcknowledge(cmd)
        self.sendCommand(cmd)
        #res = self.retreiveRespond()
        #res = self.retreiveRespond()

    """
    def setPid(self, m, p, i, d):
        cmd = createCommandSetPid(m, p, i, d)
        print("Cmd ask: ", cmd)
        self.sendCommandAndWaitAcknowledge(cmd)
        self.retreiveRespond()

    def listCommand(self):
        cmd = createCommandListCommand()
        print("Cmd ask: ", cmd)
        self.sendCommandAndWaitAcknowledge(cmd)
        res = self.retreiveRespond()
        print "List of command on MCU:"
        print res[1:]
    """
    def sendCommand(self, cmd):
        self.ser.write(cmd)
        self.ser.write(b'\0')
        self.ser.flush()

    def sendCommandAndWaitAcknowledge(self, cmd):
        """
        Send command and wait the awk.
        Also print error and debug message receive before awk
        :param cmd: packaged command
        """
        self.ser.write(cmd)
        self.ser.write(b'\0')
        self.ser.flush()
        while True:
            res = unpackagePayload(self.readUntilZero())
            if res is []:
                print("Empty packet ????")
            elif self.isValidAcknowledge(res):
                return res
            elif self.isNack(res):
                # Resend the package in the case of Nack
                self.ser.write(cmd)
                self.ser.write(b'\0')
                self.ser.flush()
            elif self.isError(res):
                print("ERROR: ", res[1:])
            elif self.isDebug(res):
                print("DEBUG: ", res[1:])


    def isValidAcknowledge(self, pack):
        return pack[0] == CMD_ACK
    def isNack(self, pack):
        return pack[0] == CMD_NACK
    def isError(self, id):
        return id == ROBOT_CRASHED_NOTIFICATION_ID
    def isDebug(self, res):
        return res[0] == CMD_DEBUG
    def isMultiPartPacket(self, res):
        return res[0] == CMD_MULTI_PART
    def getId(self, res):
        return res[3]

    def retreiveRespond(self):
        res = unpackagePayload(self.readUntilZero())
        id = self.getId(res)
        """
        last_res = res

        while self.isMultiPartPacket(last_res):
            last_res = unpackagePayload(self.readUntilZero())
            res += last_res[1:]
        else:
            # Set the id on the last part to the head of the respond
            res = last_res[0] + res[1:]
        """

        if self.isError(id):
            print("ERROR: ", res[1:])
        #elif self.isDebug(last_res):
        #    print("DEBUG: ", res[1:])
        #else:
        #    print('unpacked res=', res)
        return res



    def readUntilZero(self):
        start_time = time.time()
        buf = self.ser.read(1)
        while not b'\0' in buf:
            bytesToRead = self.ser.inWaiting()
            if bytesToRead > 0:
                buf += self.ser.read(1)
            elif time.time() - start_time > 1:
                raise serial.SerialTimeoutException("Timeout on serial communication")
        return buf

