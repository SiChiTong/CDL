#ifndef __CDL_DIRECTORY_H__
#define __CDL_DIRECTORY_H__

#include <CDL/Util/File.h>

namespace CDL
{
    class DLL_API Directory
    {
        private:
            string m_name;
            void *m_directories;
            void *m_files;
            int  *m_ref;

        public:
            Directory(const string &n=string::nullstr);
            virtual ~Directory();
            Directory(const Directory &);
            Directory& operator=(const Directory &);
            void refresh();
            unsigned int getDirectoryCount() const;
            unsigned int getFileCount() const;
            const string &getDirectoryName(const unsigned int &) const;
            const string &getFileName(const unsigned int &) const;
            string getDirectoryPath(const unsigned int&) const;
            string getFilePath(const unsigned int&) const;
    };
}

#endif//__CDL_DIRECTORY_H__
