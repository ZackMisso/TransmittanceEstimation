#include "canonical_test.h"
#include "floatimage.h"
#include "util.h"

unsigned int simple_hash(unsigned int x)
{
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}

CanonicalTest::CanonicalTest(std::string prefix,
                             Estimator* estimator,
                             Extinction* extinction,
                             Sampler* sampler,
                             long base_seed,
                             bool equal_cost,
                             uint32_t max_cost,
                             uint32_t samples,
                             uint32_t trials,
                             uint32_t resolution)
{
    FullResults results = FullResults();

    Float maxTrans = 1.0;
    Float ninTrans = 0.0;
    Float baseTrans = 0.0;

    ninTrans = 0.98 * maxTrans;
    baseTrans = 0.01 * maxTrans;

    results.resize(resolution * resolution);

    for (int i = 0; i < resolution; ++i)
    {
        // if (i % 100 == 0)
        // {
        cout << extinction->getName() << " " << estimator->getName() << " i: " << i << endl;
        // }

        for (int j = 0; j < resolution; ++j)
        {
            Extinction* ext = extinction;

            Float minMajorantEfficiency = ext->calculateMinMajorantEfficiency();
            Float maxMajorantEfficiency = ext->calculateMaxMajorantEfficiency();

            ext->setA(0.0);
            ext->setB(1.0);

            Func* majFunc = ext->getMajorantFunction();
            Func* extFunc = ext->getExtinctionFunction();

            Float desiredTransmittance = maxTrans - (baseTrans + ninTrans * Float(j) / Float(resolution - 1));
            Float sigmaT = -Util::LOG(desiredTransmittance);

            Float efficiency = (minMajorantEfficiency + (maxMajorantEfficiency - minMajorantEfficiency) * Float(resolution - i - 1) / Float(resolution - 1));

            extFunc->solveForIntegral(0.0, 1.0, sigmaT);

            // majorant function should always be set to null-ratio
            ((NullRatioFunc*)majFunc)->setRatio(efficiency);

            ext->preProcess();

            runEstimator(extinction,
                         estimator,
                         sampler,
                         samples,
                         trials,
                         results[i * resolution + j],
                         i * resolution + j,
                         resolution,
                         base_seed + i * resolution + j,
                         equal_cost,
                         max_cost);
        }
    }

    FloatImage trans = FloatImage(resolution, resolution, 3);
    FloatImage var = FloatImage(resolution, resolution, 3);
    FloatImage cost = FloatImage(resolution, resolution, 3);
    FloatImage eff = FloatImage(resolution, resolution, 3);

    // write out the results to images
    for (int k = 0; k < 3; ++k)
    {
        for (int i = 0; i < resolution; ++i)
        {
            for (int j = 0; j < resolution; ++j)
            {
                trans(j, i, k) = (results[j + resolution * i].transmittance);
                cost(j, i, k) = (results[j + resolution * i].cost);
                var(j, i, k) = (results[j + resolution * i].variance);
                eff(j, i, k) = (results[j + resolution * i].variance * results[j + resolution * i].cost);
            }
        }
    }

    string path = prefix + "/" + estimator->getName();

    string extension = ".png";
    string extension2 = ".hdr";

    trans.write(path + "_mean" + extension);
    var.write(path + "_var" + extension);
    cost.write(path + "_cost" + extension);
    eff.write(path + "_eff" + extension);

    trans.write(path + "_mean" + extension2);
    var.write(path + "_var" + extension2);
    cost.write(path + "_cost" + extension2);
    eff.write(path + "_eff" + extension2);
}

void CanonicalTest::runEstimator(Extinction* ext,
                                 Estimator* est,
                                 Sampler* sampler,
                                 uint32_t samples,
                                 uint32_t trials,
                                 EstimatorTestResult& testResult,
                                 uint32_t location,
                                 uint32_t resolution,
                                 long base_seed,
                                 bool equal_cost,
                                 uint32_t max_cost)
{
    Float expected = ext->calculateExtinctionIntegral(0.0, 1.0);

    Float mean = 0.0;
    Float var = 0.0;
    Float cost = 0.0;

    if (!equal_cost)
    {
        for (int i = 0; i < trials; ++i)
        {
            Float trans = 0.0;
            Float cost_tmp = 0.0;

            Sampler* base_sampler = sampler->copy();
            base_sampler->reseed(simple_hash(base_seed + (i * resolution * resolution * resolution)));
            base_sampler->setNumSamples(samples);

            for (int j = 0; j < samples; ++j)
            {
                TransmittanceQuaryRecord rec(ext, 0.0, 1.0, -1, samples);
                trans += est->T(rec, base_sampler);
                cost_tmp += Float(rec.extCalls);

                base_sampler->nextSample();
            }

            trans /= Float(samples);
            cost_tmp /= Float(samples);

            if (est->getType() == EST_EXPECTED) i = trials;

            Float mean_new = mean + (1.0 / Float(i+1)) * (trans - mean);
            var = var + (trans - mean) * (trans - mean_new);
            mean = mean_new;

            cost += cost_tmp;
            delete base_sampler;
        }
    }
    else
    {
        // this experiment runs a 1-sample estimator for an arbitrary number
        // of trials until a maximum cost is reached for all simulations

        // base_sampler is assumed to always be independent for this case
        Sampler* base_sampler = new Independent();
        base_sampler->reseed(simple_hash(base_seed + (1 * resolution * resolution * resolution)));
        base_sampler->setNumSamples(1);
        trials = 0;

        while (cost < max_cost)
        {
            // run the estimator
            TransmittanceQuaryRecord rec(ext, 0.0, 1.0, -1, samples);
            Float trans = est->T(rec, base_sampler);
            int cost_tmp = rec.extCalls;
            sampler->nextSample();

            if (est->getType() == EST_EXPECTED) cost_tmp = max_cost;

            cost += cost_tmp;

            trials++;

            Float mean_new = mean + (1.0 / Float(trials)) * (trans - mean);

            var = var + (trans - mean) * (trans - mean_new);

            mean = mean_new;
        }

        delete base_sampler;
    }

    testResult.trials = trials;
    testResult.gtTransmittance = expected;
    testResult.transmittance = mean;
    testResult.variance = var / Float(trials);
    testResult.cost = cost / Float(trials);
}
