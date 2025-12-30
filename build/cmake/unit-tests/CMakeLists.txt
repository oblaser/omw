# author        Oliver Blaser
# date          16.12.2023
# copyright     MIT - Copyright (c) 2023 Oliver Blaser

cmake_minimum_required(VERSION 3.13)

project(omw-unit-tests)


set(UNIT_TEST_EXE_SHARED ${BINNAME}-unit-test-shared)
set(UNIT_TEST_EXE_STATIC ${BINNAME}-unit-test-static)

include_directories(../../../include/)

link_directories(../)

set(SOURCES_UNIT_TEST
../../../tests/unit/main.cpp

../../../tests/unit/algorithm.cpp
../../../tests/unit/checksum.cpp
../../../tests/unit/cli.cpp
../../../tests/unit/clock.cpp
../../../tests/unit/color.cpp
../../../tests/unit/encoding.cpp
../../../tests/unit/int.cpp
../../../tests/unit/io_serialPort.cpp
../../../tests/unit/math.cpp
../../../tests/unit/string.cpp
../../../tests/unit/uri.cpp
../../../tests/unit/utility.cpp
../../../tests/unit/vector.cpp
../../../tests/unit/version.cpp
../../../tests/unit/windows_envVar.cpp
../../../tests/unit/windows_string.cpp
)

#add_executable(${UNIT_TEST_EXE_SHARED} ${SOURCES_UNIT_TEST})
#target_link_libraries(${UNIT_TEST_EXE_SHARED} lib${BINSHARED}.so)
#set_target_properties(${UNIT_TEST_EXE_SHARED} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../)

add_executable(${UNIT_TEST_EXE_STATIC} ${SOURCES_UNIT_TEST})
target_link_libraries(${UNIT_TEST_EXE_STATIC} lib${BINSTATIC}.a)
set_target_properties(${UNIT_TEST_EXE_STATIC} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../)
