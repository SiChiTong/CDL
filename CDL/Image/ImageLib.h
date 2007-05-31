//========================================================================
/** @type      C/C++ Header File
 *  @file     ImageLib.h
 *  @author   alcoco
 *  @date     
 *   Created:       00:28:32 06/03/2005
 *   Last Update:   20:26:48 30/05/2007
 */
//========================================================================
#ifndef __CDL_IMAGELIB_H__
#define __CDL_IMAGELIB_H__

#include <CDL/Image/Image.h>
#include <CDL/Util/Stream.h>
#include <CDL/Util/string.h>

namespace CDL
{

    class DLL_API ImageLib
    {
        private:
            static ImageLib *m_instance;

        public:
            virtual Image load(const string &)=0;
            virtual Image load(RandomAccessIOStream &, const string &)=0;
            virtual void save(const string &, const Image &)=0;
            virtual void save(RandomAccessIOStream &, const Image &, const string &type="jpg")=0;
            static ImageLib &newInstance();
            static void registerLibrary(ImageLib &);
    };
}

#endif//__CDL_IMAGELIB_H__
