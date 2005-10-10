#ifndef __CDL_PLANE_H__
#define __CDL_PLANE_H__

#include <CDL/Math/Primitive.h>

namespace CDL
{
    class DLL_API Plane: public Primitive
    {
        protected:
            Vec3t   m_point;
            Vec3t   m_normal;
            DefType m_D;

        public:
            Plane(const Vec3t &p=Vec3t(0,0,0), const Vec3t &n=Vec3t(0,0,0));
            Plane(const Vec3t &, const Vec3t &, const Vec3t &);
            Plane(const DefType &, const DefType &, const DefType &, const DefType &);
            const Vec3t& getPoint() const;
            void  setPoint(const Vec3t &);
            const Vec3t& getNormal() const;
            void  setNormal(const Vec3t &);
            Intersection intersect(const Ray &) const;
            DefType dist(const Vec3t &) const;
    };
}

#endif//__CDL_PLANE_H__
