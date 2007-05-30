#ifndef __CDL_SOCKET_H__
#define __CDL_SOCKET_H__

#include <CDL/Util/Stream.h>
#include <CDL/Util/InetAddress.h>
#include <CDL/Util/NonCopyable.h>

namespace CDL
{
	class ServerSocket;

    class DLL_API Socket: public IOStream, public NonCopyable
    {
        protected:
            void        *m_sock;
            Socket(const void *);
            friend class ServerSocket;

        public:
            Socket();
            virtual ~Socket();
            int  read(void *, const int &);
            int  write(const void *, const int &);
            void connect(const InetAddress &, const int &);
            void bind(const int &);
			InetAddress getInetAddress() const;
            void close();
    };
}

#include <CDL/Util/ServerSocket.h>

#endif//__CDL_SOCKET_H__
