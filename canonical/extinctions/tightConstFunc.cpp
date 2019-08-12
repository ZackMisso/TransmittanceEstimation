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
        // cout << "whoa" << endl;
        return func->getMax();
    }
    else
    {
        // cout << "whoa2" << endl;
        // if (!func) cout << "yikes" << endl;
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

void TightConstFunc::updateVariables(const vector<ExtVarGuiData>& vars, FuncType type) {
    // no variables to update
}

void TightConstFunc::getVariables(vector<ExtVarGuiData>& vars, FuncType type) const {
    // no variables to update
}

void TightConstFunc::updateAxisValue(AxisVar var, Float val, FuncType type) {
    // no variables to update
}

vector<AxisVar> TightConstFunc::getValidAxis(FuncType type) const {
    vector<AxisVar> vars = vector<AxisVar>();

    return vars;
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

void TightConstFunc::infoDump() const {
    cout << "Const Tight" << endl;
    // cout << "C: " << func->calculateMaxValue(0.0, 1.0);
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

ExtinctionType TightConstFunc::getType() const {
    return EXT_TIGHT;
}

void TightConstFunc::setIsMajorant(bool param) { isMajorant = param; }
