#!/bin/bash
set -eux
cp test.cu test.cpp
g++ test.cpp
nvcc test.cu