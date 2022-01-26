#!/bin/bash

# author        Oliver Blaser
# date          26.01.2022
# copyright     MIT - Copyright (c) 2022 Oliver Blaser

cd ./cmake
if [ $? -ne 0 ]
then
    exit 1
fi

make clean
if [ $? -ne 0 ]
then
    exit 1
fi

exit 0
