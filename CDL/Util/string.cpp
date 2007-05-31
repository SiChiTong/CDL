//========================================================================
/** @type     C/C++ Header File
 *  @file     string.h
 *  @author   alex
 *  @date
 *   Created:       11:36:16 30/05/2007
 *   Last Update:   02:05:32 31/05/2007
 */
//========================================================================
#define SKIP_OPERATORS
#include "string.h"
#include <ctype.h>
#include <stdlib.h>
#include <cstdarg>

namespace CDL {

const string string::empty;

string string::printf(const char *fmt, ...)
{
    char tmp[1];
    va_list ap;

    va_start(ap, fmt);
    int len=vsnprintf(tmp, 1, fmt, ap);
    va_end(ap);

    if (len > 1)
    {
        string str(len,'\0'); 
        va_start(ap, fmt);
        int len=vsnprintf(str.m_str, len+1, fmt, ap);
        va_end(ap);
        return str;
    }

    return string::empty;
}

string::string()
{
    m_ref=new int(1);
    m_length=0;
    m_str=new char[1];
    m_str[m_length]='\0';
}
string::string(size_t n, char c)
{
    m_ref=new int(1);
    m_length=n;
    m_str=new char[m_length+1];
    memset(m_str,c,n);
    m_str[m_length]='\0';
}
string::string(const char *s, size_t n)
{
    m_ref=new int(1);
    if (n == npos)
        m_length=strlen(s);
    else
        m_length=n;
    m_str=new char[m_length+1];
    memcpy(m_str,s,m_length);
    m_str[m_length]='\0';
}
string::string(const string &s, size_t pos, size_t n)
{
    if (n == npos)
    {
        m_ref=s.m_ref;
        ++(*m_ref);
        m_length=s.m_length-pos;
        m_str=&s.m_str[pos];
    }
    else
    {
        m_ref=new int(1);
        m_length=n;
        m_str=new char[m_length+1];
        memcpy(m_str,&s.m_str[pos],m_length);
        m_str[m_length]='\0';
    }
}
string::string(const string &s1, const string &s2)
{
    m_ref=new int(1);
    m_length=s1.m_length+s2.m_length;
    m_str=new char[m_length+1];
    memcpy(m_str,s1.m_str,s1.m_length);
    memcpy(&m_str[s1.m_length],s2.m_str,s2.m_length);
    m_str[m_length]='\0';
}
string::string(const string &s1, const char *s2)
{
    int len2=strlen(s2);
    m_ref=new int(1);
    m_length=s1.m_length+len2;
    m_str=new char[m_length+1];
    memcpy(m_str,s1.m_str,s1.m_length);
    memcpy(&m_str[s1.m_length],s2,len2);
    m_str[m_length]='\0';
}
string::string(const char *s1, const string &s2)
{
    int len1=strlen(s1);
    m_ref=new int(1);
    m_length=len1+s2.m_length;
    m_str=new char[m_length+1];
    memcpy(m_str,s1,len1);
    memcpy(&m_str[len1],s2.m_str,s2.m_length);
    m_str[m_length]='\0';
}
string::string(const string &s, char c)
{
    m_ref=new int(1);
    m_length=s.m_length+1;
    m_str=new char[m_length+1];
    memcpy(m_str,s.m_str,s.m_length);
    m_str[s.m_length]=c;
    m_str[m_length]='\0';
}
string::string(char c, const string &s)
{
    m_ref=new int(1);
    m_length=s.m_length+1;
    m_str=new char[m_length+1];
    m_str[0]=c;
    memcpy(&m_str[1],s.m_str,s.m_length);
    m_str[m_length]='\0';
}
string::~string()
{
    if(!--(*m_ref))
    {
        delete m_ref;
        delete []m_str;
    }
}

const string &string::operator=(const string &s)
{
    if (this != &s)
    {
        if (!--(*m_ref))
        {
            delete m_ref;
            delete []m_str;
        }
        m_ref=s.m_ref;
        ++(*m_ref);
        m_str=s.m_str;
        m_length=s.m_length;
    }

    return *this;
}

const string &string::operator=(const char *s)
{
    if (m_str != s)
    {
        if (!--(*m_ref))
        {
            delete m_ref;
            delete []m_str;
        }
        m_ref=new int(1);
        m_length=strlen(s);
        m_str=new char[m_length+1];
        memcpy(m_str,s,m_length);
        m_str[m_length]='\0';
    }

    return *this;
}

string string::toLower() const
{
    string lower(m_str,m_length);
    for (int i=0; i<m_length; i++)
        lower.m_str[i]=tolower(lower.m_str[i]);

    return lower;
}

string string::toUpper() const
{
    string upper(m_str,m_length);
    for (int i=0; i<m_length; i++)
        upper.m_str[i]=toupper(upper.m_str[i]);

    return upper;
}

size_t string::find(const string &s, size_t pos) const
{
    return find(s.m_str,pos);
}

size_t string::find(const char *s, size_t pos) const
{
    char *ptr=strstr(&m_str[pos],s);
    if (ptr == NULL) return npos;
    return ptr-m_str;
}

size_t string::find(char c, size_t pos) const
{
    char *ptr=strchr(&m_str[pos],c);
    if (ptr == NULL) return npos;
    return ptr-m_str;
}

size_t string::rfind(const string &s, size_t pos) const
{
    return rfind(s.m_str,pos);
}

size_t string::rfind(const char *s, size_t pos) const
{
    for (int i=(pos == npos ? m_length -1 : pos); i>=0; i--)
        if (!strcmp(&m_str[pos],s))
            return i;
    return npos;
}

size_t string::rfind(char c, size_t pos) const
{
    for (int i=(pos == npos ? m_length -1 : pos); i>=0; i--)
        if (m_str[i] == c)
            return i;
    return npos;
}

size_t string::find_of(const string &s, size_t pos) const
{
    for (int i=pos; i<m_length; i++)
    {
        for (int j=0; j<s.m_length; j++)
            if (m_str[i] == s.m_str[j])
                return i;
    }
    return npos;
}

size_t string::find_of(const char *s, size_t pos) const
{
    int len=strlen(s);
    for (int i=pos; i<m_length; i++)
    {
        for (int j=0; j<len; j++)
            if (m_str[i] == s[j])
                return i;
    }
    return npos;
}

size_t string::find_nof(const string &s, size_t pos) const
{
    for (int i=pos; i<m_length; i++)
    {
        for (int j=0; j<s.m_length; j++)
            if (m_str[i] != s.m_str[j])
                return i;
    }
    return npos;
}

size_t string::find_nof(const char *s, size_t pos) const
{
    int len=strlen(s);
    for (int i=pos; i<m_length; i++)
    {
        for (int j=0; j<len; j++)
            if (m_str[i] != s[j])
                return i;
    }
    return npos;
}

size_t string::rfind_of(const string &s, size_t pos) const
{
    for (int i=(pos == npos ? m_length -1 : pos); i>=0; i--)
    {
        for (int j=0; j<s.m_length; j++)
            if (m_str[i] == s.m_str[j])
                return i;
    }
    return npos;
}

size_t string::rfind_of(const char *s, size_t pos) const
{
    int len=strlen(s);
    for (int i=(pos == npos ? m_length -1 : pos); i>=0; i--)
    {
        for (int j=0; j<len; j++)
            if (m_str[i] == s[j])
                return i;
    }
    return npos;
}

size_t string::rfind_nof(const string &s, size_t pos) const
{
    for (int i=(pos == npos ? m_length -1 : pos); i>=0; i--)
    {
        for (int j=0; j<s.m_length; j++)
            if (m_str[i] != s.m_str[j])
                return i;
    }
    return npos;
}

size_t string::rfind_nof(const char *s, size_t pos) const
{
    int len=strlen(s);
    for (int i=(pos == npos ? m_length -1 : pos); i>=0; i--)
    {
        for (int j=0; j<len; j++)
            if (m_str[i] != s[j])
                return i;
    }
    return npos;
}

int    string::toInt()    const {return (int)atoi(m_str);}
char   string::toChar()   const {return (char)m_str[0];}
bool   string::toBool()   const {return (bool)(!compare("true") ? true : false);}
float  string::toFloat()  const {return (float)atof(m_str);}
double string::toDouble() const {return (double)atof(m_str);}

}
