#include <CDL/Util/Digest.h>

namespace CDL
{
	DEFCLASS("Digest");

	Digest::Digest(const byte *data, const int &length)
	{
		if (data && length)
		{
            m_length=length;
            m_data=new byte [m_length];
            memcpy(m_data,data,m_length);
            char str_digest[m_length*2+1];
			for (int i=0, p=0; i<m_length; i++, p+=2)
				sprintf(&str_digest[p], "%02x", (unsigned int)(((unsigned char *)m_data)[i]));
            m_str=string(str_digest,m_length*2);
		}
		else
        {
            m_data='\0';
            m_length=0;
        }
	}

	Digest::~Digest()
	{
        if (m_data)
            delete []m_data;
	}

	const unsigned char *Digest::getValue() const
	{
        return m_data;
	}

	const string &Digest::getString() const
	{
		return m_str;
	}

    const size_t &Digest::getLength() const
    {
         return m_length;
    }
}
