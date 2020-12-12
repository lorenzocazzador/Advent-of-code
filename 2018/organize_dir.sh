#!/bin/bash
for i in {3..9}
do 
    mv 0$i/1/AoC_"$i"Dic_1.cpp 0$i/1.cpp
    mv 0$i/2/AoC_"$i"Dic_2.cpp 0$i/2.cpp
done
