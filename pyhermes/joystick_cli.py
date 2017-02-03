from mcu_serial_com import *
from time import sleep
import time
from joystick.jstick import *
from math import *

JOYSTICK_DEAD_ZONE = 0.1

def joystick_cli():
    MAX_SPEED = 1200.0
    port = getFirstSerialPort()
    com = McuCom(port)

    try:
        joy = Joystick()
    except FileNotFoundError:
        print("Please plug a joystick *facepalm*")
        return

    while True:
    	x, y = joy.buttons['stick1'].coords
    	_, t = joy.buttons['stick2'].coords

    	mag = sqrt(x*x+y*y)
    	angle = atan2(y, x)
    	mag = mag if abs(mag) > JOYSTICK_DEAD_ZONE else 0
    	x =  MAX_SPEED * mag * cos(angle)
    	y =  -MAX_SPEED * mag * sin(angle)
    	theta =  -MAX_SPEED * t / 3.0

    	com.sendSpeed(x, y, theta)

    	if joy.buttons['a'].value:
    		print("kick")
    		com.kick()
    		sleep(0.1)
    	if joy.buttons['y'].value:
    		print("charge")
    		com.charge()
    		sleep(0.1)
    	if joy.buttons['b'].value:
    		print("slow mod")
    		MAX_SPEED = 400.0
    	if joy.buttons['x'].value:
    		print("fast mod")
    		MAX_SPEED = 1200.0
    	


    	print("x:{: 3.3f} y:{: 3.3f} t:{: 3.3f}".format(x, y, t))
    	sleep(0.05)
