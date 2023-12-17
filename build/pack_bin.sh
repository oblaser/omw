#!/bin/bash

# author        Oliver Blaser
# date          16.12.2023
# copyright     MIT - Copyright (c) 2022 Oliver Blaser

source dep_globals.sh

platform=$(uname -m)
packedDir="./packed"
outDirName="${prjDirName}_linux_$platform"
outDir="$packedDir/$outDirName"
archive="$packedDir/${prjDirName}_linux_${platform}_v$versionstr.tar.gz"

rm -rf $outDir

mkdir -p $outDir/$prjDirName
mkdir $outDir/$prjDirName/include
mkdir $outDir/$prjDirName/lib

cp -r ../include/* $outDir/$prjDirName/include
cp ../lib/lib${prjBinName}.a $outDir/$prjDirName/lib
cp ../lib/lib${prjBinName}.so* $outDir/$prjDirName/lib

writeReadmeFile $outDir/$prjDirName/readme.txt
cp ../license.txt $outDir/$prjDirName

rm -f $archive
tar -czf $archive -C $outDir $prjDirName
