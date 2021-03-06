#!/bin/bash
ITEREATIONS=(1000 10000 100000 1000000 10000000 100000000)
THREADS=(1 2 4 8 16)
NRUNS=5
echo "exec_time, iterations, nThreads" | tee output_file.csv
for IT in "${ITEREATIONS[@]}"; do
  for TH in "${THREADS[@]}"; do
    for R in `seq 1 $NRUNS`; do
          echo `(/usr/bin/time -f '%U' ./approxPiMT $IT $TH) 2>&1`",$IT,$TH"
            
    done
  done
done | tee -a output_file.csv