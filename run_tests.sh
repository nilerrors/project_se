#!/bin/bash

rm -rf ./cmake-build-debug > /dev/null 2>&1

cmake -S . -B cmake-build-debug > /dev/null 2>&1

cd ./cmake-build-debug

make debug_target -s > /dev/null 2>&1

cd ..

clear

./cmake-build-debug/debug_target

