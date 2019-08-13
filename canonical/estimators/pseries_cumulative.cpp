#include "pseries_cumulative.h"
#include "../util.h"

Pseries_Cumulative::Pseries_Cumulative() : Estimator() {
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

string Pseries_Cumulative::getName() const {
    return "pseries_cumulative";
}
