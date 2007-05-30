#ifndef __CDL_INETADDRESS_H__
#define __CDL_INETADDRESS_H__

#include <CDL/defs.h>
#include <CDL/Util/NonCopyable.h>
#include <CDL/Util/string.h>

namespace CDL
{
    // BUG: introduced with noncopyable
    class DLL_API InetAddress
    {
        private:
            void *m_addr;
            string m_hostname;

        public:
            InetAddress(const string &);
            virtual ~InetAddress();
            const string &getName() const;
            string getAddress() const;
			int getIntAddress() const;
            static InetAddress getLocalHost();
            void *getPtr() const;
    };
}

#endif//__CDL_INETADDRESS_H__
