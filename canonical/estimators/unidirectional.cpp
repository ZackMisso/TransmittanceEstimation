#include "unidirectional.h"
#include <tgmath.h>

Unidirectional::Unidirectional() : Estimator() { }

Float Unidirectional::T(TransmittanceQuaryRecord& rec, Sampler* sampler) const {
    Float x = rec.a;
    Float T = 0.0;
    Float weight = 1.0;

    while (true) {
        Float k = rec.extFunc->calculateMajorant(x);
        Float newx = x + sampleExpFF(rec, sampler, k);

        Float val = exp(-k * (rec.b - x));

        Float nfrProb = 1.0;
        Float ratProb = val;
        Float nfrContr = val;
        Float ratContr = 1.0;

        Float ratMISWeight = ratProb / (ratProb + nfrProb);
        Float nfrMISWeight = nfrProb / (ratProb + nfrProb);

        if (newx >= rec.b)
        {
            T += weight * (ratContr * ratMISWeight + nfrContr * nfrMISWeight);
            break;
        }

        T += weight * (nfrContr * nfrMISWeight);
        x = newx;

        Float ext = rec.extFunc->calculateExtinction(x, rec.extCalls);
        weight *= ((k - ext) / k);
    }

    rec.transmittance = T;

    return T;
}

string Unidirectional::getName() const {
    return "unidirectional";
}
