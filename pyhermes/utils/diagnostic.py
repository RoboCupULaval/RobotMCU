from serial.serialutil import SerialTimeoutException

from pyhermes.McuCommunicator import McuCommunicator
import sched, time


def ping(robot_id):
	com = McuCommunicator()

	PING_FREQUENCY = 100
	PING_PERIOD = 1.0/PING_FREQUENCY
	print("Ping robot {} at {}hz@{}ms".format(robot_id, PING_FREQUENCY, PING_PERIOD*1000))

	max_ping_time = 0
	nb_send = 0
	nb_timeout = 0
	sum_time = 0.0
	try:
		while True:
			start_time = time.time()
			if com.testHeartBeat(robot_id):
				elapse_time = time.time() - start_time
				sum_time += elapse_time
				max_ping_time = max(elapse_time, max_ping_time)
				print("[SUCCESS] Ping took {:5.2f}ms".format(elapse_time * 1000.0))
			else:
				elapse_time = time.time() - start_time
				print("[ERROR] Timeout {:5.2f}ms".format(elapse_time * 1000.0))
				nb_timeout += 1
			nb_send += 1

			time.sleep(PING_PERIOD)
	except (KeyboardInterrupt, SystemExit):
		com.serial_port.close()
		print("==== RESULT ====")
		nb_success = nb_send - nb_timeout
		print("Avg:{:5.2f} Max:{:5.2f} Success:{:5.2f}% Timeout/send:{}/{}".format(sum_time/nb_success, max_ping_time*1000.0, float(nb_success)/nb_send*100.0, nb_timeout, nb_send, ))

def find_robots():
	com = McuCommunicator(timeout=0.05)

	while True:
		batteries = {}
		for id in range(1, 7):
			batterie_lvl = com.getBatterie(id)
			if batterie_lvl:
				batteries[id] = batterie_lvl
		if len(batteries) == 0:
			print("No robot found.")
		else:
			print(batteries)

		time.sleep(1.0)



def get_num_request(com, robot_id):
	flag = True
	while flag:
		try:
			num_request = com.getNumRequest(robot_id)
		except SerialTimeoutException:
			print("Timeout on serial com, retrying")
			continue
		flag = False
	return num_request



def test_packet_lost(robot_id):
	com = McuCommunicator(timeout = 0.5)

	NUMBER_PACKET = 500
	REQUEST_FREQUENCY = 20
	REQUEST_PERIOD = 1.0/REQUEST_FREQUENCY

	print("Sending {} packet at {}hz@{}ms".format(NUMBER_PACKET, REQUEST_FREQUENCY, REQUEST_PERIOD*1000.0))

	sc = sched.scheduler(time.time, time.sleep)

	start_num_request = get_num_request(com, robot_id)
	#start_num_request += 1 # Take into account the getNumRequest packet in the count
	start = time.time()
	def loop_send_packet(sc, nb_left):
		if nb_left > 0:
			sc.enter(REQUEST_PERIOD, 1, loop_send_packet, (sc, nb_left-1,))
		com.sendSpeed(robot_id, 0, 0, -1.0)  # Any unidirectionnal command could be use here to benchmark

	sc.enter(REQUEST_PERIOD, 1, loop_send_packet, (sc, NUMBER_PACKET-1,))
	sc.run()
	timelapse = time.time() - start
	#print("It tooks {:5.2f}s expects {:5.2f}".format(timelapse, NUMBER_PACKET*REQUEST_PERIOD))

	end_num_request = get_num_request(com, robot_id)
	num_request = end_num_request - start_num_request
	num_request &= 0xFFFFFFFF  # 32 bit mask

	print("{} request send, {} received, {:5.2f}% received in {:5.2f}s.".format(NUMBER_PACKET, num_request, float(num_request)/NUMBER_PACKET * 100.0, timelapse))
	if num_request > NUMBER_PACKET:
		print("Too much packet? start={}, end={} num_request={}".format(start_num_request, end_num_request, num_request))
