//========================================================================
/** @type     C++ Source File
 *  @file     cdtl.cpp
 *  @author   acornejo
 *  @date
 *   Created:       01:12:44 19/01/2008
 *   Last Update:   01:46:51 19/01/2008
 */
//========================================================================
#include <CDL/CDTL/list.h>
#include <CDL/CDTL/vector.h>
#include <CDL/CDTL/array.h>
#include <stdio.h>

using namespace CDL::CDTL;

int main()
{
    list<int> ilist;
    array<int,7> iarray;
    ilist.push_back(1);
    ilist.push_back(2);
    ilist.push_back(3);
    ilist.push_back(5);
    ilist.push_back(7);
    ilist.push_back(11);
    ilist.push_back(13);

    list<int>::iterator first(ilist.begin()), last(ilist.end());
    int j=0;
    while (first != last)
    {
        iarray[j++]=*first;
        printf("%d\n", *first);fflush(stdout);
        ++first;
    }
        
    for (int i=0; i<iarray.size(); i++)
        printf("array[%d]=%d\n", i,iarray[i]);

    return 0;
}
