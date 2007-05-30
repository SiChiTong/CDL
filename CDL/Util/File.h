#ifndef __CDL_FILE_H__
#define __CDL_FILE_H__

#include <CDL/Util/Stream.h>
#include <CDL/Util/NonCopyable.h>

namespace CDL
{
    class DLL_API File: public RandomAccessIOStream, public NonCopyable
    {
        private:
            FILE *m_fp;
            char *m_name;

        public:
            typedef enum {READ=1<<0, WRITE=1<<1, NOCLOSE=1<<2} File_perm;

            File(const char *f='\0', const int &mode=READ);
            virtual ~File();
            File(FILE *, const int &);
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
