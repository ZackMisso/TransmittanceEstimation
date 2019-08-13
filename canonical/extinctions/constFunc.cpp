#include "constFunc.h"

ConstFunc::ConstFunc() {
    c = 1.0;
}

ConstFunc::ConstFunc(Float c) : c(c) { }

Float ConstFunc::evalFunction(Float x, Float a, Float b) const {
    return c;
}

Float ConstFunc::calculateIntegral(Float a, Float b) const {
    return c * (b - a);
}

Float ConstFunc::calculateVariance(Float a, Float b) const {
    return 0.0;
}

Float ConstFunc::calculateMaxValue(Float a, Float b) const {
    return c;
}

Float ConstFunc::calculateMinValue(Float a, Float b) const {
    return c;
}

Float ConstFunc::calculateMinEfficiency() const {
    return 0.01;
}

Float ConstFunc::calculateMaxEfficiency() const {
    return 0.95;
}

void ConstFunc::solveForIntegral(Float a, Float b, Float area) {
    c = area / (b - a);
    preProcess(a, b);
}

Func* ConstFunc::copy() const {
    ConstFunc* newFunc = new ConstFunc();

    newFunc->c = c;
    newFunc->integral = integral;
    newFunc->variance = variance;
    newFunc->min = min;
    newFunc->max = max;

    return newFunc;
}

string ConstFunc::getName(FuncType type) const {
    if (type == FUNC_MAJORANT) {
        return "maj_const";
    } else if (type == FUNC_MINORANT) {
        return "min_const";
    } else if (type == FUNC_EXTINCTION) {
        return "const";
    } else {
        return "const";
    }
}

bool ConstFunc::needsDependent() const {
    return false;
}

ExtinctionType ConstFunc::getType() const {
    return EXT_CONST;
}

Float ConstFunc::getC() const { return c; }

// setter methods
void ConstFunc::setC(Float param) { c = param; }
