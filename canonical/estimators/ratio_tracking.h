#pragma once

#include "primaryestimator.h"

class RatioTracking : public PrimaryEstimator {
public:
    RatioTracking();

    // numerical estimation
    virtual Float T(TransmittanceQuaryRecord& rec, Sampler* sampler) const;
    virtual Float simpleT(Float ext, Float maj, int term, Float a, Float b) const;

    virtual string getName() const;
    virtual string getFullName() const;

    virtual Estimator* copy() const;
};
