//========================================================================
/** @type     C++ Source File
 *  @file     HermiteCurveTangent.cpp
 *  @author   acornejo
 *  @date
 *   Created:       01:08:25 04/05/2005
 *   Last Update:   01:52:28 04/05/2005
 */
//========================================================================

#include <CDL/Math/HermiteCurveTangent.h>

namespace CDL
{
    HermiteCurveTangent::HermiteCurveTangent(const Vec3t &P1, const Vec3t &P2, const Vec3t &P3, const Vec3t &P4)
    {
         setPoints(P1, P2, P3, P4);
    }

    void HermiteCurveTangent::setPoints(const Vec3t &P1, const Vec3t &P2, const Vec3t &P3, const Vec3t &P4)
    {
         m_P[0]=P1;
         m_P[1]=P2;
         m_P[2]=P3;
         m_P[3]=P4;
    }

    void HermiteCurveTangent::setPoints(const Vec3t P[4])
    {
         m_P[0]=P[0];
         m_P[1]=P[1];
         m_P[2]=P[2];
         m_P[3]=P[3];
    }

    const Vec3t *HermiteCurveTangent::getPoints() const
    {
         return m_P;
    }

    const Vec3t *HermiteCurveTangent::getTangents() const
    {
         return m_T;
    }
}
