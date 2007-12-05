//========================================================================
/** @type     C++ Source File
 *  @file     file2digest.cpp
 *  @author   acornejo
 *  @date
 *   Created:       18:20:17 28/01/2006
 *   Last Update:   16:34:56 05/12/2007
 */
//========================================================================
#include <CDL/CDL.h>

using CDL::File;
using CDL::Buffer;

int main(int argc, char *argv[])
{
    for (int i=1; i<argc; i++)
    {
         File file(argv[i],File::READ);
         size_t size=file.size();
         unsigned char buffer[size];
         file.read(buffer,size);
         Buffer buf(size,buffer);
         printf("MD5:   %s  %s\n", buf.getMD5().getString().c_str(), argv[i]);
         printf("SHA1:  %s  %s\n", buf.getSHA1().getString().c_str(), argv[i]);
         printf("CRC64: %s  %s\n", buf.getCRC64().getString().c_str(), argv[i]);
    }

    return 0;
}
