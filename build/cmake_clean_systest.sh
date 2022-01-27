#!/bin/bash

# author        Oliver Blaser
# date          27.01.2022
# copyright     MIT - Copyright (c) 2022 Oliver Blaser

errCnt=0
function procErrorCode()
{
    if [ $1 -ne 0 ]; then ((++errCnt)); fi;
}



rm -rf cmake-system-tests/CMakeFiles/
procErrorCode $?

rm -f cmake-system-tests/CMakeCache.txt
procErrorCode $?

rm -f cmake-system-tests/cmake_install.cmake
procErrorCode $?

rm -f cmake-system-tests/Makefile
procErrorCode $?

rm -f cmake-system-tests/omw-system-test-cli-shared
procErrorCode $?

rm -f cmake-system-tests/omw-system-test-cli-static
procErrorCode $?

rm -f cmake-system-tests/omw-system-test-file-shared
procErrorCode $?

rm -f cmake-system-tests/omw-system-test-file-static
procErrorCode $?



exitCode=0
if [ $errCnt -ne 0 ]; then exitCode=1; fi;

exit $exitCode
