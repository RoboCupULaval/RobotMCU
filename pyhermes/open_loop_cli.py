from mcu_serial_com import *
from time import sleep
import time

current_milli_time = lambda: int(round(time.time() * 1000))

def open_loop_test():
    port = getFirstSerialPort()
    com = McuCom(port)

    # wait to contact robot
    while not com.testHeartBeat():
    	pass

    com.sendSpeed(0,0,0) # break
    sleep(1)

    print("Start open loop")
    com.setRegister(REG_CTRL_LOOP_STATE, 0) # set open loop

    # free wheel 0.3, 0.6, 1.0
    commands = [
    (1700, 0.5),
    (1500, 0.55)
    ]

    for (dt, command) in commands:
    	print(time, command)
    	start = current_milli_time();
    	while current_milli_time() - start < dt:
    		com.sendSpeed(-command, command, 0)

    #while True:
    print("Stop open loop")
    com.sendSpeed(0,0,0)
    com.setRegister(REG_CTRL_LOOP_STATE, 1) # set close loop

    com.ser.close()
.41