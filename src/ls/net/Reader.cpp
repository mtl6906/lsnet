#include "ls/net/Reader.h"
#include "ls/Exception.h"
#include "sys/socket.h"

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
				throw Exception(Exception::LS_ERECV);
			if(n == 0)
				throw Exception(Exception::LS_EEOF);
			return n;
		}

		int Reader::tryRead(void *data, int len)
		{
			int n = recv(fd, data, len, MSG_DONTWAIT);
			if(n < 0)
				throw Exception(Exception::LS_ERECV);
			if(n == 0)
				throw Exception(Exception::LS_EEOF);
			return n;
		}
	}
}
