//========================================================================
/** @type     C++ Source File
 *  @file     FixedPoint.cpp
 *  @author   alcoco
 *  @date     
 *   Created:       16:07:20 08/03/2005
 *   Last Update:   22:51:10 28/05/2007
 */
//========================================================================

#include <CDL/Math/FixedPoint.h>

namespace CDL
{
    DEFCLASS("FixedPoint");

    size_t FixedPoint::D_PRECISION=20;

    FixedPoint::FixedPoint(const size_t &decimal, const fpoint_t &value)
    {
        m_value=value;
        m_decBits=-1;
        setPrecision(decimal);
    }

    FixedPoint::FixedPoint(const size_t &decimal, const float &value)
    {
         m_decBits=-1;
         setPrecision(decimal);
         m_value=(fpoint_t)(value*(float)(1LL<<m_decBits));
    }

    FixedPoint::FixedPoint(const size_t &decimal, const double &value)
    {
         m_decBits=-1;
         setPrecision(decimal);
         m_value=(fpoint_t)(value*(double)(1LL<<m_decBits));
    }

    FixedPoint::FixedPoint(const float &value)
    {
        m_decBits=D_PRECISION;
        m_value=(fpoint_t)(value*(float)(1LL<<m_decBits));
    }

    FixedPoint::FixedPoint(const double &value)
    {
        m_decBits=D_PRECISION;
        m_value=(fpoint_t)(value*(double)(1LL<<m_decBits));
    }

    FixedPoint::FixedPoint(const FixedPoint &fp)
    {
        m_value=fp.m_value;
        m_decBits=fp.m_decBits;
    }

    const FixedPoint &FixedPoint::operator=(const float &value)
    {
        m_value=(fpoint_t)(value*(float)(1LL<<m_decBits));

        return *this;
    }

    const FixedPoint &FixedPoint::operator=(const double &value)
    {
        m_value=(fpoint_t)(value*(double)(1LL<<m_decBits));

        return *this;
    }

    const FixedPoint &FixedPoint::operator=(const FixedPoint &fp)
    {
        if (&fp != this)
        {
            m_value=fp.m_value;
            m_decBits=fp.m_decBits;
        }

        return *this;
    }

    const FixedPoint &FixedPoint::operator+=(const FixedPoint &fp)
    {
        adjust(fp);
        m_value+=fp.m_value;
        return *this;
    }

    const FixedPoint &FixedPoint::operator-=(const FixedPoint &fp)
    {
        adjust(fp);
        m_value-=fp.m_value;
        return *this;
    }

    const FixedPoint &FixedPoint::operator*=(const FixedPoint &fp)
    {
        adjust(fp);
        m_value=(m_value*fp.m_value)>>m_decBits;
        return *this;
    }

    const FixedPoint &FixedPoint::operator/=(const FixedPoint &fp)
    {
        adjust(fp);
        m_value=(m_value<<m_decBits)/fp.m_value;
        return *this;
    }

    FixedPoint FixedPoint::operator+(const FixedPoint &fp) const
    {
        FixedPoint tmp(fp);
        tmp.adjust(*this);
        tmp.m_value+=m_value;
        return tmp;
    }

    FixedPoint FixedPoint::operator-(const FixedPoint &fp) const
    {
        FixedPoint tmp(fp);
        tmp.adjust(*this);
        tmp.m_value=m_value-tmp.m_value;
        return tmp;
    }

    FixedPoint FixedPoint::operator*(const FixedPoint &fp) const
    {
        FixedPoint tmp(fp);
        tmp.adjust(*this);
        tmp.m_value=(m_value*tmp.m_value)>>m_decBits;

        return tmp;
    }

    FixedPoint FixedPoint::operator/(const FixedPoint &fp) const
    {
        FixedPoint tmp(fp);
        tmp.adjust(*this);
        tmp.m_value=(m_value<<m_decBits)/tmp.m_value;

        return tmp;
    }


    bool FixedPoint::operator==(const FixedPoint &fp) const
    {
        FixedPoint tmp(fp);
        tmp.adjust(*this);

        if (m_value == tmp.m_value)
            return true;
        else
            return false;
    }

    bool FixedPoint::operator!=(const FixedPoint &fp) const
    {
        FixedPoint tmp(fp);
        tmp.adjust(*this);

        if (m_value != tmp.m_value)
            return true;
        else
            return false;
    }

    bool FixedPoint::operator<=(const FixedPoint &fp) const
    {
        FixedPoint tmp(fp);
        tmp.adjust(*this);

        if (m_value <= tmp.m_value)
            return true;
        else
            return false;
    }

    bool FixedPoint::operator>=(const FixedPoint &fp) const
    {
        FixedPoint tmp(fp);
        tmp.adjust(*this);

        if (m_value >= tmp.m_value)
            return true;
        else
            return false;
    }

    bool FixedPoint::operator<(const FixedPoint &fp) const
    {
        FixedPoint tmp(fp);
        tmp.adjust(*this);

        if (m_value < tmp.m_value)
            return true;
        else
            return false;
    }

    bool FixedPoint::operator>(const FixedPoint &fp) const
    {
        FixedPoint tmp(fp);
        tmp.adjust(*this);

        if (m_value > tmp.m_value)
            return true;
        else
            return false;
    }

    FixedPoint::operator float() const
    {
        return (((float)m_value)/(float)(1<<m_decBits));
    }

    FixedPoint::operator double() const
    {
        return (((double)m_value)/(double)(1<<m_decBits));
    }

    void FixedPoint::setPrecision(const char &decimal)
    {
        char oldDec=m_decBits;
        if (decimal > sizeof(fpoint_t)*8-2 || decimal < 1)
        {
            Error_send("Invalid specification of x.%d\n", decimal);
            m_decBits=D_PRECISION;
        }
        else
            m_decBits=decimal;

        if (oldDec != -1)
        {
            if (oldDec == m_decBits)
                return;
            if (oldDec < m_decBits)
                m_value>>=(m_decBits-oldDec);
            else
                m_value<<=(oldDec-m_decBits);
        }
    }

    const char &FixedPoint::getPrecision() const
    {
         return m_decBits;
    }

    void FixedPoint::setValue(const fpoint_t &value)
    {
         m_value=value;
    }

    const FixedPoint::fpoint_t &FixedPoint::getValue() const
    {
        return m_value;
    }

    void FixedPoint::adjust(const FixedPoint &fp)
    {
        if (m_decBits == fp.m_decBits)
            return;
        if (m_decBits < fp.m_decBits)
            m_value>>=(fp.m_decBits-m_decBits);
        else
            m_value<<=(m_decBits-fp.m_decBits);
        m_decBits=fp.m_decBits;
    }
}
