#!/usr/bin/python

import binascii
import struct
import threading
import time
import numpy as np


class Button:

        def __init__(self, button_id):
            self.button_id = button_id
            self.value = False

        def update(self, command):
            if command['type'] == 1 and command['button'] == self.button_id:
                self.value = command['value']


class Stick:

        def __init__(self, x, y):
            self.x_value = x
            self.y_value = y
            self.coords = np.array([0., 0.])

        def update(self, command):
            if command['type'] == 2:
                if command['button'] == self.x_value:
                    self.coords[0] = command['value'] / 32767
                elif command['button'] == self.y_value:
                    self.coords[1] = command['value'] / 32767


class Joystick:
    buttons = {}

    def __init__(self):
        self.jstick_file = open("/dev/input/js0", "rb")
        self.thread = threading.Thread(target=self.updateCoords)
        self.thread.start()
        self.buttons['stick1'] = Stick(0, 1)
        self.buttons['stick2'] = Stick(3, 2)
        self.buttons['a'] = Button(0)
        self.buttons['b'] = Button(1)
        self.buttons['x'] = Button(2)
        self.buttons['y'] = Button(3)
        self.buttons['l'] = Button(10)
        self.buttons['r'] = Button(11)

    def updateCoords(self):
        while True:
            buf = self.jstick_file.read(8)
            #print(binascii.hexlify(buf))
            command = {}
            command['button'] = buf[7]
            command['type'] = buf[6]
            command['value'] = struct.unpack('h', buf[4:6])[0]
            for key, button in self.buttons.items():
                button.update(command)
            time.sleep(0)

    def __del__(self):
        file.close()
