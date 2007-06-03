//========================================================================
/** @type     C/C++ Header File
 *  @file     StringTokenizer.h
 *  @author   acornejo
 *  @date
 *   Created:       01:13:56 24/01/2006
 *   Last Update:   17:43:43 02/06/2007
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
            string m_str;
            string m_delim;
            size_t m_pos;

        public:
            StringTokenizer(string str=string::nullstr, string delim=m_defaultDelim);
            void setDelimiter(string &);
            const string &getDelimiter() const;
            void setString(string &);
            const string &getString() const;
            virtual ~StringTokenizer();
            size_t countTokens() const;
            bool hasMoreTokens() const;
            string nextToken();
    };
}

#endif//__CDL_STRINGTOKENIZER_H__
