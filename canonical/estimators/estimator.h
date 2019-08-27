#pragma once

#include "../extinctions/extinctionFunc.h"
#include "../samplers/sampler.h"

struct TransmittanceQuaryRecord
{
    // input
    const Extinction* extFunc; // reference to the extinction function
    const Float a; // start of the medium
    const Float b; // end of the medium
    const int n; // path length to evaluate
    const int samples; // number of samples

    // output
    int extCalls; // cost of evaluating transmittance
    Float transmittance;


    TransmittanceQuaryRecord(const Extinction* ext, Float a, Float b, int n, int samples) : extFunc(ext), a(a), b(b), n(n), samples(samples) {
        extCalls = 0;
        transmittance = 0;
    }
};

class Estimator {
public:
    Estimator();
    virtual ~Estimator();

    // numerical estimation
    virtual Float T(TransmittanceQuaryRecord& rec, Sampler* sampler) const = 0;

    virtual void preProcess(Extinction* extFunc, Float a, Float b);
    virtual string getName() const = 0;

    Float sampleExpFF(const TransmittanceQuaryRecord& rec, Sampler* sampler, Float maj) const;
    Float sampleUniFF(const TransmittanceQuaryRecord& rec, Sampler* sampler) const;

    Float pdfUniFF(Float x, const TransmittanceQuaryRecord& rec) const;
    Float pdfExpFF(Float x, const TransmittanceQuaryRecord& rec, Float maj) const;
protected:
};
