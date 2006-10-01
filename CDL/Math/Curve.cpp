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

    const size_t &Curve::getNumPoints() const
    {
        return m_N;
    }
}
