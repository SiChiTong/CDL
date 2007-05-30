#ifndef __CDL_DATAGRAMPACKET_H__
#define __CDL_DATAGRAMPACKET_H__

#include <CDL/Util/Buffer.h>
#include <CDL/Util/InetAddress.h>
#include <CDL/Util/NonCopyable.h>

namespace CDL
{
	class DLL_API DatagramPacket: public NonCopyable
	{
		private:
			int         m_length;
			int         m_port;
			Buffer      m_buf;
			InetAddress m_addr;

		public:
			DatagramPacket(const Buffer &b=Buffer(), const InetAddress &i=InetAddress::getLocalHost(), const int &p=0);
			virtual ~DatagramPacket();
			const int &getLength() const;
			void setLength(const int &);
			const Buffer &getBuffer() const;
			void setBuffer(const Buffer &);
			const InetAddress &getAddress() const;
			void setAddress(const InetAddress &);
			const int &getPort() const;
			void setPort(const int &);
	};
}

#endif//__CDL_DATAGRAMPACKET_H__
