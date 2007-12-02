#ifndef __CDTL_ARRAY_H__
#define __CDTL_ARRAY_H__

#include <stdio.h>

namespace CDL { namespace CDTL {

template <class T, size_t N>
class array
{
    private:
        T elem[N];
    
    public:
        array() {}
        template <class U>
        array(const array<U,N> &a)
        {
            for (size_t i=0; i<N; i++)
                elem[i]=a.elem[i];
        }
        template <class U>
        array &operator=(const array<U,N> &a)
        {
            for (size_t i=0; i<N; i++)
                elem[i]=a.elem[i];
            return *this;
        }
        T &operator[](const size_t &i)
        {
            return elem[i];
        }
        const T &operator[](const size_t &i) const
        {
            return elem[i];
        }
        size_t size() const {return N;}
};
}}

#endif//__CDTL_ARRAY_H__
