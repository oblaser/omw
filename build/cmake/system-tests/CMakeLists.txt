# author        Oliver Blaser
# date          16.12.2023
# copyright     MIT - Copyright (c) 2023 Oliver Blaser

cmake_minimum_required(VERSION 3.13)

project(omw-unit-tests)


set(SYSTEM_TEST_EXE_CLI_SHARED ${BINNAME}-system-test-cli-shared)
set(SYSTEM_TEST_EXE_CLI_STATIC ${BINNAME}-system-test-cli-static)
set(SYSTEM_TEST_EXE_FILE_SHARED ${BINNAME}-system-test-file-shared)
set(SYSTEM_TEST_EXE_FILE_STATIC ${BINNAME}-system-test-file-static)

include_directories(../../../include/)

link_directories(../)


# cli

set(SOURCES_SYSTEM_TEST_CLI
../../../tests/system/omw-test_cli/main.cpp
)

add_executable(${SYSTEM_TEST_EXE_CLI_SHARED} ${SOURCES_SYSTEM_TEST_CLI})
target_link_libraries(${SYSTEM_TEST_EXE_CLI_SHARED} lib${BINSHARED}.so)
set_target_properties(${SYSTEM_TEST_EXE_CLI_SHARED} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../)

add_executable(${SYSTEM_TEST_EXE_CLI_STATIC} ${SOURCES_SYSTEM_TEST_CLI})
target_link_libraries(${SYSTEM_TEST_EXE_CLI_STATIC} lib${BINSTATIC}.a)
set_target_properties(${SYSTEM_TEST_EXE_CLI_STATIC} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../)


# file

set(SOURCES_SYSTEM_TEST_FILE
../../../tests/system/omw-test_file/main.cpp
)

add_executable(${SYSTEM_TEST_EXE_FILE_SHARED} ${SOURCES_SYSTEM_TEST_FILE})
target_link_libraries(${SYSTEM_TEST_EXE_FILE_SHARED} lib${BINSHARED}.so)
set_target_properties(${SYSTEM_TEST_EXE_FILE_SHARED} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../)

add_executable(${SYSTEM_TEST_EXE_FILE_STATIC} ${SOURCES_SYSTEM_TEST_FILE})
target_link_libraries(${SYSTEM_TEST_EXE_FILE_STATIC} lib${BINSTATIC}.a)
set_target_properties(${SYSTEM_TEST_EXE_FILE_STATIC} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../)
