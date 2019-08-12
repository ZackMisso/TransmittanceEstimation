#include "pseries_ratio.h"
#include <tgmath.h>

Pseries_Ratio::Pseries_Ratio() : PrimaryEstimator() {
    type = EST_PSERIES_RAT;
}

// NOTE: THIS ASSUMES THAT THE MAJORANT IS CONSTANT
Float Pseries_Ratio::T(TransmittanceQuaryRecord& rec, Sampler* sampler) const {
    Float sample = sampler->next1D();

    Float maj = rec.extFunc->calculateMajorant((rec.b - rec.a) / 2.0 + rec.a);
    Float tau = maj * (rec.b - rec.a);
    Float prob = exp(-tau);
    Float cdf = prob;
    Float Tr = 1.0;

    int i = 1;

    for (; cdf < sample; cdf += prob, ++i)
    {
        Float x = sampleUniFF(rec, sampler);
        Tr *= 1.0 - rec.extFunc->calculateExtinction(x, rec.extCalls) / maj;
        prob *= tau / Float(i);

        // std::cout << "pre i: " << i << std::endl;
        // std::cout << "pre Tr: " << Tr * exp(-tau) << std::endl;
        // std::cout << "pre prob: " << prob << std::endl;
        // std::cout << std::endl;
    }

    // std::cout << "i: " << i << std::endl;
    // std::cout << "Tr: " << Tr << std::endl;
    // std::cout << "prob: " << prob << std::endl;

    rec.transmittance = Tr;

    return Tr;
}

Float Pseries_Ratio::simpleT(Float ext, Float maj, int term, Float a, Float b) const
{
    // TODO
    return 0.0;
}

string Pseries_Ratio::getName() const {
    return "pseries_ratio";
}

string Pseries_Ratio::getFullName() const {
    return "pseries_ratio";
}

Estimator* Pseries_Ratio::copy() const {
    Pseries_Ratio* estimator = new Pseries_Ratio();

    return estimator;
}
