//========================================================================
/** @type     C++ Source File
 *  @file     HermiteCurveSegment.cpp
 *  @author   acornejo
 *  @date
 *   Created:       23:24:34 03/05/2005
 *   Last Update:   23:45:56 03/05/2005
 */
//========================================================================
#include <CDL/Math/HermiteCurveSegment.h>

namespace CDL
{
    const Mat4t HermiteCurveSegment::g_H(2,-2,1,1,-3,3,-2,-1,0,0,1,0,1,0,0,0);

    HermiteCurveSegment::HermiteCurveSegment(const Vec3t &P1, const Vec3t &P2, const Vec3t &T1, const Vec3t &T2)
    {
        setPoints(P1, P2);
        setTangents(T1, T2);
    }

    void HermiteCurveSegment::setPoints(const Vec3t &P1, const Vec3t &P2)
    {
        m_P[0]=P1;
        m_P[1]=P2;
    }

    void HermiteCurveSegment::setTangents(const Vec3t &T1, const Vec3t &T2)
    {
        m_T[0]=T1;
        m_T[1]=T2;
    }

    const Vec3t *HermiteCurveSegment::getPoints() const
    {
        return m_P;
    }

    const Vec3t *HermiteCurveSegment::getTangents() const
    {
        return m_T;
    }

    Vec3t HermiteCurveSegment::getPoint(const float &t) const
    {
        const float t2=t*t, t3=t2*t;
        const Vec4t Sh=Vec4t(1,t,t2,t3)*g_H;

        return m_P[0]*Sh[0]+m_P[1]*Sh[1]+m_T[0]*Sh[2]+m_T[1]*Sh[3];
    }
}
