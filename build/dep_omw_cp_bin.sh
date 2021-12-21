#!/bin/bash

# author        Oliver Blaser
# date          21.12.2021
# copyright     MIT - Copyright (c) 2021 Oliver Blaser

source dep_omw_globals.sh

{
    mkdir -p ../lib &&
    cp cmake/libomw-static.a ../lib/libomw.a &&
    cp cmake/libomw-shared.so ../lib/libomw.so.$versionstr &&
    exit 0
}

exit 1
