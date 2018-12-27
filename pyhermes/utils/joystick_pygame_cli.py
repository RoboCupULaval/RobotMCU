from pyhermes.McuCommunicator import McuCommunicator, DRIBBLER_REGISTER
from time import sleep
import time
from .joystick_pygame.joystick import RobotJoystick
from math import *

SEND_FREQUENCY = 20	

def do_joystick(com, joy, robot_id):
	global MAX_SPEED
	global current_dribbler_speed
	x, y = joy.get_left_axis_vector()
	_, t = joy.get_right_axis_vector()

	x = x * MAX_SPEED
	y = y * MAX_SPEED
	t = t * 6 * MAX_SPEED / 2

	KICK_FORCE = 0
	DRIBBLE_SPEED = 0
	CHARGING = False
	if joy.get_btn_value("X"):
		print("kick")
		KICK_FORCE = 50
		# com.kick(robot_id, KICK_FORCE)
	if joy.get_btn_value("B"):
		print("pass")
		KICK_FORCE = 20
		#com.kick(robot_id, 2)
	if joy.get_btn_value("A"):
		print("Dribble on")
		DRIBBLE_SPEED = 3

	if joy.get_btn_value("Y"):
		print("Charge")
		CHARGING = True

	# if joy.get_btn_value("Y"):
	# 	print("Dribbleur off")
	#	com.turnOffDribbler(robot_id)
	if joy.get_btn_value("L1"):
		print("slow mode")
		MAX_SPEED = 0.3
	if joy.get_btn_value("R1"):
		print("fast mode")
		MAX_SPEED = 3
    
    # Don't send anything if the robot is immobile
	if abs(x) + abs(y) + abs(t) > 0.001 or True:
		#com.sendSpeed(robot_id, x, y, t)
		com.sendSpeedAdvance(robot_id, x, y, t, CHARGING, KICK_FORCE, DRIBBLE_SPEED)

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
		first_packet_no_wait = True
		for joy, robot_id in robotJoystick:
			if first_packet_no_wait:
				first_packet_no_wait = False
			do_joystick(com, joy, robot_id)
		sleep(1.0/SEND_FREQUENCY)
		print() # cariage return

