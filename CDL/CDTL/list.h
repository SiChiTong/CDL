//========================================================================
/** @type     C/C++ Header File
 *  @file     list.h
 *  @author   acornejo
 *  @date
 *   Created:       14:57:55 07/03/2007
 *   Last Update:   12:15:29 09/03/2007
 */
//========================================================================
template <class Data>
class List
{
    private:
        struct NodeBase
        {
            NodeBase *next;
            NodeBase *prev;
        } m_end;
        struct Node: public NodeBase
        {
                Data data;
                Node(Data _data): data(_data) {}
        };
        size_t m_size;

    public:
        typedef Data value_type;
        typedef value_type &reference;
        typedef value_type *pointer;
        typedef int distance_type;
        typedef const value_type &const_reference;
        typedef const value_type *const_pointer;
        typedef size_t size_type;
        template <class T>
        class ListIterator
        {
            private:
                NodeBase *node;

            public:
                typedef T value_type;
                typedef T &reference;
                typedef T *pointer;
                typedef int distance_type;

                ListIterator(NodeBase *_node=NULL): node(_node) {}
                reference operator*() {return ((Node *)node)->data;}
                ListIterator &operator++() {node=node->next; return *this;}
                ListIterator &operator--() {node=node->prev; return *this;}
                ListIterator operator++(int) {ListIterator tmp=*this; node=node->next; return tmp;}
                ListIterator operator--(int) {ListIterator tmp=*this; node=node->prev; return tmp;}
                bool operator==(const ListIterator &r) const {return node == r.node;}
                bool operator!=(const ListIterator &r) const {return node != r.node;}

            friend class List;
        };
        typedef ListIterator<value_type> iterator;
        typedef ListIterator<const value_type> const_iterator;

        List(): m_size(0) {m_end.next=m_end.prev=&m_end;}

        ~List() {clear();}

        iterator insert(iterator pos, const_reference data)
        {
            Node *elem=new Node(data);
            NodeBase *n=pos.node;
            NodeBase *p=n->prev;
            elem->next=n;
            elem->prev=p;
            p->next=elem;
            n->prev=elem;
            m_size++;
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
            m_size--;
            return iterator(next);
        }

        void insert(iterator pos, const_iterator first, const_iterator last)
        {
            for (; first != last; ++first)
                insert(pos,*first);
        }

        iterator erase(iterator first, iterator last)
        {
            for (; first != last; ++first)
                erase(first);
            return last;
        }

        void remove(const_reference data)
        {
            iterator first(begin()), last(end());
            while (first != last)
            {
                iterator next=first;
                ++next;
                if (data == *first) erase(first);
                first=next;
            }
        }

        void remove_first(const_reference data)
        {
            iterator first(begin()), last(end());
            while (first != last)
            {
                iterator next=first;
                ++next;
                if (data == *first)
                {
                    erase(first);
                    break;
                }
                first=next;
            }
        }

        size_type max_size() const {return size_type(-1);}
        size_type size() const {return m_size;}
        bool empty() const {return m_size == 0;}
        iterator begin() {return iterator(m_end.next);}
        iterator end() {return iterator(&m_end);}
        const_iterator begin() const {return iterator(m_end.next);}
        const_iterator end() const {return iterator(&m_end);}
        reference front() {return *begin();}
        reference back()  {return *(--end());}
        const_reference front() const {return *begin();}
        const_reference back()  const {return *(--end());}
        void push_front(const_reference data) {insert(begin(),data);}
        void push_back(const_reference data) {insert(end(),data);}
        void pop_front() {erase(begin());}
        void pop_back() {erase(--end());}
        void clear() {erase(begin(),end());}
        void swap(List<Data> &x) {NodeBase tmp=m_end;m_end=x.m_end;x.m_end=tmp;}
};
