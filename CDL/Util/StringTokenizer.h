//========================================================================
/** @type     C/C++ Header File
 *  @file     StringTokenizer.h
 *  @author   acornejo
 *  @date
 *   Created:       01:13:56 24/01/2006
 *   Last Update:   19:51:20 02/02/2006
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
            size_t m_delimCount;
            const char *m_str;
            const char *m_ptr;
            const char *m_delim;

        public:
            StringTokenizer(const char *str="", const char *delim=m_defaultDelim);
            void setDelimiter(const char *);
            const char *getDelimiter() const;
            void setString(const char *);
            const char *getString() const;
            virtual ~StringTokenizer();
            size_t countTokens() const;
            bool hasMoreTokens();
            const char *nextToken(char *tok='\0');
    };
}


#endif//__CDL_STRINGTOKENIZER_H__
