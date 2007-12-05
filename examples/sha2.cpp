//========================================================================
/** @type     C++ Source File
 *  @file     sha2.cpp
 *  @author   acornejo
 *  @date
 *   Created:       17:04:03 05/12/2007
 *   Last Update:   17:30:09 05/12/2007
 */
//========================================================================
#include <CDL/CDL.h>
#include <vector>

using namespace CDL;

int main(int argc, char const *argv[])
{
    size_t buf_size=4096, offset=0, size, cbuf_size=0;
    byte buf[buf_size], *cbuf;
    std::vector<byte> input;

    do
    {
        size=fread(buf,1,buf_size,stdin);
        for (size_t i=0; i<size; i++)
            input.push_back(buf[i]);
    } while (size > 0);

    cbuf_size=input.size();
    cbuf=new byte[cbuf_size];
    for (size_t i=0; i<cbuf_size; i++)
        cbuf[i]=input[i];
    input.clear();

    Buffer b(cbuf_size,(byte *)cbuf);
    printf("%s\n", b.getSHA256().getString().c_str());
    delete []cbuf;

    return 0;
}
