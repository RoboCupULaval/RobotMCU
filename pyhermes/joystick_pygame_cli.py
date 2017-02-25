from tkinter.constants import CURRENT

import pygame

from mcu_serial_com import *
from time import sleep
import time
from joystick_pygame.joystick import RobotJoystick
from math import *


def do_joystick(com, joy, robot_id):
	global MAX_SPEED
	global current_dribbler_speed
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
		new_speed = current_dribbler_speed + 1
		if new_speed > 3:
			new_speed = 1
		print("Dribbleur set to ", new_speed)
		com.setDribblerSpeed(robot_id, new_speed)
		current_dribbler_speed = new_speed
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

def joystick_pygame_cli(robot_id):
	global MAX_SPEED
	MAX_SPEED = 1.0
	global current_dribbler_speed
	current_dribbler_speed = 0

	# Initialize
	pygame.init()
	pygame.joystick.init()
	joystick_count = pygame.joystick.get_count()

	print('# of detected joystick : {}'.format(joystick_count))

	robotJoystick = []

	# For each joystick:
	for i in range(joystick_count):
		joystick = pygame.joystick.Joystick(i)
		joystick.init()
		robotJoystick.append((RobotJoystick(joystick), robot_id + i))

	port = getFirstSerialPort()
	com = McuCom(port)
	com.setRegister(robot_id, REG_CTRL_LOOP_STATE, 2)

	while True:
		pygame.event.pump()
		for (joy, robot_id) in robotJoystick:
			do_joystick(com, joy, robot_id)
		sleep(0.005)
		print() # cariage return

