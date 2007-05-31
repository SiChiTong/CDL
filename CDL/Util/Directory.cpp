#include <CDL/Util/Directory.h>

#ifdef Windows_NT
#include <windows.h>
#endif
#include <dirent.h>
#include <vector>

namespace CDL
{
    DEFCLASS("Directory");

    typedef std::vector<string> strset;

    Directory::Directory(const string &name)
    {
        m_ref=new int(1);
        m_directories=new strset;
        m_files=new strset;
        if (name.length() > 0)
        {
            char lastc=name[name.length()-1];
            if (lastc == '/' || lastc == '\\')
                m_name=name.substr(0,name.length()-1);
            else
                m_name=name;
        }
        refresh();
    }

    Directory::~Directory()
    {
        if (!--(*m_ref))
        {
            delete m_ref;
            refresh();
            delete ((strset *)m_directories);
            delete ((strset *)m_files);
        }
    }

    Directory::Directory(const Directory &d)
    {
        m_ref=d.m_ref;
        ++(*m_ref);
        m_name=d.m_name;
        m_directories=d.m_directories;
        m_files=d.m_files;
    }

    Directory& Directory::operator=(const Directory &d)
    {
        if (this != &d)
        {
            if (!--(*m_ref))
            {
                delete m_ref;
                refresh();
                delete ((strset *)m_directories);
                delete ((strset *)m_files);
            }
            m_ref=d.m_ref;
            ++(*m_ref);
            m_name=d.m_name;
            m_directories=d.m_directories;
            m_files=d.m_files;
        }
    }

    void Directory::refresh()
    {
#if defined(Linux)
        DIR *dir;
        struct dirent *entry;
#elif defined(Windows_NT)

        HANDLE dir;
        WIN32_FIND_DATA entry;
#endif

        ((strset *)m_files)->clear();
        ((strset *)m_directories)->clear();

        if (m_name.length() == 0)
            return;

#if   defined(Linux)

        dir=opendir(m_name.c_str());

        if (!dir)
        {
            Error_send("Unable to open directory %s\n", m_name.c_str());
            return;
        }

        while ((entry=readdir(dir)) != NULL)
        {
            string name(entry->d_name);
            if (DT_DIR&entry->d_type)
                ((strset *)m_directories)->push_back(name);
            else
                ((strset *)m_files)->push_back(name);
        }

        closedir(dir);
#elif defined(Windows_NT)

        string dir=m_name+"/*";
        dir=FindFirstFile(dir.c_str(), &entry);

        if (dir == INVALID_HANDLE_VALUE)
        {
            Error_send("Unable to open directory %s\n", m_name);
            return;
        }

        do
        {
            string name(entry.cFileName);
            if (entry.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
                ((strset *)m_directories)->push_back(name);
            else
                ((strset *)m_files)->push_back(name);
        }
        while(FindNextFile(dir, &entry) != 0);

        FindClose(dir);
#endif
    }

    unsigned int Directory::getDirectoryCount() const
    {
        return ((strset *)m_directories)->size();
    }

    unsigned int Directory::getFileCount() const
    {
        return ((strset *)m_files)->size();
    }

    const string &Directory::getDirectoryName(const unsigned int &index) const
    {
        unsigned int count=getDirectoryCount();

        if (index < count)
            return (*((strset *)m_directories))[index];

        Error_send("Requested subdirectory %d, %s has %d subdirectories\n", index, m_name.c_str(), count);
        return string::empty;
    }

    const string &Directory::getFileName(const unsigned int &index) const
    {
        unsigned int count=getFileCount();

        if (index < count)
            return (*((strset *)m_files))[index];

        Error_send("Requested file %d, %s has %d files\n", index, m_name.c_str(), count);
        return string::empty;
    }

    string Directory::getDirectoryPath(const unsigned int &index) const
    {
        const string &name=getDirectoryName(index);

        if (name.length() > 0)
            return m_name+"/"+name;
        return string::empty;
    }

    string Directory::getFilePath(const unsigned int &index) const
    {
        const string &name=getFileName(index);

        if (name.length() > 0)
            return m_name+"/"+name;
        return string::empty;
    }
}
