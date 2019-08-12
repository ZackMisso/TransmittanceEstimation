#pragma once

#include "estimator.h"

class PrimaryEstimator : public Estimator {
public:
    PrimaryEstimator();

    virtual void preProcess(Extinction* extFunc, Float a, Float b);

    virtual void updateAxisValue(AxisVar var, Float value);
    virtual vector<AxisVar> getValidAxis() const;

    virtual void updateEstVar(EstimatorVarFloat var, Float value);
    virtual void updateEstVar(EstimatorVarInt var, int value);
    virtual void getEstVar(EstimatorVarFloat var, Float& data) const;
    virtual void getEstVar(EstimatorVarInt var, int& data) const;
    virtual vector<EstimatorVarFloat> getValidEstFloatVars() const;
    virtual vector<EstimatorVarInt> getValidEstIntVars() const;
};
