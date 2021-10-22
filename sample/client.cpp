#include "ls/net/Client.h"
#include "ls/net/Socket.h"
#include "ls/io/OutputStream.h"
#include "ls/Buffer.h"
#include "iostream"
#include "memory"

using namespace std;

using ls::net::Client;
using ls::net::Socket;
using ls::io::OutputStream;
using ls::Buffer;

int main(int argc, char **argv)
{
	Client client("127.0.0.1", atoi(argv[1]));
	Socket sock(client.connect());
	OutputStream out(sock.getWriter(), new Buffer());
	for(;;)
	{
		string text;
		cin >> text;
		out.append(text);
		out.write();
	}
	return 0;
}
