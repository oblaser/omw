#!/bin/bash

# author        Oliver Blaser
# date          21.12.2021
# copyright     MIT - Copyright (c) 2021 Oliver Blaser

source dep_omw_globals.sh

packedDir="./packed"
outDirName="omw_doc"
outDir="$packedDir/$outDirName"
archive="$packedDir/omw_doc_v$versionstr.tar.gz"

rm -rf $outDir

mkdir -p $outDir

cp -r ../doc/out/* $outDir

cp dep_readme.txt $outDir/readme.txt
cp ../license.txt $outDir

rm -f $archive
tar -czf $archive -C $packedDir $outDirName
