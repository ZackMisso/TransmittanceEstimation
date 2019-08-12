#pragma once

#include "primaryestimator.h"

class SecondaryEstimator : public Estimator {
public:
    SecondaryEstimator();

    // numerical estimation
    virtual Float T(TransmittanceQuaryRecord& rec, Sampler* sampler) const;
    virtual Float simpleT(Float ext, Float maj, int term, Float a, Float b) const;
    virtual Float convergeT(TransmittanceQuaryRecord& rec, Sampler* sampler, vector<Float>& means, vector<Float>& costs);

    virtual Estimator* copy() const;

    virtual void updateAxisValue(AxisVar var, Float value);
    virtual vector<AxisVar> getValidAxis() const;

    virtual void updateEstVar(EstimatorVarFloat var, Float value);
    virtual void updateEstVar(EstimatorVarInt var, int value);
    virtual void getEstVar(EstimatorVarFloat var, Float& data) const;
    virtual void getEstVar(EstimatorVarInt var, int& data) const;
    virtual vector<EstimatorVarFloat> getValidEstFloatVars() const;
    virtual vector<EstimatorVarInt> getValidEstIntVars() const;

    virtual string getName() const;
    virtual string getFullName() const;

    void setPrimaryEstimator(Estimator* param);

protected:
    Estimator* estimator;
};
