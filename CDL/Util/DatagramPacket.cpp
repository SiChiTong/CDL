#include <CDL/Util/DatagramPacket.h>

namespace CDL
{
	DEFCLASS("DatagramPacket");

	DatagramPacket::DatagramPacket(const Buffer &b, const InetAddress &i, const int &port): m_addr(i)
	{
		m_ref=new int(1);
		m_buf=b;
		m_port=port;
		m_length=0;
	}

	DatagramPacket::DatagramPacket(const DatagramPacket &p): m_addr(p.m_addr)
	{
		m_ref=p.m_ref;
		++(*m_ref);
		m_length=p.m_length;
		m_port=p.m_port;
		m_buf=p.m_buf;
	}

	DatagramPacket::~DatagramPacket()
	{
		if (!--(*m_ref))
			delete m_ref;
	}

	const DatagramPacket &DatagramPacket::operator=(const DatagramPacket &p)
	{
		if (this != &p)
		{
			if (!--(*m_ref))
				delete m_ref;
			m_ref=p.m_ref;
			++(*m_ref);
			m_length=p.m_length;
			m_port=p.m_port;
			m_buf=p.m_buf;
			m_addr=p.m_addr;
		}
	}

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
