#include <CDL/Math/Complex.h>

namespace CDL
{
    #define REAL m_c[0]
    #define IMAG m_c[1]

    Complex::Complex()
    {
        REAL=DefType(0);
        IMAG=DefType(0);
    }

    Complex::Complex(const Complex &c)
    {
        REAL=c.REAL;
        IMAG=c.IMAG;
    }

    Complex::Complex(const DefType *p)
    {
        REAL=*(p+0);
        IMAG=*(p+1);
    }

    Complex::Complex(const DefType &real, const DefType &imag)
    {
        REAL=real;
        IMAG=imag;
    }

    bool    Complex::operator==(const Complex &c) const
    {
        return REAL == c.REAL && IMAG == c.IMAG;
    }

    bool    Complex::operator!=(const Complex &c) const
    {
        return REAL != c.REAL || IMAG != c.IMAG;
    }

    Complex Complex::operator+(const Complex &c) const
    {
        return Complex(REAL+c.REAL, IMAG+c.IMAG);
    }

    Complex Complex::operator-(const Complex &c) const
    {
        return Complex(REAL-c.REAL, IMAG-c.IMAG);
    }

    Complex Complex::operator*(const Complex &c) const
    {
        return Complex(REAL*c.REAL-IMAG*c.IMAG, REAL*c.IMAG+IMAG*c.REAL);
    }

    Complex Complex::operator*(const DefType &f) const
    {
        return Complex(REAL*f, IMAG*f);
    }

    Complex Complex::operator/(const DefType &f) const
    {
		const DefType t=1.0/f;
        return Complex(REAL*t, IMAG*t);
    }

    Complex Complex::operator~() const
    {
        return Complex(REAL, -IMAG);
    }

    Complex Complex::operator-() const
    {
        return Complex(-REAL,-IMAG);
    }

    const Complex &Complex::operator=(const Complex &c)
    {
        if (this != &c)
        {
            REAL=c.REAL;
            IMAG=c.IMAG;
        }
        return *this;
    }

    const Complex& Complex::operator+=(const Complex &c)
    {
        REAL+=c.REAL;
        IMAG+=c.IMAG;
        return *this;
    }

    const Complex& Complex::operator-=(const Complex &c)
    {
        REAL-=c.REAL;
        IMAG-=c.IMAG;
        return *this;
    }

    const Complex& Complex::operator*=(const Complex &c)
    {
        *this=(*this)*c;
        return *this;
    }

    const Complex& Complex::operator*=(const DefType &f)
    {
        REAL*=f;
        IMAG*=f;
        return *this;
    }

    const Complex& Complex::operator/=(const DefType &f)
    {
		const DefType t=1.0/f;
        REAL*=t;
        IMAG*=t;
        return *this;
    }

    const Complex& Complex::normalize()
    {
        DefType l=1.0/length();
        REAL*=l;
        IMAG*=l;
        return *this;
    }

    const Complex& Complex::conjugate()
    {
        IMAG=-IMAG;
        return *this;
    }

    DefType Complex::abs() const
    {
        return hypot(REAL,IMAG);
    }

    DefType Complex::angle() const
    {
        return atan2(IMAG,REAL);
    }

    const DefType &Complex::getReal() const
    {
        return REAL;
    }

    const DefType &Complex::getImag() const
    {
        return IMAG;
    }

    void    Complex::setReal(const DefType &r)
    {
        REAL=r;
    }

    void    Complex::setImag(const DefType &i)
    {
        IMAG=i;
    }

    DefType Complex::norm() const
    {
        return REAL*REAL+IMAG*IMAG;
    }

    DefType Complex::length() const
    {
        return sqrt(REAL*REAL+IMAG*IMAG);
    }
}
