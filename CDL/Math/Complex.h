#ifndef __CDL_COMPLEX_H__
#define __CDL_COMPLEX_H__

#include <CDL/defs.h>

namespace CDL
{
#undef Complex

    class DLL_API Complex
    {
        private:
            DefType m_c[2];

        public:
            Complex();
            Complex(const Complex&);
            Complex(const DefType *);
            Complex(const DefType &, const DefType &);
            const DefType &getReal() const;
            void    setReal(const DefType &);
            const DefType &getImag() const;
            void    setImag(const DefType &);
            Complex  operator~() const;
            Complex  operator-() const;
            bool    operator==(const Complex&) const;
            bool    operator!=(const Complex&) const;
            Complex operator+(const Complex&) const;
            Complex operator-(const Complex&) const;
            Complex operator*(const Complex&) const;
            Complex operator*(const DefType&) const;
            Complex operator/(const DefType&) const;
            const Complex &operator=(const Complex&);
            const Complex &operator+=(const Complex&);
            const Complex &operator-=(const Complex&);
            const Complex &operator*=(const Complex&);
            const Complex &operator*=(const DefType&);
            const Complex &operator/=(const DefType&);
            const Complex &normalize();
            const Complex &conjugate();
            DefType  abs()    const;
            DefType  angle()  const;
            DefType  norm()   const;
            DefType  length() const;
    };
}

#endif//__CDL_COMPLEX_H__
