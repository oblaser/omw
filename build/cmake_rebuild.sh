#!/bin/bash

# author        Oliver Blaser
# date          17.12.2021
# copyright     MIT - Copyright (c) 2021 Oliver Blaser

result=0

function handleFailure()
{
    ((++result))
    echo -e "\033[31m  --=====#   failed  #=====--\033[39m"
}

echo -e "\033[96mcmake rebuild\033[39m"
echo "  --=====#   Clean   #=====--"
./cmake_clean.sh
if [ $? -ne 0 ]
then
    handleFailure
else
    echo "  --=====#   Build   #=====--"
    ./cmake_build.sh
    if [ $? -ne 0 ]
    then
        handleFailure
    else
        echo -e "\033[32m  --=====#   \033[92mDone\033[32m    #=====--\033[39m"
    fi
fi

exit $result
