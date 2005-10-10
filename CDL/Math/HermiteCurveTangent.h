//========================================================================
/** @type     C/C++ Header File
 *  @file     HermiteCurveTangent.h
 *  @author   acornejo
 *  @date
 *   Created:       00:43:13 04/05/2005
 *   Last Update:   14:58:38 15/06/2005
 */
//========================================================================

#ifndef __CDL_CURVETANGENT_H__
#define __CDL_CURVETANGENT_H__

#include <CDL/Math/Vector.h>

namespace CDL
{
    class DLL_API HermiteCurveTangent
    {
        protected:
            Vec3t m_P[4];
            Vec3t m_T[2];

        public:
            HermiteCurveTangent() {}
            HermiteCurveTangent(const Vec3t &P1, const Vec3t &P2, const Vec3t &P3, const Vec3t &P4);
            void setPoints(const Vec3t &, const Vec3t &, const Vec3t &, const Vec3t &);
            void setPoints(const Vec3t []);
            const Vec3t *getPoints() const;
            virtual void calculateTangents() {}
            const Vec3t *getTangents() const;
    };
}

#endif//__CDL_CURVETANGENT_H__
