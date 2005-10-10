#include <CDL/Math/Sphere.h>

namespace CDL
{
    Sphere::Sphere(const Vec3t &p, const DefType &r)
    {
        m_point=p;
        m_radius=r;
    }

    Intersection Sphere::intersect(const Ray &r) const
    {
        const Vec3t v(r.m_point-m_point); // 2 function call
        const DefType b=-dot(v,r.m_normal); // function call

        if (b > 0)
        {
            const DefType sq=b*b-v.norm()+m_radius*m_radius; // function call
            if (sq >= 0)
            {
				const DefType det=sqrtf(sq), i2=b+det; // function call
				if (i2 > 0)
				{
                    const DefType i1=b-det;
					if (i1 > 0)
					{
						const Vec3t p(r.positionAtTime(i1)); // 2 function calls
						return Intersection(p,(p-m_point)/m_radius,i1,true,false); // 3 function calls
					}
					else
					{
						const Vec3t p(r.positionAtTime(i2)); // 2 function calls
						return Intersection(p,(p-m_point)/-m_radius,i2,true,true); // 3 function calls
					}
	            }
			}
        }

        // Maximum of 10 function calls, can be reduced to 4 by inlining vector
        // class

        return Intersection();
    }

    DefType Sphere::dist(const Vec3t &p) const
    {
        return (m_point-p).length()-m_radius;
    }

    DefType Sphere::dist(const Sphere &s) const
    {
        return dist(s.m_point)-s.m_radius;
    }

    const Vec3t &Sphere::getPoint() const
    {
         return m_point;
    }

    void Sphere::setPoint(const Vec3t &point)
    {
         m_point=point;
    }

    const DefType& Sphere::getRadius() const
    {
        return m_radius;
    }

    void    Sphere::setRadius(const DefType &radius)
    {
        m_radius=radius;
    }
}
