//========================================================================
/** @type     C/C++ Header File
 *  @file     string.h
 *  @author   alex
 *  @date
 *   Created:       23:03:52 29/05/2007
 *   Last Update:   02:56:37 31/05/2007
 */
//========================================================================
#ifndef __CDL_STRING_H__
#define __CDL_STRING_H__

class string_base
{
    protected:
        char *m_start;
        char *m_finish;
        char *m_eos;

        void terminate_string()
        {
            if (m_finish)
                *m_finish=0;
        }

        void allocate(size_t n)
        {
            m_start=new char[n];
            m_finish=m_start;
            m_eos=m_start+n;
        }

        void deallocate()
        {
            if (m_start)
                delete []m_start;
            m_start=m_finish=m_eos=0;
        }

        void fill_n(size_t n, const char c)
        {
            memset(m_start,c,n);
        }

        void copy_n(size_t n, const char *str)
        {
            memcpy(m_start,str,n);
        }

        void copyto_n(size_t n, char *str)
        {
            memcpy(str,m_start,n);
        }

        size_t length(const char *s) const
        {
            size_t i=0;
            while (s[i] != '\0') ++i;
            return i;
        }

    public:
        string_base(): m_start(0), m_finish(0), m_eos(0) {}
        string_base(size_t n) {allocate(n);}
        ~string_base() {deallocate();}
};

class string: public string_base
{
    public:
        typedef char value_type;
        typedef value_type *pointer;
        typedef const value_type *const_pointer;
        typedef value_type &reference;
        typedef const value_type &const_reference;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;
        typedef const value_type *const_iterator;
        typedef value_type *iterator;
        typedef string self;
        enum {npos=-1};

        string(): string_base(8) {terminate_string();}
        string(const self &x, size_type pos=0, size_type n=npos) {}
        string(const_pointer *s) {allocate(length(s)+1);copy_n(size(),s);}
        string(const_pointer *s, size_type n): string_base(n+1) {copy_n(n,s);terminate_string();}
        string(size_type n, value_type c): string_base(n+1) {fill_n(c);terminate_string();}

        void reserve(size_type n=0)
        {
            if (n > capacity())
            {
                size_type len=n+1;
                value_type *new_start=new value_type[len];
                value_type *new_finish=new_start+len;
                copyto_n(len,new_start);
                deallocate();
                m_start=new_start;
                m_finish=m_start+len;
                m_eos=m_start+len;
            }
        }

        void resize(size_type n, value_type c)
        {
            if (n < size())
                erase(begin()+n,end());
            else
                append(n-size(),c);
        }

        const value_type *c_str() const        { return m_start; }
        const value_type *data() const         { return m_start; }
        const_iterator begin() const           { return m_start; }
        const_iterator end() const             { return m_finish; }
        const_reverse_iterator rbegin() const  { return const_reverse_iterator(m_finish); }
        const_reverse_iterator rend() const    { return const_reverse_iterator(m_start); }
        iterator begin()                       { return m_start; }
        iterator end()                         { return m_finish; }
        reverse_iterator rbegin()              { return reverse_iterator(m_finish); }
        reverse_iterator rend()                { return reverse_iterator(m_start); }
        size_type size() const                 { return size_type(m_finish-m_start); }
        size_type max_size() const             { return size_type(-1) / sizeof(T); }
        size_type capacity() const             { return size_type(m_eos - m_start-1); }
        bool empty() const                     { return m_start == m_finish; }
        reference operator[](size_type n)    { return *(m_start+n); }
        const_reference operator[](size_type n) const { return *(m_start+n); }
        reference at(size_type n)              { return *(m_start+n); }
        const_reference at(size_type n) const  { return *(m_start+n); }
        void resize(size_type n) {resize(n,'\0');}
        void clear() {m_finish=m_start;terminate_string()}
        void swap(self &x) {swap(m_start,x.m_start);swap(m_end,x.m_end);swap(m_eos,x.m_eos);}
        size_type length() const {return m_finish-mstart;}
};

#endif//__CDL_STRING_H__
