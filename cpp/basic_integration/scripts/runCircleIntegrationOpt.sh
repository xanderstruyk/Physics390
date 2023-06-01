#!/bin/bash

echo "nargs: $#"

if [ $# -lt 1 ]; then
	echo "Pass an optimization level : 'O?'"
	return 
fi
Otype=$1

make clean
make PERF_TIME=1 PERF_OPT=${Otype}

do_perf_stat=0
if [ $# -eq 2 ]; then
	do_perf_stat=1
fi


ntrials=10000
samples=1000000;


#
# Naive
#
if [ ${do_perf_stat} -eq 1 ]; then
    fname=./data/stat_O${Otype}_pi_1D_Naive_ntrials_${ntrials}_samples_${samples}.dat
else
    fname=./data/O${Otype}_pi_1D_Naive_ntrials_${ntrials}_samples_${samples}.dat
fi 

if [ -e $fname  ]; then
    rm $fname 
fi;
echo "running sample size $samples, Naive"

j=0;
while (( $j < $ntrials )); 
  do 
  if [ ${do_perf_stat} -eq 1 ]; then 
      perf stat ./bin/test_pi_1D_Naive $RANDOM $samples 2> tmp.log
      astr=$(grep Area tmp.log)
      istr=$(grep instr tmp.log | awk '{print $1}' | sed -e 's/,//g')
      str="$astr instru: $istr"
      echo $str >> $fname
      rm tmp.log
  else
      ./bin/test_pi_1D_Naive $RANDOM $samples 2>> $fname
  fi
  (( j++ ));
done;




#
# MeanVar
#
if [ ${do_perf_stat} -eq 1 ]; then
    fname=./data/stat_O${Otype}_pi_1D_MeanVariance_ntrials_${ntrials}_samples_${samples}.dat
else
    fname=./data/O${Otype}_pi_1D_MeanVariance_ntrials_${ntrials}_samples_${samples}.dat
fi

if [ -e $fname  ]; then
    rm $fname 
fi;
echo "running sample size $samples, MeanVar"

j=0;
while (( $j < $ntrials )); 
  do 
  if [ ${do_perf_stat} -eq 1 ]; then 
      perf stat ./bin/test_pi_1D_MeanVariance $RANDOM $samples 2> tmp.log
      astr=$(grep Integral tmp.log)
      istr=$(grep instr tmp.log | awk '{print $1}' | sed -e 's/,//g')
      str="$astr instru: $istr"
      echo $str >> $fname
      rm tmp.log
  else
      ./bin/test_pi_1D_MeanVariance $RANDOM $samples 2>> $fname
  fi
  (( j++ ));
done;


