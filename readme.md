Canonical Tests

In this repository we provide the implementation of generating our canonical
plots as seen in the paper Integral formulations of volumetric
transmittance. While our paper utilizes a false color transformation and
provides isocontours, we leave out our that messy implementation and just
provide the logic and means of generating the base heatmaps. We also provide
an intuitive abstraction of transmittance estimators for any individuals who
wants to test their own against ours and previous work.

To compile the program simply do the following:

cmake ./ && make

And to run the program you have the following options:

./transm_est samp_name all <other options>
./transm_est samp_name ext_name_1 ... ext_name_n est_name_1 ... est_name_n <other options>

The first option runs all combinations of estimators and extinctions utilizing the specified sampler, while the second option runs all combinations of the estimators and extinctions specified.

The sampler is optional, and if no sampler is specified the sampler defaults to independent samples.
At least one extinction and one estimator must be specified, otherwise the program will terminate without running any experiments.

List of <other options>:
prefix <str> - adds a prefix to the paths for all saved images
base_seed <int> - sets the base seed for the rng
equal_cost - specifies that the test is equal cost
             if a test is equal cost then the sampler is only allowed to be an independent sampler, and samples/trials will be hardcoded to 1.
samples <int> - sets the sample count (disabled if equal cost)
trials <int> - sets the number of trials (disabled if equal cost)
resolution <int> - sets the resolution of the plots

List of available samplers:

halton - Halton sampler
hammersley - Hammersley sampler
independent - Independent sampler
latinip - In-Place Latin Hypercubes sampler

List of available extinction functions:

const - Constant extinction: f(x) = c
cos - Cosine extinction: f(x) = y + h * cos(s * x + k)
gauss - Gaussian extinction: f(x) = h * e^((-(x-m)^2) / (2 * s))
hole - Hole extinction: f(x) = c - h * e^((-(x-m)^2) / (2 * s))
lin_inc - Linear increasing extinction: f(x) = m * x + y
lin_dec - Linear decreasing extinction: f(x) = -m * x + y

List of available transmittance estimators:

bidirectional - Bidirectional MIS
expected - Ground Truth
next_flight_ratio - Next-flight
pseries_cmf - p-series CMF
pseries_cumulative - p-series cumulative
pseries_next_flight_ratio - Next-flight reformulated in p-series framework
pseries_ratio - Ratio-tracking reformulated in p-series framework
ratio - Ratio_tracking
track_length - Delta-tracking / track-length
unidirectional - Unidirectional MIS

All results are written as png and hdr images.
