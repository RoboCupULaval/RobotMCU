from mcu_serial_com import *
from time import sleep
import time
from joystick.jstick import *
from math import *

MAX_SPEED = 200.0
JOYSTICK_DEAD_ZONE = 0.1

def joystick_cli():
    port = getFirstSerialPort()
    com = McuCom(port)

    joy = Joystick()

    while True:
    	x, y = joy.buttons['stick1'].coords
    	_, t = joy.buttons['stick2'].coords
    	mag = sqrt(x*x+y*y)
    	angle = atan2(y, x)
    	mag = mag if abs(mag) > JOYSTICK_DEAD_ZONE else 0
    	x =  MAX_SPEED * mag * cos(angle)
    	y =  MAX_SPEED * mag * sin(angle)
    	theta =  MAX_SPEED * t

    	com.sendSpeed(x, y, theta)

    	print("x:{: 3.3f} y:{: 3.3f} t:{: 3.3f}".format(x, y, t))
    	sleep(0.01)
