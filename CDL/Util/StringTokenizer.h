//========================================================================
/** @type     C/C++ Header File
 *  @file     StringTokenizer.h
 *  @author   acornejo
 *  @date
 *   Created:       01:13:56 24/01/2006
 *   Last Update:   01:58:33 24/01/2006
 */
//========================================================================

#ifndef __CDL_STRINGTOKENIZER_H__
#define __CDL_STRINGTOKENIZER_H__

#include <CDL/defs.h>


namespace CDL
{
    class StringTokenizer
    {
        private:
            static const char *m_defaultDelim;
            const char *m_str;
            const char *m_ptr;
            const char *m_delim;

        public:
            StringTokenizer(const char *str="", const char *delim=m_defaultDelim);
            virtual ~StringTokenizer();
            size_t countTokens() const;
            bool hasMoreTokens() const;
            void nextToken(char *tok);
    };
}


#endif//__CDL_STRINGTOKENIZER_H__
