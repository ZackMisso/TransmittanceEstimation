#include "canonical_test.h"
#include "floatimage.h"
#include "base_includes.h"
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fstream>
#include <vector>

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

    std::vector<Extinction*> extinctions = std::vector<Extinction*>();
    std::vector<Estimator*> estimators = std::vector<Estimator*>();
    Sampler* sampler = new Independent();

    std::string prefix = ".";
    long base_seed = 0x34da32d;
    bool equal_cost = false;
    uint32_t max_cost = 16384;
    uint32_t samples = 16;
    uint32_t trials = 16;
    uint32_t resolution = 512;

    for (int i = 1; i < argc; ++i)
    {
        // sampler setting
        if (strcmp(argv[i], "independent") == 0)
        {
            delete sampler;
            sampler = new Independent();
        }
        else if (strcmp(argv[i], "halton") == 0)
        {
            delete sampler;
            sampler = new Halton();
        }
        else if (strcmp(argv[i], "hammersley") == 0)
        {
            delete sampler;
            sampler = new Hammersley();
        }
        else if (strcmp(argv[i], "latinip") == 0)
        {
            delete sampler;
            sampler = new LatinHyperCubesInPlace();
        }

        // extinction setting
        else if (strcmp(argv[i], "const") == 0)
        {
            extinctions.push_back(create_const_extinction());
        }
        else if (strcmp(argv[i], "cos") == 0)
        {
            extinctions.push_back(create_cos_extinction());
        }
        else if (strcmp(argv[i], "gauss") == 0)
        {
            extinctions.push_back(create_gauss_extinction());
        }
        else if (strcmp(argv[i], "hole") == 0)
        {
            extinctions.push_back(create_hole_extinction());
        }
        else if (strcmp(argv[i], "lin_inc") == 0)
        {
            extinctions.push_back(create_lin_inc_extinction());
        }
        else if (strcmp(argv[i], "lin_dec") == 0)
        {
            extinctions.push_back(create_lin_dec_extinction());
        }

        // estimator setting
        else if (strcmp(argv[i], "bidirectional") == 0)
        {
            estimators.push_back(new Bidirectional());
        }
        else if (strcmp(argv[i], "expected") == 0)
        {
            estimators.push_back(new Expected());
        }
        else if (strcmp(argv[i], "next_flight_ratio") == 0)
        {
            estimators.push_back(new NextFlight_RatioTracking());
        }
        else if (strcmp(argv[i], "pseries_cmf") == 0)
        {
            estimators.push_back(new Pseries_CDF());
        }
        else if (strcmp(argv[i], "pseries_cumulative") == 0)
        {
            estimators.push_back(new Pseries_Cumulative());
        }
        else if (strcmp(argv[i], "pseries_next_flight_ratio") == 0)
        {
            estimators.push_back(new Pseries_NextFlightRatio());
        }
        else if (strcmp(argv[i], "pseries_ratio") == 0)
        {
            estimators.push_back(new Pseries_Ratio());
        }
        else if (strcmp(argv[i], "ratio") == 0)
        {
            estimators.push_back(new RatioTracking());
        }
        else if (strcmp(argv[i], "track_length") == 0)
        {
            estimators.push_back(new TrackLength());
        }
        else if (strcmp(argv[i], "unidirectional") == 0)
        {
            estimators.push_back(new Unidirectional());
        }

        // other option setting
        else if (strcmp(argv[i], "prefix") == 0)
        {
            prefix = std::string(argv[++i]);
        }
        else if (strcmp(argv[i], "base_seed") == 0)
        {
            base_seed = (long)stoi(argv[++i]);
        }
        else if (strcmp(argv[i], "equal_cost") == 0)
        {
            equal_cost = true;
        }
        else if (strcmp(argv[i], "samples") == 0)
        {
            samples = stoi(argv[++i]);
        }
        else if (strcmp(argv[i], "trials") == 0)
        {
            trials = stoi(argv[++i]);
        }
        else if (strcmp(argv[i], "resolution") == 0)
        {
            resolution = stoi(argv[++i]);
        }

        // specifying all
        else if (strcmp(argv[i], "all") == 0)
        {
            extinctions.push_back(create_const_extinction());
            extinctions.push_back(create_cos_extinction());
            extinctions.push_back(create_gauss_extinction());
            extinctions.push_back(create_hole_extinction());
            extinctions.push_back(create_lin_inc_extinction());
            extinctions.push_back(create_lin_dec_extinction());

            estimators.push_back(new Bidirectional());
            estimators.push_back(new Expected());
            estimators.push_back(new NextFlight_RatioTracking());
            estimators.push_back(new Pseries_CDF());
            estimators.push_back(new Pseries_Cumulative());
            estimators.push_back(new Pseries_NextFlightRatio());
            estimators.push_back(new Pseries_Ratio());
            estimators.push_back(new RatioTracking());
            estimators.push_back(new TrackLength());
            estimators.push_back(new Unidirectional());
        }
    }

    if (estimators.size() == 0) std::cout << "Warning: no esitmator specified" << std::endl;
    if (extinctions.size() == 0) std::cout << "Warning: no extinction specified" << std::endl;

    // run canonical tests for each combination of specified extinctions
    // and estimators
    for (int i = 0; i < estimators.size(); ++i)
    {
        for (int j = 0; j < extinctions.size(); ++j)
        {
            Estimator* est = estimators[i];
            Extinction* ext = extinctions[j];

            CanonicalTest(prefix,
                          est,
                          ext,
                          sampler,
                          base_seed,
                          equal_cost,
                          max_cost,
                          samples,
                          trials,
                          resolution);
        }
    }

    for (int i = 0; i < estimators.size(); ++i) delete estimators[i];
    for (int i = 0; i < extinctions.size(); ++i) delete extinctions[i];
    delete sampler;

    return 0;
}
