#pragma once

#include "base_includes.h"

class CanonicalTest {
public:
    CanonicalTest(std::string prefix,
                  Estimator* estimator,
                  Extinction* extinction,
                  Sampler* sampler,
                  long base_seed,
                  bool equal_cost,
                  uint32_t max_cost,
                  uint32_t samples,
                  uint32_t trials,
                  uint32_t resolution);

    void runEstimator(Extinction* ext,
                      Estimator* est,
                      Sampler* sampler,
                      uint32_t samples,
                      uint32_t trials,
                      EstimatorTestResult& testResult,
                      uint32_t location,
                      uint32_t resolution,
                      long base_seed,
                      bool equal_cost,
                      uint32_t max_cost);
};
