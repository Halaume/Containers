#!/bin/bash

make

time ./Containers_ft &> /dev/null | awk '{print $1}'
echo 'AAAAAAAAAAAAAAAA'
time_ft=time ./Containers_ft $1 &> /dev/null
time_std=time ./Containers_std $1 &> /dev/null

echo "time ft = " $time_ft
echo "time std = " $time_std
