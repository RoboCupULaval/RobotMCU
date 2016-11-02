
# To install dependency : 
# pip install cobs bitstring pyserial

from threading import Thread
from time import sleep
import sys
import argparse

from mcu_serial_com import *
from open_loop_cli import *
from diagnostic import *


if __name__ == "__main__":
    print("==== pyhermes ====")
    if sys.version_info[0] < 3:
        raise "Must be python 3"

    main_parser = argparse.ArgumentParser(description='Communication utility between Robocup Robot and control station')
    main_parser.add_argument('command', choices={"ping", "test"}, help='Type of utility')


    """
    subparsers = main_parser.add_subparsers('command', choices={},help='Type of utility')
    ping_parser = subparsers.add_parser('ping', help='Search for robot to talk to')
    ping_parser.set_defaults(which='a1')
    test_parser = subparsers.add_parser('test', help='Test open loop and unit test')
    test_parser.set_defaults(which='a2')
    """
    args = main_parser.parse_args()

    if args.command == "ping":
        diagnostic()
    elif args.command == "test":
        open_loop_test()


