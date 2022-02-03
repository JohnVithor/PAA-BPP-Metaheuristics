#!/bin/bash
tentativas=$1
path_instances=$2
seed=$3
max_time=$4

echo Algoritmo,Instancia,Tempo_Nanosegundos,Tempo_Segundos,Tempo_Minutos,N_bins

files=$(ls $path_instances)
    for filename in $files
    do
        soma_nanosegundos=0
        soma_segundos=0
        soma_minutos=0
        bins=0
        for tentativa in $(seq $tentativas)
        do
            ./bin/GRASP_driver $path_instances$filename $seed $max_time 1 0.1 1000000 10000000 10 3 > ./results/GRASP$filename$tentativa.txt
            bins=$(sed '1!d' ./results/GRASP$filename$tentativa.txt)
            bins="${bins##* }"

            nanosegundos=$(sed '2!d' ./results/$filename$tentativa.txt)
            segundos=$(sed '3!d' ./results/$filename$tentativa.txt)
            minutos=$(sed '4!d' ./results/$filename$tentativa.txt)
            nanosegundos="${nanosegundos##* }"
            segundos="${segundos##* }"
            minutos="${minutos##* }"
            soma_nanosegundos=$((soma_nanosegundos + nanosegundos))
            soma_segundos=$((soma_segundos + segundos))
            soma_minutos=$((soma_minutos + minutos))
            
        done
        echo GRASP,$filename,$((soma_nanosegundos / tentativas)), $((soma_segundos / tentativas)), $((soma_minutos / tentativas)),$bins
    done