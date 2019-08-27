#pragma once

#include "../common.h"
#include <pcg32.h>

class Sampler {
public:
    Sampler();
    Sampler(uint32_t seed);
    Sampler(uint32_t seedOne, uint32_t seedTwo);
    virtual ~Sampler();

    virtual void reseed();
    virtual void reseed(unsigned int seed);
    virtual void reseed(unsigned int seedOne, unsigned int seedTwo);

    virtual void reseedSampler(unsigned int seed);
    virtual void reseedJitter(unsigned int seed);

    virtual void reset() = 0;

    virtual Float next1D() = 0;
    virtual Pdd next2D() = 0;

    virtual void nextSample() = 0;

    virtual Sampler* copy() = 0;

    virtual string getName() const = 0;

    pcg32 getSampleRNG() const;
    pcg32 getJitterRNG() const;
    uint32_t getSampSeed() const;
    uint32_t getJitSeed() const;
    uint32_t getNumDimensions() const;
    uint32_t getNumSamples() const;

    virtual void setSampSeed(uint32_t param);
    virtual void setJitSeed(uint32_t param);
    virtual void setNumDimensions(uint32_t param);
    virtual void setNumSamples(uint32_t param);

protected:
    pcg32 sampleRNG;
    pcg32 jitterRNG;
    uint32_t sampSeed;
    uint32_t jitSeed;
    uint32_t numDimensions;
    uint32_t numSamples;
};
