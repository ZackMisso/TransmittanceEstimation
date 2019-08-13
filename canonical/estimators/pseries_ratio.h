#pragma once

#include "estimator.h"

class Pseries_Ratio : public Estimator {
public:
    Pseries_Ratio();

    // numerical estimation
    virtual Float T(TransmittanceQuaryRecord& rec, Sampler* sampler) const;

    virtual string getName() const;
};
