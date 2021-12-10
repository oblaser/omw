#!/bin/bash

# author        Oliver Blaser
# date          10.12.2021
# copyright     MIT - Copyright (c) 2021 Oliver Blaser

builtDir="./built"
outDirName="omw_doc"
outDir="$builtDir/$outDirName"
archive="$builtDir/omw_doc_vX.X.X.tar.gz"

rm -rf $outDir

mkdir $outDir

cp -r ../doc/out/* $outDir

cp release_readme.txt $outDir/readme.txt
cp ../license.txt $outDir

rm -f $archive
tar -czf $archive -C $builtDir $outDirName
