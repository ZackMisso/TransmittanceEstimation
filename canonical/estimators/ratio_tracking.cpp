#include "ratio_tracking.h"
#include <tgmath.h>

RatioTracking::RatioTracking() : Estimator() { }

Float RatioTracking::T(TransmittanceQuaryRecord& rec, Sampler* sampler) const {
    Float x = rec.a;
    Float T = 1;

    do {
        // Sample a random value y with pdf(y) = k * exp(-ky) set x = a + y
        Float k = rec.extFunc->calculateMajorant(x);
        x += sampleExpFF(rec, sampler, k);

        if (x >= rec.b) break;

        T *= (1.0 - rec.extFunc->calculateExtinction(x, rec.extCalls) / k);
    } while(true);

    rec.transmittance = T;

    return T;
}

string RatioTracking::getName() const {
    return "ratio";
}
