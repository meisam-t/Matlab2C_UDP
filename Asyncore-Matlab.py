

import asyncore
import socket
import struct
import time


UDP_IP = "localhost"
UDP_PORT = 12345
bTime = 0
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((UDP_IP, UDP_PORT))
class AsyncoreServerUDP(asyncore.dispatcher):
	def __init__(self):
		asyncore.dispatcher.__init__(self)
		self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
		self.sock.bind((UDP_IP, UDP_PORT))
		print ("System ready on "+str(UDP_IP))
	
	#Even though UDP is connectionless this is called when it binds to a port
	def handle_connect(self):
		print ("Server Started...")

	# This is called everytime there is something to read
	while True:
		bTime = time.time()
		data, addr = sock.recvfrom(1024)
		mess = struct.unpack('>' + 'dddddddd', data)
		Time_interval = time.time() - bTime
		print(str(mess) + str(Time_interval) + "\n")
		print(mess[0], mess[1], mess[2], mess[3], mess[4], mess[5], mess[6], mess[7])

	# This is called all the time and causes errors if you leave it out.
	def handle_write(self):
		pass

AsyncoreServerUDP()
asyncore.loop()