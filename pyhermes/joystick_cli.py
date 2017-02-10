from mcu_serial_com import *
from time import sleep
import time
from joystick.jstick import *
from math import *

JOYSTICK_DEAD_ZONE = 0.1

def get_joysticks():
    joyList = glob.glob('/dev/input/js*')

    if len(joyList) == 0:
        print('No joystick found! Exiting...')
        exit()
    elif len(joyList) == 1:
        print('One joystick found and selected: ' + str(joyList[0]))
    else:
        print('Multiple joystick detected')
        for joy_path in joyList:
            print(joy_path)

    return joyList

def do_joystick(com, joy, robot_id):
	global MAX_SPEED    
	MAX_SPEED = 1200.0
	y, x = joy.buttons['stick1'].coords
	_, t = joy.buttons['stick2'].coords

	mag = sqrt(x*x+y*y)
	angle = atan2(y, x)
	mag = mag if abs(mag) > JOYSTICK_DEAD_ZONE else 0
	x =  -MAX_SPEED * mag * cos(angle)
	y =  -MAX_SPEED * mag * sin(angle)
	theta =  -MAX_SPEED * t / 3.0

	com.sendSpeed(robot_id, x, y, theta)

	if joy.buttons['a'].value:
		print("kick")
		com.kick(robot_id)
		#sleep(0.1)
	if joy.buttons['y'].value:
		print("charge")
		com.charge(robot_id)
		#sleep(0.1)
	if joy.buttons['l'].value:
		print("Dribbleur n")
		com.turnOnDribbler(robot_id)
		#sleep(0.1)
	if joy.buttons['r'].value:
		print("Dribbleur off")
		com.turnOffDribbler(robot_id)
		#sleep(0.1)
	if joy.buttons['b'].value:
		print("slow mod")
		MAX_SPEED = 400.0
	if joy.buttons['x'].value:
		print("fast mod")
		MAX_SPEED = 1200.0
	print("id:{: 3.3f} x:{: 3.3f} y:{: 3.3f} t:{: 3.3f} ".format(robot_id, x, y, t), end='')

def joystick_cli(robot_id):

    joy_list = get_joysticks()

    joy_robot_list = [(Joystick(joy_list[i]), robot_id + i) for i in range(len(joy_list))]     

    port = getFirstSerialPort()
    com = McuCom(port)
    
    while True:
        for (joy, robot_id) in joy_robot_list:
            do_joystick(com, joy, robot_id)
            sleep(0.020)
        print() # cariage return
    
