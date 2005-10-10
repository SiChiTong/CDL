#ifndef __CDL_INETADDRESS_H__
#define __CDL_INETADDRESS_H__

#include <CDL/defs.h>

namespace CDL
{
    class DLL_API InetAddress
    {
        private:
            int*  m_ref;
            void *m_addr;
            char  m_hostname[128];

        public:
            InetAddress(const char *);
            virtual ~InetAddress();
            InetAddress(const InetAddress&);
            const char *getName() const;
            const char *getAddress() const;
			int getIntAddress() const;
            static InetAddress getLocalHost();
            const InetAddress &operator=(const InetAddress&);
            void *getPtr() const;
    };
}

#endif//__CDL_INETADDRESS_H__
