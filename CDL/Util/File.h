#ifndef __CDL_FILE_H__
#define __CDL_FILE_H__

#include <CDL/Util/Stream.h>
#include <CDL/Util/NonCopyable.h>
#include <CDL/Util/string.h>

namespace CDL
{
    class DLL_API File: public RandomAccessIOStream, public NonCopyable
    {
        private:
            FILE *m_fp;
            string m_name;

        public:
            typedef enum {READ=1<<0, WRITE=1<<1, NOCLOSE=1<<2} File_perm;

            File(const string &n=string::nullstr, const int &mode=READ);
            virtual ~File();
            File(FILE *, const int &);
            const string &getName() const;
            string getExtension() const;
            static bool exists(const string &);
            int  read(void *, const int &);
            int  write(const void *, const int &);
            int  seek(const long&, const int &m=SEEK_SET);
            long tell();
            void putback(const char &);
            void flush();
            void close();
    };
}

#endif//__CDL_FILE_H__
