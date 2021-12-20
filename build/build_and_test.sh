#!/bin/bash

# author        Oliver Blaser
# date          19.12.2021
# copyright     MIT - Copyright (c) 2021 Oliver Blaser

# Options:
# -s                    also run system test executables
# --only-shared
# --only-static



if [ "$1" == "--only-shared" ]
then
    ./make_build.sh omw-unit-test-shared
    if [ $? -eq 0 ]; then cd ./cmake; ./omw-unit-test-shared; fi
    exit 0
fi

if [ "$1" == "--only-static" ]
then
    ./make_build.sh omw-unit-test-static
    if [ $? -eq 0 ]; then cd ./cmake; ./omw-unit-test-static; fi
    exit 0
fi



./make_build.sh
if [ $? -eq 0 ]; then ./run_test.sh $1; fi
