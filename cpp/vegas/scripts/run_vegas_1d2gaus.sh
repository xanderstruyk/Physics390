#!/bin

Ntrials=10000
Niter=20
Ng=50


ipath=./data/vegas_1d_ng_${Ng}
opath=./png/vegas_1d_ng_${Ng}


mkdir -p $ipath
mkdir -p $opath

Nevts=( 10000 );
#Nevts=( 10000 25000 50000 75000 100000 250000 500000 750000 1000000);


if [ -e ${ipath}/sample_stderr.dat ]; then
    rm ${ipath}/sample_stderr.dat
fi;

if [ -e ${ipath}/weighted_sample_stderr.dat ]; then
    rm ${ipath}/weighted_sample_stderr.dat
fi;

i=0;
for e in ${Nevts[*]}; do

    ofile=${ipath}/Itrials__Ntrials_${Ntrials}_Niter_${Niter}_Nevts_${e}.dat
    
    echo "./bin/vegas_integrate_1d2gaus --debug  --path $ipath --seed $RANDOM --trials $Ntrials --iterations $Niter --events $e --importance $Ng   > ${ofile}"
    ./bin/vegas_integrate_1d2gaus --debug  --path $ipath --seed $RANDOM --trials $Ntrials --iterations $Niter --events $e --importance $Ng   > ${ofile}

    str=`root -l -q ./root/vegas1d/plotIntegral.C\($Ntrials,$Niter,$e,\"$ipath\",\"$opath\"\) | grep rms`
    echo "str --> $str"

    enew=`echo $str | awk '{print $2}'`
    avg_uni=`echo $str | awk '{print $4}'`
    avg_vegas=`echo $str | awk '{print $6}'`
    rms_uni=`echo $str | awk '{print $8}'`
    rms_vegas=`echo $str | awk '{print $10}'`
    var_uni=`echo $str | awk '{print $12}'`
    var_vegas=`echo $str | awk '{print $14}'`
    varavg_uni=`echo $str | awk '{print $16}'`
    varavg_vegas=`echo $str | awk '{print $18}'`
    echo "$e $enew ${avg_uni} ${avg_vegas} ${rms_uni} ${rms_vegas} ${var_uni} ${var_vegas} ${varavg_uni} ${varavg_vegas}" >> ${ipath}/sample_stderr.dat
    echo "stat --> e: $e enew: $enew avgU: ${avg_uni} avgV: ${avg_vegas} rmsU: ${rms_uni} rmsV: ${rms_vegas} varU: ${var_uni} varV: ${var_vegas} varavgU: ${varavg_uni} varavgV: ${varavg_vegas}"


    #root -l -q -b  root/vegas1d/plotWeightedIntegral.C\($Ntrials,$Niter,$e,\"$ipath\",\"$opath\"\) | tail -1 >> ${ipath}/weighted_sample_stderr.dat


    for s in $(seq 0 9); do 
	root -l -q ./root/vegas1d/plotIsample.C\($e,$s,\"$ipath\",\"$opath\"\)
    done

    # need to fix on quest
    #root -l -q -e "gInterpreter->AddIncludePath(\"$PWD/include\")" ./root/vegas1d/plotBounds.C\($Niter,$e,\"$ipath\",\"$opath\"\)

    (( i++ ));
done;

#root -l -q ./root/vegas1d/plotStdErrSummary.C\(\"$ipath\",\"$opath\"\)
#root -l -q ./root/vegas1d/plotWeightedStdErrSummary.C\(\"$ipath\",\"$opath\"\)
