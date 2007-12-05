//========================================================================
/** @type     C++ Source File
 *  @file     rc4.cpp
 *  @author   acornejo
 *  @date
 *   Created:       16:28:35 05/12/2007
 *   Last Update:   16:36:35 05/12/2007
 */
//========================================================================
#include <CDL/CDL.h>

using namespace CDL;

int main (int argc, char const* argv[])
{
    Buffer buf("some nice content which can span several\nlines and contains the wierdest characters\nlike #$%%^!@#$ and even non ASCII ones (not shown here)");
    printf("unencrypted:\n-------------\n%s\n--------------\n", buf.getData());
    buf.RC4("passfrase");
    printf("unencrypted:\n-------------\n%s\n--------------\n", buf.getData());
    buf.RC4("passfrase");
    printf("unencrypted:\n-------------\n%s\n--------------\n", buf.getData());
    return 0;
}
