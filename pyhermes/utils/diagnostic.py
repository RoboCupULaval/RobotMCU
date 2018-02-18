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

		time.sleep(0.5)



def get_num_request(com, robot_id):
	first_timeout = True
	while True:
		try:
			num_request = com.getNumRequest(robot_id)
		except SerialTimeoutException:
			if first_timeout:
				print("[ROBOT {}] Timeout on serial com, retrying".format(robot_id), end="", flush=True)
				first_timeout = False
			else:
				print(".", end="", flush=True)
			continue
		print()
		return num_request

"""
====Issue #18====
Remarques:
Peut importe la fréquence d'envoie, peut importe le temps entre les packets
Tous les packets perdus ont été ack
Un seul packet est envoyé par robot. Si un appel bi est faite, un seul autre packet peut être renvoyé
== Liste des tests ==
11223344 -> OK
12       -> OK
123      -> OK
1234     -> X    -> Tous les packets sont envoyé par le nrf, MAIS chaque robot ne recoit qu'un packet
12345    -> OK
1122     -> OK
1123     -> X    -> Le robot 1 OK, 2 et 3 recoit 1 seul packet
2213     -> X    -> Le robot 2 OK, 1 et 3 recoit 1 seul packet -> Invariant des id
1213     -> X    -> Le robot 1 OK, 2 et 3 recoit 1 seul packet -> Invariant de l'ordre
112      -> OK  
1112     -> X    -> Le robot 1 OK et le robot 2 recoit 1 seul packet -> 3x packet de 1 cause le 2 de brisé
11112    -> OK    
11122    -> X    -> Le robot 1 OK et le robot 2 recoit la moitié des packets + 1
11212    -> OK
12112    -> OK
111223   -> X    -> Le robot 1 2/3 des packets +1, 2 et 3 ok  -> le 1 à un de ses packets qui trigger le bug
111222   -> X    -> Le robot 1 et 2 recoient 2/3 des packets +1

==================
1234|1234
     ^^^^----- Recoit AUCUN packet
1112|1112
        ^----- Recoit AUCUN packet
1123|1123
	   ^^----- Recoit AUCUN packet 
1213|1213
	  ^-^----- Recoit AUCUN packet 
11122|11122
         ^---- Recoit AUCUN packet
111223|111223
       ^------ Recoit AUCUN packet
111222|111222
       ^--^--- Recoit AUCUN packet

1222112211|1222112211
    ^-------^--^- Recoit AUCUN packet


S'il y a trois call vers un autre robot entre deux transmitions, la deuxième transmition est perdu

"""
def test_packet_lost(robots_id):
	com = McuCommunicator(timeout = 0.5)

	DURATION_IN_S = 2
	REQUEST_FREQUENCY = 4
	NUMBER_PACKET = DURATION_IN_S * REQUEST_FREQUENCY
	REQUEST_PERIOD = 1.0/REQUEST_FREQUENCY

	TIME_WAIT_BETWEEN_PACKET = 0.0  # 0.005s seem to make a different with more than 3 robots [fixed]
	
	print("Sending {} packet at {}hz@{}ms".format(NUMBER_PACKET, REQUEST_FREQUENCY, REQUEST_PERIOD*1000.0))

	start_num_request = [get_num_request(com, id) for id in robots_id]
	
	# We wait for the fifo to clear...
	input("Press enter after you check the fifo")

	#start_num_request += 1 # Take into account the getNumRequest packet in the count
	print("Starting test...")
	def loop_send_packet(sc, nb_left):
		if nb_left > 0:
			sc.enter(REQUEST_PERIOD, 1, loop_send_packet, (sc, nb_left-1,))

		#for idx, id in enumerate(robots_id):
		for idx, id in enumerate([2,1,1,1,1,1,1,2]):
			if idx != 0 and TIME_WAIT_BETWEEN_PACKET != 0.0:
				time.sleep(TIME_WAIT_BETWEEN_PACKET)
			print("Send to robot {}".format(id))
			input("continue?")
			com.sendSpeed(id, 0, 0, 0.5)  # Any unidirectionnal command could be use here to benchmark
		

	sc = sched.scheduler(time.time, time.sleep)
	sc.enter(REQUEST_PERIOD, 1, loop_send_packet, (sc, (NUMBER_PACKET)-1,))
	start = time.time()
	sc.run()
	timelapse = time.time() - start
	print("It tooks {:5.2f}s expects {:5.2f}".format(timelapse, NUMBER_PACKET*REQUEST_PERIOD))

	input("Press enter to check results")

	total_failure_rate = 0
	for index, id in enumerate(robots_id):
		end_num_request = get_num_request(com, id)
		num_request = end_num_request - start_num_request[index]
		num_request &= 0xFFFFFFFF  # 32 bit mask for handling integer overflow

		failure_ratio = 1.0 - float(num_request) / NUMBER_PACKET
		total_failure_rate += failure_ratio / len(robots_id)
		print("[ROBOT {}] {} request send, {:3} received, {:5.2f}% lost in {:5.2f}s.".format(id, NUMBER_PACKET, num_request, failure_ratio * 100.0, timelapse))
		if num_request > NUMBER_PACKET:
			print("Too much packet? start={}, end={} num_request={}".format(start_num_request[index], end_num_request, num_request))
	print("Total failure rate={:5.2f}%".format(total_failure_rate * 100.0))
