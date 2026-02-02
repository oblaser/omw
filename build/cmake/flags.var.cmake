# author        Oliver Blaser
# date          30.12.2025
# copyright     MIT - Copyright (c) 2025 Oliver Blaser

set(OMW_COMPILE_OPTIONS
    -pedantic
    -Wall
    -Wextra
    -Wpedantic
    -Werror=format
    -Werror=overflow
    -Werror=return-type
    -Werror=array-bounds
    -Werror=unused-parameter
    -Wdouble-promotion

    $<$<COMPILE_LANGUAGE:C>:
        -Werror=discarded-qualifiers
        -Werror=implicit
        -Werror=incompatible-pointer-types
        -Werror=int-conversion
        -Werror=pointer-sign
    >

    $<$<COMPILE_LANGUAGE:CXX>:
        -Werror=reorder
        -Werror=switch
        -Wsuggest-override
    >
)
