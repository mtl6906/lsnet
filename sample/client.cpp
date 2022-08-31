#include "ls/net/Client.h"
#include "ls/net/Socket.h"
#include "ls/io/OutputStream.h"
#include "ls/Buffer.h"
#include "iostream"
#include "memory"
#include "ls/Exception.h"
#include "ls/DefaultLogger.h"

using namespace std;
using namespace ls;

using ls::net::Client;
using ls::net::Socket;
using ls::io::OutputStream;
using ls::Buffer;

int main(int argc, char **argv)
{
	Client client("127.0.0.1", atoi(argv[1]));
	int connfd = client.connect();
	if(connfd < 0)
	{
		LOGGER(ls::INFO) << "connect error" << ls::endl;
		return 0;
	}
	Socket sock(connfd);
	Buffer buffer;
	OutputStream out(sock.getWriter(), &buffer);
	for(;;)
	{
		string text;
		cin >> text;
		if(out.append(text) < 0)	
		{
			LOGGER(ls::INFO) << "buffer full, reinput" << ls::endl;
			buffer.clear();
			continue;
		}
		int n = out.write();
		if(n < 0)
			throw n;
	}
	return 0;
}
