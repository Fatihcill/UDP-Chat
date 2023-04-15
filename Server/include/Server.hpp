#pragma once

#include <string.h>
#include <netdb.h>
#include <map>
#include <iostream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#ifdef QT_EXT
#include <QByteArray>
#endif

#define BUF_SIZE 1024

class Server
{
public:
	Server();
	~Server();

	void CreateServer(const char *_port);
	void UpdateRecv();
	void UpdateSend();
	void HandleMessage();
	void BroadcastMessageToAll(std::string _message);
	void CloseConnection();
	// template function which is name of ReceiveMessage
	template <typename T>
	int ReceiveMessage(T buf, size_t size);
	void Int32Package(int32_t value);

private:
#ifdef QT_EXT
	QByteArray package_Buffer;
#else
	std::vector<std::vector<uint8_t>> package_Buffer;
#endif

	int sockfd;
	int buffer_len;
	struct sockaddr_in serv_addr, clnt_addr;
	socklen_t clnt_addr_size;
	char buffer[BUF_SIZE] = {0};
	bool isRun;
	struct addrinfo hints, *addressInfo, *point;

	std::map<std::string, struct sockaddr_in> all_clients;
	char client_name[BUF_SIZE] = {0};
	// utils
	void GetClientName(std::string _message);
};
