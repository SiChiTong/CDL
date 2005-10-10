#include <CDL/Math/Plane.h>

namespace CDL
{
    Plane::Plane(const Vec3t &p, const Vec3t &n)
    {
        m_point=p;
        m_normal=n;
        m_normal.normalize();
        m_D=-dot(m_normal,m_point);
    }

    Plane::Plane(const Vec3t &v0, const Vec3t &v1, const Vec3t &v2)
    {
        m_point=v2;
        m_normal=cross((v2-v1),(v0-v1));
        m_normal.normalize();
        m_D=-dot(m_normal,m_point);
    }

    Plane::Plane(const DefType &a, const DefType &b, const DefType &c, const DefType &td)
    {
        DefType length;
        m_normal=Vec3t(a,b,c);
        length=m_normal.length();
        m_D=td/length;
        m_normal/=length;
        m_point=m_normal*m_D;
    }

    const Vec3t& Plane::getPoint() const
    {
        return m_point;
    }

    void Plane::setPoint(const Vec3t &point)
    {
        m_point=point;
    }

    const Vec3t& Plane::getNormal() const
    {
        return m_normal;
    }

    void Plane::setNormal(const Vec3t &normal)
    {
        m_normal=normal;
        m_D=-dot(m_normal,m_point);
    }

    Intersection Plane::intersect(const Ray &r) const
    {
        const DefType d=dot(m_normal,r.m_normal);

        if (d != 0)
        {
			const DefType dist=-(dot(m_normal,r.m_point)+m_D)/d;
            if (dist > 0)
            {
				if (d > 0)
					return Intersection(r.positionAtTime(dist),-m_normal,dist,true,false);
				else
					return Intersection(r.positionAtTime(dist),m_normal,dist,true,true);
            }
        }

        return Intersection();
    }

    DefType Plane::dist(const Vec3t &p) const
    {
        return dot(m_normal,p)+m_D;
    }
}
