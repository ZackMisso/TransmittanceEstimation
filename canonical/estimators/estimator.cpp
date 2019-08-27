#include "estimator.h"
#include <tgmath.h>

Estimator::Estimator() {
    // does nothing
}

Estimator::~Estimator() {
    // does nothing
}

void Estimator::preProcess(Extinction* extFunc, Float a, Float b) {
    // does nothing
}

Float Estimator::sampleExpFF(const TransmittanceQuaryRecord& rec, Sampler* sampler, Float maj) const {
    return -log(1.0 - sampler->next1D()) / maj;
}

Float Estimator::sampleUniFF(const TransmittanceQuaryRecord& rec, Sampler* sampler) const {
    return sampler->next1D() * (rec.b - rec.a) + rec.a;
}

Float Estimator::pdfExpFF(Float ffd, const TransmittanceQuaryRecord& rec, Float maj) const {
    return maj * exp(-maj * ffd);
}

Float Estimator::pdfUniFF(Float x, const TransmittanceQuaryRecord& rec) const {
    return 1.0 / (rec.b - rec.a);
}
