//========================================================================
/** @type     C/C++ Header File
 *  @file     HermiteCurveSegment.h
 *  @author   acornejo
 *  @date
 *   Created:       23:03:08 03/05/2005
 *   Last Update:   14:58:29 15/06/2005
 */
//========================================================================

#ifndef __CDL_HERMITECURVESEGMENT_H__
#define __CDL_HERMITECURVESEGMENT_H__

#include <CDL/Math/Vector.h>
#include <CDL/Math/Matrix.h>

namespace CDL
{
    class DLL_API HermiteCurveSegment
    {
        private:
            Vec3t m_P[2];
            Vec3t m_T[2];
            static const Mat4t g_H;

        public:
            HermiteCurveSegment() {}
            HermiteCurveSegment(const Vec3t &, const Vec3t &, const Vec3t &, const Vec3t &);
            void setPoints(const Vec3t &, const Vec3t &);
            void setTangents(const Vec3t &, const Vec3t &);
            const Vec3t *getPoints() const;
            const Vec3t *getTangents() const;
            virtual Vec3t getPoint(const float &) const;
    };
}

#endif//__CDL_HERMITECURVESEGMENT_H__
