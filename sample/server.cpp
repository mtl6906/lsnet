#include "ls/epoll/Tool.h"
#include "ls/net/Server.h"
#include "ls/net/Reader.h"
#include "ls/Exception.h"
#include "ls/io/Factory.h"
#include "ls/DefaultLogger.h"
#include "ls/Pool.h"
#include "iostream"
#include "map"
#include "memory"

using namespace std;
using namespace ls;

io::Factory factory;

class Connection
{
	public:
		Connection(int buffersize = 65536) : buffersize(buffersize), sock(nullptr), inputStream(nullptr), outputStream(nullptr)
		{

		}

		void reset(net::Socket *sock)
		{
			inputStream.reset(nullptr);
			outputStream.reset(nullptr);
			this -> sock.reset(sock);
		}

		io::InputStream *getInputStream()
		{
			if(inputStream == nullptr)
				inputStream.reset(
					factory.makeInputStream(sock -> getReader(), new Buffer(buffersize))
				);
			return inputStream.get();
		}

		io::OutputStream *getOutputStream()
		{
			if(outputStream)
				outputStream.reset(
					factory.makeOutputStream(sock -> getWriter(), new Buffer(buffersize))
				);
			return outputStream.get();
		}
	private:
		int buffersize;
		unique_ptr<net::Socket> sock;
		unique_ptr<io::InputStream> inputStream;
		unique_ptr<io::OutputStream> outputStream;
};

int main(int argc, char **argv)
{

	Pool<Connection> pool;
	for(int i=0;i<128;++i)
		pool.put(new Connection());
	epoll::Tool tool(128);
	net::Server server(stoi(argv[1]));

	map<int, Connection *> connectionMapper;
	tool.add(server.getFd(), EPOLLIN);
	for(;;)
	{
		int ret = tool.wait(-1);
		cout << ret << " event happen..." <<endl;
		for(int i=0;i<ret;++i)
		{
			cout << "event " << i;
			int fd = tool.event(i).data.fd;
			cout << " at fd " << fd << endl;
			if(server.getFd() == fd)
			{
				int connfd = server.accept();
				if(connfd < 0)
				{
					LOGGER(ls::INFO) << "accept error" << ls::endl;
					return 0;
				}
				cout << "accept fd " << connfd << endl;
				auto connection = pool.get();
				connection -> reset(new net::Socket(connfd));
				connectionMapper.emplace(connfd, connection);
				tool.add(connfd, EPOLLIN | EPOLLET);
			}
			else if(tool.event(i).events & EPOLLIN)
			{
				auto connection = connectionMapper[fd];
				auto inputStream = connection -> getInputStream();
				int result = inputStream -> tryRead();
				if(result < 0 && errno != EAGAIN && errno != EWOULDBLOCK)
				{
					cout << "release: " << fd << endl;
					connection -> reset(nullptr);
					pool.put(connection);
					connectionMapper.erase(fd);
					continue;
				}
				int ec;
				string text = inputStream -> split(ec, "end");
				if(ec == Exception::LS_EFORMAT && inputStream -> full())
				{
					LOGGER(ls::INFO) << "end" << ls::endl;
					return 0;
				}
				cout << text << endl;
			}
		}
	}
	return 0;
}
