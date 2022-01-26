#!/bin/bash

# author        Oliver Blaser
# date          26.01.2022
# copyright     MIT - Copyright (c) 2022 Oliver Blaser

cd ./cmake
if [ $? -ne 0 ]
then
    exit 1
fi

if [ -z $1 ]
then
    make
    if [ $? -ne 0 ]
    then
        exit 1
    fi
else
    make $1
    if [ $? -ne 0 ]
    then
        exit 1
    fi
fi

cd ..
./dep_omw_cp_bin.sh
exit $?
