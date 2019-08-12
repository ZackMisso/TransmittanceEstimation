#include "cosFunc.h"
#include "../util.h"

CosFunc::CosFunc() {
    h = 0.8;
    s = 20.0;
    k = 0.0;
    y = 0.8;
}

Float CosFunc::evalFunction(Float x, Float a, Float b) const {
    return h * Util::COS(s * x + k) + y;
}

Float CosFunc::calculateIntegral(Float a, Float b) const {
    Float bcomp = (h / s) * Util::SIN(s * b + k) + y * b;
    Float acomp = (h / s) * Util::SIN(s * a + k) + y * a;
    return bcomp - acomp;
}

Float CosFunc::calculateVariance(Float a, Float b) const {
    // TODO
    return 0.0;
}

Float CosFunc::calculateMaxValue(Float a, Float b) const {
    // cout << "WHAT :: " << h + y << endl;
    // TODO: MODIFY THIS
    return h + y;
}

Float CosFunc::calculateMinValue(Float a, Float b) const {
    // TODO: MODIFY THIS
    return y - h;
}

Float CosFunc::calculateMinEfficiency() const {
    // return 0.0005;
    return 0.01;
}

Float CosFunc::calculateMaxEfficiency() const {
    return 0.45;

    // return 0.9995;
    // return 0.6;
}

void CosFunc::solveForIntegral(Float a, Float b, Float area) {
    // Float bcomp = (1.0 / s) * sin(s * b + k) + b * y;
    // Float acomp = (1.0 / s) * sin(s * a + k) + a * y;
    // h = area / (bcomp - acomp);
    //
    // if (h > y)
    // {
    //     Float tmp = area / (b - a);
    //
    //     y = tmp;
    //     h = tmp;
    // }

    // TEMPORARY FIX
    h = 10000000000000000.0;

    y = area / (b - a);
    if (h > y) h = y;

    Func::solveForIntegral(a, b, area);
}

void CosFunc::updateVariables(const vector<ExtVarGuiData>& vars, FuncType type) {
    if (type == FUNC_MAJORANT) {
        for (int i = 0; i < vars.size(); ++i) {
            if (vars[i].name == "maj_h") {
                h = vars[i].floatval;
            } else if (vars[i].name == "maj_s") {
                s = vars[i].floatval;
            } else if (vars[i].name == "maj_k") {
                k = vars[i].floatval;
            } else if (vars[i].name == "maj_y") {
                y = vars[i].floatval;
            }
        }
    }
    else if (type == FUNC_MINORANT) {
        for (int i = 0; i < vars.size(); ++i) {
            if (vars[i].name == "min_h") {
                h = vars[i].floatval;
            } else if (vars[i].name == "min_s") {
                s = vars[i].floatval;
            } else if (vars[i].name == "min_k") {
                k = vars[i].floatval;
            } else if (vars[i].name == "min_y") {
                y = vars[i].floatval;
            }
        }
    }
    else if (type == FUNC_EXTINCTION) {
        for (int i = 0; i < vars.size(); ++i) {
            if (vars[i].name == "h") {
                h = vars[i].floatval;
            } else if (vars[i].name == "s") {
                s = vars[i].floatval;
            } else if (vars[i].name == "k") {
                k = vars[i].floatval;
            } else if (vars[i].name == "y") {
                y = vars[i].floatval;
            }
        }
    }
}

void CosFunc::getVariables(vector<ExtVarGuiData>& vars, FuncType type) const {
    if (type == FUNC_MAJORANT) {
        ExtVarGuiData hData;
        hData.name = "maj_h";
        hData.floatval = float(h);
        hData.varType = EXT_VAR_FLOAT;
        vars.push_back(hData);

        ExtVarGuiData kData;
        kData.name = "maj_k";
        kData.floatval = float(k);
        kData.varType = EXT_VAR_FLOAT;
        vars.push_back(kData);

        ExtVarGuiData sData;
        sData.name = "maj_s";
        sData.floatval = float(s);
        sData.varType = EXT_VAR_FLOAT;
        vars.push_back(sData);

        ExtVarGuiData yData;
        yData.name = "maj_y";
        yData.floatval = float(y);
        yData.varType = EXT_VAR_FLOAT;
        vars.push_back(yData);
    }
    else if (type == FUNC_MINORANT) {
        ExtVarGuiData hData;
        hData.name = "min_h";
        hData.floatval = float(h);
        hData.varType = EXT_VAR_FLOAT;
        vars.push_back(hData);

        ExtVarGuiData kData;
        kData.name = "min_k";
        kData.floatval = float(k);
        kData.varType = EXT_VAR_FLOAT;
        vars.push_back(kData);

        ExtVarGuiData sData;
        sData.name = "min_s";
        sData.floatval = float(s);
        sData.varType = EXT_VAR_FLOAT;
        vars.push_back(sData);

        ExtVarGuiData yData;
        yData.name = "min_y";
        yData.floatval = float(y);
        yData.varType = EXT_VAR_FLOAT;
        vars.push_back(yData);
    }
    else if (type == FUNC_EXTINCTION) {
        ExtVarGuiData hData;
        hData.name = "h";
        hData.floatval = float(h);
        hData.varType = EXT_VAR_FLOAT;
        vars.push_back(hData);

        ExtVarGuiData kData;
        kData.name = "k";
        kData.floatval = float(k);
        kData.varType = EXT_VAR_FLOAT;
        vars.push_back(kData);

        ExtVarGuiData sData;
        sData.name = "s";
        sData.floatval = float(s);
        sData.varType = EXT_VAR_FLOAT;
        vars.push_back(sData);

        ExtVarGuiData yData;
        yData.name = "y";
        yData.floatval = float(y);
        yData.varType = EXT_VAR_FLOAT;
        vars.push_back(yData);
    }
}

void CosFunc::updateAxisValue(AxisVar var, Float val, FuncType type) {
    if (type == FUNC_MAJORANT) {
        if (var == MAJ_COS_H) {
            h = val;
        } else if (var == MAJ_COS_K) {
            k = val;
        } else if (var == MAJ_COS_S) {
            s = val;
        } else if (var == MAJ_COS_Y) {
            y = val;
        }
    }
    else if (type == FUNC_MINORANT) {
        if (var == MIN_COS_H) {
            h = val;
        } else if (var == MIN_COS_K) {
            k = val;
        } else if (var == MIN_COS_S) {
            s = val;
        } else if (var == MIN_COS_Y) {
            y = val;
        }
    }
    else if (type == FUNC_EXTINCTION) {
        if (var == COS_H) {
            h = val;
        } else if (var == COS_K) {
            k = val;
        } else if (var == COS_S) {
            s = val;
        } else if (var == COS_Y) {
            y = val;
        }
    }
}

vector<AxisVar> CosFunc::getValidAxis(FuncType type) const {
    vector<AxisVar> vars = vector<AxisVar>();

    if (type == FUNC_MAJORANT) {
        vars.push_back(MAJ_COS_H);
        vars.push_back(MAJ_COS_S);
        vars.push_back(MAJ_COS_K);
        vars.push_back(MAJ_COS_Y);
    }
    else if (type == FUNC_MINORANT) {
        vars.push_back(MIN_COS_H);
        vars.push_back(MIN_COS_S);
        vars.push_back(MIN_COS_K);
        vars.push_back(MIN_COS_Y);
    }
    else if (type == FUNC_EXTINCTION) {
        vars.push_back(COS_H);
        vars.push_back(COS_S);
        vars.push_back(COS_K);
        vars.push_back(COS_Y);
    }

    return vars;
}

Func* CosFunc::copy() const {
    CosFunc* newFunc = new CosFunc();

    newFunc->h = h;
    newFunc->s = s;
    newFunc->k = k;
    newFunc->y = y;
    newFunc->integral = integral;
    newFunc->variance = variance;
    newFunc->min = min;
    newFunc->max = max;

    return newFunc;
}

string CosFunc::getName(FuncType type) const {
    if (type == FUNC_MAJORANT) {
        return "maj_cos";
    }
    else if (type == FUNC_MINORANT) {
        return "min_cos";
    }
    else if (type == FUNC_EXTINCTION) {
        return "cos";
    }

    return "cos";
}

void CosFunc::infoDump() const {
    cout << "H: " << h << endl;
    cout << "S: " << s << endl;
    cout << "K: " << k << endl;
    cout << "Y: " << y << endl;
}

bool CosFunc::needsDependent() const {
    return false;
}

ExtinctionType CosFunc::getType() const {
    return EXT_COS;
}

void CosFunc::setH(Float param) { h = param; }
void CosFunc::setS(Float param) { s = param; }
void CosFunc::setK(Float param) { k = param; }
void CosFunc::setY(Float param) { y = param; }
