#include "sampler.h"

Sampler::Sampler() {
    sampSeed = 0x45454;
    jitSeed = 0x54545;
    numDimensions = 0;
    numSamples = 0;

    reseed(sampSeed, jitSeed);
}

Sampler::Sampler(uint32_t seed) {
    sampSeed = seed;
    jitSeed = 0x54545;
    numDimensions = 0;
    numSamples = 0;

    reseed(sampSeed, jitSeed);
}

Sampler::Sampler(uint32_t seedOne, uint32_t seedTwo) {
    sampSeed = seedOne;
    jitSeed = seedTwo;
    numDimensions = 0;
    numSamples = 0;

    reseed(sampSeed, jitSeed);
}

Sampler::~Sampler() {
    // does nothing
}

void Sampler::reseed() {
    reseedSampler(sampSeed);
    reseedJitter(jitSeed);
}

void Sampler::reseed(unsigned int seed) {
    reseedSampler(seed);
    reseedJitter(jitSeed);
}

void Sampler::reseed(unsigned int seedOne, unsigned int seedTwo) {
    reseedSampler(seedOne);
    reseedJitter(seedTwo);
}

void Sampler::reseedSampler(unsigned int seed) {
    sampSeed = seed;
    // srand(sampSeed);
    uint64_t r1 = 142;
    // cout << "R1: " << r1 << endl;
    uint64_t r2 = seed;
    // cout << "R2: " << r2 << endl;
    sampleRNG = pcg32(r1, r2);
}

void Sampler::reseedJitter(unsigned int seed) {
    jitSeed = seed;
    // srand(jitSeed);
    // uint64_t r1 = rand();
    // uint64_t r2 = rand();
    jitterRNG = pcg32(2185, seed);
}

SamplerType Sampler::getType() const {
    return type;
}

pcg32 Sampler::getSampleRNG() const {
    return sampleRNG;
}

pcg32 Sampler::getJitterRNG() const {
    return jitterRNG;
}

uint32_t Sampler::getSampSeed() const {
    return sampSeed;
}

uint32_t Sampler::getJitSeed() const {
    return jitSeed;
}

uint32_t Sampler::getNumDimensions() const {
    return numDimensions;
}

uint32_t Sampler::getNumSamples() const {
    return numSamples;
}

void Sampler::setSampSeed(uint32_t param) {
    sampSeed = param;
}

void Sampler::setJitSeed(uint32_t param) {
    jitSeed = param;
}

void Sampler::setNumDimensions(uint32_t param) {
    numDimensions = param;
}

void Sampler::setNumSamples(uint32_t param) {
    numSamples = param;
}
