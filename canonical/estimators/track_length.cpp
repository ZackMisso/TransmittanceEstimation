#include "track_length.h"
#include <tgmath.h>

TrackLength::TrackLength() : Estimator() { }

Float TrackLength::T(TransmittanceQuaryRecord& rec, Sampler* sampler) const {
    // Choose a constant k such that k >= ext(x) for all x[a,b]
    Float k = rec.extFunc->calculateMajorant((rec.b + rec.a) / 2.0);
    Float x = rec.a;
    x = 0.0;

    do {
        // Sample a random value y with pdf(y) = k * exp(-ky) set x = a + y
        x += sampleExpFF(rec, sampler, k);

        // If x > b stop and return 1
        if (x >= rec.b) {
            rec.transmittance = 1.0;
            return 1.0;
        }
        // Sample a uniform random number g[0,1]
        Float g = sampler->next1D();

        // If g <= ext(x) / k; stop and return 0
        if (g <= rec.extFunc->calculateExtinction(x, rec.extCalls) / k) {
            rec.transmittance = 0.0;
            return 0.0;
        }
    } while(true);
    // this should never be reached
    return 0.0;
}

string TrackLength::getName() const {
    return "track_length";
}
