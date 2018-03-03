from pyhermes.McuCommunicator import McuCommunicator, DRIBBLER_REGISTER
from time import sleep
import time
from .joystick_pygame.joystick import RobotJoystick
from math import *

SEND_FREQUENCY = 100

class Robot:
	def __init__(self, id, speed):
		self.id = id
		self.speed = speed

FAST_SPEED = 0.8
SLOW_SPEED = 0.4

def do_joystick(com, joy, robot):
	x, y = joy.get_left_axis_vector()
	_, t = joy.get_right_axis_vector()

	x = x * robot.speed
	y = y * robot.speed
	t = t * 6 * robot.speed


	if joy.get_btn_value("X"):
		print("kick")
		com.kick(robot.id, 5)
	if joy.get_btn_value("B"):
		print("pass")
		com.kick(robot.id, 2)
	if joy.get_btn_value("A"):
		print("charge")
		com.charge(robot.id)
	if joy.get_btn_value("select"):
		print("Dribbleur on")
		com.turnOnDribbler(robot.id)
		#new_speed = 2
		#print("Dribbleur set to ", new_speed)
		#com.setRegister(robot_id, DRIBBLER_REGISTER, new_speed)
	# 	current_dribbler_speed = new_speed
	# 	sleep(0.05)
	if joy.get_btn_value("Y"):
		print("Dribbleur off")
		com.turnOffDribbler(robot.id)
	if joy.get_btn_value("L1"):
		print("slow mode")
		robot.speed = SLOW_SPEED
	if joy.get_btn_value("R1"):
		print("fast mode")
		robot.speed = FAST_SPEED
    
    # Don't send anything if the robot is immobile
	if abs(x) + abs(y) + abs(t) > 0.001 or True:
		com.sendSpeed(robot.id, x, y, t)

	print("[{}] x:{: 3.3f} y:{: 3.3f} t:{: 3.3f} | ".format(robot.id, x, y, t), end='')

def joystick_pygame_cli(robots_id):
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
		robotJoystick.append((RobotJoystick(joystick), Robot(robot_id, SLOW_SPEED)))

	com = McuCommunicator()
	# TODO fix that
	#com.setRegister(robot_id, 0x00, 1)

	while True:
		pygame.event.pump()
		first_packet_no_wait = True
		for joy, robot in robotJoystick:
			if first_packet_no_wait:
				first_packet_no_wait = False
			do_joystick(com, joy, robot)
		sleep(1.0/SEND_FREQUENCY)
		print() # cariage return

