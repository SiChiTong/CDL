#ifndef __CDTL_ARRAY_H__
#define __CDTL_ARRAY_H__

#include <CDL/CDTL/iterator.h>
#include <CDL/CDTL/function_base.h>

namespace CDL { namespace CDTL {

template <class T, size_t N>
class array
{
    private:
        T elem[N];
        
    public:
        template <class U>
        class array_iterator: public iterator_base<random_access_iterator_tag,U,int>
        {
// FIXME: should use reference instead of U& and difference_type instead of int
            private:
                U *ptr;
            public:
                typedef array_iterator<U> self;

                array_iterator(U *_ptr): ptr(_ptr) {}
                U &operator*() {return *ptr;}
                self &operator++() {ptr++; return *this;}
                self &operator--() {ptr--; return *this;}
                self operator++(int) {self tmp=*this; ptr++; return tmp;}
                self operator--(int) {self tmp=*this; ptr--; return tmp;}
                bool operator==(const self &r) const {return ptr == r.ptr;}
                bool operator!=(const self &r) const {return ptr != r.ptr;}

                self operator+(int n) const {return self(ptr+n);}
                self operator-(int n) const {return self(ptr-n);}
                self &operator+=(int n) {ptr+=n; return *this;}
                self &operator-=(int n) {ptr-=n; return *this;}
                U &operator[](int n) const {return *(*this+n);}

            friend class array;
        };
        typedef array<T,N> self;

// Container types
        typedef T value_type;
        typedef value_type &reference;
        typedef value_type *pointer;
        typedef int difference_type;
        typedef const value_type &const_reference;
        typedef const value_type *const_pointer;
        typedef size_t size_type;
        typedef array_iterator<const value_type> const_iterator;
        typedef array_iterator<value_type> iterator;

// Reversible container types
        typedef reverse_iterator<const_iterator> const_reverse_iterator;
        typedef reverse_iterator<iterator> reverse_iterator;

// Container methods
        array() {}
        template <class U>
        array(const array<U,N> &a)
        {
            for (size_type i=0; i<N; i++)
                elem[i]=a.elem[i];
        }
        template <class U>
        array &operator=(const array<U,N> &a)
        {
            for (size_type i=0; i<N; i++)
                elem[i]=a.elem[i];
            return *this;
        }
        iterator       begin() {return elem;}
        const_iterator begin() const {return elem;}
        iterator       end()   {return elem+N;}
        const_iterator end() const {return elem+N;}
        size_type      max_size() const {return N;}
        size_type      size() const {return N;}
        bool           empty() const {return N == 0;}
        template <class U>
        void swap(const array<U,N> &a)
        {
            U tmp;
            for (size_type i=0; i<N; i++)
            {
                tmp=a.elem[i];
                a.elem[i]=elem[i];
                elem[i]=tmp;
            }
        }
        reference       front() {return elem[0];}
        const_reference front() const {return elem[0];}

// Reversible container methods
        reverse_iterator       rbegin() {return reverse_iterator(end());}
        const_reverse_iterator rbegin() const {return const_reverse_iterator(end());}
        reverse_iterator       rend()   {return reverse_iterator(begin());}
        const_reverse_iterator rend() const {return const_reverse_iterator(begin());}

// Random access container
        reference       at(size_type i) { return elem[i]; }       // should do rangecheck and throw exception
        const_reference at(size_type i) const { return elem[i]; } // should do rangecheck and throw exception
        reference       operator[](size_type i) {return elem[i];}
        const_reference operator[](size_type i) const {return elem[i];}

// Array specific methods
        template <class U>
        void assign(const U &val)
        {
            for (size_type i=0; i<N; i++)
                elem[i]=val;
        }
        pointer         c_array() {return elem;}
        reference       back()  {return elem[N-1];}
        const_reference back() const {return elem[N-1];}
};

}} /* namespace CDTL, namespace CDL */

#endif//__CDTL_ARRAY_H__
