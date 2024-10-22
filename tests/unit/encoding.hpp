/*
author          Oliver Blaser
date            24.01.2022
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


TEST_CASE("encoding.h omw::bcd") {}


TEST_CASE("encoding.h omw::bigEndian decode")
{
    const uint8_t data[] = { 0xFF, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0x00, 0x11 };

    CHECK(omw::bigEndian::decode_i16(data + 9, 1) == -86);
    CHECK(omw::bigEndian::decode_ui16(data + 9, 1) == 170);
    CHECK(omw::bigEndian::decode_i32(data + 8, 1) == -103);
    CHECK(omw::bigEndian::decode_ui32(data + 8, 1) == 153);
    CHECK(omw::bigEndian::decode_i64(data + 7, 1) == -120);
    CHECK(omw::bigEndian::decode_ui64(data + 7, 1) == 136);
    CHECK(omw::bigEndian::decode_i128(data + 11, 1) == omw::int128_t(-52));
    CHECK(omw::bigEndian::decode_ui128(data + 11, 1) == omw::uint128_t(204));

    CHECK(omw::bigEndian::decode_i16(data) == -222);
    CHECK(omw::bigEndian::decode_ui16(data) == 65314);
    CHECK(omw::bigEndian::decode_i32(data) == -14535868);
    CHECK(omw::bigEndian::decode_ui32(data) == 4280431428);
    CHECK(omw::bigEndian::decode_i64(data) == -62431076246194296);
    CHECK(omw::bigEndian::decode_ui64(data) == 18384312997463357320u);
    CHECK(omw::bigEndian::decode_i128(data) == omw::int128_t(0xFF22334455667788, 0x99AABBCCDDEE0011));
    CHECK(omw::bigEndian::decode_ui128(data) == omw::uint128_t(0xFF22334455667788, 0x99AABBCCDDEE0011));

    TESTUTIL_TRYCATCH_OPEN_DECLARE_VAL(int16_t, 123);
    TESTUTIL_TRYCATCH_CHECK(omw::bigEndian::decode_i16(nullptr), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::bigEndian::decode_i16(data, 0), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::bigEndian::decode_i16(data, 3), std::overflow_error);
    TESTUTIL_TRYCATCH_CLOSE();

    TESTUTIL_TRYCATCH_OPEN_DECLARE_VAL(uint16_t, 123);
    TESTUTIL_TRYCATCH_CHECK(omw::bigEndian::decode_ui16(nullptr), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::bigEndian::decode_ui16(data, 0), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::bigEndian::decode_ui16(data, 3), std::overflow_error);
    TESTUTIL_TRYCATCH_CLOSE();

    TESTUTIL_TRYCATCH_OPEN_DECLARE_VAL(int32_t, 123);
    TESTUTIL_TRYCATCH_CHECK(omw::bigEndian::decode_i32(nullptr), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::bigEndian::decode_i32(data, 0), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::bigEndian::decode_i32(data, 5), std::overflow_error);
    TESTUTIL_TRYCATCH_CLOSE();

    TESTUTIL_TRYCATCH_OPEN_DECLARE_VAL(uint32_t, 123);
    TESTUTIL_TRYCATCH_CHECK(omw::bigEndian::decode_ui32(nullptr), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::bigEndian::decode_ui32(data, 0), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::bigEndian::decode_ui32(data, 5), std::overflow_error);
    TESTUTIL_TRYCATCH_CLOSE();

    TESTUTIL_TRYCATCH_OPEN_DECLARE_VAL(int64_t, 123);
    TESTUTIL_TRYCATCH_CHECK(omw::bigEndian::decode_i64(nullptr), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::bigEndian::decode_i64(data, 0), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::bigEndian::decode_i64(data, 9), std::overflow_error);
    TESTUTIL_TRYCATCH_CLOSE();

    TESTUTIL_TRYCATCH_OPEN_DECLARE_VAL(uint64_t, 123);
    TESTUTIL_TRYCATCH_CHECK(omw::bigEndian::decode_ui64(nullptr), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::bigEndian::decode_ui64(data, 0), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::bigEndian::decode_ui64(data, 9), std::overflow_error);
    TESTUTIL_TRYCATCH_CLOSE();

    TESTUTIL_TRYCATCH_OPEN_DECLARE_VAL(omw::int128_t, omw::int128_t(123));
    TESTUTIL_TRYCATCH_CHECK(omw::bigEndian::decode_i128(nullptr), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::bigEndian::decode_i128(data, 0), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::bigEndian::decode_i128(data, 17), std::overflow_error);
    TESTUTIL_TRYCATCH_CLOSE();

    TESTUTIL_TRYCATCH_OPEN_DECLARE_VAL(omw::uint128_t, omw::uint128_t(123));
    TESTUTIL_TRYCATCH_CHECK(omw::bigEndian::decode_ui128(nullptr), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::bigEndian::decode_ui128(data, 0), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::bigEndian::decode_ui128(data, 17), std::overflow_error);
    TESTUTIL_TRYCATCH_CLOSE();
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
    omw::bigEndian::encode_16(buffer.data() + 0, sVal);
    CHECK(buffer == result);

    sVal = -1;
    buffer = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    result = { 0, 0xFF, 0xFF, 3, 4, 5, 6, 7, 8, 9 };
    omw::bigEndian::encode_16(buffer.data() + 1, sVal);
    CHECK(buffer == result);


    uint16_t uVal;

    uVal = 513;
    buffer = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    result = { 0, 1, 2, 1, 4, 5, 6, 7, 8, 9 };
    omw::bigEndian::encode_16(buffer.data() + 2, uVal);
    CHECK(buffer == result);

    uVal = 0xFFFF;
    buffer = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    result = { 0, 1, 2, 3, 4, 5, 6, 7, 0xFF, 0xFF };
    omw::bigEndian::encode_16(buffer.data() + 8, uVal);
    CHECK(buffer == result);


    buffer_type* pTryCatchValue;
    const buffer_type initial = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    TESTUTIL_TRYCATCH_SE_DECLARE_VAL(buffer_type, pTryCatchValue, initial);
    TESTUTIL_TRYCATCH_SE_CHECK((omw::bigEndian::encode_16(nullptr, sVal)), std::invalid_argument);
    TESTUTIL_TRYCATCH_SE_CHECK((omw::bigEndian::encode_16(nullptr, uVal)), std::invalid_argument);
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
    omw::bigEndian::encode_32(buffer.data() + 0, sVal);
    CHECK(buffer == result);

    sVal = -1;
    buffer = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    result = { 0, 0xFF, 0xFF, 0xFF, 0xFF, 5, 6, 7, 8, 9 };
    omw::bigEndian::encode_32(buffer.data() + 1, sVal);
    CHECK(buffer == result);


    uint32_t uVal;

    uVal = 514;
    buffer = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    result = { 0, 1, 0, 0, 2, 2, 6, 7, 8, 9 };
    omw::bigEndian::encode_32(buffer.data() + 2, uVal);
    CHECK(buffer == result);

    uVal = 0xFFFFFFFF;
    buffer = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    result = { 0, 1, 2, 3, 4, 5, 0xFF, 0xFF, 0xFF, 0xFF };
    omw::bigEndian::encode_32(buffer.data() + 6, uVal);
    CHECK(buffer == result);


    buffer_type* pTryCatchValue;
    const buffer_type initial = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    TESTUTIL_TRYCATCH_SE_DECLARE_VAL(buffer_type, pTryCatchValue, initial);
    TESTUTIL_TRYCATCH_SE_CHECK((omw::bigEndian::encode_32(nullptr, sVal)), std::invalid_argument);
    TESTUTIL_TRYCATCH_SE_CHECK((omw::bigEndian::encode_32(nullptr, uVal)), std::invalid_argument);
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
    omw::bigEndian::encode_64(buffer.data() + 0, sVal);
    CHECK(buffer == result);

    sVal = -1;
    buffer = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    result = { 0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 9 };
    omw::bigEndian::encode_64(buffer.data() + 1, sVal);
    CHECK(buffer == result);


    uint64_t uVal;

    uVal = 512;
    buffer = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    result = { 0, 1, 0, 0, 0, 0, 0, 0, 2, 0 };
    omw::bigEndian::encode_64(buffer.data() + 2, uVal);
    CHECK(buffer == result);

    uVal = 0xFFFFFFFFFFFFFFFF;
    buffer = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    result = { 0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 9 };
    omw::bigEndian::encode_64(buffer.data() + 1, uVal);
    CHECK(buffer == result);


    buffer_type* pTryCatchValue;
    const buffer_type initial = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    TESTUTIL_TRYCATCH_SE_DECLARE_VAL(buffer_type, pTryCatchValue, initial);
    TESTUTIL_TRYCATCH_SE_CHECK((omw::bigEndian::encode_64(nullptr, sVal)), std::invalid_argument);
    TESTUTIL_TRYCATCH_SE_CHECK((omw::bigEndian::encode_64(nullptr, uVal)), std::invalid_argument);
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
    omw::bigEndian::encode_128(buffer.data() + 0, sVal);
    CHECK(buffer == result);

    sVal = -1;
    buffer = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };
    result = { 0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 17, 18, 19 };
    omw::bigEndian::encode_128(buffer.data() + 1, sVal);
    CHECK(buffer == result);


    omw::uint128_t uVal;

    uVal.set(10, 0x123456);
    buffer = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };
    result = { 0, 1, 2, 3, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0x12, 0x34, 0x56 };
    omw::bigEndian::encode_128(buffer.data() + 4, uVal);
    CHECK(buffer == result);

    uVal.sets(-1);
    buffer = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };
    result = { 0, 1, 2, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 19 };
    omw::bigEndian::encode_128(buffer.data() + 3, uVal);
    CHECK(buffer == result);


    buffer_type* pTryCatchValue;
    const buffer_type initial = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };
    TESTUTIL_TRYCATCH_SE_DECLARE_VAL(buffer_type, pTryCatchValue, initial);
    TESTUTIL_TRYCATCH_SE_CHECK((omw::bigEndian::encode_128(nullptr, sVal)), std::invalid_argument);
    TESTUTIL_TRYCATCH_SE_CHECK((omw::bigEndian::encode_128(nullptr, uVal)), std::invalid_argument);
}


TEST_CASE("encoding.h omw::url")
{
    const omw::string str = "+\"*%&/()=asdf(fdsf)";
    const omw::string enc = "%2B%22%2A%25%26%2F%28%29%3Dasdf%28fdsf%29";

    CHECK(omw::url::encode(str) == enc);
    CHECK(omw::url::encode(omw::url::encode(str)) == "%252B%2522%252A%2525%2526%252F%2528%2529%253Dasdf%2528fdsf%2529");
}


#endif // TEST_OMW_ENCODING_H
