//========================================================================
/** @type     C++ Source File
 *  @file     file2buffer.cpp
 *  @author   acornejo
 *  @date
 *   Created:       18:20:17 28/01/2006
 *   Last Update:   19:19:47 28/01/2006
 */
//========================================================================
#include <CDL/CDL.h>

using CDL::File;

int main(int argc, char *argv[])
{
    for (int i=1; i<argc; i++)
    {
         File file(argv[i],File::READ);
         size_t size=file.size();
         unsigned char buffer[size];
         file.read(buffer,size);
         printf("unsigned char buffer_name%d[] = {", i);
         for (int j=0; j<size; j++)
         {
              printf("%d", (int)buffer[j]);
              if (j != size-1)
                  printf(",");
         }
         printf("};\n");
         printf("static Buffer name%d(%d,buffer_name%d);\n", i, size, i);
    }

    return 0;
}
