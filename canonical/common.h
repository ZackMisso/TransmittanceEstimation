#pragma once

#include <iostream>
#include <vector>
#include <utility>

using std::endl;
using std::cout;
using std::vector;
using std::pair;

#define M_PI 3.14159265358979323846f
#define EPSILON 1e-8

// number of raymarching steps taken to estimate integrals
#define RESOLUTION 100000.0

// #define USE_SINGLE_PRECISION
#define USE_DOUBLE_PRECISION
// TODO: maybe carry over support for this
// #define USE_ARBITRARY_PRECISION

#ifdef USE_SINGLE_PRECISION
typedef float Float;
#endif

#ifdef USE_DOUBLE_PRECISION
typedef double Float;
#endif

using namespace std;

// pair datastructures
typedef vector<pair<Float, Float> > HistData;
typedef pair<Float, Float> Pdd;
typedef pair<uint32_t, uint32_t> Puu;

struct EstimatorTestResult
{
    uint32_t samples;
    uint32_t trials;
    Float gtTransmittance;
    Float transmittance;
    Float variance;
    Float cost;
};

struct EstimatorStratTestResult
{
    uint32_t samples;
    uint32_t trials;
    Float gtTransmittance;

    Float base_transmittance;
    Float base_variance;
    Float base_cost;

    Float strat_transmittance;
    Float strat_variance;
    Float strat_cost;
};

typedef vector<EstimatorTestResult> FullResults;
typedef vector<EstimatorStratTestResult> FullStratResults;
