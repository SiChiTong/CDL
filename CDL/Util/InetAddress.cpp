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
    InetAddress::InetAddress(const string &name)
    {
#if defined(Windows_NT)
        if (!g_ref++)
        {
            WSADATA info;
            WSAStartup(MAKEWORD(2,0),&info);
        }
#endif
        m_addr=new in_addr;
        hostent *he=gethostbyname(name.c_str());
        if (he)
        {
            *((in_addr*)m_addr)=*((in_addr *)he->h_addr);
            m_hostname=he->h_name;
        }
    }

    InetAddress::~InetAddress()
    {
#if defined(Windows_NT)
        if (!--g_ref)
            WSACleanup();
#endif
        delete (in_addr*)m_addr;
    }

    const string &InetAddress::getName() const
    {
        return m_hostname;
    }

    string InetAddress::getAddress() const
    {
        return string(inet_ntoa(*((in_addr*)m_addr)));
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
