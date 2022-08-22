/*
author          Oliver Blaser
date            27.01.2022
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



TEST_CASE("checksum.h omw::preview::crc16_kermit()")
{
    const uint8_t* data;
    omw::vector< uint8_t> v;

    CHECK(omw::preview::crc16_kermit(nullptr, 0) == 0x0000); // init value

    data = reinterpret_cast<const uint8_t*>("abcd");
    CHECK(omw::preview::crc16_kermit(data, 0) == 0x0000); // init value

    data = reinterpret_cast<const uint8_t*>("123456789");
    CHECK(omw::preview::crc16_kermit(data, 9) == 0x2189);

    data = reinterpret_cast<const uint8_t*>("MhGTD87x9MLw6JJo9DYb");
    CHECK(omw::preview::crc16_kermit(data, 20) == 0xB383);

    data = reinterpret_cast<const uint8_t*>("d1klmQLr8dYjDKfq7qawiMGmT07MViBUFCEUkMCG");
    CHECK(omw::preview::crc16_kermit(data, 40) == 0x5454);

    v = { 0x1B, 0x87, 0xD6, 0x55, 0x41, 0x9F, 0x97, 0x07, 0x06, 0x38, 0x0C, 0x9D, 0xAF, 0x38, 0xC9, 0x8F, 0x42, 0x5D, 0x0C, 0x66, 0xA8, 0x53, 0xE5, 0xFF, 0xF1, 0x89, 0x1A, 0x3A, 0xF4, 0x96, 0x33, 0x39 };
    CHECK(omw::preview::crc16_kermit(v.data(), v.size()) == 0xA75E);
}



#endif // TEST_OMW_CHECKSUM_H
