#include "holeFunc.h"
#include "../util.h"

HoleFunc::HoleFunc() {
    h = 1.0;
    sig = 1.0;
    m = 0.5;
    c = 1.0;
}

Float HoleFunc::evalFunction(Float x, Float a, Float b) const {
    Float exponent = (x - m) * (x - m) / (2.0 * sig * sig);
    return c - h * Util::EXP(-exponent);
}

Float HoleFunc::gaussFunction(Float x, Float a, Float b) const {
    Float exponent = (x - m) * (x - m) / (2.0 * sig * sig);
    return h * Util::EXP(-exponent);
}

Float HoleFunc::calculateIntegral(Float a, Float b) const {
    Float sum = 0.0;
    Float stepSize = (b - a) / RESOLUTION;

    for (Float i = 0.0; i < b; i += stepSize) {
        sum += stepSize * evalFunction(i, a, b);
    }

    return sum;
}

Float HoleFunc::gaussArea(Float a, Float b) const {
    Float sum = 0.0;
    Float stepSize = (b - a) / RESOLUTION;

    for (Float i = 0.0; i < b; i += stepSize) {
        sum += stepSize * gaussFunction(i, a, b);
    }

    return sum;
}

Float HoleFunc::calculateVariance(Float a, Float b) const {
    // TODO

    return 0.0;
}

Float HoleFunc::calculateMaxValue(Float a, Float b) const {
    return c;
}

Float HoleFunc::calculateMinValue(Float a, Float b) const {
    return c - h;
}

Float HoleFunc::calculateMinEfficiency() const {
    return 0.01;
}

Float HoleFunc::calculateMaxEfficiency() const {
    return 0.85;
}

void HoleFunc::solveForIntegral(Float a, Float b, Float area) {
    Float gArea = gaussArea(a, b);

    Float newC = (area + gArea) / (b - a);

    h = 100.0;

    if (newC > h) c = newC;
    else
    {
        for (int i = 0; i < 5; ++i)
        {
            Float currentArea = calculateIntegral(a, b);
            Float newH = area * c / (currentArea);
            c = newH;
            h = newH;
        }
    }
}

Func* HoleFunc::copy() const {
    HoleFunc* newFunc = new HoleFunc();

    newFunc->h = h;
    newFunc->m = m;
    newFunc->sig = sig;
    newFunc->c = c;
    newFunc->integral = integral;
    newFunc->variance = variance;
    newFunc->min = min;
    newFunc->max = max;

    return newFunc;
}

string HoleFunc::getName(FuncType type) const {
    if (type == FUNC_MAJORANT) {
        return "maj_hole";
    }
    else if (type == FUNC_MINORANT) {
        return "min_hole";
    }
    else if (type == FUNC_EXTINCTION) {
        return "hole";
    }

    return "hole";
}

bool HoleFunc::needsDependent() const {
    return false;
}

ExtinctionType HoleFunc::getType() const {
    return EXT_HOLE;
}

void HoleFunc::setH(Float param) { h = param; }
void HoleFunc::setM(Float param) { m = param; }
void HoleFunc::setSig(Float param) { sig = param; }
void HoleFunc::setC(Float param) { c = param; }
