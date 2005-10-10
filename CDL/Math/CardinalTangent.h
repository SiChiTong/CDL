//========================================================================
/** @type     C/C++ Header File
 *  @file     CardinalTangent.h
 *  @author   acornejo
 *  @date
 *   Created:       01:33:27 04/05/2005
 *   Last Update:   14:56:49 15/06/2005
 */
//========================================================================

#include <CDL/Math/HermiteCurveTangent.h>


#ifndef __CDL_CARDINALTANGENT_H__
#define __CDL_CARDINALTANGENT_H__

namespace CDL
{
    class DLL_API CardinalTangent: public HermiteCurveTangent
    {
        private:
            float m_A[2];
        public:
            void setA(const float &, const float &);
            const float *getA() const;
            virtual void calculateTangents();
    };
}

#endif//__CDL__CARDINALTANGENT_H__
