#include "gaussFunc.h"
#include "../util.h"

GaussFunc::GaussFunc() {
    h = 1.0;
    sig = 1.0;
    m = 0.5;
}

Float GaussFunc::evalFunction(Float x, Float a, Float b) const {
    Float exponent = (x - m) * (x - m) / (2.0 * sig * sig);
    return h * Util::EXP(-exponent);
}

Float GaussFunc::calculateIntegral(Float a, Float b) const {
    // TODO: fix this

    Float sum = 0.0;
    Float stepSize = (b - a) / RESOLUTION;

    for (Float i = 0.0; i < b; i += stepSize) {
        sum += stepSize * evalFunction(i, a, b);
    }

    return sum;
}

Float GaussFunc::calculateVariance(Float a, Float b) const {
    return sig;
}

Float GaussFunc::calculateMaxValue(Float a, Float b) const {
    return h;
}

Float GaussFunc::calculateMinValue(Float a, Float b) const {
    return std::min(evalFunction(a, a, b), evalFunction(b, a, b));
}

Float GaussFunc::calculateMinEfficiency() const {
    // return 0.0005;
    return 0.01;
}

Float GaussFunc::calculateMaxEfficiency() const {
    return 0.12;

    // return 0.9995;

    // return 0.6;
}

void GaussFunc::solveForIntegral(Float a, Float b, Float area) {
    Float currentArea = calculateIntegral(a, b);
    Float newh = area * h / currentArea;
    h = newh;
    Func::solveForIntegral(a, b, area);
}

void GaussFunc::updateVariables(const vector<ExtVarGuiData>& vars, FuncType type) {
    if (type == FUNC_MAJORANT) {
        for (int i = 0; i < vars.size(); ++i) {
            if (vars[i].name == "maj_h") {
                h = vars[i].floatval;
            } else if (vars[i].name == "maj_m") {
                m = vars[i].floatval;
            } else if (vars[i].name == "maj_sig") {
                sig = vars[i].floatval;
            }
        }
    }
    else if (type == FUNC_MINORANT) {
        for (int i = 0; i < vars.size(); ++i) {
            if (vars[i].name == "min_h") {
                h = vars[i].floatval;
            } else if (vars[i].name == "min_m") {
                m = vars[i].floatval;
            } else if (vars[i].name == "min_sig") {
                sig = vars[i].floatval;
            }
        }
    }
    else if (type == FUNC_EXTINCTION) {
        for (int i = 0; i < vars.size(); ++i) {
            if (vars[i].name == "h") {
                h = vars[i].floatval;
            } else if (vars[i].name == "m") {
                m = vars[i].floatval;
            } else if (vars[i].name == "sig") {
                sig = vars[i].floatval;
            }
        }
    }
}

void GaussFunc::getVariables(vector<ExtVarGuiData>& vars, FuncType type) const {
    if (type == FUNC_MAJORANT) {
        ExtVarGuiData hData;
        hData.name = "maj_h";
        hData.varType = EXT_VAR_FLOAT;
        hData.floatval = float(h);
        vars.push_back(hData);

        ExtVarGuiData mData;
        mData.name = "maj_m";
        mData.varType = EXT_VAR_FLOAT;
        mData.floatval = float(m);
        vars.push_back(mData);

        ExtVarGuiData sigData;
        sigData.name = "maj_sig";
        sigData.varType = EXT_VAR_FLOAT;
        sigData.floatval = float(sig);
        vars.push_back(sigData);
    }
    else if (type == FUNC_MINORANT) {
        ExtVarGuiData hData;
        hData.name = "min_h";
        hData.varType = EXT_VAR_FLOAT;
        hData.floatval = float(h);
        vars.push_back(hData);

        ExtVarGuiData mData;
        mData.name = "min_m";
        mData.varType = EXT_VAR_FLOAT;
        mData.floatval = float(m);
        vars.push_back(mData);

        ExtVarGuiData sigData;
        sigData.name = "min_sig";
        sigData.varType = EXT_VAR_FLOAT;
        sigData.floatval = float(sig);
        vars.push_back(sigData);
    }
    else if (type == FUNC_EXTINCTION) {
        ExtVarGuiData hData;
        hData.name = "h";
        hData.varType = EXT_VAR_FLOAT;
        hData.floatval = float(h);
        vars.push_back(hData);

        ExtVarGuiData mData;
        mData.name = "m";
        mData.varType = EXT_VAR_FLOAT;
        mData.floatval = float(m);
        vars.push_back(mData);

        ExtVarGuiData sigData;
        sigData.name = "sig";
        sigData.varType = EXT_VAR_FLOAT;
        sigData.floatval = float(sig);
        vars.push_back(sigData);
    }
}

void GaussFunc::updateAxisValue(AxisVar var, Float val, FuncType type) {
    if (type == FUNC_MAJORANT) {
        if (var == MAJ_GAUSS_H) {
            h = val;
        } else if (var == MAJ_GAUSS_M) {
            m = val;
        } else if (var == MAJ_GAUSS_SIG) {
            sig = val;
        }
    }
    else if (type == FUNC_MINORANT) {
        if (var == MIN_GAUSS_H) {
            h = val;
        } else if (var == MIN_GAUSS_M) {
            m = val;
        } else if (var == MIN_GAUSS_SIG) {
            sig = val;
        }
    }
    else if (type == FUNC_EXTINCTION) {
        if (var == GAUSS_H) {
            h = val;
        } else if (var == GAUSS_M) {
            m = val;
        } else if (var == GAUSS_SIG) {
            sig = val;
        }
    }
}

vector<AxisVar> GaussFunc::getValidAxis(FuncType type) const {
    vector<AxisVar> vars = vector<AxisVar>();

    if (type == FUNC_MAJORANT) {
        vars.push_back(MAJ_GAUSS_H);
        vars.push_back(MAJ_GAUSS_M);
        vars.push_back(MAJ_GAUSS_SIG);
    }
    else if (type == FUNC_MINORANT) {
        vars.push_back(MIN_GAUSS_H);
        vars.push_back(MIN_GAUSS_M);
        vars.push_back(MIN_GAUSS_SIG);
    }
    else if (type == FUNC_EXTINCTION) {
        vars.push_back(GAUSS_H);
        vars.push_back(GAUSS_M);
        vars.push_back(GAUSS_SIG);
    }

    return vars;
}

Func* GaussFunc::copy() const {
    GaussFunc* newFunc = new GaussFunc();

    newFunc->h = h;
    newFunc->m = m;
    newFunc->sig = sig;
    newFunc->integral = integral;
    newFunc->variance = variance;
    newFunc->min = min;
    newFunc->max = max;

    return newFunc;
}

string GaussFunc::getName(FuncType type) const {
    if (type == FUNC_MAJORANT) {
        return "maj_gauss";
    }
    else if (type == FUNC_MINORANT) {
        return "min_gauss";
    }
    else if (type == FUNC_EXTINCTION) {
        return "gauss";
    }

    return "gauss";
}

void GaussFunc::infoDump() const {
    cout << "H: " << h << endl;
    cout << "M: " << m << endl;
    cout << "Sig: " << sig << endl;
}

bool GaussFunc::needsDependent() const {
    return false;
}

ExtinctionType GaussFunc::getType() const {
    return EXT_GAUSS;
}

Float GaussFunc::getH() { return h; }

void GaussFunc::setH(Float param) { h = param; }
void GaussFunc::setM(Float param) { m = param; }
void GaussFunc::setSig(Float param) { sig = param; }
