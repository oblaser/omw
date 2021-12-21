#!/bin/bash

# author        Oliver Blaser
# date          20.12.2021
# copyright     MIT - Copyright (c) 2021 Oliver Blaser

source dep_omw_globals.sh

builtDir="./built"
outDirName="omw_doc"
outDir="$builtDir/$outDirName"
archive="$builtDir/omw_doc_v$versionstr.tar.gz"

rm -rf $outDir

mkdir $outDir

cp -r ../doc/out/* $outDir

cp release_readme.txt $outDir/readme.txt
cp ../license.txt $outDir

rm -f $archive
tar -czf $archive -C $builtDir $outDirName
