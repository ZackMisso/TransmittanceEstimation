#include "latinip.h"
#include "permute.h"

LatinHyperCubesInPlace::LatinHyperCubesInPlace() : Sampler() {
    currentDim = 0;
    currentSample = 0;
    jit = 0.0;
}

LatinHyperCubesInPlace::LatinHyperCubesInPlace(unsigned int seed) : Sampler(seed) {
    currentDim = 0;
    currentSample = 0;
    jit = 0.0;
}

LatinHyperCubesInPlace::LatinHyperCubesInPlace(unsigned int seedOne, unsigned int seedTwo) : Sampler(seedOne, seedTwo) {
    currentDim = 0;
    currentSample = 0;
    jit = 0.0;
}

void LatinHyperCubesInPlace::reseed() {
    Sampler::reseed();

    jit = 1.0;
}

void LatinHyperCubesInPlace::reseed(unsigned int seed) {
    Sampler::reseed(seed);

    jit = 1.0;
}

void LatinHyperCubesInPlace::reseed(unsigned int seedOne, unsigned int seedTwo) {
    Sampler::reseed(seedOne, seedTwo);

    jit = 1.0;
}

Float LatinHyperCubesInPlace::next1D() {
    int32_t samp = sampleRNG.nextUInt();
    int32_t value = Permutation::permute(currentSample, numSamples, samp);

    Float sample = Float(value) + 0.5;
    Float jitter = jit * (jitterRNG.nextFloat() - 0.5);
    sample += jitter;
    sample /= Float(numSamples);
    currentDim++;

    return sample;
}

Pdd LatinHyperCubesInPlace::next2D() {
    return Pdd(next1D(), next1D());
}

void LatinHyperCubesInPlace::nextSample() {
    reseedSampler(sampSeed);
    currentDim = 0;
    currentSample++;
}

void LatinHyperCubesInPlace::reset() {
    reseedSampler(sampSeed);
    reseedJitter(jitSeed);
    currentSample = 0;
    currentDim = 0;
}

Sampler* LatinHyperCubesInPlace::copy() {
    return new LatinHyperCubesInPlace(sampSeed, jitSeed);
}

string LatinHyperCubesInPlace::getName() const {
    return "latin_in_place";
}
