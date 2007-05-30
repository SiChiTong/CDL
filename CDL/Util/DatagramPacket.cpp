#include <CDL/Util/DatagramPacket.h>

namespace CDL
{
	DEFCLASS("DatagramPacket");

	DatagramPacket::DatagramPacket(const Buffer &b, const InetAddress &i, const int &port): m_addr(i)
	{
		m_buf=b;
		m_port=port;
		m_length=0;
	}

	DatagramPacket::~DatagramPacket() {}

	const int &DatagramPacket::getLength() const
	{
		return m_length;
	}

	void DatagramPacket::setLength(const int &l)
	{
		m_length=l;
	}

	const Buffer &DatagramPacket::getBuffer() const
	{
		return m_buf;
	}

	void DatagramPacket::setBuffer(const Buffer &b)
	{
		m_buf=b;
	}

	const InetAddress &DatagramPacket::getAddress() const
	{
		return m_addr;
	}

	void DatagramPacket::setAddress(const InetAddress &i)
	{
		m_addr=i;
	}

	const int &DatagramPacket::getPort() const
	{
		return m_port;
	}

	void DatagramPacket::setPort(const int &p)
	{
		m_port=p;
	}
}
