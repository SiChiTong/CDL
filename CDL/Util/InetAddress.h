#ifndef __CDL_INETADDRESS_H__
#define __CDL_INETADDRESS_H__

#include <CDL/defs.h>
#include <CDL/Util/NonCopyable.h>

namespace CDL
{
    // BUG: introduced with noncopyable
    class DLL_API InetAddress
    {
        private:
            void *m_addr;
            char  m_hostname[128];

        public:
            InetAddress(const char *);
            virtual ~InetAddress();
            const char *getName() const;
            const char *getAddress() const;
			int getIntAddress() const;
            static InetAddress getLocalHost();
            void *getPtr() const;
    };
}

#endif//__CDL_INETADDRESS_H__
