#!/bin/bash

# author        Oliver Blaser
# date          26.01.2022
# copyright     MIT - Copyright (c) 2022 Oliver Blaser

errCnt=0
function procErrorCode()
{
    if [ $1 -ne 0 ]; then ((++errCnt)); fi;
}



rm -rf cmake/CMakeFiles/
procErrorCode $?

rm -f cmake/CMakeCache.txt
procErrorCode $?

rm -f cmake/cmake_install.cmake
procErrorCode $?

rm -f cmake/*.so
procErrorCode $?

rm -f cmake/*.a
procErrorCode $?

rm -f cmake/Makefile
procErrorCode $?

rm -f cmake/omw-system-test-cli-shared
procErrorCode $?

rm -f cmake/omw-system-test-cli-static
procErrorCode $?

rm -f cmake/omw-unit-test-shared
procErrorCode $?

rm -f cmake/omw-unit-test-static
procErrorCode $?



exitCode=0
if [ $errCnt -ne 0 ]; then exitCode=1; fi;

exit $exitCode
