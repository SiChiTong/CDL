#include <CDL/Math/Quaternion.h>

namespace CDL
{
    static const size_t lut[3]={1,2,0};

#define X q[0]
#define Y q[1]
#define Z q[2]
#define W q[3]

    DefType dot(const Quaternion &q1, const Quaternion &q2)
    {
        const DefType *p=(DefType *)&q1, *q=(DefType *)&q2;
        return p[0]*X+p[1]*Y+p[2]*Z+p[3]*W;
    }

    Quaternion operator*(const Vec3t &v1, const Quaternion &q1)
    {
        const DefType *q=(DefType *)&v1, *x=(DefType *)&q1;
        return Quaternion(
                 X*x[3]+Y*x[2]-Z*x[1],
                 Y*x[3]+Z*x[0]-X*x[2],
                 Z*x[3]+X*x[1]-Y*x[0],
                -X*x[0]-Y*x[1]-Z*x[2]);
    }

    Quaternion::Quaternion()
    {
        X=DefType(0);
        Y=DefType(0);
        Z=DefType(0);
        W=DefType(1);
    }

    Quaternion::Quaternion(const Quaternion &q1)
    {
        X=q1.X;
        Y=q1.Y;
        Z=q1.Z;
        W=q1.W;
    }

    Quaternion::Quaternion(const DefType *p)
    {
        X=*(p+0);
        Y=*(p+1);
        Z=*(p+2);
        W=*(p+3);
    }

    Quaternion::Quaternion(const DefType &x, const DefType &y, const DefType &z, const DefType &w)
    {
        X=x;
        Y=y;
        Z=z;
        W=w;
    }

    DefType &Quaternion::operator[](const size_t &i)
    {
        return q[i];
    }

    const DefType &Quaternion::operator[](const size_t &i) const
    {
        return q[i];
    }

    Quaternion Quaternion::slerp(const Quaternion &qx, const DefType &t) const
    {
        Quaternion q1(*this), q2(qx);
        q1.normalize();
        q2.normalize();

        const DefType angle=acos(dot(q1,q2));
        const DefType s=sin(angle);

        if (!equal(s,DefType(0)))
        {
            const DefType is=1/s;
            return q1*(sin((1-t)*angle)*is)+q2*(sin(t*angle)*is);
        }
        else
            return q1*t+q2*(1-t);
    }

    bool Quaternion::operator==(const Quaternion &q1) const
    {
        return X == q1.X && Y == q1.Y && Z == q1.Z && W == q1.W;
    }

    bool Quaternion::operator!=(const Quaternion &q1) const
    {
        return X != q1.X || Y != q1.Y || Z != q1.Z || W != q1.W;
    }

    Quaternion Quaternion::operator+(const Quaternion &q1) const
    {
        return Quaternion(X+q1.X, Y+q1.Y, Z+q1.Z, W+q1.W);
    }

    Quaternion Quaternion::operator-(const Quaternion &q1) const
    {
        return Quaternion(X-q1.X, Y-q1.Y, Z-q1.Z, W-q1.W);
    }

    Quaternion Quaternion::operator*(const Quaternion &q1) const
    {
        return Quaternion(
                W*q1.X+X*q1.W+Y*q1.Z-Z*q1.Y,
                W*q1.Y+Y*q1.W+Z*q1.X-X*q1.Z,
                W*q1.Z+Z*q1.W+X*q1.Y-Y*q1.X,
                W*q1.W-X*q1.X-Y*q1.Y-Z*q1.Z);
    }

    Quaternion Quaternion::operator/(const Quaternion &q1) const
    {
        return (*this)*!q1;
    }

    Vec3t Quaternion::operator*(const Vec3t &vec) const // rota al vector
    {
        const DefType *v=(DefType *)&vec;
        const DefType x=W*v[0]+Y*v[2]-Z*v[1];
        const DefType y=W*v[1]+Z*v[0]-X*v[2];
        const DefType z=W*v[2]+X*v[1]-Y*v[0];
        const DefType w=X*v[0]+Y*v[1]+Z*v[2];

        return Vec3t(x*W+w*X-y*Z+z*Y, y*W+w*Y-z*X+x*Z, z*W+w*Z-x*Y+y*X);
    }

    Quaternion Quaternion::operator*(const DefType &f) const
    {
        return Quaternion(X*f, Y*f, Z*f, W*f);
    }

    Quaternion Quaternion::operator/(const DefType &f) const
    {
        const DefType t=1.0/f;
        return Quaternion(X*t, Y*t, Z*t, W*t);
    }

    Quaternion Quaternion::operator~() const
    {
        return Quaternion(-X, -Y, -Z, W);
    }

    Quaternion Quaternion::operator!() const
    {
        DefType n=-1.0/norm();
        return Quaternion(X*n, Y*n, Z*n, -W*n);      // ~(*this)/norm();
    }

    Quaternion Quaternion::operator-() const
    {
        return Quaternion(-X, -Y, -Z, -W);
    }

    const Quaternion& Quaternion::operator=(const Quaternion &q1)
    {
        if (this != &q1)
        {
            X=q1.X;
            Y=q1.Y;
            Z=q1.Z;
            W=q1.W;
        }
        return *this;
    }

    const Quaternion& Quaternion::operator+=(const Quaternion &q1)
    {
        X+=q1.X;
        Y+=q1.Y;
        Z+=q1.Z;
        W+=q1.W;
        return *this;
    }

    const Quaternion& Quaternion::operator-=(const Quaternion &q1)
    {
        X-=q1.X;
        Y-=q1.Y;
        Z-=q1.Z;
        W-=q1.W;
        return *this;
    }

    const Quaternion& Quaternion::operator*=(const Quaternion &q1)
    {
        *this=(*this)*q1;
        return *this;
    }

    const Quaternion& Quaternion::operator/=(const Quaternion &q1)
    {
        *this=(*this)/q1;
        return *this;
    }

    const Quaternion& Quaternion::operator*=(const DefType &f)
    {
        X*=f;
        Y*=f;
        Z*=f;
        W*=f;
        return *this;
    }

    const Quaternion& Quaternion::operator/=(const DefType &f)
    {
        const DefType t=1.0/f;
        X*=t;
        Y*=t;
        Z*=t;
        W*=t;
        return *this;
    }

    const Quaternion& Quaternion::fromAxis(const Vec3t &v, const DefType &angle)
    {
        const DefType ang=DEG2RAD(angle)*0.5f, c=cos(ang), s=sin(ang), *axis=(DefType *)&v;

        X=axis[0]*s;
        Y=axis[1]*s;
        Z=axis[2]*s;
        W=c;

        return *this;
    }

    const Quaternion& Quaternion::fromEuler(const Vec3t &v)
    {
        const DefType *euler=(DefType *)&v;
        const DefType x=DEG2RAD(euler[0])*0.5f, y=DEG2RAD(euler[1])*0.5f, z=DEG2RAD(euler[2])*0.5f;
        const DefType c1=cos(x), c2=cos(y), c3=cos(z);
        const DefType s1=sin(x), s2=sin(y), s3=sin(z);
        const DefType s2c3=s2*c3, c2s3=c2*s3, c2c3=c2*c3, s2s3=s2*s3;

        X = s1*s2c3 + c1*c2s3;
        Y = s1*c2c3 + c1*s2s3;
        Z = c1*s2c3 - s1*c2s3;
        W = c1*c2c3 - s1*s2s3;

        return *this;
    }

    const Quaternion &Quaternion::fromMatrix(const Mat3t &mat)
    {
        const DefType *m=(DefType *)&mat;
        const DefType trace = m[M3_ij(0,0)] + m[M3_ij(1,1)] + m[M3_ij(2,2)];
        DefType root;

        if (trace > 0)
        {
            root = sqrt(trace + 1);
            W = 0.5*root;
            root = 0.5/root;
            X = (m[M3_ij(2,1)] - m[M3_ij(1,2)]) * root;
            Y = (m[M3_ij(0,2)] - m[M3_ij(2,0)]) * root;
            Z = (m[M3_ij(1,0)] - m[M3_ij(0,1)]) * root;
        }
        else
        {
            size_t i = 0;
            if (m[M3_ij(1,1)] > m[M3_ij(i,i)]) i=1;
            if (m[M3_ij(2,2)] > m[M3_ij(i,i)]) i=2;
            size_t j = lut[i], k = lut[j];

            root = sqrt(m[M3_ij(i,i)] - m[M3_ij(j,j)] - m[M3_ij(k,k)] + 1);
            q[i] = 0.5*root;
            root = 0.5/root;
            W = (m[M3_ij(k,j)] - m[M3_ij(j,k)]) * root;
            q[j] = (m[M3_ij(j,i)] + m[M3_ij(i,j)]) * root;
            q[k] = (m[M3_ij(k,i)] + m[M3_ij(i,k)]) * root;
        }

        return *this;
    }

    const Quaternion &Quaternion::rotate(const Vec3t &v, const DefType &angle)
    {
        const DefType ang=DEG2RAD(angle)*0.5f, c=cos(ang), s=sin(ang), *axis=(DefType *)&v;
        *this=(*this)*Quaternion(axis[0]*s, axis[1]*s, axis[2]*s, c);
    }

    const Quaternion &Quaternion::rotateX(const DefType &angle)
    {
        const DefType ang=DEG2RAD(angle)*0.5f, c=cos(ang), s=sin(ang);
        *this=(*this)*Quaternion(s,0,0,c);
    }

    const Quaternion &Quaternion::rotateY(const DefType &angle)
    {
        const DefType ang=DEG2RAD(angle)*0.5f, c=cos(ang), s=sin(ang);
        *this=(*this)*Quaternion(0,s,0,c);
    }

    const Quaternion &Quaternion::rotateZ(const DefType &angle)
    {
        const DefType ang=DEG2RAD(angle)*0.5f, c=cos(ang), s=sin(ang);
        *this=(*this)*Quaternion(0,0,s,c);
    }

    const Quaternion& Quaternion::normalize()
    {
        DefType l=norm();

        if (l != 1.0f)
        {
            l=1.0/sqrtf(l);
            X*=l;
            Y*=l;
            Z*=l;
            W*=l;
        }

        return *this;
    }

    const Quaternion& Quaternion::conjugate()
    {
        X=-X;
        Y=-Y;
        Z=-Z;
        return *this;
    }

    const Quaternion& Quaternion::invert()
    {
        const DefType n=-1.0/norm();
        X*=n;
        Y*=n;
        Z*=n;
        W*=-n;
        return *this;
    }

    void Quaternion::toMatrix(Mat3t &mat) const
    {
        DefType *m=(DefType *)&mat;
        const DefType xx=X*X, xy=X*Y, xz=X*Z, xw=X*W;
        const DefType yy=Y*Y, yz=Y*Z, yw=Y*W;
        const DefType zz=Z*Z, zw=Z*W;

        m[M3_ij(0,0)] =1-2*(yy+zz);
        m[M3_ij(0,1)] =  2*(xy-zw);
        m[M3_ij(0,2)] =  2*(xz+yw);
        m[M3_ij(1,0)] =  2*(xy+zw);
        m[M3_ij(1,1)] =1-2*(xx+zz);
        m[M3_ij(1,2)] =  2*(yz-xw);
        m[M3_ij(2,0)] =  2*(xz-yw);
        m[M3_ij(2,1)] =  2*(yz+xw);
        m[M3_ij(2,2)] =1-2*(xx+yy);
    }

    void Quaternion::toMatrix(Mat4t &mat) const
    {
        DefType *m=(DefType *)&mat;
        const DefType xx=X*X, xy=X*Y, xz=X*Z, xw=X*W;
        const DefType yy=Y*Y, yz=Y*Z, yw=Y*W;
        const DefType zz=Z*Z, zw=Z*W;

        m[M4_ij(0,0)] =1-2*(yy+zz);
        m[M4_ij(0,1)] =  2*(xy-zw);
        m[M4_ij(0,2)] =  2*(xz+yw);
        m[M4_ij(1,0)] =  2*(xy+zw);
        m[M4_ij(1,1)] =1-2*(xx+zz);
        m[M4_ij(1,2)] =  2*(yz-xw);
        m[M4_ij(2,0)] =  2*(xz-yw);
        m[M4_ij(2,1)] =  2*(yz+xw);
        m[M4_ij(2,2)] =1-2*(xx+yy);

        m[M4_ij(3,0)]=m[M4_ij(3,1)]=m[M4_ij(3,2)]=m[M4_ij(0,3)]=m[M4_ij(1,3)]=m[M4_ij(2,3)]=0;
        m[M4_ij(3,3)]=1;
    }
    DefType Quaternion::det() const
    {
         const DefType d=X*X+Y*Y+Z*Z+W*W;
         return d*d;
    }

    DefType Quaternion::norm() const
    {
        return X*X+Y*Y+Z*Z+W*W;
    }

    DefType Quaternion::length() const
    {
        return sqrt(X*X+Y*Y+Z*Z+W*W);
    }

    DefType Quaternion::angle() const
    {
        return RAD2DEG(2.0f*acos(W));
    }

    Vec3t  Quaternion::axis() const
    {
        const DefType scale=1.0/sqrt(X*X+Y*Y+Z*Z);
        return Vec3t(X*scale, Y*scale, Z*scale);
    }
}
