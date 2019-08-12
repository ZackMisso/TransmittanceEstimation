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

void ScosFunc::updateVariables(const vector<ExtVarGuiData>& vars, FuncType type) {
    if (type == FUNC_MAJORANT) {
        for (int i = 0; i < vars.size(); ++i) {
            if (vars[i].name == "maj_h") {
                h = vars[i].floatval;
            } else if (vars[i].name == "maj_s") {
                s = vars[i].floatval;
            }
        }
    }
    else if (type == FUNC_MINORANT) {
        for (int i = 0; i < vars.size(); ++i) {
            if (vars[i].name == "min_h") {
                h = vars[i].floatval;
            } else if (vars[i].name == "min_s") {
                s = vars[i].floatval;
            }
        }
    }
    else if (type == FUNC_EXTINCTION) {
        for (int i = 0; i < vars.size(); ++i) {
            if (vars[i].name == "h") {
                h = vars[i].floatval;
            } else if (vars[i].name == "s") {
                s = vars[i].floatval;
            }
        }
    }
}

void ScosFunc::getVariables(vector<ExtVarGuiData>& vars, FuncType type) const {
    if (type == FUNC_MAJORANT) {
        ExtVarGuiData hData;
        hData.name = "maj_h";
        hData.varType = EXT_VAR_FLOAT;
        hData.floatval = float(h);
        vars.push_back(hData);

        ExtVarGuiData sData;
        sData.name = "maj_s";
        sData.varType = EXT_VAR_FLOAT;
        sData.floatval = float(s);
        vars.push_back(sData);
    }
    else if (type == FUNC_MINORANT) {
        ExtVarGuiData hData;
        hData.name = "min_h";
        hData.varType = EXT_VAR_FLOAT;
        hData.floatval = float(h);
        vars.push_back(hData);

        ExtVarGuiData sData;
        sData.name = "min_s";
        sData.varType = EXT_VAR_FLOAT;
        sData.floatval = float(s);
        vars.push_back(sData);
    }
    else if (type == FUNC_EXTINCTION) {
        ExtVarGuiData hData;
        hData.name = "h";
        hData.varType = EXT_VAR_FLOAT;
        hData.floatval = float(h);
        vars.push_back(hData);

        ExtVarGuiData sData;
        sData.name = "s";
        sData.varType = EXT_VAR_FLOAT;
        sData.floatval = float(s);
        vars.push_back(sData);
    }
}

void ScosFunc::updateAxisValue(AxisVar var, Float val, FuncType type) {
    if (type == FUNC_MAJORANT) {
        if (val == MAJ_SCOS_H) {
            h = val;
        } else if (val == MAJ_SCOS_S) {
            s = val;
        }
    }
    else if (type == FUNC_MINORANT) {
        if (val == MIN_SCOS_H) {
            h = val;
        } else if (val == MIN_SCOS_S) {
            s = val;
        }
    }
    else if (type == FUNC_EXTINCTION) {
        if (val == SCOS_H) {
            h = val;
        } else if (val == SCOS_S) {
            s = val;
        }
    }
}

vector<AxisVar> ScosFunc::getValidAxis(FuncType type) const {
    vector<AxisVar> vars = vector<AxisVar>();

    if (type == FUNC_MAJORANT) {
        vars.push_back(MAJ_SCOS_H);
        vars.push_back(MAJ_SCOS_S);
    }
    else if (type == FUNC_MINORANT) {
        vars.push_back(MIN_SCOS_H);
        vars.push_back(MIN_SCOS_S);
    }
    else if (type == FUNC_EXTINCTION) {
        vars.push_back(SCOS_H);
        vars.push_back(SCOS_S);
    }

    return vars;
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

void ScosFunc::infoDump() const {
    cout << "H: " << h << endl;
    cout << "S: " << s << endl;
}

bool ScosFunc::needsDependent() const {
    return false;
}

ExtinctionType ScosFunc::getType() const {
    return EXT_SCOS;
}

Float ScosFunc::getH() { return h; }
Float ScosFunc::getS() { return s; }

void ScosFunc::setH(Float param) { h = param; }
void ScosFunc::setS(Float param) { s = param; }
