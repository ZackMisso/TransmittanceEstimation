#include "extinctionFunc.h"
#include "constFunc.h"
#include "tightConstFunc.h"

Extinction::Extinction() {
    a = 0.0;
    b = 1.0;
    extinctionFunction = nullptr;
    majorantFunction = nullptr;
    minorantFunction = nullptr;
}

Extinction::~Extinction() {
    delete extinctionFunction;
    delete minorantFunction;
    delete majorantFunction;
}

Float Extinction::calculateExtinction(Float x, int& extCalls) const {
    extCalls++;
    return extinctionFunction->evalFunction(x, a, b);
}

Float Extinction::calculateExtinction(Float x, bool log) const {
    return extinctionFunction->evalFunction(x, a, b);
}

Float Extinction::calculateExtinctionIntegral(Float a, Float b) const {
    return extinctionFunction->getIntegral();
}

Float Extinction::calculateExtinctionVariance(Float a, Float b) const {
    return extinctionFunction->getVariance();
}

Float Extinction::calculateAverageExtinction(Float a, Float b) const {
    return extinctionFunction->getIntegral() / (b - a);
}

Float Extinction::calculateMajorant(Float x) const {
    return majorantFunction->evalFunction(x, a, b);
}

Float Extinction::calculateMajorantIntegral(Float a, Float b) const {
    // if (b == this->b) // this seems very fishy
    //     return majorantFunction->getIntegral();
    return majorantFunction->evalIntegral(a, b);
}

Float Extinction::calculateMajorantVariance(Float a, Float b) const {
    return majorantFunction->getVariance();
}

Float Extinction::calculateMajorantAverage(Float a, Float b) const {
    return majorantFunction->getIntegral() / (b - a);
}

Float Extinction::calculateMinorant(Float x) const {
    return minorantFunction->evalFunction(x, a, b);
}

Float Extinction::calculateMinorantIntegral(Float a, Float b) const {
    // if (b == this->b)
    //     return majorantFunction->getIntegral();
    return majorantFunction->evalIntegral(a, b);
}

Float Extinction::calculateMinorantVariance(Float a, Float b) const {
    return minorantFunction->getVariance();
}

Float Extinction::calculateMinorantAverage(Float a, Float b) const {
    return minorantFunction->getIntegral() / (b - a);
}

Float Extinction::calculateMinMajorantEfficiency() const {
    return extinctionFunction->calculateMinEfficiency();
}

Float Extinction::calculateMaxMajorantEfficiency() const {
    return extinctionFunction->calculateMaxEfficiency();
}

void Extinction::setOpticalDepth(Float c) {
    extinctionFunction->solveForIntegral(a, b, c);
    // TODO: majorant / minorants ???
}

Float Extinction::calculateMaxExtinction(Float a, Float b) const {
    return extinctionFunction->getMax();
}

Float Extinction::calculateMinExtinction(Float a, Float b) const {
    return extinctionFunction->getMin();
}

void Extinction::preProcess() {
    // cout << "what" << endl;
    extinctionFunction->preProcess(a, b);
    // cout << "who" << endl;
    majorantFunction->preProcess(a, b);
    // cout << "where" << endl;
    minorantFunction->preProcess(a, b);
    // cout << "which" << endl;
}

Extinction* Extinction::copy() const {
    Extinction* newFunc = new Extinction();

    newFunc->setA(a);
    newFunc->setB(b);
    newFunc->setExtinctionFunction(extinctionFunction->copy());
    newFunc->setMajorantFunction(majorantFunction->copy());
    newFunc->setMinorantFunction(minorantFunction->copy());

    // cout << "post copy" << endl;

    if (newFunc->getMajorantFunction()->needsDependent())
    {
        newFunc->getMajorantFunction()->setDependent(newFunc->getExtinctionFunction());
    }

    if (newFunc->getMinorantFunction()->needsDependent())
    {
        newFunc->getMinorantFunction()->setDependent(newFunc->getExtinctionFunction());
    }

    return newFunc;
}

string Extinction::getName() const {
    return extinctionFunction->getName(FUNC_EXTINCTION);
}

ExtinctionType Extinction::getType() const {
    return extinctionFunction->getType();
}

// getter methods
Func* Extinction::getExtinctionFunction() const { return extinctionFunction; }
Func* Extinction::getMajorantFunction() const { return majorantFunction; }
Func* Extinction::getMinorantFunction() const { return minorantFunction; }

// setter methods
void Extinction::setExtinctionFunction(Func* param) {
    // if (extinctionFunction) delete extinctionFunction;
    extinctionFunction = param;
}

void Extinction::setMajorantFunction(Func* param) {
    // if (majorantFunction) delete majorantFunction;
    majorantFunction = param;
}

void Extinction::setMinorantFunction(Func* param) {
    // if (minorantFunction) delete minorantFunction;
    minorantFunction = param;
}

Float Extinction::getA() const { return a; }
Float Extinction::getB() const { return b; }

void Extinction::setA(Float param) { a = param; }
void Extinction::setB(Float param) { b = param; }
