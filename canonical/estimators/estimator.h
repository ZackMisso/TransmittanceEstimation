#pragma once

#include "../extinctions/extinctionFunc.h"
#include "../samplers/sampler.h"
#include "../hist.h"

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
    // int iterations;
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
    virtual Float simpleT(Float ext, Float maj, int term, Float a, Float b) const = 0;

    virtual void preProcess(Extinction* extFunc, Float a, Float b);
    virtual string getName() const = 0;
    virtual string getFullName() const = 0;

    virtual Estimator* copy() const = 0;

    Float sampleExpFF(const TransmittanceQuaryRecord& rec, Sampler* sampler, Float maj) const;
    Float sampleUniFF(const TransmittanceQuaryRecord& rec, Sampler* sampler) const;

    Float pdfUniFF(Float x, const TransmittanceQuaryRecord& rec) const;
    Float pdfExpFF(Float x, const TransmittanceQuaryRecord& rec, Float maj) const;

    // TODO :: add non-quary versions of sample and pdf

    virtual void updateAxisValue(AxisVar var, Float value) = 0;
    virtual vector<AxisVar> getValidAxis() const = 0;

    virtual void updateEstVar(EstimatorVarFloat var, Float value) = 0;
    virtual void updateEstVar(EstimatorVarInt var, int value) = 0;
    virtual void getEstVar(EstimatorVarFloat var, Float& data) const = 0;
    virtual void getEstVar(EstimatorVarInt var, int& data) const = 0;
    virtual vector<EstimatorVarFloat> getValidEstFloatVars() const = 0;
    virtual vector<EstimatorVarInt> getValidEstIntVars() const = 0;

    // getter / setters
    void setSamplingRate(int param);
    EstimatorType getType();
protected:
    EstimatorType type;
    int samplingRate;
};
