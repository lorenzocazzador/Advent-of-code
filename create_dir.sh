#!/bin/bash
# $1 = anno
mkdir "$1"
for g in {01..25}
do
    mkdir "$1/$g"
    touch "$1/$g/1.py"
    mkdir "$1/$g/input"
    touch "$1/$g/input/ex"
    touch "$1/$g/input/in"
done
