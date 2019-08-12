#pragma once

#include "sampler.h"
#include "halton_sampler.h"

class Halton : public Sampler {
public:
    Halton();
    Halton(unsigned int seed);
    Halton(unsigned int seedOne, unsigned int seedTwo);

    virtual ~Halton();

    virtual void reseed();
    virtual void reseed(unsigned int seed);
    virtual void reseed(unsigned int seedOne, unsigned int seedTwo);

    virtual Float next1D();
    virtual Pdd next2D();

    virtual void loggedNext1D(Float& dimVal, Float& jitVal);

    virtual void nextSample();

    virtual void reset();

    virtual Sampler* copy();

    virtual bool correlated() const;

    virtual string getName() const;

protected:
    Halton_sampler halton;
    uint32_t currentDim;
    uint32_t currentSample;
};
