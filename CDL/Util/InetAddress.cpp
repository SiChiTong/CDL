#include <CDL/Util/InetAddress.h>
#include <errno.h>

#if   defined(Windows_NT)
	#include <windows.h>
	#include <winsock2.h>
	static int g_ref=0;
#else
	#include <unistd.h>             // Socket.*
	#include <arpa/inet.h>              // InetAddress.*
	#include <netdb.h>                  // InetAddress.getHost*
#endif

namespace CDL
{
    InetAddress::InetAddress(const char *name)
    {
#if defined(Windows_NT)
        if (!g_ref++)
        {
            WSADATA info;
            WSAStartup(MAKEWORD(2,0),&info);
        }
#endif
        m_addr=new in_addr;
        hostent *he=gethostbyname(name);
        if (he)
        {
            *((in_addr*)m_addr)=*((in_addr *)he->h_addr);
			strcpy(m_hostname, he->h_name);
        }
        else
			strcpy(m_hostname, "");
    }

    InetAddress::~InetAddress()
    {
#if defined(Windows_NT)
        if (!--g_ref)
            WSACleanup();
#endif
        delete (in_addr*)m_addr;
    }

    const char *InetAddress::getName() const
    {
        return m_hostname;
    }

    const char *InetAddress::getAddress() const
    {
        return inet_ntoa(*((in_addr*)m_addr));
    }

	int InetAddress::getIntAddress() const
	{
		return *((int *)m_addr);
	}

    InetAddress InetAddress::getLocalHost()
    {
        char local[256]="localhost";
        gethostname(local, 255);
        return InetAddress(local);
    }

    void *InetAddress::getPtr() const
    {
        return m_addr;
    }
}
