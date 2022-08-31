#include "ls/net/Reader.h"
#include "ls/Exception.h"
#include "sys/socket.h"
#include "ls/DefaultLogger.h"

namespace ls
{
	namespace net
	{
		Reader::Reader(int fd) : fd(fd)
		{

		}

		int Reader::read(void *data, int len)
		{
			int n = recv(fd, data, len, 0);
			if(n < 0)
				return Exception::LS_ERECV;
			if(n == 0)
				return Exception::LS_EEOF;
			return n;
		}

		int Reader::tryRead(void *data, int len)
		{
			LOGGER(ls::INFO) <<"fd: " <<fd <<", "
			       <<"data: " << (data == nullptr)  <<", "
			       <<"len: " << len << ls::endl;
			int n = recv(fd, data, len, MSG_DONTWAIT);
			if(n < 0 && (errno == EWOULDBLOCK || errno == EAGAIN))
				return Exception::LS_EWOULDBLOCK;
			if(n < 0)
				return Exception::LS_ERECV;
			if(n == 0)
				return Exception::LS_EEOF;
			return n;
		}
	}
}
