#include <CDL/Util/ServerSocket.h>
#include <errno.h>

#if   defined(Windows_NT)
	#include <windows.h>
	#include <winsock2.h>
	typedef SOCKET socket_t;
	static int g_ref=0;
#else
	#include <sys/socket.h>             // Socket.*
	#include <unistd.h>                 // Socket.close
	#include <arpa/inet.h>              // InetAddress.*
	#include <netdb.h>                  // InetAddress.getHost*
	typedef int socket_t;
#endif

namespace CDL
{
	DEFCLASS("ServerSocket");

    ServerSocket::ServerSocket(const int &port)
    {
        bind(port);
        listen();
    }

    void ServerSocket::listen(const int &maxcon)
    {
        if (::listen(*((socket_t*)m_sock), maxcon))
		{
			int error=errno;
			Error_send("Unable to listen with a queue of %d with error %d\n", maxcon, error);
		}
    }

    Socket& ServerSocket::accept() const
    {
        socket_t sock=::accept(*((socket_t*)m_sock),NULL,NULL);
		if (sock == -1)
		{
			int error=errno;
			Error_send("Error accepting connection with error %d\n", error);
		}
        return *(new Socket(&sock));
    }
}
