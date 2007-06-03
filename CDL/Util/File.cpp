#include <CDL/Util/File.h>

#if   defined(Windows_NT)
	#include <io.h>
#else
	#include <unistd.h>
#endif

namespace CDL
{
    DEFCLASS("File");

    File::File(const string &name, const int &mode): m_name(name)
    {
        if (m_name.length() > 0)
        {
            m_mode=mode;
            char strMode[4]={'w','b','+','\0'};

            if (m_mode&READ)
                strMode[0]='r';
            if (m_mode&WRITE)
                strMode[0]='w';
            if (m_mode&WRITE && mode&READ)
                strMode[2]='+';
            else
                strMode[2]='\0';
            if (strMode[0] == '\0')
                return;

            if ((m_fp=fopen(m_name.c_str(), strMode)) == NULL)
            {
                Error_send("Unable to open file %s as %s\n", m_name.c_str(), strMode);
                m_mode=0;
            }
        }
        else
        {
            m_fp=NULL;
            m_mode=0;
        }
    }

    File::File(FILE *fp, const int &mode)
    {
        m_fp=fp;
        m_mode=mode;
        m_mode|=NOCLOSE;
    }

    File::~File()
    {
        close();
    }

    void File::close()
    {
        if (m_mode && !(m_mode&NOCLOSE))
        {
            fflush(m_fp);
            fclose(m_fp);
        }
        m_fp=NULL;
        m_mode=0;
    }

    bool File::exists(const string &name)
    {
        return access(name.c_str(), 0) != -1;
    }

    const string &File::getName() const
    {
        return m_name;
    }

    string File::getExtension() const
    {
        int pos=m_name.find('.');
        if (pos == string::npos)
            return string::nullstr;
        else
            return m_name.substr(pos+1);
    }

    void File::flush()
    {
        if (m_mode&WRITE)
            fflush(m_fp);
        else
        {
            if (m_mode&READ)
            {
                Error_send("Unable to flush read-only file %s\n", m_name.c_str());
                return;
            }
        }
    }

    void File::putback(const char &c)
    {
        if (m_mode&READ)
            ungetc((int)c,m_fp);
        else
        {
            if (m_mode&WRITE)
            {
                Error_send("Unable to put back character in write-only file %s\n", m_name.c_str());
                return;
            }
        }
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
                Error_send("Unable to read write-only file %s\n", m_name.c_str());
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
                Error_send("Unable to write read-only file %s\n", m_name.c_str());
                return 0;
            }
            return -1;
        }
    }

    int File::seek(const long &aPos, const int &type)
    {
        fseek(m_fp, aPos, type);
    }

    long  File::tell()
    {
        return ftell(m_fp);
    }
}
