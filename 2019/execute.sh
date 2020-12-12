#!/bin/bash
mkdir 'output'
dart 1.dart < input/in > output/out1
cat output/out1
dart 2.dart < input/in > output/out2
cat output/out2

