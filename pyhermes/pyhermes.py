
# To install dependency : 
# pip install cobs bitstring pyserial

from threading import Thread
from time import sleep
from mcu_serial_com import *


if __name__ == "__main__":
    print("==== pyhermes ====")
    port = getFirstSerialPort()

    com = McuCom(port, 9600) #115200
    quitting = False
    def listener():
        while True:
            buf = ""
            while not '\n' in buf:
                if quitting:
                    return
                buf += '' #str(com.ser.read(1))
            print(buf)

    #thread = Thread(target = listener)
    #thread.start()

    try:
        while True:
            com.testHeartBeat()
            #sleep(1)
    except (KeyboardInterrupt, SystemExit):
        quitting = True
        #thread.join()
        com.ser.close()


