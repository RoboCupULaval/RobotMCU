from pyhermes.McuCommunicator import McuCommunicator, DRIBBLER_REGISTER
from time import sleep
import time
from .joystick_pygame.joystick import RobotJoystick
from math import *


def do_joystick(com, joy, robot_id):
	global MAX_SPEED
	global current_dribbler_speed
	x, y = joy.get_left_axis_vector()
	_, t = joy.get_right_axis_vector()

	x = x * MAX_SPEED
	y = y * MAX_SPEED
	t = t * 6


	if joy.get_btn_value("X"):
		print("kick")
		com.kick(robot_id, 5)
		sleep(0.05)
	if joy.get_btn_value("B"):
		print("pass")
		com.kick(robot_id, 2)
		sleep(0.05)
	if joy.get_btn_value("A"):
		print("charge")
		com.charge(robot_id)
		sleep(0.05)
	if joy.get_btn_value("select"):
		print("Dribbleur on")
		com.turnOnDribbler(robot_id)
		sleep(0.05)
		#new_speed = 2
		#print("Dribbleur set to ", new_speed)
		#com.setRegister(robot_id, DRIBBLER_REGISTER, new_speed)
	# 	current_dribbler_speed = new_speed
	# 	sleep(0.05)
	if joy.get_btn_value("Y"):
		print("Dribbleur off")
		com.turnOffDribbler(robot_id)
		sleep(0.05)
	if joy.get_btn_value("L1"):
		print("slow mode")
		MAX_SPEED = 0.2
	if joy.get_btn_value("R1"):
		print("fast mode")
		MAX_SPEED = 1

	com.sendSpeed(robot_id, x, y, t)

	print("id:{: 3.3f} x:{: 3.3f} y:{: 3.3f} t:{: 3.3f} ".format(robot_id, x, y, t), end='')

def joystick_pygame_cli(robots_id):
	global MAX_SPEED
	MAX_SPEED = 0.2
	global current_dribbler_speed
	current_dribbler_speed = 0
	import pygame

	# Initialize
	pygame.init()
	pygame.joystick.init()
	joystick_count = pygame.joystick.get_count()

	print('# of detected joystick : {}'.format(joystick_count))

	if isinstance(robots_id, int):
		robots_id = [robots_id]   

	if joystick_count < len(robots_id):
		print("You have less robot id({}) than joystick ({})".format(len(robots_id), joystick))
		return

	robotJoystick = []
    # For each joystick:
	for i, robot_id in enumerate(robots_id):
		joystick = pygame.joystick.Joystick(i)
		joystick.init()
		robotJoystick.append((RobotJoystick(joystick), robot_id))

	com = McuCommunicator()
	# TODO fix that
	#com.setRegister(robot_id, 0x00, 1)

	while True:
		pygame.event.pump()
		for (joy, robot_id) in robotJoystick:
			do_joystick(com, joy, robot_id)
		sleep(0.05)
		print() # cariage return

