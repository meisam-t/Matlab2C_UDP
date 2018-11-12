#include <stdio.h>
#include <winsock.h>
#include <iostream>
#include <io.h>
#pragma comment(lib,"ws2_32.lib")	//Winsock Library

void error(const char *);

int main()
{
	WSAData data;
	WSAStartup(MAKEWORD(2, 2), &data);

	int sock, length, n;
	int fromlen;
	struct sockaddr_in server;
	struct sockaddr_in from;
	char message_recv[sizeof(double) * 8];
	char buf[1024];
	unsigned short serverPort = 12345;
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0) error("Opening socket");
	length = sizeof(server);
	memset(&server, 0, length);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(serverPort);
	if (bind(sock, (struct sockaddr *)&server, length) < 0) error("binding");
	fromlen = sizeof(struct sockaddr_in);
	while (1)
	{
		n = recvfrom(sock, buf, 1024, 0, (struct sockaddr *)&from, &fromlen);
		memcpy(&message_recv, buf, sizeof(buf));
		if (n < 0) error("recvfrom");
		//write(1,"Received a datagram: ", 21);
		//write(1,buf,n);
		//printf("Received a datagram: %lf\n", buf[7] >> 56);
		printf("Server: The data is \"%F%F%F%F%F%F%F%F\"\n", (buf[7] << 56), (buf)[6] << 48), (buf[5] << 40), (buf[4] << 32), (buf[3] << 24), (buf[2] << 16), (buf[1] << 8), (buf[0]);

		//printf("Server: The data is \"%f\"\n", (buf[7] >>56)| (buf)[1] << 48)| (buf[2] << 40)| (buf[3] << 32)| (buf[4] << 24)| (buf[5] << 16)| (buf[6] << 8)| (buf[7]);

		//printf("Data: %s\n", &message_recv[1]);
		//printf("Server: The data is \"%d\"\n", (message_recv[0] << 56) | (message_recv)[6] << 48) | (message_recv[5] << 40) | (message_recv[4] << 32) | (message_recv[3] << 24) | (message_recv[2] << 16) | (message_recv[1] << 8) | (message_recv[0]);

		n = sendto(sock, "Got your message\n", 17, 0, (struct sockaddr *)&from, fromlen);
		if (n < 0)error("sendto");
	}
	closesocket(sock);
	WSACleanup();
	return 0;
}


void error(const char *msg)
{
	perror(msg);
	exit(0);
}