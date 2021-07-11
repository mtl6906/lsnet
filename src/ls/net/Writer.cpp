#include "ls/net/Writer.h"
#include "ls/Exception.h"
#include "sys/socket.h"

namespace ls
{
	namespace net
	{
		Writer::Writer(int fd) : fd(fd)
		{

		}

		int Writer::write(void *data, int len)
		{
			int n = send(fd, data, len, 0);
			if(n < 0)
				throw Exception(Exception::LS_ESEND);
			return n;
		}

		int Writer::tryWrite(void *data, int len)
		{
			int n = send(fd, data, len, MSG_DONTWAIT);
			if(n < 0)
				throw Exception(Exception::LS_ESEND);
			return n;
		}
	}
}
