from mcu_serial_com import *

def diagnostic(robot_id):
    port = getFirstSerialPort()
    com = McuCom(port)

    try:
        while True:
            com.testHeartBeat(robot_id)
    except (KeyboardInterrupt, SystemExit):
        com.ser.close()
