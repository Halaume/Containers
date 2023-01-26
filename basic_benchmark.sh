#!/bin/bash

make

time_ft=`date +%s.%N`
echo -e "---Start test FT---\n"

./Containers_ft $1

echo -e "---End test FT---\n"
time_ft_end=`date +%s.%N`

time_std=`date +%s.%N`
echo "Start test STD\n"

./Containers_std $1

echo -e "\nEnd test STD\n"
time_std_end=`date +%s.%N`

runtime_ft=$(echo "$time_ft_end-$time_ft" | bc -l)
runtime_std=$(echo "$time_std_end-$time_std" | bc -l)

BLUE="\033[0;94m"
OFF="\033[0m"
echo -e "\n$BLUE runtime (sec) ft with seed $1 : " $runtime_ft "$OFF"
echo -e "\n$BLUE runtime (sec) std with seed $1 : " $runtime_std "$OFF"
