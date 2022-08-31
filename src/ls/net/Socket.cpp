#include "ls/net/Socket.h"
#include "ls/net/Writer.h"
#include "ls/net/Reader.h"
#include "unistd.h"

namespace ls
{
	namespace net
	{
		Socket::Socket(int fd) : fd(fd), writer(nullptr), reader(nullptr)
		{

		}

		io::Writer *Socket::getWriter()
		{
			if(nullptr == writer)
				writer.reset(new Writer(fd));
			return writer.get();
		}

		io::Reader *Socket::getReader()
		{
			if(nullptr == reader)
				reader.reset(new Reader(fd));
			return reader.get();
		}

		int Socket::getFd()
		{
			return fd;
		}

		Socket::~Socket()
		{
			if(fd > 0)
				close(fd);
		}

		void Socket::reset(int fd)
		{
			if(this -> fd > 0)
				close(this -> fd);
			this -> fd = fd;
			writer.reset(nullptr);
			reader.reset(nullptr);
		}
	}
}
