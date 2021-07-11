#ifndef LS_NET_SERVER_H
#define LS_NET_SERVER_H

#include "ls/net/Socket.h"

namespace ls
{
	namespace net
	{
		class Server
		{
			public:
				Server(int port);
				int accept();
				int getFd();
			protected:
				int listenfd;
		};
	}
}

#endif
