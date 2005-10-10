#include <CDL/Util/Stream.h>

namespace CDL
{
    Stream::Stream()
    {
        m_mode=0;
    }

    Stream::~Stream()
    {
        m_mode=0;
    }

    bool Stream::isValid() const
    {
        return m_mode != 0;
    }

    void InputStream::readChar(char &aChar)
    {
        read(&aChar, sizeof(char));
    }

    void InputStream::readShort(short &aShort)
    {
        read(&aShort, sizeof(short));
        LE16_TO_CPU(aShort);
    }

    void InputStream::readInt(int &aInt)
    {
        read(&aInt, sizeof(int));
        LE32_TO_CPU(aInt);
    }

    void InputStream::readLong(long &aLong)
    {
        read(&aLong, sizeof(long));
        LE32_TO_CPU(aLong);
    }

    void InputStream::readSize(size_t &aSize)
    {
         read(&aSize, sizeof(size_t));
         LE32_TO_CPU(aSize);
    }

    void InputStream::readFloat(float &aFloat)
    {
        read(&aFloat, sizeof(float));
        LE32_TO_CPU(aFloat);
    }

    void InputStream::readDouble(double &aDouble)
    {
        read(&aDouble, sizeof(double));
        LE64_TO_CPU(aDouble);
    }

    void InputStream::readString(char *str)
    {
        str[0]='\0';
        int index=0, rd;

        do
        {
            rd=read(&str[index], sizeof(char));
        }
        while (str[index++] != '\0' && rd == 1);
    }

    void InputStream::readLine(char *str)
    {
         str[0]='\0';
         int index=0, rd;

         do
         {
             rd=read(&str[index], sizeof(char));
         } while(str[index++] != '\n' && rd == 1);

         str[index]='\0';
         if (str[index-2] == '\r')
         {
             str[index-2]='\0';
             str[index-1]='\0';
         }
    }

    void InputStream::readToken(char *str, const char &del)
    {
         str[0]='\0';
         int index=-1, rd;

         do
         {
             index++;
             rd=read(&str[index], sizeof(char));
         } while(str[index] != del && str[index] != '\0' && rd == 1);

         if (str[index] != '\0')
             str[index]='\0';
    }

    void OutputStream::writeChar(const char &aChar)
    {
        write(&aChar, sizeof(char));
    }

    void OutputStream::writeShort(const short &aShort)
    {
        short x=aShort;
        LE16_TO_CPU(x);
        write(&x, sizeof(short));
    }

    void OutputStream::writeInt(const int &aInt)
    {
        int x=aInt;
        LE32_TO_CPU(x);
        write(&x, sizeof(int));
    }

    void OutputStream::writeLong(const long &aLong)
    {
        long x=aLong;
        LE32_TO_CPU(x);
        write(&x, sizeof(long));
    }

    void OutputStream::writeSize(const size_t &aSize)
    {
        size_t x=aSize;
        LE32_TO_CPU(x);
        write(&x, sizeof(size_t));
    }

    void OutputStream::writeFloat(const float &aFloat)
    {
        float x=aFloat;
        LE32_TO_CPU(x);
        write(&x, sizeof(float));
    }

    void OutputStream::writeDouble(const double &aDouble)
    {
        double x=aDouble;
        LE64_TO_CPU(x);
        write(&x, sizeof(double));
    }

    void OutputStream::writeCString(const char *str)
    {
        int index=0;

        do
        {
            write(&str[index], sizeof(char));
        }
        while (str[index++] != '\0');
    }

    void OutputStream::writeString(const char *str)
    {
        int index=0;

        while (str[index] != '\0')
        {
            write(&str[index], sizeof(char));
            index++;
        }
    }
}
