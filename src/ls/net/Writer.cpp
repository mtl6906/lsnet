#include "ls/net/Writer.h"
#include "ls/Exception.h"
#include "sys/socket.h"
#include "ls/DefaultLogger.h"

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
				return Exception::LS_ESEND;
			return n;
		}

		int Writer::tryWrite(void *data, int len)
		{
			int n = send(fd, data, len, MSG_DONTWAIT);
			if(n < 0 && (errno == EAGAIN || errno == EWOULDBLOCK))
				return Exception::LS_EWOULDBLOCK;
			if(n < 0)
				return Exception::LS_ESEND;
			return n;
		}
	}
}
