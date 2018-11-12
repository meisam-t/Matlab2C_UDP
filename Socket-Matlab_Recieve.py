
import socket
import struct
import time
import gc
import random



UDP_IP = "localhost"
UDP_PORT = 12345
UDp_C_Port = 10006
UDP_PORT_send = 10005
bTime = 0

sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
sock.bind((UDP_IP, UDP_PORT))

print(" UDP connection has established on : "+str(UDP_IP))

while True:
	x1 = random.randrange(123)
	x2 = random.randrange(2342354)
	x3 = random.randrange(2342354)
	x4 = random.randrange(2342354)
	x5 = random.randrange(2342354)
	x6 = random.randrange(2342354)
	x7 = random.randrange(2342354)
	x8 = random.randrange(2342354)

	Message = struct.pack("<" + "dddddddd", x1,x2 , x3, x4, x5, x6, x7, x8)
	bTime = time.time()
	data, addr = sock.recvfrom(1024)
	mess = struct.unpack('>' + 'dddddddd', data)
	Time_interval = time.time() - bTime
	print(str(mess ) + str(Time_interval) + "\n")
	print(mess[0] , mess[1], mess[2] , mess[3],mess[4], mess[5],mess[6], mess[7])
	sock.sendto(Message,(UDP_IP,UDP_PORT_send))
