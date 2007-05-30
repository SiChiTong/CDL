#ifndef __CDL_DATAGRAMSOCKET_H__
#define __CDL_DATAGRAMSOCKET_H__

#include <CDL/Util/DatagramPacket.h>
#include <CDL/Util/NonCopyable.h>

namespace CDL
{
    class DLL_API DatagramSocket: public NonCopyable
    {
        protected:
            void        *m_sock;

        public:
            DatagramSocket();
            virtual ~DatagramSocket();
            int  read(DatagramPacket &);
            int  write(const DatagramPacket &);
            void bind(const int &);
            void close();
    };
}

#endif//__CDL_DATAGRAMSOCKET_H__
