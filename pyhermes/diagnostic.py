from mcu_serial_com import *

def diagnostic():
    port = getFirstSerialPort()
    com = McuCom(port, robot_id=robot_id)

    try:
        while True:
            com.testHeartBeat()
    except (KeyboardInterrupt, SystemExit):
        com.ser.close()
