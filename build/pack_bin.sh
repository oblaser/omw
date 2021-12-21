#!/bin/bash

# author        Oliver Blaser
# date          21.12.2021
# copyright     MIT - Copyright (c) 2021 Oliver Blaser

source dep_omw_globals.sh

platform=$(uname -m)
packedDir="./packed"
outDirName="omw_linux_$platform"
outDir="$packedDir/$outDirName"
archive="$packedDir/omw_linux_${platform}_v$versionstr.tar.gz"

rm -rf $outDir

mkdir -p $outDir/omw
mkdir $outDir/omw/include
mkdir $outDir/omw/lib

cp -r ../include/* $outDir/omw/include
cp ../lib/libomw.a $outDir/omw/lib
cp ../lib/libomw.so* $outDir/omw/lib

cp dep_readme.txt $outDir/omw/readme.txt
cp ../license.txt $outDir/omw

rm -f $archive
tar -czf $archive -C $outDir omw
