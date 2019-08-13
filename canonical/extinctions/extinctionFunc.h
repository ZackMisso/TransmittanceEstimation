#pragma once

#include "../common.h"
#include "../hist.h"
#include "func.h"

class Extinction {
public:
    Extinction();
    ~Extinction();

    Float calculateExtinction(Float x, int& extCalls) const;
    Float calculateExtinction(Float x, bool log) const;
    Float calculateExtinctionIntegral(Float a, Float b) const;
    Float calculateExtinctionVariance(Float a, Float b) const;
    Float calculateAverageExtinction(Float a, Float b) const;

    Float calculateMajorant(Float x) const;
    Float calculateMajorantIntegral(Float a, Float b) const;
    Float calculateMajorantVariance(Float a, Float b) const;
    Float calculateMajorantAverage(Float a, Float b) const;

    Float calculateMinorant(Float x) const;
    Float calculateMinorantIntegral(Float a, Float b) const;
    Float calculateMinorantVariance(Float a, Float b) const;
    Float calculateMinorantAverage(Float a, Float b) const;

    void setOpticalDepth(Float c);

    void preProcess();

    Float calculateMaxExtinction(Float a, Float b) const;
    Float calculateMinExtinction(Float a, Float b) const;

    Float calculateMinMajorantEfficiency() const;
    Float calculateMaxMajorantEfficiency() const;

    Extinction* copy() const;
    string getName() const;

    ExtinctionType getType() const;

    // getter methods
    Func* getExtinctionFunction() const;
    Func* getMajorantFunction() const;
    Func* getMinorantFunction() const;
    Float getA() const;
    Float getB() const;

    // setter methods
    void setExtinctionFunction(Func* param);
    void setMajorantFunction(Func* param);
    void setMinorantFunction(Func* param);
    void setA(Float param);
    void setB(Float param);
protected:
    Func* extinctionFunction;
    Func* majorantFunction;
    Func* minorantFunction;

    Float a;
    Float b;
};
