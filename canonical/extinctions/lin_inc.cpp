#include "lin_inc.h"

LinIncFunc::LinIncFunc() {
    m = 1.0;
    y = 0.0;
}

Float LinIncFunc::evalFunction(Float x, Float a, Float b) const {
    Float val = m * x + y;
    return (val < 0.0) ? 0.0 : val;
}

Float LinIncFunc::calculateIntegral(Float a, Float b) const {
    Float bcomp = 0.5 * m * b * b + b * y;
    Float acomp = 0.5 * m * a * a + a * y;
    return bcomp - acomp;
}

Float LinIncFunc::calculateVariance(Float a, Float b) const {
    // TODO
    return 0.0;
}

Float LinIncFunc::calculateMaxValue(Float a, Float b) const {
    if (m > 0.0) return evalFunction(b);
    return evalFunction(a);
}

Float LinIncFunc::calculateMinValue(Float a, Float b) const {
    if (m > 0.0) return evalFunction(a);
    return evalFunction(b);
}

Float LinIncFunc::calculateMinEfficiency() const {
    return 0.01;
}

Float LinIncFunc::calculateMaxEfficiency() const {
    return 0.45;
}

void LinIncFunc::solveForIntegral(Float a, Float b, Float area) {
    y = 0;
    m = 2.0 * area;
    Func::solveForIntegral(a, b, area);
}

Func* LinIncFunc::copy() const {
    LinIncFunc* newFunc = new LinIncFunc();

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

string LinIncFunc::getName(FuncType type) const {
    if (type == FUNC_MAJORANT) {
        return "maj_lin_inc";
    }
    else if (type == FUNC_MINORANT) {
        return "min_lin_inc";
    }
    else if (type == FUNC_EXTINCTION) {
        return "lin_inc";
    }

    return "lin_inc";
}

bool LinIncFunc::needsDependent() const {
    return false;
}

void LinIncFunc::setM(Float param) { m = param; }
void LinIncFunc::setY(Float param) { y = param; }
