from mcu_serial_com import *
from time import sleep
import time

current_milli_time = lambda: int(round(time.time() * 1000))


def rotate_test(robot_id):
	print("Start rotate test")
	port = getFirstSerialPort()
	com = McuCom(port)

	while True:
		print("Rotate command send")
		com.sendSpeed(robot_id, 0 , 0, 1.0) # break
		sleep(0.01)

def switch_to_close_loop(robot_id):
	port = getFirstSerialPort()
	com = McuCom(port)
	print("Switch to close loop test")
	com.setRegister(robot_id,REG_CTRL_LOOP_STATE, 2)



def open_loop_test(robot_id):
    commands = []

    commands.append((6000, 0, 0, 0))

    # RAMP ..
    # for cmd in range(-40, 40, 1):
    #     commands.append((200, 0, -cmd/100, cmd/100))
    #
    # commands.append((1000, 0, -0.4, 0.4))

    do_test(1, 0, commands, robot_id)

# 0.03 max 2 wheels speed
# 0.07 max 4 wheels speed
def close_loop_test(robot_id):
    commands = [
    (10000, 0.3535, 0.3535)
    ]
    do_test(1, 1, commands, robot_id)




def do_test(ctrl_loop_state_initially, ctrl_loop_state_for_test, commands, robot_id) :
    port = getFirstSerialPort()
    #port = '/dev/ttyACM0'
    com = McuCom(port)

    # wait to contact robot
    #while not com.testHeartBeat():
    #	pass

    com.sendSpeed(robot_id,0,0,0) # break
    sleep(1)

    print("Start open loop")
    com.setRegister(robot_id,REG_CTRL_LOOP_STATE, ctrl_loop_state_for_test) # set open loop


    if ctrl_loop_state_for_test == 0:
        for (dt, wheel_set, left_wheel, right_wheel) in commands:
            print(time.time(), left_wheel, right_wheel)
            start = current_milli_time();
            while current_milli_time() - start < dt:
                com.sendSpeed(robot_id, wheel_set, left_wheel, right_wheel)  # -command
                sleep(0.05)
    else:
        for (dt, x, y) in commands:
            print(time, x, ' ', y)
            start = current_milli_time();
            while current_milli_time() - start < dt:
                com.sendSpeed(robot_id, x, y, 0) # -command
                sleep(0.05)

    #while True:
    print("Stop open loop")
    for i in range(1, 10):
    	com.sendSpeed(robot_id,0,0,0)
    	sleep(0.1)
    com.setRegister(robot_id,REG_CTRL_LOOP_STATE, ctrl_loop_state_initially) # set close loop

    com.ser.close()
