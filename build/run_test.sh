#!/bin/bash

# author        Oliver Blaser
# date          11.01.2022
# copyright     MIT - Copyright (c) 2022 Oliver Blaser

# Options:
# -s    also run system test executables


cd cmake

if [ "$1" == "-s" ]
then
    echo -e "\033[96momw-system-test-cli-shared\033[39m"
    ./omw-system-test-cli-shared
    
    echo -e "\033[96momw-system-test-cli-static\033[39m"
    ./omw-system-test-cli-static
fi

echo -e "\033[96momw-unit-test-shared\033[39m"
./omw-unit-test-shared

echo -e "\033[96momw-unit-test-static\033[39m"
./omw-unit-test-static
