#!/bin/bash

set -e

clear
cp test.cu test.cpp

# python setup.py install --user

echo "******************** gcc ********************"
g++ test.cpp

echo
echo

echo "******************** nvcc ********************"
nvcc test.cu