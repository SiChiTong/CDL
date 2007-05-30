#include <CDL/Util/Buffer.h>
#include <CDL/Math/Random.h>
#include <CDL/Util/md5.h>
#include <CDL/Util/sha1.h>
#include <CDL/Util/crc64.h>
#include <CDL/Util/sha512.h>

namespace CDL
{
    DEFCLASS("Buffer");

    Buffer::Buffer(const int &length, byte *data)
    {
        m_length=length;
        m_pos=0;
        m_clean=false;
        if (m_length)
        {
            if (data)
                 m_data=data;
            else
            {
                m_data=new byte[m_length];
                memset(m_data,0, m_length);
                m_clean=true;
            }
        }
        else
            m_data='\0';
    }

    Buffer::Buffer(const string &str)
    {
         m_length=str.length();
         m_pos=0;
         m_clean=true;
         if (m_length)
         {
             m_data=new char[m_length];
             memcpy(m_data,str.c_str(),m_length);
         }
         else
             m_data='\0';
    }

    Buffer::Buffer(const Buffer &b)
    {
        m_pos=b.m_pos;
        m_length=b.m_length;
        m_clean=b.m_clean;
        if (m_clean)
        {
            m_data=new byte[m_length];
            memcpy(m_data,b.m_data,m_length);
        }
        else
            m_data=b.m_data;
    }

    Buffer::~Buffer()
    {
        if (m_data && m_length && m_clean)
            delete [](byte *)m_data;
    }

    const Buffer &Buffer::operator=(const Buffer &b)
    {
        if (&b != this)
        {
            if (m_data && m_length && m_clean)
                delete [](byte *)m_data;
            m_length=b.m_length;
            m_pos=b.m_pos;
            m_pos=b.m_pos;
            m_length=b.m_length;
            m_clean=b.m_clean;
            if (m_clean)
            {
                m_data=new byte[m_length];
                memcpy(m_data,b.m_data,m_length);
            }
            else
                m_data=b.m_data;
        }
        return *this;
    }

    int Buffer::read(void *data, const int &size)
    {
        if (m_pos+size <= m_length)
        {
            memcpy(data, &((byte *)m_data)[m_pos], size);
            m_pos+=size;
            return size;
        }
        else
        {
            int sz=m_length-m_pos;
            if (sz >0)
            {
                memcpy(data, &((byte *)m_data)[m_pos], sz);
                m_pos+=sz;
                return sz;
            }
            else
            {
                Error_send("Pointer is already at end of stream\n");
                return 0;
            }
        }
    }

    int Buffer::write(const void *data, const int &size)
    {
        if (m_pos+size <= m_length)
        {
            memcpy(&((byte *)m_data)[m_pos], data, size);
            m_pos+=size;
            return size;
        }
        else
        {
            int sz=m_length-m_pos;
            if (sz >0)
            {
                memcpy(&((byte *)m_data)[m_pos], data, sz);
                m_pos+=sz;
                return sz;
            }
            else
            {
                Error_send("Pointer is already at end of stream\n");
                return 0;
            }
        }
    }

    int Buffer::seek(const long &pos, const int &m)
    {
        switch(m)
        {
            case SEEK_SET:
                m_pos=pos;
                break;
            case SEEK_CUR:
                m_pos+=pos;
                break;
            case SEEK_END:
                m_pos=m_length+pos;
                break;
            default:
                Error_send("Invalid seek mode %d\n", m);
                return -1;
        }

        if (m_pos > m_length || m_pos < 0)
        {
            Error_send("Seek went past valid position to %d\n", m_pos);
            return -1;
        }
        return 0;
    }

    long Buffer::tell()
    {
        return m_pos;
    }

    bool Buffer::operator==(const Buffer &b) const
    {
        return (m_length == b.m_length && m_pos == b.m_pos &&!memcmp(m_data,b.m_data,m_length));
    }

    bool Buffer::operator!=(const Buffer &b) const
    {
        return (m_length != b.m_length || m_pos != b.m_pos || memcmp(m_data,b.m_data,m_length));
    }

    void *Buffer::getData() const
    {
        return m_data;
    }

    const int &Buffer::getLength() const
    {
        return m_length;
    }

    void Buffer::setLength(const int &length)
    {
        int min=MIN(length,m_length);
        byte *tmp;
        if (length) tmp=new byte[length];
        else tmp='\0';
        memcpy(tmp,m_data,min);
        if (m_data && m_length)
            delete [](byte *)m_data;
        m_data=tmp;
        m_length=length;
    }

    void Buffer::copy(const Buffer &b, const int &offset)
    {
        if (offset > m_length)
        {
            Error_send("Overflow when copying at offset %d when buffer size is %d\n", offset, m_length);
            return;
        }
        if (offset < 0)
        {
            Error_send("Invalid offset of %d\n", offset);
            return;
        }
        int count=m_length-offset;
        if (b.m_length < count) count=b.m_length;

        memcpy(&((byte *)m_data)[offset], b.m_data, count);
    }

    void Buffer::clear()
    {
        memset(m_data,0,m_length);
        m_pos=0;
    }

    void Buffer::RC4(const string &key)
    {
        size_t i, j;
        byte S[256], T;

        for (i=0; i<256; i++)
            S[i]=i;
        for (i=0, j=0; i<256; i++)
        {
            j=(j+S[i]+key[i%key.length()])&0xFF;
            T=S[i];
            S[i]=S[j];
            S[j]=T;
        }

        i=0;
        j=0;
/*        for (size_t k=0; k<1024; k++) // Skip first 1024 bytes
        {
            i=(i+1)&0xFF;
            j=(j+S[i])&0xFF;
            T=S[i];
            S[i]=S[j];
            S[j]=T;
        }*/

        unsigned char *data=(unsigned char *)m_data;
        for (size_t total=m_length; total; total--)
        {
            i=(i+1)&0xFF;
            j=(j+S[i])&0xFF;
            T=S[i];
            S[i]=S[j];
            S[j]=T;
            *(data++)^=S[(S[i]+S[j])&0xFF];
        }
    }

    Digest Buffer::getMD5() const
    {
        unsigned char digest[16]={0};
        MD5_CTX context;

        MD5Init(&context);
        MD5Update(&context, (unsigned char *)m_data, m_length);
        MD5Final(digest,&context);

        return Digest(digest,16);
    }

    Digest Buffer::getSHA1() const
    {
        unsigned char digest[20]={0};
        SHA1Context context;

        SHA1Reset(&context);
        SHA1Input(&context, (unsigned char *)m_data, m_length);
        SHA1Result(&context, digest);

        return Digest(digest,20);
    }

    Digest Buffer::getSHA512() const
    {
        unsigned char digest[64]={0};
        sha512_ctx context;

        sha512_init(&context);
        sha512_update(&context, (unsigned char *)m_data, m_length);
        sha512_final(&context, digest);

        return Digest(digest,64);
    }

    Digest Buffer::getCRC64() const
    {
        unsigned char digest[8]={0};
        CRC64Context context;

        CRC64Reset(&context);
        CRC64Input(&context, (unsigned char *)m_data, m_length);
        CRC64Result(&context, digest);

        return Digest(digest,8);
    }
}
