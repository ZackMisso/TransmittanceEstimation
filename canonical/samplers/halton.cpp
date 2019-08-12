#include "halton.h"

Halton::Halton() : Sampler() {
    type = SAMP_HALTON;
    // halton.init_random(sampSeed);
    currentDim = 0;
    currentSample = 0;
}

Halton::Halton(unsigned int seed) : Sampler(seed) {
    type = SAMP_HALTON;
    // halton.init_random(sampSeed);
    currentDim = 0;
    currentSample = 0;
}

Halton::Halton(unsigned int seedOne, unsigned int seedTwo) : Sampler(seedOne, seedTwo) {
    type = SAMP_HALTON;
    currentDim = 0;
    currentSample = 0;
}

// halton does not require jitter

void Halton::reseed() {
    reseedSampler(sampSeed);
    halton.init_random(sampleRNG);
    currentDim = 0;
}

void Halton::reseed(unsigned int seed) {
    sampSeed = seed;
    reseedSampler(sampSeed);
    halton.init_random(sampleRNG);
    currentDim = 0;
}

void Halton::reseed(unsigned int seedOne, unsigned int seedTwo) {
    sampSeed = seedOne;
    reseedSampler(sampSeed);
    halton.init_random(sampleRNG);
    currentDim = 0;
}

Halton::~Halton() {
    // does nothing
}

Float Halton::next1D() {
    if (currentDim > 255) {
        // cout << "PAST SAMPLE" << endl;
        currentDim++;
        Float samp = sampleRNG.nextFloat();
        // cout << "Actual Samp: " << samp << endl;
        return samp;
    }

    Float sample = halton.sample(currentDim, currentSample);
    currentDim++;
    return sample;
}

Pdd Halton::next2D() {
    return Pdd(next1D(), next1D());
}

void Halton::loggedNext1D(Float& dimVal, Float& jitVal) {
    if (currentDim > 255) {
        // cout << "PAST SAMPLE" << endl;
        dimVal = sampleRNG.nextFloat();
        currentDim++;
        jitVal = 0.0;
        return;
    }

    Float sample = halton.sample(currentDim, currentSample);
    currentDim++;
    dimVal = sample;
    jitVal = 0.0;
}

void Halton::nextSample() {
    currentSample++;
    currentDim = 0;
}

void Halton::reset() {
    reseed(sampSeed, jitSeed);
    currentSample = 0;
    currentDim = 0;
}

Sampler* Halton::copy() {
    return new Halton(sampSeed, jitSeed);
}

bool Halton::correlated() const {
    return true;
}

string Halton::getName() const {
    return "halton";
}
