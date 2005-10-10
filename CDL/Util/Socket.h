#ifndef __CDL_SOCKET_H__
#define __CDL_SOCKET_H__

#include <CDL/Util/Stream.h>
#include <CDL/Util/InetAddress.h>

namespace CDL
{
	class ServerSocket;

    class DLL_API Socket: public IOStream
    {
        protected:
            int*         m_ref;
            void        *m_sock;
            Socket(const void *);
            friend class ServerSocket;

        public:
            Socket();
            virtual ~Socket();
            Socket(const Socket&);
            int  read(void *, const int &);
            int  write(const void *, const int &);
            const Socket &operator=(const Socket&);
            void connect(const InetAddress &, const int &);
            void bind(const int &);
			InetAddress getInetAddress() const;
            void close();
    };
}

#include <CDL/Util/ServerSocket.h>

#endif//__CDL_SOCKET_H__
