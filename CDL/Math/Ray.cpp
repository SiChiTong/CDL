#include <CDL/Math/Ray.h>

namespace CDL
{
    Ray::Ray():m_point(0,0,0),m_normal(1,0,0) {}

    Ray::Ray(const Vec3t &from, const Vec3t &to): m_point(from)
    {
        m_normal=(to-from).normalize();
    }

    DefType Ray::dist(const Vec3t &p)
    {
        return cross(m_normal,(m_point-p)).length();
    }

    DefType Ray::dist(const Ray &r)
    {
        return dot((r.m_point-m_point),cross(m_normal,r.m_normal));
    }

    void Ray::setNormal(const Vec3t &n)
    {
        m_normal=n;
    }

    const Vec3t &Ray::getNormal() const
    {
        return m_normal;
    }

    void Ray::setPoint(const Vec3t &p)
    {
        m_point=p;
    }

    const Vec3t &Ray::getPoint() const
    {
        return m_point;
    }

    Vec3t Ray::positionAtTime(const DefType &t) const
    {
         return m_point+m_normal*t;
    }
    
    /*
    DefType Ray::intersect(Poly &p)
    {
    	DefType T;
    	if ((T=intersect((Plane &)p)) > 0)
    	{
    		Vec3t pnt=m_point+m_normal*T;
    		size_t i1, i2;
    		if (p.Normal()[0] > p.Normal()[1] && p.Normal()[0] > p.Normal()[2]) {i1=1;i2=2;}
    		else if (p.Normal()[1] > p.Normal()[2]) {i1=0;i2=2;}
    		else {i1=0;i2=1;}
     
    		DefType u0=pnt[i1]-p.Vertex(0)[i1], v0=pnt[i2]-p.Vertex(0)[i2];
    		DefType u1, u2, v1, v2, alpha, beta;
    		for (size_t i=1; i<p.Num()-1; i++)
    		{
    			u1=p.Vertex(i  )[i1]-p.Vertex(0)[i1];v1=p.Vertex(i  )[i2]-p.Vertex(0)[i2];
    			u2=p.Vertex(i+1)[i1]-p.Vertex(0)[i1];v2=p.Vertex(i+1)[i2]-p.Vertex(0)[i2];
     
    			if (u1 == 0)
    			{
    				beta=u0/u2;
    				if (beta >= 0 && beta <= 1)
    				{
    					alpha=(v0-beta*v2)/v1;
    					if (alpha >= 0 && alpha+beta <= 1) return T;
    				}
    			}
    			else
    			{
    				beta=(v0*u1-u0*v1)/(v2*u1-u2*v1);
    				if (beta >= 0 && beta <=1)
                    {
                        alpha=(u0-beta*u2)/u1;
                        if (alpha >= 0 && alpha+beta <= 1) return T;
                    }
                }
            }
            return 0;
        }
        return T;
    }
*/
}
