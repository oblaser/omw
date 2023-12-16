# author        Oliver Blaser
# date          16.12.2023
# copyright     MIT - Copyright (c) 2023 Oliver Blaser

cmake_minimum_required(VERSION 3.13)

project(omw)

set(BINNAME omw)



set(BINSHARED ${BINNAME}-shared)
set(BINSTATIC ${BINNAME}-static)
set(UNIT_TEST_EXE_SHARED ${BINNAME}-unit-test-shared)
set(UNIT_TEST_EXE_STATIC ${BINNAME}-unit-test-static)

#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED true)

add_subdirectory(lib)
add_subdirectory(unit-tests)
