#include <CDL/Util/DatagramSocket.h>

#if defined(Windows_NT)
	#include <windows.h>
	#include <winsock2.h>
	#define errnox WSAGetLastError()
	typedef int socklen_t;
	typedef SOCKET socket_t;
	static int g_ref=0;
#elif defined(Linux)
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
	DEFCLASS("DatagramSocket");

    DatagramSocket::DatagramSocket()
    {
#if defined(Windows_NT)
        if (!g_ref++)
        {
            WSADATA info;
            WSAStartup(MAKEWORD(2,0),&info);        // Unchecked exception
        }
#endif
        m_ref=new int(1);
        m_sock=new socket_t;
        *((socket_t*)m_sock)=::socket(AF_INET, SOCK_DGRAM,0);
		if (*((socket_t*)m_sock) == -1)
		{
			int error=errnox;
			Error_send("Unable to create UDP socket with error %d\n", error);
		}
    }

    DatagramSocket::DatagramSocket(const DatagramSocket &s)
    {
#if defined(Windows_NT)
        if (!g_ref++)
        {
            WSADATA info;
            WSAStartup(MAKEWORD(2,0),&info);        // Unchecked exception
        }
#endif
        m_ref=s.m_ref;
        ++(*m_ref);
        m_sock=s.m_sock;
    }

    DatagramSocket::~DatagramSocket()
    {
        if (!--(*m_ref))
        {
            close();
            delete m_ref;
            delete (socket_t*)m_sock;
        }
#if defined(Windows_NT)
        if (!--g_ref)
            WSACleanup();
#endif
    }

    const DatagramSocket &DatagramSocket::operator=(const DatagramSocket &s)
    {
        if (this != &s)
        {
            if (!--(*m_ref))
            {
                close();
                delete m_ref;
                delete (socket_t*)m_sock;
            }
            m_ref=s.m_ref;
            ++(*m_ref);
            m_sock=s.m_sock;
        }
        return *this;
    }

    int DatagramSocket::read(DatagramPacket &p)
    {
		int numbytes;
		sockaddr_in addr;
		socklen_t addr_len=sizeof(addr);

		if ((numbytes=recvfrom(*((socket_t*)m_sock), (char *)p.getBuffer().getData(), p.getBuffer().getLength(), 0,
						(sockaddr *)&addr, &addr_len)) == -1)
		{
			Error_send("Unable to receive packet from UDP socket\n");
		}

		p.setAddress(InetAddress(inet_ntoa(addr.sin_addr)));
		p.setLength(numbytes);

		return numbytes;
    }

    int DatagramSocket::write(const DatagramPacket &p)
    {
		int numbytes;
		sockaddr_in addr;
		socklen_t addr_len=sizeof(addr);

		memset(&addr, 0, addr_len);
		addr.sin_family=AF_INET;
		addr.sin_port=htons(p.getPort());
		addr.sin_addr=*((in_addr*)p.getAddress().getPtr());

		if ((numbytes=sendto(*((socket_t*)m_sock), (char *)p.getBuffer().getData(), p.getLength(), 0,
						(sockaddr *)&addr, addr_len)) == -1)
		{
			Error_send("Unable to send packet from UDP socket\n");
		}

		return numbytes;
    }

    void DatagramSocket::bind(const int &port)
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

    void DatagramSocket::close()
    {
#if defined(Windows_NT)
        closesocket(*((socket_t*)m_sock));
#else
        ::close(*((socket_t*)m_sock));
#endif
    }
}
