//========================================================================
/** @type     C/C++ Header File
 *  @file     StringTokenizer.h
 *  @author   acornejo
 *  @date
 *   Created:       01:13:56 24/01/2006
 *   Last Update:   18:45:37 30/05/2007
 */
//========================================================================

#ifndef __CDL_STRINGTOKENIZER_H__
#define __CDL_STRINGTOKENIZER_H__

#include <CDL/defs.h>
#include <CDL/Util/string.h>

namespace CDL
{
    class StringTokenizer
    {
        private:
            static const string m_defaultDelim;
            const string *m_str;
            const string *m_delim;
            size_t m_pos;

        public:
            StringTokenizer(const string &str=string::empty, const string &delim=m_defaultDelim);
            void setDelimiter(const string &);
            const string &getDelimiter() const;
            void setString(const string &);
            const string &getString() const;
            virtual ~StringTokenizer();
            size_t countTokens() const;
            bool hasMoreTokens();
            string nextToken();
    };
}

#endif//__CDL_STRINGTOKENIZER_H__
