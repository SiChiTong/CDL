#include <CDL/Util/File.h>

#if   defined(Windows_NT)
	#include <io.h>
#else
	#include <unistd.h>
#endif

namespace CDL
{
    DEFCLASS("File");

    File::File(const char *name)
    {
        m_ref=new int(1);
        if (name)
        {
            if ((m_fp=fopen(name, "r")) != NULL)
            {
                m_mode=READ;
                m_name=new char[strlen(name)+1];
                strcpy(m_name, name);
            }
            else
            {
                Error_send("Unable to open file %s\n", name);
                m_mode=0;
                m_name='\0';
            }
        }
        else
        {
            m_fp=NULL;
            m_mode=0;
            m_name='\0';
        }
    }

    File::File(const char *name, const int &mode)
    {
        m_ref=new int(1);
        if (name)
        {
            char strMode[4]={'w','b','+','\0'};

            if (mode&READ)
                strMode[0]='r';
            if (mode&WRITE)
                strMode[0]='w';
            if (mode&WRITE && mode&READ)
                strMode[2]='+';
            else
                strMode[2]='\0';
            if (strMode[0] == '\0')
                return;

            if ((m_fp=fopen(name, strMode)) != NULL)
            {
                m_mode=mode;
                m_name=new char[strlen(name)+1];
                strcpy(m_name,name);
            }
            else
            {
                Error_send("Unable to open file %s\n", name);
                m_mode=0;
                m_name='\0';
            }
        }
        else
        {
            m_fp=NULL;
            m_mode=0;
            m_name='\0';
        }
    }

    File::File(FILE *fp, const int &mode)
    {
        m_ref=new int(1);
        m_fp=fp;
        m_mode=mode;
        m_mode|=NOCLOSE;
        m_name='\0';
    }

    File::File(const File &f)
    {
        m_ref=f.m_ref;
        ++(*m_ref);
        m_fp=f.m_fp;
        m_mode=f.m_mode;
        m_name=f.m_name;
    }

    File::~File()
    {
        --(*m_ref);
        if (*m_ref == 0)
        {
            delete m_ref;
            close();
        }
    }

    File& File::operator=(const File &f)
    {
        if (this != &f)
        {
            --(*m_ref);
            if (*m_ref == 0)
            {
                delete m_ref;
                close();
            }
            m_ref=f.m_ref;
            ++(*m_ref);
            m_fp=f.m_fp;
            m_mode=f.m_mode;
            m_name=f.m_name;
        }
        return *this;
    }

    void File::close()
    {
        if (*m_ref < 2)
        {
            if (m_mode && !(m_mode&NOCLOSE))
			{
				fflush(m_fp);
                fclose(m_fp);
			}
            if (m_name)
                delete []m_name;
        }
        m_fp=NULL;
        m_mode=0;
        m_name='\0';
    }

    bool File::exists(const char *name)
    {
        return access(name, 0) != -1;
    }

    const char *File::getName() const
    {
        return m_name;
    }

    void File::flush()
    {
        if (m_mode&WRITE)
            fflush(m_fp);
        else
        {
            if (m_mode&READ)
            {
                Error_send("Unable to flush read-only file %s\n", m_name);
                return;
            }
        }
    }

    void File::putback(const int &c)
    {
        if (m_mode&READ)
            ungetc(c,m_fp);
        else
        {
            if (m_mode&WRITE)
            {
                Error_send("Unable to put back character in write-only file %s\n", m_name);
                return;
            }
        }
    }

    int File::size()
    {
         int pos=tell();
         seek(0L,SEEK_END);
         int size=tell();
         seek(pos,SEEK_SET);
         return size;
    }

    int File::read(void *vData, const int &cnt)
    {
        if (m_mode&READ)
        {
            int count=fread(vData, 1, cnt, m_fp);
            if (count != cnt)
                m_mode=0;
            return count;
        }
        else
        {
            if (m_mode&WRITE)
            {
                Error_send("Unable to read write-only file %s\n", m_name);
                return 0;
            }
            return -1;
        }
    }

    int File::write(const void *vData, const int &cnt)
    {
        if (m_mode&WRITE)
        {
            int count=fwrite(vData, 1, cnt, m_fp);
            if (count != cnt)
                m_mode=0;
            return count;
        }
        else
        {
            if (m_mode&READ)
            {
                Error_send("Unable to write read-only file %s\n", m_name);
                return 0;
            }
            return -1;
        }
    }

    bool File::isEOF() const
    {
        return feof(m_fp) != 0;
    }

    int File::seek(const long &aPos, const int &type)
    {
        return fseek(m_fp, aPos, type);
    }

    long  File::tell()
    {
        return ftell(m_fp);
    }
}
