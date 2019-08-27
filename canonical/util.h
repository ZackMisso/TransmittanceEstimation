#include "common.h"
#include <tgmath.h>

// just a collection of math helper functions

class Util {
public:
    // clamp methods
    static Float clamp(Float val, Float min, Float max);

    static Float abs(Float value);
    static Float EXP(Float val);
    static Float LOG(Float val);
    static Float POW(Float base, Float power);
    static Float ABS(Float val);
    static Float COS(Float val);
    static Float SIN(Float val);

    // sampling methods
    static float randomDigitScramble(float f, unsigned scramble);
};
