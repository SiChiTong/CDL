//========================================================================
/** @type     C/C++ Header File
 *  @file     XML.h
 *  @author   acornejo
 *  @date
 *   Created:       02:21:25 02/05/2005
 *   Last Update:   15:06:36 15/06/2005
 */
//========================================================================

#ifndef __CDL_XML_H__
#define __CDL_XML_H__

#include <CDL/Util/Stream.h>
#include <CDL/Util/DOMNode.h>

namespace CDL
{
    class DLL_API XML
    {
        public:
            static DOMNode read(InputStream &);
            static void write(OutputStream &, const DOMNode &);
    };
}
#endif//__CDL_XML_H__
