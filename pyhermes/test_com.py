#!/usr/bin/env python
from mcu_serial_com import *
import unittest

BAUDRATE = 19200

class TestRobotMaster(unittest.TestCase):
    def setUp(self):
        port = getFirstSerialPort()
        print('Serial device selected: ' + str(port))
        self.mcu = McuCom(port, BAUDRATE)

    def test_get_robot_name(self):
        assert self.mcu.testRobotName()




