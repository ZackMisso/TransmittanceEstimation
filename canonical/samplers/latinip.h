#pragma once

#include "sampler.h"

class LatinHyperCubesInPlace : public Sampler {
public:
    LatinHyperCubesInPlace();
    LatinHyperCubesInPlace(unsigned int seed);
    LatinHyperCubesInPlace(unsigned int seedOne, unsigned int seedTwo);

    virtual void reseed();
    virtual void reseed(unsigned int seed);
    virtual void reseed(unsigned int seedOne, unsigned int seedTwo);

    virtual Float next1D();
    virtual Pdd next2D();

    virtual void reset();

    virtual void loggedNext1D(Float& dimVal, Float& jitVal);

    virtual void nextSample();

    virtual Sampler* copy();

    virtual bool correlated() const;

    virtual string getName() const;

protected:
    Float jit;
    uint32_t currentDim;
    uint32_t currentSample;
};
