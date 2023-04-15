#include "Server.hpp"
#include <thread>

Server sv;
std::thread readthread, writethread;

void readfunc()
{
	sv.UpdateRecv();
}

void writefunc()
{
	sv.UpdateSend();
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cout << "Usage: " << argv[0] << " <port>" << std::endl;
		exit(1);
	}
	sv.CreateServer(argv[1]);

	std::thread readthread = std::thread(readfunc);
	std::thread writethread = std::thread(writefunc);

	readthread.join();
	writethread.join();

	return 0;
}
