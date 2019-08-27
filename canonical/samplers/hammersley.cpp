#include "hammersley.h"
#include "../util.h"

Hammersley::Hammersley() : Sampler() {
    currentDim = 0;
    currentSample = 0;
}

Hammersley::Hammersley(unsigned int seed) : Sampler(seed) {
    currentDim = 0;
    currentSample = 0;
}

Hammersley::Hammersley(unsigned int seedOne, unsigned int seedTwo) : Sampler(seedOne, seedTwo) {
    currentDim = 0;
    currentSample = 0;
}

void Hammersley::reseed() {
    reseedSampler(sampSeed);
    halton.init_random(sampleRNG);
    scramble = sampleRNG.nextUInt();
}

void Hammersley::reseed(unsigned int seed) {
    sampSeed = seed;
    reseedSampler(sampSeed);
    halton.init_random(sampleRNG);
    scramble = sampleRNG.nextUInt();
}

void Hammersley::reseed(unsigned int seedOne, unsigned int seedTwo) {
    sampSeed = seedOne;
    reseedSampler(sampSeed);
    halton.init_random(sampleRNG);
    scramble = sampleRNG.nextUInt();
}

Hammersley::~Hammersley() {
    // does nothing
}

Float Hammersley::next1D() {
    Float sample = 0.0;

    if (currentDim == 0) {
        sample = Util::randomDigitScramble(float(currentSample * inv), scramble);
    } else {
        if (currentDim > 255) {
            return sampleRNG.nextFloat();
        }

        sample = halton.sample(currentDim, currentSample);
    }

    currentDim++;
    return sample;
}

Pdd Hammersley::next2D() {
    return Pdd(next1D(), next1D());
}

void Hammersley::nextSample() {
    currentSample++;
    currentDim = 0;
}

void Hammersley::reset() {
    reseed(sampSeed, jitSeed);
    currentSample = 0;
    currentDim = 0;
}

Sampler* Hammersley::copy() {
    return new Hammersley(sampSeed, jitSeed);
}

string Hammersley::getName() const {
    return "hammersley";
}

void Hammersley::setNumSamples(uint32_t param) {
    numSamples = param;
    inv = 1.0 / Float(param);
}
