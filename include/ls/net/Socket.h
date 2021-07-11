#ifndef LS_NET_SOCKET_H
#define LS_NET_SOCKET_H

#include "ls/io/Writer.h"
#include "ls/io/Reader.h"
#include "memory"

namespace ls
{
	namespace net
	{
		class Socket
		{
			public:
				Socket(int fd);
				~Socket();
				io::Writer *getWriter();
				io::Reader *getReader();
			protected:
				int fd;
				std::unique_ptr<io::Writer> writer;
				std::unique_ptr<io::Reader> reader;
		};
	}
}

#endif
