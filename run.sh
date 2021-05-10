#!/bin/bash
set -eux

clear
cp test.cu test.cpp

python setup.py install --user

# g++ test.cpp
# nvcc test.cu