#include "ratio_tracking.h"
#include <tgmath.h>

RatioTracking::RatioTracking() : PrimaryEstimator() {
    type = EST_RATIO;
}

Float RatioTracking::T(TransmittanceQuaryRecord& rec, Sampler* sampler) const {
    Float x = rec.a;
    Float T = 1;

    // std::cout << "in here" << std::endl;

    // cout << "Hello" << endl;

    do {
        // Sample a random value y with pdf(y) = k * exp(-ky) set x = a + y

        // This is only correct if the extinction function is constant
        // std::cout << "calculating majorant" << std::endl;
        Float k = rec.extFunc->calculateMajorant(x);
        // cout << "Majorant: " << k << endl;
        // std::cout << "sampling" << std::endl;
        x += sampleExpFF(rec, sampler, k);

        if (x >= rec.b) break;

        // std::cout << "extinction" << std::endl;
        T *= (1.0 - rec.extFunc->calculateExtinction(x, rec.extCalls) / k);
    } while(true);

    // cout << "Out of here" << endl;

    // while (true) {
    //     // Sample a random value y with pdf(y) = k * exp(-ky) set x = a + y
    //
    //     // This is only correct if the extinction function is constant
    //     Float k = rec.extFunc->calculateMajorant(x);
    //     x += sampleExpFF(rec, sampler, k);
    //
    //     if (x >= rec.b) break;
    //
    //     T *= (1.0 - rec.extFunc->calculateExtinction(x, rec.extCalls) / k);
    // }

    rec.transmittance = T;

    return T;
}

Float RatioTracking::simpleT(Float ext, Float maj, int term, Float a, Float b) const
{
    Float ratio = 1.0;

    for (int i = 1; i <= term; ++i)
        ratio *= (maj - ext) / maj;

    return ratio;
}

string RatioTracking::getName() const {
    return "ratio";
}

string RatioTracking::getFullName() const {
    return "ratio";
}

Estimator* RatioTracking::copy() const {
    RatioTracking* estimator = new RatioTracking();

    return estimator;
}