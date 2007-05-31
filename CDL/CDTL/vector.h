//========================================================================
/** @type     C/C++ Header File
 *  @file     vector.h
 *  @author   alex
 *  @date
 *   Created:       20:08:35 29/05/2007
 *   Last Update:   20:58:38 29/05/2007
 */
//========================================================================
#ifndef __CDTL_VECTOR_H__
#define __CDTL_VECTOR_H__

#include <CDL/CDTL/iterator.h>

namespace CDL { namespace CDTL {

template <class T>
class vector_base
{
    protected:
        T *m_start;
        T *m_finish;
        T *m_eos;

    public:
        vector_base(): m_start(0), m_finish(0), m_eos(0) {}
        vector_base(size_t n)
        {
            m_start=new T[n];
            m_finish=m_start;
            m_eos=m_start+n;
        }
        ~vector_base()
        {
            if (m_start)
                delete []m_start;
        }
};

template <class T>
class vector: public vector_base
{
    public:
        typedef T value_type;
        typedef value_type &reference;
        typedef value_type *pointer;
        typedef ptrdiff_t difference_type;
        typedef const value_type &const_reference;
        typedef const value_type *const_pointer;
        typedef size_t size_type;
        typedef const value_type *const_iterator;
        typedef value_type *iterator;
        typedef reverse_iterator<const_iterator> const_reverse_iterator;
        typedef reverse_iterator<iterator> reverse_iterator;
        typedef vector<T> self;

        vector() {}
        vector(size_type n) {insert(begin(),n,value_type());}
        vector(size_type n, const_reference t) {insert(begin(),n,t);}
        template <InputIterator>
        vector(InputIterator first, InputIterator last) {insert(begin(),first,last);}
        vector(const self &x) {insert(begin(),x.begin(),x.end());}
        virtual ~vector() {clear()}

        void resize(size_type n, T x)
        {
            if (n < size())
                erase(begin()+n,end());
            else insert(end(),n-size(),x);
        }

        iterator begin()                       { return m_start; }
        const_iterator begin() const           { return m_start; }
        iterator end()                         { return m_finish; }
        const_iterator end() const             { return m_finish; }
        reverse_iterator rbegin()              { return reverse_iterator(end()); }
        const_reverse_iterator rbegin() const  { return const_reverse_iterator(end()); }
        reverse_iterator rend()                { return reverse_iterator(begin()); }
        const_reverse_iterator rend() const    { return const_reverse_iterator(begin()); }
        size_type size() const                 { return size_type(m_finish-m_start); }
        size_type max_size() const             { return size_type(-1) / sizeof(T); }
        size_type capacity() const             { return size_type(m_eos - m_start); }
        bool empty() const                     { return m_start == m_finish; }
        reference operator[](size_type n)    { return *(begin()+n); }
        const_reference operator[](size_type n) const { return *(begin()+n); }
        reference front()                      { return *begin(); }
        const_reference front() const          { return *begin(); }
        reference back()                       { return *(end() - 1); }
        const_reference back() const           { return *(end() - 1); }
        reference at(size_type n)              { return (*this)[n]; }
        const_reference at(size_type n) const  { return (*this)[n]; }
        void resize(size_type n) {resize(n,T());}
        void clear() {erase(begin(),end());}
        void swap(self &x) {swap(m_start,x.m_start);swap(m_end,x.m_end);swap(m_eos,x.m_eos);}
};

} /* namespace CDTL */ } /* namespace CDL */

#endif//__CDTL_VECTOR_H__
