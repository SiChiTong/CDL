//========================================================================
/** @type     C/C++ Header File
 *  @file     list.h
 *  @author   acornejo
 *  @date
 *   Created:       14:57:55 07/03/2007
 *   Last Update:   13:34:40 18/01/2008
 */
//========================================================================
#ifndef __CDTL_LIST_H__
#define __CDTL_LIST_H__

#include <CDL/CDTL/iterator.h>
#include <CDL/CDTL/function_base.h>

namespace CDL { namespace CDTL {

class list_base
{
    protected:
        struct node_base
        {
            node_base *next;
            node_base *prev;
        } *m_base;

    public:
        list_base() {m_base=new node_base;m_base->next=m_base->prev=m_base;}
        virtual ~list_base() {delete m_base;}
};

template <class T>
class list: public list_base
{
    private:
        struct node: public node_base
        {
                T data;
                node(Data _data): data(_data) {}
        } *m_base;

    public:
        template <class U>
        class list_iterator: public iterator_base<bidirectional_iterator_tag,U,int>
        {
            private:
                node_base *ptr;

                transfer(list_iterator first, list_iterator last)
                {
                    last.ptr->prev->next=ptr;
                    first.ptr->prev->next=last.ptr;
                    ptr->prev->next=first.ptr;

                    node_base *tmp=ptr->prev;
                    ptr->prev=last.ptr->prev;
                    last.ptr->prev=first.ptr->prev;
                    first.ptr->prev=tmp;
                }
            public:
                list_iterator(node_base *_ptr=NULL): ptr(_ptr) {}
                reference operator*() {return ((node *)ptr)->data;}
                list_iterator &operator++() {ptr=ptr->next; return *this;}
                list_iterator &operator--() {ptr=ptr->prev; return *this;}
                list_iterator operator++(int) {list_iterator tmp=*this; ptr=ptr->next; return tmp;}
                list_iterator operator--(int) {list_iterator tmp=*this; ptr=ptr->prev; return tmp;}
                bool operator==(const list_iterator &r) const {return ptr == r.ptr;}
                bool operator!=(const list_iterator &r) const {return ptr != r.ptr;}

            friend class list;
        };
        typedef list<T> self;

// Container types
        typedef T value_type;
        typedef value_type &reference;
        typedef value_type *pointer;
        typedef int difference_type;
        typedef const value_type &const_reference;
        typedef const value_type *const_pointer;
        typedef size_t size_type;
        typedef list_iterator<const value_type> const_iterator;
        typedef list_iterator<value_type> iterator;

// Reversible container types
        typedef reverse_iterator<const_iterator> const_reverse_iterator;
        typedef reverse_iterator<iterator> reverse_iterator;

// Container methods
        list() {}
        list(const self &x) {insert(begin(),x.begin(),x.end());}
        iterator begin() {return iterator(m_base->next);}
        iterator end() {return iterator(m_base);}
        const_iterator begin() const {return iterator(m_base->next);}
        const_iterator end() const {return iterator(m_base);}
        size_type max_size() const {return size_type(-1);}
        size_type size() const {return distance(begin(),end());}
        bool empty() const {return m_base->next == m_base;}
        void swap(self &x) {node_base *tmp=m_base;m_base=x.m_base;x.m_base=tmp;}

// Reversible container methods
        reverse_iterator rbegin() {return reverse_iterator(begin());}
        reverse_iterator rend() {return reverse_iterator(end());}
        const_reverse_iterator rbegin() const {return const_reverse_iterator(begin());}
        const_reverse_iterator rend() const {return const_reverse_iterator(end());}

// Sequence methods
        list(size_type n) {insert(begin(),n,value_type());}
        list(size_type n, const_reference t) {insert(begin(),n,t);}
        template <class InputIterator>
        list(InputIterator first, InputIterator last) {insert(begin(),first,last);}
        virtual ~list() {clear();}
        void clear() {erase(begin(),end());}

        iterator insert(iterator pos, const_reference x)
        {
            node *elem=new node(x);
            node_base *n=pos.ptr;
            node_base *p=n->prev;
            elem->next=n;
            elem->prev=p;
            p->next=elem;
            n->prev=elem;
            return iterator(elem);
        }

        template<class InputIterator>
        void insert(iterator pos, InputIterator first, InputIterator last)
        {
            for (; first != last; ++first)
                insert(pos,*first);
        }

        void insert(iterator pos, size_type n, const_reference&x)
        {
            for (; n > 0; --n)
                insert(pos,x);
        }

        iterator erase(iterator pos)
        {
            node *n=(node *)pos.ptr;
            node_base *next=n->next;
            node_base *prev=n->prev;
            prev->next=next;
            next->prev=prev;
            delete n;
            return iterator(next);
        }

        iterator erase(iterator first, iterator last)
        {
            while (first != last)
                first=erase(first);
            return last;
        }

        void resize(size_type new_size, const_reference x)
        {
            iterator i = begin();
            size_type len = 0;
            for ( ; i != end() && len < new_size; ++i, ++len);

            if (len == new_size)
                erase(i, end());
            else
              insert(end(), new_size - len, x);
        }
        
        void resize(size_type new_size)
        {
            resize(new_size,value_type());
        }

// Front insertion sequence methods
        reference front() {return *begin();}
        const_reference front() const {return *begin();}
        void push_front(const_reference x) {insert(begin(),x);}
        void pop_front() {erase(begin());}

// Back insertion sequence methods
        reference back()  {return *(--end());}
        const_reference back()  const {return *(--end());}
        void push_back(const_reference x) {insert(end(),x);}
        void pop_back() {erase(--end());}


// Linked list specific methods
        void remove(const_reference x)
        {
            iterator first(begin()), last(end());
            while (first != last)
            {
                iterator next(first);
                ++next;
                if (x == *first) erase(first);
                first=next;
            }
        }

        template <class Predicate>
        void remove_if(Predicate pred)
        {
            iterator first(begin()), last(end());
            while (first != last)
            {
                iterator next(first);
                ++next;
                if (pred(*first)) erase(first);
                first=next;
            }
        }

        template <class Compare>
        void unique(Compare comp)
        {
            iterator first(begin()), last(end());
            if (first == last) return;
            iterator next(first);
            while (++next != last)
            {
                if (comp(*first,*next))
                    erase(next);
                else
                    first=next;
                next=first;
            }
        }

        void reverse()
        {
            iterator first(begin()), last(end());
            if (!empty() && ++first != last)
            while (first != last)
            {
                iterator old(first++);
                begin().transfer(old,first);
            }
        }

        template <class Compare>
        void merge(self &x, Compare comp)
        {
            if (&x == this) return;

            iterator first1(begin()), last1(end()), first2(x.begin()), last2(x.end());
            while (first1 != last1 && first2 != last2)
                if (comp(*first2,*first1))
                {
                    iterator next(first2);
                    first1.transfer(first2,++next);
                    first2=next;
                }
                else
                    ++first1;
            if (first2 != last2)
                last1.transfer(first2,last2);
        }

        void splice(iterator pos, self &x)
        {
            if (!x.empty())
                pos.transfer(x.begin(),x.end());
        }

        void splice(iterator pos, self &x, iterator i)
        {
            iterator j(i);
            if (pos == i || pos == ++j) return;
            pos.transfer(i,j);
        }

        void splice(iterator pos, self &x, iterator first, iterator last)
        {
            if (first != last)
                pos.transfer(first,last);
        }

        template <class Compare>
        void sort(Compare comp)
        {
            if (!empty() && ++begin() != end())
            {
                self carry;
                self tmp[64];
                list *fill=&tmp[0];
                list *counter;
                while (!empty())
                {
                    carry.splice(carry.begin(),*this,begin());
                    for (counter=&tmp[0]; counter != fill && !counter->empty(); ++counter)
                    {
                        counter->merge(carry,comp);
                        carry.swap(*counter);
                    }
                    carry.swap(*counter);
                    if (counter == fill) ++fill;
                }

                for (counter=&tmp[1]; counter != fill; ++counter)
                    counter->merge(*(counter-1),comp);
                swap(*(fill-1));
            }
        }

        void unique() {unique(equal_to<value_type>());}
        void merge(self &x) {merge(x,less<value_type>());}
        void sort() {sort(less<value_type>());}
};

} /* namespace CDTL */ } /* namespace CDL */
#endif//__CDTL_LIST_H__
