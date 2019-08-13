#pragma once

#include "estimator.h"

class RatioTracking : public Estimator {
public:
    RatioTracking();

    // numerical estimation
    virtual Float T(TransmittanceQuaryRecord& rec, Sampler* sampler) const;

    virtual string getName() const;
};
