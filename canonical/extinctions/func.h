#pragma once

#include "../common.h"

enum FuncType {
    FUNC_MAJORANT,
    FUNC_MINORANT,
    FUNC_EXTINCTION
};

class Func {
public:
    virtual ~Func() { }

    virtual Float evalFunction(Float x, Float a, Float b) const = 0;

    virtual Float evalIntegral(Float a, Float b) const
    {
        return calculateIntegral(a, b);
    }

    virtual Float calculateMinEfficiency() const = 0;
    virtual Float calculateMaxEfficiency() const = 0;

    virtual void solveForIntegral(Float a, Float b, Float area)
    {
        preProcess(a, b);
    }

    // speed improvements
    void preProcess(Float a, Float b)
    {
        integral = calculateIntegral(a, b);
        variance = calculateVariance(a, b);
        min = calculateMinValue(a, b);
        max = calculateMaxValue(a, b);
    }

    virtual Func* copy() const = 0;
    virtual bool needsDependent() const = 0;

    virtual void setDependent(Func* param) { }
    virtual void declareMajorant() { }
    virtual void declareMinorant() { }

    virtual string getName(FuncType type) const = 0;

    Float getIntegral() const { return integral; }
    Float getVariance() const { return variance; }
    Float getMin() const { return min; }
    Float getMax() const { return max; }

    virtual ExtinctionType getType() const = 0;

protected:
    virtual Float calculateMaxValue(Float a, Float b) const = 0;
    virtual Float calculateMinValue(Float a, Float b) const = 0;
    virtual Float calculateIntegral(Float a, Float b) const = 0;
    virtual Float calculateVariance(Float a, Float b) const = 0;

    // cached data
    Float integral;
    Float variance;
    Float min;
    Float max;
};
