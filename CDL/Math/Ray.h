#ifndef __CDL_RAY_H__
#define __CDL_RAY_H__

#include <CDL/Math/Vector.h>

namespace CDL
{

    class Sphere;
    class Plane;
    class Triangle;

    class DLL_API Ray
    {
        protected:
            Vec3t m_point;
            Vec3t m_normal;

        public:
            Ray();
            Ray(const Vec3t &from, const Vec3t &to);
            DefType dist(const Vec3t &);
            DefType dist(const Ray &);
            const Vec3t &getNormal() const;
            void  setNormal(const Vec3t &);
            const Vec3t &getPoint() const;
            void  setPoint(const Vec3t &);
            Vec3t positionAtTime(const DefType &) const;

            friend class Sphere;
            friend class Plane;
            friend class Triangle;
    };
}

#include <CDL/Math/Sphere.h>
#include <CDL/Math/Plane.h>
#include <CDL/Math/Triangle.h>

#endif//__CDL_RAY_H__
