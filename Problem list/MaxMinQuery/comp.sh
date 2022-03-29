#!/bin/sh

for i in 1 2 3 4 5
do
    ./gen $i 10 10 10
    ./bf < $i > bf_$i.out
    ./std_v1 < $i > std_v1_$i.out
    cmp bf_$i.out std_v1_$i.out
done