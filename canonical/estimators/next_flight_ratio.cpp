#include "next_flight_ratio.h"

NextFlight_RatioTracking::NextFlight_RatioTracking() : Estimator() { }

Float NextFlight_RatioTracking::T(TransmittanceQuaryRecord& rec, Sampler* sampler) const {
    Float x = rec.a;

    vector<Float> samps = vector<Float>();

    Float k = rec.extFunc->calculateMajorant((rec.b + rec.a) / 2.0);

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


string NextFlight_RatioTracking::getName() const {
    return "next_flight_ratio";
}
