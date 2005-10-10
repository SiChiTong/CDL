//========================================================================
/** @type     C++ Source File
 *  @file     TCBTangent.cpp
 *  @author   acornejo
 *  @date
 *   Created:       01:15:31 04/05/2005
 *   Last Update:   01:31:16 04/05/2005
 */
//========================================================================
#include <CDL/Math/TCBTangent.h>


namespace CDL
{
    void TCBTangent::setTCB(const Vec3t &TCB1, const Vec3t &TCB2)
    {
         m_TCB[0]=TCB1;
         m_TCB[1]=TCB2;
    }

    const Vec3t *TCBTangent::getTCB() const
    {
         return m_TCB;
    }

    void TCBTangent::calculateTangents()
    {
        m_T[0]=((m_P[1]-m_P[0])*(1-m_TCB[0][0])*(1-m_TCB[0][1])*(1+m_TCB[0][2])+(m_P[2]-m_P[1])*(1-m_TCB[0][0])*(1+m_TCB[0][1])*(1-m_TCB[0][2]))*0.5;
        m_T[1]=((m_P[1]-m_P[0])*(1-m_TCB[1][0])*(1+m_TCB[1][1])*(1+m_TCB[1][2])+(m_P[2]-m_P[1])*(1-m_TCB[1][0])*(1-m_TCB[1][1])*(1-m_TCB[1][2]))*0.5;
    }
}
