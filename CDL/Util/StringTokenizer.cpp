//========================================================================
/** @type     C++ Source File
 *  @file     StringTokenizer.cpp
 *  @author   acornejo
 *  @date
 *   Created:       01:23:39 24/01/2006
 *   Last Update:   19:51:46 02/02/2006
 */
//========================================================================
#include <CDL/Util/StringTokenizer.h>

namespace CDL
{
     DEFCLASS("StringTokenizer");

     const char *StringTokenizer::m_defaultDelim=" \t\n\r\f";

     StringTokenizer::StringTokenizer(const char *str, const char *delim)
     {
          setDelimiter(delim);
          setString(str);
     }

     StringTokenizer::~StringTokenizer() {}

     void StringTokenizer::setDelimiter(const char *delim)
     {
          m_delim=delim;
          m_delimCount=strlen(m_delim);
     }

     void StringTokenizer::setString(const char *str)
     {
          m_str=str;
          m_ptr=&m_str[0];
     }

     const char *StringTokenizer::getDelimiter() const
     {
          return m_delim;
     }

     const char *StringTokenizer::getString() const
     {
          return m_str;
     }

     size_t StringTokenizer::countTokens() const
     {
          size_t tokens=0;
          size_t pos=0;

          while (true)
          {
               bool foundToken=true;
               char c=m_str[pos];

               if (c == '\0') break;
               for (int i=0; i<m_delimCount; i++)
                   if (c == m_delim[i]) foundToken=false;

               if (foundToken)
               {
                    tokens++;
                    do
                    {
                         pos++;
                         c=m_str[pos];
                         for (int i=0; i<m_delimCount; i++)
                             if (c == m_delim[i]) foundToken=false;
                    }
                    while (foundToken && c != '\0');
               }
               else
                   pos++;
          }

          return tokens;
     }

     bool StringTokenizer::hasMoreTokens()
     {
         while(true)
         {
              bool foundToken=true;
              char c=*m_ptr;
              for (int i=0; i<m_delimCount; i++)
                  if (c == m_delim[i]) foundToken=false;

              if (foundToken)
              {
                  if (c == '\0')
                      return false;
                  else
                      return true;
              }
              else
                  m_ptr++;
         }
     }

     const char *StringTokenizer::nextToken(char *_token)
     {
          static char f_token[512];
          char *token;
          const char *token_ptr;

          if (_token)
              token=_token;
          else
              token=f_token;
          token_ptr=&token[0];

          while (true)
          {
               bool foundToken=true;
               char c=*m_ptr;
               for (int i=0; i<m_delimCount; i++)
                   if (c == m_delim[i]) foundToken=false;

               if (foundToken)
               {
                    do
                    {
                         if (*m_ptr == '\0') break;
                         *(token++)=*(m_ptr++);
                         c=*m_ptr;
                         for (int i=0; i<m_delimCount; i++)
                                if (c == m_delim[i]) foundToken=false;
                    }
                    while (foundToken);
                    *token='\0';
                    return token_ptr;
               }
               else
                   m_ptr++;
          }
     }
}
