#!/bin/bash

# author        Oliver Blaser
# date          28.01.2022
# copyright     MIT - Copyright (c) 2022 Oliver Blaser

# Usage:
# ./system-test.sh --help



source dep_omw_globals.sh

errCnt=0
function procErrorCode()
{
    if [ $1 -ne 0 ]; then ((++errCnt)); fi;
}

function printHelp()
{
    echo "Usage:"
    echo "  ./system-test.sh arg1 [arg2 [arg3]]"
    echo ""
    echo "run script in omw/build/"
    echo ""
    echo "args:"
    echo "  -h help     print help"
    echo "  cleanAll    delete all but CMakeLists.txt"
    echo "  cmake       cmake ."
    echo "  make        make"
    echo "  clean       make clean"
    echo "  cli         run cli static test"
    echo "  cli-sh      run cli shared test"
    echo "  file        run file static test"
    echo "  file-sh     run file shared test"
}

function cmd_cmake_clean()
{
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

    rm -f cmake-system-tests/*.omwsystestfile*
    procErrorCode $?
}

function cmd_cmake()
{
    cd ./cmake-system-tests
    procErrorCode $?
    cmake .
    procErrorCode $?
    cd ..
    procErrorCode $?
}

function cmd_make()
{
    cd ./cmake-system-tests
    procErrorCode $?
    make
    procErrorCode $?
    cd ..
    procErrorCode $?
}

function cmd_clean()
{
    cd ./cmake-system-tests
    procErrorCode $?
    make clean
    procErrorCode $?
    cd ..
    procErrorCode $?
}

function procArg()
{
    ptintTitle "system-test - $1" 4
    
    if [ "$1" == "cleanAll" ]; then cmd_cmake_clean
    elif [ "$1" == "cmake" ]; then cmd_cmake
    elif [ "$1" == "make" ]; then cmd_make
    elif [ "$1" == "clean" ]; then cmd_clean
    elif [ "$1" == "cli" ]
    then
        cd ./cmake-system-tests
        procErrorCode $?
        ./omw-system-test-cli-static
        procErrorCode $?
        cd ..
        procErrorCode $?
        
    elif [ "$1" == "cli-sh" ]
    then
        cd ./cmake-system-tests
        procErrorCode $?
        ./omw-system-test-cli-shared
        procErrorCode $?
        cd ..
        procErrorCode $?
        
    elif [ "$1" == "file" ]
    then
        cd ./cmake-system-tests
        procErrorCode $?
        ./omw-system-test-file-static
        procErrorCode $?
        cd ..
        procErrorCode $?
        
    elif [ "$1" == "file-sh" ]
    then
        cd ./cmake-system-tests
        procErrorCode $?
        ./omw-system-test-file-shared
        procErrorCode $?
        cd ..
        procErrorCode $?
        
    else
        printHelp
    fi
}



procArg $1
if [ $errCnt -eq 0 ] && [ "$2" != "" ]
then
    procArg $2
    if [ $errCnt -eq 0 ] && [ "$3" != "" ]
    then
        procArg $3
    fi
fi



exitCode=0
if [ $errCnt -ne 0 ]
then
    exitCode=1
    ptintTitle "system-test - failed" 1
else
    ptintTitle "system-test - OK" 2
fi

exit $exitCode
