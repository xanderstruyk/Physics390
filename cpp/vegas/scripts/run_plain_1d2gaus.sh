#!/bin/sh

Nsamples=10000;
Nevts=(10000 25000 50000 75000 100000 250000 500000 750000);

ipath=./data/plain_integration/
opath=./png/plain_integration/

mkdir -p $ipath
mkdir -p $opath

if [ -e ${ipath}/stats_plain.dat ]; then
    rm ${ipath}/stats_plain.dat
fi;

echo "#  evts,Ihm_mean,I_rms,Shm_mean,Ism_mean,Ism_rms,Ssm_mean" >> ${ipath}/stats_plain.dat

for e in ${Nevts[*]}; do

    ./basic_integration/bin/plain_integrate_1d2gaus $RANDOM 10000 $e $ipath
    root -l -q ./root/basic_integration/compare_HM_vs_SM.C\($e,\"$ipath\",\"$opath\"\) | tail -1 >> ${ipath}/stats_plain.dat

done

root -l -q ./root/basic_integration/stats_HM_vs_SM.C\(\"$ipath\",\"$opath\"\) 
