#include "next_flight_ratio.h"

NextFlight_RatioTracking::NextFlight_RatioTracking() : PrimaryEstimator() {
    type = EST_NFR;
}

Float NextFlight_RatioTracking::T(TransmittanceQuaryRecord& rec, Sampler* sampler) const {
    // Float k = rec.maj;
    Float x = rec.a;

    vector<Float> samps = vector<Float>();

    Float k = rec.extFunc->calculateMajorant((rec.b + rec.a) / 2.0);

    // Float Tr = exp(-k * (rec.b - rec.a));

    Float Tr = exp(-k * (rec.b - rec.a));

    do {
        x += sampleExpFF(rec, sampler, k);

        if (x >= rec.b) break;

        Float ext = rec.extFunc->calculateExtinction(x, rec.extCalls);
        samps.push_back((k - ext) / k);

        Float extProd = 1.0;
        for (int i = 0; i < samps.size(); i++) extProd *= samps[i];

        Tr += extProd * exp(-k * (rec.b - x));
    } while(true);

    rec.transmittance = Tr;

    return Tr;
}

Float NextFlight_RatioTracking::simpleT(Float ext, Float maj, int term, Float a, Float b) const
{
    Float tr = exp(-maj * (b - a));

    Float ratio = 1.0;
    for (int i = 1; i <= term; ++i)
    {
        Float x = (b - a) * Float(i) / Float(term+1) + a;
        ratio *= (maj - ext) / maj;
        tr += ratio * exp(-maj * (b - x));
    }

    return tr;
}


string NextFlight_RatioTracking::getName() const {
    return "next_flight_ratio";
}

string NextFlight_RatioTracking::getFullName() const {
    return "next_flight_ratio";
}

Estimator* NextFlight_RatioTracking::copy() const {
    NextFlight_RatioTracking* estimator = new NextFlight_RatioTracking();

    // TODO

    return estimator;
}
