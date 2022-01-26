/*
author          Oliver Blaser
date            26.01.2022
copyright       MIT - Copyright (c) 2022 Oliver Blaser
*/

#ifndef TEST_OMW_CHECKSUM_H
#define TEST_OMW_CHECKSUM_H

#include <cstddef>
#include <cstdint>
#include <vector>

#include "catch2/catch.hpp"

#include <omw/checksum.h>



TEST_CASE("checksum.h parityWord(pointer)")
{
    constexpr size_t dataSize = 6;
    uint8_t data[dataSize] = { 0x40, 0x05, 0xC0, 0x18, 0x0A, 0 };

    CHECK(omw::parityWord(nullptr, 3) == 0);
    CHECK(omw::parityWord(data, 0) == 0);

    CHECK(omw::parityWord(data, 3) == 0x85);
    CHECK(omw::parityWord(data, 4) == 0x9D);
    CHECK(omw::parityWord(data + 2, 2) == 0xD8);

    data[dataSize - 1] = omw::parityWord(data, dataSize - 1);
    CHECK(data[dataSize - 1] == 0x97);
    CHECK(omw::parityWord(data, dataSize) == 0);
}

TEST_CASE("checksum.h parityWord(vector)")
{
    std::vector<uint8_t> vec = { 0x40, 0x05, 0xC0, 0x18, 0x0A, 0 };

    CHECK(omw::parityWord(vec, 0, 0) == 0);
    CHECK(omw::parityWord(vec, vec.size(), 0) == 0);

    CHECK(omw::parityWord(vec, 0, 3) == 0x85);
    CHECK(omw::parityWord(vec, 0, 4) == 0x9D);
    CHECK(omw::parityWord(vec, 2, 2) == 0xD8);

    vec.back() = omw::parityWord(vec, 0, vec.size() - 1);
    CHECK(vec.back() == 0x97);
    CHECK(omw::parityWord(vec, 0, vec.size()) == 0);

    TESTUTIL_TRYCATCH_DECLARE_VAL(uint8_t, 0x11);
    TESTUTIL_TRYCATCH_CHECK(omw::parityWord(vec, vec.size() - 1, 2), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::parityWord(vec, vec.size(), 1), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::parityWord(vec, vec.size() + 1, 0), std::invalid_argument);
}



#endif // TEST_OMW_CHECKSUM_H
