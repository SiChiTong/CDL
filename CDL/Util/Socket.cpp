#include <CDL/Util/Socket.h>

#if   defined(Windows_NT)
	#include <windows.h>
	#include <winsock2.h>
	#define errnox WSAGetLastError()
	typedef int socklen_t;
	typedef SOCKET socket_t;
	static int g_ref=0;
#else
	#include <errno.h>
	#include <sys/socket.h>             // Socket.*
	#include <unistd.h>                 // Socket.close
	#include <arpa/inet.h>              // InetAddress.*
	#include <netdb.h>                  // InetAddress.getHost*
	typedef int socket_t;
    #define errnox errno
#endif

namespace CDL
{
	DEFCLASS("Socket");

    Socket::Socket()
    {
#if defined(Windows_NT)
        if (!g_ref++)
        {
            WSADATA info;
            WSAStartup(MAKEWORD(2,0),&info);        // Unchecked exception
        }
#endif
        m_sock=new socket_t;
        *((socket_t*)m_sock)=::socket(AF_INET, SOCK_STREAM,0);	// Unchecked exception
		if (*((socket_t*)m_sock) == -1)
		{
			int error=errnox;
			Error_send("Unable to create TCP socket with error %d\n", error);
		}
    }

    Socket::~Socket()
    {
        close();
        delete (socket_t*)m_sock;
#if defined(Windows_NT)
        if (!--g_ref)
            WSACleanup();
#endif
    }

    Socket::Socket(const void *s)
    {
#if defined(Windows_NT)
        if (!g_ref++)
        {
            WSADATA info;
            WSAStartup(MAKEWORD(2,0),&info);        // Unchecked exception
        }
#endif
        m_sock=new socket_t;
        *((socket_t*)m_sock)=*((socket_t*)s);
    }

	InetAddress Socket::getInetAddress() const
	{
		sockaddr_in addr;
		socklen_t addrlen=sizeof(addr);

		memset(&addr, 0, sizeof(addr));

		if (getpeername(*((socket_t*)m_sock), (sockaddr *)&addr, &addrlen))
		{
			int error=errnox;
			Error_send("Unable to get address with error %d\n", error);
		}

		return InetAddress(inet_ntoa(addr.sin_addr));
	}

    int Socket::read(void *data, const int &size)
    {
        return recv(*((socket_t*)m_sock), (char *)data, size, 0);
    }

    int Socket::write(const void *data, const int &size)
    {
        return send(*((socket_t*)m_sock), (char *)data, size, 0);
    }

    void Socket::bind(const int &port)
    {
        sockaddr_in addr;

        memset(&addr, 0, sizeof(addr));
        addr.sin_family=AF_INET;
        addr.sin_port=htons(port);

        if (::bind(*((socket_t*)m_sock), (sockaddr *)&addr, sizeof(addr)))
		{
			int error=errnox;
			Error_send("Unable to bind to port %d with error %d\n", port, error);
		}
    }

    void Socket::connect(const InetAddress &host, const int &port)
    {
        sockaddr_in addr;

        memset(&addr, 0, sizeof(addr));
        addr.sin_family=AF_INET;
        addr.sin_port=htons(port);
        addr.sin_addr=*((in_addr*)host.getPtr());

        if (::connect(*((socket_t*)m_sock), (sockaddr *)&addr, sizeof(addr)))
		{
			int error=errnox;
			Error_send("Unable to connect to %s:%d with error %d\n", host.getName(), port, error);
		}
    }

    void Socket::close()
    {
#if defined(Windows_NT)
        closesocket(*((socket_t*)m_sock));
#else
        ::close(*((socket_t*)m_sock));
#endif
    }
}
