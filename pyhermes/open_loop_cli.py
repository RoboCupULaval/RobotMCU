from mcu_serial_com import *
from time import sleep

def open_loop_test():
    port = getFirstSerialPort()
    com = McuCom(port)

    while not com.testHeartBeat():
    	pass
        

    com.sendSpeed(0,0,0) # break
    sleep(1)
    com.setRegister(REG_CTRL_LOOP_STATE, 0) # set open loop

    print("Start open loop")
    com.sendSpeed(1,0,0) # break
    sleep(1)
    com.sendSpeed(0,0,0) # break

    print("Stop open loop")
    com.setRegister(REG_CTRL_LOOP_STATE, 1) # set close loop

    com.ser.close()
