//========================================================================
/** @type     C/C++ Header File
 *  @file     string.h
 *  @author   alex
 *  @date
 *   Created:       11:36:16 30/05/2007
 *   Last Update:   16:34:26 18/01/2008
 */
//========================================================================
#ifndef __CDL_STRING_H__
#define __CDL_STRING_H__

#include <CDL/defs.h>
#include <stdlib.h>

namespace CDL {


struct string_traits
{
    static size_t length(const char *s) {return strlen(s);}
    static int compare(const char *s1, const char *s2, size_t n) {return memcmp(s1,s2,n);}
    static const char *find(const char *s, size_t n, const char &c) {return (const char *)memchr(s,c,n);}
    static char *move(char *s1, const char *s2, size_t n) {return (char *)memmove(s1,s2,n);}
    static char *copy(char *s1, const char *s2, size_t n) {return (char *)memcpy(s1,s2,n);}
    static char *assign(char *s1, size_t n, char c) {return (char *)memset(s1,c,n);}
    static float   toFloat(const char *s) {return (float)atof(s);}
    static double toDouble(const char *s) {return (double)atof(s);}
    static int       toInt(const char *s) {return (int)atoi(s);}
};

class string
{
    private:
        char *m_str;
        size_t m_length;
        int *m_ref;

    public:
        enum {npos=-1};

        string();
        string(size_t n, char c);
        string(const char *s, size_t n=npos);
        string(const string &s, size_t pos=0, size_t n=npos);
        string(const string &s1, const string &s2);
        string(const string &s1, const char *s2);
        string(const char *s1, const string &s2);
        string(const string &s, char c);
        string(char c, const string &s);
        virtual ~string();

        size_t max_size() const {return size_t(-1)/sizeof(char)-1;}
        size_t size() const {return m_length;}
        size_t length() const {return m_length;}
        const char *c_str() const {return m_str;}
        const char *data() const {return m_str;}
        bool empty() const {return m_length == 0;}
        const string &operator=(const string &s);
        const string &operator=(const char *s);
        const char operator[](size_t n) const {return m_str[n];}
        const char at(size_t n) const {return m_str[n];}

        string toLower() const;
        string toUpper() const;
        string substr(size_t pos=0, size_t n=npos) const {return string(*this,pos,n);}
        int compare(size_t pos, size_t n1, const char *s, size_t n2) const
        {
            int len=n1;
            if (n2 < len) len=n2;
            int r=string_traits::compare(m_str+pos,s,len);
            if (!r) return n1-n2;
            return r;
        }
        int compare(const string &s) const {return compare(0,m_length,s.m_str,s.m_length);}
        int compare(size_t pos, size_t n, const string &s) const {return compare(pos,n,s.m_str,s.m_length);}
        int compare(size_t p,size_t n, const string &s,size_t p2,size_t n2) const {return compare(p,n,s.m_str+p2,n2);}
        int compare(const char *s) const {return compare(0,m_length,s,string_traits::length(s));}
        int compare(size_t pos, size_t n, const char *s) const {return compare(pos,n,s,string_traits::length(s));}

        size_t find(const string &s, size_t pos=0) const {return find(s.m_str,pos,s.m_length);}
        size_t find(const char *s, size_t pos=0) const   {return find(s,pos,string_traits::length(s));}
        size_t find(const char *s, size_t pos, size_t n) const;
        size_t find(char c, size_t pos=0) const;
        size_t rfind(const string &s, size_t pos=npos) const {return find(s.m_str,pos,s.m_length);}
        size_t rfind(const char *s, size_t pos=npos) const   {return find(s,pos,string_traits::length(s));}
        size_t rfind(const char *s, size_t pos, size_t n) const;
        size_t rfind(char c, size_t pos=npos) const;
        size_t find_first_of(const string &s, size_t pos=0) const {return find_first_of(s.m_str,pos,s.m_length);}
        size_t find_first_of(const char *s, size_t pos=0) const   {return find_first_of(s,pos,string_traits::length(s));}
        size_t find_first_of(char c, size_t pos=0) const          {return find(c,pos);}
        size_t find_first_of(const char *s, size_t pos, size_t n) const;
        size_t find_first_not_of(const string &s, size_t p=0) const {return find_first_not_of(s.m_str,p,s.m_length);}
        size_t find_first_not_of(const char *s, size_t pos=0) const {return find_first_not_of(s,pos,string_traits::length(s));}
        size_t find_first_not_of(char c, size_t pos=0) const {return find_first_not_of(&c,pos,1);}
        size_t find_first_not_of(const char *s, size_t pos, size_t n) const;
        size_t find_last_of(const string &s, size_t pos=npos) const {return find_last_of(s.m_str,pos,s.m_length);}
        size_t find_last_of(const char *s, size_t pos=npos) const   {return find_last_of(s,pos,string_traits::length(s));}
        size_t find_last_of(char c, size_t pos=npos) const          {return rfind(c,pos);}
        size_t find_last_of(const char *s, size_t pos, size_t n) const;
        size_t find_last_not_of(const string &s, size_t p=npos) const {return find_last_not_of(s.m_str,p,s.m_length);}
        size_t find_last_not_of(const char *s, size_t pos=npos) const {return find_last_not_of(s,pos,string_traits::length(s));}
        size_t find_last_not_of(char c, size_t pos=npos) const        {return find_last_not_of(&c,pos,1);}
        size_t find_last_not_of(const char *s, size_t pos, size_t n) const;

        int    toInt()    const {return string_traits::toInt(m_str);}
        char   toChar()   const {return (char)m_str[0];}
        bool   toBool()   const {return (bool)(!compare("true") ? true : false);}
        float  toFloat()  const {return string_traits::toFloat(m_str);}
        double toDouble() const {return string_traits::toDouble(m_str);}

        static const string nullstr;
        static string printf(const char *, ...);
};

#ifndef SKIP_OPERATORS
inline string operator+(const string &s1, const string &s2) {return string(s1,s2);}
inline string operator+(const char *s1,   const string &s2) {return string(s1,s2);}
inline string operator+(const string &s1, const char *s2)   {return string(s1,s2);}
inline string operator+(const char c,     const string &s)  {return string(c,s);}
inline string operator+(const string &s,  const char c)     {return string(s,c);}

inline bool operator==(const string &s1, const string &s2) {return s1.compare(s2) == 0;}
inline bool operator==(const char *s1,   const string &s2) {return s2.compare(s1) == 0;}
inline bool operator==(const string &s1, const char *s2)   {return s1.compare(s2) == 0;}

inline bool operator!=(const string &s1, const string &s2) {return s1.compare(s2) != 0;}
inline bool operator!=(const char *s1,   const string &s2) {return s2.compare(s1) != 0;}
inline bool operator!=(const string &s1, const char *s2)   {return s1.compare(s2) != 0;}

inline bool operator<(const string &s1, const string &s2)  {return s1.compare(s2) < 0;}
inline bool operator<(const char *s1,   const string &s2)  {return s2.compare(s1) > 0;}
inline bool operator<(const string &s1, const char *s2)    {return s1.compare(s2) < 0;}

inline bool operator>(const string &s1, const string &s2)  {return s1.compare(s2) > 0;}
inline bool operator>(const char *s1,   const string &s2)  {return s2.compare(s1) < 0;}
inline bool operator>(const string &s1, const char *s2)    {return s1.compare(s2) > 0;}

inline bool operator<=(const string &s1, const string &s2) {return s1.compare(s2) <= 0;}
inline bool operator<=(const char *s1,   const string &s2) {return s2.compare(s1) >= 0;}
inline bool operator<=(const string &s1, const char *s2)   {return s1.compare(s2) <= 0;}

inline bool operator>=(const string &s1, const string &s2) {return s1.compare(s2) >= 0;}
inline bool operator>=(const char *s1,   const string &s2) {return s2.compare(s1) <= 0;}
inline bool operator>=(const string &s1, const char *s2)   {return s1.compare(s2) >= 0;}
#endif

}

#endif//__CDL_STRING_H__
