#ifndef __CDL_SERVERSOCKET_H__
#define __CDL_SERVERSOCKET_H__

#include <CDL/Util/Socket.h>

namespace CDL
{
    class DLL_API ServerSocket: public Socket
    {
        public:
            ServerSocket(const int &);
            Socket& accept() const;
            void listen(const int &c=5);
    };
}

#endif//__CDL_SERVERSOCKET_H__
