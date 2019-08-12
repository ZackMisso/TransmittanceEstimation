#include "independent.h"

Independent::Independent() : Sampler() {
    type = SAMP_IND;
}

Independent::Independent(unsigned int seed) : Sampler(seed) {
    type = SAMP_IND;
}

Independent::Independent(unsigned int seedOne, unsigned int seedTwo) : Sampler(seedOne, seedTwo) {
    type = SAMP_IND;
}

Independent::~Independent() {
    // nothing to clean up
}

Float Independent::next1D() {
    return sampleRNG.nextFloat();
}

Pdd Independent::next2D() {
    return Pdd(sampleRNG.nextFloat(), sampleRNG.nextFloat());
}

void Independent::loggedNext1D(Float& dimVal, Float& jitVal) {
    dimVal = sampleRNG.nextFloat();
    jitVal = 0.0;
}

uint32_t Independent::next1D_U() {
    return sampleRNG.nextUInt();
}

void Independent::nextSample() {
    // does nothing
}

void Independent::reset() {
    reseed(sampSeed, jitSeed);
}

Sampler* Independent::copy() {
    Independent* newSampler = new Independent(sampSeed, jitSeed);
    return newSampler;
}

string Independent::getName() const {
    return "independent";
}

bool Independent::correlated() const {
    return true;
}
