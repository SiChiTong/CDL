//========================================================================
/** @type     C/C++ Header File
 *  @file     insertion_sort.h
 *  @author   acornejo
 *  @date
 *   Created:       00:31:54 28/09/2006
 *   Last Update:   16:36:55 29/05/2007
 */
//========================================================================
#ifndef __INSERTION_SORT_H__
#define __INSERTION_SORT_H__

namespace CDL { namespace CDTL {

template <class RandomIterator, class Comparator, class Object>
void insertion_sort_core( const RandomIterator &begin,
                    const RandomIterator &end,
                    Comparator lessThan,
                    const Object &obj)
{
    RandomIterator j;

    for( RandomIterator p = begin+1; p != end; ++p )
    {
        Object tmp = *p;
        for( j = p; j != begin && lessThan( tmp, *( j-1 ) ); --j )
            *j = *(j-1);
        *j = tmp;
    }
}

template <class RandomIterator, class Comparator>
void insertion_sort( const RandomIterator & begin,
                    const RandomIterator & end,
                    Comparator lessThan )
{
    if( begin != end )
        insertion_sort_core( begin, end, lessThan, *begin );
}

template <class RandomIterator, class Object>
void insertion_sort_helper( const RandomIterator & begin,
                        const RandomIterator & end,
                        const Object & obj )
{
    insertion_sort( begin, end, less<Object>() );
}

template <class RandomIterator>
void insertion_sort( const RandomIterator & begin,
                    const RandomIterator & end )
{
    if( begin != end )
        insertion_sort_helper( begin, end, *begin );
}

} /* namespace CDTL */ } /* namespace CDL */
#endif//__INSERTION_SORT_H__
