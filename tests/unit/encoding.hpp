/*
author          Oliver Blaser
date            11.01.2022
copyright       MIT - Copyright (c) 2022 Oliver Blaser
*/

#ifndef TEST_OMW_ENCODING_H
#define TEST_OMW_ENCODING_H

#include <array>
#include <cstdint>
#include <stdexcept>
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
    //TESTUTIL_TRYCATCH_DECLARE_VAL(buffer_type, initial);
    //TESTUTIL_TRYCATCH_CHECK(omw::bigEndian::encode_16(nullptr, buffer.data() + bufferSize, sVal), std::invalid_argument);
    //TESTUTIL_TRYCATCH_CHECK(omw::bigEndian::encode_16(buffer.data() + 1, nullptr, std::invalid_argument);
    //TESTUTIL_TRYCATCH_CHECK(omw::bigEndian::encode_16(buffer.data() + bufferSize - 1, buffer.data() + bufferSize, sVal), std::out_of_range);
}
TEST_CASE("encoding.h omw::bigEndian encode_16()")
{
    constexpr size_t bufferSize = 10;
    using buffer_type = std::array<uint8_t, bufferSize>;
    buffer_type buffer;
    buffer_type result;

    int16_t sVal;

    sVal = 0xEF;
    buffer = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    result = { 0x00, 0xEF, 2, 3, 4, 5, 6, 7, 8, 9 };
    omw::bigEndian::encode_16(buffer.data() + 0, buffer.data() + bufferSize, sVal);
    CHECK(buffer == result);

    sVal = -1;
    buffer = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    result = { 0, 0xFF, 0xFF, 3, 4, 5, 6, 7, 8, 9 };
    omw::bigEndian::encode_16(buffer.data() + 1, buffer.data() + bufferSize, sVal);
    CHECK(buffer == result);


    uint16_t uVal;

    uVal = 513;
    buffer = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    result = { 0, 1, 2, 1, 4, 5, 6, 7, 8, 9 };
    omw::bigEndian::encode_16(buffer.data() + 2, buffer.data() + bufferSize, uVal);
    CHECK(buffer == result);

    uVal = 0xFFFF;
    buffer = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    result = { 0, 1, 2, 3, 4, 5, 6, 7, 0xFF, 0xFF };
    omw::bigEndian::encode_16(buffer.data() + 8, buffer.data() + bufferSize, uVal);
    CHECK(buffer == result);


    buffer_type* pTryCatchValue;
    const buffer_type initial = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    TESTUTIL_TRYCATCH_SE_DECLARE_VAL(buffer_type, pTryCatchValue, initial);
    TESTUTIL_TRYCATCH_SE_CHECK((omw::bigEndian::encode_16(nullptr, pTryCatchValue->data() + pTryCatchValue->size(), sVal)), std::invalid_argument);
    TESTUTIL_TRYCATCH_SE_CHECK((omw::bigEndian::encode_16(pTryCatchValue->data(), nullptr, sVal)), std::invalid_argument);
    TESTUTIL_TRYCATCH_SE_CHECK((omw::bigEndian::encode_16(pTryCatchValue->data() + pTryCatchValue->size() - 1, pTryCatchValue->data() + pTryCatchValue->size(), sVal)), std::out_of_range);
    TESTUTIL_TRYCATCH_SE_CHECK((omw::bigEndian::encode_16(pTryCatchValue->data() + pTryCatchValue->size(), pTryCatchValue->data() + pTryCatchValue->size(), sVal)), std::out_of_range);
    TESTUTIL_TRYCATCH_SE_CHECK((omw::bigEndian::encode_16(nullptr, pTryCatchValue->data() + pTryCatchValue->size(), uVal)), std::invalid_argument);
    TESTUTIL_TRYCATCH_SE_CHECK((omw::bigEndian::encode_16(pTryCatchValue->data(), nullptr, uVal)), std::invalid_argument);
    TESTUTIL_TRYCATCH_SE_CHECK((omw::bigEndian::encode_16(pTryCatchValue->data() + pTryCatchValue->size() - 1, pTryCatchValue->data() + pTryCatchValue->size(), uVal)), std::out_of_range);
    TESTUTIL_TRYCATCH_SE_CHECK((omw::bigEndian::encode_16(pTryCatchValue->data() + pTryCatchValue->size(), pTryCatchValue->data() + pTryCatchValue->size(), uVal)), std::out_of_range);
}
TEST_CASE("encoding.h omw::bigEndian encode_32()")
{
    constexpr size_t bufferSize = 10;
    using buffer_type = std::array<uint8_t, bufferSize>;
    buffer_type buffer;
    buffer_type result;


    int32_t sVal;

    sVal = 0xCDEF12;
    buffer = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    result = { 0x00, 0xCD, 0xEF, 0x12, 4, 5, 6, 7, 8, 9 };
    omw::bigEndian::encode_32(buffer.data() + 0, buffer.data() + bufferSize, sVal);
    CHECK(buffer == result);

    sVal = -1;
    buffer = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    result = { 0, 0xFF, 0xFF, 0xFF, 0xFF, 5, 6, 7, 8, 9 };
    omw::bigEndian::encode_32(buffer.data() + 1, buffer.data() + bufferSize, sVal);
    CHECK(buffer == result);


    uint32_t uVal;

    uVal = 514;
    buffer = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    result = { 0, 1, 0, 0, 2, 2, 6, 7, 8, 9 };
    omw::bigEndian::encode_32(buffer.data() + 2, buffer.data() + bufferSize, uVal);
    CHECK(buffer == result);

    uVal = 0xFFFFFFFF;
    buffer = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    result = { 0, 1, 2, 3, 4, 5, 0xFF, 0xFF, 0xFF, 0xFF };
    omw::bigEndian::encode_32(buffer.data() + 6, buffer.data() + bufferSize, uVal);
    CHECK(buffer == result);


    buffer_type* pTryCatchValue;
    const buffer_type initial = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    TESTUTIL_TRYCATCH_SE_DECLARE_VAL(buffer_type, pTryCatchValue, initial);
    TESTUTIL_TRYCATCH_SE_CHECK((omw::bigEndian::encode_32(nullptr, pTryCatchValue->data() + pTryCatchValue->size(), sVal)), std::invalid_argument);
    TESTUTIL_TRYCATCH_SE_CHECK((omw::bigEndian::encode_32(pTryCatchValue->data(), nullptr, sVal)), std::invalid_argument);
    TESTUTIL_TRYCATCH_SE_CHECK((omw::bigEndian::encode_32(pTryCatchValue->data() + pTryCatchValue->size() - 1, pTryCatchValue->data() + pTryCatchValue->size(), sVal)), std::out_of_range);
    TESTUTIL_TRYCATCH_SE_CHECK((omw::bigEndian::encode_32(pTryCatchValue->data() + pTryCatchValue->size(), pTryCatchValue->data() + pTryCatchValue->size(), sVal)), std::out_of_range);
    TESTUTIL_TRYCATCH_SE_CHECK((omw::bigEndian::encode_32(nullptr, pTryCatchValue->data() + pTryCatchValue->size(), uVal)), std::invalid_argument);
    TESTUTIL_TRYCATCH_SE_CHECK((omw::bigEndian::encode_32(pTryCatchValue->data(), nullptr, uVal)), std::invalid_argument);
    TESTUTIL_TRYCATCH_SE_CHECK((omw::bigEndian::encode_32(pTryCatchValue->data() + pTryCatchValue->size() - 3, pTryCatchValue->data() + pTryCatchValue->size(), uVal)), std::out_of_range);
    TESTUTIL_TRYCATCH_SE_CHECK((omw::bigEndian::encode_32(pTryCatchValue->data() + pTryCatchValue->size(), pTryCatchValue->data() + pTryCatchValue->size(), uVal)), std::out_of_range);
}
TEST_CASE("encoding.h omw::bigEndian encode_64()")
{
    constexpr size_t bufferSize = 10;
    using buffer_type = std::array<uint8_t, bufferSize>;
    buffer_type buffer;
    buffer_type result;


    int64_t sVal;

    sVal = 0xABCDEF12345678;
    buffer = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    result = { 0, 0xAB, 0xCD, 0xEF, 0x12, 0x34, 0x56, 0x78, 8, 9 };
    omw::bigEndian::encode_64(buffer.data() + 0, buffer.data() + bufferSize, sVal);
    CHECK(buffer == result);

    sVal = -1;
    buffer = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    result = { 0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 9 };
    omw::bigEndian::encode_64(buffer.data() + 1, buffer.data() + bufferSize, sVal);
    CHECK(buffer == result);


    uint64_t uVal;

    uVal = 512;
    buffer = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    result = { 0, 1, 0, 0, 0, 0, 0, 0, 2, 0 };
    omw::bigEndian::encode_64(buffer.data() + 2, buffer.data() + bufferSize, uVal);
    CHECK(buffer == result);

    uVal = 0xFFFFFFFFFFFFFFFF;
    buffer = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    result = { 0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 9 };
    omw::bigEndian::encode_64(buffer.data() + 1, buffer.data() + bufferSize, uVal);
    CHECK(buffer == result);


    buffer_type* pTryCatchValue;
    const buffer_type initial = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    TESTUTIL_TRYCATCH_SE_DECLARE_VAL(buffer_type, pTryCatchValue, initial);
    TESTUTIL_TRYCATCH_SE_CHECK((omw::bigEndian::encode_64(nullptr, pTryCatchValue->data() + pTryCatchValue->size(), sVal)), std::invalid_argument);
    TESTUTIL_TRYCATCH_SE_CHECK((omw::bigEndian::encode_64(pTryCatchValue->data(), nullptr, sVal)), std::invalid_argument);
    TESTUTIL_TRYCATCH_SE_CHECK((omw::bigEndian::encode_64(pTryCatchValue->data() + pTryCatchValue->size() - 1, pTryCatchValue->data() + pTryCatchValue->size(), sVal)), std::out_of_range);
    TESTUTIL_TRYCATCH_SE_CHECK((omw::bigEndian::encode_64(pTryCatchValue->data() + pTryCatchValue->size(), pTryCatchValue->data() + pTryCatchValue->size(), sVal)), std::out_of_range);
    TESTUTIL_TRYCATCH_SE_CHECK((omw::bigEndian::encode_64(nullptr, pTryCatchValue->data() + pTryCatchValue->size(), uVal)), std::invalid_argument);
    TESTUTIL_TRYCATCH_SE_CHECK((omw::bigEndian::encode_64(pTryCatchValue->data(), nullptr, uVal)), std::invalid_argument);
    TESTUTIL_TRYCATCH_SE_CHECK((omw::bigEndian::encode_64(pTryCatchValue->data() + pTryCatchValue->size() - 7, pTryCatchValue->data() + pTryCatchValue->size(), uVal)), std::out_of_range);
    TESTUTIL_TRYCATCH_SE_CHECK((omw::bigEndian::encode_64(pTryCatchValue->data() + pTryCatchValue->size(), pTryCatchValue->data() + pTryCatchValue->size(), uVal)), std::out_of_range);
}
TEST_CASE("encoding.h omw::bigEndian encode_128()")
{
    constexpr size_t bufferSize = 20;
    using buffer_type = std::array<uint8_t, bufferSize>;
    buffer_type buffer;
    buffer_type result;


    omw::int128_t sVal;

    sVal.sets(-1, 0xABCDEF123456);
    buffer = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };
    result = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 0xAB, 0xCD, 0xEF, 0x12, 0x34, 0x56, 16, 17, 18, 19 };
    omw::bigEndian::encode_128(buffer.data() + 0, buffer.data() + bufferSize, sVal);
    CHECK(buffer == result);

    sVal = -1;
    buffer = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };
    result = { 0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 17, 18, 19 };
    omw::bigEndian::encode_128(buffer.data() + 1, buffer.data() + bufferSize, sVal);
    CHECK(buffer == result);


    omw::uint128_t uVal;

    uVal.set(10, 0x123456);
    buffer = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };
    result = { 0, 1, 2, 3, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0x12, 0x34, 0x56 };
    omw::bigEndian::encode_128(buffer.data() + 4, buffer.data() + bufferSize, uVal);
    CHECK(buffer == result);

    uVal.sets(-1);
    buffer = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };
    result = { 0, 1, 2, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 19 };
    omw::bigEndian::encode_128(buffer.data() + 3, buffer.data() + bufferSize, uVal);
    CHECK(buffer == result);


    buffer_type* pTryCatchValue;
    const buffer_type initial = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };
    TESTUTIL_TRYCATCH_SE_DECLARE_VAL(buffer_type, pTryCatchValue, initial);
    TESTUTIL_TRYCATCH_SE_CHECK((omw::bigEndian::encode_128(nullptr, pTryCatchValue->data() + pTryCatchValue->size(), sVal)), std::invalid_argument);
    TESTUTIL_TRYCATCH_SE_CHECK((omw::bigEndian::encode_128(pTryCatchValue->data(), nullptr, sVal)), std::invalid_argument);
    TESTUTIL_TRYCATCH_SE_CHECK((omw::bigEndian::encode_128(pTryCatchValue->data() + pTryCatchValue->size() - 1, pTryCatchValue->data() + pTryCatchValue->size(), sVal)), std::out_of_range);
    TESTUTIL_TRYCATCH_SE_CHECK((omw::bigEndian::encode_128(pTryCatchValue->data() + pTryCatchValue->size(), pTryCatchValue->data() + pTryCatchValue->size(), sVal)), std::out_of_range);
    TESTUTIL_TRYCATCH_SE_CHECK((omw::bigEndian::encode_128(nullptr, pTryCatchValue->data() + pTryCatchValue->size(), uVal)), std::invalid_argument);
    TESTUTIL_TRYCATCH_SE_CHECK((omw::bigEndian::encode_128(pTryCatchValue->data(), nullptr, uVal)), std::invalid_argument);
    TESTUTIL_TRYCATCH_SE_CHECK((omw::bigEndian::encode_128(pTryCatchValue->data() + pTryCatchValue->size() - 15, pTryCatchValue->data() + pTryCatchValue->size(), uVal)), std::out_of_range);
    TESTUTIL_TRYCATCH_SE_CHECK((omw::bigEndian::encode_128(pTryCatchValue->data() + pTryCatchValue->size(), pTryCatchValue->data() + pTryCatchValue->size(), uVal)), std::out_of_range);
}


TEST_CASE("encoding.h omw::url")
{
    const omw::string str = "+\"*%&/()=asdf(fdsf)";
    const omw::string enc = "%2B%22%2A%25%26%2F%28%29%3Dasdf%28fdsf%29";

    CHECK(omw::url::encode(str) == enc);
    CHECK(omw::url::encode(omw::url::encode(str)) == "%252B%2522%252A%2525%2526%252F%2528%2529%253Dasdf%2528fdsf%2529");
}


#endif // TEST_OMW_ENCODING_H
