#include "gaussFunc.h"
#include "../util.h"

GaussFunc::GaussFunc() {
    h = 1.0;
    sig = 1.0;
    m = 0.5;
}

Float GaussFunc::evalFunction(Float x, Float a, Float b) const {
    Float exponent = (x - m) * (x - m) / (2.0 * sig * sig);
    return h * Util::EXP(-exponent);
}

Float GaussFunc::calculateIntegral(Float a, Float b) const {
    Float sum = 0.0;
    Float stepSize = (b - a) / RESOLUTION;

    for (Float i = 0.0; i < b; i += stepSize) {
        sum += stepSize * evalFunction(i, a, b);
    }

    return sum;
}

Float GaussFunc::calculateVariance(Float a, Float b) const {
    return sig;
}

Float GaussFunc::calculateMaxValue(Float a, Float b) const {
    return h;
}

Float GaussFunc::calculateMinValue(Float a, Float b) const {
    return std::min(evalFunction(a, a, b), evalFunction(b, a, b));
}

Float GaussFunc::calculateMinEfficiency() const {
    return 0.01;
}

Float GaussFunc::calculateMaxEfficiency() const {
    return 0.12;
}

void GaussFunc::solveForIntegral(Float a, Float b, Float area) {
    Float currentArea = calculateIntegral(a, b);
    Float newh = area * h / currentArea;
    h = newh;
    Func::solveForIntegral(a, b, area);
}

Func* GaussFunc::copy() const {
    GaussFunc* newFunc = new GaussFunc();

    newFunc->h = h;
    newFunc->m = m;
    newFunc->sig = sig;
    newFunc->integral = integral;
    newFunc->variance = variance;
    newFunc->min = min;
    newFunc->max = max;

    return newFunc;
}

string GaussFunc::getName(FuncType type) const {
    if (type == FUNC_MAJORANT) {
        return "maj_gauss";
    }
    else if (type == FUNC_MINORANT) {
        return "min_gauss";
    }
    else if (type == FUNC_EXTINCTION) {
        return "gauss";
    }

    return "gauss";
}

bool GaussFunc::needsDependent() const {
    return false;
}

void GaussFunc::setH(Float param) { h = param; }
void GaussFunc::setM(Float param) { m = param; }
void GaussFunc::setSig(Float param) { sig = param; }
