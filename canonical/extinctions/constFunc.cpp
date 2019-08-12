#include "constFunc.h"

ConstFunc::ConstFunc() {
    c = 1.0;
}

ConstFunc::ConstFunc(Float c) : c(c) { }

Float ConstFunc::evalFunction(Float x, Float a, Float b) const {
    return c;
}

Float ConstFunc::calculateIntegral(Float a, Float b) const {
    // std::cout << "Integral: " << c * (b - a) << endl;
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
    // return 0.0005;
}

Float ConstFunc::calculateMaxEfficiency() const {
    return 0.95;

    // return 0.6;

    // return 0.9995;
}

void ConstFunc::solveForIntegral(Float a, Float b, Float area) {
    c = area / (b - a);
    preProcess(a, b);
}

void ConstFunc::updateVariables(const vector<ExtVarGuiData>& vars, FuncType type) {
    if (type == FUNC_MAJORANT) {
        for (int i = 0; i < vars.size(); ++i) {
            if (vars[i].name == "maj_c") {
                c = vars[i].floatval;
            }
        }
    }
    else if (type == FUNC_MINORANT) {
        for (int i = 0; i < vars.size(); ++i) {
            if (vars[i].name == "min_c") {
                c = vars[i].floatval;
            }
        }
    }
    else if (type == FUNC_EXTINCTION) {
        for (int i = 0; i < vars.size(); ++i) {
            if (vars[i].name == "c") {
                c = vars[i].floatval;
            }
        }
    }
}

void ConstFunc::getVariables(vector<ExtVarGuiData>& vars, FuncType type) const {
    if (type == FUNC_MAJORANT) {
        ExtVarGuiData cData;
        cData.name = "maj_c";
        cData.floatval = float(c);
        cData.varType = EXT_VAR_FLOAT;
        vars.push_back(cData);
    }
    else if (type == FUNC_MINORANT) {
        ExtVarGuiData cData;
        cData.name = "min_c";
        cData.floatval = float(c);
        cData.varType = EXT_VAR_FLOAT;
        vars.push_back(cData);
    }
    else if (type == FUNC_EXTINCTION) {
        ExtVarGuiData cData;
        cData.name = "c";
        cData.floatval = float(c);
        cData.varType = EXT_VAR_FLOAT;
        vars.push_back(cData);
    }
}

void ConstFunc::updateAxisValue(AxisVar var, Float val, FuncType type) {
    if (type == FUNC_MAJORANT) {
        if (var == MAJ_CONST_C) {
            c = val;
        }
    }
    else if (type == FUNC_MINORANT) {
        if (var == MIN_CONST_C) {
            c = val;
        }
    }
    else if (type == FUNC_EXTINCTION) {
        if (var == CONST_C) {
            c = val;
        }
    }
}

vector<AxisVar> ConstFunc::getValidAxis(FuncType type) const {
    vector<AxisVar> vars = vector<AxisVar>();

    if (type == FUNC_MAJORANT) {
        vars.push_back(MAJ_CONST_C);
    }
    else if (type == FUNC_MINORANT) {
        vars.push_back(MIN_CONST_C);
    }
    else if (type == FUNC_EXTINCTION) {
        vars.push_back(CONST_C);
    }

    return vars;
}

Func* ConstFunc::copy() const {
    ConstFunc* newFunc = new ConstFunc();

    // cout << "COPY" << endl;

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

void ConstFunc::infoDump() const {
    cout << "C: " << c << endl;
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
