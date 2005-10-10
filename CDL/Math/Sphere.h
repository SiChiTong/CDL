#ifndef __CDL_SPHERE_H__
#define __CDL_SPHERE_H__

#include <CDL/Math/Primitive.h>

namespace CDL
{
    class DLL_API Sphere: public Primitive
    {
        private:
            Vec3t   m_point;
            DefType m_radius;

        public:
            Sphere(const Vec3t &p=Vec3t(0,0,0), const DefType &r=0);
            const Vec3t& getPoint() const;
            void  setPoint(const Vec3t &);
            const DefType& getRadius() const;
            void setRadius(const DefType &);
            Intersection intersect(const Ray &) const;
            DefType dist(const Vec3t&) const;
            DefType dist(const Sphere &) const;
    };
}

#endif//__CDL_SPHERE_H__
