#include "lin_dec.h"

LinDecFunc::LinDecFunc() {
    m = 1.0;
    y = 0.0;
}

Float LinDecFunc::evalFunction(Float x, Float a, Float b) const {
    Float val = m * x + y;
    return (val < 0.0) ? 0.0 : val;
}

Float LinDecFunc::calculateIntegral(Float a, Float b) const {
    Float bcomp = 0.5 * m * b * b + b * y;
    Float acomp = 0.5 * m * a * a + a * y;
    return bcomp - acomp;
}

Float LinDecFunc::calculateVariance(Float a, Float b) const {
    // TODO
    return 0.0;
}

Float LinDecFunc::calculateMaxValue(Float a, Float b) const {
    if (m > 0.0) return evalFunction(b);
    return evalFunction(a);
}

Float LinDecFunc::calculateMinValue(Float a, Float b) const {
    if (m > 0.0) return evalFunction(a);
    return evalFunction(b);
}

Float LinDecFunc::calculateMinEfficiency() const {
    return 0.01;
}

Float LinDecFunc::calculateMaxEfficiency() const {
    return 0.45;
}

void LinDecFunc::solveForIntegral(Float a, Float b, Float area) {
    y = 2.0 * area;
    m = -2.0 * area;

    Func::solveForIntegral(a, b, area);
}

Func* LinDecFunc::copy() const {
    LinDecFunc* newFunc = new LinDecFunc();

    newFunc->setM(m);
    newFunc->setY(y);

    newFunc->m = m;
    newFunc->y = y;
    newFunc->integral = integral;
    newFunc->variance = variance;
    newFunc->min = min;
    newFunc->max = max;

    return newFunc;
}

string LinDecFunc::getName(FuncType type) const {
    if (type == FUNC_MAJORANT) {
        return "maj_lin_dec";
    }
    else if (type == FUNC_MINORANT) {
        return "min_lin_dec";
    }
    else if (type == FUNC_EXTINCTION) {
        return "lin_dec";
    }

    return "lin_dec";
}

bool LinDecFunc::needsDependent() const {
    return false;
}

ExtinctionType LinDecFunc::getType() const {
    return EXT_LIN_DEC;
}

void LinDecFunc::setM(Float param) { m = param; }
void LinDecFunc::setY(Float param) { y = param; }
