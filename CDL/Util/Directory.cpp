#include <CDL/Util/Directory.h>

#ifdef Windows_NT
#include <windows.h>
#endif
#include <dirent.h>
#include <set>

namespace CDL
{
    DEFCLASS("Directory");

    struct ltstr
    {
        bool operator()(const char *s1, const char *s2)
        {
            return strcmp(s1,s2) < 0;
        }
    };

    typedef std::set
        <const char *, ltstr> strset;

    Directory::Directory(const char *name)
    {
        m_ref=new int(1);
        m_directories=new strset;
        m_files=new strset;
        if (name != '\0')
        {
            m_name=new char[strlen(name)+1];
            strcpy(m_name, name);
            if (strchr("/\\", m_name[strlen(m_name)-1]))
                m_name[strlen(m_name)-1]='\0';
        }
        else
            m_name='\0';

        refresh();
    }

    Directory::~Directory()
    {
        --(*m_ref);
        if ((*m_ref) == 0)
        {
            delete m_ref;
            if (m_name)
                delete []m_name;
            m_name='\0';
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
            --(*m_ref);
            if (*m_ref == 0)
            {
                delete m_ref;
                if (m_name)
                    delete []m_name;
                m_name='\0';
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

        char *name;

        for (strset::iterator i=((strset *)m_files)->begin(); i != ((strset *)m_files)->end(); ++i)
            delete []*i;
        ((strset *)m_files)->clear();
        for (strset::iterator i=((strset *)m_directories)->begin(); i != ((strset *)m_directories)->end(); ++i)
            delete []*i;
        ((strset *)m_directories)->clear();

        if (!m_name)
            return;

#if   defined(Linux)

        dir=opendir(m_name);

        if (!dir)
        {
            Error_send("Unable to open directory %s\n", m_name);
            return;
        }

        while ((entry=readdir(dir)) != NULL)
        {
            name=new char[strlen(entry->d_name)+1];
            strcpy(name, entry->d_name);
            if (DT_DIR&entry->d_type)
                ((strset *)m_directories)->insert(name);
            else
                ((strset *)m_files)->insert(name);
        }

        closedir(dir);
#elif defined(Windows_NT)

        name=new char[strlen(m_name)+3];
        strcat(strcpy(name,m_name),"/*");
        dir=FindFirstFile(name, &entry);
        delete name;

        if (dir == INVALID_HANDLE_VALUE)
        {
            Error_send("Unable to open directory %s\n", m_name);
            return;
        }

        do
        {
            name=new char[strlen(entry.cFileName)+1];
            strcpy(name, entry.cFileName);
            if (entry.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
                ((strset *)m_directories)->insert(name);
            else
                ((strset *)m_files)->insert(name);
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

    const char *Directory::getDirectoryName(const unsigned int &index) const
    {
        unsigned int count=getDirectoryCount();

        if (index < count)
        {
            strset::iterator i=((strset *)m_directories)->begin();
            for (int j=0; j<index; j++, i++)
                ;
            return *i;
        }

        Error_send("Requested subdirectory %d, %s has %d subdirectories\n", index, m_name, count);
        return '\0';
    }

    const char *Directory::getFileName(const unsigned int &index) const
    {
        unsigned int count=getFileCount();

        if (index < count)
        {
            strset::iterator i=((strset *)m_files)->begin();
            for (int j=0; j<index; j++, i++)
                ;
            return *i;
        }

        Error_send("Requested file %d, %s has %d files\n", index, m_name, count);
        return '\0';
    }

    Directory Directory::getDirectory(const unsigned int &index) const
    {
        char path[512];
        const char *name=getDirectoryName(index);

        if (name)
        {
            strcpy(path, m_name);
            strcat(path, "/");
            strcat(path,name);
            return Directory(path);
        }
        return Directory();
    }

    File Directory::getFile(const unsigned int &index) const
    {
        char path[512];
        const char *name=getFileName(index);

        if (name)
        {
            strcpy(path, m_name);
            strcat(path, "/");
            strcat(path,name);
            return File(path, File::READ|File::WRITE);
        }
        return File();
    }
}
