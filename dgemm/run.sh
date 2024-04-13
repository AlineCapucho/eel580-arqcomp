#!/bin/bash

declare -a N=("1" "2" "4" "8" "16" "32" "64" "128" "256" "512" "1024" "2048")

for n in "${N[@]}"; do
    ./chapter_3_v1 ${n}
done
