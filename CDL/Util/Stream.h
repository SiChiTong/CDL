#ifndef __CDL_STREAM_H__
#define __CDL_STREAM_H__

#include <CDL/defs.h>

namespace CDL
{
    class DLL_API Stream
    {
        protected:
            int  m_mode;

        public:
            Stream();
            virtual ~Stream();
            bool isValid() const;
            virtual void close() {};
    };

    class DLL_API InputStream: public virtual Stream
    {
        public:
            virtual int read(void *, const int &s)=0;

            void readChar(char &);
            void readShort(short &);
            void readInt(int &);
            void readLong(long &);
            void readSize(size_t &);
            void readFloat(float &);
            void readDouble(double &);
            void readString(char *);
            void readLine(char *);
            void readToken(char *, const char &d=',');
    };

    class DLL_API OutputStream: public virtual Stream
    {
        public:
            virtual int write(const void *, const int &s)=0;

            void writeChar(const char &);
            void writeShort(const short &);
            void writeInt(const int &);
            void writeLong(const long &);
            void writeSize(const size_t &);
            void writeFloat(const float &);
            void writeDouble(const double &);
            void writeString(const char *);
            void writeCString(const char *);
    };

    class DLL_API IOStream: public InputStream, public OutputStream {};
}

#endif//__CDL_STREAM_H__
