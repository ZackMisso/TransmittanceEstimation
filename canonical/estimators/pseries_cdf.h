#pragma once

#include "estimator.h"

class Pseries_CDF : public Estimator {
public:
    Pseries_CDF();

    // numerical estimation
    virtual Float T(TransmittanceQuaryRecord& rec, Sampler* sampler) const;

    virtual string getName() const;
};
