#ifndef __CDL_BEZIER_H__
#define __CDL_BEZIER_H__

#include <CDL/Math/Curve.h>

namespace CDL
{
    class DLL_API Bezier: public Curve
    {
        public:
            Vec3t getPoint(const DefType &) const;
    };
}

#endif//__CDL_BEZIER_H__
