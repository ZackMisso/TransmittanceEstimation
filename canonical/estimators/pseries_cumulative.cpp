#include "pseries_cumulative.h"
#include "../util.h"

Pseries_Cumulative::Pseries_Cumulative() : PrimaryEstimator() {
    type = EST_PSERIES_CUMULATIVE;
}

Float Pseries_Cumulative::T(TransmittanceQuaryRecord& rec, Sampler* sampler) const {
    Float t = 0.0;
    Float W = 1.0;
    Float i = 1.0;

    Float majorant = rec.extFunc->calculateMajorant(0.5);

    Float rr;
    do
    {
        rr = sampler->next1D();
    } while (rr == 0.0);

    while (true) {
        Float left = W;
        Float x = sampleUniFF(rec, sampler);

        Float wi = (1.0 / i) * (majorant - rec.extFunc->calculateExtinction(x, rec.extCalls)) / (pdfUniFF(x, rec));

        Float accept = Util::ABS(W * wi);

        if (accept > 1.0) accept = 1.0;

        if (accept <= rr) {
            t += left;
            break;
        }

        rr /= accept;

        t += left;
        W *= (wi / accept);
        i += 1.0;
    }

    rec.transmittance = t * exp(-majorant * (rec.b - rec.a));

    // return t * exp(-rec.extFunc->calculateMajorantIntegral(rec.a, rec.b));
    return t * exp(-majorant * (rec.b - rec.a));
}

Float Pseries_Cumulative::simpleT(Float ext, Float maj, int term, Float a, Float b) const
{
    Float W = 1.0;
    Float t = 1.0;
    Float i = 1.0;

    Float tau = maj * (b - a);

    bool terminates = false;

    for (int k = 1; k <= term; ++k)
    {
        Float wi = (1.0 / i) * (maj - ext) * (b - a);
        if (W * wi < 1.0) terminates = true;
        else terminates = false;
        W *= wi / (max(min(W * wi, 1.0), 0.9));
        t += W;
        i += 1.0;
    }

    if (!terminates) return -1.0;

    return t * exp(-maj * (b - a));
}

string Pseries_Cumulative::getName() const {
    return "pseries_cumulative";
}

string Pseries_Cumulative::getFullName() const {
    return "pseries_cumulative";
}

Estimator* Pseries_Cumulative::copy() const {
    Pseries_Cumulative* estimator = new Pseries_Cumulative();

    return estimator;
}
