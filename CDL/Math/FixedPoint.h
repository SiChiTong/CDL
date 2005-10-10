//========================================================================
/** @type     C/C++ Header File
 *  @file     FixedPoint.h
 *  @author   alcoco
 *  @date     
 *   Created:       15:59:03 08/03/2005
 *   Last Update:   14:58:19 15/06/2005
 */
//========================================================================

#ifndef __CDL_FIXEDPOINT_H__
#define __CDL_FIXEDPOINT_H__

#include <CDL/defs.h>

namespace CDL
{
    class DLL_API FixedPoint
    {
        public:
            static int D_PRECISION;
            typedef long long fpoint_t;

        private:
            fpoint_t m_value;
            char     m_decBits;

        public:
            FixedPoint(const int &d=D_PRECISION, const fpoint_t &v=0LL);
            FixedPoint(const int &d, const float &);
            FixedPoint(const int &d, const double &);
            FixedPoint(const FixedPoint &);
            FixedPoint(const float &);
            FixedPoint(const double &);
            const FixedPoint &operator=(const float &);
            const FixedPoint &operator=(const double &);
            const FixedPoint &operator=(const FixedPoint &);
            const FixedPoint &operator+=(const FixedPoint &);
            const FixedPoint &operator-=(const FixedPoint &);
            const FixedPoint &operator*=(const FixedPoint &);
            const FixedPoint &operator/=(const FixedPoint &);
            FixedPoint operator+(const FixedPoint &) const;
            FixedPoint operator-(const FixedPoint &) const;
            FixedPoint operator*(const FixedPoint &) const;
            FixedPoint operator/(const FixedPoint &) const;
            bool operator==(const FixedPoint &) const;
            bool operator!=(const FixedPoint &) const;
            bool operator<=(const FixedPoint &) const;
            bool operator>=(const FixedPoint &) const;
            bool operator<(const FixedPoint &) const;
            bool operator>(const FixedPoint &) const;
            operator  float() const;
            operator double() const;
            void setPrecision(const char &);
            const char &getPrecision() const;
            void setValue(const fpoint_t &);
            const FixedPoint::fpoint_t &getValue() const;
            void adjust(const FixedPoint &);
    };

}

#endif//__CDL_FIXEDPOINT_H__
