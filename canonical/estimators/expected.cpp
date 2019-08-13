#include "expected.h"

Expected::Expected() : Estimator() {
    type = EST_EXPECTED;
}

Float Expected::T(TransmittanceQuaryRecord& rec, Sampler* sampler) const {
    Float od = rec.extFunc->calculateExtinctionIntegral(rec.a, rec.b);
    rec.transmittance = exp(-od);
    return exp(-od);
}

string Expected::getName() const {
    return "expected";
}
