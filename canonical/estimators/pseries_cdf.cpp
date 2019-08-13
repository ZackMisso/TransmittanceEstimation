#include "pseries_cdf.h"
#include <tgmath.h>

Pseries_CDF::Pseries_CDF() : Estimator() {
    type = EST_PSERIES_CDF;
}

Float Pseries_CDF::T(TransmittanceQuaryRecord& rec, Sampler* sampler) const {
    Float t = 0.0;
    Float W = 1.0;
    Float i = 1.0;
    Float runningCDF = 0.0;
    Float tau = rec.extFunc->getMajorantFunction()->evalIntegral(rec.a, rec.b);
    Float val = exp(-tau);
    Float lastPDF = val;

    Float goal = 0.99;

    Float rr;
    do
    {
        rr = sampler->next1D();
    } while (rr == 0.0);

    while (runningCDF < goal)
    {
        Float x = sampleUniFF(rec, sampler);
        Float majorant = rec.extFunc->calculateMajorant(x);
        Float extdiff = majorant - rec.extFunc->calculateExtinction(x, rec.extCalls);
        Float wi = (1.0 / i) * (extdiff) / (pdfUniFF(x, rec));
        runningCDF += lastPDF;
        // std::cout << "running CDF: " << runningCDF << std::endl;
        // std::cout << "Tau: " << tau << std::endl;
        lastPDF *= tau / (i);
        t += W;
        W *= (wi);
        i += 1.0;
    }

    while (true) {
        Float left = W;

        Float accept = tau / i;
        runningCDF += lastPDF;

        if (accept <= rr) {
            t += left;
            break;
        }

        rr /= accept;

        Float x = sampleUniFF(rec, sampler);
        Float majorant = rec.extFunc->calculateMajorant(x);
        Float extdiff = majorant - rec.extFunc->calculateExtinction(x, rec.extCalls);
        Float wi = (1.0 / i) * (extdiff) / (pdfUniFF(x, rec));

        lastPDF *= tau / i;
        t += left;
        W *= (wi / accept);
        i += 1.0;
    }

    rec.transmittance = t * val;

    return t * val;
}

string Pseries_CDF::getName() const {
    return "pseries_cdf";
}
