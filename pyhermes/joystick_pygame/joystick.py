import pygame
import json
import time
from math import fabs

pygame.display.set_mode([1,1])

with open('joystick_config.json') as configsFile:
    configs = json.load(configsFile)


class RobotJoystick():

    """ X : is up/down and Y is left/right, ranging from 1.0 to -1.0 with up and right being positive values"""

    def __init__(self, joystick):
        self.joystick = joystick
        self.deadZone = 0.05
        self.config = configs[joystick.get_name()]

    def getBtnValue(self, btn):
        return self.joystick.get_button(self.config['buttons'][btn])

    def getLeftAxisVector(self):
        x = self.joystick.get_axis(self.config['axis']['left']['updown']['id']) * self.config['axis']['left']['updown']['up']
        y = self.joystick.get_axis(self.config['axis']['left']['leftright']['id']) * self.config['axis']['left']['leftright']['left']

        if fabs(x) < self.deadZone:
            x = 0
        if fabs(y) < self.deadZone:
            y = 0

        return x, y

    def getRightAxisVector(self):
        x = self.joystick.get_axis(self.config['axis']['right']['updown']['id']) * self.config['axis']['right']['updown']['up']
        y = self.joystick.get_axis(self.config['axis']['right']['leftright']['id']) * self.config['axis']['right']['leftright']['left']

        if fabs(x) < self.deadZone:
            x = 0
        if fabs(y) < self.deadZone:
            y = 0

        return x, y

    def getDPadVector(self):
        x = self.joystick.get_hat(self.config['dpad']['updown']['id']) * self.config['dpad']['updown']['up']
        y = self.joystick.get_hat(self.config['dpad']['leftright']['id']) * self.config['dpad']['leftright']['left']

        if fabs(x) < self.deadZone:
            x = 0
        if fabs(y) < self.deadZone:
            y = 0

        return x, y

if __name__ == '__main__':
    # Initialize
    pygame.init()
    pygame.joystick.init()
    joystick_count = pygame.joystick.get_count()

    print(joystick_count)

    robotJoystick = []

    # For each joystick:
    for i in range(joystick_count):
        joystick = pygame.joystick.Joystick(i)
        joystick.init()
        robotJoystick.append(RobotJoystick(joystick))

    while True:
        pygame.event.pump()
        for i in range(joystick_count):
            print(str(robotJoystick[i].getLeftAxisVector()) + '\n')
            print(str(robotJoystick[i].getBtnValue('X')))

        time.sleep(0.001)