//========================================================================
/** @type     C++ Source File
 *  @file     StringTokenizer.cpp
 *  @author   acornejo
 *  @date
 *   Created:       01:23:39 24/01/2006
 *   Last Update:   01:59:37 24/01/2006
 */
//========================================================================
#include <CDL/Util/StringTokenizer.h>

namespace CDL
{
     DEFCLASS("StringTokenizer");

     const char *StringTokenizer::m_defaultDelim=" \t\n\r\f";

     StringTokenizer::StringTokenizer(const char *str, const char *delim)
     {
          m_str=str;
          m_ptr=&m_str[0];
          m_delim=delim;
     }

     StringTokenizer::~StringTokenizer() {}

     size_t StringTokenizer::countTokens() const
     {
          size_t tokens=0;
          size_t pos=0, delimCount=strlen(m_delim);

          while (true)
          {
               bool foundToken=true;
               char c=m_str[pos];

               if (c == '\0') break;
               for (int i=0; i<delimCount; i++)
                   if (c == m_delim[i]) foundToken=false;

               if (foundToken)
               {
                    tokens++;
                    do
                    {
                         pos++;
                         c=m_str[pos];
                         for (int i=0; i<delimCount; i++)
                             if (c == m_delim[i]) foundToken=false;
                    }
                    while (foundToken && c != '\0');
               }
               else
                   pos++;
          }

          return tokens;
     }

     bool StringTokenizer::hasMoreTokens() const
     {
          size_t pos=0, delimCount=strlen(m_delim);

         while(true)
         {
              bool foundToken=true;
              char c=m_ptr[pos++];
              if (c == '\0') return false;
              for (int i=0; i<delimCount; i++)
                  if (c == m_delim[i]) foundToken=false;

              if (foundToken) return true;
         }
     }

     void StringTokenizer::nextToken(char *token)
     {
          size_t delimCount=strlen(m_delim);

          while (true)
          {
               bool foundToken=true;
               char c=*m_ptr;
               for (int i=0; i<delimCount; i++)
                   if (c == m_delim[i]) foundToken=false;

               if (foundToken)
               {
                    do
                    {
                         if (*m_ptr == '\0') break;
                         *(token++)=*(m_ptr++);
                         c=*m_ptr;
                         for (int i=0; i<delimCount; i++)
                                if (c == m_delim[i]) foundToken=false;
                    }
                    while (foundToken);
                    *token='\0';
                    return;
               }
               else
                   m_ptr++;
          }
     }
}
