#!/bin/bash

libdir=gtest/lib

if [ ! -d "$libdir" ]; then
    mkdir gtest/lib
fi

libdir=$(realpath $libdir)

gtest=$(realpath gtest)

tempdir=$(mktemp -d)

echo "Created: $tempdir"

cp ./gtest/gtest.zip $tempdir

cd $tempdir

unzip "gtest.zip"

./configure

cmake .

make

cp ./libgtest_main.a ./libgtest.a "$libdir"

rm -rf "$tempdir"
