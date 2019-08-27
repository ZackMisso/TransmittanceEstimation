#include "util.h"

Float Util::clamp(Float val, Float min, Float max) {
    if (val > max) return max;
    if (val < min) return min;
    return val;
}

Float Util::abs(Float value) {
    if (value >= 0.0) return value;
    return -value;
}

Float Util::EXP(Float val)
{
    #ifdef USE_ARBITRARY_PRECISION
    return mpfr_pp::exp(val);
    #else
    return exp(val);
    #endif
}

Float Util::LOG(Float val)
{
    #ifdef USE_ARBITRARY_PRECISION
    return mpfr_pp::log(val);
    #else
    return log(val);
    #endif
}

Float Util::POW(Float base, Float power)
{
    #ifdef USE_ARBITRARY_PRECISION
    return mpfr_pp::pow(base, power);
    #else
    return pow(base, power);
    #endif
}

Float Util::ABS(Float val)
{
    #ifdef USE_ARBITRARY_PRECISION
    return mpfr_pp::abs(val);
    #else
    return abs(val);
    #endif
}

Float Util::COS(Float val)
{
    #ifdef USE_ARBITRARY_PRECISION
    return mpfr_pp::cos(val);
    #else
    return cos(val);
    #endif
}

Float Util::SIN(Float val)
{
    #ifdef USE_ARBITRARY_PRECISION
    return mpfr_pp::sin(val);
    #else
    return sin(val);
    #endif
}

float Util::randomDigitScramble(float f, unsigned scramble)
{
    return (unsigned(f*0x100000000LL) ^ scramble) * 2.3283064365386962890625e-10f;
}
