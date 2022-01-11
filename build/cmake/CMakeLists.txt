# author        Oliver Blaser
# date          11.01.2022
# copyright     MIT - Copyright (c) 2022 Oliver Blaser

cmake_minimum_required(VERSION 3.13)

project(omw)

include_directories(../../include/)
link_directories(./)

set(SHAREDLIB omw-shared)
set(STATICLIB omw-static)
set(UNIT_TEST_EXE_SHARED omw-unit-test-shared)
set(UNIT_TEST_EXE_STATIC omw-unit-test-static)
set(SYSTEM_TEST_EXE_CLI_SHARED omw-system-test-cli-shared)
set(SYSTEM_TEST_EXE_CLI_STATIC omw-system-test-cli-static)


# library

set(SOURCES
../../src/io/serialPort.cpp
../../src/windows/envVar.cpp
../../src/windows/error.cpp
../../src/windows/exception.cpp
../../src/windows/resources.cpp
../../src/windows/string.cpp
../../src/windows/windows.cpp
../../src/algorithm.cpp
../../src/cli.cpp
../../src/color.cpp
../../src/encoding.cpp
../../src/int.cpp
../../src/math.cpp
../../src/omw.cpp
../../src/string.cpp
../../src/utility.cpp
../../src/version.cpp
)

add_library(${SHAREDLIB} SHARED ${SOURCES})
add_library(${STATICLIB} STATIC ${SOURCES})


# unit test

set(SOURCES_UNIT_TEST
../../tests/unit/main.cpp
)

add_executable(${UNIT_TEST_EXE_SHARED} ${SOURCES_UNIT_TEST})
target_link_libraries(${UNIT_TEST_EXE_SHARED} lib${SHAREDLIB}.so)

add_executable(${UNIT_TEST_EXE_STATIC} ${SOURCES_UNIT_TEST})
target_link_libraries(${UNIT_TEST_EXE_STATIC} lib${STATICLIB}.a)


#system test

set(SOURCES_SYSTEM_TEST
../../tests/system/omw-test_cli/main.cpp
)

add_executable(${SYSTEM_TEST_EXE_CLI_SHARED} ${SOURCES_SYSTEM_TEST})
target_link_libraries(${SYSTEM_TEST_EXE_CLI_SHARED} lib${SHAREDLIB}.so)

add_executable(${SYSTEM_TEST_EXE_CLI_STATIC} ${SOURCES_SYSTEM_TEST})
target_link_libraries(${SYSTEM_TEST_EXE_CLI_STATIC} lib${STATICLIB}.a)

