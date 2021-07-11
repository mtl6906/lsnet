#include "ls/net/Client.h"
#include "ls/net/Socket.h"
#include "ls/io/Factory.h"
#include "iostream"
#include "memory"

using namespace std;

using ls::net::Client;
using ls::net::Socket;
using ls::io::OutputStream;
using ls::io::Factory;

int main(int argc, char **argv)
{
	Factory factory;
	Client client("127.0.0.1", atoi(argv[1]));
	Socket sock(client.connect());
	unique_ptr<OutputStream> out(factory.makeOutputStream(sock.getWriter()));
	for(;;)
	{
		string text;
		cin >> text;
		out -> append(text);
		out -> write();
	}
	return 0;
}
