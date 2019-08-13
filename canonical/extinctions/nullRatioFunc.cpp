#include "nullRatioFunc.h"
#include "../util.h"

NullRatioFunc::NullRatioFunc() {
    isMajorant = true;
    func = nullptr;
    ratio = 1.0;
    preProcessed = false;
    preProcessedG = 0.0;
    preProcessedMax = 0.0;
}

Float NullRatioFunc::evalFunction(Float x, Float a, Float b) const {
    Float majVal = func->getMax();
    Float minVal = func->getMin();
    Float area = func->getIntegral();

    Float realArea = area;
    Float tightArea = majVal * (b - a);

    Float g = ((realArea / ratio) - tightArea) / (b - a);

    return g + majVal;
}

Float NullRatioFunc::calculateIntegral(Float a, Float b) const {
    return evalFunction((b - a) / 2.0, a, b) * (b - a);
}

Float NullRatioFunc::calculateVariance(Float a, Float b) const {
    return 0.0;
}

Float NullRatioFunc::calculateMaxValue(Float a, Float b) const {
    return evalFunction((b - a) / 2.0, a, b);
}

Float NullRatioFunc::calculateMinValue(Float a, Float b) const {
    return evalFunction((b - a) / 2.0, a, b);
}

Float NullRatioFunc::calculateMinEfficiency() const {
    // TODO
    return 0.0;
}

Float NullRatioFunc::calculateMaxEfficiency() const {
    // TODO
    return 0.0;
}

void NullRatioFunc::solveForIntegral(Float a, Float b, Float area) {
    // this can not be supported
    Func::solveForIntegral(a, b, area);
}

Func* NullRatioFunc::copy() const {
    NullRatioFunc* newFunc = new NullRatioFunc();

    newFunc->isMajorant = isMajorant;
    newFunc->func = nullptr;
    newFunc->ratio = ratio;
    newFunc->preProcessed = false;
    newFunc->integral = integral;
    newFunc->variance = variance;
    newFunc->min = min;
    newFunc->max = max;

    return newFunc;
}

string NullRatioFunc::getName(FuncType type) const {
    if (type == FUNC_MAJORANT) {
        return "maj_null_ratio";
    }
    else if (type == FUNC_MINORANT) {
        return "min_null_ratio";
    }
    return "maj_null_ratio";
}

bool NullRatioFunc::needsDependent() const {
    return true;
}

void NullRatioFunc::setDependent(Func* param) {
    func = param;
}

void NullRatioFunc::declareMajorant() {
    isMajorant = true;
}

void NullRatioFunc::declareMinorant() {
    isMajorant = false;
}

ExtinctionType NullRatioFunc::getType() const {
    return EXT_NULL_RATIO;
}

void NullRatioFunc::setIsMajorant(bool param) { isMajorant = param; }
void NullRatioFunc::setRatio(Float param) { ratio = param; }
