#include "holeFunc.h"
#include "../util.h"

HoleFunc::HoleFunc() {
    h = 1.0;
    sig = 1.0;
    m = 0.5;
    c = 1.0;
}

Float HoleFunc::evalFunction(Float x, Float a, Float b) const {
    Float exponent = (x - m) * (x - m) / (2.0 * sig * sig);
    return c - h * Util::EXP(-exponent);
}

Float HoleFunc::gaussFunction(Float x, Float a, Float b) const {
    Float exponent = (x - m) * (x - m) / (2.0 * sig * sig);
    return h * Util::EXP(-exponent);
}

Float HoleFunc::calculateIntegral(Float a, Float b) const {
    Float sum = 0.0;
    Float stepSize = (b - a) / RESOLUTION;

    for (Float i = 0.0; i < b; i += stepSize) {
        sum += stepSize * evalFunction(i, a, b);
    }

    return sum;
}

Float HoleFunc::gaussArea(Float a, Float b) const {
    Float sum = 0.0;
    Float stepSize = (b - a) / RESOLUTION;

    for (Float i = 0.0; i < b; i += stepSize) {
        sum += stepSize * gaussFunction(i, a, b);
    }

    return sum;
}

Float HoleFunc::calculateVariance(Float a, Float b) const {
    // TODO

    return 0.0;
}

Float HoleFunc::calculateMaxValue(Float a, Float b) const {
    return c;
}

Float HoleFunc::calculateMinValue(Float a, Float b) const {
    return c - h;
}

Float HoleFunc::calculateMinEfficiency() const {
    // return 0.0005;
    return 0.01;
}

Float HoleFunc::calculateMaxEfficiency() const {
    return 0.85;

    // return 0.9995;

    // return 0.6;
}

void HoleFunc::solveForIntegral(Float a, Float b, Float area) {
    // if ((b - a) * y >= area)
    // {
    //     h = 0.0;
    //     return;
    // }


    Float gArea = gaussArea(a, b);

    Float newC = (area + gArea) / (b - a);

    // TEMPORARY FIX
    h = 100.0;

    if (newC > h) c = newC;
    else
    {
        for (int i = 0; i < 5; ++i)
        {
            Float currentArea = calculateIntegral(a, b);
            Float newH = area * c / (currentArea);
            c = newH;
            h = newH;
        }
    }

    // Float newC = area +
    //
    // Float currentArea = calculateIntegral(a, b);
    // Float newh = ((area - y * (b - a)) * h) / (currentArea - y * (b - a));
    // h = newh;
    // Func::solveForIntegral(a, b, area);
}

void HoleFunc::updateVariables(const vector<ExtVarGuiData>& vars, FuncType type) {
    if (type == FUNC_MAJORANT) {
        for (int i = 0; i < vars.size(); ++i) {
            if (vars[i].name == "maj_h") {
                h = vars[i].floatval;
            } else if (vars[i].name == "maj_m") {
                m = vars[i].floatval;
            } else if (vars[i].name == "maj_sig") {
                sig = vars[i].floatval;
            } else if (vars[i].name == "maj_c") {
                c = vars[i].floatval;
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
            } else if (vars[i].name == "min_c") {
                c = vars[i].floatval;
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
            } else if (vars[i].name == "c") {
                c = vars[i].floatval;
            }
        }
    }
}

void HoleFunc::getVariables(vector<ExtVarGuiData>& vars, FuncType type) const {
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

        ExtVarGuiData cData;
        cData.name = "maj_c";
        cData.varType = EXT_VAR_FLOAT;
        cData.floatval = float(c);
        vars.push_back(cData);
    }
    else if (type == FUNC_MINORANT) {
        ExtVarGuiData hData;
        hData.name = "min_h";
        hData.varType = EXT_VAR_FLOAT;
        hData.floatval = float();
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

        ExtVarGuiData cData;
        cData.name = "min_c";
        cData.varType = EXT_VAR_FLOAT;
        cData.floatval = float(c);
        vars.push_back(cData);
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

        ExtVarGuiData cData;
        cData.name = "c";
        cData.varType = EXT_VAR_FLOAT;
        cData.floatval = float(c);
        vars.push_back(cData);
    }
}

void HoleFunc::updateAxisValue(AxisVar var, Float val, FuncType type) {
    if (type == FUNC_MAJORANT) {
        if (var == MAJ_HOLE_H) {
            h = val;
        } else if (var == MAJ_HOLE_M) {
            m = val;
        } else if (var == MAJ_HOLE_SIG) {
            sig = val;
        } else if (var == MAJ_HOLE_C) {
            c = val;
        }
    }
    else if (type == FUNC_MINORANT) {
        if (var == MIN_HOLE_H) {
            h = val;
        } else if (var == MIN_HOLE_M) {
            m = val;
        } else if (var == MIN_HOLE_SIG) {
            sig = val;
        } else if (var == MIN_HOLE_C) {
            c = val;
        }
    }
    else if (type == FUNC_EXTINCTION) {
        if (var == HOLE_H) {
            h = val;
        } else if (var == HOLE_M) {
            m = val;
        } else if (var == HOLE_SIG) {
            sig = val;
        } else if (var == HOLE_C) {
            c = val;
        }
    }
}

vector<AxisVar> HoleFunc::getValidAxis(FuncType type) const {
    vector<AxisVar> vars = vector<AxisVar>();

    if (type == FUNC_MAJORANT) {
        vars.push_back(MAJ_HOLE_H);
        vars.push_back(MAJ_HOLE_M);
        vars.push_back(MAJ_HOLE_SIG);
        vars.push_back(MAJ_HOLE_C);
    }
    else if (type == FUNC_MINORANT) {
        vars.push_back(MIN_HOLE_H);
        vars.push_back(MIN_HOLE_M);
        vars.push_back(MIN_HOLE_SIG);
        vars.push_back(MIN_HOLE_C);
    }
    else if (type == FUNC_EXTINCTION) {
        vars.push_back(HOLE_H);
        vars.push_back(HOLE_M);
        vars.push_back(HOLE_SIG);
        vars.push_back(HOLE_C);
    }

    return vars;
}

Func* HoleFunc::copy() const {
    HoleFunc* newFunc = new HoleFunc();

    newFunc->h = h;
    newFunc->m = m;
    newFunc->sig = sig;
    newFunc->c = c;
    newFunc->integral = integral;
    newFunc->variance = variance;
    newFunc->min = min;
    newFunc->max = max;

    return newFunc;
}

string HoleFunc::getName(FuncType type) const {
    if (type == FUNC_MAJORANT) {
        return "maj_hole";
    }
    else if (type == FUNC_MINORANT) {
        return "min_hole";
    }
    else if (type == FUNC_EXTINCTION) {
        return "hole";
    }

    return "hole";
}

void HoleFunc::infoDump() const {
    cout << "H: " << h << endl;
    cout << "M: " << m << endl;
    cout << "Sig: " << sig << endl;
    cout << "C: " << c << endl;
}

bool HoleFunc::needsDependent() const {
    return false;
}

ExtinctionType HoleFunc::getType() const {
    return EXT_HOLE;
}

// Float HoleFunc::getH() { return h; }

void HoleFunc::setH(Float param) { h = param; }
void HoleFunc::setM(Float param) { m = param; }
void HoleFunc::setSig(Float param) { sig = param; }
void HoleFunc::setC(Float param) { c = param; }
