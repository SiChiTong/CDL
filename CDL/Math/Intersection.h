#ifndef __CDL_INTERSECTION_H__
#define __CDL_INTERSECTION_H__

#include <CDL/Math/Vector.h>

namespace CDL
{
    class DLL_API Intersection
    {
        private:
            Vec3t   m_point;
            Vec3t   m_normal;
            DefType m_T;
            bool    m_inter;
			bool    m_inner;

        public:
            Intersection()
            {
                 m_inter=false;
            }
            Intersection(const Vec3t &point, const Vec3t &normal=Vec3t(), const DefType &T=0.0f, const bool &inter=false, const bool &inner=false)
            {
				m_point=point;
				m_normal=normal;
				m_T=T;
				m_inter=inter;
				m_inner=inner;
			}
			Intersection(const Intersection &i)
			{
				m_point=i.m_point;
				m_normal=i.m_normal;
				m_T=i.m_T;
				m_inter=i.m_inter;
				m_inner=i.m_inner;
			}
			Intersection &operator=(const Intersection &i)
			{
				if (&i != this)
				{
					m_point=i.m_point;
					m_normal=i.m_normal;
					m_T=i.m_T;
					m_inter=i.m_inter;
					m_inner=i.m_inner;
				}
				return *this;
			}
            operator bool() const
            {
                return m_inter;
            }
            void operator=(const bool &b)
            {
                m_inter=b;
            }
            bool operator>(const Intersection &i) const
            {
                return m_T >  i.m_T;
            }
            bool operator<(const Intersection &i) const
            {
                return m_T <  i.m_T;
            }
            bool operator>=(const Intersection &i) const
            {
                return m_T >= i.m_T;
            }
            bool operator<=(const Intersection &i) const
            {
                return m_T <= i.m_T;
            }
            bool operator==(const Intersection &i) const
            {
                return m_T == i.m_T;
            }
            const Vec3t  &getNormal() const
            {
                return m_normal;
            }
            void    setNormal(const Vec3t &normal)
            {
                m_normal=normal;
            }
            const Vec3t  &getPoint() const
            {
                return m_point;
            }
            void    setPoint(const Vec3t &point)
            {
                m_point=point;
            }
            const DefType &getT() const
            {
                return m_T;
            }
            void    setT(const DefType &T)
            {
                m_T=T;
            }
			const bool &isInner() const {return m_inner;}
    };
}

#endif//__CDL_INTERSECTION_H__
