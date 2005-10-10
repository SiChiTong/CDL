#ifndef __CDL_QUATERNION_H__
#define __CDL_QUATERNION_H__

#include <CDL/Math/Math.h>
#include <CDL/Math/Vector.h>
#include <CDL/Math/Matrix.h>

namespace CDL
{
    class DLL_API Quaternion
    {
        private:
            DefType q[4];

        public:
            Quaternion();
            Quaternion(const Quaternion&);
            Quaternion(const DefType *);
            Quaternion(const DefType &, const DefType &, const DefType &, const DefType &);
            DefType       &operator[](const size_t &);
            const DefType &operator[](const size_t &) const;
            Quaternion slerp(const Quaternion &, const DefType &) const;
            Quaternion operator~() const;
            Quaternion operator!() const;
            Quaternion operator-() const;
            bool       operator==(const Quaternion&) const;
            bool       operator!=(const Quaternion&) const;
            Quaternion operator+(const Quaternion&) const;
            Quaternion operator-(const Quaternion&) const;
            Quaternion operator*(const Quaternion&) const;
            Quaternion operator/(const Quaternion&) const;
            Quaternion operator*(const DefType&) const;
            Quaternion operator/(const DefType&) const;
            Vec3t      operator*(const Vec3t &) const; // rota al vector
            const Quaternion &operator=(const Quaternion&);
            const Quaternion &operator+=(const Quaternion&);
            const Quaternion &operator-=(const Quaternion&);
            const Quaternion &operator*=(const Quaternion&);
            const Quaternion &operator/=(const Quaternion&);
            const Quaternion &operator*=(const DefType&);
            const Quaternion &operator/=(const DefType&);
			const Quaternion &fromAxis(const Vec3t &, const DefType &);
			const Quaternion &fromEuler(const Vec3t &);
			const Quaternion &fromMatrix(const Mat3t &);
            const Quaternion &rotate(const Vec3t &, const DefType &);
            const Quaternion &rotateX(const DefType &);
            const Quaternion &rotateY(const DefType &);
            const Quaternion &rotateZ(const DefType &);
            const Quaternion &normalize();
            const Quaternion &conjugate();
            const Quaternion &invert();
			void toMatrix(Mat3t &) const;
			void toMatrix(Mat4t &) const;
            DefType norm()   const;
            DefType length() const;
			DefType angle()  const;
			Vec3t   axis()   const;
    };

    typedef Quaternion Quatt;

    DefType dot(const Quatt &, const Quatt &);
    Quaternion operator*(const Vec3t &, const Quaternion &);
}

#endif//__CDL_QUATERNION_H__
