#!/bin/sh

traffic=uniform
powergate_auto_config=1
off_percentile=50

for dim in 8 10
do
  for inj in `seq -w 0.01 0.01 0.90`
  do
    condition=`echo "$inj > 0.75" | bc -l`
    if [ $dim -gt 6 ] && [ $condition -eq 1 ]; then
      break
    fi
    for scheme in baseline rpa rpc norp nord flov opt_flov
    do
      powergate_type=$scheme
      mkdir -p ../results/throughput/${scheme}/${dim}dim
      drain_threshold=20
      if [ $scheme = "flov" ] || [ $scheme = "opt_flov" ]; then
        powergate_type="flov"
        drain_threshold=200
      elif [ $scheme = "baseline" ] || [ $scheme = "norp" ]; then
        powergate_type="no_pg"
      fi
      wait_for_tail_credit=1
      if [ $scheme = "rpa" ] || [ $scheme = "rpc" ] || [ $scheme = "norp" ]; then
        wait_for_tail_credit=0
      else
        wait_for_tail_credit=1
      fi
      count=`ps aux | grep booksim | wc -l`
      while [ $count -ge 26 ]; do
        count=`ps aux | grep booksim | wc -l`
      done
      logfile=../results/throughput/${scheme}/${dim}dim/${traffic}_${inj}inj_${dim}dim_${off_percentile}off.log
      ../src/booksim \
        ../runfiles/${scheme}/meshcmp_${off_percentile}off.cfg \
        k=${dim} injection_rate=${inj} \
        powergate_type=${powergate_type} \
        converged_threshold=-1 \
        powergate_auto_config=1 \
        traffic=${traffic} \
        powergate_percentile=${off_percentile} \
        priority=age \
        vc_buf_size=5 \
        packet_size=5 \
        hold_switch_for_packet=1 \
        routing_deadlock_timeout_threshold=512 \
        idle_threshold=20 \
        drain_threshold=${drain_threshold} \
        nord_power_centric_wakeup_threshold=1 \
        wait_for_tail_credit=${wait_for_tail_credit} \
        flov_monitor_epoch=1000 > ${logfile} 2>&1 &
    done
  done
done
