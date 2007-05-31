//========================================================================
/** @type     C/C++ Header File
 *  @file     list.h
 *  @author   acornejo
 *  @date
 *   Created:       14:57:55 07/03/2007
 *   Last Update:   21:48:58 29/05/2007
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
        struct NodeBase
        {
            NodeBase *next;
            NodeBase *prev;
        } *m_base;

    public:
        list_base() {m_base=new NodeBase;m_base->next=m_base->prev=m_base;}
        virtual ~list_base() {delete m_base;}
};

template <class Data>
class list: public list_base
{
    private:
        struct Node: public NodeBase
        {
                Data data;
                Node(Data _data): data(_data) {}
        };
    public:
        typedef Data value_type;
        typedef value_type &reference;
        typedef value_type *pointer;
        typedef int difference_type;
        typedef const value_type &const_reference;
        typedef const value_type *const_pointer;
        typedef size_t size_type;
        template <class T>
        class list_iterator: public iterator<bidirectional_iterator_tag,T,int>
        {
            private:
                NodeBase *node;

                transfer(list_iterator first, list_iterator last)
                {
                    last.node->prev->next=node;
                    first.node->prev->next=last.node;
                    node->prev->next=first.node;

                    NodeBase *tmp=node->prev;
                    node->prev=last.node->prev;
                    last.node->prev=first.node->prev;
                    first.node->prev=tmp;
                }
            public:
                list_iterator(NodeBase *_node=NULL): node(_node) {}
                reference operator*() {return ((Node *)node)->data;}
                list_iterator &operator++() {node=node->next; return *this;}
                list_iterator &operator--() {node=node->prev; return *this;}
                list_iterator operator++(int) {list_iterator tmp=*this; node=node->next; return tmp;}
                list_iterator operator--(int) {list_iterator tmp=*this; node=node->prev; return tmp;}
                bool operator==(const list_iterator &r) const {return node == r.node;}
                bool operator!=(const list_iterator &r) const {return node != r.node;}

            friend class list;
        };
        typedef list_iterator<const value_type> const_iterator;
        typedef list_iterator<value_type> iterator;
        typedef reverse_iterator<const_iterator> const_reverse_iterator;
        typedef reverse_iterator<iterator> reverse_iterator;
        typedef list<Data> self;

        list() {}
        list(size_type n) {insert(begin(),n,value_type());}
        list(size_type n, const_reference t) {insert(begin(),n,t);}
        template <class InputIterator>
        list(InputIterator first, InputIterator last) {insert(begin(),first,last);}
        list(const self &x) {insert(begin(),x.begin(),x.end());}
        virtual ~list() {clear();}

        iterator insert(iterator pos, const_reference data)
        {
            Node *elem=new Node(data);
            NodeBase *n=pos.node;
            NodeBase *p=n->prev;
            elem->next=n;
            elem->prev=p;
            p->next=elem;
            n->prev=elem;
            return iterator(elem);
        }

        iterator erase(iterator pos)
        {
            Node *n=(Node *)pos.node;
            NodeBase *next=n->next;
            NodeBase *prev=n->prev;
            prev->next=next;
            next->prev=prev;
            delete n;
            return iterator(next);
        }

        template<class InputIterator>
        void insert(iterator pos, InputIterator first, InputIterator last)
        {
            for (; first != last; ++first)
                insert(pos,*first);
        }

        void insert(iterator pos, size_type n, const Data &x)
        {
            for (; n > 0; --n)
                insert(pos,x);
        }

        iterator erase(iterator first, iterator last)
        {
            while (first != last)
                first=erase(first);

            return last;
        }

        void remove(const_reference data)
        {
            iterator first(begin()), last(end());
            while (first != last)
            {
                iterator next(first);
                ++next;
                if (data == *first) erase(first);
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

        void unique() {unique(equal_to<Data>());}
        void merge(self &x) {merge(x,less<Data>());}
        void sort() {sort(less<Data>());}
        size_type max_size() const {return size_type(-1);}
        size_type size() const {return distance(begin(),end());}
        bool empty() const {return m_base->next == m_base;}
        iterator begin() {return iterator(m_base->next);}
        iterator end() {return iterator(m_base);}
        reverse_iterator rbegin() {return reverse_iterator(begin());}
        reverse_iterator rend() {return reverse_iterator(end());}
        const_iterator begin() const {return iterator(m_base->next);}
        const_iterator end() const {return iterator(m_base);}
        const_reverse_iterator rbegin() const {return const_reverse_iterator(begin());}
        const_reverse_iterator rend() const {return const_reverse_iterator(end());}
        reference front() {return *begin();}
        reference back()  {return *(--end());}
        const_reference front() const {return *begin();}
        const_reference back()  const {return *(--end());}
        void push_front(const_reference data) {insert(begin(),data);}
        void push_back(const_reference data) {insert(end(),data);}
        void pop_front() {erase(begin());}
        void pop_back() {erase(--end());}
        void clear() {erase(begin(),end());}
        void swap(self &x) {NodeBase *tmp=m_base;m_base=x.m_base;x.m_base=tmp;}
};

} /* namespace CDTL */ } /* namespace CDL */
#endif//__CDTL_LIST_H__
