#include "halton.h"

Halton::Halton() : Sampler() {
    currentDim = 0;
    currentSample = 0;
}

Halton::Halton(unsigned int seed) : Sampler(seed) {
    currentDim = 0;
    currentSample = 0;
}

Halton::Halton(unsigned int seedOne, unsigned int seedTwo) : Sampler(seedOne, seedTwo) {
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
        currentDim++;
        Float samp = sampleRNG.nextFloat();
        return samp;
    }

    Float sample = halton.sample(currentDim, currentSample);
    currentDim++;
    return sample;
}

Pdd Halton::next2D() {
    return Pdd(next1D(), next1D());
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

string Halton::getName() const {
    return "halton";
}
