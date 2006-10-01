#include <CDL/Math/Matrix.h>

namespace CDL
{
    DEFCLASS("Matrix");
    #define DT DefType

    DT operator*(const DT &v, const Mat2t &m)
    {
        DT *mp=(DT *)&m;

        return v*mp[M2_ij(0,0)]+mp[M2_ij(0,1)];
    }

    Vec2t operator*(const Vec2t &v, const Mat2t &m)
    {
        DT *vp=(DT *)&v, *mp=(DT *)&m;

        return Vec2t(
                vp[0]*mp[M2_ij(0,0)]+vp[1]*mp[M2_ij(0,1)],
                vp[0]*mp[M2_ij(1,0)]+vp[1]*mp[M2_ij(1,1)]);
    }

    Vec2t operator*(const Vec2t &v, const Mat3t &m)
    {
        DT *vp=(DT *)&v, *mp=(DT *)&m;

        return Vec2t(
                vp[0]*mp[M3_ij(0,0)]+vp[1]*mp[M3_ij(0,1)]+mp[M3_ij(0,2)],
                vp[0]*mp[M3_ij(1,0)]+vp[1]*mp[M3_ij(1,1)]+mp[M3_ij(1,2)]);
    }

    Vec3t operator*(const Vec3t &v, const Mat3t &m)
    {
        DT *vp=(DT *)&v, *mp=(DT *)&m;

        return Vec3t(
                vp[0]*mp[M3_ij(0,0)]+vp[1]*mp[M3_ij(0,1)]+vp[2]*mp[M3_ij(0,2)],
                vp[0]*mp[M3_ij(1,0)]+vp[1]*mp[M3_ij(1,1)]+vp[2]*mp[M3_ij(1,2)],
                vp[0]*mp[M3_ij(2,0)]+vp[1]*mp[M3_ij(2,1)]+vp[2]*mp[M3_ij(2,2)]);
    }

    Vec3t operator*(const Vec3t &v, const Mat4t &m)
    {
        DT *vp=(DT *)&v, *mp=(DT *)&m;

        return Vec3t(
                vp[0]*mp[M4_ij(0,0)]+vp[1]*mp[M4_ij(0,1)]+vp[2]*mp[M4_ij(0,2)]+mp[M4_ij(0,3)],
                vp[0]*mp[M4_ij(1,0)]+vp[1]*mp[M4_ij(1,1)]+vp[2]*mp[M4_ij(1,2)]+mp[M4_ij(1,3)],
                vp[0]*mp[M4_ij(2,0)]+vp[1]*mp[M4_ij(2,1)]+vp[2]*mp[M4_ij(2,2)]+mp[M4_ij(2,3)]);
    }

    Vec4t operator*(const Vec4t &v, const Mat4t &m)
    {
        DT *vp=(DT *)&v, *mp=(DT *)&m;

        return Vec4t(
                vp[0]*mp[M4_ij(0,0)]+vp[1]*mp[M4_ij(0,1)]+vp[2]*mp[M4_ij(0,2)]+vp[3]*mp[M4_ij(0,3)],
                vp[0]*mp[M4_ij(1,0)]+vp[1]*mp[M4_ij(1,1)]+vp[2]*mp[M4_ij(1,2)]+vp[3]*mp[M4_ij(1,3)],
                vp[0]*mp[M4_ij(2,0)]+vp[1]*mp[M4_ij(2,1)]+vp[2]*mp[M4_ij(2,2)]+vp[3]*mp[M4_ij(2,3)],
                vp[0]*mp[M4_ij(3,0)]+vp[1]*mp[M4_ij(3,1)]+vp[2]*mp[M4_ij(3,2)]+vp[3]*mp[M4_ij(3,3)]);
    }

    Mat3t star(const Vec3t &v)
    {
        const DT *p=(DT *)&v;
        return Mat3t(0,-p[2],p[1],p[2],0,-p[0],-p[1],p[0],0);
    }

    Mat2t::Mat2t()
    {}

    Mat2t::Mat2t(const DT *mat)
    {
        DT *mp=(DT *)this;
        mp[0]=mat[0];
        mp[1]=mat[1];
        mp[2]=mat[2];
        mp[3]=mat[3];
    }

    Mat2t::Mat2t(const Mat2t &t)
    {
        DT *mp=(DT *)this, *tp=(DT *)&t;
        mp[0]=tp[0];
        mp[1]=tp[1];
        mp[2]=tp[2];
        mp[3]=tp[3];
    }

    Mat2t::Mat2t(const Vec2t &i, const Vec2t &j)
    {
        m[0]=i;
        m[1]=j;
    }

    Mat2t::Mat2t(const DT &i, const DT &j, const DT &k, const DT &l)
    {
        DT *mp=(DT *)this;
        mp[M2_ij(0,0)]=i;
        mp[M2_ij(0,1)]=j;
        mp[M2_ij(1,0)]=k;
        mp[M2_ij(1,1)]=l;
    }

    const DT& Mat2t::minor(const size_t &i, const size_t &j) const
    {
        if (i == 0)
            return m[1].subVector(j);
        return m[0].subVector(j);
    }

    Vec2t& Mat2t::operator[](const size_t &i)
    {
        if (i > 1)
        {
            Error_send("Index %d out of range\n", i);
            return m[0];
        }
        return m[i];
    }

    const Vec2t& Mat2t::operator[](const size_t &i) const
    {
        if (i > 1)
        {
            Error_send("Index %d out of range\n", i);
            return m[0];
        }
        return m[i];
    }

    Mat2t Mat2t::operator+(const Mat2t &t) const
    {
        DT *mp=(DT *)this, *tp=(DT *)&t;

        return Mat2t(
                mp[M2_ij(0,0)]+tp[M2_ij(0,0)],
                mp[M2_ij(0,1)]+tp[M2_ij(0,1)],
                mp[M2_ij(1,0)]+tp[M2_ij(1,0)],
                mp[M2_ij(1,1)]+tp[M2_ij(1,1)]);
    }

    Mat2t Mat2t::operator-(const Mat2t &t) const
    {
        DT *mp=(DT *)this, *tp=(DT *)&t;

        return Mat2t(
                mp[M2_ij(0,0)]-tp[M2_ij(0,0)],
                mp[M2_ij(0,1)]-tp[M2_ij(0,1)],
                mp[M2_ij(1,0)]-tp[M2_ij(1,0)],
                mp[M2_ij(1,1)]-tp[M2_ij(1,1)]);
    }

    Mat2t Mat2t::operator*(const Mat2t &t) const
    {
        DT *mp=(DT *)this, *tp=(DT *)&t;

        return Mat2t(
                mp[M2_ij(0,0)]*tp[M2_ij(0,0)]+mp[M2_ij(0,1)]*tp[M2_ij(1,0)],
                mp[M2_ij(0,0)]*tp[M2_ij(0,1)]+mp[M2_ij(0,1)]*tp[M2_ij(1,1)],
                mp[M2_ij(1,0)]*tp[M2_ij(0,0)]+mp[M2_ij(1,1)]*tp[M2_ij(1,0)],
                mp[M2_ij(1,0)]*tp[M2_ij(0,1)]+mp[M2_ij(1,1)]*tp[M2_ij(1,1)]);
    }

    Mat2t Mat2t::operator/(const Mat2t &t) const
    {
        return (*this)*!t;
    }

    Mat2t Mat2t::operator*(const DT &f) const
    {
        DT *mp=(DT *)this;

        return Mat2t(
                mp[M2_ij(0,0)]*f,
                mp[M2_ij(0,1)]*f,
                mp[M2_ij(1,0)]*f,
                mp[M2_ij(1,1)]*f);
    }

    Mat2t Mat2t::operator/(const DT &f) const
    {
        DT *mp=(DT *)this;

        return Mat2t(
                mp[M2_ij(0,0)]/f,
                mp[M2_ij(0,1)]/f,
                mp[M2_ij(1,0)]/f,
                mp[M2_ij(1,1)]/f);
    }

    Mat2t Mat2t::operator~() const
    {
        DT *mp=(DT *)this;

        return Mat2t(
                mp[M2_ij(0,0)],
                mp[M2_ij(1,0)],
                mp[M2_ij(0,1)],
                mp[M2_ij(1,1)]);
    }

    Mat2t Mat2t::operator*() const
    {
        DT *mp=(DT *)this;

        return Mat2t(
                mp[M2_ij(1,1)],
                -mp[M2_ij(0,1)],
                -mp[M2_ij(1,0)],
                mp[M2_ij(0,0)]);
    }

    Mat2t Mat2t:: operator!() const
    {
        return *(*this)/det();
    }

    Mat2t Mat2t::operator-() const
    {
        DT *mp=(DT *)this;

        return Mat2t(
                -mp[M2_ij(0,0)],
                -mp[M2_ij(0,1)],
                -mp[M2_ij(1,0)],
                -mp[M2_ij(1,1)]);
    }

    const Mat2t& Mat2t::operator=(const Mat2t &t)
    {

        DT *mp=(DT *)this, *tp=(DT *)&t;

        if (mp != tp)
        {
            mp[0]=tp[0];
            mp[1]=tp[1];
            mp[2]=tp[2];
            mp[3]=tp[3];
        }
        return *this;
    }

    const Mat2t& Mat2t::operator+=(const Mat2t &t)
    {
        DT *mp=(DT *)this, *tp=(DT *)&t;

        mp[0]+=tp[0];
        mp[1]+=tp[1];
        mp[2]+=tp[2];
        mp[3]+=tp[3];
        return *this;
    }

    const Mat2t& Mat2t::operator-=(const Mat2t &t)
    {
        DT *mp=(DT *)this, *tp=(DT *)&t;

        mp[0]-=tp[0];
        mp[1]-=tp[1];
        mp[2]-=tp[2];
        mp[3]-=tp[3];
        return *this;
    }

    const Mat2t& Mat2t::operator*=(const Mat2t &t)
    {
        (*this)=(*this)*t;
        return *this;
    }

    const Mat2t& Mat2t::operator/=(const Mat2t &t)
    {
        (*this)=(*this)/t;
        return *this;
    }

    const Mat2t& Mat2t::operator*=(const DT &f)
    {
        DT *mp=(DT *)this;

        mp[0]*=f;
        mp[1]*=f;
        mp[2]*=f;
        mp[3]*=f;
        return *this;
    }

    const Mat2t& Mat2t::operator/=(const DT &f)
    {
        DT *mp=(DT *)this, t=1/f;

        mp[0]*=t;
        mp[1]*=t;
        mp[2]*=t;
        mp[3]*=t;
        return *this;
    }

    const Mat2t& Mat2t::transpose()
    {
        (*this)=~(*this);
        return *this;
    }

    const Mat2t& Mat2t::adjoint()
    {
        (*this)=*(*this);
        return *this;
    }

    const Mat2t& Mat2t::invert()
    {
        (*this)=!(*this);
        return *this;
    }

    DT Mat2t::det() const
    {
        return   m[0][0]*m[1][1]
            -m[0][1]*m[1][0];
    }

    void Mat2t::identity()
    {
        DT *mp=(DT *)this;

        mp[0]=1;
        mp[1]=0;
        mp[2]=0;
        mp[3]=1;
    }

    void Mat2t::scale(const Vec2t &s)
    {
        (*this)*=Mat2t(s[0], 0,
                       0,    s[1]);
    }

    void Mat2t::setToScale(const Vec2t &s)
    {
        DT *mp=(DT *)this;

        mp[0]=s[0];
        mp[1]=0;
        mp[2]=0;
        mp[3]=s[1];
    }

    void Mat2t::rotate(const DT &angleDeg)
    {
        const DT angle=DEG2RAD(angleDeg), s=sin(angle), c=cos(angle);
        (*this)*=Mat2t(c,s,
                       -s,c);
    }

    void Mat2t::setToRotation(const DT &angleDeg)
    {
        const DT angle=DEG2RAD(angleDeg), s=sin(angle), c=cos(angle);
        DT *mp=(DT *)this;

        mp[M2_ij(0,0)]=c;
        mp[M2_ij(0,1)]=s;
        mp[M2_ij(1,0)]=-s;
        mp[M2_ij(1,1)]=c;

    }

    void Mat2t::translate(const DT &t)
    {
        (*this)*=Mat2t(1,t,
                       0,1);
    }

    void Mat2t::setToTranslation(const DT &t)
    {
        DT *mp=(DT *)this;

        mp[M2_ij(0,0)]=1;
        mp[M2_ij(0,1)]=t;
        mp[M2_ij(1,0)]=0;
        mp[M2_ij(1,1)]=1;
    }


    // --------------------------------------------------------------------------------------------

    Mat3t::Mat3t()
    {}

    Mat3t::Mat3t(const DT *mat)
    {
        DT *mp=(DT *)this;
        mp[0]=mat[0];
        mp[1]=mat[1];
        mp[2]=mat[2];
        mp[3]=mat[3];
        mp[4]=mat[4];
        mp[5]=mat[5];
        mp[6]=mat[6];
        mp[7]=mat[7];
        mp[8]=mat[8];
    }

    Mat3t::Mat3t(const Mat2t &t)
    {
        DT *mp=(DT *)this, *tp=(DT *)&t;
        mp[M3_ij(0,0)]=tp[M2_ij(0,0)];
        mp[M3_ij(0,1)]=tp[M2_ij(0,1)];
        mp[M3_ij(0,2)]=0;
        mp[M3_ij(1,0)]=tp[M2_ij(1,0)];
        mp[M3_ij(1,1)]=tp[M2_ij(1,1)];
        mp[M3_ij(1,2)]=0;
        mp[M3_ij(2,0)]=0;
        mp[M3_ij(2,1)]=0;
        mp[M3_ij(2,2)]=1;
    }


    Mat3t::Mat3t(const Mat3t &t)
    {
        DT *mp=(DT *)this, *tp=(DT *)&t;
        mp[0]=tp[0];
        mp[1]=tp[1];
        mp[2]=tp[2];
        mp[3]=tp[3];
        mp[4]=tp[4];
        mp[5]=tp[5];
        mp[6]=tp[6];
        mp[7]=tp[7];
        mp[8]=tp[8];
    }

    Mat3t::Mat3t(const Vec3t &i, const Vec3t &j, const Vec3t &k)
    {
        m[0]=i;
        m[1]=j;
        m[2]=k;
    }

    Mat3t::Mat3t(const DT &a, const DT &b, const DT &c, const DT &d, const DT &e, const DT &f, const DT &g, const DT &h, const DT &i)
    {
        DT *mp=(DT *)this;
        mp[M3_ij(0,0)]=a;
        mp[M3_ij(0,1)]=b;
        mp[M3_ij(0,2)]=c;
        mp[M3_ij(1,0)]=d;
        mp[M3_ij(1,1)]=e;
        mp[M3_ij(1,2)]=f;
        mp[M3_ij(2,0)]=g;
        mp[M3_ij(2,1)]=h;
        mp[M3_ij(2,2)]=i;
    }

    Mat2t Mat3t::minor(const size_t &i, const size_t &j) const
    {
        if (i == 0)
            return Mat2t(m[1].subVector(j), m[2].subVector(j));
        if (i == 1)
            return Mat2t(m[0].subVector(j), m[2].subVector(j));
        return Mat2t(m[0].subVector(j), m[1].subVector(j));
    }

    Vec3t& Mat3t::operator[](const size_t &i)
    {
        if (i > 2)
        {
            Error_send("Index %d out of range\n", i);
            return m[0];
        }
        return m[i];
    }

    const Vec3t& Mat3t::operator[](const size_t &i) const
    {
        if (i > 2)
        {
            Error_send("Index %d out of range\n", i);
            return m[0];
        }
        return m[i];
    }

    Mat3t Mat3t::operator+(const Mat3t &t) const
    {
        DT *mp=(DT *)this, *tp=(DT *)&t;

        return Mat3t(
                mp[M3_ij(0,0)]+tp[M3_ij(0,0)],
                mp[M3_ij(0,1)]+tp[M3_ij(0,1)],
                mp[M3_ij(0,2)]+tp[M3_ij(0,2)],
                mp[M3_ij(1,0)]+tp[M3_ij(1,0)],
                mp[M3_ij(1,1)]+tp[M3_ij(1,1)],
                mp[M3_ij(1,2)]+tp[M3_ij(1,2)],
                mp[M3_ij(2,0)]+tp[M3_ij(2,0)],
                mp[M3_ij(2,1)]+tp[M3_ij(2,1)],
                mp[M3_ij(2,2)]+tp[M3_ij(2,2)]);
    }

    Mat3t Mat3t::operator-(const Mat3t &t) const
    {
        DT *mp=(DT *)this, *tp=(DT *)&t;

        return Mat3t(
                mp[M3_ij(0,0)]-tp[M3_ij(0,0)],
                mp[M3_ij(0,1)]-tp[M3_ij(0,1)],
                mp[M3_ij(0,2)]-tp[M3_ij(0,2)],
                mp[M3_ij(1,0)]-tp[M3_ij(1,0)],
                mp[M3_ij(1,1)]-tp[M3_ij(1,1)],
                mp[M3_ij(1,2)]-tp[M3_ij(1,2)],
                mp[M3_ij(2,0)]-tp[M3_ij(2,0)],
                mp[M3_ij(2,1)]-tp[M3_ij(2,1)],
                mp[M3_ij(2,2)]-tp[M3_ij(2,2)]);
    }

    Mat3t Mat3t::operator*(const Mat3t &t) const
    {
        DT *mp=(DT *)this, *tp=(DT *)&t;

        return Mat3t(
                mp[M3_ij(0,0)]*tp[M3_ij(0,0)]+mp[M3_ij(0,1)]*tp[M3_ij(1,0)]+mp[M3_ij(0,2)]*tp[M3_ij(2,0)],
                mp[M3_ij(0,0)]*tp[M3_ij(0,1)]+mp[M3_ij(0,1)]*tp[M3_ij(1,1)]+mp[M3_ij(0,2)]*tp[M3_ij(2,1)],
                mp[M3_ij(0,0)]*tp[M3_ij(0,2)]+mp[M3_ij(0,1)]*tp[M3_ij(1,2)]+mp[M3_ij(0,2)]*tp[M3_ij(2,2)],
                mp[M3_ij(1,0)]*tp[M3_ij(0,0)]+mp[M3_ij(1,1)]*tp[M3_ij(1,0)]+mp[M3_ij(1,2)]*tp[M3_ij(2,0)],
                mp[M3_ij(1,0)]*tp[M3_ij(0,1)]+mp[M3_ij(1,1)]*tp[M3_ij(1,1)]+mp[M3_ij(1,2)]*tp[M3_ij(2,1)],
                mp[M3_ij(1,0)]*tp[M3_ij(0,2)]+mp[M3_ij(1,1)]*tp[M3_ij(1,2)]+mp[M3_ij(1,2)]*tp[M3_ij(2,2)],
                mp[M3_ij(2,0)]*tp[M3_ij(0,0)]+mp[M3_ij(2,1)]*tp[M3_ij(1,0)]+mp[M3_ij(2,2)]*tp[M3_ij(2,0)],
                mp[M3_ij(2,0)]*tp[M3_ij(0,1)]+mp[M3_ij(2,1)]*tp[M3_ij(1,1)]+mp[M3_ij(2,2)]*tp[M3_ij(2,1)],
                mp[M3_ij(2,0)]*tp[M3_ij(0,2)]+mp[M3_ij(2,1)]*tp[M3_ij(1,2)]+mp[M3_ij(2,2)]*tp[M3_ij(2,2)]);
    }

    Mat3t Mat3t::operator/(const Mat3t &t) const
    {
        return (*this)*!t;
    }

    Mat3t Mat3t::operator*(const DT &f) const
    {
        DT *mp=(DT *)this;

        return Mat3t(
                mp[M3_ij(0,0)]*f,
                mp[M3_ij(0,1)]*f,
                mp[M3_ij(0,2)]*f,
                mp[M3_ij(1,0)]*f,
                mp[M3_ij(1,1)]*f,
                mp[M3_ij(1,2)]*f,
                mp[M3_ij(2,0)]*f,
                mp[M3_ij(2,1)]*f,
                mp[M3_ij(2,2)]*f);
    }

    Mat3t Mat3t::operator/(const DT &f) const
    {
        DT *mp=(DT *)this;

        return Mat3t(
                mp[M3_ij(0,0)]/f,
                mp[M3_ij(0,1)]/f,
                mp[M3_ij(0,2)]/f,
                mp[M3_ij(1,0)]/f,
                mp[M3_ij(1,1)]/f,
                mp[M3_ij(1,2)]/f,
                mp[M3_ij(2,0)]/f,
                mp[M3_ij(2,1)]/f,
                mp[M3_ij(2,2)]/f);
    }

    Mat3t Mat3t::operator~() const
    {
        DT *mp=(DT *)this;

        return Mat3t(
                mp[M3_ij(0,0)],
                mp[M3_ij(1,0)],
                mp[M3_ij(2,0)],
                mp[M3_ij(0,1)],
                mp[M3_ij(1,1)],
                mp[M3_ij(2,1)],
                mp[M3_ij(0,2)],
                mp[M3_ij(1,2)],
                mp[M3_ij(2,2)]);
    }

    Mat3t Mat3t::operator*() const
    {
        DT *mp=(DT *)this;

        return Mat3t(
                mp[M3_ij(1,1)]*mp[M3_ij(2,2)]-mp[M3_ij(1,2)]*mp[M3_ij(2,1)],
                mp[M3_ij(0,1)]*mp[M3_ij(2,2)]-mp[M3_ij(0,2)]*mp[M3_ij(2,1)],
                mp[M3_ij(0,1)]*mp[M3_ij(1,2)]-mp[M3_ij(0,2)]*mp[M3_ij(1,1)],
                mp[M3_ij(1,0)]*mp[M3_ij(2,2)]-mp[M3_ij(1,2)]*mp[M3_ij(2,0)],
                mp[M3_ij(0,0)]*mp[M3_ij(2,2)]-mp[M3_ij(0,2)]*mp[M3_ij(2,0)],
                mp[M3_ij(0,0)]*mp[M3_ij(1,2)]-mp[M3_ij(0,2)]*mp[M3_ij(1,0)],
                mp[M3_ij(1,0)]*mp[M3_ij(2,1)]-mp[M3_ij(1,1)]*mp[M3_ij(2,0)],
                mp[M3_ij(0,0)]*mp[M3_ij(2,1)]-mp[M3_ij(0,1)]*mp[M3_ij(2,0)],
                mp[M3_ij(0,0)]*mp[M3_ij(1,1)]-mp[M3_ij(0,1)]*mp[M3_ij(1,0)]);
    }

    Mat3t Mat3t:: operator!() const
    {
        return *(*this)/det();
    }

    Mat3t Mat3t::operator-() const
    {
        DT *mp=(DT *)this;

        return Mat3t(
                -mp[M3_ij(0,0)],
                -mp[M3_ij(0,1)],
                -mp[M3_ij(0,2)],
                -mp[M3_ij(1,0)],
                -mp[M3_ij(1,1)],
                -mp[M3_ij(1,2)],
                -mp[M3_ij(2,0)],
                -mp[M3_ij(2,1)],
                -mp[M3_ij(2,2)]);
    }

    const Mat3t& Mat3t::operator=(const Mat3t &t)
    {
        DT *mp=(DT *)this, *tp=(DT *)&t;

        if (mp != tp)
        {
            mp[0]=tp[0];
            mp[1]=tp[1];
            mp[2]=tp[2];
            mp[3]=tp[3];
            mp[4]=tp[4];
            mp[5]=tp[5];
            mp[6]=tp[6];
            mp[7]=tp[7];
            mp[8]=tp[8];
        }
        return *this;
    }

    const Mat3t& Mat3t::operator+=(const Mat3t &t)
    {
        DT *mp=(DT *)this, *tp=(DT *)&t;

        mp[0]+=tp[0];
        mp[1]+=tp[1];
        mp[2]+=tp[2];
        mp[3]+=tp[3];
        mp[4]+=tp[4];
        mp[5]+=tp[5];
        mp[6]+=tp[6];
        mp[7]+=tp[7];
        mp[8]+=tp[8];
        return *this;
    }

    const Mat3t& Mat3t::operator-=(const Mat3t &t)
    {
        DT *mp=(DT *)this, *tp=(DT *)&t;

        mp[0]-=tp[0];
        mp[1]-=tp[1];
        mp[2]-=tp[2];
        mp[3]-=tp[3];
        mp[4]-=tp[4];
        mp[5]-=tp[5];
        mp[6]-=tp[6];
        mp[7]-=tp[7];
        mp[8]-=tp[8];
        return *this;
    }

    const Mat3t& Mat3t::operator*=(const Mat3t &t)
    {
        (*this)=(*this)*t;
        return *this;
    }

    const Mat3t& Mat3t::operator/=(const Mat3t &t)
    {
        (*this)=(*this)/t;
        return *this;
    }

    const Mat3t& Mat3t::operator*=(const DT &f)
    {
        DT *mp=(DT *)this;

        mp[0]*=f;
        mp[1]*=f;
        mp[2]*=f;
        mp[3]*=f;
        mp[4]*=f;
        mp[5]*=f;
        mp[6]*=f;
        mp[7]*=f;
        mp[8]*=f;
        return *this;
    }

    const Mat3t& Mat3t::operator/=(const DT &f)
    {
        DT *mp=(DT *)this, t=1/f;

        mp[0]*=t;
        mp[1]*=t;
        mp[2]*=t;
        mp[3]*=t;
        mp[4]*=t;
        mp[5]*=t;
        mp[6]*=t;
        mp[7]*=t;
        mp[8]*=t;
        return *this;
    }

    const Mat3t& Mat3t::transpose()
    {
        (*this)=~(*this);
        return *this;
    }

    const Mat3t& Mat3t::adjoint()
    {
        (*this)=*(*this);
        return *this;
    }

    const Mat3t& Mat3t::invert()
    {
        (*this)=!(*this);
        return *this;
    }

    DT Mat3t::det() const
    {
        DT *mp=(DT *)this;
        return mp[M3_ij(0,0)]*(mp[M3_ij(1,1)]*mp[M3_ij(2,2)]-mp[M3_ij(1,2)]*mp[M3_ij(2,1)]) +
            mp[M3_ij(1,0)]*(mp[M3_ij(2,1)]*mp[M3_ij(0,2)]-mp[M3_ij(0,1)]*mp[M3_ij(2,2)]) +
            mp[M3_ij(2,0)]*(mp[M3_ij(0,1)]*mp[M3_ij(1,2)]-mp[M3_ij(1,1)]*mp[M3_ij(0,2)]);
    }

    void Mat3t::identity()
    {
        DT *mp=(DT *)this;
        mp[0]=1;
        mp[1]=0;
        mp[2]=0;
        mp[3]=0;
        mp[4]=1;
        mp[5]=0;
        mp[6]=0;
        mp[7]=0;
        mp[8]=1;
    }

    void Mat3t::rotate(const DT &angleDeg, const Vec3t &axisVec)
    {
        const DT angle=DEG2RAD(angleDeg), c=cos(angle), s=sin(angle), t=1.0-c, *axis=(DT *)&axisVec;
        (*this)*=Mat3t(
                       t*axis[0]*axis[0]+c,         t*axis[1]*axis[0]-s*axis[2], t*axis[2]*axis[0]+s*axis[1],
                       t*axis[0]*axis[1]+s*axis[2], t*axis[1]*axis[1]+c,         t*axis[2]*axis[1]-s*axis[0],
                       t*axis[0]*axis[2]-s*axis[1], t*axis[1]*axis[2]+s*axis[0], t*axis[2]*axis[2]+c       );
    }

    void Mat3t::rotateX(const DT &angleDeg)
    {
        const DT angle=DEG2RAD(angleDeg), c=cos(angle), s=sin(angle);
        (*this)*=Mat3t( 1, 0, 0,
                        0, c,-s,
                        0, s, c);
    }

    void Mat3t::rotateY(const DT &angleDeg)
    {
        const DT angle=DEG2RAD(angleDeg), c=cos(angle), s=sin(angle);
        (*this)*=Mat3t( c, 0, s,
                        0, 1, 0,
                       -s, 0, c);
    }

    void Mat3t::rotateZ(const DT &angleDeg)
    {
        const DT angle=DEG2RAD(angleDeg), c=cos(angle), s=sin(angle);
        (*this)*=Mat3t( c,-s, 0,
                        s, c, 0,
                        0, 0, 1);
    }

    void Mat3t::setToRotation(const DT &angleDeg, const Vec3t &axisVec)
    {
        const DT angle=DEG2RAD(angleDeg), c=cos(angle), s=sin(angle), t=1.0-c, *axis=(DT *)&axisVec;
        DT *mp=(DT *)this;

        mp[M3_ij(0,0)]=t*axis[0]*axis[0]+c;
        mp[M3_ij(0,1)]=t*axis[0]*axis[1]-s*axis[2];
        mp[M3_ij(0,2)]=t*axis[0]*axis[2]+s*axis[1];
        mp[M3_ij(1,0)]=t*axis[1]*axis[0]+s*axis[2];
        mp[M3_ij(1,1)]=t*axis[1]*axis[1]+c;
        mp[M3_ij(1,2)]=t*axis[1]*axis[2]-s*axis[0];
        mp[M3_ij(2,0)]=t*axis[2]*axis[0]-s*axis[1];
        mp[M3_ij(2,1)]=t*axis[2]*axis[1]+s*axis[0];
        mp[M3_ij(2,2)]=t*axis[2]*axis[2]+c;
    }

    void Mat3t::translate(const Vec2t &t)
    {
        (*this)*=Mat3t(1, 0, t[0],
                       0, 1, t[1],
                       0, 0, 1);
    }

    void Mat3t::setToTranslation(const Vec2t &t)
    {
        DT *mp=(DT *)this;

        mp[M3_ij(0,0)]=1;
        mp[M3_ij(0,1)]=0;
        mp[M3_ij(0,2)]=t[0];
        mp[M3_ij(1,0)]=0;
        mp[M3_ij(1,1)]=1;
        mp[M3_ij(1,2)]=t[1];
        mp[M3_ij(2,0)]=0;
        mp[M3_ij(2,1)]=0;
        mp[M3_ij(2,2)]=1;
    }

    void Mat3t::scale(const Vec3t &s)
    {
        (*this)*=Mat3t(s[0], 0.0,  0.0,
                       0.0,  s[1], 0.0,
                       0.0,  0.0,  s[2]);
    }

    void Mat3t::setToScale(const Vec3t &s)
    {
        DT *mp=(DT *)this;

        mp[0]=s[0];
        mp[1]=0;
        mp[2]=0;
        mp[3]=0;
        mp[4]=s[1];
        mp[5]=0;
        mp[6]=0;
        mp[7]=0;
        mp[8]=s[2];
    }


    // -------------------------------------------------------------------------

    Mat4t::Mat4t()
    {}

    Mat4t::Mat4t(const DT *mat)
    {
        DT *mp=(DT *)this;
        mp[0]=mat[0];
        mp[1]=mat[1];
        mp[2]=mat[2];
        mp[3]=mat[3];
        mp[4]=mat[4];
        mp[5]=mat[5];
        mp[6]=mat[6];
        mp[7]=mat[7];
        mp[8]=mat[8];
        mp[9]=mat[9];
        mp[10]=mat[10];
        mp[11]=mat[11];
        mp[12]=mat[12];
        mp[13]=mat[13];
        mp[14]=mat[14];
        mp[15]=mat[15];
    }

    Mat4t::Mat4t(const Mat3t &t)
    {
        DT *mp=(DT *)this, *tp=(DT *)&t;
        mp[M4_ij(0,0)]=tp[M3_ij(0,0)];
        mp[M4_ij(0,1)]=tp[M3_ij(0,1)];
        mp[M4_ij(0,2)]=tp[M3_ij(0,2)];
        mp[M4_ij(0,3)]=0;
        mp[M4_ij(1,0)]=tp[M3_ij(1,0)];
        mp[M4_ij(1,1)]=tp[M3_ij(1,1)];
        mp[M4_ij(1,2)]=tp[M3_ij(1,2)];
        mp[M4_ij(1,3)]=0;
        mp[M4_ij(2,0)]=tp[M3_ij(2,0)];
        mp[M4_ij(2,1)]=tp[M3_ij(2,1)];
        mp[M4_ij(2,2)]=tp[M3_ij(2,2)];
        mp[M4_ij(2,3)]=0;
        mp[M4_ij(3,0)]=0;
        mp[M4_ij(3,1)]=0;
        mp[M4_ij(3,2)]=0;
        mp[M4_ij(3,3)]=1;

    }

    Mat4t::Mat4t(const Mat4t &t)
    {
        DT *mp=(DT *)this, *tp=(DT *)&t;
        mp[0]=tp[0];
        mp[1]=tp[1];
        mp[2]=tp[2];
        mp[3]=tp[3];
        mp[4]=tp[4];
        mp[5]=tp[5];
        mp[6]=tp[6];
        mp[7]=tp[7];
        mp[8]=tp[8];
        mp[9]=tp[9];
        mp[10]=tp[10];
        mp[11]=tp[11];
        mp[12]=tp[12];
        mp[13]=tp[13];
        mp[14]=tp[14];
        mp[15]=tp[15];
    }

    Mat4t::Mat4t(const Vec4t &i, const Vec4t &j, const Vec4t &k, const Vec4t &l)
    {
        m[0]=i;
        m[1]=j;
        m[2]=k;
        m[3]=l;
    }

    Mat4t::Mat4t(const DT &a, const DT &b, const DT &c, const DT &d, const DT &e, const DT &f, const DT &g, const DT &h,
            const DT &i, const DT &j, const DT &k, const DT &l, const DT &m1, const DT &n, const DT &o, const DT &p)
    {
        DT *mp=(DT *)this;
        mp[M4_ij(0,0)]=a;
        mp[M4_ij(0,1)]=b;
        mp[M4_ij(0,2)]=c;
        mp[M4_ij(0,3)]=d;
        mp[M4_ij(1,0)]=e;
        mp[M4_ij(1,1)]=f;
        mp[M4_ij(1,2)]=g;
        mp[M4_ij(1,3)]=h;
        mp[M4_ij(2,0)]=i;
        mp[M4_ij(2,1)]=j;
        mp[M4_ij(2,2)]=k;
        mp[M4_ij(2,3)]=l;
        mp[M4_ij(3,0)]=m1;
        mp[M4_ij(3,1)]=n;
        mp[M4_ij(3,2)]=o;
        mp[M4_ij(3,3)]=p;
    }

    Mat3t Mat4t::minor(const size_t &i, const size_t &j) const
    {
        if (i == 0)
            return Mat3t(m[1].subVector(j), m[2].subVector(j), m[3].subVector(j));
        if (i == 1)
            return Mat3t(m[0].subVector(j), m[2].subVector(j), m[3].subVector(j));
        if (i == 2)
            return Mat3t(m[0].subVector(j), m[1].subVector(j), m[3].subVector(j));
        return Mat3t(m[0].subVector(j), m[1].subVector(j), m[2].subVector(j));
    }

    Vec4t& Mat4t::operator[](const size_t &i)
    {
        if (i > 3)
        {
            Error_send("Index %d out of range\n", i);
            return m[0];
        }
        return m[i];
    }

    const Vec4t& Mat4t::operator[](const size_t &i) const
    {
        if (i > 3)
        {
            Error_send("Index %d out of range\n", i);
            return m[0];
        }
        return m[i];
    }

    Mat4t Mat4t::operator+(const Mat4t &t) const
    {
        DT *mp=(DT *)this, *tp=(DT *)&t;

        return Mat4t(
                mp[M4_ij(0,0)]+tp[M4_ij(0,0)],
                mp[M4_ij(0,1)]+tp[M4_ij(0,1)],
                mp[M4_ij(0,2)]+tp[M4_ij(0,2)],
                mp[M4_ij(0,3)]+tp[M4_ij(0,3)],
                mp[M4_ij(1,0)]+tp[M4_ij(1,0)],
                mp[M4_ij(1,1)]+tp[M4_ij(1,1)],
                mp[M4_ij(1,2)]+tp[M4_ij(1,2)],
                mp[M4_ij(1,3)]+tp[M4_ij(1,3)],
                mp[M4_ij(2,0)]+tp[M4_ij(2,0)],
                mp[M4_ij(2,1)]+tp[M4_ij(2,1)],
                mp[M4_ij(2,2)]+tp[M4_ij(2,2)],
                mp[M4_ij(2,3)]+tp[M4_ij(2,3)],
                mp[M4_ij(3,0)]+tp[M4_ij(3,0)],
                mp[M4_ij(3,1)]+tp[M4_ij(3,1)],
                mp[M4_ij(3,2)]+tp[M4_ij(3,2)],
                mp[M4_ij(3,3)]+tp[M4_ij(3,3)]);
    }

    Mat4t Mat4t::operator-(const Mat4t &t) const
    {
        DT *mp=(DT *)this, *tp=(DT *)&t;

        return Mat4t(
                mp[M4_ij(0,0)]-tp[M4_ij(0,0)],
                mp[M4_ij(0,1)]-tp[M4_ij(0,1)],
                mp[M4_ij(0,2)]-tp[M4_ij(0,2)],
                mp[M4_ij(0,3)]-tp[M4_ij(0,3)],
                mp[M4_ij(1,0)]-tp[M4_ij(1,0)],
                mp[M4_ij(1,1)]-tp[M4_ij(1,1)],
                mp[M4_ij(1,2)]-tp[M4_ij(1,2)],
                mp[M4_ij(1,3)]-tp[M4_ij(1,3)],
                mp[M4_ij(2,0)]-tp[M4_ij(2,0)],
                mp[M4_ij(2,1)]-tp[M4_ij(2,1)],
                mp[M4_ij(2,2)]-tp[M4_ij(2,2)],
                mp[M4_ij(2,3)]-tp[M4_ij(2,3)],
                mp[M4_ij(3,0)]-tp[M4_ij(3,0)],
                mp[M4_ij(3,1)]-tp[M4_ij(3,1)],
                mp[M4_ij(3,2)]-tp[M4_ij(3,2)],
                mp[M4_ij(3,3)]-tp[M4_ij(3,3)]);
    }

    Mat4t Mat4t::operator*(const Mat4t &t) const
    {
        DT *mp=(DT *)this, *tp=(DT *)&t;

        return Mat4t(
                mp[M4_ij(0,0)]*tp[M4_ij(0,0)]+mp[M4_ij(0,1)]*tp[M4_ij(1,0)]+mp[M4_ij(0,2)]*tp[M4_ij(2,0)]+mp[M4_ij(0,3)]*tp[M4_ij(3,0)],
                mp[M4_ij(0,0)]*tp[M4_ij(0,1)]+mp[M4_ij(0,1)]*tp[M4_ij(1,1)]+mp[M4_ij(0,2)]*tp[M4_ij(2,1)]+mp[M4_ij(0,3)]*tp[M4_ij(3,1)],
                mp[M4_ij(0,0)]*tp[M4_ij(0,2)]+mp[M4_ij(0,1)]*tp[M4_ij(1,2)]+mp[M4_ij(0,2)]*tp[M4_ij(2,2)]+mp[M4_ij(0,3)]*tp[M4_ij(3,2)],
                mp[M4_ij(0,0)]*tp[M4_ij(0,3)]+mp[M4_ij(0,1)]*tp[M4_ij(1,3)]+mp[M4_ij(0,2)]*tp[M4_ij(2,3)]+mp[M4_ij(0,3)]*tp[M4_ij(3,3)],
                mp[M4_ij(1,0)]*tp[M4_ij(0,0)]+mp[M4_ij(1,1)]*tp[M4_ij(1,0)]+mp[M4_ij(1,2)]*tp[M4_ij(2,0)]+mp[M4_ij(1,3)]*tp[M4_ij(3,0)],
                mp[M4_ij(1,0)]*tp[M4_ij(0,1)]+mp[M4_ij(1,1)]*tp[M4_ij(1,1)]+mp[M4_ij(1,2)]*tp[M4_ij(2,1)]+mp[M4_ij(1,3)]*tp[M4_ij(3,1)],
                mp[M4_ij(1,0)]*tp[M4_ij(0,2)]+mp[M4_ij(1,1)]*tp[M4_ij(1,2)]+mp[M4_ij(1,2)]*tp[M4_ij(2,2)]+mp[M4_ij(1,3)]*tp[M4_ij(3,2)],
                mp[M4_ij(1,0)]*tp[M4_ij(0,3)]+mp[M4_ij(1,1)]*tp[M4_ij(1,3)]+mp[M4_ij(1,2)]*tp[M4_ij(2,3)]+mp[M4_ij(1,3)]*tp[M4_ij(3,3)],
                mp[M4_ij(2,0)]*tp[M4_ij(0,0)]+mp[M4_ij(2,1)]*tp[M4_ij(1,0)]+mp[M4_ij(2,2)]*tp[M4_ij(2,0)]+mp[M4_ij(2,3)]*tp[M4_ij(3,0)],
                mp[M4_ij(2,0)]*tp[M4_ij(0,1)]+mp[M4_ij(2,1)]*tp[M4_ij(1,1)]+mp[M4_ij(2,2)]*tp[M4_ij(2,1)]+mp[M4_ij(2,3)]*tp[M4_ij(3,1)],
                mp[M4_ij(2,0)]*tp[M4_ij(0,2)]+mp[M4_ij(2,1)]*tp[M4_ij(1,2)]+mp[M4_ij(2,2)]*tp[M4_ij(2,2)]+mp[M4_ij(2,3)]*tp[M4_ij(3,2)],
                mp[M4_ij(2,0)]*tp[M4_ij(0,3)]+mp[M4_ij(2,1)]*tp[M4_ij(1,3)]+mp[M4_ij(2,2)]*tp[M4_ij(2,3)]+mp[M4_ij(2,3)]*tp[M4_ij(3,3)],
                mp[M4_ij(3,0)]*tp[M4_ij(0,0)]+mp[M4_ij(3,1)]*tp[M4_ij(1,0)]+mp[M4_ij(3,2)]*tp[M4_ij(2,0)]+mp[M4_ij(3,3)]*tp[M4_ij(3,0)],
                mp[M4_ij(3,0)]*tp[M4_ij(0,1)]+mp[M4_ij(3,1)]*tp[M4_ij(1,1)]+mp[M4_ij(3,2)]*tp[M4_ij(2,1)]+mp[M4_ij(3,3)]*tp[M4_ij(3,1)],
                mp[M4_ij(3,0)]*tp[M4_ij(0,2)]+mp[M4_ij(3,1)]*tp[M4_ij(1,2)]+mp[M4_ij(3,2)]*tp[M4_ij(2,2)]+mp[M4_ij(3,3)]*tp[M4_ij(3,2)],
                mp[M4_ij(3,0)]*tp[M4_ij(0,3)]+mp[M4_ij(3,1)]*tp[M4_ij(1,3)]+mp[M4_ij(3,2)]*tp[M4_ij(2,3)]+mp[M4_ij(3,3)]*tp[M4_ij(3,3)]);
    }

    Mat4t Mat4t::operator/(const Mat4t &t) const
    {
        return (*this)*!t;
    }

    Mat4t Mat4t::operator*(const DT &f) const
    {
        DT *mp=(DT *)this;

        return Mat4t(
                mp[M4_ij(0,0)]*f,
                mp[M4_ij(0,1)]*f,
                mp[M4_ij(0,2)]*f,
                mp[M4_ij(0,3)]*f,
                mp[M4_ij(1,0)]*f,
                mp[M4_ij(1,1)]*f,
                mp[M4_ij(1,2)]*f,
                mp[M4_ij(1,3)]*f,
                mp[M4_ij(2,0)]*f,
                mp[M4_ij(2,1)]*f,
                mp[M4_ij(2,2)]*f,
                mp[M4_ij(2,3)]*f,
                mp[M4_ij(3,0)]*f,
                mp[M4_ij(3,1)]*f,
                mp[M4_ij(3,2)]*f,
                mp[M4_ij(3,3)]*f);
    }

    Mat4t Mat4t::operator/(const DT &f) const
    {
        DT *mp=(DT *)this, t=1/f;

        return Mat4t(
                mp[M4_ij(0,0)]*t,
                mp[M4_ij(0,1)]*t,
                mp[M4_ij(0,2)]*t,
                mp[M4_ij(0,3)]*t,
                mp[M4_ij(1,0)]*t,
                mp[M4_ij(1,1)]*t,
                mp[M4_ij(1,2)]*t,
                mp[M4_ij(1,3)]*t,
                mp[M4_ij(2,0)]*t,
                mp[M4_ij(2,1)]*t,
                mp[M4_ij(2,2)]*t,
                mp[M4_ij(2,3)]*t,
                mp[M4_ij(3,0)]*t,
                mp[M4_ij(3,1)]*t,
                mp[M4_ij(3,2)]*t,
                mp[M4_ij(3,3)]*t);
    }

    Mat4t Mat4t::operator~() const
    {
        DT *mp=(DT *)this;

        return Mat4t(
                mp[M4_ij(0,0)],
                mp[M4_ij(1,0)],
                mp[M4_ij(2,0)],
                mp[M4_ij(3,0)],
                mp[M4_ij(0,1)],
                mp[M4_ij(1,1)],
                mp[M4_ij(2,1)],
                mp[M4_ij(3,1)],
                mp[M4_ij(0,2)],
                mp[M4_ij(1,2)],
                mp[M4_ij(2,2)],
                mp[M4_ij(3,2)],
                mp[M4_ij(0,3)],
                mp[M4_ij(1,3)],
                mp[M4_ij(2,3)],
                mp[M4_ij(3,3)]);
    }

    Mat4t Mat4t::operator*() const
    {
        DT *mp=(DT *)this;

        return Mat4t(
                mp[M4_ij(1,1)]*(mp[M4_ij(2,2)]*mp[M4_ij(3,3)]-mp[M4_ij(2,3)]*mp[M4_ij(3,2)])-mp[M4_ij(1,2)]*(mp[M4_ij(2,1)]*mp[M4_ij(3,3)]-mp[M4_ij(2,3)]*mp[M4_ij(3,1)])+mp[M4_ij(1,3)]*(mp[M4_ij(2,1)]*mp[M4_ij(3,2)]-mp[M4_ij(2,2)]*mp[M4_ij(3,1)]),
                -mp[M4_ij(0,1)]*(mp[M4_ij(2,2)]*mp[M4_ij(3,3)]-mp[M4_ij(2,3)]*mp[M4_ij(3,2)])+mp[M4_ij(0,2)]*(mp[M4_ij(2,1)]*mp[M4_ij(3,3)]-mp[M4_ij(2,3)]*mp[M4_ij(3,1)])-mp[M4_ij(0,3)]*(mp[M4_ij(2,1)]*mp[M4_ij(3,2)]-mp[M4_ij(2,2)]*mp[M4_ij(3,1)]),
                mp[M4_ij(0,1)]*(mp[M4_ij(1,2)]*mp[M4_ij(3,3)]-mp[M4_ij(1,3)]*mp[M4_ij(3,2)])-mp[M4_ij(0,2)]*(mp[M4_ij(1,1)]*mp[M4_ij(3,3)]-mp[M4_ij(1,3)]*mp[M4_ij(3,1)])+mp[M4_ij(0,3)]*(mp[M4_ij(1,1)]*mp[M4_ij(3,2)]-mp[M4_ij(1,2)]*mp[M4_ij(3,1)]),
                -mp[M4_ij(0,1)]*(mp[M4_ij(1,2)]*mp[M4_ij(2,3)]-mp[M4_ij(1,3)]*mp[M4_ij(2,2)])+mp[M4_ij(0,2)]*(mp[M4_ij(1,1)]*mp[M4_ij(2,3)]-mp[M4_ij(1,3)]*mp[M4_ij(2,1)])-mp[M4_ij(0,3)]*(mp[M4_ij(1,1)]*mp[M4_ij(2,2)]-mp[M4_ij(1,2)]*mp[M4_ij(2,1)]),
                -mp[M4_ij(1,0)]*(mp[M4_ij(2,2)]*mp[M4_ij(3,3)]-mp[M4_ij(2,3)]*mp[M4_ij(3,2)])+mp[M4_ij(1,2)]*(mp[M4_ij(2,0)]*mp[M4_ij(3,3)]-mp[M4_ij(2,3)]*mp[M4_ij(3,0)])-mp[M4_ij(1,3)]*(mp[M4_ij(2,0)]*mp[M4_ij(3,2)]-mp[M4_ij(2,2)]*mp[M4_ij(3,0)]),
                mp[M4_ij(0,0)]*(mp[M4_ij(2,2)]*mp[M4_ij(3,3)]-mp[M4_ij(2,3)]*mp[M4_ij(3,2)])-mp[M4_ij(0,2)]*(mp[M4_ij(2,0)]*mp[M4_ij(3,3)]-mp[M4_ij(2,3)]*mp[M4_ij(3,0)])+mp[M4_ij(0,3)]*(mp[M4_ij(2,0)]*mp[M4_ij(3,2)]-mp[M4_ij(2,2)]*mp[M4_ij(3,0)]),
                -mp[M4_ij(0,0)]*(mp[M4_ij(1,2)]*mp[M4_ij(3,3)]-mp[M4_ij(1,3)]*mp[M4_ij(3,2)])+mp[M4_ij(0,2)]*(mp[M4_ij(1,0)]*mp[M4_ij(3,3)]-mp[M4_ij(1,3)]*mp[M4_ij(3,0)])-mp[M4_ij(0,3)]*(mp[M4_ij(1,0)]*mp[M4_ij(3,2)]-mp[M4_ij(1,2)]*mp[M4_ij(3,0)]),
                mp[M4_ij(0,0)]*(mp[M4_ij(1,2)]*mp[M4_ij(2,3)]-mp[M4_ij(1,3)]*mp[M4_ij(2,2)])-mp[M4_ij(0,2)]*(mp[M4_ij(1,0)]*mp[M4_ij(2,3)]-mp[M4_ij(1,3)]*mp[M4_ij(2,0)])+mp[M4_ij(0,3)]*(mp[M4_ij(1,0)]*mp[M4_ij(2,2)]-mp[M4_ij(1,2)]*mp[M4_ij(2,0)]),
                mp[M4_ij(1,0)]*(mp[M4_ij(2,1)]*mp[M4_ij(3,3)]-mp[M4_ij(2,3)]*mp[M4_ij(3,1)])-mp[M4_ij(1,1)]*(mp[M4_ij(2,0)]*mp[M4_ij(3,3)]-mp[M4_ij(2,3)]*mp[M4_ij(3,0)])+mp[M4_ij(1,3)]*(mp[M4_ij(2,0)]*mp[M4_ij(3,1)]-mp[M4_ij(2,1)]*mp[M4_ij(3,0)]),
                -mp[M4_ij(0,0)]*(mp[M4_ij(2,1)]*mp[M4_ij(3,3)]-mp[M4_ij(2,3)]*mp[M4_ij(3,1)])+mp[M4_ij(0,1)]*(mp[M4_ij(2,0)]*mp[M4_ij(3,3)]-mp[M4_ij(2,3)]*mp[M4_ij(3,0)])-mp[M4_ij(0,3)]*(mp[M4_ij(2,0)]*mp[M4_ij(3,1)]-mp[M4_ij(2,1)]*mp[M4_ij(3,0)]),
                mp[M4_ij(0,0)]*(mp[M4_ij(1,1)]*mp[M4_ij(3,3)]-mp[M4_ij(1,3)]*mp[M4_ij(3,1)])-mp[M4_ij(0,1)]*(mp[M4_ij(1,0)]*mp[M4_ij(3,3)]-mp[M4_ij(1,3)]*mp[M4_ij(3,0)])+mp[M4_ij(0,3)]*(mp[M4_ij(1,0)]*mp[M4_ij(3,1)]-mp[M4_ij(1,1)]*mp[M4_ij(3,0)]),
                -mp[M4_ij(0,0)]*(mp[M4_ij(1,1)]*mp[M4_ij(2,3)]-mp[M4_ij(1,3)]*mp[M4_ij(2,1)])+mp[M4_ij(0,1)]*(mp[M4_ij(1,0)]*mp[M4_ij(2,3)]-mp[M4_ij(1,3)]*mp[M4_ij(2,0)])-mp[M4_ij(0,3)]*(mp[M4_ij(1,0)]*mp[M4_ij(2,1)]-mp[M4_ij(1,1)]*mp[M4_ij(2,0)]),
                -mp[M4_ij(1,0)]*(mp[M4_ij(2,1)]*mp[M4_ij(3,2)]-mp[M4_ij(2,2)]*mp[M4_ij(3,1)])+mp[M4_ij(1,1)]*(mp[M4_ij(2,0)]*mp[M4_ij(3,2)]-mp[M4_ij(2,2)]*mp[M4_ij(3,0)])-mp[M4_ij(1,2)]*(mp[M4_ij(2,0)]*mp[M4_ij(3,1)]-mp[M4_ij(2,1)]*mp[M4_ij(3,0)]),
                mp[M4_ij(0,0)]*(mp[M4_ij(2,1)]*mp[M4_ij(3,2)]-mp[M4_ij(2,2)]*mp[M4_ij(3,1)])-mp[M4_ij(0,1)]*(mp[M4_ij(2,0)]*mp[M4_ij(3,2)]-mp[M4_ij(2,2)]*mp[M4_ij(3,0)])+mp[M4_ij(0,2)]*(mp[M4_ij(2,0)]*mp[M4_ij(3,1)]-mp[M4_ij(2,1)]*mp[M4_ij(3,0)]),
                -mp[M4_ij(0,0)]*(mp[M4_ij(1,1)]*mp[M4_ij(3,2)]-mp[M4_ij(1,2)]*mp[M4_ij(3,1)])+mp[M4_ij(0,1)]*(mp[M4_ij(1,0)]*mp[M4_ij(3,2)]-mp[M4_ij(1,2)]*mp[M4_ij(3,0)])-mp[M4_ij(0,2)]*(mp[M4_ij(1,0)]*mp[M4_ij(3,1)]-mp[M4_ij(1,1)]*mp[M4_ij(3,0)]),
                mp[M4_ij(0,0)]*(mp[M4_ij(1,1)]*mp[M4_ij(2,2)]-mp[M4_ij(1,2)]*mp[M4_ij(2,1)])-mp[M4_ij(0,1)]*(mp[M4_ij(1,0)]*mp[M4_ij(2,2)]-mp[M4_ij(1,2)]*mp[M4_ij(2,0)])+mp[M4_ij(0,2)]*(mp[M4_ij(1,0)]*mp[M4_ij(2,1)]-mp[M4_ij(1,1)]*mp[M4_ij(2,0)]));
    }

    Mat4t Mat4t:: operator!() const
    {
        return *(*this)/det();
    }

    Mat4t Mat4t::operator-() const
    {
        DT *mp=(DT *)this;

        return Mat4t(
                -mp[M4_ij(0,0)],
                -mp[M4_ij(0,1)],
                -mp[M4_ij(0,2)],
                -mp[M4_ij(0,3)],
                -mp[M4_ij(1,0)],
                -mp[M4_ij(1,1)],
                -mp[M4_ij(1,2)],
                -mp[M4_ij(1,3)],
                -mp[M4_ij(2,0)],
                -mp[M4_ij(2,1)],
                -mp[M4_ij(2,2)],
                -mp[M4_ij(2,3)],
                -mp[M4_ij(3,0)],
                -mp[M4_ij(3,1)],
                -mp[M4_ij(3,2)],
                -mp[M4_ij(3,3)]);
    }

    const Mat4t& Mat4t::operator=(const Mat4t &t)
    {
        DT *mp=(DT *)this, *tp=(DT *)&t;

        if (mp != tp)
        {
            mp[0]=tp[0];
            mp[1]=tp[1];
            mp[2]=tp[2];
            mp[3]=tp[3];
            mp[4]=tp[4];
            mp[5]=tp[5];
            mp[6]=tp[6];
            mp[7]=tp[7];
            mp[8]=tp[8];
            mp[9]=tp[9];
            mp[10]=tp[10];
            mp[11]=tp[11];
            mp[12]=tp[12];
            mp[13]=tp[13];
            mp[14]=tp[14];
            mp[15]=tp[15];
        }
        return *this;
    }

    const Mat4t& Mat4t::operator+=(const Mat4t &t)
    {
        DT *mp=(DT *)this, *tp=(DT *)&t;
        mp[0]+=tp[0];
        mp[1]+=tp[1];
        mp[2]+=tp[2];
        mp[3]+=tp[3];
        mp[4]+=tp[4];
        mp[5]+=tp[5];
        mp[6]+=tp[6];
        mp[7]+=tp[7];
        mp[8]+=tp[8];
        mp[9]+=tp[9];
        mp[10]+=tp[10];
        mp[11]+=tp[11];
        mp[12]+=tp[12];
        mp[13]+=tp[13];
        mp[14]+=tp[14];
        mp[15]+=tp[15];
        return *this;
    }

    const Mat4t& Mat4t::operator-=(const Mat4t &t)
    {
        DT *mp=(DT *)this, *tp=(DT *)&t;
        mp[0]-=tp[0];
        mp[1]-=tp[1];
        mp[2]-=tp[2];
        mp[3]-=tp[3];
        mp[4]-=tp[4];
        mp[5]-=tp[5];
        mp[6]-=tp[6];
        mp[7]-=tp[7];
        mp[8]-=tp[8];
        mp[9]-=tp[9];
        mp[10]-=tp[10];
        mp[11]-=tp[11];
        mp[12]-=tp[12];
        mp[13]-=tp[13];
        mp[14]-=tp[14];
        mp[15]-=tp[15];
        return *this;
    }

    const Mat4t& Mat4t::operator*=(const Mat4t &t)
    {
        (*this)=(*this)*t;
        return *this;
    }

    const Mat4t& Mat4t::operator/=(const Mat4t &t)
    {
        (*this)=(*this)/t;
        return *this;
    }

    const Mat4t& Mat4t::operator*=(const DT &f)
    {
        DT *mp=(DT *)this;
        mp[0]*=f;
        mp[1]*=f;
        mp[2]*=f;
        mp[3]*=f;
        mp[4]*=f;
        mp[5]*=f;
        mp[6]*=f;
        mp[7]*=f;
        mp[8]*=f;
        mp[9]*=f;
        mp[10]*=f;
        mp[11]*=f;
        mp[12]*=f;
        mp[13]*=f;
        mp[14]*=f;
        mp[15]*=f;
        return *this;
    }

    const Mat4t& Mat4t::operator/=(const DT &f)
    {
        DT *mp=(DT *)this, t=1/f;
        mp[0]*=t;
        mp[1]*=t;
        mp[2]*=t;
        mp[3]*=t;
        mp[4]*=t;
        mp[5]*=t;
        mp[6]*=t;
        mp[7]*=t;
        mp[8]*=t;
        mp[9]*=t;
        mp[10]*=t;
        mp[11]*=t;
        mp[12]*=t;
        mp[13]*=t;
        mp[14]*=t;
        mp[15]*=t;
        return *this;
    }

    const Mat4t& Mat4t::transpose()
    {
        (*this)=~(*this);
        return *this;
    }

    const Mat4t& Mat4t::adjoint()
    {
        (*this)=*(*this);
        return *this;
    }

    const Mat4t& Mat4t::invert()
    {
        (*this)=!(*this);
        return *this;
    }

    DT Mat4t::det() const
    {
        DT *mp=(DT *)this;
        return   mp[M4_ij(0,0)]*mp[M4_ij(1,1)]*mp[M4_ij(2,2)]*mp[M4_ij(3,3)]
            -mp[M4_ij(0,0)]*mp[M4_ij(1,1)]*mp[M4_ij(2,3)]*mp[M4_ij(3,2)]
            +mp[M4_ij(0,0)]*mp[M4_ij(1,2)]*mp[M4_ij(2,3)]*mp[M4_ij(3,1)]
            -mp[M4_ij(0,0)]*mp[M4_ij(1,2)]*mp[M4_ij(2,1)]*mp[M4_ij(3,3)]
            +mp[M4_ij(0,0)]*mp[M4_ij(1,3)]*mp[M4_ij(2,1)]*mp[M4_ij(3,2)]
            -mp[M4_ij(0,0)]*mp[M4_ij(1,3)]*mp[M4_ij(2,2)]*mp[M4_ij(3,1)]
            -mp[M4_ij(0,1)]*mp[M4_ij(1,2)]*mp[M4_ij(2,3)]*mp[M4_ij(3,0)]
            +mp[M4_ij(0,1)]*mp[M4_ij(1,2)]*mp[M4_ij(2,0)]*mp[M4_ij(3,3)]
            -mp[M4_ij(0,1)]*mp[M4_ij(1,3)]*mp[M4_ij(2,0)]*mp[M4_ij(3,2)]
            +mp[M4_ij(0,1)]*mp[M4_ij(1,3)]*mp[M4_ij(2,2)]*mp[M4_ij(3,0)]
            -mp[M4_ij(0,1)]*mp[M4_ij(1,0)]*mp[M4_ij(2,2)]*mp[M4_ij(3,3)]
            +mp[M4_ij(0,1)]*mp[M4_ij(1,0)]*mp[M4_ij(2,3)]*mp[M4_ij(3,2)]
            +mp[M4_ij(0,2)]*mp[M4_ij(1,3)]*mp[M4_ij(2,0)]*mp[M4_ij(3,1)]
            -mp[M4_ij(0,2)]*mp[M4_ij(1,3)]*mp[M4_ij(2,1)]*mp[M4_ij(3,0)]
            +mp[M4_ij(0,2)]*mp[M4_ij(1,0)]*mp[M4_ij(2,1)]*mp[M4_ij(3,3)]
            -mp[M4_ij(0,2)]*mp[M4_ij(1,0)]*mp[M4_ij(2,3)]*mp[M4_ij(3,1)]
            +mp[M4_ij(0,2)]*mp[M4_ij(1,1)]*mp[M4_ij(2,3)]*mp[M4_ij(3,0)]
            -mp[M4_ij(0,2)]*mp[M4_ij(1,1)]*mp[M4_ij(2,0)]*mp[M4_ij(3,3)]
            -mp[M4_ij(0,3)]*mp[M4_ij(1,0)]*mp[M4_ij(2,1)]*mp[M4_ij(3,2)]
            +mp[M4_ij(0,3)]*mp[M4_ij(1,0)]*mp[M4_ij(2,2)]*mp[M4_ij(3,1)]
            -mp[M4_ij(0,3)]*mp[M4_ij(1,1)]*mp[M4_ij(2,2)]*mp[M4_ij(3,0)]
            +mp[M4_ij(0,3)]*mp[M4_ij(1,1)]*mp[M4_ij(2,0)]*mp[M4_ij(3,2)]
            -mp[M4_ij(0,3)]*mp[M4_ij(1,2)]*mp[M4_ij(2,0)]*mp[M4_ij(3,1)]
            +mp[M4_ij(0,3)]*mp[M4_ij(1,2)]*mp[M4_ij(2,1)]*mp[M4_ij(3,0)];
    }

    void Mat4t::identity()
    {
        DT *mp=(DT *)this;
        mp[0]=1;
        mp[1]=0;
        mp[2]=0;
        mp[3]=0;
        mp[4]=0;
        mp[5]=1;
        mp[6]=0;
        mp[7]=0;
        mp[8]=0;
        mp[9]=0;
        mp[10]=1;
        mp[11]=0;
        mp[12]=0;
        mp[13]=0;
        mp[14]=0;
        mp[15]=1;
    }

    void Mat4t::rotate(const DT &angleDeg, const Vec3t &axisVec)
    {
        const DT angle=DEG2RAD(angleDeg), c=cos(angle), s=sin(angle), t=1.0-c, *axis=(DT *)&axisVec;
        (*this)*=Mat4t(
                       t*axis[0]*axis[0]+c,         t*axis[1]*axis[0]-s*axis[2], t*axis[2]*axis[0]+s*axis[1],	0,
                       t*axis[0]*axis[1]+s*axis[2], t*axis[1]*axis[1]+c,         t*axis[2]*axis[1]-s*axis[0],	0,
                       t*axis[0]*axis[2]-s*axis[1], t*axis[1]*axis[2]+s*axis[0], t*axis[2]*axis[2]+c,           0,
                       0,							0,							0,								1);
    }

    void Mat4t::rotateX(const DT &angleDeg)
    {
        const DT angle=DEG2RAD(angleDeg), c=cos(angle), s=sin(angle);
        (*this)*=Mat4t( 1, 0, 0, 0,
                        0, c,-s, 0,
                        0, s, c, 0,
                        0, 0, 0, 1);
    }

    void Mat4t::rotateY(const DT &angleDeg)
    {
        const DT angle=DEG2RAD(angleDeg), c=cos(angle), s=sin(angle);
        (*this)*=Mat4t( c, 0, s, 0,
                        0, 1, 0, 0,
                       -s, 0, c, 0,
                        0, 0, 0, 1);
    }

    void Mat4t::rotateZ(const DT &angleDeg)
    {
        const DT angle=DEG2RAD(angleDeg), c=cos(angle), s=sin(angle);
        (*this)*=Mat4t( c,-s, 0, 0,
                        s, c, 0, 0,
                        0, 0, 1, 0,
                        0, 0, 0, 1);
    }

    void Mat4t::setToRotation(const DT &angleDeg, const Vec3t &axisVec)
    {
        const DT angle=DEG2RAD(angleDeg), c=cos(angle), s=sin(angle), t=1.0-c, *axis=(DT *)&axisVec;
        DT *mp=(DT *)this;

        mp[M4_ij(0,0)]=t*axis[0]*axis[0]+c;
        mp[M4_ij(0,1)]=t*axis[0]*axis[1]-s*axis[2];
        mp[M4_ij(0,2)]=t*axis[0]*axis[2]+s*axis[1];
        mp[M4_ij(0,3)]=0;
        mp[M4_ij(1,0)]=t*axis[1]*axis[0]+s*axis[2];
        mp[M4_ij(1,1)]=t*axis[1]*axis[1]+c;
        mp[M4_ij(1,2)]=t*axis[1]*axis[2]-s*axis[0];
        mp[M4_ij(1,3)]=0;
        mp[M4_ij(2,0)]=t*axis[2]*axis[0]-s*axis[1];
        mp[M4_ij(2,1)]=t*axis[2]*axis[1]+s*axis[0];
        mp[M4_ij(2,2)]=t*axis[2]*axis[2]+c;
        mp[M4_ij(2,3)]=0;
        mp[M4_ij(3,0)]=0;
        mp[M4_ij(3,1)]=0;
        mp[M4_ij(3,2)]=0;
        mp[M4_ij(3,3)]=1;
    }

    void Mat4t::translate(const Vec3t &t)
    {
        (*this)*=Mat4t(1.0,  0.0,  0.0, t[0],
                       0.0,  1.0,  0.0, t[1],
                       0.0,  0.0,  1.0, t[2],
                       0.0,  0.0,  0.0, 1.0);
    }

    void Mat4t::setToTranslation(const Vec3t &t)
    {
        DT *mp=(DT *)this;

        mp[M4_ij(0,0)]=1;
        mp[M4_ij(0,1)]=0;
        mp[M4_ij(0,2)]=0;
        mp[M4_ij(0,3)]=t[0];
        mp[M4_ij(1,0)]=0;
        mp[M4_ij(1,1)]=1;
        mp[M4_ij(1,2)]=0;
        mp[M4_ij(1,3)]=t[1];
        mp[M4_ij(2,0)]=0;
        mp[M4_ij(2,1)]=0;
        mp[M4_ij(2,2)]=1;
        mp[M4_ij(2,3)]=t[2];
        mp[M4_ij(3,0)]=0;
        mp[M4_ij(3,1)]=0;
        mp[M4_ij(3,2)]=0;
        mp[M4_ij(3,3)]=1;
    }

    void Mat4t::scale(const Vec3t &s)
    {
        (*this)*=Mat4t(
                       s[0], 0.0,  0.0,  0.0,
                       0.0,  s[1], 0.0,  0.0,
                       0.0,  0.0,  s[2], 0.0,
                       0.0,  0.0,  0.0,  1.0);
    }

    void Mat4t::setToScale(const Vec3t &s)
    {
        DT *mp=(DT *)this;

        mp[M4_ij(0,0)]=s[0];
        mp[M4_ij(0,1)]=0;
        mp[M4_ij(0,2)]=0;
        mp[M4_ij(0,3)]=0;
        mp[M4_ij(1,0)]=0;
        mp[M4_ij(1,1)]=s[1];
        mp[M4_ij(1,2)]=0;
        mp[M4_ij(1,3)]=0;
        mp[M4_ij(2,0)]=0;
        mp[M4_ij(2,1)]=0;
        mp[M4_ij(2,2)]=s[2];
        mp[M4_ij(2,3)]=0;
        mp[M4_ij(3,0)]=0;
        mp[M4_ij(3,1)]=0;
        mp[M4_ij(3,2)]=0;
        mp[M4_ij(3,3)]=1;
    }
#undef DT
}
