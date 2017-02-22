from mcu_serial_com import *
from time import sleep
import time
from joystick_pygame import *
from math import *

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
	x, y = joy.getLeftAxisVector()
	_, t = joy.getRightAxisVector()

	x = x * MAX_SPEED
	y = y * MAX_SPEED

	com.sendSpeed(robot_id, x, y, t)

	if joy.getBtnValue("X"):
		print("kick")
		com.kick(robot_id)
		sleep(0.05)
	if joy.getBtnValue("A"):
		print("charge")
		com.charge(robot_id)
		sleep(0.05)
	if joy.getBtnValue("B"):
		print("Dribbleur n")
		com.turnOnDribbler(robot_id)
		sleep(0.05)
	if joy.getBtnValue("Y"):
		print("Dribbleur off")
		com.turnOffDribbler(robot_id)
		sleep(0.05)
	if joy.getBtnValue("L1"):
		print("slow mode")
		MAX_SPEED = 0.1
	if joy.getBtnValue("R1"):
		print("fast mode")
		MAX_SPEED = 1.0
	print("id:{: 3.3f} x:{: 3.3f} y:{: 3.3f} t:{: 3.3f} ".format(robot_id, x, y, t), end='')

def joystick_cli(robot_id):


    joy_robot_list = [(Joystick(joy_list[i]), robot_id + i) for i in range(len(joy_list))]     

    #port = getFirstSerialPort()
    #com = McuCom(port)
    #com.setRegister(robot_id, REG_CTRL_LOOP_STATE, 2)    
    while True:
        for (joy, robot_id) in joy_robot_list:
            do_joystick(com, joy, robot_id)
            sleep(0.005)
        print() # cariage return
    
