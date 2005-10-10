#include <CDL/Math/Curve.h>

namespace CDL
{
    Curve::Curve()
    {
        m_N=0;
    }

    Curve::~Curve()
    {
        m_N=0;
    }

    const int &Curve::getNumPoints() const
    {
        return m_N;
    }
}
