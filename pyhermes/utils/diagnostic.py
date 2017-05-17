from pyhermes.McuCommunicator import McuCommunicator
import time

def diagnostic(robot_id):
	com = McuCommunicator()

	print("Ping robot {}... ".format(robot_id))
	try:
		while True:
			start_time = time.time()
			if com.testHeartBeat(robot_id):
				elapse_time = time.time() - start_time
				print("[SUCCESS] Ping took {:5.2f}ms".format(elapse_time * 1000.0))
			else:
				print("[ERROR] Timeout")

				time.sleep(1)
	except (KeyboardInterrupt, SystemExit):
		com.serial_port.close()
