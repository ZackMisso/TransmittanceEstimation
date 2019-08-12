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
    // TODO
    return 0.01;
}

Float LinIncFunc::calculateMaxEfficiency() const {
    // TODO
    return 0.45;
}

void LinIncFunc::solveForIntegral(Float a, Float b, Float area) {
    y = 0;
    m = 2.0 * area;
    Func::solveForIntegral(a, b, area);
}

void LinIncFunc::updateVariables(const vector<ExtVarGuiData>& vars, FuncType type) {
    if (type == FUNC_MAJORANT) {
        for (int i = 0; i < vars.size(); ++i) {
            if (vars[i].name == "maj_m") {
                m = vars[i].floatval;
            } else if (vars[i].name == "maj_y") {
                y = vars[i].floatval;
            }
        }
    }
    else if (type == FUNC_MINORANT) {
        for (int i = 0; i < vars.size(); ++i) {
            if (vars[i].name == "min_m") {
                m = vars[i].floatval;
            } else if (vars[i].name == "min_y") {
                y = vars[i].floatval;
            }
        }
    }
    else if (type == FUNC_EXTINCTION) {
        for (int i = 0; i < vars.size(); ++i) {
            if (vars[i].name == "m") {
                m = vars[i].floatval;
            } else if (vars[i].name == "y") {
                y = vars[i].floatval;
            }
        }
    }
}

void LinIncFunc::getVariables(vector<ExtVarGuiData>& vars, FuncType type) const {
    if (type == FUNC_MAJORANT) {
        ExtVarGuiData mData;
        mData.name = "maj_m";
        mData.varType = EXT_VAR_FLOAT;
        mData.floatval = float(m);
        vars.push_back(mData);

        ExtVarGuiData yData;
        yData.name = "maj_y";
        yData.varType = EXT_VAR_FLOAT;
        yData.floatval = float(y);
        vars.push_back(yData);
    }
    else if (type == FUNC_MINORANT) {
        ExtVarGuiData mData;
        mData.name = "min_m";
        mData.varType = EXT_VAR_FLOAT;
        mData.floatval = float(m);
        vars.push_back(mData);

        ExtVarGuiData yData;
        yData.name = "min_y";
        yData.varType = EXT_VAR_FLOAT;
        yData.floatval = float(y);
        vars.push_back(yData);
    }
    else if (type == FUNC_EXTINCTION) {
        ExtVarGuiData mData;
        mData.name = "m";
        mData.varType = EXT_VAR_FLOAT;
        mData.floatval = float(m);
        vars.push_back(mData);

        ExtVarGuiData yData;
        yData.name = "y";
        yData.varType = EXT_VAR_FLOAT;
        yData.floatval = float(y);
        vars.push_back(yData);
    }
}

void LinIncFunc::updateAxisValue(AxisVar var, Float val, FuncType type) {
    if (type == FUNC_MAJORANT) {
        if (var == MAJ_LIN_M) {
            m = val;
        } else if (var == MAJ_LIN_Y) {
            y = val;
        }
    }
    else if (type == FUNC_MINORANT) {
        if (var == MIN_LIN_M) {
            m = val;
        } else if (var == MIN_LIN_Y) {
            y = val;
        }
    }
    else if (type == FUNC_EXTINCTION) {
        if (var == LIN_M) {
            m = val;
        } else if (var == LIN_Y) {
            y = val;
        }
    }
}

vector<AxisVar> LinIncFunc::getValidAxis(FuncType type) const {
    vector<AxisVar> vars = vector<AxisVar>();

    if (type == FUNC_MAJORANT) {
        vars.push_back(MAJ_LIN_M);
        vars.push_back(MAJ_LIN_Y);
    }
    else if (type == FUNC_MINORANT) {
        vars.push_back(MIN_LIN_M);
        vars.push_back(MIN_LIN_Y);
    }
    else if (type == FUNC_EXTINCTION) {
        vars.push_back(LIN_M);
        vars.push_back(LIN_Y);
    }

    return vars;
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

void LinIncFunc::infoDump() const {
    cout << "M: " << m << endl;
    cout << "Y: " << y << endl;
}

bool LinIncFunc::needsDependent() const {
    return false;
}

ExtinctionType LinIncFunc::getType() const {
    return EXT_LIN_INC;
}

void LinIncFunc::setM(Float param) { m = param; }
void LinIncFunc::setY(Float param) { y = param; }
