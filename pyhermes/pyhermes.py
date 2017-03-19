#!/usr/bin/env python3

# To install dependency : 
# pip install cobs bitstring pyserial

from threading import Thread
from time import sleep
import sys
import argparse
import csv

from mcu_serial_com import *
from ctrl_test_cli import *
from joystick_cli import joystick_cli
from joystick_pygame_cli import joystick_pygame_cli
from diagnostic import *


if __name__ == '__main__':
    print('==== pyhermes ====')
    if sys.version_info[0] < 3:
        raise 'Must be python 3'

    main_parser = argparse.ArgumentParser(description='Utilities for communication between ULtron robots and base station')

    subparsers = main_parser.add_subparsers(dest='command')

    ping_parser = subparsers.add_parser('ping', help='Send ping to a robot')
    ping_parser.add_argument('robot_id', type=int, help='ID of the robot')

    joystick_parser = subparsers.add_parser('joystick', help='Control a robot using a joystick')
    joystick_parser.add_argument('--pygame', action='store_true', help='Use pygame cli over default linux one')
    joystick_parser.add_argument('robot_id', type=int, help='ID of the robot')

    ctrl_parser = subparsers.add_parser('ctrl_test', help='Test a robot control loop with custom commands')
    ctrl_parser.add_argument('ctrl_loop_type', choices={'open_loop', 'close_loop'}, help='Type of control loop')
    ctrl_parser.add_argument('speed_commands_file', type=str, help='Path to the txt file containing rows of speed commands')
    ctrl_parser.add_argument('robot_id', type=int, help='ID of the robot')


    args = main_parser.parse_args()

    print(args)

    if args.command == 'ping':
        diagnostic(args.robot_id)

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


