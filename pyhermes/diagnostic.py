from mcu_serial_com import *

def diagnostic():
    port = getFirstSerialPort()
    com = McuCom(port)

    try:
        while True:
            com.testHeartBeat()
    except (KeyboardInterrupt, SystemExit):
        com.ser.close()
