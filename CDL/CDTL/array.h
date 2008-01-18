#ifndef __CDTL_ARRAY_H__
#define __CDTL_ARRAY_H__

#include <CDL/CDTL/iterator.h>
#include <CDL/CDTL/function_base.h>
#define rangecheck(i) {}

namespace CDL { namespace CDTL {

template <class T, size_t N>
class array
{
    public: // misses iterator
        typedef T value_type;
        typedef value_type &reference;
        typedef value_type *pointer;
        typedef int difference_type;
        typedef const value_type &const_reference;
        typedef const value_type *const_pointer;
        typedef size_t size_type;
        typedef array<T,N> self;

        template <class U>
        class array_iterator: public iterator<random_access_iterator_tag,T,int>
        {
            private:
                U *ptr;
            public:
                typedef array_iterator<U> self;

                array_iterator(U *_ptr): ptr(_ptr) {}
                reference operator*() {return *ptr;}
                self &operator++() {ptr++; return *this;}
                self &operator--() {ptr--; return *this;}
                self operator++(int) {self tmp=*this; ptr++; return tmp;}
                self operator--(int) {self tmp=*this; ptr--; return tmp;}
                bool operator==(const self &r) const {return ptr == r.ptr;}
                bool operator!=(const self &r) const {return ptr != r.ptr;}

                // random access iterator
                self operator+(difference_type n) const {return self(ptr+n);}
                self operator-(difference_type n) const {return self(ptr-n);}
                self &operator+=(difference_type n) {ptr+=n; return *this;}
                self &operator-=(difference_type n) {ptr-=n; return *this;}
                reference operator[](difference_type n) const {return *(*this+n);}

            friend class array;
        };
        typedef array_iterator<const value_type> const_iterator;
        typedef array_iterator<value_type> iterator;
        typedef reverse_iterator<const_iterator> const_reverse_iterator;
        typedef reverse_iterator<iterator> reverse_iterator;

    private:
        T elem[N];

    public:
// constructors
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

// modifiers
        template <class U>
        void assign(const U &val)
        {
            for (size_type i=0; i<N; i++)
                elem[i]=val;
        }

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

// forward iterator support
        iterator       begin() {return elem;}
        const_iterator begin() const {return elem;}
        iterator       end()   {return elem+N;}
        const_iterator end() const {return elem+N;}

// reverse iterator support
        reverse_iterator       rbegin() {return reverse_iterator(end());}
        const_reverse_iterator rbegin() const {return const_reverse_iterator(end());}
        reverse_iterator       rend()   {return reverse_iterator(begin());}
        const_reverse_iterator rend() const {return const_reverse_iterator(begin());}

// element access
        reference       at(size_type i) { rangecheck(i); return elems[i]; }
        const_reference at(size_type i) const { rangecheck(i); return elems[i]; }
        reference       operator[](size_type i) {return elem[i];}
        const_reference operator[](size_type i) const {return elem[i];}
        reference       front() {return elem[0];}
        const_reference front() const {return elem[0];}
        reference       back()  {return elem[N-1];}
        const_reference back() const {return elem[N-1];}
        pointer         c_array() {return elem;}

// capacity
        size_type       max_size() const {return N;}
        size_type       size() const {return N;}
        bool            empty() const {return N == 0;}
};

}} /* namespace CDTL, namespace CDL */

#endif//__CDTL_ARRAY_H__
