# author        Oliver Blaser
# date          14.12.2021
# copyright     MIT - Copyright (c) 2021 Oliver Blaser

cmake_minimum_required(VERSION 3.13)

project(omw-tests-unit)

include_directories(../../../include/ ./)
link_directories(../../../build/cmake/)

#set(TEST_EXEC_SHARED ${CMAKE_PROJECT_NAME}_shared)
set(TEST_EXEC_STATIC ${CMAKE_PROJECT_NAME}_static)

#add_executable(${TEST_EXEC_SHARED} ../main.cpp)
#target_link_libraries(${TEST_EXEC_SHARED} libomw-shared.so)

add_executable(${TEST_EXEC_STATIC} ../main.cpp)
target_link_libraries(${TEST_EXEC_STATIC} libomw.a)
