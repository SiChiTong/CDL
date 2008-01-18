//========================================================================
/** @type     C/C++ Header File
 *  @file     iterator.h
 *  @author   alex
 *  @date
 *   Created:       11:11:01 29/05/2007
 *   Last Update:   16:48:48 29/05/2007
 */
//========================================================================
#ifndef __CDTL_ITERATOR_H__
#define __CDTL_ITERATOR_H__

#include <cstddef>

namespace CDL { namespace CDTL {

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

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
        typedef reverse_iterator<Iterator> self;

        reverse_iterator() {}
        reverse_iterator(Iterator x): current(x) {}
        Iterator base() const {return current;}
        reference operator*() {Iterator tmp(current); return *--tmp;}
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

} /* namespace CDTL */ } /* namespace CDL */
#endif//__CDTL_ITERATOR_H__
