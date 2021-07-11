#ifndef LS_NET_READER_H
#define LS_NET_READER_H

#include "ls/io/Reader.h"

namespace ls
{
	namespace net
	{
		class Reader : public io::Reader
		{
			public:
				Reader(int fd);
				int read(void *data, int len) override;
				int tryRead(void *data, int len) override;
			protected:
				int fd;
		};
	}
}

#endif
