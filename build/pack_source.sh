#!/bin/bash

# author        Oliver Blaser
# date          20.12.2021
# copyright     MIT - Copyright (c) 2021 Oliver Blaser

source dep_omw_globals.sh

builtDir="./built"
outDirName="omw_src"
outDir="$builtDir/$outDirName"
archive="$builtDir/omw_src_v$versionstr.tar.gz"

rm -rf $outDir

mkdir -p $outDir/omw
mkdir $outDir/omw/include
mkdir $outDir/omw/src

cp -r ../include/* $outDir/omw/include
cp -r ../src/* $outDir/omw/src

cp release_readme.txt $outDir/omw/readme.txt
cp ../license.txt $outDir/omw

rm -f $archive
tar -czf $archive -C $outDir omw
