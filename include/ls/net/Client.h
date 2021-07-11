#ifndef LS_NET_CLIENT_H
#define LS_NET_CLIENT_H

#include "string"

namespace ls
{
	namespace net
	{
		class Client
		{
			public:
				Client(const std::string &ip, int port);
				int connect();
			protected:
				std::string ip;
				int port;
		};
	}
}

#endif
