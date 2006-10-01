#ifndef __CDL_MATH_H__
#define __CDL_MATH_H__

#include <CDL/defs.h>

#include <CDL/Math/FixedPoint.h>
#include <CDL/Math/Complex.h>
#include <CDL/Math/FFT.h>
#include <CDL/Math/Random.h>
#include <CDL/Math/Vector.h>
#include <CDL/Math/Matrix.h>
#include <CDL/Math/Quaternion.h>
#include <CDL/Math/Ray.h>
#include <CDL/Math/Intersection.h>
#include <CDL/Math/Primitive.h>
#include <CDL/Math/Plane.h>
#include <CDL/Math/Sphere.h>
#include <CDL/Math/Ray.h>
#include <CDL/Math/FixedPoint.h>
#include <CDL/Math/ODESolver.h>

namespace CDL
{
    DLL_API DefType DLL_CALLCONV linear_interp(const DefType &, const DefType &, const DefType &);
    DLL_API DefType DLL_CALLCONV cosine_interp(const DefType &, const DefType &, const DefType &);
    DLL_API DefType DLL_CALLCONV cubic_interp(const DefType &, const DefType &, const DefType &, const DefType &, const DefType &);
    DLL_API DefType DLL_CALLCONV ease(const DefType &);
    DLL_API DefType DLL_CALLCONV ease_ext(const DefType &);
    DLL_API DefType DLL_CALLCONV sin(const DefType &);
    DLL_API DefType DLL_CALLCONV cos(const DefType &);
    DLL_API DefType DLL_CALLCONV tan(const DefType &);
    DLL_API DefType DLL_CALLCONV asin(const DefType &);
    DLL_API DefType DLL_CALLCONV acos(const DefType &);
    DLL_API DefType DLL_CALLCONV atan(const DefType &);
    DLL_API DefType DLL_CALLCONV sinh(const DefType &);
    DLL_API DefType DLL_CALLCONV cosh(const DefType &);
    DLL_API DefType DLL_CALLCONV tanh(const DefType &);
    DLL_API DefType DLL_CALLCONV asinh(const DefType &);
    DLL_API DefType DLL_CALLCONV acosh(const DefType &);
    DLL_API DefType DLL_CALLCONV atanh(const DefType &);
    DLL_API DefType DLL_CALLCONV sqrt(const DefType &);
    DLL_API DefType DLL_CALLCONV inv_sqrt(const DefType &);
    DLL_API DefType DLL_CALLCONV hypot(const DefType &, const DefType &);
    DLL_API bool DLL_CALLCONV equal(const DefType &, const DefType &);
    DLL_API DefType DLL_CALLCONV atan(const DefType &, const DefType &);
    DLL_API DefType DLL_CALLCONV simpson1D(DefType (*f)(const DefType &), const DefType &, const DefType &, const size_t &);
    DLL_API bool DLL_CALLCONV coplanar(const Vec3t &, const Vec3t &, const Vec3t &, const Vec3t &);
    DLL_API bool DLL_CALLCONV colinear(const Vec3t &, const Vec3t &, const Vec3t &);
}

#endif//__CDL_MATH_H__
