#!/usr/bin/env python
from cobs import cobs
from command import *
import serial
import io
import time
import glob

from time import sleep

def getFirstSerialPort():
    defaultPort = '/dev/ttyBaseStation'
    # Give priority to BaseStation macro
    if glob.glob(defaultPort):
        print("Default to port {}".format(defaultPort))
        return defaultPort
    ttyList = glob.glob('/dev/ttyACM*')
    ttyList +=  glob.glob('/dev/ttyBaseStation')
    ttyList +=  glob.glob('/dev/rfcomm*')
    ttyList +=  glob.glob('/dev/ttyUSB*')
    ttyList +=  glob.glob('/dev/tty.Robot*')
    ttyList +=  glob.glob('/dev/tty.usbmodem*')

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
    """Handle communication between the robot and the computer"""
    def __init__(self, port, baudrate=115200, time_out=0.2):
        self.port = port
        self.baudrate = baudrate
        self.timeout = time_out
        
        while True:
            try:
                self.ser = serial.Serial(port, baudrate, timeout=time_out)
            except serial.serialutil.SerialException:
                print("Fail to open port")
                sleep(1)
                continue
            break
        # Set escape caracter to \0

    def testHeartBeat(self, robot_id):
        cmd = createNoArgCommand(robot_id, CMD_HEART_BEAT_REQUEST)
        print("Cmd ask: ", cmd)
        #self.sendCommandAndWaitAcknowledge(cmd)
        self.sendCommand(cmd)
        try:
            res = self.retreiveRespond()
        except cobs.DecodeError:
            print("No Robot detected (invalid response)")
            return False
        except serial.SerialTimeoutException:
            print("No Robot detected")
            return False

        if self.getId(res) == CMD_HEART_BEAT_RESPOND:
            print("Robot {} is alive".format(res[1]))
            return True
        else:
            print("Invalid response {}".format(res))
            return False


        #print 'Header', ":".join("{:02x}".format(ord(c)) for c in res)
        #return res[0] == CMD_ASK_ROBOT_NAME and  res[1] == ROBOT_NAME


    def sendSpeed(self, robot_id, vx, vy, vz):
        cmd = create3FloatCommand(robot_id, CMD_MOVEMENT_COMMAND, vx, vy, vz)
        #print("Cmd ask: ", cmd)
        #self.sendCommandAndWaitAcknowledge(cmd)
        self.sendCommand(cmd)
        #res = self.retreiveRespond()
        #res = self.retreiveRespond()

    def sendOpenLoopSpeed(self, robot_id, cmd1, cmd2, cmd3, cmd4):
        """ Send a speed command in open loop mode. Each command represent a pwm between 0 and 1. """
        cmd = create4FloatCommand(robot_id, CMD_MOVEMENT_COMMAND_OPEN, cmd1, cmd2, cmd3, cmd4)
        self.sendCommand(cmd)

    def turnOnDribbler(self, robot_id):
        self.setRegister(robot_id, REG_SET_DRIBBLER_SPEED_COMMAND, 3)

    def setDribblerSpeed(self, robot_id, speed):
        self.setRegister(robot_id, REG_SET_DRIBBLER_SPEED_COMMAND, speed)

    def turnOffDribbler(self, robot_id):
        self.setRegister(robot_id, REG_SET_DRIBBLER_SPEED_COMMAND, 0)
    
    def kick(self, robot_id):
        self.setRegister(robot_id, REG_KICK_COMMAND, 4)

    def charge(self, robot_id):
        self.setRegister(robot_id, REG_CHARGE_KICKER_COMMAND, 0)
        
    def setRegister(self, robot_id, register, value):
        cmd = create2BytesCommand(robot_id, CMD_SET_REGISTER, register, value)
        print("Cmd ask: ", cmd)
        #self.sendCommandAndWaitAcknowledge(cmd)
        self.sendCommand(cmd)

    def sendCommand(self, cmd):
        self.ser.write(cmd)
        self.ser.flush()

    def sendCommandAndWaitAcknowledge(self, cmd):
        """
        Send command and wait the awk.
        Also print error and debug message receive before awk
        :param cmd: packaged command
        """
        while True:
            self.sendCommand(cmd)
            try:
                res = self.retreiveRespond()
            except cobs.DecodeError:
                print("No response, sending again (invalid response)")
                continue
            except serial.SerialTimeoutException:
                print("No response, sending again")
                continue

            if self.isValidAcknowledge(res):
                print("Awknownledge!")
                break
            elif self.isError(res):
                print("ERROR: ", res[1:])
            else:
                print("Unexpected id response")

            #elif self.isDebug(res):
            #    print("DEBUG: ", res[1:])

    def isError(self, res):
        return self.getId(res) == CMD_ROBOT_CRASHED_NOTIFICATION
    def isValidAcknowledge(self, res):
        return self.getId(res) == CMD_ACK
    def getId(self, res):
        return res[3]

    def retreiveRespond(self):
        res = unpackagePayload(self.readUntilZero())
        if len(res) < len(generateHeader(0, 0)):
            raise cobs.DecodeError()
        """
        last_res = res

        while self.isMultiPartPacket(last_res):
            last_res = unpackagePayload(self.readUntilZero())
            res += last_res[1:]
        else:
            # Set the id on the last part to the head of the respond
            res = last_res[0] + res[1:]
        """

        if self.isError(res):
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
            elif (time.time() - start_time) > self.timeout:
                raise serial.SerialTimeoutException("Timeout on serial communication")
        return buf

