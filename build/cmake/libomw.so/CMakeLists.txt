# author        Oliver Blaser
# date          21.05.2024
# copyright     MIT - Copyright (c) 2024 Oliver Blaser


################################################################################
#
# This file is not to be used in conjunction with the build.sh script, it's
# meant to be included by a projects CMakeLists.txt file.
#
################################################################################


cmake_minimum_required(VERSION 3.13)

project(omw)

include_directories(${CMAKE_CURRENT_LIST_DIR}/../../../include/)

include(${CMAKE_CURRENT_LIST_DIR}/../libomw.var.cmake)

add_library(${BINNAME} SHARED ${SOURCES})
set_target_properties(${BINNAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/../../../lib/)
