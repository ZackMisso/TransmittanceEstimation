#include "common.h"
#include "hist.h"
#include <tgmath.h>

// just a collection of math helper functions

class Util {
public:
    // type prints
    static void printHist(HistData& data);
    // lerp methods
    static Float lerpFactor(Float first, Float second, Float desired);
    static Float lerp(Float one, Float two, Float t);
    // clamp methods
    static Float clamp(Float val, Float min, Float max);
    static float clamp(float val, float min, float max);
    static int clamp(int val, int min, int max);
    // min/max functions
    static int max(int one, int two);
    static int min(int one, int two);
    static Float max(Float one, Float two);
    static Float min(Float one, Float two);
    // equals functions
    static bool equals(Float one, Float two);
    static bool equals(float one, float two);
    static bool lessThan(Float less, Float greater);
    static bool lessThan(float less, float greater);
    static bool greaterThan(Float greater, Float less);
    static bool greaterThan(float greater, float less);
    // abs functions
    static Float abs(Float value);
    static float abs(float value);
    // averaging methods
    static Float sum(const HistData& hist);
    static Float findValueAtPoint(const HistData& hist, Float x);
    static Pii findBinsBetweenPoint(const HistData& hist, Float x);
    // methods for mc estimators
    static bool one(Float a, Float b, Float x);
    // multiple sort
    // static void findIncreasingOrder(vector<Float>& values, vector<int>& order);
    // sort one at a time
    static void sort(HistData& hist);
    static void merge(HistData& one, HistData& two, HistData& hist);
    // sort three by the same sorting as the first
    static void sort(HistData& hist, HistData& copyOne, HistData& copyTwo);
    static void merge(HistData& one, HistData& two, HistData& hist,
                      HistData& c1_one, HistData& c1_two, HistData& copyOne,
                      HistData& c2_one, HistData& c2_two, HistData& copyTwo);
    // color methods for images
    static Float nearestNeighborValue(VarHistMap* map, Float x, Float y, int flags);
    static Float bilinearInterpValue(VarHistMap* map, Float x, Float y, int flags);
    static Float distance(Float x, Float y, Float xx, Float yy);
    static int midpoint(Float val);
    static int mod(Float val);
    // hist conversion methods
    static HistData convertISHistToRenderHist(HistData& data, Float b);
    static Float verifyNonZero(Float param);
    static ExtinctionType getExtinctionFromVar(ExtinctionVar var);
    static ExtinctionVar getDefaultFromType(ExtinctionType type);
    static string errToString(ErrorType type);
    static string estVarToString(EstimatorVarInt var);
    static string estVarToString(EstimatorVarFloat var);
    static Float EXP(Float val);
    static Float LOG(Float val);
    static Float POW(Float base, Float power);
    static Float ABS(Float val);
    static Float COS(Float val);
    static Float SIN(Float val);
    // sampling methods
    static float randomDigitScramble(float f, unsigned scramble);
};
