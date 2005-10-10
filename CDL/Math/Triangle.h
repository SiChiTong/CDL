//========================================================================
/** @type     C/C++ Header File
 *  @file     Triangle.h
 *  @author   acornejo
 *  @date
 *   Created:       01:03:41 12/06/2005
 *   Last Update:   15:12:06 15/06/2005
 */
//========================================================================
#ifndef __CDL_TRIANGLE_H__
#define __CDL_TRIANGLE_H__

#include <CDL/Math/Primitive.h>

namespace CDL
{
    class DLL_API Triangle: public Primitive
    {
        private:
            Vec3t m_vert[3];
            Vec3t m_normal;

        public:
            Triangle(const Vec3t &p0=Vec3t(), const Vec3t &p1=Vec3t(), const Vec3t &p2=Vec3t());
            Triangle(const Triangle &);
            const Triangle &operator=(const Triangle &);
            const Vec3t &getVertex(const size_t &) const;
            void setVertex(const size_t &, const Vec3t &);
            const Vec3t &getNormal() const;
            void setNormal(const Vec3t &);
            const Vec3t &getVertex0() const;
            void setVertex0(const Vec3t &);
            const Vec3t &getVertex1() const;
            void setVertex1(const Vec3t &);
            const Vec3t &getVertex2() const;
            void setVertex2(const Vec3t &);
            Intersection intersect(const Ray &) const;
    };
}

#endif//__CDL_TRIANGLE_H__
