// The below code is authored by Zackary Misso
// It is free to use as long as credit is given for its use

#pragma once

#include <mpfr.h>
// #include "/usr/local/include/mpfr.h"
#include <stdio.h>
#include <string>

#define REAL_PRECISION 512

namespace mpfr_pp
{

static void mpfr_from_str(const std::string str, mpfr_t& result)
{
    mpfr_init2(result, REAL_PRECISION);
    mpfr_set_str(result, str.c_str(), /*base*/10, MPFR_RNDN);
}

static void mpfr_from_str(const char* str, mpfr_t& result)
{
    mpfr_init2(result, REAL_PRECISION);
    mpfr_set_str(result, str, /*base*/10, MPFR_RNDN);
}

struct real
{
protected:
    mpfr_t m_val;

    void text(std::string message, const mpfr_t& val) const
    {
        std::cout << message << std::endl;
        mpfr_out_str (stdout, 10, 0, val, MPFR_RNDD);
        std::cout << std::endl;
    }

public:
    void text(std::string message) const
    {
        text(message, m_val);
    }

    real()
    {
        mpfr_init2(m_val, REAL_PRECISION);
    }

    real(const real& val)
    {
        mpfr_init2(m_val, REAL_PRECISION);
        mpfr_set(m_val, val.m_val, MPFR_RNDN);
    }

    real(const long double& val)
    {
        mpfr_init2(m_val, REAL_PRECISION);
        mpfr_set_ld(m_val, val, MPFR_RNDN);
    }

    real(const double& val)
    {
        mpfr_init2(m_val, REAL_PRECISION);
        mpfr_set_d(m_val, val, MPFR_RNDN);
    }

    real(const float& val)
    {
        mpfr_init2(m_val, REAL_PRECISION);
        mpfr_set_flt(m_val, val, MPFR_RNDN);
    }

    real(const unsigned long& val)
    {
        mpfr_init2(m_val, REAL_PRECISION);
        mpfr_set_ui(m_val, val, MPFR_RNDN);
    }

    real(const long& val)
    {
        mpfr_init2(m_val, REAL_PRECISION);
        mpfr_set_si(m_val, val, MPFR_RNDN);
    }

    real(const unsigned int& val)
    {
        mpfr_init2(m_val, REAL_PRECISION);
        mpfr_set_ui(m_val, val, MPFR_RNDN);
    }

    real(const int& val)
    {
        mpfr_init2(m_val, REAL_PRECISION);
        mpfr_set_si(m_val, val, MPFR_RNDN);
    }

    real(std::string val)
    {
        mpfr_init2(m_val, REAL_PRECISION);
        mpfr_set_str(m_val, val.c_str(), /*base*/10, MPFR_RNDN);
    }

    real(const char* val)
    {
        mpfr_init2(m_val, REAL_PRECISION);
        mpfr_set_str(m_val, val, /*base*/10, MPFR_RNDN);
    }

    ~real()
    {
        mpfr_clear(m_val);
    }

    // operators
    void operator++()
    {
        mpfr_t one;
        mpfr_from_str("1.0", one);
        mpfr_add(m_val, m_val, one, MPFR_RNDN);
        mpfr_clear(one);
    }

    void operator--()
    {
        mpfr_t one;
        mpfr_from_str("1.0", one);
        mpfr_sub(m_val, m_val, one, MPFR_RNDN);
        mpfr_clear(one);
    }

    real operator-() const
    {
        mpfr_t tmp;
        mpfr_init2(tmp, REAL_PRECISION);
        mpfr_set_d(tmp, -1.0, MPFR_RNDN);
        mpfr_mul(tmp, m_val, tmp, MPFR_RNDN);

        real val;
        mpfr_set(val.m_val, tmp, MPFR_RNDN);

        mpfr_clear(tmp);

        return val;
    }

    real operator+(const real& other) const
    {
        mpfr_t tmp;
        mpfr_init2(tmp, REAL_PRECISION);
        mpfr_add(tmp, other.m_val, m_val, MPFR_RNDN);

        real val;
        mpfr_set(val.m_val, tmp, MPFR_RNDN);

        mpfr_clear(tmp);

        return val;
    }

    real operator-(const real& other) const
    {
        mpfr_t tmp;
        mpfr_init2(tmp, REAL_PRECISION);
        mpfr_sub(tmp, m_val, other.m_val, MPFR_RNDN);

        real val;
        mpfr_set(val.m_val, tmp, MPFR_RNDN);

        mpfr_clear(tmp);

        return val;
    }

    real operator*(const real& other) const
    {
        mpfr_t tmp;
        mpfr_init2(tmp, REAL_PRECISION);
        mpfr_mul(tmp, m_val, other.m_val, MPFR_RNDN);

        real val;
        mpfr_set(val.m_val, tmp, MPFR_RNDN);

        mpfr_clear(tmp);

        return val;
    }

    real operator/(const real& other) const
    {
        mpfr_t tmp;
        mpfr_init2(tmp, REAL_PRECISION);
        mpfr_div(tmp, m_val, other.m_val, MPFR_RNDN);

        real val;
        mpfr_set(val.m_val, tmp, MPFR_RNDN);

        mpfr_clear(tmp);

        return val;
    }

    real& operator=(const real& other)
    {
        mpfr_set(m_val, other.m_val, MPFR_RNDN);
        return *this;
    }

    void operator+=(const real& other)
    {
        mpfr_add(m_val, m_val, other.m_val, MPFR_RNDN);
    }

    void operator-=(const real& other)
    {
        mpfr_sub(m_val, m_val, other.m_val, MPFR_RNDN);
    }

    void operator*=(const real& other)
    {
        mpfr_mul(m_val, m_val, other.m_val, MPFR_RNDN);
    }

    void operator/=(const real& other)
    {
        mpfr_div(m_val, m_val, other.m_val, MPFR_RNDN);
    }

    bool operator==(const real& other) const
    {
        int compare = mpfr_cmp(m_val, other.m_val);
        return compare == 0;
    }

    bool operator!=(const real& other) const
    {
        int compare = mpfr_cmp(m_val, other.m_val);
        return compare != 0;
    }

    bool operator<(const real& other) const
    {
        int compare = mpfr_cmp(m_val, other.m_val);
        return compare < 0;
    }

    bool operator<=(const real& other) const
    {
        int compare = mpfr_cmp(m_val, other.m_val);
        return compare <= 0;
    }

    bool operator>(const real& other) const
    {
        int compare = mpfr_cmp(m_val, other.m_val);
        return compare > 0;
    }

    bool operator>=(const real& other) const
    {
        int compare = mpfr_cmp(m_val, other.m_val);
        return compare >= 0;
    }

    explicit operator long double() const
    {
        return mpfr_get_ld(m_val, MPFR_RNDN);
    }
    explicit operator double() const
    {
        return mpfr_get_d(m_val, MPFR_RNDN);
    }
    explicit operator float() const
    {
        return mpfr_get_flt(m_val, MPFR_RNDN);
    }
    explicit operator unsigned long() const
    {
        return mpfr_get_ui(m_val, MPFR_RNDN);
    }
    explicit operator long() const
    {
        return mpfr_get_si(m_val, MPFR_RNDN);
    }
    explicit operator unsigned int() const
    {
        return (unsigned int)mpfr_get_ui(m_val, MPFR_RNDN);
    }
    explicit operator int() const
    {
        return (int)mpfr_get_si(m_val, MPFR_RNDN);
    }

    // friend methods
    friend real operator+(const double& two, const real& one);
    friend real operator-(const double& two, const real& one);
    friend real operator*(const double& two, const real& one);
    friend real operator/(const double& two, const real& one);

    friend inline bool operator>(const double& two, const real& one);
    friend inline bool operator<(const double& two, const real& one);
    friend inline bool operator==(const double& two, const real& one);
    friend inline bool operator!=(const double& two, const real& one);
    friend inline bool operator>=(const double& two, const real& one);
    friend inline bool operator<=(const double& two, const real& one);

    friend inline std::ostream& operator<<(std::ostream& out, const real& value);

    friend inline real abs(const real& value);
    friend inline real cos(const real& value);
    friend inline real sin(const real& value);
    friend inline real exp(const real& value);
    friend inline real log(const real& value);
    friend inline real pow(const real& base, const real& pow);
};

inline std::ostream& operator<<(std::ostream& out, const real& value)
{
    out << double(value);
    return out;
}

inline bool operator>(const double& two, const real& one)
{
    mpfr_t tmp;
    mpfr_init2(tmp, REAL_PRECISION);
    mpfr_set_d(tmp, two, MPFR_RNDN);
    int compare = mpfr_cmp(tmp, one.m_val);
    mpfr_clear(tmp);
    return compare > 0;
}

inline bool operator<(const double& two, const real& one)
{
    mpfr_t tmp;
    mpfr_init2(tmp, REAL_PRECISION);
    mpfr_set_d(tmp, two, MPFR_RNDN);
    int compare = mpfr_cmp(tmp, one.m_val);
    mpfr_clear(tmp);
    return compare < 0;
}

inline bool operator==(const double& two, const real& one)
{
    mpfr_t tmp;
    mpfr_init2(tmp, REAL_PRECISION);
    mpfr_set_d(tmp, two, MPFR_RNDN);
    int compare = mpfr_cmp(tmp, one.m_val);
    mpfr_clear(tmp);
    return compare == 0;
}

inline bool operator!=(const double& two, const real& one)
{
    mpfr_t tmp;
    mpfr_init2(tmp, REAL_PRECISION);
    mpfr_set_d(tmp, two, MPFR_RNDN);
    int compare = mpfr_cmp(tmp, one.m_val);
    mpfr_clear(tmp);
    return compare != 0;
}

inline bool operator>=(const double& two, const real& one)
{
    mpfr_t tmp;
    mpfr_init2(tmp, REAL_PRECISION);
    mpfr_set_d(tmp, two, MPFR_RNDN);
    int compare = mpfr_cmp(tmp, one.m_val);
    mpfr_clear(tmp);
    return compare >= 0;
}

inline bool operator<=(const double& two, const real& one)
{
    mpfr_t tmp;
    mpfr_init2(tmp, REAL_PRECISION);
    mpfr_set_d(tmp, two, MPFR_RNDN);
    int compare = mpfr_cmp(tmp, one.m_val);
    mpfr_clear(tmp);
    return compare <= 0;
}

inline real abs(const real& value)
{
    mpfr_t tmp;
    mpfr_init2(tmp, REAL_PRECISION);
    mpfr_abs(tmp, value.m_val, MPFR_RNDN);

    real val;
    mpfr_set(val.m_val, tmp, MPFR_RNDN);

    mpfr_clear(tmp);

    return val;
}

inline real sin(const real& value)
{
    mpfr_t tmp;
    mpfr_init2(tmp, REAL_PRECISION);
    mpfr_sin(tmp, value.m_val, MPFR_RNDN);

    real val;
    mpfr_set(val.m_val, tmp, MPFR_RNDN);

    mpfr_clear(tmp);

    return val;
}

inline real cos(const real& value)
{
    mpfr_t tmp;
    mpfr_init2(tmp, REAL_PRECISION);
    mpfr_cos(tmp, value.m_val, MPFR_RNDN);

    real val;
    mpfr_set(val.m_val, tmp, MPFR_RNDN);

    mpfr_clear(tmp);

    return val;
}

inline real exp(const real& value)
{
    mpfr_t e;
    mpfr_init2(e, REAL_PRECISION);
    mpfr_exp(e, value.m_val, MPFR_RNDN);

    real ret;
    mpfr_set(ret.m_val, e, MPFR_RNDN);

    mpfr_clear(e);

    return ret;
}

inline real log(const real& value)
{
    mpfr_t e;
    mpfr_init2(e, REAL_PRECISION);
    mpfr_log(e, value.m_val, MPFR_RNDN);

    real ret;
    mpfr_set(ret.m_val, e, MPFR_RNDN);

    mpfr_clear(e);

    return ret;
}

inline real pow(const real& base, const real& power)
{
    mpfr_t value;
    mpfr_init2(value, REAL_PRECISION);
    mpfr_pow(value, base.m_val, power.m_val, MPFR_RNDN);

    real ret;
    mpfr_set(ret.m_val, value, MPFR_RNDN);

    mpfr_clear(value);

    return ret;
}

inline real operator+(const double& two, const real& one)
{
    mpfr_t tmp;
    mpfr_init2(tmp, REAL_PRECISION);
    mpfr_set_d(tmp, two, MPFR_RNDN);
    mpfr_add(tmp, one.m_val, tmp, MPFR_RNDN);

    real val;
    mpfr_set(val.m_val, tmp, MPFR_RNDN);

    mpfr_clear(tmp);

    return val;
}

inline real operator-(const double& two, const real& one)
{
    mpfr_t tmp;
    mpfr_init2(tmp, REAL_PRECISION);
    mpfr_set_d(tmp, two, MPFR_RNDN);
    mpfr_sub(tmp, tmp, one.m_val, MPFR_RNDN);

    real val;
    mpfr_set(val.m_val, tmp, MPFR_RNDN);

    mpfr_clear(tmp);

    return val;
}

inline real operator*(const double& two, const real& one)
{
    mpfr_t tmp;
    mpfr_init2(tmp, REAL_PRECISION);
    mpfr_set_d(tmp, two, MPFR_RNDN);
    mpfr_mul(tmp, tmp, one.m_val, MPFR_RNDN);

    real val;
    mpfr_set(val.m_val, tmp, MPFR_RNDN);

    mpfr_clear(tmp);

    return val;
}

inline real operator/(const double& two, const real& one)
{
    mpfr_t tmp;
    mpfr_init2(tmp, REAL_PRECISION);
    mpfr_set_d(tmp, two, MPFR_RNDN);
    mpfr_div(tmp, tmp, one.m_val, MPFR_RNDN);

    real val;
    mpfr_set(val.m_val, tmp, MPFR_RNDN);

    mpfr_clear(tmp);

    return val;
}

}
