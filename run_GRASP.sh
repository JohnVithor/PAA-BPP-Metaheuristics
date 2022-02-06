#!/bin/bash
tentativas=$1
path_instances=$2
seed=$3
max_time=$4

echo Algorithm,Instance,Nanoseconds,Seconds,Minutes,Mean,Best

files=$(ls $path_instances)
    for filename in $files
    do
        soma_nanosegundos=0
        soma_segundos=0
        soma_minutos=0
        soma_bins=0
        best_sol=1000000000000000000
        for tentativa in $(seq $tentativas)
        do
            ./bin/GRASP_driver $path_instances$filename $((seed * tentativa)) $max_time 50 200 1 0 1000 10 3 > ./results/GRASP$filename$tentativa.txt
            bins=$(sed '1!d' ./results/GRASP$filename$tentativa.txt)
            bins="${bins##* }"
            if [[ "$bins" -lt "$best_sol" ]]; then
              best_sol=$bins
            fi
            soma_bins=$((soma_bins + bins))
            nanosegundos=$(sed '2!d' ./results/GRASP$filename$tentativa.txt)
            segundos=$(sed '3!d' ./results/GRASP$filename$tentativa.txt)
            minutos=$(sed '4!d' ./results/GRASP$filename$tentativa.txt)
            nanosegundos="${nanosegundos##* }"
            segundos="${segundos##* }"
            minutos="${minutos##* }"
            soma_nanosegundos=$((soma_nanosegundos + nanosegundos))
            soma_segundos=$((soma_segundos + segundos))
            soma_minutos=$((soma_minutos + minutos))
        done
        echo GRASP,$filename,$(bc <<< "scale=2;$soma_nanosegundos/$tentativas"),$(bc <<< "scale=2;$soma_segundos/$tentativas"),$(bc <<< "scale=2;$soma_minutos/$tentativas"),$(bc <<< "scale=2;$soma_bins/$tentativas"),$best_sol
    done