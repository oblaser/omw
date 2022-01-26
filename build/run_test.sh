#!/bin/bash

# author        Oliver Blaser
# date          26.01.2022
# copyright     MIT - Copyright (c) 2022 Oliver Blaser

# Options:
# -s    also run system test executables


errCnt=0

function onError()
{
    ((++errCnt))
}



cd cmake

if [ "$1" == "-s" ]
then
    echo -e "\033[96momw-system-test-cli-shared\033[39m"
    ./omw-system-test-cli-shared
    if [ $? -ne 0 ]; then onError; fi;
    
    echo -e "\033[96momw-system-test-cli-static\033[39m"
    ./omw-system-test-cli-static
    if [ $? -ne 0 ]; then onError; fi;
fi

echo -e "\033[96momw-unit-test-shared\033[39m"
./omw-unit-test-shared
if [ $? -ne 0 ]; then onError; fi;

echo -e "\033[96momw-unit-test-static\033[39m"
./omw-unit-test-static
if [ $? -ne 0 ]; then onError; fi;



exitCode=0
if [ $errCnt -ne 0 ]; then exitCode=1; fi;

exit $exitCode
