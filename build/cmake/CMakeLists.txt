# author        Oliver Blaser
# date          14.12.2021
# copyright     MIT - Copyright (c) 2021 Oliver Blaser

cmake_minimum_required(VERSION 3.13)

project(omw)

include_directories(../../include/)

set(SOURCES
../../src/omw.cpp
../../src/string.cpp
../../src/version.cpp
)

#add_library(omw-shared SHARED ${SOURCES})
add_library(omw STATIC ${SOURCES})
