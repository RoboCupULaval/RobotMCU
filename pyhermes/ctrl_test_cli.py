from mcu_serial_com import *
from time import sleep
import time

current_milli_time = lambda: int(round(time.time() * 1000))


def open_loop_test(robot_id, commands):
    # commands = []
    #
    # commands.append((6000, 0, 0, 0, 0))

    # RAMP ..
    # for cmd in range(-40, 40, 1):
    #     commands.append((200, 0, -cmd/100, 0, cmd/100))
    #
    # commands.append((1000, 0, -0.4, 0, 0.4))

    do_test(1, 0, commands, robot_id)

# 0.03 max 2 wheels speed
# 0.07 max 4 wheels speed
def close_loop_test(robot_id, commands):
    # commands = [
    # (10000, 0.3535, 0.3535, 0)
    # ]
    do_test(1, 1, commands, robot_id)


def do_test(ctrl_loop_state_initially, ctrl_loop_state_for_test, commands, robot_id) :
    port = getFirstSerialPort()
    com = McuCom(port)

    # wait to contact robot
    #while not com.testHeartBeat():
    #	pass

    com.sendSpeed(robot_id,0,0,0) # break
    com.sendOpenLoopSpeed(robot_id,0,0,0,0) # break
    sleep(1)

    com.setRegister(robot_id, REG_CTRL_LOOP_STATE, ctrl_loop_state_for_test)


    if ctrl_loop_state_for_test == 0:
        print("Start open loop")
        for (dt, w1, w2, w3, w4) in commands:
            print(time.time(), w1, ' ', w2, ' ', w3, ' ', w4)
            start = current_milli_time()
            while current_milli_time() - start < dt:
                com.sendOpenLoopSpeed(robot_id, w1, w2, w3, w4)  # -command
                sleep(0.05)
        print("Stop open loop")
        for i in range(1, 10):
            com.sendOpenLoopSpeed(robot_id, 0, 0, 0, 0)
            sleep(0.1)
    else:
        print("Start close loop")
        for (dt, vx, vy, vtheta) in commands:
            print(time.time(), vx, ' ', vy, ' ', vtheta)
            start = current_milli_time()
            while current_milli_time() - start < dt:
                com.sendSpeed(robot_id, vx, vy, vtheta) # -command
                sleep(0.05)

        print("Stop close loop")
        for i in range(1, 10):
            com.sendSpeed(robot_id, 0, 0, 0)
            sleep(0.1)


    com.setRegister(robot_id, REG_CTRL_LOOP_STATE, ctrl_loop_state_initially) # set close loop

    com.ser.close()
