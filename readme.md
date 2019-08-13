Canonical Tests

In this repository we provide the implementation of generating our canonical
plots as seen in figure x of the paper Integral formulations of volumetric
transmittance. While our paper utilizes a false color transformation and
provides isocontours, we leave out our that messy implementation and just
provide the logic and means of generating the base heatmaps. We also provide
an intuitive abstraction of transmittance estimators for any individuals who
want to test their own against ours and previous work.

To compile the program simply do the following:

cmake ./ && make

And to run the program you have the following options:

./transm_est all
./transm_est ext_name_1 ... ext_name_n est_name_1 ... est_name_n

The first option runs all combinations of estimators and extinctions, while the
seconbd   
