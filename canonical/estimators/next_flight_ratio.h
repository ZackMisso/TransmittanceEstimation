#pragma once

#include "primaryestimator.h"

class NextFlight_RatioTracking : public PrimaryEstimator {
public:
    NextFlight_RatioTracking();

    // numerical estimaton
    virtual Float T(TransmittanceQuaryRecord& rec, Sampler* sampler) const;
    virtual Float simpleT(Float ext, Float maj, int term, Float a, Float b) const;

    virtual string getName() const;
    virtual string getFullName() const;

    virtual Estimator* copy() const;
};