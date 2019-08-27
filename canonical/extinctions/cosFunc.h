#pragma once

#include "func.h"

class CosFunc : public Func {
public:
    CosFunc();

    virtual Float evalFunction(Float x, Float a = 0.0, Float b = 1.0) const;

    virtual Float calculateMinEfficiency() const;
    virtual Float calculateMaxEfficiency() const;

    virtual void solveForIntegral(Float a, Float b, Float area);

    virtual Func* copy() const;

    virtual string getName(FuncType type) const;

    virtual bool needsDependent() const;

    // setter methods
    void setH(Float param);
    void setS(Float param);
    void setK(Float param);
    void setY(Float param);
protected:
    virtual Float calculateMaxValue(Float a, Float b) const;
    virtual Float calculateMinValue(Float a, Float b) const;
    virtual Float calculateIntegral(Float a, Float b) const;
    virtual Float calculateVariance(Float a, Float b) const;

    Float h;
    Float s;
    Float k;
    Float y;
};
