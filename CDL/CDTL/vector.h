//========================================================================
/** @type     C/C++ Header File
 *  @file     vector.h
 *  @author   alex
 *  @date
 *   Created:       20:08:35 29/05/2007
 *   Last Update:   15:25:09 20/01/2008
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
        typedef vector_base<T> self;
    
        vector_base(): m_start(0), m_finish(0), m_eos(0) {}
        vector_base(size_t n): m_start(0)
        {
            realloc(n);
        }
        ~vector_base()
        {
            if (m_start)
                delete []m_start;
        }
        void realloc(size_t n)
        {
            if (m_start)
            {
                size_t osize=m_finish-m_start;
                T *start=new T[n];
                T *ostart=m_start;
                m_start=start;
                m_finish=start+osize;
                m_eos=start+n;
                while (start < m_finish)
                {
                    *start=*ostart;
                    ostart++;
                    start++;
                }
            }
            else
            {
                m_start=new T[n];
                m_finish=m_start;
                m_eos=m_start+n;
            }
        }
        void swap(self &x)
        {
            swap(m_start,x.m_start);
            swap(m_finish,x.m_finish);
            swap(m_eos,x.m_eos);        
        }
};

template <class T>
class vector: public vector_base<T>
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
        vector(const self &x): vector_base<T>(x.size()) { insert(begin(),x.begin(),x.end()); }
        iterator        begin()          { return vector_base<T>::m_start; }
        const_iterator  begin() const    { return vector_base<T>::m_start; }
        iterator        end()            { return vector_base<T>::m_finish; }
        const_iterator  end() const      { return vector_base<T>::m_finish; }
        size_type       max_size() const { return size_type(-1) / sizeof(T); }
        size_type       size() const     { return size_type(vector_base<T>::m_finish-vector_base<T>::m_start); }
        bool            empty() const    { return vector_base<T>::m_start == vector_base<T>::m_finish; }
        void            swap(self &x)    { vector_base<T>::swap(x); }
        reference       front()          { return *begin(); }
        const_reference front() const    { return *begin(); }

// Reversible container method
        reverse_iterator       rbegin()       { return reverse_iterator(end()); }
        const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
        reverse_iterator       rend()         { return reverse_iterator(begin()); }
        const_reverse_iterator rend() const   { return const_reverse_iterator(begin()); }

// Sequence methods
        vector(size_type n): vector_base<T>(n) { vector_base<T>::m_finish=vector_base<T>::m_start+n; }
        vector(size_type n, const_reference x): vector_base<T>(n) {insert(begin(),n,x);}
        template <class InputIterator>
        vector(InputIterator first, InputIterator last) {insert(begin(),first,last);}
        virtual ~vector() { clear(); }
        void clear() { erase(begin(),end()); }

        void resize(size_type n, const_reference x)
        {
            if (n < size())
                erase(begin()+n,end());
            else insert(end(),n-size(),x);
        }

        void resize(size_type n) { resize(n,value_type()); }

        iterator insert(iterator pos, const_reference x)
        {
            insert(pos,1,x);
        }

        template<class InputIterator>
        void insert(iterator pos, InputIterator first, InputIterator last)
        {
            // check if input iterator or forward iterator
            // if input insert one by one calling insert(pos,x)
            // if forward insert a range
            for (; first != last; ++first)
                insert(pos,*first);
        }

        void insert(iterator pos, size_type n, const_reference x)
        {
            if (vector_base<T>::m_finish+n > vector_base<T>::m_eos) // overflow
            {
            
            }
            else
            {
                iterator src_end(end());
                iterator dst_end(pos+n);
            }
        }

        iterator erase(iterator pos)
        {
            iterator prev(pos);
            iterator next(prev+1);
            iterator last(end());
            while (next != last)
            {
                *prev=*next;
                prev=next;
                ++next;
            }
            vector_base<T>::m_finish--;
            vector_base<T>::m_finish->~T(); //destroy
                
            return pos;
        }

        iterator erase(iterator first, iterator last)
        {
            iterator src(last);
            iterator dst(first);
            for (; dst != last; ++src, ++dst)
                *dst=*src;
            iterator start(src); // destroy range
            while (start != vector_base<T>::m_finish)
            {
                start->~T();
                ++start;
            }
            vector_base<T>::m_finish=src;
            return first;
        }
        
        /* FIXME: missing insert and erase */

// Vector methods
        size_type capacity() const { return size_type(vector_base<T>::m_eos - vector_base<T>::m_start); }
        void reserve(size_type n)
        {
            if (capacity() < n)
                vector_base<T>::realloc(n);
        }

// Random access container
        reference       operator[](size_type n)       { return *(begin()+n); }
        const_reference operator[](size_type n) const { return *(begin()+n); }
        reference       at(size_type n)               { return *(begin()+n); }
        const_reference at(size_type n) const         { return *(begin()+n) }

// Back insertion sequence methods
        reference       back()                       { return *(--end()); }
        const_reference back() const                 { return *(--end()); }
        void            push_back(const_reference x) { insert(end(),x); }
        void            pop_back()                   { erase(--end()); }
};

} /* namespace CDTL */ } /* namespace CDL */

#endif//__CDTL_VECTOR_H__
