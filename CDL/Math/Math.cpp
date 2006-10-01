#include <CDL/Math/Math.h>

namespace CDL
{
    DEFCLASS("Math");

    DefType linear_interp(const DefType &t, const DefType &a, const DefType &b)
    {
        return a+t*(b-a);
    }

    DefType cosine_interp(const DefType &t, const DefType &a, const DefType &b)
    {
        return a+0.5f*(1-cos(t*MM_PI))*(b-a);
    }

    DefType cubic_interp(const DefType &t, const DefType &y0, const DefType &y1, const DefType &y2, const DefType &y3)
    {
        DefType a0=y3-y2-y0+y1, a1=y0-y1-a0;

        return (t*(t*(t*a0+a1)+y2-y0)+y1);
    }

    DefType ease(const DefType &t)
    {
        return t*t*(3-2*t);           // 3t^2-2t^3
    }

    DefType ease_ext(const DefType &t)
    {
        return t*t*t*(t*(t*6-15)+10); // 6t^5-15t^4+10t^3
    }

    DefType sin(const DefType &n)
    {
        return ::sin(n);
    }

    DefType cos(const DefType &n)
    {
        return ::cos(n);
    }

    DefType tan(const DefType &n)
    {
        return ::tan(n);
    }

    DefType asin(const DefType &n)
    {
        return ::asin(n);
    }

    DefType acos(const DefType &n)
    {
        return ::acos(n);
    }

    DefType atan(const DefType &n)
    {
        return ::atan(n);
    }

    DefType sinh(const DefType &n)
    {
        return ::sinh(n);
    }

    DefType cosh(const DefType &n)
    {
        return ::cosh(n);
    }

    DefType tanh(const DefType &n)
    {
        return ::tanh(n);
    }

#ifdef Windows_NT
    DefType asinh(const DefType &x)
    {
        return log(x+sqrt(x*x+1));
    }

    DefType acosh(const DefType &x)
    {
        return log(x+sqrt(x*x-1));
    }

    DefType atanh(const DefType &x)
    {
        return 0.5*log((1+x)/(1-x));
    }

    DefType hypot(const DefType &x, const DefType &y) // float version
    {
        Error_send("Function hypot unimplemented on windows\n");
        return 0;
    }

    DefType atan2(const DefType &u, const DefType &v)
    {
        Error_send("Function atan2 unimplemented on windows\n");
        return 0;
    }
#else
    DefType asinh(const DefType &n)
    {
        return ::asinh(n);
    }

    DefType acosh(const DefType &n)
    {
        return ::acosh(n);
    }

    DefType atanh(const DefType &n)
    {
        return ::atanh(n);
    }
#endif
    bool equal(const DefType &p, const DefType &q)
    {
        return fabs(p-q) <= MM_EPSILON;
    }

    DefType sqrt(const DefType &n)
    {
        return sqrtf(n);
    }

    DefType inv_sqrt(const DefType &n)
    {
        float v_half = n * 0.5f;
        int i = *(int *) &n;
        i = 0x5f3759df - (i >> 1);
        float v = *(float *) &i;
        return v * (1.5f - v_half * v * v);
    }

    DefType simpson1D(DefType (*func)(const DefType &), const DefType &a, const DefType &b, const size_t &steps)
    {
        DefType sum=0;
        DefType dx=(b-a)/steps;

        for (size_t i=0; i<steps; i+=2)
            sum+=(func(a+i*dx)+4*func(a+(i+1)*dx)+func(a+(i+2)*dx));

        sum*=dx/3;

        return sum;
    }

    bool coplanar(const Vec3t &v0, const Vec3t &v1, const Vec3t &v2, const Vec3t &v3)
    {
        return (fabs(dot(cross(v2-v1,v0-v1),v3-v2)) <= MM_EPSILON);
    }

    bool colinear(const Vec3t &v0, const Vec3t &v1, const Vec3t &v2)
    {
        return (cross(v1-v0,v0-v2).norm() <= MM_EPSILON);
    }
}
