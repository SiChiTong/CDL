#ifndef __CDL_DIRECTORY_H__
#define __CDL_DIRECTORY_H__

#include <CDL/Util/File.h>

namespace CDL
{
    class DLL_API Directory
    {
        private:
            char *m_name;
            void *m_directories;
            void *m_files;
            int  *m_ref;

        public:
            Directory(const char *n='\0');
            virtual ~Directory();
            Directory(const Directory &);
            Directory& operator=(const Directory &);
            void refresh();
            unsigned int getDirectoryCount() const;
            unsigned int getFileCount() const;
            const char *getDirectoryName(const unsigned int &) const;
            const char *getFileName(const unsigned int &) const;
            Directory getDirectory(const unsigned int&) const;
            File getFile(const unsigned int&) const;
    };
}

#endif//__CDL_DIRECTORY_H__
