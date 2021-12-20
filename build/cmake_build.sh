#!/bin/bash

# author        Oliver Blaser
# date          17.12.2021
# copyright     MIT - Copyright (c) 2021 Oliver Blaser

cd ./cmake
if [ $? -ne 0 ]
then
    exit 1
fi

cmake .
if [ $? -ne 0 ]
then
    exit 2
fi

make
if [ $? -ne 0 ]
then
    exit 3
fi

exit 0
