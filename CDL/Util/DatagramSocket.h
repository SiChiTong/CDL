#ifndef __CDL_DATAGRAMSOCKET_H__
#define __CDL_DATAGRAMSOCKET_H__

#include <CDL/Util/DatagramPacket.h>

namespace CDL
{
    class DLL_API DatagramSocket
    {
        protected:
            int*         m_ref;
            void        *m_sock;

        public:
            DatagramSocket();
            DatagramSocket(const DatagramSocket&);
            virtual ~DatagramSocket();
            const DatagramSocket &operator=(const DatagramSocket&);
            int  read(DatagramPacket &);
            int  write(const DatagramPacket &);
            void bind(const int &);
            void close();
    };
}

#endif//__CDL_DATAGRAMSOCKET_H__
