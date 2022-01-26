#!/bin/bash

# author        Oliver Blaser
# date          26.01.2022
# copyright     MIT - Copyright (c) 2022 Oliver Blaser

cd ./cmake
if [ $? -ne 0 ]
then
    exit 1
fi

cmake .
if [ $? -ne 0 ]
then
    exit 1
fi

make
if [ $? -ne 0 ]
then
    exit 1
fi

cd ..
./dep_omw_cp_bin.sh
exit $?
