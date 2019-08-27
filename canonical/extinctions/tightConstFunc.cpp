#include "tightConstFunc.h"

TightConstFunc::TightConstFunc() {
    isMajorant = true;
    func = nullptr;
}

TightConstFunc::TightConstFunc(Func* func, bool isMajorant)
        : func(func), isMajorant(isMajorant) { }

Float TightConstFunc::evalFunction(Float x, Float a, Float b) const {
    if (isMajorant)
    {
        return func->getMax();
    }
    else
    {
        return func->getMin();
    }
}

Float TightConstFunc::calculateIntegral(Float a, Float b) const {
    return evalFunction((b - a) / 2.0, a, b) * (b - a);
}

Float TightConstFunc::calculateVariance(Float a, Float b) const {
    return 0.0;
}

Float TightConstFunc::calculateMaxValue(Float a, Float b) const {
    return evalFunction((b + a) / 2.0, a, b);
}

Float TightConstFunc::calculateMinValue(Float a, Float b) const {
    return evalFunction((b + a) / 2.0, a, b);
}

Float TightConstFunc::calculateMinEfficiency() const {
    // TODO
    return 0.0;
}

Float TightConstFunc::calculateMaxEfficiency() const {
    // TODO
    return 0.0;
}

void TightConstFunc::solveForIntegral(Float a, Float b, Float area) {
    // this can not be supported
    Func::solveForIntegral(a, b, area);
}

Func* TightConstFunc::copy() const {
    TightConstFunc* newFunc = new TightConstFunc();

    newFunc->setIsMajorant(isMajorant);
    newFunc->func = nullptr;
    newFunc->integral = integral;
    newFunc->variance = variance;
    newFunc->min = min;
    newFunc->max = max;

    return newFunc;
}

string TightConstFunc::getName(FuncType type) const {
    if (type == FUNC_MAJORANT) {
        return "maj_tight";
    }
    else if (type == FUNC_MINORANT) {
        return "min_tight";
    }
    return "maj_tight";
}

bool TightConstFunc::needsDependent() const {
    return true;
}

void TightConstFunc::setDependent(Func* param) {
    // cout << "whim" << endl;
    func = param;
}

void TightConstFunc::declareMajorant() {
    isMajorant = true;
}

void TightConstFunc::declareMinorant() {
    isMajorant = false;
}

void TightConstFunc::setIsMajorant(bool param) { isMajorant = param; }
