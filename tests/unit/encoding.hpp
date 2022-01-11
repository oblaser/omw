/*
author          Oliver Blaser
date            10.01.2022
copyright       MIT - Copyright (c) 2022 Oliver Blaser
*/

#ifndef TEST_OMW_ENCODING_H
#define TEST_OMW_ENCODING_H

#include <array>
#include <cstdint>
#include <string>
#include <vector>

#include "catch2/catch.hpp"
#include "testUtil.h"

#include <omw/encoding.h>
#include <omw/int.h>


TEST_CASE("encoding.h omw::bcd")
{
}


TEST_CASE("encoding.h omw::bigEndian decode")
{
}


TEST_CASE("encoding.h omw::bigEndian encode_128()")
{
    constexpr size_t bufferSize = 20;
    std::array<uint8_t, bufferSize> buffer; // { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 }
    std::array<uint8_t, bufferSize> result;


    omw::int128_t i128;

    i128.sets(-1, 0xABCDEF123456);
    buffer = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };
    result = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 0xAB, 0xCD, 0xEF, 0x12, 0x34, 0x56, 16, 17, 18, 19 };
    omw::bigEndian::encode_128(buffer.data() + 0, buffer.data() + bufferSize, i128);
    CHECK(buffer == result);

    i128 = -1;
    buffer = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };
    result = { 0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 17, 18, 19 };
    omw::bigEndian::encode_128(buffer.data() + 1, buffer.data() + bufferSize, i128);
    CHECK(buffer == result);


    omw::uint128_t ui128;

    ui128.set(10, 0x123456);
    buffer = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };
    result = { 0, 1, 2, 3, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0x12, 0x34, 0x56 };
    omw::bigEndian::encode_128(buffer.data() + 4, buffer.data() + bufferSize, ui128);
    CHECK(buffer == result);

    ui128.sets(-1);
    buffer = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };
    result = { 0, 1, 2, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 19 };
    omw::bigEndian::encode_128(buffer.data() + 3, buffer.data() + bufferSize, ui128);
    CHECK(buffer == result);
}


TEST_CASE("encoding.h omw::url")
{
    const omw::string str = "+\"*%&/()=asdf(fdsf)";
    const omw::string enc = "%2B%22%2A%25%26%2F%28%29%3Dasdf%28fdsf%29";

    CHECK(omw::url::encode(str) == enc);
    CHECK(omw::url::encode(omw::url::encode(str)) == "%252B%2522%252A%2525%2526%252F%2528%2529%253Dasdf%2528fdsf%2529");
}


#endif // TEST_OMW_ENCODING_H
