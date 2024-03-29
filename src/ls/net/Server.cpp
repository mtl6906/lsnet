#include "ls/net/Server.h"
#include "ls/Exception.h"
#include "sys/socket.h"
#include "arpa/inet.h"


namespace ls
{
	namespace net
	{
		int createFd(int port)
		{
			sockaddr_in addr = {};
			addr.sin_family = AF_INET;
			addr.sin_addr.s_addr = htonl(INADDR_ANY);
			addr.sin_port = htons(port);
			int fd = socket(AF_INET, SOCK_STREAM, 0);
			if(fd < 0)
				return Exception::LS_ESOCKET;
			int enable = 1;
			if(setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &enable, sizeof(int)) < 0)
				return Exception::LS_EREUSEPORT;
			if(bind(fd, (sockaddr *)&addr, sizeof(addr)) < 0)
				return Exception::LS_EBIND;
			if(listen(fd, 128) < 0)
				return Exception::LS_ELISTEN;
			return fd;
		}

		Server::Server(int port) : listenfd(createFd(port))
		{

		}

		int Server::accept()
		{
			sockaddr_in cliaddr = {};
			socklen_t len = sizeof(cliaddr);
			int fd = ::accept(listenfd, (sockaddr *)&cliaddr, &len);
			if(fd < 0 && (errno == EAGAIN || errno == EWOULDBLOCK))
				return Exception::LS_EWOULDBLOCK;
			if(fd < 0)
				return Exception::LS_EACCEPT;
			return fd;
		}

		int Server::getFd()
		{
			return listenfd;
		}
	}
}
