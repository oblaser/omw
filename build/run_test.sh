#!/bin/bash

# author        Oliver Blaser
# date          17.12.2021
# copyright     MIT - Copyright (c) 2021 Oliver Blaser

# Options:
# -s    also run system test executables


cd cmake

if [ "$1" == "-s" ]
then
    ./omw-system-test-cli-shared
    ./omw-system-test-cli-static
fi

./omw-unit-test-shared
./omw-unit-test-static
