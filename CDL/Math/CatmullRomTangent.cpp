//========================================================================
/** @type     C++ Source File
 *  @file     CatmullRomTangent.cpp
 *  @author   acornejo
 *  @date
 *   Created:       01:37:00 04/05/2005
 *   Last Update:   01:43:53 04/05/2005
 */
//========================================================================
#include <CDL/Math/CatmullRomTangent.h>

namespace CDL
{
    void CatmullRomTangent::calculateTangents()
    {
         m_T[0]=(m_P[2]-m_P[0])*0.5;
         m_T[1]=(m_P[3]-m_P[1])*0.5;
    }
}
