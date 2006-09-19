//========================================================================
/** @type      C/C++ Header File
 *  @file     ImageLib.h
 *  @author   alcoco
 *  @date     
 *   Created:       00:28:32 06/03/2005
 *   Last Update:   19:06:17 18/09/2006
 */
//========================================================================
#ifndef __CDL_IMAGELIB_H__
#define __CDL_IMAGELIB_H__

#include <CDL/Image/Image.h>
#include <CDL/Util/Stream.h>

namespace CDL
{

    class ImageLib
    {
        private:
            static ImageLib *m_instance;

        public:
            virtual Image load(const char *)=0;
            virtual Image load(RandomAccessIOStream &, const char *)=0;
            virtual void save(const char *, const Image &)=0;
            virtual void save(RandomAccessIOStream &, const Image &, const char *type="jpg")=0;
            static ImageLib &newInstance();
            static void registerLibrary(ImageLib &);
    };
}

#endif//__CDL_IMAGELIB_H__
