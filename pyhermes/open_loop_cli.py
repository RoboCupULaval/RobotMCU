from mcu_serial_com import *
from time import sleep
import time

current_milli_time = lambda: int(round(time.time() * 1000))

def open_loop_test():
    commands = [
    (2000, 0.15),
    (3000, 0.2)
    ]
    do_test(1, 0, commands)

def close_loop_test():
    commands = [
    (1700, 200),
    (500,  0)
    ]
    do_test(1, 2, commands)


def do_test(ctrl_loop_state_initially, ctrl_loop_state_for_test, commands) :
    port = getFirstSerialPort()
    #port = '/dev/ttyACM0'
    com = McuCom(port)

    # wait to contact robot
    #while not com.testHeartBeat():
    #	pass

    com.sendSpeed(0,0,0) # break
    sleep(1)

    print("Start open loop")
    com.setRegister(REG_CTRL_LOOP_STATE, ctrl_loop_state_for_test) # set open loop


    for (dt, command) in commands:
    	print(time, command)
    	start = current_milli_time();
    	while current_milli_time() - start < dt:
    		com.sendSpeed(-command, command, 0) # -command
    		sleep(0.1)

    #while True:
    print("Stop open loop")
    for i in range(1, 10):
    	com.sendSpeed(0,0,0)
    	sleep(0.1)
    com.setRegister(REG_CTRL_LOOP_STATE, ctrl_loop_state_initially) # set close loop

    com.ser.close()