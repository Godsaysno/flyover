#!/bin/sh

#cd scripts/

#for bench in blackscholes bodytrack canneal dedup facesim ferret fluidanimate freqmine streamcluster swaptions vips x264 rtview
#for bench in blackscholes bodytrack canneal dedup ferret fluidanimate vips x264
for bench in swaptions
do
#    ./writescripts.pl $bench 32 --ckpts
#    ./run_ckpts $bench ckpts 32 32 small
#    ./run_ckpts $bench ckpts 32 32 medium
#    ./run_baseline_roi $bench baseline_timing 32 32 mesh small
    ./run_flov_roi $bench flov_timing 32 32 mesh small
#    ./run_rpa_roi $bench rpa_timing 32 32 mesh small
#    ./run_rpc_roi $bench rpc_timing 32 32 mesh small
#    ./run_baseline_roi $bench baseline_timing 32 32 mesh medium
#    ./run_flov_roi $bench flov_timing 32 32 mesh medium
#    ./run_rpa_roi $bench rpa_timing 32 32 mesh medium
#    ./run_rpc_roi $bench rpc_timing 32 32 mesh medium
done

#cd ..
