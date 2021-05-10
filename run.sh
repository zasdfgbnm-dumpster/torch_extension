#!/bin/bash
set -eux

clear
cp test.cu test.cpp

# python setup.py install --user

echo "******************** gcc ********************"
g++ test.cpp

echo "******************** nvcc ********************"
nvcc test.cu