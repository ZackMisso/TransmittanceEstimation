#pragma once

#include "estimator.h"

class Pseries_NextFlightRatio : public Estimator {
public:
    Pseries_NextFlightRatio();

    // numerical estimation
    virtual Float T(TransmittanceQuaryRecord& rec, Sampler* sampler) const;

    virtual string getName() const;
};
