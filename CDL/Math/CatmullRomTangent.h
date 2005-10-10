//========================================================================
/** @type     C/C++ Header File
 *  @file     CatmullRomTangent.h
 *  @author   acornejo
 *  @date
 *   Created:       01:33:27 04/05/2005
 *   Last Update:   14:57:02 15/06/2005
 */
//========================================================================

#include <CDL/Math/HermiteCurveTangent.h>


#ifndef __CDL_CARDINALTANGENT_H__
#define __CDL_CARDINALTANGENT_H__

namespace CDL
{
    class DLL_API CatmullRomTangent: public HermiteCurveTangent
    {
        public:
            virtual void calculateTangents();
    };
}

#endif//__CDL_CARDINALTANGENT_H__
