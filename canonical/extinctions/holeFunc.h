#pragma once

#include "func.h"
#include "constFunc.h"
#include "gaussFunc.h"

class HoleFunc : public Func
{
public:
    HoleFunc();

    virtual Float evalFunction(Float x, Float a = 0.0, Float b = 1.0) const;
    Float gaussFunction(Float x, Float a = 0.0, Float b = 1.0) const;
    Float gaussArea(Float a, Float b) const;

    virtual Float calculateMinEfficiency() const;
    virtual Float calculateMaxEfficiency() const;

    virtual void solveForIntegral(Float a, Float b, Float area);

    virtual Func* copy() const;

    virtual string getName(FuncType type) const;

    virtual bool needsDependent() const;

    void setC(Float param);
    void setM(Float param);
    void setSig(Float param);
    void setH(Float param);

protected:
    virtual Float calculateMaxValue(Float a, Float b) const;
    virtual Float calculateMinValue(Float a, Float b) const;
    virtual Float calculateIntegral(Float a, Float b) const;
    virtual Float calculateVariance(Float a, Float b) const;

    Float c;
    Float m;
    Float h;
    Float sig;
};
