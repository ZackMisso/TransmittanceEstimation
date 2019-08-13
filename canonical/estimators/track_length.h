#pragma once

#include "estimator.h"

class TrackLength : public Estimator {
public:
    TrackLength();

    // numerical estimation
    virtual Float T(TransmittanceQuaryRecord& rec, Sampler* sampler) const;

    virtual string getName() const;
};
