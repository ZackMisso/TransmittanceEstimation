#include "pseries_next_flight_ratio.h"
#include "../util.h"
#include <tgmath.h>

Pseries_NextFlightRatio::Pseries_NextFlightRatio() : Estimator() {
    type = EST_PSERIES_NFR;
}

// NOTE: THIS ASSUMES THAT THE MAJORANT IS CONSTANT
Float Pseries_NextFlightRatio::T(TransmittanceQuaryRecord& rec, Sampler* sampler) const {
    Float sample = sampler->next1D();

    // Float maj = rec.extFunc->calculateMajorant((rec.b - rec.a) / 2.0 + rec.a);
    // Float tau = maj * (rec.b - rec.a);
    // Float prob = exp(-tau);
    // Float cdf = prob;
    // Float Tr = prob;
    // Float prod = prob;
    //
    // for (int i = 1; cdf < sample; cdf += prob, ++i)
    // {
    //     Float x = sampleUniFF(rec, sampler);
    //     prod *= (maj - rec.extFunc->calculateExtinction(x, rec.extCalls)) * (rec.b - rec.a);
    //     prod *= (1.0 / i);
    //
    //     Tr += prod / (1.0 - cdf);
    //     std::cout << "T at i="<<i<<" T=" << Tr << std::endl;
    //     std::cout << "prod: " << prod << std::endl;
    //     prob *= tau / Float(i);
    // }

    Float maj = rec.extFunc->calculateMajorant((rec.b - rec.a) / 2.0 + rec.a);
    Float tau = maj * (rec.b - rec.a);
    Float prob = exp(-tau);
    Float cdf = 0.0;
    Float Tr = 0.0;
    Float prod = exp(-tau);

    for (int i = 0; cdf < sample; cdf += prob, ++i)
    {
        Float x = sampleUniFF(rec, sampler);

        if (i != 0)
        {
            prod *= (maj - rec.extFunc->calculateExtinction(x, rec.extCalls)) * (rec.b - rec.a);
            prod *= (1.0 / i);
        }

        Tr += prod / (1.0 - cdf);
        // std::cout << "T at i="<<i<<" T=" << Tr << std::endl;
        // std::cout << "prod: " << prod << std::endl;
        if (i != 0)
        {
            prob *= tau / Float(i);
        }
    }

    rec.transmittance = Tr;

    return Tr;
}

string Pseries_NextFlightRatio::getName() const {
    return "pseries_next_flight_ratio";
}
