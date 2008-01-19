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
        typedef vector<T> self;

// Container types
        typedef T value_type;
        typedef value_type &reference;
        typedef value_type *pointer;
        typedef ptrdiff_t difference_type;
        typedef const value_type &const_reference;
        typedef const value_type *const_pointer;
        typedef size_t size_type;
        typedef const value_type *const_iterator;
        typedef value_type *iterator;

// Reversible container types
        typedef reverse_iterator<const_iterator> const_reverse_iterator;
        typedef reverse_iterator<iterator> reverse_iterator;

// Container methods
        vector() {}
        vector(const self &x): vector_base(x.size()) { insert(begin(),x.begin(),x.end()); }
        iterator       begin()          { return m_start; }
        const_iterator begin() const    { return m_start; }
        iterator       end()            { return m_finish; }
        const_iterator end() const      { return m_finish; }
        size_type      max_size() const { return size_type(-1) / sizeof(T); }
        size_type      size()     const { return size_type(m_finish-m_start); }
        bool           empty()    const { return m_start == m_finish; }
        void swap(self &x)              { swap(m_start,x.m_start);swap(m_end,x.m_end);swap(m_eos,x.m_eos); }
        reference front()               { return *begin(); }
        const_reference front() const   { return *begin(); }        

// Reversible container method
        reverse_iterator rbegin()             { return reverse_iterator(end()); }
        const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
        reverse_iterator rend()               { return reverse_iterator(begin()); }
        const_reverse_iterator rend() const   { return const_reverse_iterator(begin()); }

// Sequence methods
        vector(size_type n): vector_base(n) {insert(begin(),n,value_type());}
        vector(size_type n, const_reference x): vector_base(n) {insert(begin(),n,x);}
        template <InputIterator>
        vector(InputIterator first, InputIterator last) {insert(begin(),first,last);}
        virtual ~vector() {clear();}
        void clear() {erase(begin(),end());}

        void resize(size_type n, const_reference x)
        {
            if (n < size())
                erase(begin()+n,end());
            else insert(end(),n-size(),x);
        }

        void resize(size_type n) {resize(n,value_type());}
        
        /* FIXME: missing insert and erase */

// Vector methods
        size_type capacity() const             { return size_type(m_eos - m_start); }
        void reserve(size_type n)
        {
            if (capacity() < n)
            {
                const size_type osize=size();
                if (m_start)
                {
                    pointer tmp=new value_type[n];
                    start=tmp;
                    m_finish=tmp+osize;
                    m_eos=tmp+n;
                    while (start < m_finish)
                    {
                        *start=*m_start;
                        m_start++;
                        start++;
                    }
                    m_start=tmp;
                }
                else
                {
                    m_start=new value_type[n];
                    m_finish=m_start;
                    m_eos=m_start+n;
                }
            }
        }

// Random access container
        reference operator[](size_type n)    { return *(begin()+n); }
        const_reference operator[](size_type n) const { return *(begin()+n); }
        reference at(size_type n)              { return (*this)[n]; }
        const_reference at(size_type n) const  { return (*this)[n]; }

// Back insertion sequence methods
        reference back()  {return *(--end());}
        const_reference back()  const {return *(--end());}
        void push_back(const_reference x) {insert(end(),x);}
        void pop_back() {erase(--end());}
};

} /* namespace CDTL */ } /* namespace CDL */

#endif//__CDTL_VECTOR_H__
