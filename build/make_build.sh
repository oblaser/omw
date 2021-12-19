#!/bin/bash

# author        Oliver Blaser
# date          17.12.2021
# copyright     MIT - Copyright (c) 2021 Oliver Blaser

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
        exit 2
    fi
else
    make $1
    if [ $? -ne 0 ]
    then
        exit 2
    fi
fi

exit 0
