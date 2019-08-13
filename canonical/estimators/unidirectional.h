#pragma once

#include "estimator.h"

class Unidirectional : public Estimator {
public:
    Unidirectional();

    // numerical estimaton
    virtual Float T(TransmittanceQuaryRecord& rec, Sampler* sampler) const;

    virtual string getName() const;
protected:
};
