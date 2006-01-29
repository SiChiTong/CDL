#ifndef __CDL_FILE_H__
#define __CDL_FILE_H__

#include <CDL/Util/Stream.h>

namespace CDL
{
    class DLL_API File: public RandomAccessIOStream
    {
        private:
            FILE *m_fp;
            char *m_name;
            int  *m_ref;

        public:
            typedef enum {READ=1<<0, WRITE=1<<1, NOCLOSE=1<<2} File_perm;

            File(const char *f='\0');
            File(const char *, const int &);
            virtual ~File();
            File(FILE *, const int &);
            File(const File &);
            File& operator=(const File &);
            const char *getName() const;
            const char *getExtension() const;
            static bool exists(const char *);
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
