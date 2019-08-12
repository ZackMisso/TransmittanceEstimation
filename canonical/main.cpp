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
//
// void generate_all_tests()
// {
//     for (int i = 0; i < 1024 * 1024 / 32; ++i)
//     // for (int i = 0; i < 3; ++i)
//     {
//         // make the directory containing the images
//         string command = "mkdir data/" + std::to_string(i);
//         system(command.c_str());
//
//         std::ofstream file("jobs/transm_"+std::to_string(i)+".sh");
//
//         file << "#!/bin/bash\n";
//         file << "# The name of the job, can be anything, simply used when displaying the list of running jobs\n";
//         file << "#$ -N transm_"+std::to_string(i)+"\n";
//         file << "# Combining output/error messages into one file\n";
//         file << "#$ -j y\n";
//         file << "# Set memory request:\n";
//         file << "#$ -l vf=1G\n";
//         file << "# Set walltime request:\n";
//         file << "#$ -l h_rt=02:59:00\n";
//         file << "# One needs to tell the queue system to use the current directory as the working directory\n";
//         file << "# Or else the script may fail as it will execute in your top level home directory /home/username\n";
//         file << "#$ -cwd\n";
//         file << "# then you tell it retain all environment variables (as the default is to scrub your environment)\n";
//         file << "#$ -V\n";
//         file << "# Now comes the command to be executed\n";
//         file << "./transm_cluster ratio "+ to_string(i) + " 128\n";
//         file << "exit 0\n";
//
//         file.close();
//
//         command = "qsub jobs/transm_"+std::to_string(i)+".sh";
//         system(command.c_str());
//     }
// }
//
// void combine_current_tests(int start_index, int trials)
// {
//     FloatImage reference_rand;
//     FloatImage reference_strat;
//     FloatImage reference_mean_rand;
//     FloatImage reference_mean_strat;
//
//     if (start_index == 0)
//     {
//         reference_rand = FloatImage(512, 512, 3);
//         reference_strat = FloatImage(512, 512, 3);
//         reference_mean_rand = FloatImage(512, 512, 3);
//         reference_mean_strat = FloatImage(512, 512, 3);
//
//         for (int i = 0; i < reference_rand.size(); ++i)
//         {
//             reference_rand(i) = 0.0;
//             reference_strat(i) = 0.0;
//             reference_mean_rand(i) = 0.0;
//             reference_mean_strat(i) = 0.0;
//         }
//     }
//     else
//     {
//         reference_rand = FloatImage("reference_rand.hdr");
//         reference_strat = FloatImage("reference_strat.hdr");
//         reference_mean_rand = FloatImage("reference_mean_rand.hdr");
//         reference_mean_strat = FloatImage("reference_mean_strat.hdr");
//     }
//
//     std::string estimator_rand = "ratio_var_rand.hdr";
//     std::string estimator_strat = "ratio_var_strat.hdr";
//     std::string estimator_mean_rand = "ratio_mean_rand.hdr";
//     std::string estimator_mean_strat = "ratio_mean_strat.hdr";
//
//     FloatImage total_rand = FloatImage(512, 512, 3);
//     FloatImage total_strat = FloatImage(512, 512, 3);
//     FloatImage total_mean_rand = FloatImage(512, 512, 3);
//     FloatImage total_mean_strat = FloatImage(512, 512, 3);
//
//     for (int i = 0; i < total_rand.size(); ++i)
//     {
//         total_rand(i) = 0.0;
//         total_strat(i) = 0.0;
//         total_mean_rand(i) = 0.0;
//         total_mean_strat(i) = 0.0;
//     }
//
//     int end_index = (start_index + 5999 < 1024*1024/trials) ?
//                         start_index + 5999 :
//                         1024*1024/trials;
//
//     for (int i = start_index; i < end_index; ++i)
//     {
//         std::cout << "i: " << i << std::endl;
//
//         FloatImage tmp_rand("data/"+to_string(i)+"/" + estimator_rand);
//         FloatImage tmp_strat("data/"+to_string(i)+"/" + estimator_strat);
//         FloatImage tmp_mean_rand("data/"+to_string(i)+"/"+estimator_mean_rand);
//         FloatImage tmp_mean_strat("data/"+to_string(i)+"/"+estimator_mean_strat);
//
//         tmp_rand = tmp_rand * trials;
//         tmp_strat = tmp_strat * trials;
//         tmp_mean_rand = tmp_mean_rand * trials;
//         tmp_mean_strat = tmp_mean_strat * trials;
//
//         total_rand = total_rand + tmp_rand;
//         total_strat = total_strat + tmp_strat;
//         total_mean_rand = total_mean_rand + tmp_mean_rand;
//         total_mean_strat = total_mean_strat + tmp_mean_strat;
//     }
//
//     reference_rand = reference_rand * trials * start_index + total_rand;
//     reference_strat = reference_strat * trials * start_index + total_strat;
//     reference_mean_rand = reference_mean_rand * trials * start_index + total_mean_rand;
//     reference_mean_strat = reference_mean_strat * trials * start_index + total_mean_strat;
//
//     reference_rand = reference_rand / (trials * end_index);
//     reference_strat = reference_strat / (trials * end_index);
//     reference_mean_rand = reference_mean_rand / (trials * end_index);
//     reference_mean_strat = reference_mean_strat / (trials * end_index);
//
//     reference_rand.write("reference_rand.hdr");
//     reference_strat.write("reference_strat.hdr");
//     reference_mean_rand.write("reference_mean_rand.hdr");
//     reference_mean_strat.write("reference_mean_strat.hdr");
// }

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
