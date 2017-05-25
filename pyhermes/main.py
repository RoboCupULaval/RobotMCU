#!/usr/bin/env python3
""" This is the main interface script to interact directly with pyhermes
and other included test tools."""

import sys
import argparse
import csv

from utils.ctrl_test_cli import *
from utils.joystick_cli import joystick_cli
from utils.joystick_pygame_cli import joystick_pygame_cli
from utils.diagnostic import *


if __name__ == '__main__':
    print('==== Pyhermes simple usage interface ====')
    if sys.version_info[0] < 3:
        raise 'You are not using python3!'

    my_description = 'Utilities for communication between ULtron robots and base station'

    main_parser = argparse.ArgumentParser(description=my_description)

    subparsers = main_parser.add_subparsers(dest='command')

    ping_parser = subparsers.add_parser('ping', help='Send ping to a robot')
    ping_parser.add_argument('robot_id', type=int, help='ID of the robot')

    find_robot_parser = subparsers.add_parser('find_robots', help='Find robot and print there batterie level')

    packet_lost_parser = subparsers.add_parser('test_packet_lost', help='Test number of packet lost in a unidirectional communication')
    packet_lost_parser.add_argument('robot_id', type=int, help='ID of the robot')

    ping_parser=subparsers.add_parser('test_rotate',
                                        help='Send a rotation command to the robot')
    ping_parser.add_argument('robot_id', type=int, help='ID of the robot')

    joystick_parser = subparsers.add_parser('joystick', help='Control a robot using a joystick')
    joystick_parser.add_argument('--pygame', action='store_true', help='Use pygame cli over default linux one')
    joystick_parser.add_argument('robot_id', type=int, help='ID of the robot')

    ctrl_parser = subparsers.add_parser('ctrl_test', help='Test a robot control loop with custom commands')
    ctrl_parser.add_argument('ctrl_loop_type', choices={'open_loop', 'close_loop'}, help='Type of control loop')
    ctrl_parser.add_argument('speed_commands_file', type=str, help='Path to the txt file containing rows of speed commands')
    ctrl_parser.add_argument('robot_id', type=int, help='ID of the robot')


    args = main_parser.parse_args()

    if args.command == 'ping':
        ping(args.robot_id)
    elif args.command == 'find_robots':
        find_robots()
    elif args.command == 'test_packet_lost':
        test_packet_lost(args.robot_id)
    elif args.command == 'joystick':
        if args.pygame:
            joystick_pygame_cli(args.robot_id)
        else:
            joystick_cli(args.robot_id)

    elif args.command == 'ctrl_test':
        commands = []
        with open(args.speed_commands_file, 'r') as f:
            reader = csv.reader(f)
            commands = []
            for row in reader:
                cmd = tuple(float(i) for i in row)
                commands.append(cmd)
        if args.ctrl_loop_type == 'open_loop':
            open_loop_test(args.robot_id, commands)
        else:
            close_loop_test(args.robot_id, commands)

    elif args.command == 'test_rotate':
        rotate_test(args.robot_id)

    elif args.command is None:
        print("You probably want to use the --help option!")

