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

    // if (g < 0.0) cout << "WHAT THE HEELLL" << endl;

    return g + majVal;

    // return ratio;
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

void NullRatioFunc::updateVariables(const vector<ExtVarGuiData>& vars, FuncType type) {
    if (type == FUNC_MAJORANT) {
        for (int i = 0; i < vars.size(); ++i) {
            if (vars[i].name == "maj_ratio") {
                ratio = vars[i].floatval;
            }
        }
    }
    else if (type == FUNC_MINORANT) {
        for (int i = 0; i < vars.size(); ++i) {
            if (vars[i].name == "min_ratio") {
                ratio = vars[i].floatval;
            }
        }
    }
}

void NullRatioFunc::getVariables(vector<ExtVarGuiData>& vars, FuncType type) const {
    if (type == FUNC_MAJORANT) {
        ExtVarGuiData ratioData;
        ratioData.name = "maj_ratio";
        ratioData.floatval = float(ratio);
        ratioData.varType = EXT_VAR_FLOAT;
        vars.push_back(ratioData);
    }
    else if (type == FUNC_MINORANT) {
        ExtVarGuiData ratioData;
        ratioData.name = "min_ratio";
        ratioData.floatval = float(ratio);
        ratioData.varType = EXT_VAR_FLOAT;
        vars.push_back(ratioData);
    }
}

void NullRatioFunc::updateAxisValue(AxisVar var, Float val, FuncType type) {
    if (type == FUNC_MAJORANT) {
        if (var == MAJ_NULL_RATIO) {
            // ratio = -Util::LOG(val) * 30 / -Util::LOG(0.0005);
            ratio = val;
        }
    }
    else if (type == FUNC_MINORANT) {
        if (var == MIN_NULL_RATIO) {
            // ratio = -Util::LOG(val) * 30 / -Util::LOG(0.0005);
            ratio = val;
        }
    }
}

vector<AxisVar> NullRatioFunc::getValidAxis(FuncType type) const {
    vector<AxisVar> vars = vector<AxisVar>();

    if (type == FUNC_MAJORANT) {
        vars.push_back(MAJ_NULL_RATIO);
    }
    else if (type == FUNC_MINORANT) {
        vars.push_back(MIN_NULL_RATIO);
    }

    return vars;
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

void NullRatioFunc::infoDump() const {
    // cout << "Const Tight" << endl;
    // cout << "C: " << func->calculateMaxValue(0.0, 1.0);

    cout << "Info Dump Not Implemented" << endl;

    // TODO
}

// void NullRatioFunc::preProcess(Float a, Float b) {
//     cout << "PREPROCESSING" << endl;
//     Float majVal = 0.0;
//     Float minVal = 1000000.0;
//     Float area = 0.0;
//
//     for (int i = 0; i <= 10000; ++i) {
//         Float y = func->evalFunction((b - a) * (Float(i) / Float(10000)) + a, a, b);
//
//         majVal = max(majVal, y);
//         minVal = min(minVal, y);
//
//         if (i != 0) {
//             area += func->evalFunction((b - a) * (Float(i) / Float(10000)) + a, a, b) * (1.0 / 10000.0);
//         }
//     }
//
//     Float realArea = area;
//     Float tightArea = majVal * (b - a);
//
//     Float g = ((realArea / ratio) - tightArea) / (b - a);
//
//     preProcessedG = g;
//     preProcessedMax = majVal;
//     preProcessed = true;
// }

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
