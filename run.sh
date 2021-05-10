#!/bin/bash
set -eux

python setup.py install --user

cp test.cu test.cpp
g++ test.cpp
nvcc test.cu