#pragma once

#include "func.h"

class ConstFunc : public Func {
public:
    ConstFunc();

    // debugging constructor
    ConstFunc(Float c);

    virtual Float evalFunction(Float x, Float a = 0.0, Float b = 1.0) const;

    virtual Float calculateMinEfficiency() const;
    virtual Float calculateMaxEfficiency() const;

    virtual void solveForIntegral(Float a, Float b, Float area);

    virtual void updateVariables(const vector<ExtVarGuiData>& vars, FuncType type);
    virtual void getVariables(vector<ExtVarGuiData>& vars, FuncType type) const;

    virtual void updateAxisValue(AxisVar var, Float val, FuncType type);
    virtual vector<AxisVar> getValidAxis(FuncType type) const;

    virtual Func* copy() const;

    virtual string getName(FuncType type) const;

    virtual bool needsDependent() const;

    virtual ExtinctionType getType() const;

    virtual void infoDump() const;

    // getter methods
    Float getC() const;

    // setter methods
    void setC(Float param);
protected:
    virtual Float calculateMaxValue(Float a, Float b) const;
    virtual Float calculateMinValue(Float a, Float b) const;
    virtual Float calculateIntegral(Float a, Float b) const;
    virtual Float calculateVariance(Float a, Float b) const;

    Float c;
};
