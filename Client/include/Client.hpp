#pragma once

#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>
#include <sstream>
#include <vector>

#define BUF_SIZE 1024

class Client
{
public:
	Client();
	~Client();

	void ConnectToServer(const char *_ip, const char *_port);
	void SendUpdate();
	void ReceiveUpdate();
	void SendMessage(char _cmd, std::string _message);
	void SendPackage(int32_t data);
	void CloseConnection();

private:
	char name[BUF_SIZE] = {0};
	char buffer[BUF_SIZE] = {0};
	int sockfd;
	int buffer_len;
	struct sockaddr_in serv_addr;
	bool isRun;
};