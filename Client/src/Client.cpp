#include "Client.hpp"

Client::Client() { isRun = false; }

Client::~Client() {}

void Client::ConnectToServer(const char *_ip, const char *_port)
{
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd == -1)
	{
		std::cout << "socket() error" << std::endl;
		exit(1);
	}
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(_ip);
	serv_addr.sin_port = htons(atoi(_port));

	// Get user name
	std::cout << "username: ";
	std::cin.getline(name, sizeof(name));
	if (strlen(name) == 0)
	{
		std::cerr << "Invalid name" << std::endl;
		exit(1);
	}

	// let server know that we're here
	std::string joinMessage = std::string("0:") + name + ": joined.";
	SendMessage('0', joinMessage); // login action
	isRun = true;
	std::cout << "Welcome " << name << std::endl;
}

void Client::SendUpdate()
{
	while (isRun)
	{
		std::cin.getline(buffer, sizeof(buffer));
		if (strncmp(buffer, "/package", strlen("/package")) == 0) // send package
		{
			std::stringstream ss(buffer);
			std::string item;
			int32_t data;
			while (std::getline(ss, item, ' '))
			{
				if (item != "/package")
				{
					try
					{
						data = std::stoi(item);
						SendMessage('2', ""); // package action
						SendPackage(data);
					}
					catch (const std::invalid_argument &e)
					{
						std::cout << "Invalid argument" << std::endl;
					}
				}
			}
			SendMessage('3', "sent all int32 packages"); // end of package action
		}
		else if (strcmp(buffer, "/logout") == 0)
		{
			std::string leaveMessage = std::string(name) + " left.";
			SendMessage('4', leaveMessage); // logout action
			memset(buffer, 0, BUF_SIZE);
			std::cout << "Logged out" << std::endl;
			CloseConnection();
			return; // exit thread
		}
		else // send message
			SendMessage('1', std::string(buffer));
	}
}

void Client::ReceiveUpdate()
{
	while (isRun)
	{
		buffer_len = recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);
		if (buffer_len == -1)
			exit(1);
		else
			std::cout << buffer << std::endl;
		memset(buffer, 0, buffer_len);
	}
}

void Client::SendMessage(char _cmd, std::string _message)
{
	std::string fullMessage = "";
	fullMessage = std::string(1, _cmd) + ":" + name + ":" + _message + "\0";
	if (sendto(sockfd, fullMessage.c_str(), fullMessage.length(), 0,
			   (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
	{
		CloseConnection();
		exit(1);
	}
}

void Client::SendPackage(int32_t data)
{
	if (sendto(sockfd, &data, sizeof(int32_t), 0,
			   (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
	{
		CloseConnection();
		exit(1);
	}
}

void Client::CloseConnection()
{
	isRun = false;
	shutdown(sockfd, SHUT_RDWR);
}
