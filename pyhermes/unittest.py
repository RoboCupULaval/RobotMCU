#!/usr/bin/env python
from mcu_serial_com import *
import time
from time import sleep

#BAUDRATE = 115200
BAUDRATE = 19200



def test_mcu_id():
	port = getFirstSerialPort()
	print('Serial device selected: ' + str(port))
	mcu = McuCom(port, BAUDRATE)

	while not mcu.testRobotName():
		print "ROBOT DOES NOT RESPOND!"
		time.sleep(1)


	print "**********************"
	print "ROBOT CONNECTED! :D"
	print "**********************"


	while True:
		mcu.sendSpeed(0.0, 40.0, 0.0)
		mcu.getStatus()
		sleep(1)
	#mcu.listCommand()
	#mcu.setPid(1, 3.0, 2.0, 1.0)
	

test_mcu_id()
