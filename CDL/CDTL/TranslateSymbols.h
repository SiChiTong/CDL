//========================================================================
/** @type     C/C++ Header File
 *  @file     TranslateSymbols.h
 *  @author   acornejo
 *  @date
 *   Created:       22:58:14 07/06/2005
 *   Last Update:   16:07:29 18/02/2006
 */
//========================================================================

#ifndef __TRANSLATESYMBOLS_H__
#define __TRANSLATESYMBOLS_H__

#include <CDL/defs.h>
#include <cstdarg>
#include <map>

namespace CDL
{
    namespace CDTL
    {
        template<class symbol1, class symbol2>
            class TranslateSymbols
            {
                private:
                    std::map<symbol1,symbol2> m_forward;
                    std::map<symbol2,symbol1> m_backward;

                public:
                    TranslateSymbols(const size_t &n=0, ...)
                    {
                         va_list ap;
                         va_start(ap, n);
                         for (size_t i=0; i<n; i++)
                         {
                             symbol1 s1=va_arg(ap, symbol1);
                             symbol2 s2=va_arg(ap, symbol2);
                             insertPair(s1,s2);
                         }
                         va_end(ap);
                    }
                    symbol2 forward(symbol1 key) const
                    {
                        typename std::map<symbol1,symbol2>::const_iterator i(m_forward.find(key));
                        if (i == m_forward.end())
                            return m_forward.begin()->second;
                        else
                            return i->second;
                    }
                    symbol1 backward(symbol2 key) const
                    {
                        typename std::map<symbol2,symbol1>::const_iterator i(m_backward.find(key));
                        if (i == m_backward.end())
                            return m_backward.begin()->second;
                        else
                            return i->second;
                    }
                    void insertPair(symbol1 s1, symbol2 s2)
                    {
                         m_forward.insert(std::pair<symbol1,symbol2>(s1,s2));
                         m_backward.insert(std::pair<symbol2,symbol1>(s2,s1));
                    }
            };
    }
}

#endif//__TRANSLATESYMBOLS_H__
