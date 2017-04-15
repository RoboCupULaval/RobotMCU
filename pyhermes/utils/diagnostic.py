from pyhermes.McuCommunicator import McuCommunicator

def diagnostic(robot_id):
    port = getFirstSerialPort()
    com = McuCom(port)

    try:
        while True:
            com.testHeartBeat(robot_id)
    except (KeyboardInterrupt, SystemExit):
        com.ser.close()
