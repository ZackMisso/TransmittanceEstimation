#pragma once

#include "sampler.h"
#include "halton_sampler.h"

class Hammersley : public Sampler {
public:
    Hammersley();
    Hammersley(unsigned int seed);
    Hammersley(unsigned int seedOne, unsigned int seedTwo);

    virtual ~Hammersley();

    virtual void reseed();
    virtual void reseed(unsigned int seed);
    virtual void reseed(unsigned int seedOne, unsigned int seedTwo);

    virtual Float next1D();
    virtual Pdd next2D();

    virtual void nextSample();

    virtual void reset();

    virtual Sampler* copy();

    virtual string getName() const;

    virtual void setNumSamples(uint32_t param);

protected:
    Halton_sampler halton;
    Float inv;
    uint32_t scramble;
    uint32_t currentDim;
    uint32_t currentSample;
};
