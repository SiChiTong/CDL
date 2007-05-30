//========================================================================
/** @type     C++ Source File
 *  @file     StringTokenizer.cpp
 *  @author   acornejo
 *  @date
 *   Created:       01:23:39 24/01/2006
 *   Last Update:   18:47:21 30/05/2007
 */
//========================================================================
#include <CDL/Util/StringTokenizer.h>

namespace CDL
{
    DEFCLASS("StringTokenizer");

    const string StringTokenizer::m_defaultDelim=" \t\n\r\f";

    StringTokenizer::StringTokenizer(const string &str, const string &delim): m_str(&str), m_delim(&delim)
    {
        m_pos=0;
    }

    StringTokenizer::~StringTokenizer() {}

    void StringTokenizer::setDelimiter(const string &delim)
    {
          m_delim=&delim;
    }

    void StringTokenizer::setString(const string &str)
    {
          m_str=&str;
          m_pos=0;
    }

    const string &StringTokenizer::getDelimiter() const
    {
          return *m_delim;
    }

    const string &StringTokenizer::getString() const
    {
          return *m_str;
    }

    size_t StringTokenizer::countTokens() const
    {
        size_t tokens=0;
        size_t o_pos=m_pos;
        size_t n_pos=m_pos;

        while (n_pos != string::npos)
        {
            if (n_pos > o_pos+1)
                tokens++;
            o_pos=n_pos;
            n_pos=m_str->find(*m_delim,o_pos+1);
        }

        if (o_pos != string::npos && o_pos < m_str->length()-1)
            tokens++;

        return tokens;
    }

    bool StringTokenizer::hasMoreTokens()
    {
        size_t o_pos=m_pos;
        size_t n_pos=m_pos;

        while (n_pos != string::npos)
        {
            if (n_pos > o_pos+1)
                return true;
            o_pos=n_pos;
            n_pos=m_str->find(*m_delim,o_pos+1);
        }

        if (o_pos != string::npos && o_pos < m_str->length()-1)
            return true;

        return false;
    }

    string StringTokenizer::nextToken()
    {
        size_t o_pos=m_pos;

        while (m_pos != string::npos)
        {
            if (m_pos > o_pos+1)
                return m_str->substr(o_pos+1,m_pos);
            o_pos=m_pos;
            m_pos=m_str->find(*m_delim,o_pos+1);
        }

        if (o_pos != string::npos && o_pos < m_str->length()-1)
            return m_str->substr(o_pos);

        return string::empty;
    }
}
