#!/bin/bash

##
# A script to initialize the project.
# It makes sure all the directories are created, and gtest is working.
##

if [ ! -d "reports" ]; then
  mkdir reports
fi

if [ ! -d "logs" ]; then
  mkdir logs
fi

if [ ! -d "consistency_tests" ]; then
  mkdir consistency_tests
fi

./testify.sh
