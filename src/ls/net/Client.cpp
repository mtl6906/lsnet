#include "ls/net/Client.h"
#include "ls/Exception.h"
#include "sys/socket.h"
#include "arpa/inet.h"

using namespace std;

namespace ls
{
	namespace net
	{
		Client::Client(const string &ip, int port) : ip(ip), port(port)
		{

		}

		int Client::connect()
		{
			sockaddr_in addr = {};
			addr.sin_family = AF_INET;
			inet_pton(AF_INET, ip.c_str(), &addr.sin_addr);
			addr.sin_port = htons(port);
			int fd = socket(AF_INET, SOCK_STREAM, 0);
			if(::connect(fd, (sockaddr *)&addr, sizeof(addr)) < 0)
				throw Exception(Exception::LS_ECONN);
			return fd;
		}
	}
}
