//========================================================================
/** @type     C/C++ Header File
 *  @file     iterator.h
 *  @author   alex
 *  @date
 *   Created:       11:11:01 29/05/2007
 *   Last Update:   15:34:02 20/01/2008
 */
//========================================================================
#ifndef __CDTL_ITERATOR_H__
#define __CDTL_ITERATOR_H__

#include <cstddef>

namespace CDL { namespace CDTL {

// Iterator tags
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

// Iterator traits
template <class Iterator>
struct iterator_traits
{
    typedef typename Iterator::iterator_category iterator_category;
    typedef typename Iterator::value_type value_type;
    typedef typename Iterator::difference_type difference_type;
    typedef typename Iterator::pointer pointer;
};

template <typename T>
struct iterator_traits<T *>
{
    typedef random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef T *pointer;
    typedef T &reference;
};

// Iterator base class
template <class iterator_category_t, class value_type_t,\
          class difference_type_t=ptrdiff_t, class pointer_t=value_type_t*, class reference_t=value_type_t&>
struct iterator_base
{
    typedef iterator_category_t iterator_category;
    typedef value_type_t value_type;
    typedef difference_type_t difference_type;
    typedef pointer_t pointer;
    typedef reference_t reference;
};

// Iterator distance
template <class Iterator>
typename iterator_traits<Iterator>::difference_type distance(const Iterator &first, const Iterator &last, forward_iterator_tag tag)
{
    typename iterator_traits<Iterator>::difference_type n=0;
    Iterator it(first);
    while (it != last)
    {
        ++it;
        ++n;
    }
    return n;
}

template <class Iterator>
typename iterator_traits<Iterator>::difference_type distance(const Iterator &first, const Iterator &last, random_access_iterator_tag tag)
{
    return last-first;
}

template <class Iterator>
typename iterator_traits<Iterator>::difference_type distance(const Iterator &first, const Iterator &last)
{
    typedef typename iterator_traits<Iterator>::iterator_category category;
    return distance(first,last,category());
}

// Iterator advance
template <class Iterator>
inline void advance(Iterator &i, typename iterator_traits<Iterator>::difference_type n, forward_iterator_tag tag)
{
    while (n-- >= 0) ++i;
}

template <class Iterator>
inline void advance(Iterator &i, typename iterator_traits<Iterator>::difference_type n, bidirectional_iterator_tag tag)
{
    if (n > 0)
        while (n--) ++i;
    else
        while (n++) --i;
}

template <class Iterator>
inline void advance(Iterator &i, typename iterator_traits<Iterator>::difference_type n, random_access_iterator_tag tag)
{
    i+=n;
}

template <class Iterator>
inline void advance(Iterator &i, typename iterator_traits<Iterator>::difference_type n)
{
    typedef typename iterator_traits<Iterator>::iterator_category category;
    advance(i,n,category());
}

// Reverse iterator
template <class Iterator>
class reverse_iterator: public iterator_base<typename Iterator::category_type,
                                             typename Iterator::value_type,
                                             typename Iterator::difference_type,
                                             typename Iterator::pointer,
                                             typename Iterator::reference>
{
    protected:
        Iterator current;

    public:
        typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
        typedef typename iterator_traits<Iterator>::value_type value_type;
        typedef typename iterator_traits<Iterator>::difference_type difference_type;
        typedef typename iterator_traits<Iterator>::pointer pointer;
        typedef typename iterator_traits<Iterator>::reference reference;
        typedef Iterator iterator_type;
        typedef reverse_iterator<iterator_type> self;

        reverse_iterator() {}
        reverse_iterator(iterator_type x): current(x) {}
        iterator_type base() const {return current;}
        reference operator*() {iterator_type tmp(current); return *--tmp;}
        self &operator++() {--current;return *this;}
        self &operator--() {++current;return *this;}
        self operator++(int) {self tmp(*this); --current; return tmp;}
        self operator--(int) {self tmp(*this); ++current; return tmp;}

        // random access iterator
        self operator+(difference_type n) const {return self(current-n);}
        self operator-(difference_type n) const {return self(current+n);}
        self &operator+=(difference_type n) {current-=n; return *this;}
        self &operator-=(difference_type n) {current+=n; return *this;}
        reference operator[](difference_type n) const {return *(*this+n);}
};

template <class Iterator>
inline bool operator==(const reverse_iterator<Iterator> &x, const reverse_iterator<Iterator> &y)
{
    return x.base() == y.base();
}

template <class Iterator>
inline bool operator-(const reverse_iterator<Iterator> &x, const reverse_iterator<Iterator> &y)
{
    return y.base() - x.base();
}

template <class Iterator>
inline bool operator<(const reverse_iterator<Iterator> &x, const reverse_iterator<Iterator> &y)
{
    return y.base() < x.base();
}

// Back insert iterator
template <class Container>
class back_insert_iterator: public iterator_base<output_iterator_tag, void, void, void, void>
{
    protected:
        Container *container;

    public:
        typedef Container container_type;
        typedef back_insert_iterator<container_type> self;

        explicit back_insert_iterator(container_type &x) : container(&x) {}

        self &operator=(const self &x) { container=x.container; return *this; }
        self &operator=(const typename container_type::value_type &val) { container->push_back(val); return *this; }

        self &operator*()     { return *this; }
        self &operator++()    { return *this; }
        self  operator++(int) { return *this; }
};

template <class Container>
inline back_insert_iterator<Container>  back_inserter(Container &x) { return back_insert_iterator<Container>(x); }

// Forward insert iterator
template <class Container>
class front_insert_iterator: public iterator_base<output_iterator_tag, void, void, void, void>
{
    protected:
        Container *container;

    public:
        typedef Container container_type;
        typedef front_insert_iterator<container_type> self;

        explicit front_insert_iterator(container_type &x) : container(&x) {}

        self &operator=(const self &x) { container=x.container; return *this; }
        self &operator=(const typename container_type::value_type &val) { container->push_front(val); return *this; }

        self &operator*()     { return *this; }
        self &operator++()    { return *this; }
        self  operator++(int) { return *this; }
};

template <class Container>
inline front_insert_iterator<Container>  front_inserter(Container &x) { return front_insert_iterator<Container>(x); }

// Insert iterator
template <class Container>
class insert_iterator: public iterator_base<output_iterator_tag, void, void, void, void>
{
    private:
        typename Container::iterator *iter;
    protected:
        Container *container;

    public:
        typedef Container container_type;
        typedef insert_iterator<container_type> self;

        explicit insert_iterator(container_type &x, typename Container::iterator i) : container(&x), iter(i) {}

        self &operator=(const self &x) { container=x.container; iter=x.iter; return *this; }
        self &operator=(const typename container_type::value_type &val) { iter=container->insert(iter,val); ++iter; return *this; }

        self &operator*()     { return *this; }
        self &operator++()    { return *this; }
        self  operator++(int) { return *this; }
};

template <class Container, class Iterator>
inline insert_iterator<Container>  inserter(Container &x, Iterator i) { typedef typename Container::iterator iterator; return insert_iterator<Container>(x,iterator(i)); }

} /* namespace CDTL */ } /* namespace CDL */
#endif//__CDTL_ITERATOR_H__
