#!/bin/bash

# author        Oliver Blaser
# date          26.01.2022
# copyright     MIT - Copyright (c) 2022 Oliver Blaser

result=0

function handleFailure()
{
    ((++result))
    echo -e "\033[31m  --=====#   \033[91mfailed\033[31m  #=====--\033[39m"
}

echo -e "\033[96mmake rebuild\033[39m"
echo "  --=====#   Clean   #=====--"
./make_clean.sh
if [ $? -ne 0 ]
then
    handleFailure
else
    echo "  --=====#   Build   #=====--"
    ./make_build.sh
    if [ $? -ne 0 ]
    then
        handleFailure
    else
        echo -e "\033[32m  --=====#   \033[92mDone\033[32m    #=====--\033[39m"
    fi
fi



exitCode=0
if [ $result -ne 0 ]; then exitCode=1; fi;

exit $exitCode
