# author        Oliver Blaser
# date          27.01.2022
# copyright     MIT - Copyright (c) 2022 Oliver Blaser

cmake_minimum_required(VERSION 3.13)

project(omw)

#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED true)

include_directories(../../include/)
link_directories(../cmake/)

set(SHAREDLIB omw-shared)
set(STATICLIB omw-static)
set(SYSTEM_TEST_EXE_CLI_SHARED omw-system-test-cli-shared)
set(SYSTEM_TEST_EXE_CLI_STATIC omw-system-test-cli-static)


# cli

set(SOURCES_SYSTEM_TEST_CLI
../../tests/system/omw-test_cli/main.cpp
)

add_executable(${SYSTEM_TEST_EXE_CLI_SHARED} ${SOURCES_SYSTEM_TEST_CLI})
target_link_libraries(${SYSTEM_TEST_EXE_CLI_SHARED} lib${SHAREDLIB}.so)

add_executable(${SYSTEM_TEST_EXE_CLI_STATIC} ${SOURCES_SYSTEM_TEST_CLI})
target_link_libraries(${SYSTEM_TEST_EXE_CLI_STATIC} lib${STATICLIB}.a)
