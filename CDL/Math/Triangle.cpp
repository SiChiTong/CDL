//========================================================================
/** @type     C++ Source File
 *  @file     Triangle.cpp
 *  @author   acornejo
 *  @date
 *   Created:       01:09:58 12/06/2005
 *   Last Update:   01:56:25 12/06/2005
 */
//========================================================================
#include <CDL/Math/Triangle.h>

namespace CDL
{
    #define V0 m_vert[0]
    #define V1 m_vert[1]
    #define V2 m_vert[2]
    #define N  m_normal

    DEFCLASS("Triangle");

    Triangle::Triangle(const Vec3t &v0, const Vec3t &v1, const Vec3t &v2)
    {
        V0=v0;
        V1=v1;
        V2=v2;
        N=cross(V1-V0,V2-V0);
    }

    Triangle::Triangle(const Triangle &t)
    {
         V0=t.V0;
         V1=t.V1;
         V2=t.V2;
         N=t.N;
    }

    const Triangle &Triangle::operator=(const Triangle &t)
    {
         if (&t != this)
         {
             V0=t.V0;
             V1=t.V1;
             V2=t.V2;
             N=t.N;
         }

         return *this;
    }

    const Vec3t &Triangle::getVertex(const size_t &i) const
    {
         if (i < 3)
              return m_vert[i];
         else
         {
              Error_send("Index overflow when requesting vertex %d\n", i);
         }
    }

    void Triangle::setVertex(const size_t &i, const Vec3t &v)
    {
         if (i < 3)
         {
              m_vert[i]=v;
              N=cross(V1-V0,V2-V0);
         }
         else
         {
              Error_send("Index overflow when requesting vertex %d\n", i);
         }
    }

    const Vec3t &Triangle::getNormal() const
    {
         return N;
    }

    void Triangle::setNormal(const Vec3t &n)
    {
         N=n;
    }

    const Vec3t &Triangle::getVertex0() const
    {
         return V0;
    }

    void Triangle::setVertex0(const Vec3t &v0)
    {
         V0=v0;
         N=cross(V1-V0,V2-V0);
    }

    const Vec3t &Triangle::getVertex1() const
    {
         return V1;
    }

    void Triangle::setVertex1(const Vec3t &v1)
    {
         V1=v1;
         N=cross(V1-V0,V2-V0);
    }

    const Vec3t &Triangle::getVertex2() const
    {
         return V2;
    }

    void Triangle::setVertex2(const Vec3t &v2)
    {
         V2=v2;
         N=cross(V1-V0,V2-V0);
    }

    Intersection Triangle::intersect(const Ray &r) const
    {
         const Vec3t edge1(V1-V0), edge2(V2-V0); // could precalculate
         Vec3t pvec(cross(r.getNormal(), edge2));
         DefType det=dot(edge1,pvec);

         if (det < MM_EPSILON)
             return Intersection();

         Vec3t tvec(r.getPoint()-V0);
         DefType u=dot(tvec,pvec);

         if (u < 0 || u > det)
             return Intersection();

         Vec3t qvec(cross(tvec,edge1));

         DefType v=dot(r.getPoint(),qvec);

         if (v < 0 || u+v > det)
             return Intersection();

         DefType t=dot(edge2, qvec)/det;

         return Intersection(r.positionAtTime(t), m_normal, t, true, true);
    }
}
