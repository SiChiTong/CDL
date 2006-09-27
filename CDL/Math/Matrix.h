#ifndef __CDL_MATRIX_H__
#define __CDL_MATRIX_H__

#include <CDL/Math/Vector.h>

namespace CDL
{
#define DT DefType
#ifdef minor
#undef minor
#endif

    class DLL_API Mat2t
    {
        private:
            Vec2t m[2];

        public:
            Mat2t ();
            Mat2t (const DT *);
            Mat2t (const Mat2t &);
            Mat2t (const Vec2t &, const Vec2t &);
            Mat2t (const DT &, const DT &, const DT &, const DT &);
            const DT &minor(const int &, const int &) const;
            Vec2t & operator[] (const int &);
            const Vec2t &operator[] (const int &) const;
            Mat2t operator+(const Mat2t &) const;
            Mat2t operator-(const Mat2t &) const;
            Mat2t operator*(const Mat2t &) const;
            Mat2t operator/(const Mat2t &) const;
            Mat2t operator*(const DT &) const;
            Mat2t operator/(const DT &) const;
            Mat2t operator~() const;
            Mat2t operator*() const;
            Mat2t operator!() const;
            Mat2t operator-() const;
            const Mat2t &operator= (const Mat2t &);
            const Mat2t &operator+= (const Mat2t &);
            const Mat2t &operator-= (const Mat2t &);
            const Mat2t &operator*= (const Mat2t &);
            const Mat2t &operator/= (const Mat2t &);
            const Mat2t &operator*= (const DT &);
            const Mat2t &operator/= (const DT &);
            const Mat2t &transpose ();
            const Mat2t &adjoint ();
            const Mat2t &invert ();
            DT det () const;

            void identity ();
            void rotate (const DT &);
            void scale (const Vec2t &);
            void translate (const DT &);
            void setToRotation(const DT &);
            void setToTranslation(const DT &);
            void setToScale(const Vec2t &);
    };

    class DLL_API Mat3t
    {
        private:
            Vec3t m[3];

        public:
            Mat3t ();
            Mat3t (const DT *);
            Mat3t (const Mat2t &);
            Mat3t (const Mat3t &);
            Mat3t (const Vec3t &, const Vec3t &, const Vec3t &);
            Mat3t (const DT &, const DT &, const DT &, const DT &, const DT &,
                   const DT &, const DT &, const DT &, const DT &);
            Mat2t minor(const int &, const int &) const;
            Vec3t & operator[] (const int &);
            const Vec3t & operator[] (const int &) const;
            Mat3t operator+(const Mat3t &) const;
            Mat3t operator-(const Mat3t &) const;
            Mat3t operator*(const Mat3t &) const;
            Mat3t operator/(const Mat3t &) const;
            Mat3t operator*(const DT &) const;
            Mat3t operator/(const DT &) const;
            Mat3t operator~() const;
            Mat3t operator*() const;
            Mat3t operator!() const;
            Mat3t operator-() const;
            const Mat3t &operator=(const Mat3t &);
            const Mat3t &operator+=(const Mat3t &);
            const Mat3t &operator-=(const Mat3t &);
            const Mat3t &operator*=(const Mat3t &);
            const Mat3t &operator/=(const Mat3t &);
            const Mat3t &operator*=(const DT &);
            const Mat3t &operator/=(const DT &);
            const Mat3t &transpose ();
            const Mat3t &adjoint ();
            const Mat3t &invert ();
            DT det () const;

            void identity ();
            void rotate (const DT &, const Vec3t &);
            void rotateX(const DT &);
            void rotateY(const DT &);
            void rotateZ(const DT &);
            void scale (const Vec3t &);
            void translate (const Vec2t &);
            void setToRotation(const DT &, const Vec3t &);
            void setToTranslation(const Vec2t &);
            void setToScale(const Vec3t &);
    };

    class DLL_API Mat4t
    {
        private:
            Vec4t m[4];

        public:
            Mat4t ();
            Mat4t (const DT *);
            Mat4t (const Mat4t &);
            Mat4t (const Mat3t &);
            Mat4t (const Vec4t &, const Vec4t &, const Vec4t &, const Vec4t &);
            Mat4t (const DT &, const DT &, const DT &,
                   const DT &, const DT &, const DT &,
                   const DT &, const DT &, const DT &, const DT &, const DT &,
                   const DT &, const DT &, const DT &, const DT &, const DT &);
            Mat3t minor(const int &, const int &) const;
            Vec4t & operator[] (const int &);
            const Vec4t & operator[] (const int &) const;
            Mat4t operator+(const Mat4t &) const;
            Mat4t operator-(const Mat4t &) const;
            Mat4t operator*(const Mat4t &) const;
            Mat4t operator/(const Mat4t &) const;
            Mat4t operator*(const DT &) const;
            Mat4t operator/(const DT &) const;
            Mat4t operator~() const;
            Mat4t operator*() const;
            Mat4t operator!() const;
            Mat4t operator-() const;
            const Mat4t &operator=(const Mat4t &);
            const Mat4t &operator+=(const Mat4t &);
            const Mat4t &operator-=(const Mat4t &);
            const Mat4t &operator*=(const Mat4t &);
            const Mat4t &operator/=(const Mat4t &);
            const Mat4t &operator*=(const DT &);
            const Mat4t &operator/=(const DT &);
            const Mat4t &transpose ();
            const Mat4t &adjoint ();
            const Mat4t &invert ();
            DT det () const;

            void identity ();
            void rotate (const DT &, const Vec3t &);
            void rotateX(const DT &);
            void rotateY(const DT &);
            void rotateZ(const DT &);
            void scale (const Vec3t &);
            void translate (const Vec3t &);
            void setToRotation(const DT &, const Vec3t &);
            void setToTranslation(const Vec3t &);
            void setToScale(const Vec3t &);
    };

    DLL_API DT    DLL_CALLCONV operator*(const DT &, const Mat2t &);
    DLL_API Vec2t DLL_CALLCONV operator*(const Vec2t &, const Mat2t &);
    DLL_API Vec2t DLL_CALLCONV operator*(const Vec2t &, const Mat3t &);
    DLL_API Vec3t DLL_CALLCONV operator*(const Vec3t &, const Mat3t &);
    DLL_API Vec3t DLL_CALLCONV operator*(const Vec3t &, const Mat4t &);
    DLL_API Vec4t DLL_CALLCONV operator*(const Vec4t &, const Mat4t &);
    DLL_API Mat3t DLL_CALLCONV star(const Vec3t &);
#undef DT

}
#endif// __CDL_MATRIX_H__
