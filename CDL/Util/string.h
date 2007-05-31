//========================================================================
/** @type     C/C++ Header File
 *  @file     string.h
 *  @author   alex
 *  @date
 *   Created:       11:36:16 30/05/2007
 *   Last Update:   23:17:30 30/05/2007
 */
//========================================================================
#ifndef __CDL_STRING_H__
#define __CDL_STRING_H__

#include <CDL/defs.h>

namespace CDL {

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

        const size_t &length() const {return m_length;}
        const char *c_str() const {return m_str;}
        const string &operator=(const string &s);
        const string &operator=(const char *s);
        const char operator[](size_t n) const {return m_str[n];}
        const char at(size_t n) const {return m_str[n];}

        string toLower() const;
        string toUpper() const;
        string substr(size_t pos=0, size_t n=npos) const {return string(*this,pos,n);}
        int compare(const string &s) const {return strcmp(m_str,s.m_str);}
        int compare(const char *s) const {return strcmp(m_str,s);}

        size_t find(const string &s, size_t pos=0) const;
        size_t find(const char *s, size_t pos=0) const;
        size_t find(char c, size_t pos=0) const;
        size_t rfind(const string &s, size_t pos=npos) const;
        size_t rfind(const char *s, size_t pos=npos) const;
        size_t rfind(char c, size_t pos=npos) const;
        size_t find_of(const string &s, size_t pos=0) const;
        size_t find_of(const char *s, size_t pos=0) const;
        size_t find_nof(const string &s, size_t pos=0) const;
        size_t find_nof(const char *s, size_t pos=0) const;
        size_t rfind_of(const string &s, size_t pos=npos) const;
        size_t rfind_of(const char *s, size_t pos=npos) const;
        size_t rfind_nof(const string &s, size_t pos=npos) const;
        size_t rfind_nof(const char *s, size_t pos=npos) const;

        int    toInt() const;
        char   toChar() const;
        bool   toBool() const;
        float  toFloat() const;
        double toDouble() const;

        static const string empty;
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
