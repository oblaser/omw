#!/bin/bash

# author        Oliver Blaser
# date          16.12.2023
# copyright     MIT - Copyright (c) 2022 Oliver Blaser

source dep_globals.sh

packedDir="./packed"
outDirName="${prjDirName}_doc"
outDir="$packedDir/$outDirName"
archive="$packedDir/${prjDirName}_doc_v$versionstr.tar.gz"

rm -rf $outDir

mkdir -p $outDir

cp -r ../doc/out/* $outDir

writeReadmeFile $outDir/readme.txt
cp ../license.txt $outDir

rm -f $archive
tar -czf $archive -C $packedDir $outDirName
