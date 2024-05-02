#!/bin/bash

rm -rf ./cmake-build-debug

cmake -S . -B cmake-build-debug

cd ./cmake-build-debug

make debug_target

cd ..

./cmake-build-debug/debug_target

