# author        Oliver Blaser
# date          16.12.2023
# copyright     MIT - Copyright (c) 2023 Oliver Blaser

cmake_minimum_required(VERSION 3.13)

project(omw)



include_directories(../../../include/)

set(SOURCES
../../../src/io/configFile.cpp
../../../src/io/file.cpp
../../../src/io/serialPort.cpp
../../../src/windows/envVar.cpp
../../../src/windows/error.cpp
../../../src/windows/exception.cpp
../../../src/windows/resources.cpp
../../../src/windows/string.cpp
../../../src/windows/windows.cpp
../../../src/algorithm.cpp
../../../src/checksum.cpp
../../../src/cli.cpp
../../../src/color.cpp
../../../src/encoding.cpp
../../../src/int.cpp
../../../src/math.cpp
../../../src/omw.cpp
../../../src/string.cpp
../../../src/utility.cpp
../../../src/vector.cpp
../../../src/version.cpp
)

add_library(${BINSHARED} SHARED ${SOURCES})
set_target_properties(${BINSHARED} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../)

add_library(${BINSTATIC} STATIC ${SOURCES})
set_target_properties(${BINSTATIC} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ../)
