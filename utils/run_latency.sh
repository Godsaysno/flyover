#!/bin/bash

powergate_auto_config=0
dim=8

for traffic in uniform tornado
do
  for inj in 0.02 0.08
  do
    for scheme in opt_flov #baseline rpa rpc nord flov opt_flov #rflov gflov opt_rflov opt_gflov
    do
      mkdir -p ../results/latency/${scheme}
      for off_percent in 10 20 30 40 50 60 70 80;
      do
        count=`ps aux | grep booksim | wc -l`
        while [ $count -eq 5 ]; do
          count=`ps aux | grep booksim | wc -l`
          sleep 1
        done
        ../src/booksim \
          ../runfiles/${scheme}/meshcmp_${off_percent}off.cfg \
          powergate_auto_config=${powergate_auto_config} \
          traffic=${traffic} \
          powergate_percentile=${off_percent} \
          k=${dim} \
          injection_rate=${inj} \
          > ../results/latency/${scheme}/${traffic}_${inj}inj_${off_percent}off.log &
      done
    done
  done
done
