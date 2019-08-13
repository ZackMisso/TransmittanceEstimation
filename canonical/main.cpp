#include "canonical_test.h"
#include "floatimage.h"
#include "base_includes.h"
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fstream>

Extinction* create_cos_extinction()
{
    CosFunc* cosFunc = new CosFunc();
    cosFunc->setY(1.1);
    cosFunc->setS(20.0);
    cosFunc->setK(0.8);
    cosFunc->setH(0.4);
    NullRatioFunc* majFuncCos = new NullRatioFunc();
    Extinction* cosExt = new Extinction();
    cosExt->setExtinctionFunction(cosFunc);
    cosExt->setMajorantFunction(majFuncCos);
    cosExt->setMinorantFunction(new TightConstFunc(cosFunc, false));
    majFuncCos->setDependent(cosFunc);

    return cosExt;
}

Extinction* create_const_extinction()
{
    ConstFunc* constFunc = new ConstFunc();
    NullRatioFunc* majFuncConst = new NullRatioFunc();
    Extinction* constExt = new Extinction();
    constExt->setExtinctionFunction(constFunc);
    constExt->setMajorantFunction(majFuncConst);
    constExt->setMinorantFunction(new TightConstFunc(constFunc, false));
    return constExt;
}

Extinction* create_gauss_extinction()
{
    GaussFunc* gaussFunc = new GaussFunc();
    NullRatioFunc* majFuncGauss = new NullRatioFunc();
    Extinction* gaussExt = new Extinction();
    gaussFunc->setM(0.32);
    gaussFunc->setSig(0.05);
    gaussFunc->setH(0.8);
    gaussExt->setExtinctionFunction(gaussFunc);
    gaussExt->setMajorantFunction(majFuncGauss);
    gaussExt->setMinorantFunction(new TightConstFunc(gaussFunc, false));
    return gaussExt;
}

Extinction* create_hole_extinction()
{
    HoleFunc* holeFunc = new HoleFunc();
    NullRatioFunc* majFuncHole = new NullRatioFunc();
    Extinction* holeExt = new Extinction();
    holeFunc->setM(0.32);
    holeFunc->setSig(0.05);
    holeFunc->setH(0.8);
    holeFunc->setC(1.0);
    holeExt->setExtinctionFunction(holeFunc);
    holeExt->setMajorantFunction(majFuncHole);
    holeExt->setMinorantFunction(new TightConstFunc(holeFunc, false));
    return holeExt;
}

Extinction* create_lin_dec_extinction()
{
    LinDecFunc* linDecFunc = new LinDecFunc();
    NullRatioFunc* majFuncLinDec = new NullRatioFunc();
    Extinction* linDecExt = new Extinction();
    linDecExt->setExtinctionFunction(linDecFunc);
    linDecExt->setMajorantFunction(majFuncLinDec);
    linDecExt->setMinorantFunction(new TightConstFunc(linDecFunc, false));
    return linDecExt;
}

Extinction* create_lin_inc_extinction()
{
    LinIncFunc* linIncFunc = new LinIncFunc();
    NullRatioFunc* majFuncLinInc = new NullRatioFunc();
    Extinction* linIncExt = new Extinction();
    linIncExt->setExtinctionFunction(linIncFunc);
    linIncExt->setMajorantFunction(majFuncLinInc);
    linIncExt->setMinorantFunction(new TightConstFunc(linIncFunc, false));
    return linIncExt;
}

int main(int argc, char* argv[])
{
    std::cout << "hello world" << std::endl;

    Extinction* ext = create_cos_extinction();
    Estimator* est = new RatioTracking();
    Sampler* samp = new Independent();

    std::string prefix = "test/";
    long base_seed = 0x34da32d;
    bool equal_cost = true;
    uint32_t max_cost = 16384;
    uint32_t samples = 1;
    uint32_t trials = 1;
    uint32_t resolution = 512;

    CanonicalTest(prefix,
                  est,
                  ext,
                  samp,
                  base_seed,
                  equal_cost,
                  max_cost,
                  samples,
                  trials,
                  resolution);

    delete ext;
    delete est;
    delete samp;

    //
    // std::string est_string = std::string(argv[1]);
    //
    // if (est_string == "gen")
    // {
    //     generate_all_tests();
    //     return 0;
    // }
    //
    // if (est_string == "combine")
    // {
    //     combine_current_tests(atoi(argv[1]), 32);
    // }
    //
    // std::cout << est_string << std::endl;
    // std::string index = std::string(argv[2]);
    // std::cout << "index: " << argv[2] << std::endl;
    //
    // //return 0;
    //
    // Estimator* estimator = nullptr;
    // uint32_t samples = atoi(argv[3]);
    // uint32_t trials = 32;
    //
    // if (est_string == "ratio")
    // {
    //     estimator = new RatioTracking();
    // }
    // else if (est_string == "cdf")
    // {
    //     estimator = new Pseries_CDF();
    // }
    // else if (est_string == "pratio")
    // {
    //     estimator = new Pseries_Ratio();
    // }
    // else return 0;
    //
    // pcg32 rng(0x3cf5a, 1);
    //
    // for (int i = 0; i < atoi(index.c_str()); ++i) rng.nextUInt();
    //
    // // under 3 hour run times:
    // // 128 x 8 for bidirectional
    // // 128 x 32 for ratio
    // // 128 x 32 for pseries-cdf
    // // x for pseries-cumulative
    // // x for unidirectional
    // // x for track-length
    // // x for next-flight
    //
    // JansStratTest("data/"+index,
    //               estimator,
    //               ext,
    //               rng.nextUInt(),
    //               samples,
    //               trials,
    //               512);

    return 0;
}
