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

    int RandomAccessStream::size()
    {
         size_t pos_old=tell(), size;
         seek(0,SEEK_END);
         size=tell();
         seek(pos_old,SEEK_SET);

         return size;
    }

    bool RandomAccessStream::isEOF()
    {
         size_t pos_old=tell(), pos_new;
         seek(0,SEEK_END);
         pos_new=tell();
         seek(pos_old,SEEK_SET);

         if (pos_old == pos_new) return true;
         return false;
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

    string InputStream::readString(const char &del)
    {
        static char str[4096];
        str[0]='\0';
        int index=-1, rd;

        do
        {
            index++;
            rd=read(&str[index], sizeof(char));
        } while(str[index] != del && str[index] != '\0' && rd == 1 && index < 4096);

        if (str[index] != '\0')
            str[index]='\0';
        if (str[index-2] == '\r')
        {
            str[index-2]='\0';
            str[index-1]='\0';
        }

        return string(str);
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

    void OutputStream::writeCString(const string &str)
    {
        for (int i=0; i<str.length()+1; i++)
            write(&str.c_str()[i], sizeof(char));
    }

    void OutputStream::writeString(const string &str)
    {
        for (int i=0; i<str.length(); i++)
            write(&str.c_str()[i], sizeof(char));
    }
}
