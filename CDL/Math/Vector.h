#ifndef __CDL_VECTOR_H__
#define __CDL_VECTOR_H__

#include <CDL/defs.h>

namespace CDL
{
    #define DT DefType
    class DLL_API Vector
    {
        private:
            DT    *m_v;
            size_t m_length;

        public:
            Vector(const size_t &length=0);
            Vector(const size_t &length, const DT *);
            Vector(const Vector &);
            virtual ~Vector();
            Vector subVector(const size_t &) const;
            DT       &operator[](const size_t &);
            const DT &operator[](const size_t &) const;
            Vector lerp(const Vector &, const DT &) const;
            Vector operator-() const;
            bool   operator==(const Vector &) const;
            bool   operator!=(const Vector &) const;
            Vector operator+(const Vector &) const;
            Vector operator-(const Vector &) const;
            Vector operator*(const Vector &) const;
            Vector operator*(const DT &) const;
            Vector operator/(const DT &) const;
            const Vector  &operator=(const Vector &);
            const Vector &operator+=(const Vector &);
            const Vector &operator-=(const Vector &);
            const Vector &operator*=(const Vector &);
            const Vector &operator*=(const DT &);
            const Vector &operator/=(const DT &);
            const Vector &normalize();
            const size_t &getLength() const {return m_length;}
            Vector project(const Vector &) const;
            DT distance(const Vector &) const;
            DT distanceSq(const Vector &) const;
            DT length() const;
            DT norm() const;
            void reset();
    };

    class DLL_API Vec2t
    {
        private:
            DT v[2];

        public:
            Vec2t();
            Vec2t(const DT*);
            Vec2t(const DT&, const DT&);
            Vec2t(const Vec2t&);
            const DT& subVector(const size_t &i=1) const;
            DT&       operator[](const size_t &);
            const DT& operator[](const size_t &) const;
            Vec2t lerp(const Vec2t&, const DT&) const;
            Vec2t operator-() const;
            bool  operator==(const Vec2t&) const;
            bool  operator!=(const Vec2t&) const;
            Vec2t operator+(const Vec2t&) const;
            Vec2t operator-(const Vec2t&) const;
            Vec2t operator*(const Vec2t&) const;
            Vec2t operator*(const DT&) const;
            Vec2t operator/(const DT&) const;
            const Vec2t &operator=(const Vec2t&);
            const Vec2t &operator+=(const Vec2t&);
            const Vec2t &operator-=(const Vec2t&);
            const Vec2t &operator*=(const Vec2t&);
            const Vec2t &operator*=(const DT&);
            const Vec2t &operator/=(const DT&);
            const Vec2t &normalize();
            Vec2t project(const Vec2t &) const;
            DT distance(const Vec2t&) const;
            DT distanceSq(const Vec2t&) const;
            DT length() const;
            DT norm()   const;
            void reset();
    };

    class DLL_API Vec3t
    {
        private:
            DT v[3];

        public:
            Vec3t();
            Vec3t(const DT*);
            Vec3t(const DT&, const DT&, const DT&);
            Vec3t(const Vec2t&);
            Vec3t(const Vec3t&);
            Vec2t subVector(const size_t &i=2) const;
            DT&       operator[](const size_t &);
            const DT& operator[](const size_t &) const;
            Vec3t lerp(const Vec3t&, const DT&) const;
            Vec3t slerp(const Vec3t&, const DT&) const;
            Vec3t operator-() const;
            bool  operator==(const Vec3t&) const;
            bool  operator!=(const Vec3t&) const;
            Vec3t operator+(const Vec3t&) const;
            Vec3t operator-(const Vec3t&) const;
            Vec3t operator*(const Vec3t&) const;
            Vec3t operator*(const DT&) const;
            Vec3t operator/(const DT&) const;
            const Vec3t &operator=(const Vec2t&);
            const Vec3t &operator=(const Vec3t&);
            const Vec3t &operator+=(const Vec3t&);
            const Vec3t &operator-=(const Vec3t&);
            const Vec3t &operator*=(const Vec3t&);
            const Vec3t &operator*=(const DT&);
            const Vec3t &operator/=(const DT&);
            const Vec3t &normalize();
            Vec3t project(const Vec3t &) const;
            DT distance(const Vec3t&) const;
            DT distanceSq(const Vec3t&) const;
            DT length() const;
            DT norm()   const;
            void reset();
    };

    class DLL_API Vec4t
    {
        private:
            DT v[4];

        public:
            Vec4t();
            Vec4t(const DT*);
            Vec4t(const DT&, const DT&, const DT&, const DT&);
            Vec4t(const Vec3t&);
            Vec4t(const Vec4t&);
            Vec3t subVector(const size_t &i=3) const;
            DT&       operator[](const size_t &);
            const DT& operator[](const size_t &) const;
            Vec4t lerp(const Vec4t&, const DT&) const;
            Vec4t operator-() const;
            bool  operator==(const Vec4t&) const;
            bool  operator!=(const Vec4t&) const;
            Vec4t operator+(const Vec4t&) const;
            Vec4t operator-(const Vec4t&) const;
            Vec4t operator*(const Vec4t&) const;
            Vec4t operator*(const DT&) const;
            Vec4t operator/(const DT&) const;
            const Vec4t &operator=(const Vec3t&);
            const Vec4t &operator=(const Vec4t&);
            const Vec4t &operator+=(const Vec4t&);
            const Vec4t &operator-=(const Vec4t&);
            const Vec4t &operator*=(const Vec4t&);
            const Vec4t &operator*=(const DT&);
            const Vec4t &operator/=(const DT&);
            const Vec4t &normalize();
            Vec4t project(const Vec4t &) const;
            DT distance(const Vec4t&) const;
            DT distanceSq(const Vec4t&) const;
            DT length() const;
            DT norm()   const;
            void reset();
    };

    DLL_API DT DLL_CALLCONV dot(const Vector &, const Vector &);
    DLL_API DT DLL_CALLCONV dot(const Vec2t &, const Vec2t &);
    DLL_API DT DLL_CALLCONV dot(const Vec3t &, const Vec3t &);
    DLL_API DT DLL_CALLCONV dot(const Vec4t &, const Vec4t &);
    DLL_API DT DLL_CALLCONV area(const Vec2t &, const Vec2t &, const Vec2t &);
    DLL_API Vec3t DLL_CALLCONV cross(const Vec3t &, const Vec3t &);
    DLL_API Vec4t DLL_CALLCONV cross(const Vec4t &, const Vec4t &);
    DLL_API DT DLL_CALLCONV angle(const Vector &, const Vector &);
    DLL_API DT DLL_CALLCONV angle(const Vec2t &, const Vec2t &);
    DLL_API DT DLL_CALLCONV angle(const Vec3t &, const Vec3t &);
    DLL_API DT DLL_CALLCONV angle(const Vec4t &, const Vec4t &);
#undef DT
}

#endif//__CDL_VECTOR_H__
