#include "Client.hpp"
#include <thread>

Client client;
std::thread readthread, writethread;

void readfunc()
{
	client.ReceiveUpdate();
}

void writefunc()
{
	client.SendUpdate();
}

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		std::cout << "Usage: " << argv[0] << " <IP> <port>" << std::endl;
		exit(1);
	}
	client.ConnectToServer(argv[1], argv[2]);

	readthread = std::thread(readfunc);
	writethread = std::thread(writefunc);
	writethread.join();
	readthread.join();

	return 0;
}
