#include "cosFunc.h"
#include "../util.h"

CosFunc::CosFunc() {
    h = 0.8;
    s = 20.0;
    k = 0.0;
    y = 0.8;
}

Float CosFunc::evalFunction(Float x, Float a, Float b) const {
    return h * Util::COS(s * x + k) + y;
}

Float CosFunc::calculateIntegral(Float a, Float b) const {
    Float bcomp = (h / s) * Util::SIN(s * b + k) + y * b;
    Float acomp = (h / s) * Util::SIN(s * a + k) + y * a;
    return bcomp - acomp;
}

Float CosFunc::calculateVariance(Float a, Float b) const {
    // TODO
    return 0.0;
}

Float CosFunc::calculateMaxValue(Float a, Float b) const {
    return h + y;
}

Float CosFunc::calculateMinValue(Float a, Float b) const {
    return y - h;
}

Float CosFunc::calculateMinEfficiency() const {
    return 0.01;
}

Float CosFunc::calculateMaxEfficiency() const {
    return 0.45;
}

void CosFunc::solveForIntegral(Float a, Float b, Float area) {
    h = 10000000000000000.0;

    y = area / (b - a);
    if (h > y) h = y;

    Func::solveForIntegral(a, b, area);
}

Func* CosFunc::copy() const {
    CosFunc* newFunc = new CosFunc();

    newFunc->h = h;
    newFunc->s = s;
    newFunc->k = k;
    newFunc->y = y;
    newFunc->integral = integral;
    newFunc->variance = variance;
    newFunc->min = min;
    newFunc->max = max;

    return newFunc;
}

string CosFunc::getName(FuncType type) const {
    if (type == FUNC_MAJORANT) {
        return "maj_cos";
    }
    else if (type == FUNC_MINORANT) {
        return "min_cos";
    }
    else if (type == FUNC_EXTINCTION) {
        return "cos";
    }

    return "cos";
}

bool CosFunc::needsDependent() const {
    return false;
}

ExtinctionType CosFunc::getType() const {
    return EXT_COS;
}

void CosFunc::setH(Float param) { h = param; }
void CosFunc::setS(Float param) { s = param; }
void CosFunc::setK(Float param) { k = param; }
void CosFunc::setY(Float param) { y = param; }
