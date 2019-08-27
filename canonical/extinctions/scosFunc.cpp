#include "scosFunc.h"
#include "../util.h"

ScosFunc::ScosFunc() {
    h = 0.8;
    s = 5.0;
}

Float ScosFunc::evalFunction(Float x, Float a, Float b) const {
    return h * Util::COS(s * x) + h;
}

Float ScosFunc::calculateIntegral(Float a, Float b) const {
    Float bcomp = (h / s) * Util::SIN(s * b) + h * b;
    Float acomp = (h / s) * Util::SIN(s * a) + h * a;
    return bcomp - acomp;
}

Float ScosFunc::calculateVariance(Float a, Float b) const {
    // TODO
    return 0.0;
}

Float ScosFunc::calculateMaxValue(Float a, Float b) const {
    return 2.0 * h;
}

Float ScosFunc::calculateMinValue(Float a, Float b) const {
    return 0.0;
}

Float ScosFunc::calculateMinEfficiency() const {
    return 0.01;
}

Float ScosFunc::calculateMaxEfficiency() const {
    return 0.45;
}

void ScosFunc::solveForIntegral(Float a, Float b, Float area) {
    Float bcomp = (1.0 / s) * sin(s * b) + b;
    Float acomp = (1.0 / s) * sin(s * a) + a;
    h = area / (bcomp - acomp);
    Func::solveForIntegral(a, b, area);
}

Func* ScosFunc::copy() const {
    ScosFunc* newFunc = new ScosFunc();

    newFunc->setH(h);
    newFunc->setS(s);

    newFunc->h = h;
    newFunc->s = s;
    newFunc->integral = integral;
    newFunc->variance = variance;
    newFunc->min = min;
    newFunc->max = max;

    return newFunc;
}

string ScosFunc::getName(FuncType type) const {
    if (type == FUNC_MAJORANT) {
        return "maj_scos";
    }
    else if (type == FUNC_MINORANT) {
        return "min_scos";
    }
    else if (type == FUNC_EXTINCTION) {
        return "scos";
    }

    return "scos";
}

bool ScosFunc::needsDependent() const {
    return false;
}

void ScosFunc::setH(Float param) { h = param; }
void ScosFunc::setS(Float param) { s = param; }
