# author        Oliver Blaser
# date          30.12.2025
# copyright     MIT - Copyright (c) 2025 Oliver Blaser

set(OMW_COMPILE_OPTIONS
    -Wall
    -Wextra
    -Wpedantic
    -Werror=format
    -Werror=overflow
    -Werror=return-type
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
        # -Wno-psabi
        -Wuseless-cast
        -Wsuggest-override
    >
)
