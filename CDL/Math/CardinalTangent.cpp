//========================================================================
/** @type     C++ Source File
 *  @file     CardinalTangent.cpp
 *  @author   acornejo
 *  @date
 *   Created:       01:37:00 04/05/2005
 *   Last Update:   01:41:14 04/05/2005
 */
//========================================================================
#include <CDL/Math/CardinalTangent.h>

namespace CDL
{
    void CardinalTangent::setA(const float &A1, const float &A2)
    {
         m_A[0]=A1;
         m_A[1]=A2;
    }

    const float *CardinalTangent::getA() const
    {
         return m_A;
    }

    void CardinalTangent::calculateTangents()
    {
         m_T[0]=(m_P[2]-m_P[0])*m_A[0];
         m_T[1]=(m_P[3]-m_P[1])*m_A[1];
    }
}
