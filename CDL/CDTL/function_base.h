//========================================================================
/** @type     C/C++ Header File
 *  @file     function_base.h
 *  @author   alex
 *  @date
 *   Created:       12:12:53 29/05/2007
 *   Last Update:   18:28:49 29/05/2007
 */
//========================================================================
#ifndef __CDTL_FUNCTION_BASE_H__
#define __CDTL_FUNCTION_BASE_H__

namespace CDL { namespace CDTL {

template <class Arg, class Result>
struct unary_function
{
    typedef Arg argument_type;
    typedef Result result_type;
};

template <class Arg1, class Arg2, class Result>
struct binary_function
{
    typedef Arg1 first_argument_type;
    typedef Arg2 second_argument_type;
    typedef Result result_type;
};

template <class T>
struct equal_to: public binary_function<T,T,bool>
{
    bool operator() (const T &x, const T &y) const {return x == y;}
};

template <class T>
struct not_equal_to: public binary_function<T,T,bool>
{
    bool operator() (const T &x, const T &y) const {return x != y;}
};

template <class T>
struct greater: public binary_function<T,T,bool>
{
    bool operator() (const T &x, const T &y) const {return x > y;}
};

template <class T>
struct less: public binary_function<T,T,bool>
{
    bool operator() (const T &x, const T &y) const {return x < y;}
};

template <class T>
struct greater_equal: public binary_function<T,T,bool>
{
    bool operator() (const T &x, const T &y) const {return x >= y;}
};

template <class t>
struct less_equal: public binary_function<t,t,bool>
{
    bool operator() (const t &x, const t &y) const {return x <= y;}
};

template <class T>
struct plus: public binary_function<T,T,T>
{
    bool operator() (const T &x, const T &y) const {return x+y;}
};

template <class T>
struct minus: public binary_function<T,T,T>
{
    bool operator() (const T &x, const T &y) const {return x-y;}
};

template <class T>
struct multiplies: public binary_function<T,T,T>
{
    bool operator() (const T &x, const T &y) const {return x*y;}
};

template <class T>
struct divides: public binary_function<T,T,T>
{
    bool operator() (const T &x, const T &y) const {return x/y;}
};

template <class T>
struct modulus: public binary_function<T,T,T>
{
    bool operator() (const T &x, const T &y) const {return x%y;}
};

template <class T>
struct negate: public unary_function<T,T>
{
    T operator()(const T &x) {return -x;}
};

template <class T>
struct logical_and: public binary_function<T,T,bool>
{
    bool operator()(const T &x, const T &y) const {return x && y;}
};

template <class T>
struct logical_or: public binary_function<T,T,bool>
{
    bool operator()(const T &x, const T &y) const {return x || y;}
};

template <class T>
struct logical_not: public unary_function<T,bool>
{
    bool operator()(const T &x) const {return !x;}
};

template <class T>
inline void swap(T &a, T &b)
{
    T tmp=a;
    a=b;
    b=tmp;
}

template <class T>
inline const T &min(const T &a, const T &b) {return b < a ? b : a;}

template <class T>
inline const T &max(const T &a, const T &b) {return a < b ? b : a;}

} /* namespace CDTL */ } /* namespace CDL */
#endif//__FUNCTION_BASE_H__
