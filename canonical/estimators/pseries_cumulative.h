#pragma once

#include "estimator.h"

class Pseries_Cumulative : public Estimator {
public:
    Pseries_Cumulative();

    // numerical estimation
    virtual Float T(TransmittanceQuaryRecord& rec, Sampler* sampler) const;

    virtual string getName() const;
};
