#include <CDL/Math/Vector.h>
#include <CDL/Math/Math.h>

namespace CDL
{
    DEFCLASS("Vector");

#define  DT DefType
    DT dot(const Vector &v1, const Vector &v2)
    {
        const DT *p=(DT *)&v1, *q=(DT *)&v2;
        const size_t &length=v1.getLength();
        DT sum=0;

        for (int i=0; i<length; i++)
            sum+=p[i]*q[i];

        return sum;
    }

    DT dot(const Vec2t &v1, const Vec2t &v2)
    {
        const DT *p=(DT *)&v1, *q=(DT *)&v2;
        return p[0]*q[0]+p[1]*q[1];
    }

    DT dot(const Vec3t &v1, const Vec3t &v2)
    {
        const DT *p=(DT *)&v1, *q=(DT *)&v2;
        return p[0]*q[0]+p[1]*q[1]+p[2]*q[2];
    }

    DT dot(const Vec4t &v1, const Vec4t &v2)
    {
        const DT *p=(DT *)&v1, *q=(DT *)&v2;
        return p[0]*q[0]+p[1]*q[1]+p[2]*q[2]+p[3]*q[3];
    }

    Vec3t cross(const Vec3t &v1, const Vec3t &v2)
    {
        const DT *p=(DT *)&v1, *q=(DT *)&v2;
        return Vec3t(p[1]*q[2]-p[2]*q[1], p[2]*q[0]-p[0]*q[2], p[0]*q[1]-p[1]*q[0]);
    }

    Vec4t cross(const Vec4t &v1, const Vec4t &v2)
    {
        const DT *p=(DT *)&v1, *q=(DT *)&v2;
        return Vec4t(p[1]*q[2]-p[2]*q[1], p[2]*q[0]-p[0]*q[2], p[0]*q[1]-p[1]*q[0], p[3]*q[3]);
    }

#define ANG(x) (acos(x)*180.0/MM_PI)

    DT angle(const Vector &v1, const Vector &v2)
    {
        const DT *p=(DT *)&v1, *q=(DT *)&v2;
        const size_t &length=v1.getLength();
        DT ab=0, aa=0, bb=0;

        for (int i=0; i<length; i++)
        {
            ab+=p[i]*q[i];
            aa+=p[i]*p[i];
            bb+=q[i]*q[i];
        }

        return ANG(ab/sqrt(aa*bb));
    }

    DT angle(const Vec2t &v1, const Vec2t &v2)
    {
         const DT *p=(DT *)&v1, *q=(DT *)&v2;
         return ANG((p[0]*q[0]+p[1]*q[1])/sqrt((p[0]*p[0]+p[1]*p[1])*(q[0]*q[0]+q[1]*q[1])));
    }

    DT angle(const Vec3t &v1, const Vec3t &v2)
    {
         const DT *p=(DT *)&v1, *q=(DT *)&v2;
         return ANG((p[0]*q[0]+p[1]*q[1]+p[2]*q[2])/sqrt((p[0]*p[0]+p[1]*p[1]+p[2]*p[2])*(q[0]*q[0]+q[1]*q[1]+q[2]*q[2])));
    }

    DT angle(const Vec4t &v1, const Vec4t &v2)
    {
         const DT *p=(DT *)&v1, *q=(DT *)&v2;
         return ANG((p[0]*q[0]+p[1]*q[1]+p[2]*q[2]+p[3]*q[3])/sqrt((p[0]*p[0]+p[1]*p[1]+p[2]*p[2]+p[3]*p[3])*(q[0]*q[0]+q[1]*q[1]+q[2]*q[2]+q[3]*q[3])));
    }


    // ******************************************************************
    // ****                         Vector                           ****
    // ******************************************************************

    Vector::Vector(const size_t &length)
    {
        m_length=length;
        if (length)
        {
            m_v=new DT[m_length];
            reset();
        }
        else
            m_v='\0';
    }

    Vector::Vector(const size_t &length, const DT *v)
    {
        m_length=length;
        if (length)
        {
            m_v=new DT[m_length];
            memcpy(m_v, v, sizeof(DT)*m_length);
        }
        else
            m_v='\0';
    }

    Vector::Vector(const Vector &v)
    {
        m_length=v.m_length;
        if (m_length)
        {
            m_v=new DT[m_length];
            memcpy(m_v, v.m_v, sizeof(DT)*m_length);
        }
        else
            m_v='\0';
    }

    Vector::~Vector()
    {
        if (m_length)
            delete []m_v;
    }

    Vector Vector::subVector(const size_t &i) const
    {
        if (m_length)
        {
            size_t length=m_length-1;
            Vector v(length);

            for (int i=0; i<length; i++)
                v.m_v[i]=m_v[i];

            return v;
        }
        else
            return Vector();
    }

    DT &Vector::operator[](const size_t &i)
    {
        if (i < m_length)
        {
            return m_v[i];
        }
        else
        {
            Error_send("Index %d out of range\n", i);
            return m_v[0];
        }
    }

    const DT &Vector::operator[](const size_t &i) const
    {
        if (i < m_length)
        {
            return m_v[i];
        }
        else
        {
            Error_send("Index %d out of range\n", i);
            return m_v[0];
        }
    }

    Vector Vector::lerp(const Vector &v, const DT &t) const
    {
        return (*this)*(1.0-t)+v*t;
    }

    Vector Vector::operator-() const
    {
        Vector v(m_length);

        for (int i=0; i<m_length; i++)
            v.m_v[i]=-m_v[i];

        return 0;
    }

    bool Vector::operator==(const Vector &v) const
    {
        if (this == &v) return true;
        if (m_length != v.m_length)
            return false;
        for (int i=0; i<m_length; i++)
            if (m_v[i] != v.m_v[i])
                return false;
        return true;
    }

    bool Vector::operator!=(const Vector &v) const
    {
        if (this == &v) return false;
        if (m_length != v.m_length)
            return true;
        for (int i=0; i<m_length; i++)
            if (m_v[i] != v.m_v[i])
                return true;
        return false;
    }

    Vector Vector::operator+(const Vector &v) const
    {
        if (m_length != v.m_length)
        {
            Error_send("Incompatible vector lengths %d and %d\n", m_length, v.m_length);
            return Vector();
        }
        else
        {
            Vector res(v);

            for (int i=0; i<m_length; i++)
                res.m_v[i]+=m_v[i];

            return res;
        }
    }

    Vector Vector::operator-(const Vector &v) const
    {
        if (m_length != v.m_length)
        {
            Error_send("Incompatible vector lengths %d and %d\n", m_length, v.m_length);
            return Vector();
        }
        else
        {
            Vector res(*this);

            for (int i=0; i<m_length; i++)
                res.m_v[i]-=v.m_v[i];

            return res;
        }
    }

    Vector Vector::operator*(const Vector &v) const
    {
        if (m_length != v.m_length)
        {
            Error_send("Incompatible vector lengths %d and %d\n", m_length, v.m_length);
            return Vector();
        }
        else
        {
            Vector res(v);

            for (int i=0; i<m_length; i++)
                res.m_v[i]*=m_v[i];

            return res;
        }
    }

    Vector Vector::operator*(const DT &f) const
    {
        Vector res(*this);

        for (int i=0; i<m_length; i++)
            res.m_v[i]*=f;

        return res;
    }

    Vector Vector::operator/(const DT &f) const
    {
        Vector res(*this);
        const DT f_1=1/f;

        for (int i=0; i<m_length; i++)
            res.m_v[i]*=f_1;

        return res;
    }

    const Vector &Vector::operator=(const Vector &v)
    {
        if (this != &v)
        {
            if (m_length)
                delete []m_v;
            m_length=v.m_length;
            if (m_length)
            {
                m_v=new DT[m_length];
                memcpy(m_v, v.m_v, sizeof(DT)*m_length);
            }
            else
                m_v='\0';
        }

        return *this;
    }

    const Vector &Vector::operator+=(const Vector &v)
    {
        if (m_length != v.m_length)
        {
            Error_send("Incompatible vector lengths %d and %d\n", m_length, v.m_length);
        }
        else
        {
            for (int i=0; i<m_length; i++)
                m_v[i]+=v.m_v[i];
        }

        return *this;
    }

    const Vector &Vector::operator-=(const Vector &v)
    {
        if (m_length != v.m_length)
        {
            Error_send("Incompatible vector lengths %d and %d\n", m_length, v.m_length);
        }
        else
        {
            for (int i=0; i<m_length; i++)
                m_v[i]-=v.m_v[i];
        }

        return *this;
    }

    const Vector &Vector::operator*=(const Vector &v)
    {
        if (m_length != v.m_length)
        {
            Error_send("Incompatible vector lengths %d and %d\n", m_length, v.m_length);
        }
        else
        {
            for (int i=0; i<m_length; i++)
                m_v[i]*=v.m_v[i];
        }

        return *this;
    }

    const Vector &Vector::operator*=(const DT &f)
    {
        for (int i=0; i<m_length; i++)
            m_v[i]*=f;

        return *this;
    }

    const Vector &Vector::operator/=(const DT &f)
    {
        const DT f_1=1/f;

        for (int i=0; i<m_length; i++)
            m_v[i]*=f_1;

        return *this;
    }

    Vector Vector::project(const Vector &v) const
    {
        if (m_length != v.m_length)
            return Vector();
        return (*this)*(dot(*this,v)/norm());
    }

    DT Vector::distance(const Vector &t) const
    {
        DT sum=0;

        if (m_length == t.m_length)
        {
            for (int i=0; i<m_length; i++)
            {
                const DT factor=m_v[i]-t.m_v[i];
                sum+=factor*factor;
            }
            sum=sqrtf(sum);
        }

        return sum;
    }

    DT Vector::norm() const
    {
        DT sum=0;

        for (int i=0; i<m_length; i++)
            sum+=m_v[i]*m_v[i];

        return sum;
    }

    DT Vector::length() const
    {
        DT sum=0;

        for (int i=0; i<m_length; i++)
            sum+=m_v[i]*m_v[i];

        sum=sqrtf(sum);

        return sum;
    }

    const Vector& Vector::normalize()
    {
        DT l=1/length();

        for (int i=0; i<m_length; i++)
            m_v[i]*=l;

        return *this;
    }

    void Vector::reset()
    {
        memset(m_v, 0, sizeof(DT)*m_length);
    }

    // ******************************************************************
    // ****                          Vec2t                           ****
    // ******************************************************************

    Vec2t::Vec2t()
    {
        v[0]=DT(0);
        v[1]=DT(0);
    }

    Vec2t::Vec2t(const DT *vec)
    {
        v[0]=vec[0];
        v[1]=vec[1];
    }

    Vec2t::Vec2t(const DT &i, const DT &j)
    {
        v[0]=i;
        v[1]=j;
    }

    Vec2t::Vec2t(const Vec2t &t)
    {
        v[0]=t.v[0];
        v[1]=t.v[1];
    }

    DT& Vec2t::operator[](const int &i)
    {
        if (i < 0 || i > 1)
        {
            Error_send("Index %d out of range\n", i);
            return v[0];
        }
        return v[i];
    }

    const DT& Vec2t::operator[](const int &i) const
    {
        if (i < 0 || i > 1)
        {
            Error_send("Index %d out of range\n", i);
            return v[0];
        }
        return v[i];
    }

    Vec2t Vec2t::lerp(const Vec2t &t, const DT &f) const
    {
        return (*this)*(1.0-f)+t*f;
    }

    Vec2t Vec2t::operator-() const
    {
        return Vec2t(-v[0], -v[1]);
    }

    bool  Vec2t::operator==(const Vec2t &t) const
    {
        return (t.v[0] == v[0] && t.v[1] == v[1]);
    }

    bool  Vec2t::operator!=(const Vec2t &t) const
    {
        return (t.v[0] != v[0] || t.v[1] != v[1]);
    }

    Vec2t Vec2t::operator+(const Vec2t &t) const
    {
        return Vec2t(v[0]+t.v[0],v[1]+t.v[1]);
    }

    Vec2t Vec2t::operator-(const Vec2t &t) const
    {
        return Vec2t(v[0]-t.v[0],v[1]-t.v[1]);
    }

    Vec2t Vec2t::operator*(const Vec2t &t) const
    {
        return Vec2t(v[0]*t.v[0],v[1]*t.v[1]);
    }

    Vec2t Vec2t::operator*(const DT &f) const
    {
        return Vec2t(v[0]*f,v[1]*f);
    }

    Vec2t Vec2t::operator/(const DT &f) const
    {
        DT t=1/f;
        return Vec2t(v[0]*t,v[1]*t);
    }

    const Vec2t& Vec2t::operator=(const Vec2t &t)
    {
        if (this != &t)
        {
            v[0]=t.v[0];
            v[1]=t.v[1];
        }
        return *this;
    }

    const DT& Vec2t::subVector(const int &i) const
    {
        if (i == 0)
            return v[1];
        return v[0];
    }

    const Vec2t& Vec2t::operator+=(const Vec2t &t)
    {
        v[0]+=t.v[0];
        v[1]+=t.v[1];
        return *this;
    }

    const Vec2t& Vec2t::operator-=(const Vec2t &t)
    {
        v[0]-=t.v[0];
        v[1]-=t.v[1];
        return *this;
    }

    const Vec2t& Vec2t::operator*=(const Vec2t &t)
    {
        v[0]*=t.v[0];
        v[1]*=t.v[1];
        return *this;
    }

    const Vec2t& Vec2t::operator*=(const DT &f)
    {
        v[0]*=f;
        v[1]*=f;
        return *this;
    }

    const Vec2t& Vec2t::operator/=(const DT &f)
    {
        const DT &t=1/f;
        v[0]*=t;
        v[1]*=t;
        return *this;
    }

    Vec2t Vec2t::project(const Vec2t &b) const
    {
        const Vec2t &a(*this);

        return a*(dot(a,b)/norm());
    }

    DT Vec2t::distance(const Vec2t &t) const
    {
        return sqrtf((v[0]-t.v[0])*(v[0]-t.v[0])+(v[1]-t.v[1])*(v[1]-t.v[1]));
    }

    DT Vec2t::norm() const
    {
        return v[0]*v[0]+v[1]*v[1];
    }

    DT Vec2t::length() const
    {
        return sqrtf(v[0]*v[0]+v[1]*v[1]);
    }

    const Vec2t& Vec2t::normalize()
    {
        DT l=1/sqrtf(v[0]*v[0]+v[1]*v[1]);
        v[0]*=l;
        v[1]*=l;
        return *this;
    }

    void Vec2t::reset()
    {
        v[0]=DT(0);
        v[1]=DT(0);
    }

    // ******************************************************************
    // ****                          Vec3t                           ****
    // ******************************************************************

    Vec3t::Vec3t()
    {
        v[0]=DT(0);
        v[1]=DT(0);
        v[2]=DT(0);
    }

    Vec3t::Vec3t(const DT *vec)
    {
        v[0]=vec[0];
        v[1]=vec[1];
        v[2]=vec[2];
    }

    Vec3t::Vec3t(const DT &i, const DT &j, const DT &k)
    {
        v[0]=i;
        v[1]=j;
        v[2]=k;
    }

    Vec3t::Vec3t(const Vec3t &t)
    {
        v[0]=t.v[0];
        v[1]=t.v[1];
        v[2]=t.v[2];
    }

    Vec3t::Vec3t(const Vec2t &t)
    {
        v[0]=t[0];
        v[1]=t[1];
        v[2]=DT(1);
    }

    DT& Vec3t::operator[](const int &i)
    {
        if (i < 0 || i > 2)
        {
            Error_send("Index %d out of range\n", i);
            return v[0];
        }
        return v[i];
    }

    const DT& Vec3t::operator[](const int &i) const
    {
        if (i < 0 || i > 2)
        {
            Error_send("Index %d out of range\n", i);
            return v[0];
        }
        return v[i];
    }

    Vec3t Vec3t::lerp(const Vec3t &v1, const DT &t) const
    {
        return (*this)*(1.0-t)+v1*t;
    }

    Vec3t Vec3t::slerp(const Vec3t &v2_v, const DT &t) const
    {
        static const Quaternion I(0,0,0,1);
        const DefType *v2=v2_v.v;
        const DefType d=v[0]*v2[0]+v[1]*v2[1]+v[2]*v2[2];
        const Vec3t axis_v(v[1]*v2[2]-v[2]*v2[1], v[2]*v2[0]-v[0]*v2[2], v[0]*v2[1]-v[1]*v2[0]);
        const DefType qw=sqrtf((v[0]*v[0]+v[1]*v[1]+v[2]*v[2])*(v2[0]*v2[0]+v2[1]*v2[1]+v2[2]*v2[2]))+d;
        const DefType *axis=axis_v.v;

        if (qw < 0.0001)
            return I.slerp(Quaternion(-axis[2],axis[1],axis[0],qw),t)*(*this);
        else
            return I.slerp(Quaternion(axis[0],axis[1],axis[2],qw),t)*(*this);
    }

    Vec3t Vec3t::operator-() const
    {
        return Vec3t(-v[0],-v[1],-v[2]);
    }

    bool  Vec3t::operator==(const Vec3t &t) const
    {
        return (t.v[0] == v[0] && t.v[1] == v[1] && t.v[2] == v[2]);
    }

    bool  Vec3t::operator!=(const Vec3t &t) const
    {
        return (t.v[0] != v[0] || t.v[1] != v[1] || t.v[2] != v[2]);
    }

    Vec3t Vec3t::operator+(const Vec3t &t) const
    {
        return Vec3t(v[0]+t.v[0],v[1]+t.v[1],v[2]+t.v[2]);
    }

    Vec3t Vec3t::operator-(const Vec3t &t) const
    {
        return Vec3t(v[0]-t.v[0],v[1]-t.v[1],v[2]-t.v[2]);
    }

    Vec3t Vec3t::operator*(const Vec3t &t) const
    {
        return Vec3t(v[0]*t.v[0],v[1]*t.v[1],v[2]*t.v[2]);
    }

    Vec3t Vec3t::operator*(const DT &f) const
    {
        return Vec3t(v[0]*f, v[1]*f, v[2]*f);
    }

    Vec3t Vec3t::operator/(const DT &f) const
    {
        DT t=1/f;
        return Vec3t(v[0]*t, v[1]*t, v[2]*t);
    }

    const Vec3t& Vec3t::operator=(const Vec2t &t)
    {
        v[0]=t[0];
        v[1]=t[1];
        v[2]=DT(1);

        return *this;
    }

    const Vec3t& Vec3t::operator=(const Vec3t &t)
    {
        if (this != &t)
        {
            v[0]=t.v[0];
            v[1]=t.v[1];
            v[2]=t.v[2];
        }
        return *this;
    }

    Vec2t Vec3t::subVector(const int &i) const
    {
        if (i == 0)
            return Vec2t(v[1],v[2]);
        if (i == 1)
            return Vec2t(v[0],v[2]);
        return Vec2t(v[0],v[1]);
    }

    const Vec3t& Vec3t::operator+=(const Vec3t &t)
    {
        v[0]+=t.v[0];
        v[1]+=t.v[1];
        v[2]+=t.v[2];
        return *this;
    }

    const Vec3t& Vec3t::operator-=(const Vec3t &t)
    {
        v[0]-=t.v[0];
        v[1]-=t.v[1];
        v[2]-=t.v[2];
        return *this;

    }

    const Vec3t& Vec3t::operator*=(const Vec3t &t)
    {
        v[0]*=t.v[0];
        v[1]*=t.v[1];
        v[2]*=t.v[2];
        return *this;
    }

    const Vec3t& Vec3t::operator*=(const DT &f)
    {
        v[0]*=f;
        v[1]*=f;
        v[2]*=f;
        return *this;
    }

    const Vec3t& Vec3t::operator/=(const DT &f)
    {
        DT t=1/f;
        v[0]*=t;
        v[1]*=t;
        v[2]*=t;
        return *this;
    }

    Vec3t Vec3t::project(const Vec3t &b) const
    {
        const Vec3t &a(*this);

        return a*(dot(a,b)/norm());
    }

    DT Vec3t::distance(const Vec3t &t) const
    {
        return sqrtf((v[0]-t.v[0])*(v[0]-t.v[0])+(v[1]-t.v[1])*(v[1]-t.v[1])+(v[2]-t.v[2])*(v[2]-t.v[2]));
    }

    DT Vec3t::norm() const
    {
        return v[0]*v[0]+v[1]*v[1]+v[2]*v[2];
    }

    DT Vec3t::length() const
    {
        return sqrtf(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
    }

    const Vec3t& Vec3t::normalize()
    {
        DT l=1/sqrtf(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
        v[0]*=l;
        v[1]*=l;
        v[2]*=l;
        return *this;
    }

    void Vec3t::reset()
    {
        v[0]=DT(0);
        v[1]=DT(0);
        v[2]=DT(0);
    }

    // ******************************************************************
    // ****                          Vec4t                           ****
    // ******************************************************************

    Vec4t::Vec4t()
    {
        v[0]=DT(0);
        v[1]=DT(0);
        v[2]=DT(0);
        v[3]=DT(0);
    }

    Vec4t::Vec4t(const DT *vec)
    {
        v[0]=vec[0];
        v[1]=vec[1];
        v[2]=vec[2];
        v[3]=vec[3];
    }

    Vec4t::Vec4t(const DT &i, const DT &j, const DT &k, const DT &l)
    {
        v[0]=i;
        v[1]=j;
        v[2]=k;
        v[3]=l;
    }

    Vec4t::Vec4t(const Vec4t &t)
    {
        v[0]=t.v[0];
        v[1]=t.v[1];
        v[2]=t.v[2];
        v[3]=t.v[3];
    }

    Vec4t::Vec4t(const Vec3t &t)
    {
        v[0]=t[0];
        v[1]=t[1];
        v[2]=t[2];
        v[3]=DT(1);
    }

    DT& Vec4t::operator[](const int &i)
    {
        if (i < 0 || i > 3)
        {
            Error_send("Index %d out of range\n", i);
            return v[0];
        }
        return v[i];
    }

    const DT& Vec4t::operator[](const int &i) const
    {
        if (i < 0 || i > 3)
        {
            Error_send("Index %d out of range\n", i);
            return v[0];
        }
        return v[i];
    }

    Vec4t Vec4t::lerp(const Vec4t &t, const DT &f) const
    {
        return (*this)*(1.0-f)+t*f;
    }

    Vec4t Vec4t::operator-() const
    {
        return Vec4t(-v[0],-v[1],-v[2],-v[3]);
    }

    bool  Vec4t::operator==(const Vec4t &t) const
    {
        return (t.v[0] == v[0] && t.v[1] == v[1] && t.v[2] == v[2] && t.v[3] == v[3]);
    }

    bool  Vec4t::operator!=(const Vec4t &t) const
    {
        return (t.v[0] != v[0] || t.v[1] != v[1] || t.v[2] != v[2] || t.v[3] != v[3]);
    }

    Vec4t Vec4t::operator+(const Vec4t &t) const
    {
        return Vec4t(v[0]+t.v[0], v[1]+t.v[1], v[2]+t.v[2], v[3]+t.v[3]);
    }

    Vec4t Vec4t::operator-(const Vec4t &t) const
    {
        return Vec4t(v[0]-t.v[0], v[1]-t.v[1], v[2]-t.v[2], v[3]-t.v[3]);
    }

    Vec4t Vec4t::operator*(const Vec4t &t) const
    {
        return Vec4t(v[0]*t.v[0], v[1]*t.v[1], v[2]*t.v[2], v[3]*t.v[3]);
    }

    Vec4t Vec4t::operator*(const DT &f) const
    {
        return Vec4t(v[0]*f, v[1]*f, v[2]*f, v[3]*f);
    }

    Vec4t Vec4t::operator/(const DT &f) const
    {
        DT t=1/f;
        return Vec4t(v[0]*t, v[1]*t, v[2]*t, v[3]*t);
    }

    Vec3t Vec4t::subVector(const int &i) const
    {
        if (i == 0)
            return Vec3t(v[1],v[2],v[3]);
        if (i == 1)
            return Vec3t(v[0],v[2],v[3]);
        if (i == 2)
            return Vec3t(v[0],v[1],v[3]);
        return Vec3t(v[0],v[1],v[2]);
    }

    const Vec4t& Vec4t::operator=(const Vec3t &t)
    {
        v[0]=t[0];
        v[1]=t[1];
        v[2]=t[2];
        v[3]=DT(1);

        return *this;
    }

    const Vec4t& Vec4t::operator=(const Vec4t &t)
    {
        if (this != &t)
        {
            v[0]=t.v[0];
            v[1]=t.v[1];
            v[2]=t.v[2];
            v[3]=t.v[3];
        }
        return *this;
    }

    const Vec4t& Vec4t::operator+=(const Vec4t &t)
    {
        v[0]+=t.v[0];
        v[1]+=t.v[1];
        v[2]+=t.v[2];
        v[3]+=t.v[3];
        return *this;
    }

    const Vec4t& Vec4t::operator-=(const Vec4t &t)
    {
        v[0]-=t.v[0];
        v[1]-=t.v[1];
        v[2]-=t.v[2];
        v[3]-=t.v[3];
        return *this;
    }

    const Vec4t& Vec4t::operator*=(const Vec4t &t)
    {
        v[0]*=t.v[0];
        v[1]*=t.v[1];
        v[2]*=t.v[2];
        v[3]*=t.v[3];
        return *this;
    }

    const Vec4t& Vec4t::operator*=(const DT &f)
    {
        v[0]*=f;
        v[1]*=f;
        v[2]*=f;
        v[3]*=f;
        return *this;
    }

    const Vec4t& Vec4t::operator/=(const DT &f)
    {
        DT t=1/f;
        v[0]*=t;
        v[1]*=t;
        v[2]*=t;
        v[3]*=t;
        return *this;
    }

    Vec4t Vec4t::project(const Vec4t &b) const
    {
        const Vec4t &a(*this);

        return a*(dot(a,b)/norm());
    }

    DT Vec4t::distance(const Vec4t &t) const
    {
        return sqrtf((v[0]-t.v[0])*(v[0]-t.v[0])+(v[1]-t.v[1])*(v[1]-t.v[1])+(v[2]-t.v[2])*(v[2]-t.v[2])+(v[3]-t.v[3])*(v[3]-t.v[3]));
    }

    DT Vec4t::norm() const
    {
        return v[0]*v[0]+v[1]*v[1]+v[2]*v[2]+v[3]*v[3];
    }

    DT Vec4t::length() const
    {
        return sqrtf(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]+v[3]*v[3]);
    }

    const Vec4t& Vec4t::normalize()
    {
        DT l=1/sqrtf(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]+v[3]*v[3]);
        v[0]*=l;
        v[1]*=l;
        v[2]*=l;
        v[3]*=l;
        return *this;
    }

    void Vec4t::reset()
    {
        v[0]=DT(0);
        v[1]=DT(0);
        v[2]=DT(0);
        v[3]=DT(0);
    }
#undef DT
}
