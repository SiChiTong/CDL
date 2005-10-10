#ifndef __CDL_PRIMITIVE_H__
#define __CDL_PRIMITIVE_H__

#include <CDL/Math/Intersection.h>

namespace CDL
{
    class Ray;

    class DLL_API Primitive
    {
        public:
            virtual Intersection intersect(const Ray &) const=0;
    };
}

#include <CDL/Math/Ray.h>

#endif//__CDL_PRIMITIVE_H__
