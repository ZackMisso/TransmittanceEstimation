#include "expected.h"

Expected::Expected() : PrimaryEstimator() {
    type = EST_EXPECTED;
}

Float Expected::T(TransmittanceQuaryRecord& rec, Sampler* sampler) const {
    Float od = rec.extFunc->calculateExtinctionIntegral(rec.a, rec.b);
    rec.transmittance = exp(-od);
    return exp(-od);
}

Float Expected::simpleT(Float ext, Float maj, int term, Float a, Float b) const
{
    // TODO
    return 0.0;
}

string Expected::getName() const {
    return "expected";
}

string Expected::getFullName() const {
    return "expected";
}

Estimator* Expected::copy() const {
    return new Expected();
}
