#include "Server.hpp"
#ifdef QT_EXT
#include "PackageManager.hpp"
#endif

Server::Server()
{
	isRun = false;
	sockfd = 0;
	package_Buffer.clear();
}

Server::~Server() {}

void Server::CreateServer(const char *_port)
{
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd == -1)
	{
		std::cout << "socket() error" << std::endl;
		exit(1);
	}
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(_port));
	if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
	{
		std::cout << "bind() error" << std::endl;
		exit(1);
	}
	isRun = true;
	std::cout << "Server is live!" << std::endl;
}

template <typename T>
int Server::ReceiveMessage(T buf, size_t size)
{
	return (recvfrom(sockfd, (void *)buf, size, 0,
					 (struct sockaddr *)&clnt_addr, &clnt_addr_size));
}

void Server::UpdateRecv()
{
	while (isRun)
	{
		clnt_addr_size = sizeof(clnt_addr);
		buffer_len = ReceiveMessage(buffer, BUF_SIZE);
		if (buffer_len > 0)
			HandleMessage();
	}
}

void Server::UpdateSend()
{
	char message[BUF_SIZE] = {0};
	while (isRun)
	{
		std::cin.getline(message, sizeof(message));
		memset(client_name, 0, sizeof(client_name));
		BroadcastMessageToAll(std::string("Server: ") + message);
	}
}

void Server::Int32Package(int32_t value)
{
#ifdef QT_EXT
	PackageManager::int32_Paketle(&package_Buffer, value);
#else
	uint8_t *bytes = reinterpret_cast<uint8_t *>(&value);
	std::vector<uint8_t> byteArrayVector(bytes, bytes + sizeof(int32_t));
	package_Buffer.push_back(byteArrayVector);
#endif
}

void Server::HandleMessage()
{
	// handle data from a client
	char code = buffer[0];
	GetClientName(buffer);
	if (code == '0') // login client
	{
		all_clients.insert(std::pair<std::string, struct sockaddr_in>(client_name, clnt_addr));
		std::cout << "clients size: " << all_clients.size() << std::endl;
		std::cout << client_name << " Join" << std::endl;
	}
	else if (code == '1') // send message
	{
		std::cout << buffer << std::endl;
		BroadcastMessageToAll(buffer);
	}
	else if (code == '2') // get package
	{
		int32_t data;
		ReceiveMessage(&data, sizeof(data));
		Int32Package(data);
	}
	else if (code == '3') // print packages and clear Buffer
	{
#ifdef QT_EXT
		qDebug() << package_Buffer.toHex();
#else
		// Print the byte arrays from the vector
		for (size_t i = 0; i < package_Buffer.size(); i++)
		{
			std::stringstream ss;
			ss << std::hex << std::setfill('0');
			for (size_t j = 0; j < package_Buffer[i].size(); j++)
			{
				ss << std::setw(2) << static_cast<unsigned>(package_Buffer[i].data()[j]);
			}
			std::cout << ss.str() << " ";
		}
#endif
		package_Buffer.clear();
		std::cout << std::endl;
	}
	else if (code == '4') // logout client
	{
		for (auto const &client : all_clients)
		{
			if (client.first.compare(client_name) == 0)
			{
				std::cout << client.first << " Left" << std::endl;
				all_clients.erase(client.first);
				break;
			}
		}
		std::cout << "clients size: " << all_clients.size() << std::endl;
		if (all_clients.size() == 0)
			CloseConnection();
	}
	memset(buffer, 0, buffer_len);
}

void Server::BroadcastMessageToAll(std::string _message)
{
	for (auto const &client : all_clients)
	{
		if (client.first.compare(client_name) != 0)
		{
			sendto(sockfd, _message.c_str(), _message.length(), 0,
				   (struct sockaddr *)&client.second, clnt_addr_size);
		}
	}
}

void Server::CloseConnection()
{
	std::cout << "No Client left. Server is closed!" << std::endl;
	isRun = false;
	shutdown(sockfd, SHUT_RDWR);
	exit(0);
}

// utils
void Server::GetClientName(std::string _message)
{
	// clear client_name
	memset(client_name, 0, sizeof(client_name));
	// get client name
	for (size_t i = 2; i < _message.length(); i++)
	{
		if (_message[i] == ':')
			break;
		client_name[i - 2] = _message[i];
	}
}
