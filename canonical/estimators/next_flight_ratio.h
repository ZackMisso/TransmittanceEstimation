#pragma once

#include "estimator.h"

class NextFlight_RatioTracking : public Estimator {
public:
    NextFlight_RatioTracking();

    // numerical estimaton
    virtual Float T(TransmittanceQuaryRecord& rec, Sampler* sampler) const;

    virtual string getName() const;
};
