#pragma once

#include "estimator.h"

class Bidirectional : public Estimator {
public:
    Bidirectional();

    // numerical estimaton
    virtual Float T(TransmittanceQuaryRecord& rec, Sampler* sampler) const;

    virtual string getName() const;
protected:
};
