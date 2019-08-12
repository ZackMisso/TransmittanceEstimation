#include "pseries_cdf.h"
#include <tgmath.h>

Pseries_CDF::Pseries_CDF() : PrimaryEstimator() {
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

Float Pseries_CDF::simpleT(Float ext, Float maj, int term, Float a, Float b) const
{
    Float t = 0.0;
    Float W = 1.0;
    Float i = 1.0;
    Float runningCDF = 0.0;
    Float tau = maj * (b - a);
    Float lastPDF = exp(-maj * (b - a));
    Float goal = 0.99;

    int k = 0;
    while (runningCDF < goal)
    {
        Float wi = (1.0 / i) * (maj - ext) * (b - a);
        runningCDF += lastPDF;
        lastPDF *= tau / i;
        t += W;
        W *= wi;
        i += 1.0;
        k++;
    }

    if (k > term) return -1.0;

    for (; k <= term; ++k)
    {
        Float wi = (1.0 / i) * (maj - ext) * (b - a);
        W *= wi / (0.6);
        t += W;
        i += 1.0;
    }

    return t * exp(-maj * (b - a));
}

string Pseries_CDF::getName() const {
    return "pseries_cdf";
}

string Pseries_CDF::getFullName() const {
    return "pseries_cdf";
}

Estimator* Pseries_CDF::copy() const {
    Pseries_CDF* estimator = new Pseries_CDF();

    return estimator;
}
