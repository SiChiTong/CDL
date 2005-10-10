//========================================================================
/** @type     C/C++ Header File
 *  @file     TCBTangent.h
 *  @author   acornejo
 *  @date
 *   Created:       01:13:29 04/05/2005
 *   Last Update:   15:12:56 15/06/2005
 */
//========================================================================
#ifndef __CDL_TCBTANGENT_H__
#define __CDL_TCBTANGENT_H__

#include <CDL/Math/HermiteCurveTangent.h>

namespace CDL
{
    class DLL_API TCBTangent: public HermiteCurveTangent
    {
        private:
            Vec3t m_TCB[2];

        public:
            void setTCB(const Vec3t &, const Vec3t &);
            const Vec3t *getTCB() const;
            virtual void calculateTangents();
    };

}

#endif//__CDL_TCBTANGENT_H__
