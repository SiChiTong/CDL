//========================================================================
/** @type     C++ Source File
 *  @file     ImageLib.cpp
 *  @author   acornejo
 *  @date
 *   Created:       18:18:16 18/09/2006
 *   Last Update:   19:06:26 18/09/2006
 */
//========================================================================
#include <CDL/Image/ImageLib.h>

namespace CDL
{
    DEFCLASS("ImageLib");

    ImageLib *ImageLib::m_instance='\0';

    ImageLib &ImageLib::newInstance()
    {
        if (!m_instance)
        {
            Error_send("ImageLib instance is not registered\n");
        }
        return *m_instance;
    }

    void ImageLib::registerLibrary(ImageLib &lib)
    {
        m_instance=&lib;
    }
}
