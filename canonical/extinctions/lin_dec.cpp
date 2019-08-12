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

void LinDecFunc::updateVariables(const vector<ExtVarGuiData>& vars, FuncType type) {
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

void LinDecFunc::getVariables(vector<ExtVarGuiData>& vars, FuncType type) const {
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

void LinDecFunc::updateAxisValue(AxisVar var, Float val, FuncType type) {
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

vector<AxisVar> LinDecFunc::getValidAxis(FuncType type) const {
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

void LinDecFunc::infoDump() const {
    cout << "M: " << m << endl;
    cout << "Y: " << y << endl;
}

bool LinDecFunc::needsDependent() const {
    return false;
}

ExtinctionType LinDecFunc::getType() const {
    return EXT_LIN_DEC;
}

void LinDecFunc::setM(Float param) { m = param; }
void LinDecFunc::setY(Float param) { y = param; }
