#pragma once

#include "estimator.h"

class Expected : public Estimator {
public:
    Expected();

    // numerical esitimation
    virtual Float T(TransmittanceQuaryRecord& rec, Sampler* sampler) const;

    virtual string getName() const;
};
