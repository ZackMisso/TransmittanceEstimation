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

#define RESOLUTION 100000.0
#define NEWTONS_ITERATIONS 10

// TODO: figure out if these are used anymore
#define EXT_IMP_SAMPS 10
#define MAX_ITERATIONS 3000
#define START_ITERATION 100
#define START_BATCH 0
#define MAX_BATCHES 100
#define IMAGE_RESOLUTION_X 512
#define IMAGE_RESOLUTION_Y 512

// #define JOBSPATH "/home/firal/Documents/Research/TransSamples/jobs/"
// #define JOBSPATH "/Users/ZackMisso/Documents/Dartmouth/TransSamples/jobs/"
// #define JOBSPATH "/Users/fortuna/Documents/Research/TransSamples/jobs/"
#define JOBSPATH "/Users/corneria/Documents/Research/TransSamples/jobs/"
#define DATAPATH "/Users/corneria/Documents/Research/TransSamples/data/"
#define NOISEPATH "noise/"
#define NULLRATIOPATH "nullratio/"
#define ANALYSISPATH "analysis/"
#define CONVERGENCEPATH "convergence/"
#define ITERATIVEPATH "iterative/"
#define DUMBITERATIVEPATH "itdumbfinal/"
#define EFFOPTPATH "effopt/"
#define GUIPATH "gui/"
// #define LOGSPATH "/home/firal/Documents/Research/TransSamples/logs/"
// #define LOGSPATH "/Users/ZackMisso/Documents/Dartmouth/TransSamples/logs/"
// #define LOGSPATH "/Users/fortuna/Documents/Research/TransSamples/logs/"
#define LOGSPATH "/Users/corneria/Documents/Research/TransSamples/logs/"

// used for meetings
// #define DROPBOXPATH "/Users/fortuna/Dropbox/"
#define DROPBOXPATH "/Users/fortuna/Dropbox/Volume-Sampling/"

// #define USE_SINGLE_PRECISION
#define USE_DOUBLE_PRECISION
// #define USE_ARBITRARY_PRECISION

#ifdef USE_SINGLE_PRECISION
typedef float Float;
#endif

#ifdef USE_DOUBLE_PRECISION
typedef double Float;
#endif

#include <chrono>
using namespace std::chrono_literals;
using namespace std::chrono;
using namespace std;

using clockc = std::chrono::high_resolution_clock;

enum AxisVar
{
    AXIS_NONE,
    CONST_C, MIN_CONST_C, MAJ_CONST_C,
    LIN_M, MIN_LIN_M, MAJ_LIN_M,
    LIN_Y, MIN_LIN_Y, MAJ_LIN_Y,
    SCOS_H, MIN_SCOS_H, MAJ_SCOS_H,
    SCOS_S, MIN_SCOS_S, MAJ_SCOS_S,
    COS_H, MIN_COS_H, MAJ_COS_H,
    COS_S, MIN_COS_S, MAJ_COS_S,
    COS_K, MIN_COS_K, MAJ_COS_K,
    COS_Y, MIN_COS_Y, MAJ_COS_Y,
    EXP_H, MIN_EXP_H, MAJ_EXP_H,
    EXP_S, MIN_EXP_S, MAJ_EXP_S,
    EXP_K, MIN_EXP_K, MAJ_EXP_K,
    EXP_Y, MIN_EXP_Y, MAJ_EXP_Y,
    STEP_H, MIN_STEP_H, MAJ_STEP_H,
    STEP_D, MIN_STEP_D, MAJ_STEP_D,
    STEP_Y, MIN_STEP_Y, MAJ_STEP_Y,
    VALUE_F, MIN_VALUE_F, MAJ_VALUE_F,
    VALUE_A, MIN_VALUE_A, MAJ_VALUE_A,
    VALUE_X, MIN_VALUE_X, MAJ_VALUE_X,
    VALUE_Y, MIN_VALUE_Y, MAJ_VALUE_Y,
    PERLIN_F, MIN_PERLIN_F, MAJ_PERLIN_F,
    PERLIN_A, MIN_PERLIN_A, MAJ_PERLIN_A,
    GAUSS_H, MIN_GAUSS_H, MAJ_GAUSS_H,
    GAUSS_M, MIN_GAUSS_M, MAJ_GAUSS_M,
    ELEVATED_GAUSS_M, MIN_ELEVATED_GAUSS_M, MAJ_ELEVATED_GAUSS_M,
    ELEVATED_GAUSS_H, MIN_ELEVATED_GAUSS_H, MAJ_ELEVATED_GAUSS_H,
    ELEVATED_GAUSS_SIG, MIN_ELEVATED_GAUSS_SIG, MAJ_ELEVATED_GAUSS_SIG,
    ELEVATED_GAUSS_Y, MIN_ELEVATED_GAUSS_Y, MAJ_ELEVATED_GAUSS_Y,
    HOLE_M, MIN_HOLE_M, MAJ_HOLE_M,
    HOLE_H, MIN_HOLE_H, MAJ_HOLE_H,
    HOLE_SIG, MIN_HOLE_SIG, MAJ_HOLE_SIG,
    HOLE_C, MIN_HOLE_C, MAJ_HOLE_C,
    GAUSS_SIG, MIN_GAUSS_SIG, MAJ_GAUSS_SIG,
    MIN_SCALE_SCALE, MAJ_SCALE_SCALE,
    MIN_NULL_RATIO, MAJ_NULL_RATIO,

    DIST,      // TODO
    MAJ_SCALE,
    MAJ_TRANS
};

enum ExtinctionType
{
    EXT_NONE = 0x0,
    EXT_STEP,
    EXT_SCOS,
    EXT_COS,
    EXT_LIN,
    EXT_EXP,
    EXT_PERLIN,
    EXT_CONST,
    EXT_VALUE,
    EXT_NPERLIN,
    EXT_GAUSS,
    EXT_ELEVATED_GAUSS,
    EXT_SCALE,
    EXT_TIGHT,
    EXT_NULL_RATIO,
    EXT_HOLE,

    EXT_COS_HIGH_FREQ,
    EXT_GAUSS_RIGHT,
    EXT_LIN_INC,
    EXT_LIN_DEC
};

enum ExtinctionVar
{
    EXT_CONST_C,

    EXT_LIN_M,
    EXT_LIN_Y,

    EXT_SCOS_H,
    EXT_SCOS_S,

    EXT_COS_H,
    EXT_COS_S,
    EXT_COS_K,
    EXT_COS_Y,

    EXT_EXP_H,
    EXT_EXP_S,
    EXT_EXP_K,
    EXT_EXP_Y,

    EXT_STEP_H,
    EXT_STEP_D,
    EXT_STEP_Y,

    EXT_PERLIN_F,
    EXT_PERLIN_Y,

    EXT_VAR_NONE
};

enum EstimatorType
{
    EST_TRACKLENGTH = 0,
    EST_RATIO,
    EST_RESIDUAL,
    EST_RESIDUALRATIO,
    EST_RAY,
    EST_EXACT,
    EST_E_52,
    EST_PSERIES_CUMULATIVE,
    EST_NFD,
    EST_NFR,
    EST_NFR_CDF,
    EST_NFR_REV,
    EST_NFR_UNIFORM,
    EST_NFR_UNIFORM_REV,
    EST_BIDIR,
    EST_RATMIS_HYP,
    EST_UNI,
    EST_UNI_PRINCIPLED,
    EST_UNI_PRINCIPLED_NORMALIZED,
    EST_UNI_PMF,
    EST_UNI_PMF_NORMALIZED,
    EST_UNI_INVERSE,
    EST_UNI_INVERSE_RAT_PMF,
    EST_UNI_INVERSE_PRINCIPLED,
    EST_UNI_INVERSE_PMF,
    EST_UNI_INVERSE_SCORE,
    EST_RATMISPWR,
    EST_PSERIES_RAT,
    EST_PSERIES_RAT_MULTITERM,
    EST_PSERIES_RAT_STRAT,
    EST_PSERIES_NFR,
    EST_PSERIES_NFR_PATH,
    EST_PSERIES_NFR_PRINCIPLED,
    EST_PSERIES_INTERP,
    EST_PSERIES_CDF,
    EST_PSERIES_CDF_PRINCIPLED,
    EST_PSERIES_POISSON,
    EST_PSERIES_SAND_BOX,
    EST_PSERIES_CUMULATIVE_RATIO,
    EST_PSERIES_CUMULATIVE_MIN,
    EST_EXPECTED,
    EST_NONE
};

enum EstimatorVarFloat
{
    EST_FL_NONE = 0
};

enum EstimatorVarInt
{
    EST_INT_NONE = 0,
    EST_INT_NAIVE_SAMPLES,
    EST_INT_COR_NAIVE_SAMPLES,
    EST_INT_REC_HYP_DIM_DIMS
};

enum ExtVarType
{
    EXT_VAR_INT,
    EXT_VAR_FLOAT
};

enum SamplerType
{
    SAMP_NONE,
    SAMP_IND,
    SAMP_LPQMC,
    SAMP_LATIN,
    SAMP_LATIN_IP,
    SAMP_REG,
    SAMP_REG_JIT,
    SAMP_HALTON,
    SAMP_HALTON_IP,
    SAMP_HAMMERSLEY,
    SAMP_HAMMERSLEY_IP,
    SAMP_LATIN_IP_VAN,
    SAMP_LATIN_IP_UNI
};

enum ScreenType
{
    SCR_MAIN = 0x1,
    SCR_ERROR = 0x2,
    SCR_EXT = 0x4,
    SCR_HEATMP = 0x8,
    SCR_COMPR = 0x10,
    SCR_GRID = 0x20,
    SCR_MASTER = 0x40,
    SCR_NONE = 0x0
};

enum ErrorType
{
    ET_VARIANCE = 0x1,
    ET_MEAN = 0x2,
    ET_ABSERROR = 0x4,
    ET_ABSRELERROR = 0x8,
    ET_EFFICIENCY = 0x10,
    ET_COST = 0x20,
    ET_EXPECTED = 0x40,
    ET_BIAS = 0x80,
    ET_SAMPVARIANCE = 0x100,
    ET_SAMPEFFICIENCY = 0x200
};

enum ThreadTaskType
{
    THREAD_NONE,
    THREAD_EXT_EVAL,
    THREAD_EST_EVAL_BLOCK,
    THREAD_EST_LOG_EVAL_BLOCK,
    THREAD_SAMP_EVAL,
    THREAD_EST_COMPARE,
    THREAD_SAMP_COMPARE,
    THREAD_OFF_EXT_EVAL,
    THREAD_OFF_GT_EVAL,
    THREAD_JANS_TEST,
    THREAD_JANS_TEST_SINGLE,
    THREAD_JANS_STRAT_TEST
};

enum RenderStage
{
    STAGE_EST_HEAT,
    STAGE_EST_BIAS,
    STAGE_ONE_HEAT,
    STAGE_TWO_HEAT,
    STAGE_COMPARE,
    STAGE_NONE,
    STAGE_GRAPH
};

struct InputData
{
    bool gui;
    bool exit;
    bool batch;
    int batchStart;
    ExtinctionType extType;
    EstimatorType  estType;
    std::string    batchFile;
};

typedef vector<pair<Float, Float> > HistData;
typedef pair<Float, Float> Pdd;
typedef pair<uint32_t, uint32_t> Puu;
typedef pair<int, int> Pii;
typedef pair<AxisVar, string> Pxs;
typedef pair<AxisVar, string> Pys;
typedef pair<EstimatorVarFloat, Float> Pestd;
typedef pair<EstimatorVarInt, int> Pesti;

struct ExtVarGuiData
{
    ExtVarType varType;
    float floatval;
    int intval;
    string name;
};

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
