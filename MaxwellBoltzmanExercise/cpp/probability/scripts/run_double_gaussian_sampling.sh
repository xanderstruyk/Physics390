#!/bin/sh

mkdir -p data/double_gaussian_sampling
mkdir -p png/double_gaussian_sampling

Nsamples=5000
Nevts=( 10 20 50 100 200 500 1000 2000 5000 10000 20000 50000 100000 200000);

#
# generate samples of given event sizes
# outputs first 10 samples of each to data/gaussian_sampling
#
for e in ${Nevts[*]}; do
 ./bin/test_double_gaussian_sampling $RANDOM $Nsamples $e
done;

#
# plot the 10 samples of each
#
i=0;
while (( $i < 10 )); do
    
    for e in ${Nevts[*]}; do
	root -l -q -b root/double_gaussian_sampling/plotDoubleGaussianSample.C\($i,$Nsamples,$e\);
    done
    
    (( i++ ));
    
done

#
# now plot the mean & variance from each of the 5k samples 
# and save summary stats
#
if [ -e ./data/double_gaussian_sampling/sample_stats_std.dat ]; then
    rm ./data/double_gaussian_sampling/sample_stats_std.dat
fi;

for e in ${Nevts[*]}; do
    str=`root -l -q -b root/double_gaussian_sampling/plotDoubleGaussianSampleStats.C\($Nsamples,$e\) | grep rms`
    stddev=`echo $str  | awk '{print $8}'`
    meanvar=`echo $str  | awk '{print $10}'`
    echo "$e $stddev $meanvar" >> ./data/double_gaussian_sampling/sample_stats_std.dat
done

#
# finally, plot the estimated stderr of the sampling means vs Nevt
#
root -l -q -b root/double_gaussian_sampling/plotDoubleGaussianSampleStdErr.C


