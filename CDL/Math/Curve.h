#ifndef __CDL_CURVE_H__
#define __CDL_CURVE_H__

#include <CDL/Math/Vector.h>

namespace CDL
{
    class DLL_API Curve
    {
        protected:
            int   m_N;

        public:
            Curve();
            virtual ~Curve();
            const int &getNumPoints() const;
            virtual Vec3t getPoint(const DefType &) const=0;
    };
}

#endif//__CDL_CURVE_H__
