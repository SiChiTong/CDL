//========================================================================
/** @type     C++ Source File
 *  @file     StringTokenizer.cpp
 *  @author   acornejo
 *  @date
 *   Created:       01:23:39 24/01/2006
 *   Last Update:   01:26:13 31/05/2007
 */
//========================================================================
#include <CDL/Util/StringTokenizer.h>

namespace CDL
{
    DEFCLASS("StringTokenizer");

    string const StringTokenizer::m_defaultDelim=" \t\n\r\f";

    StringTokenizer::StringTokenizer(string str, string delim): m_str(str), m_delim(delim)
    {
        m_pos=-1;
    }

    StringTokenizer::~StringTokenizer() {}

    void StringTokenizer::setDelimiter(string &delim)
    {
          m_delim=delim;
    }

    void StringTokenizer::setString(string &str)
    {
          m_str=str;
          m_pos=0;
    }

    const string &StringTokenizer::getDelimiter() const
    {
          return m_delim;
    }

    const string &StringTokenizer::getString() const
    {
          return m_str;
    }

    size_t StringTokenizer::countTokens() const
    {
        size_t tokens=0;
        size_t o_pos;
        size_t n_pos=m_pos;

        do
        {
            o_pos=n_pos+1;
            n_pos=m_str.find_of(m_delim,o_pos);
            if (n_pos != string::npos && n_pos > o_pos)
                tokens++;
        }
        while (n_pos != string::npos);

        if (o_pos < m_str.length()-1)
            tokens++;

        return tokens;
    }

    bool StringTokenizer::hasMoreTokens() const
    {
        size_t o_pos;
        size_t n_pos=m_pos;

        do
        {
            o_pos=n_pos+1;
            n_pos=m_str.find_of(m_delim,o_pos);
            if (n_pos != string::npos && n_pos > o_pos)
                return true;
        }
        while (n_pos != string::npos);

        if (o_pos < m_str.length()-1)
            return true;

        return false;
    }

    string StringTokenizer::nextToken()
    {
        size_t o_pos;

        do
        {
            o_pos=m_pos+1;
            m_pos=m_str.find_of(m_delim,o_pos);
            if (m_pos != string::npos && m_pos > o_pos)
                return m_str.substr(o_pos,m_pos-o_pos);
        }
        while (m_pos != string::npos);

        if (o_pos < m_str.length()-1)
        {
            m_pos=m_str.length();
            return m_str.substr(o_pos);
        }

        return string::empty;
    }
}
