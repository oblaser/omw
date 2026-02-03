# author        Oliver Blaser
# date          02.02.2026
# copyright     MIT - Copyright (c) 2026 Oliver Blaser

set(BINNAME omw)

set(SOURCES
${CMAKE_CURRENT_LIST_DIR}/../../src/io/configFile.cpp
${CMAKE_CURRENT_LIST_DIR}/../../src/io/file.cpp
${CMAKE_CURRENT_LIST_DIR}/../../src/io/serialPort.cpp
${CMAKE_CURRENT_LIST_DIR}/../../src/windows/envVar.cpp
${CMAKE_CURRENT_LIST_DIR}/../../src/windows/error.cpp
${CMAKE_CURRENT_LIST_DIR}/../../src/windows/exception.cpp
${CMAKE_CURRENT_LIST_DIR}/../../src/windows/resources.cpp
${CMAKE_CURRENT_LIST_DIR}/../../src/windows/string.cpp
${CMAKE_CURRENT_LIST_DIR}/../../src/windows/windows.cpp
${CMAKE_CURRENT_LIST_DIR}/../../src/algorithm.cpp
${CMAKE_CURRENT_LIST_DIR}/../../src/ansi-esc.cpp
${CMAKE_CURRENT_LIST_DIR}/../../src/checksum.cpp
${CMAKE_CURRENT_LIST_DIR}/../../src/cli.cpp
${CMAKE_CURRENT_LIST_DIR}/../../src/clock.cpp
${CMAKE_CURRENT_LIST_DIR}/../../src/color.cpp
${CMAKE_CURRENT_LIST_DIR}/../../src/encoding.cpp
${CMAKE_CURRENT_LIST_DIR}/../../src/int.cpp
${CMAKE_CURRENT_LIST_DIR}/../../src/math.cpp
${CMAKE_CURRENT_LIST_DIR}/../../src/omw.cpp
${CMAKE_CURRENT_LIST_DIR}/../../src/string.cpp
${CMAKE_CURRENT_LIST_DIR}/../../src/uri.cpp
${CMAKE_CURRENT_LIST_DIR}/../../src/utility.cpp
${CMAKE_CURRENT_LIST_DIR}/../../src/vector.cpp
${CMAKE_CURRENT_LIST_DIR}/../../src/version.cpp
)
