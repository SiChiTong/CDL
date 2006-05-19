#include <CDL/Util/Digest.h>

namespace CDL
{
	DEFCLASS("Digest");

	Digest::Digest(const unsigned char *data, const int &length)
	{
		if (data && length)
		{
            m_length=length;
            m_data=new unsigned char [m_length];
            memcpy(m_data,data,m_length);
			m_str=new char[m_length*2+1];
			for (int i=0, p=0; i<m_length; i++, p+=2)
				sprintf(&m_str[p], "%02x", (unsigned int)(((unsigned char *)m_data)[i]));
			m_str[m_length*2]='\0';
		}
		else
        {
			m_str='\0';
            m_data='\0';
            m_length=0;
        }
	}

	Digest::~Digest()
	{
		if (m_str)
	        delete []m_str;
        if (m_data)
            delete []m_data;
	}

	const unsigned char *Digest::getValue() const
	{
        return m_data;
	}

	const char *Digest::getString() const
	{
		return m_str;
	}

    const size_t &Digest::getLength() const
    {
         return m_length;
    }
}
