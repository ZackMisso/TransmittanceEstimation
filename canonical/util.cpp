#include "util.h"

Float Util::lerpFactor(Float first, Float second, Float desired) {
    return (desired - first) / (second - first);
}

Float Util::lerp(Float one, Float two, Float t) {
    return (two - one) * t + one;
}

Float Util::clamp(Float val, Float min, Float max) {
    if (val > max) return max;
    if (val < min) return min;
    return val;
}

float Util::clamp(float val, float min, float max) {
    if (val > max) return max;
    if (val < min) return min;
    return val;
}

int Util::clamp(int val, int min, int max) {
    if (val > max) return max;
    if (val < min) return min;
    return val;
}

int Util::max(int one, int two) {
    return (one > two) ? one : two;
}

int Util::min(int one, int two) {
    return (one > two) ? two : one;
}

Float Util::max(Float one, Float two) {
    return (one > two) ? one : two;
}

Float Util::min(Float one, Float two) {
    return (one > two) ? two : one;
}

bool Util::equals(Float one, Float two) {
    return (Util::abs(two - one) < EPSILON);
}

bool Util::equals(float one, float two) {
    return (Util::abs(two - one) < EPSILON);
}

bool Util::lessThan(Float less, Float greater) {
    return !((less - greater) > -EPSILON);
}

bool Util::lessThan(float less, float greater) {
    return !((less - greater) > -EPSILON);
}

bool Util::greaterThan(Float greater, Float less) {
    return (less - greater) < EPSILON;
}

bool Util::greaterThan(float greater, float less) {
    return (less - greater) < EPSILON;
}


Float Util::abs(Float value) {
    if (value >= 0.0) return value;
    return -value;
}

float Util::abs(float value) {
    if (value >= 0.f) return value;
    return -value;
}

Float Util::sum(const HistData& hist) {
    Float total = 0;
    for (int i = 0; i < hist.size(); i++) {
        total += hist[i].second;
    }
    return total;
}

// this is very expensive O(N^2) TODO: rewrite later
// TODO: test this thoroughly
// void Util::findIncreasingOrder(vector<Float>& values, vector<int>& order) {
//     Float prevVal = -1.0;
//     Float currentVal = 100000000000.0;
//     vector<int> currentIndex = vector<int>();
//
//     for (int i = 0; i < values.size(); ++i) {
//         for (int j = 0; j < values.size(); ++j) {
//             if (values[j] > prevVal && values[j] < currentVal) {
//                 currentIndex.clear();
//                 currentIndex.push_back(j);
//                 currentVal = values[j];
//             } else if (values[j] == currentVal) {
//                 currentIndex.push_back(j);
//             }
//         }
//
//         for (int j = 0; j < currentIndex.size(); ++j) {
//             order.push_back(currentIndex[j]);
//         }
//
//         prevVal = currentVal;
//         currentVal = 100000000000.0;
//         i += currentIndex.size() - 1;
//     }
// }

Float Util::findValueAtPoint(const HistData& hist, Float x) {
    int index = 0;
    if (hist.size() == 0) return 0.0;
    while(hist[index].first <= x && index < hist.size() - 1)
        index++;
    const Pdd prev = hist[index-1];
    const Pdd next = hist[index];
    Float pos = (x - prev.first) / (next.first - prev.first);
    return (next.second - prev.second) * pos + prev.second;
}

Pii Util::findBinsBetweenPoint(const HistData& hist, Float x) {
    Pii bin = Pii(-1, -1);

    for (int i = 0; i < hist.size(); i++) {
        if (x <= hist[i].second) {
            bin.second = i;
            bin.first = i - 1;
            i = hist.size();
        }
    }

    if (bin.first == -1 && bin.second != -1) {
        bin.first = 0;
        bin.second = 1;
        // cout << "HAH???" << endl;
    }

    if (bin.first == -1 && bin.second == -1) {
        bin.second = hist.size() - 1;
        bin.first = hist.size() - 2;
        cout << "NO HAH" << endl;
    }

    return bin;
}

void Util::sort(HistData& hist) {
    if (hist.size() <= 1) return;

    HistData one = HistData();
    HistData two = HistData();

    for (int i = 0; i < hist.size(); i++) {
        if (i % 2 == 0) one.push_back(hist[i]);
        else two.push_back(hist[i]);
    }

    hist.clear();
    sort(one);
    sort(two);
    merge(one, two, hist);
}

void Util::merge(HistData& one, HistData& two, HistData& res) {
    int i = 0;
    int j = 0;
    while (i < one.size() && j < two.size()) {
        if (one[i].first < two[j].first) {
            res.push_back(one[i++]);
        } else if (one[i].first > two[j].first) {
            res.push_back(two[j++]);
        } else {
            if (one[i].second < two[j].second) res.push_back(two[j++]);
            else res.push_back(one[i++]);
        }
    }
    while (i < one.size()) {
        res.push_back(one[i++]);
    }
    while (j < two.size()) {
        res.push_back(two[j++]);
    }
}

void Util::sort(HistData& hist, HistData& copyOne, HistData& copyTwo) {
    // TODO
    if (hist.size() <= 1) return;

    HistData one = HistData();
    HistData two = HistData();

    for (int i = 0; i < hist.size(); i++) {
        if (i % 2 == 0) one.push_back(hist[i]);
        else two.push_back(hist[i]);
    }

    hist.clear();
    sort(one);
    sort(two);
    merge(one, two, hist);
}

void Util::merge(HistData& one, HistData& two, HistData& res,
                 HistData& c1_one, HistData& c1_two, HistData& copyOne,
                 HistData& c2_one, HistData& c2_two, HistData& copyTwo)
{
    // TODO
    int i = 0;
    int j = 0;
    while (i < one.size() && j < two.size()) {
        if (one[i].first < two[j].first) {
            res.push_back(one[i++]);
        } else if (one[i].first > two[j].first) {
            res.push_back(two[j++]);
        } else {
            if (one[i].second < two[j].second) res.push_back(two[j++]);
            else res.push_back(one[i++]);
        }
    }
    while (i < one.size()) {
        res.push_back(one[i++]);
    }
    while (j < two.size()) {
        res.push_back(two[j++]);
    }
}

bool Util::one(Float a, Float b, Float x) {
    if (x <= a) return false;
    if (x >= b) return false;
    return true;
}

Float Util::nearestNeighborValue(VarHistMap* map, Float x, Float y, int flags) {
    Float value = 0.0;
    Float bestDistance = 100000000.0;
    int bestIndex = -1;

    for (int i = 0; i < map->size(HRF_HIST); i++) {
        Float tmpx = map->getData(HRF_NONE, 0)[i].first;
        Float tmpy = map->getData(HRF_NONE, 0)[i].second;

        Float newDist = distance(x, y, tmpx, tmpy);
        if (newDist < bestDistance) {
            bestDistance = newDist;
            bestIndex = i;
        }
    }

    if (flags == HRF_VAR) return map->getHist(bestIndex)->getVariance();
    if (flags == HRF_MEANS) return map->getHist(bestIndex)->getMean();
    if (flags == HRF_RELERR) return map->getHist(bestIndex)->getAbsRelError();
    if (flags == HRF_ABSERR) return map->getHist(bestIndex)->getAbsError();

    return map->getHist(bestIndex)->getVariance();
}

Float Util::bilinearInterpValue(VarHistMap* map, Float x, Float y, int flags) {
    // TODO
    return 0.0;
}

Float Util::distance(Float x, Float y, Float xx, Float yy) {
    return (x - xx) * (x - xx) + (y - yy) * (y - yy);
}

int Util::midpoint(Float val) {
    int flor = floor(double(val));
    Float partial = val - (Float)flor;
    if (partial < 0.5) return flor;
    return ceil(double(val));
}

int Util::mod(Float val) {
    // int flor = floor(val);
    return floor(double(val));
}

// Incorporate this into extinction later to be more efficient
HistData Util::convertISHistToRenderHist(HistData& data, Float b) {

    HistData hist = HistData();

    Float leng = ( data[data.size() - 1].first + data[0].first );
    Float stride = ( data[1].first - data[0].first );

    for (int i = 0; i < data.size() - 1; i++) {
        Float x = i * stride;
        Float nextX = x + stride;
        hist.push_back(Pdd(x, 0.0));
        hist.push_back(Pdd(x, data[i].second));
        hist.push_back(Pdd(nextX, data[i].second));
        hist.push_back(Pdd(nextX, 0.0));
    }

    stride = (b - data[data.size() - 1].first) * 2.0;
    // cout << "STRIDE: " << stride << endl;
    // cout << "FIRST: " << data[data.size() - 1].first << endl;
    hist.push_back(Pdd(b - stride, 0.0));
    hist.push_back(Pdd(b - stride, data[data.size() - 1].second));
    hist.push_back(Pdd(b, data[data.size() - 1].second));
    hist.push_back(Pdd(b, 0.0));

    // Keeping for rendering purposes later
    // for (int i = 0; i < data.size() - 1; i++) {
    //     if (i == data.size() - 1) {
    //         hist.push_back(data[i]);
    //     } else {
    //         hist.push_back(data[i]);
    //
    //         Float midpoint = (data[i + 1].first + data[i].first) / 2.0;
    //
    //         hist.push_back(Pdd(midpoint, data[i].second));
    //         hist.push_back(Pdd(midpoint, data[i + 1].second));
    //     }
    // }

    return hist;
}

void Util::printHist(HistData& data) {
    for (int i = 0; i < data.size(); i++) {
        cout << i << ": " << data[i].first << ", " << data[i].second << endl;
    }
}

Float Util::verifyNonZero(Float param) {
    if (param == 0.0) return EPSILON;
    return param;
}

ExtinctionType Util::getExtinctionFromVar(ExtinctionVar var) {
    if (var == EXT_CONST_C) return EXT_CONST;
    else if (var == EXT_SCOS_S) return EXT_SCOS;
    else if (var == EXT_SCOS_H) return EXT_SCOS;
    else if (var == EXT_COS_H) return EXT_COS;
    else if (var == EXT_COS_S) return EXT_COS;
    else if (var == EXT_COS_K) return EXT_COS;
    else if (var == EXT_COS_Y) return EXT_COS;
    else if (var == EXT_EXP_H) return EXT_EXP;
    else if (var == EXT_EXP_K) return EXT_EXP;
    else if (var == EXT_EXP_S) return EXT_EXP;
    else if (var == EXT_EXP_Y) return EXT_EXP;
    else if (var == EXT_LIN_M) return EXT_LIN;
    else if (var == EXT_LIN_Y) return EXT_LIN;
    else if (var == EXT_STEP_H) return EXT_STEP;
    else if (var == EXT_STEP_D) return EXT_STEP;
    else if (var == EXT_STEP_Y) return EXT_STEP;
    else if (var == EXT_PERLIN_F) return EXT_PERLIN;
    else if (var == EXT_PERLIN_Y) return EXT_PERLIN;
    return EXT_NONE;
}

ExtinctionVar Util::getDefaultFromType(ExtinctionType type) {
    if (type == EXT_CONST) return EXT_CONST_C;
    else if (type == EXT_SCOS) return EXT_SCOS_S;
    else if (type == EXT_COS) return EXT_COS_S;
    else if (type == EXT_LIN) return EXT_LIN_Y;
    else if (type == EXT_STEP) return EXT_STEP_H;
    else if (type == EXT_EXP) return EXT_EXP_S;
    else if (type == EXT_PERLIN) return EXT_PERLIN_F;
    return EXT_VAR_NONE;
}

string Util::errToString(ErrorType type) {
    if (type == ET_VARIANCE) return "var";
    else if (type == ET_MEAN) return "mean";
    else if (type == ET_ABSERROR) return "abs";
    else if (type == ET_ABSRELERROR) return "absrel";
    else if (type == ET_EFFICIENCY) return "eff";
    else if (type == ET_COST) return "cost";
    else if (type == ET_EXPECTED) return "expec";
    else if (type == ET_BIAS) return "bias";
    else if (type == ET_SAMPVARIANCE) return "sampvar";
    else if (type == ET_SAMPEFFICIENCY) return "sampeff";
    else return "unk";
}

string Util::estVarToString(EstimatorVarInt var) {
    if (var == EST_INT_NAIVE_SAMPLES) return "ext_samples";

    return "";
}

string Util::estVarToString(EstimatorVarFloat var) {
    return "";
}

Float Util::EXP(Float val)
{
    #ifdef USE_ARBITRARY_PRECISION
    return mpfr_pp::exp(val);
    #else
    return exp(val);
    #endif
}

Float Util::LOG(Float val)
{
    #ifdef USE_ARBITRARY_PRECISION
    return mpfr_pp::log(val);
    #else
    return log(val);
    #endif
}

Float Util::POW(Float base, Float power)
{
    #ifdef USE_ARBITRARY_PRECISION
    return mpfr_pp::pow(base, power);
    #else
    return pow(base, power);
    #endif
}

Float Util::ABS(Float val)
{
    #ifdef USE_ARBITRARY_PRECISION
    return mpfr_pp::abs(val);
    #else
    return abs(val);
    #endif
}

Float Util::COS(Float val)
{
    #ifdef USE_ARBITRARY_PRECISION
    return mpfr_pp::cos(val);
    #else
    return cos(val);
    #endif
}

Float Util::SIN(Float val)
{
    #ifdef USE_ARBITRARY_PRECISION
    return mpfr_pp::sin(val);
    #else
    return sin(val);
    #endif
}

float Util::randomDigitScramble(float f, unsigned scramble)
{
    return (unsigned(f*0x100000000LL) ^ scramble) * 2.3283064365386962890625e-10f;
}
