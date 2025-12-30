/*
author          Oliver Blaser
date            11.01.2022
copyright       MIT - Copyright (c) 2022 Oliver Blaser
*/

#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

#include "catch2/catch.hpp"
#include "testUtil.h"

#include <omw/int.h>

namespace {
bool base_int128_eq(const omw::Base_Int128& val, uint64_t h, uint64_t l) { return ((val.hi() == h) && (val.lo() == l)); }
bool base_int128_eqs(const omw::Base_Int128& val, int64_t h, uint64_t l) { return ((val.his() == h) && (val.lo() == l)); }
} // namespace


TEST_CASE("int.h macros")
{
    CHECK(OMW_8BIT_ALL == 255);
    CHECK(OMW_8BIT_LSB == 1);
    CHECK(OMW_8BIT_MSB == 128);

    CHECK(OMW_16BIT_ALL == static_cast<uint16_t>(UINT16_MAX));
    CHECK(OMW_16BIT_LSB == static_cast<uint16_t>(1));
    CHECK(OMW_16BIT_MSB == static_cast<uint16_t>(INT16_MIN));

    CHECK(OMW_32BIT_ALL == UINT32_MAX);
    CHECK(OMW_32BIT_LSB == 1);
    CHECK(OMW_32BIT_MSB == INT32_MIN);

    CHECK(OMW_64BIT_ALL == UINT64_MAX);
    CHECK(OMW_64BIT_LSB == 1);
    CHECK(OMW_64BIT_MSB == INT64_MIN);

    CHECK(base_int128_eq(OMW_128BIT_ALL, UINT64_MAX, UINT64_MAX));
    CHECK(base_int128_eq(OMW_128BIT_LSB, 0, 1));
    CHECK(base_int128_eqs(OMW_128BIT_MSB, INT64_MIN, 0));

    CHECK(base_int128_eqs(OMW_INT128_MIN, INT64_MIN, 0));
    CHECK(base_int128_eq(OMW_INT128_MAX, INT64_MAX, UINT64_MAX));
    CHECK(base_int128_eq(OMW_UINT128_MAX, UINT64_MAX, UINT64_MAX));
}



TEST_CASE("int.h omw::Base_Int128 ctor")
{
    CHECK(base_int128_eq(omw::Base_Int128(), 0, 0));

    CHECK(base_int128_eq(omw::Base_Int128(0), 0, 0));
    CHECK(base_int128_eq(omw::Base_Int128(1), 0, 1));
    CHECK(base_int128_eq(omw::Base_Int128(123), 0, 123));
    CHECK(base_int128_eq(omw::Base_Int128(-123), UINT64_MAX, -123));
    CHECK(base_int128_eq(omw::Base_Int128(-1), UINT64_MAX, UINT64_MAX));
    CHECK(base_int128_eq(omw::Base_Int128(INT32_MIN), UINT64_MAX, INT32_MIN));
    CHECK(base_int128_eq(omw::Base_Int128(INT32_MAX), 0, INT32_MAX));
    CHECK(base_int128_eq(omw::Base_Int128(UINT32_MAX), 0, UINT32_MAX));
    CHECK(base_int128_eq(omw::Base_Int128(UINT64_MAX), UINT64_MAX, UINT64_MAX));
    CHECK(base_int128_eq(omw::Base_Int128(INT64_MAX), 0, INT64_MAX));
    CHECK(base_int128_eq(omw::Base_Int128(INT64_MIN), UINT64_MAX, INT64_MIN));

    CHECK(base_int128_eq(omw::Base_Int128(0, 0), 0, 0));
    CHECK(base_int128_eq(omw::Base_Int128(0x0123456789abcdef, 0xa0b1c2d3e4f56789), 0x0123456789abcdef, 0xa0b1c2d3e4f56789));
    CHECK(base_int128_eq(omw::Base_Int128(0x1234567890abcdef, 0xa0b1c2d3e4f56789), 0x1234567890abcdef, 0xa0b1c2d3e4f56789));
    CHECK(base_int128_eq(omw::Base_Int128(0xa0b1c2d3e4f56789, 0x1234567890abcdef), 0xa0b1c2d3e4f56789, 0x1234567890abcdef));

    CHECK(base_int128_eq(omw::Base_Int128(0, 0, 0, 0), 0, 0));
    CHECK(base_int128_eq(omw::Base_Int128(0x01234567, 0x12345678, 0xABCDEF01, 0x98765432), 0x0123456712345678, 0xABCDEF0198765432));
    CHECK(base_int128_eq(omw::Base_Int128(0xABCDEF01, 0x12345678, 0x01234567, 0x98765432), 0xABCDEF0112345678, 0x0123456798765432));
    CHECK(base_int128_eq(omw::Base_Int128(0x98765432, 0x12345678, 0xABCDEF01, 0x01234567), 0x9876543212345678, 0xABCDEF0101234567));
}

TEST_CASE("int.h omw::Base_Int128 set")
{
    omw::Base_Int128 x;
    CHECK(base_int128_eq(x, 0, 0));



    x.set(0, 0);
    CHECK(base_int128_eq(x, 0, 0));

    x.set(0x0123456789abcdef, 0xa0b1c2d3e4f56789);
    CHECK(base_int128_eq(x, 0x0123456789abcdef, 0xa0b1c2d3e4f56789));

    x.set(0x1234567890abcdef, 0xa0b1c2d3e4f56789);
    CHECK(base_int128_eq(x, 0x1234567890abcdef, 0xa0b1c2d3e4f56789));

    x.set(0xa0b1c2d3e4f56789, 0x1234567890abcdef);
    CHECK(base_int128_eq(x, 0xa0b1c2d3e4f56789, 0x1234567890abcdef));



    x.set(0, 0, 0, 0);
    CHECK(base_int128_eq(x, 0, 0));

    x.set(0x01234567, 0x12345678, 0xABCDEF01, 0x98765432);
    CHECK(base_int128_eq(x, 0x0123456712345678, 0xABCDEF0198765432));

    x.set(0xABCDEF01, 0x12345678, 0x01234567, 0x98765432);
    CHECK(base_int128_eq(x, 0xABCDEF0112345678, 0x0123456798765432));

    x.set(0x98765432, 0x12345678, 0xABCDEF01, 0x01234567);
    CHECK(base_int128_eq(x, 0x9876543212345678, 0xABCDEF0101234567));
}

TEST_CASE("int.h omw::Base_Int128 sets")
{
    omw::Base_Int128 x;
    CHECK(base_int128_eq(x, 0, 0));



    x.sets(0);
    CHECK(base_int128_eq(x, 0, 0));

    x.sets(123);
    CHECK(base_int128_eq(x, 0, 123));

    x.sets(-1);
    CHECK(base_int128_eq(x, UINT64_MAX, UINT64_MAX));

    x.sets(-123);
    CHECK(base_int128_eq(x, UINT64_MAX, 0xFFFFFFFFFFFFFF85));

    x.sets(INT32_MIN);
    CHECK(base_int128_eq(x, UINT64_MAX, 0xFFFFFFFF80000000));

    x.sets(INT32_MAX);
    CHECK(base_int128_eq(x, 0, 0x07FFFFFFF));

    x.sets(UINT32_MAX);
    CHECK(base_int128_eq(x, 0, UINT32_MAX));

    x.sets(INT64_MIN);
    CHECK(base_int128_eq(x, UINT64_MAX, 0x8000000000000000));

    x.sets(INT64_MAX);
    CHECK(base_int128_eq(x, 0, 0x7FFFFFFFFFFFFFFF));

    x.sets(UINT64_MAX);
    CHECK(base_int128_eq(x, UINT64_MAX, UINT64_MAX));



    x.sets(1, 0);
    CHECK(base_int128_eq(x, 1, 0));

    x.sets(0x0123456789abcdef, 0xa0b1c2d3e4f56789);
    CHECK(base_int128_eq(x, 0x0123456789abcdef, 0xa0b1c2d3e4f56789));

    x.sets(0x1234567890abcdef, 0xa0b1c2d3e4f56789);
    CHECK(base_int128_eq(x, 0x1234567890abcdef, 0xa0b1c2d3e4f56789));

    x.sets(0xa0b1c2d3e4f56789, 0x1234567890abcdef);
    CHECK(base_int128_eq(x, 0xa0b1c2d3e4f56789, 0x1234567890abcdef));



    x.sets(0, 0, 0, 0);
    CHECK(base_int128_eq(x, 0, 0));

    x.sets(0x01234567, 0x12345678, 0xABCDEF01, 0x98765432);
    CHECK(base_int128_eq(x, 0x0123456712345678, 0xABCDEF0198765432));

    x.sets(0xABCDEF01, 0x12345678, 0x01234567, 0x98765432);
    CHECK(base_int128_eq(x, 0xABCDEF0112345678, 0x0123456798765432));

    x.sets(0x98765432, 0x12345678, 0xABCDEF01, 0x01234567);
    CHECK(base_int128_eq(x, 0x9876543212345678, 0xABCDEF0101234567));



    const uint8_t data[20] = { 0x78, 0x90, 0x34, 0xAB, 0xCD, 0x56, 0xEF, 0x12, 0x49, 0x21, 0x87, 0x37, 0x94, 0x54, 0xBE, 0xFA, 123, 54, 87, 10 };

    x.set(123, 456);
    x.sets(nullptr, 0);
    CHECK(base_int128_eq(x, 123, 456));
    x.sets(nullptr, 2);
    CHECK(base_int128_eq(x, 123, 456));
    x.sets(data, 0);
    CHECK(base_int128_eq(x, 123, 456));

    x.sets(data, 2);
    CHECK(base_int128_eq(x, 0, 0x7890));
    x.sets(data, 16);
    CHECK(base_int128_eq(x, 0x789034ABCD56EF12, 0x492187379454BEFA));
    x.sets(data + 1, 16);
    CHECK(base_int128_eq(x, 0x9034ABCD56EF1249, 0x2187379454BEFA7B));
    x.sets(data + 5, 5);
    CHECK(base_int128_eq(x, 0, 0x56EF124921));

    x.sets(data + 1, 15);
    CHECK(base_int128_eq(x, 0xFF9034ABCD56EF12, 0x492187379454BEFA));
    x.sets(data + 1, 4);
    CHECK(base_int128_eq(x, UINT64_MAX, 0xFFFFFFFF9034ABCD));

    x.set(123, 456);
    try
    {
        x.sets(data, 17);
    }
    catch (std::overflow_error& ex)
    {
        const char* const msg = ex.what();
        CHECK(1 == 1);
    }
    catch (...)
    {
        CHECK(1 != 1);
    }
    CHECK(base_int128_eq(x, 123, 456));
    try
    {
        x.sets(data, -1);
    }
    catch (std::overflow_error& ex)
    {
        const char* const msg = ex.what();
        CHECK(1 == 1);
    }
    catch (...)
    {
        CHECK(1 != 1);
    }
    CHECK(base_int128_eq(x, 123, 456));
}

TEST_CASE("int.h omw::Base_Int128 setu")
{
    omw::Base_Int128 x;
    CHECK(base_int128_eq(x, 0, 0));



    x.setu(0);
    CHECK(base_int128_eq(x, 0, 0));

    x.setu(123);
    CHECK(base_int128_eq(x, 0, 123));

    x.setu(-1);
    CHECK(base_int128_eq(x, 0, UINT64_MAX));

    x.setu(-123);
    CHECK(base_int128_eq(x, 0, 0xFFFFFFFFFFFFFF85));

    x.setu(INT32_MIN);
    CHECK(base_int128_eq(x, 0, 0xFFFFFFFF80000000));

    x.setu(0x80000000);
    CHECK(base_int128_eq(x, 0, 0x80000000));

    x.setu(INT32_MAX);
    CHECK(base_int128_eq(x, 0, 0x7FFFFFFF));

    x.setu(UINT32_MAX);
    CHECK(base_int128_eq(x, 0, 0xFFFFFFFF));

    x.setu(INT64_MIN);
    CHECK(base_int128_eq(x, 0, 0x8000000000000000));

    x.setu(INT64_MAX);
    CHECK(base_int128_eq(x, 0, 0x7FFFFFFFFFFFFFFF));

    x.setu(UINT64_MAX);
    CHECK(base_int128_eq(x, 0, UINT64_MAX));



    const uint8_t data[20] = { 0x78, 0x90, 0x34, 0xAB, 0xCD, 0x56, 0xEF, 0x12, 0x49, 0x21, 0x87, 0x37, 0x94, 0x54, 0xBE, 0xFA, 123, 54, 87, 10 };

    x.set(123, 456);
    x.setu(nullptr, 0);
    CHECK(base_int128_eq(x, 123, 456));
    x.setu(nullptr, 2);
    CHECK(base_int128_eq(x, 123, 456));
    x.setu(data, 0);
    CHECK(base_int128_eq(x, 123, 456));

    x.setu(data, 2);
    CHECK(base_int128_eq(x, 0, 0x7890));
    x.setu(data, 16);
    CHECK(base_int128_eq(x, 0x789034ABCD56EF12, 0x492187379454BEFA));
    x.setu(data + 1, 16);
    CHECK(base_int128_eq(x, 0x9034ABCD56EF1249, 0x2187379454BEFA7B));
    x.setu(data + 5, 5);
    CHECK(base_int128_eq(x, 0, 0x56EF124921));

    x.setu(data + 1, 15);
    CHECK(base_int128_eq(x, 0x009034ABCD56EF12, 0x492187379454BEFA));
    x.setu(data + 1, 4);
    CHECK(base_int128_eq(x, 0, 0x9034ABCD));

    x.set(123, 456);
    try
    {
        x.setu(data, 17);
    }
    catch (std::overflow_error& ex)
    {
        const char* const msg = ex.what();
        CHECK(1 == 1);
    }
    catch (...)
    {
        CHECK(1 != 1);
    }
    CHECK(base_int128_eq(x, 123, 456));
    try
    {
        x.setu(data, -1);
    }
    catch (std::overflow_error& ex)
    {
        const char* const msg = ex.what();
        CHECK(1 == 1);
    }
    catch (...)
    {
        CHECK(1 != 1);
    }
    CHECK(base_int128_eq(x, 123, 456));
}

TEST_CASE("int.h omw::Base_Int128 getters")
{
    omw::Base_Int128 x;

    x.set(0, 0);
    CHECK(x.hi() == 0);
    CHECK(x.his() == 0);
    CHECK(x.lo() == 0);

    x.set(0, 123456789);
    CHECK(x.hi() == 0);
    CHECK(x.his() == 0);
    CHECK(x.lo() == 123456789);

    x.set(1234567890123, 0);
    CHECK(x.hi() == 1234567890123);
    CHECK(x.his() == 1234567890123);
    CHECK(x.lo() == 0);

    x.set(0x8000000000000000, 0);
    CHECK(x.hi() == 9223372036854775808u);
    CHECK(x.his() == INT64_MIN);
    CHECK(x.lo() == 0);

    x.set(UINT64_MAX, 0);
    CHECK(x.hi() == UINT64_MAX);
    CHECK(x.his() == -1);
    CHECK(x.lo() == 0);
}

TEST_CASE("int.h omw::Base_Int128 bool conversion operators")
{
    omw::Base_Int128 x;

    if (x) { CHECK(1 != 1); }
    else { CHECK(1 == 1); }

    x.set(0, 1);
    if (x) { CHECK(1 == 1); }
    else { CHECK(1 != 1); }

    x.set(1, 0);
    if (x) { CHECK(1 == 1); }
    else { CHECK(1 != 1); }

    x.set(1, 1);
    if (x) { CHECK(1 == 1); }
    else { CHECK(1 != 1); }



    x.set(0, 1);
    if (x && true) { CHECK(1 == 1); }
    else { CHECK(1 != 1); }

    x.set(0, 0);
    if (x && true) { CHECK(1 != 1); }
    else { CHECK(1 == 1); }
}

TEST_CASE("int.h omw::Base_Int128 operators")
{
    omw::Base_Int128 x;

    // += -=
    x.set(0, 0);
    x += 54;
    CHECK(base_int128_eq(x, 0, 54));
    x -= 47;
    CHECK(base_int128_eq(x, 0, 7));
    x += 123;
    CHECK(base_int128_eq(x, 0, 130));
    x -= 63;
    CHECK(base_int128_eq(x, 0, 67));
    x -= -67;
    CHECK(base_int128_eq(x, 0, 134));

    x.set(0, 0);
    x += 5;
    CHECK(base_int128_eq(x, 0, 5));
    x -= 8;
    CHECK(base_int128_eq(x, UINT64_MAX, UINT64_MAX - 2));
    x += omw::Base_Int128(UINT64_MAX, UINT64_MAX);
    CHECK(base_int128_eq(x, UINT64_MAX, UINT64_MAX - 3));
    x += -1;
    CHECK(base_int128_eq(x, UINT64_MAX, UINT64_MAX - 4));
    x -= -1;
    CHECK(base_int128_eq(x, UINT64_MAX, UINT64_MAX - 3));

    x.set(0, UINT64_MAX - 2);
    x += 6;
    CHECK(base_int128_eq(x, 1, 3));
    x -= omw::Base_Int128(0, UINT64_MAX);
    CHECK(base_int128_eq(x, 0, 4));
    x -= omw::Base_Int128(UINT64_MAX, UINT64_MAX);
    CHECK(base_int128_eq(x, 0, 5));


    // &= |= ^=
    x.set(0, 0);
    x |= omw::Base_Int128(0xFFFFFFFF5555AAAA, 0x12345678);
    CHECK(base_int128_eq(x, 0xFFFFFFFF5555AAAA, 0x12345678));
    x &= omw::Base_Int128(0x5555AAAA00FF00FF, 0xFFFF0000FFFF0000);
    CHECK(base_int128_eq(x, 0x5555AAAA005500AA, 0x12340000));
    x ^= omw::Base_Int128(0x55AA00FF0AAF055F, 0x987600009999ABCD);
    CHECK(base_int128_eq(x, 0x00FFAA550AFA05F5, 0x987600008BADABCD));
    x |= -1;
    CHECK(base_int128_eq(x, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF));


    // a++
    x.set(0, 0xFFFFFFFFFFFFFFFD);
    CHECK(base_int128_eq(x++, 0, 0xFFFFFFFFFFFFFFFD));
    CHECK(base_int128_eq(x++, 0, 0xFFFFFFFFFFFFFFFE));
    CHECK(base_int128_eq(x++, 0, 0xFFFFFFFFFFFFFFFF));
    CHECK(base_int128_eq(x++, 1, 0));
    CHECK(base_int128_eq(x, 1, 1));

    x.set(0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFD);
    CHECK(base_int128_eq(x++, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFD));
    CHECK(base_int128_eq(x++, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFE));
    CHECK(base_int128_eq(x++, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF));
    CHECK(base_int128_eq(x++, 0, 0));
    CHECK(base_int128_eq(x, 0, 1));


    // ++a
    x.set(0, 0xFFFFFFFFFFFFFFFC);
    CHECK(base_int128_eq(++x, 0, 0xFFFFFFFFFFFFFFFD));
    CHECK(base_int128_eq(++x, 0, 0xFFFFFFFFFFFFFFFE));
    CHECK(base_int128_eq(++x, 0, 0xFFFFFFFFFFFFFFFF));
    CHECK(base_int128_eq(++x, 1, 0));
    CHECK(base_int128_eq(++x, 1, 1));

    x.set(0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFC);
    CHECK(base_int128_eq(++x, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFD));
    CHECK(base_int128_eq(++x, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFE));
    CHECK(base_int128_eq(++x, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF));
    CHECK(base_int128_eq(++x, 0, 0));
    CHECK(base_int128_eq(++x, 0, 1));


    // a--
    x.set(1, 1);
    CHECK(base_int128_eq(x--, 1, 1));
    CHECK(base_int128_eq(x--, 1, 0));
    CHECK(base_int128_eq(x--, 0, 0xFFFFFFFFFFFFFFFF));
    CHECK(base_int128_eq(x--, 0, 0xFFFFFFFFFFFFFFFE));
    CHECK(base_int128_eq(x, 0, 0xFFFFFFFFFFFFFFFD));

    x.set(0, 1);
    CHECK(base_int128_eq(x--, 0, 1));
    CHECK(base_int128_eq(x--, 0, 0));
    CHECK(base_int128_eq(x--, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF));
    CHECK(base_int128_eq(x--, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFE));
    CHECK(base_int128_eq(x, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFD));


    // --a
    x.set(1, 2);
    CHECK(base_int128_eq(--x, 1, 1));
    CHECK(base_int128_eq(--x, 1, 0));
    CHECK(base_int128_eq(--x, 0, 0xFFFFFFFFFFFFFFFF));
    CHECK(base_int128_eq(--x, 0, 0xFFFFFFFFFFFFFFFE));
    CHECK(base_int128_eq(--x, 0, 0xFFFFFFFFFFFFFFFD));

    x.set(0, 2);
    CHECK(base_int128_eq(--x, 0, 1));
    CHECK(base_int128_eq(--x, 0, 0));
    CHECK(base_int128_eq(--x, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF));
    CHECK(base_int128_eq(--x, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFE));
    CHECK(base_int128_eq(--x, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFD));
}

TEST_CASE("int.h omw::Base_Int128 left shift operator")
{
    omw::Base_Int128 x;

    x.set(0x1234567800000000, 0x12345678);
    x <<= 0;
    CHECK(base_int128_eq(x, 0x1234567800000000, 0x12345678));

    x.set(0, 1);
    x <<= 3;
    CHECK(base_int128_eq(x, 0, 8));

    x.set(1, 0);
    x <<= 3;
    CHECK(base_int128_eq(x, 8, 0));

    x.set(0, 0xA5);
    x <<= 32;
    CHECK(base_int128_eq(x, 0, 0xA500000000));

    x.set(0, 1);
    x <<= 65;
    CHECK(base_int128_eq(x, 2, 0));

    x.set(UINT64_MAX, UINT64_MAX);
    x <<= 127;
    CHECK(base_int128_eq(x, 0x8000000000000000, 0));

    x.set(0, 1);
    x <<= 128;
    CHECK(base_int128_eq(x, 0, 0));

    x.set(UINT64_MAX, UINT64_MAX);
    x <<= 128;
    CHECK(base_int128_eq(x, 0, 0));

    x.set(0, 0x12345678);
    x <<= 32;
    CHECK(base_int128_eq(x, 0, 0x1234567800000000));

    x.set(0x1234567800000000, 0x12345678);
    x <<= 48;
    CHECK(base_int128_eq(x, 0x1234, 0x5678000000000000));
}



TEST_CASE("int.h omw::SignedInt128")
{
    omw::SignedInt128 x;
    CHECK(base_int128_eq(x, 0, 0));
    CHECK(x.isNegative() == false);
    CHECK(x.sign() == 1);

    x = omw::SignedInt128();
    CHECK(base_int128_eq(x, 0, 0));
    CHECK(x.isNegative() == false);
    CHECK(x.sign() == 1);

    x = omw::SignedInt128(0);
    CHECK(base_int128_eq(x, 0, 0));
    CHECK(x.isNegative() == false);
    CHECK(x.sign() == 1);

    x = omw::SignedInt128(1);
    CHECK(base_int128_eq(x, 0, 1));
    CHECK(x.isNegative() == false);
    CHECK(x.sign() == 1);

    x = omw::SignedInt128(123);
    CHECK(base_int128_eq(x, 0, 123));
    CHECK(x.isNegative() == false);
    CHECK(x.sign() == 1);

    x = omw::SignedInt128(-123);
    CHECK(base_int128_eq(x, UINT64_MAX, -123));
    CHECK(x.isNegative() == true);
    CHECK(x.sign() == -1);

    x = omw::SignedInt128(-1);
    CHECK(base_int128_eq(x, UINT64_MAX, UINT64_MAX));
    CHECK(x.isNegative() == true);
    CHECK(x.sign() == -1);

    x = omw::SignedInt128(INT32_MIN);
    CHECK(base_int128_eq(x, UINT64_MAX, INT32_MIN));
    CHECK(x.isNegative() == true);
    CHECK(x.sign() == -1);

    x = omw::SignedInt128(INT32_MAX);
    CHECK(base_int128_eq(x, 0, INT32_MAX));
    CHECK(x.isNegative() == false);
    CHECK(x.sign() == 1);

    x = omw::SignedInt128(UINT32_MAX);
    CHECK(base_int128_eq(x, 0, UINT32_MAX));
    CHECK(x.isNegative() == false);
    CHECK(x.sign() == 1);

    x = omw::SignedInt128(UINT64_MAX);
    CHECK(base_int128_eq(x, UINT64_MAX, UINT64_MAX));
    CHECK(x.isNegative() == true);
    CHECK(x.sign() == -1);

    x = omw::SignedInt128(INT64_MAX);
    CHECK(base_int128_eq(x, 0, INT64_MAX));
    CHECK(x.isNegative() == false);
    CHECK(x.sign() == 1);

    x = omw::SignedInt128(INT64_MIN);
    CHECK(base_int128_eq(x, UINT64_MAX, INT64_MIN));
    CHECK(x.isNegative() == true);
    CHECK(x.sign() == -1);


    uint64_t tmpH = 0;
    x = omw::SignedInt128(tmpH, 0);
    CHECK(base_int128_eq(x, 0, 0));
    CHECK(x.isNegative() == false);
    CHECK(x.sign() == 1);

    x = omw::SignedInt128(0x0123456789abcdef, 0xa0b1c2d3e4f56789);
    CHECK(base_int128_eq(x, 0x0123456789abcdef, 0xa0b1c2d3e4f56789));
    CHECK(x.isNegative() == false);
    CHECK(x.sign() == 1);

    x = omw::SignedInt128(0x1234567890abcdef, 0xa0b1c2d3e4f56789);
    CHECK(base_int128_eq(x, 0x1234567890abcdef, 0xa0b1c2d3e4f56789));
    CHECK(x.isNegative() == false);
    CHECK(x.sign() == 1);

    x = omw::SignedInt128(0xa0b1c2d3e4f56789, 0x1234567890abcdef);
    CHECK(base_int128_eq(x, 0xa0b1c2d3e4f56789, 0x1234567890abcdef));
    CHECK(x.isNegative() == true);
    CHECK(x.sign() == -1);



    x = omw::SignedInt128(0, 0, 0, 0);
    CHECK(base_int128_eq(x, 0, 0));
    CHECK(x.isNegative() == false);
    CHECK(x.sign() == 1);

    x = omw::SignedInt128(0x01234567, 0x12345678, 0xABCDEF01, 0x98765432);
    CHECK(base_int128_eq(x, 0x0123456712345678, 0xABCDEF0198765432));
    CHECK(x.isNegative() == false);
    CHECK(x.sign() == 1);

    x = omw::SignedInt128(0xABCDEF01, 0x12345678, 0x01234567, 0x98765432);
    CHECK(base_int128_eq(x, 0xABCDEF0112345678, 0x0123456798765432));
    CHECK(x.isNegative() == true);
    CHECK(x.sign() == -1);

    x = omw::SignedInt128(0x98765432, 0x12345678, 0xABCDEF01, 0x01234567);
    CHECK(base_int128_eq(x, 0x9876543212345678, 0xABCDEF0101234567));
    CHECK(x.isNegative() == true);
    CHECK(x.sign() == -1);



    omw::SignedInt128 signedOther;

    signedOther = 123;
    x = signedOther;
    CHECK(base_int128_eq(x, 0, 123));
    CHECK(x.isNegative() == false);
    CHECK(x.sign() == 1);
    x = omw::SignedInt128(signedOther);
    CHECK(base_int128_eq(x, 0, 123));
    CHECK(x.isNegative() == false);
    CHECK(x.sign() == 1);

    signedOther = -123;
    x = signedOther;
    CHECK(base_int128_eq(x, UINT64_MAX, -123));
    CHECK(x.isNegative() == true);
    CHECK(x.sign() == -1);
    x = omw::SignedInt128(signedOther);
    CHECK(base_int128_eq(x, UINT64_MAX, -123));
    CHECK(x.isNegative() == true);
    CHECK(x.sign() == -1);



    omw::UnsignedInt128 unsignedOther;

    unsignedOther = 123;
    x = unsignedOther;
    CHECK(base_int128_eq(x, 0, 123));
    CHECK(x.isNegative() == false);
    CHECK(x.sign() == 1);
    x = omw::SignedInt128(unsignedOther);
    CHECK(base_int128_eq(x, 0, 123));
    CHECK(x.isNegative() == false);
    CHECK(x.sign() == 1);

    unsignedOther = -123;
    x = unsignedOther;
    CHECK(base_int128_eq(x, UINT64_MAX, -123));
    CHECK(x.isNegative() == true);
    CHECK(x.sign() == -1);
    x = omw::SignedInt128(unsignedOther);
    CHECK(base_int128_eq(x, UINT64_MAX, -123));
    CHECK(x.isNegative() == true);
    CHECK(x.sign() == -1);
}

TEST_CASE("int.h omw::SignedInt128 assign operator")
{
    omw::SignedInt128 x;

    x.set(123, 456);
    x = 54;
    CHECK(base_int128_eq(x, 0, 54));
    x = -1;
    CHECK(base_int128_eq(x, OMW_64BIT_ALL, OMW_64BIT_ALL));
    x = 123;
    CHECK(base_int128_eq(x, 0, 123));
    x = -67;
    CHECK(base_int128_eq(x, OMW_64BIT_ALL, 0xFFFFFFFFFFFFFFBD));
}

TEST_CASE("int.h omw::SignedInt128 right shift operator")
{
    omw::SignedInt128 x;

#ifdef OMWi_INT_RIGHTSHIFT_DEBUG
    omw::SignedInt128& r = x;

    // CHECK(r.hi() == 0xabcd);
    // CHECK(r.lo() == 0xabcd);
    // std::cout << "\033[99m" << omw::toHexStr(r.oldValue_h, '-') + "  " + omw::toHexStr(r.oldValue_l, '-') << "\033[39m" << std::endl;
    // std::cout << "\033[95m" << omw::toHexStr(r.lastMask_h, '-') + "  " + omw::toHexStr(r.lastMask_l, '-') << "\033[39m\n\n" << std::endl;

    std::cout << "\n\n\033[99m"
              << "oldValue"
              << "\033[39m" << std::endl;
    std::cout << "\033[95m"
              << "lastMask"
              << "\033[39m\n\n"
              << std::endl;
#endif

    x.set(0x8000000000000000, 0x8003);
    x >>= 0;
    CHECK(base_int128_eq(x, 0x8000000000000000, 0x8003));
    x.set(0x4000000000000000, 0x8003);
    x >>= 0;
    CHECK(base_int128_eq(x, 0x4000000000000000, 0x8003));

    x.set(0x8000000000000000, 0x8003);
    x >>= 3;
    CHECK(base_int128_eq(x, 0xF000000000000000, 0x1000));
    x.set(0x4000000000000000, 0x8003);
    x >>= 3;
    CHECK(base_int128_eq(x, 0x0800000000000000, 0x1000));

    x.set(0x8000000000000000, 0x8003);
    x >>= 63;
    CHECK(base_int128_eq(x, OMW_64BIT_ALL, 0));
    x.set(0x4000000000000000, 0x8003);
    x >>= 63;
    CHECK(base_int128_eq(x, 0, 0x8000000000000000));

    x.set(0x8000000000000000, 0x8003);
    x >>= 64;
    CHECK(base_int128_eq(x, OMW_64BIT_ALL, 0x8000000000000000));
    x.set(0x4000000000000000, 0x8003);
    x >>= 64;
    CHECK(base_int128_eq(x, 0, 0x4000000000000000));

    x.set(0x8000000000000000, 0x8003);
    x >>= 65;
    CHECK(base_int128_eq(x, OMW_64BIT_ALL, 0xC000000000000000));
    x.set(0x4000000000000000, 0x8003);
    x >>= 65;
    CHECK(base_int128_eq(x, 0, 0x2000000000000000));

    x.set(0x8000000000000000, 0x8003);
    x >>= 127;
    CHECK(base_int128_eq(x, OMW_64BIT_ALL, OMW_64BIT_ALL));
    x.set(0x4000000000000000, 0x8003);
    x >>= 127;
    CHECK(base_int128_eq(x, 0, 0));
    x.set(0x4000000000000000, 0x8003);
    x >>= 126;
    CHECK(base_int128_eq(x, 0, 1));

    x.set(0x8000000000000000, 0x8003);
    x >>= 128;
    CHECK(base_int128_eq(x, OMW_64BIT_ALL, OMW_64BIT_ALL));
    x.set(0x4000000000000000, 0x8003);
    x >>= 128;
    CHECK(base_int128_eq(x, 0, 0));

    x.set(0x8000000000000000, 0x8003);
    x >>= 129;
    CHECK(base_int128_eq(x, OMW_64BIT_ALL, OMW_64BIT_ALL));
    x.set(0x4000000000000000, 0x8003);
    x >>= 129;
    CHECK(base_int128_eq(x, 0, 0));

    x.set(0x8000000000000000, 0x8003);
    x >>= -1;
    CHECK(base_int128_eq(x, OMW_64BIT_ALL, OMW_64BIT_ALL));
    x.set(0x4000000000000000, 0x8003);
    x >>= -1;
    CHECK(base_int128_eq(x, 0, 0));
}



TEST_CASE("int.h omw::UnsignedInt128")
{
    omw::UnsignedInt128 x;
    CHECK(base_int128_eq(x, 0, 0));

    x = omw::UnsignedInt128();
    CHECK(base_int128_eq(x, 0, 0));

    x = omw::UnsignedInt128(0);
    CHECK(base_int128_eq(x, 0, 0));

    x = omw::UnsignedInt128(1);
    CHECK(base_int128_eq(x, 0, 1));

    x = omw::UnsignedInt128(123);
    CHECK(base_int128_eq(x, 0, 123));

    x = omw::UnsignedInt128(-123);
    CHECK(base_int128_eq(x, UINT64_MAX, -123));

    x = omw::UnsignedInt128(-1);
    CHECK(base_int128_eq(x, UINT64_MAX, UINT64_MAX));

    x = omw::UnsignedInt128(INT32_MIN);
    CHECK(base_int128_eq(x, UINT64_MAX, INT32_MIN));

    x = omw::UnsignedInt128(INT32_MAX);
    CHECK(base_int128_eq(x, 0, INT32_MAX));

    x = omw::UnsignedInt128(UINT32_MAX);
    CHECK(base_int128_eq(x, 0, UINT32_MAX));

    x = omw::UnsignedInt128(UINT64_MAX);
    CHECK(base_int128_eq(x, UINT64_MAX, UINT64_MAX));

    x = omw::UnsignedInt128(INT64_MAX);
    CHECK(base_int128_eq(x, 0, INT64_MAX));

    x = omw::UnsignedInt128(INT64_MIN);
    CHECK(base_int128_eq(x, UINT64_MAX, INT64_MIN));


    uint64_t tmpH = 0;
    x = omw::UnsignedInt128(tmpH, 0);
    CHECK(base_int128_eq(x, 0, 0));

    x = omw::UnsignedInt128(0x0123456789abcdef, 0xa0b1c2d3e4f56789);
    CHECK(base_int128_eq(x, 0x0123456789abcdef, 0xa0b1c2d3e4f56789));

    x = omw::UnsignedInt128(0x1234567890abcdef, 0xa0b1c2d3e4f56789);
    CHECK(base_int128_eq(x, 0x1234567890abcdef, 0xa0b1c2d3e4f56789));

    x = omw::UnsignedInt128(0xa0b1c2d3e4f56789, 0x1234567890abcdef);
    CHECK(base_int128_eq(x, 0xa0b1c2d3e4f56789, 0x1234567890abcdef));



    x = omw::UnsignedInt128(0, 0, 0, 0);
    CHECK(base_int128_eq(x, 0, 0));

    x = omw::UnsignedInt128(0x01234567, 0x12345678, 0xABCDEF01, 0x98765432);
    CHECK(base_int128_eq(x, 0x0123456712345678, 0xABCDEF0198765432));

    x = omw::UnsignedInt128(0xABCDEF01, 0x12345678, 0x01234567, 0x98765432);
    CHECK(base_int128_eq(x, 0xABCDEF0112345678, 0x0123456798765432));

    x = omw::UnsignedInt128(0x98765432, 0x12345678, 0xABCDEF01, 0x01234567);
    CHECK(base_int128_eq(x, 0x9876543212345678, 0xABCDEF0101234567));



    omw::UnsignedInt128 unsignedOther;

    unsignedOther = 123;
    x = unsignedOther;
    CHECK(base_int128_eq(x, 0, 123));
    x = omw::UnsignedInt128(unsignedOther);
    CHECK(base_int128_eq(x, 0, 123));

    unsignedOther = -123;
    x = unsignedOther;
    CHECK(base_int128_eq(x, UINT64_MAX, -123));
    x = omw::UnsignedInt128(unsignedOther);
    CHECK(base_int128_eq(x, UINT64_MAX, -123));



    omw::SignedInt128 signedOther;

    signedOther = 123;
    x = signedOther;
    CHECK(base_int128_eq(x, 0, 123));
    x = omw::UnsignedInt128(signedOther);
    CHECK(base_int128_eq(x, 0, 123));

    signedOther = -123;
    x = signedOther;
    CHECK(base_int128_eq(x, UINT64_MAX, -123));
    x = omw::UnsignedInt128(signedOther);
    CHECK(base_int128_eq(x, UINT64_MAX, -123));
}

TEST_CASE("int.h omw::UnsignedInt128 assign operator")
{
    omw::UnsignedInt128 x;

    x.set(123, 456);
    x = 54;
    CHECK(base_int128_eq(x, 0, 54));
    x = -1;
    CHECK(base_int128_eq(x, OMW_64BIT_ALL, OMW_64BIT_ALL));
    x = 123;
    CHECK(base_int128_eq(x, 0, 123));
    x = -67;
    CHECK(base_int128_eq(x, OMW_64BIT_ALL, 0xFFFFFFFFFFFFFFBD));
}

TEST_CASE("int.h omw::UnsignedInt128 right shift operator")
{
    omw::UnsignedInt128 x;

    x.set(0x8000000000000000, 0x8003);
    x >>= 0;
    CHECK(base_int128_eq(x, 0x8000000000000000, 0x8003));
    x.set(0x4000000000000000, 0x8003);
    x >>= 0;
    CHECK(base_int128_eq(x, 0x4000000000000000, 0x8003));

    x.set(0x8000000000000000, 0x8003);
    x >>= 3;
    CHECK(base_int128_eq(x, 0x1000000000000000, 0x1000));
    x.set(0x4000000000000000, 0x8003);
    x >>= 3;
    CHECK(base_int128_eq(x, 0x0800000000000000, 0x1000));

    x.set(0x8000000000000000, 0x8003);
    x >>= 63;
    CHECK(base_int128_eq(x, 1, 0));
    x.set(0x4000000000000000, 0x8003);
    x >>= 63;
    CHECK(base_int128_eq(x, 0, 0x8000000000000000));

    x.set(0x8000000000000000, 0x8003);
    x >>= 64;
    CHECK(base_int128_eq(x, 0, 0x8000000000000000));
    x.set(0x4000000000000000, 0x8003);
    x >>= 64;
    CHECK(base_int128_eq(x, 0, 0x4000000000000000));

    x.set(0x8000000000000000, 0x8003);
    x >>= 65;
    CHECK(base_int128_eq(x, 0, 0x4000000000000000));
    x.set(0x4000000000000000, 0x8003);
    x >>= 65;
    CHECK(base_int128_eq(x, 0, 0x2000000000000000));

    x.set(0x8000000000000000, 0x8003);
    x >>= 127;
    CHECK(base_int128_eq(x, 0, 1));
    x.set(0x4000000000000000, 0x8003);
    x >>= 127;
    CHECK(base_int128_eq(x, 0, 0));
    x.set(0x4000000000000000, 0x8003);
    x >>= 126;
    CHECK(base_int128_eq(x, 0, 1));

    x.set(0x8000000000000000, 0x8003);
    x >>= 128;
    CHECK(base_int128_eq(x, 0, 0));
    x.set(0x4000000000000000, 0x8003);
    x >>= 128;
    CHECK(base_int128_eq(x, 0, 0));

    x.set(0x8000000000000000, 0x8003);
    x >>= 129;
    CHECK(base_int128_eq(x, 0, 0));
    x.set(0x4000000000000000, 0x8003);
    x >>= 129;
    CHECK(base_int128_eq(x, 0, 0));

    x.set(0x8000000000000000, 0x8003);
    x >>= -1;
    CHECK(base_int128_eq(x, 0, 0));
    x.set(0x4000000000000000, 0x8003);
    x >>= -1;
    CHECK(base_int128_eq(x, 0, 0));
}



TEST_CASE("int.h signed arithmetic operators")
{
    omw::int128_t x;

    // unary + -
    x = 123;
    CHECK(base_int128_eq(+x, 0, 123));
    x = -123;
    CHECK(base_int128_eq(+x, UINT64_MAX, -123));
    x = 123;
    CHECK(base_int128_eq(-x, UINT64_MAX, -123));
    x = -123;
    CHECK(base_int128_eq(-x, 0, 123));


    // +
    x.set(0, 0);
    CHECK(base_int128_eq(x + 54, 0, 54));
    CHECK(base_int128_eq(x + -123, UINT64_MAX, 0xFFFFFFFFFFFFFF85));
    CHECK(base_int128_eq(x + INT64_MIN, UINT64_MAX, 0x8000000000000000));
    CHECK(base_int128_eq(x + INT64_MAX, 0, 0x7FFFFFFFFFFFFFFF));
    CHECK(base_int128_eq(x + UINT64_MAX, UINT64_MAX, UINT64_MAX));
    CHECK(base_int128_eq(x + omw::int128_t(0, UINT64_MAX), 0, UINT64_MAX));
    CHECK(base_int128_eq(x + 0xFFFFFFFFFFFFFFFD, UINT64_MAX, -3));
    CHECK(base_int128_eq(x + omw::int128_t(0, 0xFFFFFFFFFFFFFFFD), 0, 0xFFFFFFFFFFFFFFFD));

    x.set(0, 5);
    CHECK(base_int128_eq(x + 54, 0, 59));
    CHECK(base_int128_eq(x + -123, UINT64_MAX, 0xFFFFFFFFFFFFFF8A));
    CHECK(base_int128_eq(x + INT64_MIN, UINT64_MAX, 0x8000000000000005));
    CHECK(base_int128_eq(x + INT64_MAX, 0, 0x8000000000000004));
    CHECK(base_int128_eq(x + UINT64_MAX, 0, 4));
    CHECK(base_int128_eq(x + omw::int128_t(0, UINT64_MAX), 1, 4));
    CHECK(base_int128_eq(x + 0xFFFFFFFFFFFFFFFD, 0, 2));
    CHECK(base_int128_eq(x + omw::int128_t(0, 0xFFFFFFFFFFFFFFFD), 1, 2));


    // -
    x.set(0, 0);
    CHECK(base_int128_eq(x - 54, UINT64_MAX, -54));
    CHECK(base_int128_eq(x - -123, 0, 123));
    CHECK(base_int128_eq(x - INT64_MIN, 0, 0x8000000000000000));
    CHECK(base_int128_eq(x - INT64_MAX, UINT64_MAX, 0x8000000000000001));
    CHECK(base_int128_eq(x - UINT64_MAX, 0, 1));
    CHECK(base_int128_eq(x - omw::int128_t(0, UINT64_MAX), UINT64_MAX, 1));
    CHECK(base_int128_eq(x - 0xFFFFFFFFFFFFFFFD, 0, 3));
    CHECK(base_int128_eq(x - omw::int128_t(0, 0xFFFFFFFFFFFFFFFD), UINT64_MAX, 3));

    x.set(0, 5);
    CHECK(base_int128_eq(x - 54, UINT64_MAX, -49));
    CHECK(base_int128_eq(x - -123, 0, 128));
    CHECK(base_int128_eq(x - INT64_MIN, 0, 0x8000000000000005));
    CHECK(base_int128_eq(x - INT64_MAX, UINT64_MAX, 0x8000000000000006));
    CHECK(base_int128_eq(x - UINT64_MAX, 0, 6));
    CHECK(base_int128_eq(x - omw::int128_t(0, UINT64_MAX), UINT64_MAX, 6));
    CHECK(base_int128_eq(x - 0xFFFFFFFFFFFFFFFD, 0, 8));
    CHECK(base_int128_eq(x - omw::int128_t(0, 0xFFFFFFFFFFFFFFFD), UINT64_MAX, 8));


    // & | ^
    x.set(0, 0);
    CHECK(base_int128_eq(x | omw::Base_Int128(0xFFFFFFFF5555AAAA, 0x12345678), 0xFFFFFFFF5555AAAA, 0x12345678));

    x.set(0xFFFFFFFF5555AAAA, 0x12345678);
    CHECK(base_int128_eq(x & omw::Base_Int128(0x5555AAAA00FF00FF, 0xFFFF0000FFFF0000), 0x5555AAAA005500AA, 0x12340000));

    x.set(0x5555AAAA005500AA, 0x12340000);
    CHECK(base_int128_eq(x ^ omw::Base_Int128(0x55AA00FF0AAF055F, 0x987600009999ABCD), 0x00FFAA550AFA05F5, 0x987600008BADABCD));


    // <<
    x.set(0x1234567800000000, 0x12345678);
    CHECK(base_int128_eq(x << 0, 0x1234567800000000, 0x12345678));

    x.set(0, 1);
    CHECK(base_int128_eq(x << 3, 0, 8));

    x.set(1, 0);
    CHECK(base_int128_eq(x << 3, 8, 0));

    x.set(0, 0xA5);
    CHECK(base_int128_eq(x << 32, 0, 0xA500000000));

    x.set(0, 1);
    CHECK(base_int128_eq(x << 65, 2, 0));

    x.set(UINT64_MAX, UINT64_MAX);
    CHECK(base_int128_eq(x << 127, 0x8000000000000000, 0));

    x.set(0, 1);
    CHECK(base_int128_eq(x << 128, 0, 0));

    x.set(UINT64_MAX, UINT64_MAX);
    CHECK(base_int128_eq(x << 128, 0, 0));

    x.set(0, 0x12345678);
    CHECK(base_int128_eq(x << 32, 0, 0x1234567800000000));

    x.set(0x1234567800000000, 0x12345678);
    CHECK(base_int128_eq(x << 48, 0x1234, 0x5678000000000000));


    // >>
    x.set(0x1234567800000000, 0x12345678);
    CHECK(base_int128_eq(x >> 0, 0x1234567800000000, 0x12345678));

    x.set(0x8000000000000000, 0);
    CHECK(base_int128_eq(x >> 3, 0xF000000000000000, 0));

    x.set(0, 0x8000000000000000);
    CHECK(base_int128_eq(x >> 3, 0, 0x1000000000000000));

    x.set(0, 0xA500000000);
    CHECK(base_int128_eq(x >> 32, 0, 0xA5));

    x.set(0x8000000000000000, 1);
    CHECK(base_int128_eq(x >> 65, UINT64_MAX, 0xC000000000000000));

    x.set(UINT64_MAX, UINT64_MAX);
    CHECK(base_int128_eq(x >> 127, UINT64_MAX, UINT64_MAX));

    x.set(0x8000000000000000, 0);
    CHECK(base_int128_eq(x >> 128, UINT64_MAX, UINT64_MAX));

    x.set(UINT64_MAX, UINT64_MAX);
    CHECK(base_int128_eq(x >> 128, UINT64_MAX, UINT64_MAX));

    x.set(0x1234567800000000, 0);
    CHECK(base_int128_eq(x >> 32, 0x12345678, 0));

    x.set(0x1234567800000000, 123456);
    CHECK(base_int128_eq(x >> 48, 0x1234, 0x5678000000000000));
}



TEST_CASE("int.h unsigned arithmetic operators")
{
    omw::uint128_t x;

    // unary + -
    x = 123;
    CHECK(base_int128_eq(+x, 0, 123));
    x = -123;
    CHECK(base_int128_eq(+x, UINT64_MAX, -123));
    x = 123;
    CHECK(base_int128_eq(-x, UINT64_MAX, -123));
    x = -123;
    CHECK(base_int128_eq(-x, 0, 123));


    // +
    x.set(0, 0);
    CHECK(base_int128_eq(x + 54, 0, 54));
    CHECK(base_int128_eq(x + -123, UINT64_MAX, 0xFFFFFFFFFFFFFF85));
    CHECK(base_int128_eq(x + INT64_MIN, UINT64_MAX, 0x8000000000000000));
    CHECK(base_int128_eq(x + INT64_MAX, 0, 0x7FFFFFFFFFFFFFFF));
    CHECK(base_int128_eq(x + UINT64_MAX, UINT64_MAX, UINT64_MAX));
    CHECK(base_int128_eq(x + omw::uint128_t(0, UINT64_MAX), 0, UINT64_MAX));
    CHECK(base_int128_eq(x + 0xFFFFFFFFFFFFFFFD, UINT64_MAX, -3));
    CHECK(base_int128_eq(x + omw::uint128_t(0, 0xFFFFFFFFFFFFFFFD), 0, 0xFFFFFFFFFFFFFFFD));

    x.set(0, 5);
    CHECK(base_int128_eq(x + 54, 0, 59));
    CHECK(base_int128_eq(x + -123, UINT64_MAX, 0xFFFFFFFFFFFFFF8A));
    CHECK(base_int128_eq(x + INT64_MIN, UINT64_MAX, 0x8000000000000005));
    CHECK(base_int128_eq(x + INT64_MAX, 0, 0x8000000000000004));
    CHECK(base_int128_eq(x + UINT64_MAX, 0, 4));
    CHECK(base_int128_eq(x + omw::uint128_t(0, UINT64_MAX), 1, 4));
    CHECK(base_int128_eq(x + 0xFFFFFFFFFFFFFFFD, 0, 2));
    CHECK(base_int128_eq(x + omw::uint128_t(0, 0xFFFFFFFFFFFFFFFD), 1, 2));


    // -
    x.set(0, 0);
    CHECK(base_int128_eq(x - 54, UINT64_MAX, -54));
    CHECK(base_int128_eq(x - -123, 0, 123));
    CHECK(base_int128_eq(x - INT64_MIN, 0, 0x8000000000000000));
    CHECK(base_int128_eq(x - INT64_MAX, UINT64_MAX, 0x8000000000000001));
    CHECK(base_int128_eq(x - UINT64_MAX, 0, 1));
    CHECK(base_int128_eq(x - omw::uint128_t(0, UINT64_MAX), UINT64_MAX, 1));
    CHECK(base_int128_eq(x - 0xFFFFFFFFFFFFFFFD, 0, 3));
    CHECK(base_int128_eq(x - omw::uint128_t(0, 0xFFFFFFFFFFFFFFFD), UINT64_MAX, 3));

    x.set(0, 5);
    CHECK(base_int128_eq(x - 54, UINT64_MAX, -49));
    CHECK(base_int128_eq(x - -123, 0, 128));
    CHECK(base_int128_eq(x - INT64_MIN, 0, 0x8000000000000005));
    CHECK(base_int128_eq(x - INT64_MAX, UINT64_MAX, 0x8000000000000006));
    CHECK(base_int128_eq(x - UINT64_MAX, 0, 6));
    CHECK(base_int128_eq(x - omw::uint128_t(0, UINT64_MAX), UINT64_MAX, 6));
    CHECK(base_int128_eq(x - 0xFFFFFFFFFFFFFFFD, 0, 8));
    CHECK(base_int128_eq(x - omw::uint128_t(0, 0xFFFFFFFFFFFFFFFD), UINT64_MAX, 8));


    // & | ^
    x.set(0, 0);
    CHECK(base_int128_eq(x | omw::Base_Int128(0xFFFFFFFF5555AAAA, 0x12345678), 0xFFFFFFFF5555AAAA, 0x12345678));

    x.set(0xFFFFFFFF5555AAAA, 0x12345678);
    CHECK(base_int128_eq(x & omw::Base_Int128(0x5555AAAA00FF00FF, 0xFFFF0000FFFF0000), 0x5555AAAA005500AA, 0x12340000));

    x.set(0x5555AAAA005500AA, 0x12340000);
    CHECK(base_int128_eq(x ^ omw::Base_Int128(0x55AA00FF0AAF055F, 0x987600009999ABCD), 0x00FFAA550AFA05F5, 0x987600008BADABCD));


    // <<
    x.set(0x1234567800000000, 0x12345678);
    CHECK(base_int128_eq(x << 0, 0x1234567800000000, 0x12345678));

    x.set(0, 1);
    CHECK(base_int128_eq(x << 3, 0, 8));

    x.set(1, 0);
    CHECK(base_int128_eq(x << 3, 8, 0));

    x.set(0, 0xA5);
    CHECK(base_int128_eq(x << 32, 0, 0xA500000000));

    x.set(0, 1);
    CHECK(base_int128_eq(x << 65, 2, 0));

    x.set(UINT64_MAX, UINT64_MAX);
    CHECK(base_int128_eq(x << 127, 0x8000000000000000, 0));

    x.set(0, 1);
    CHECK(base_int128_eq(x << 128, 0, 0));

    x.set(UINT64_MAX, UINT64_MAX);
    CHECK(base_int128_eq(x << 128, 0, 0));

    x.set(0, 0x12345678);
    CHECK(base_int128_eq(x << 32, 0, 0x1234567800000000));

    x.set(0x1234567800000000, 0x12345678);
    CHECK(base_int128_eq(x << 48, 0x1234, 0x5678000000000000));


    // >>
    x.set(0x1234567800000000, 0x12345678);
    CHECK(base_int128_eq(x >> 0, 0x1234567800000000, 0x12345678));

    x.set(0x8000000000000000, 0);
    CHECK(base_int128_eq(x >> 3, 0x1000000000000000, 0));

    x.set(0, 0x8000000000000000);
    CHECK(base_int128_eq(x >> 3, 0, 0x1000000000000000));

    x.set(0, 0xA500000000);
    CHECK(base_int128_eq(x >> 32, 0, 0xA5));

    x.set(0x8000000000000000, 1);
    CHECK(base_int128_eq(x >> 65, 0, 0x4000000000000000));

    x.set(UINT64_MAX, UINT64_MAX);
    CHECK(base_int128_eq(x >> 127, 0, 1));

    x.set(0x8000000000000000, 0);
    CHECK(base_int128_eq(x >> 128, 0, 0));

    x.set(UINT64_MAX, UINT64_MAX);
    CHECK(base_int128_eq(x >> 128, 0, 0));

    x.set(0x1234567800000000, 0);
    CHECK(base_int128_eq(x >> 32, 0x12345678, 0));

    x.set(0x1234567800000000, 123456);
    CHECK(base_int128_eq(x >> 48, 0x1234, 0x5678000000000000));
}

TEST_CASE("int.h compairson operators signed")
{
    omw::int128_t a, b;

    a.sets(-123);
    b.sets(-123);
    CHECK(a == b);
    CHECK_FALSE(a != b);
    CHECK_FALSE(a < b);
    CHECK_FALSE(a > b);
    CHECK(a <= b);
    CHECK(a >= b);

    a.sets(1);
    b.sets(0);
    CHECK_FALSE(a == b);
    CHECK(a != b);
    CHECK_FALSE(a < b);
    CHECK(a > b);
    CHECK_FALSE(a <= b);
    CHECK(a >= b);

    a.set(UINT64_MAX, 0);
    b.sets(-1);
    CHECK_FALSE(a == b);
    CHECK(a != b);
    CHECK(a < b);
    CHECK_FALSE(a > b);
    CHECK(a <= b);
    CHECK_FALSE(a >= b);

    a.set(UINT64_MAX, 123);
    b.set(UINT64_MAX, 122);
    CHECK_FALSE(a == b);
    CHECK(a != b);
    CHECK_FALSE(a < b);
    CHECK(a > b);
    CHECK_FALSE(a <= b);
    CHECK(a >= b);

    a.set(0x7000000000000000, 123);
    b.set(0x7000000000000000, 122);
    CHECK_FALSE(a == b);
    CHECK(a != b);
    CHECK_FALSE(a < b);
    CHECK(a > b);
    CHECK_FALSE(a <= b);
    CHECK(a >= b);

    a.set(0xF000000000000000, 123);
    b.set(0xF000000000000000, 122);
    CHECK_FALSE(a == b);
    CHECK(a != b);
    CHECK_FALSE(a < b);
    CHECK(a > b);
    CHECK_FALSE(a <= b);
    CHECK(a >= b);

    a.set(0, UINT64_MAX);
    b.set(1, 0);
    CHECK_FALSE(a == b);
    CHECK(a != b);
    CHECK(a < b);
    CHECK_FALSE(a > b);
    CHECK(a <= b);
    CHECK_FALSE(a >= b);
}

TEST_CASE("int.h compairson operators unsigned")
{
    omw::uint128_t a, b;

    a.setu(123);
    b.setu(123);
    CHECK(a == b);
    CHECK_FALSE(a != b);
    CHECK_FALSE(a < b);
    CHECK_FALSE(a > b);
    CHECK(a <= b);
    CHECK(a >= b);

    a.sets(1);
    b.sets(0);
    CHECK_FALSE(a == b);
    CHECK(a != b);
    CHECK_FALSE(a < b);
    CHECK(a > b);
    CHECK_FALSE(a <= b);
    CHECK(a >= b);

    a.set(UINT64_MAX, 0);
    b.sets(-1);
    CHECK_FALSE(a == b);
    CHECK(a != b);
    CHECK(a < b);
    CHECK_FALSE(a > b);
    CHECK(a <= b);
    CHECK_FALSE(a >= b);

    a.set(UINT64_MAX, 123);
    b.set(UINT64_MAX, 122);
    CHECK_FALSE(a == b);
    CHECK(a != b);
    CHECK_FALSE(a < b);
    CHECK(a > b);
    CHECK_FALSE(a <= b);
    CHECK(a >= b);

    a.set(0x7000000000000000, 123);
    b.set(0x7000000000000000, 122);
    CHECK_FALSE(a == b);
    CHECK(a != b);
    CHECK_FALSE(a < b);
    CHECK(a > b);
    CHECK_FALSE(a <= b);
    CHECK(a >= b);

    a.set(0xF000000000000000, 123);
    b.set(0xF000000000000000, 122);
    CHECK_FALSE(a == b);
    CHECK(a != b);
    CHECK_FALSE(a < b);
    CHECK(a > b);
    CHECK_FALSE(a <= b);
    CHECK(a >= b);

    a.set(0, UINT64_MAX);
    b.set(1, 0);
    CHECK_FALSE(a == b);
    CHECK(a != b);
    CHECK(a < b);
    CHECK_FALSE(a > b);
    CHECK(a <= b);
    CHECK_FALSE(a >= b);
}

TEST_CASE("int.h compairson operators mixed")
{
    omw::int128_t s;
    omw::uint128_t u;

    CHECK(s == u);
    CHECK(u == s);
    CHECK_FALSE(s != u);
    CHECK_FALSE(u != s);
    CHECK_FALSE(s < u);
    CHECK_FALSE(u < s);
    CHECK_FALSE(s > u);
    CHECK_FALSE(u > s);
    CHECK(s <= u);
    CHECK(u <= s);
    CHECK(s >= u);
    CHECK(u >= s);

    s = 123;
    u = 123;
    CHECK(s == u);
    CHECK(u == s);
    CHECK_FALSE(s != u);
    CHECK_FALSE(u != s);
    CHECK_FALSE(s < u);
    CHECK_FALSE(u < s);
    CHECK_FALSE(s > u);
    CHECK_FALSE(u > s);
    CHECK(s <= u);
    CHECK(u <= s);
    CHECK(s >= u);
    CHECK(u >= s);

    s = 54;
    u = 123;
    CHECK_FALSE(s == u);
    CHECK_FALSE(u == s);
    CHECK(s != u);
    CHECK(u != s);
    CHECK(s < u);
    CHECK_FALSE(u < s);
    CHECK_FALSE(s > u);
    CHECK(u > s);
    CHECK(s <= u);
    CHECK_FALSE(u <= s);
    CHECK_FALSE(s >= u);
    CHECK(u >= s);

    s = 123;
    u = 54;
    CHECK_FALSE(s == u);
    CHECK_FALSE(u == s);
    CHECK(s != u);
    CHECK(u != s);
    CHECK_FALSE(s < u);
    CHECK(u < s);
    CHECK(s > u);
    CHECK_FALSE(u > s);
    CHECK_FALSE(s <= u);
    CHECK(u <= s);
    CHECK(s >= u);
    CHECK_FALSE(u >= s);

    s = -1;
    u = 123;
    CHECK_FALSE(s == u);
    CHECK_FALSE(u == s);
    CHECK(s != u);
    CHECK(u != s);
    CHECK(s < u);
    CHECK_FALSE(u < s);
    CHECK_FALSE(s > u);
    CHECK(u > s);
    CHECK(s <= u);
    CHECK_FALSE(u <= s);
    CHECK_FALSE(s >= u);
    CHECK(u >= s);

    s = 123;
    u.set(INT64_MAX, 0);
    CHECK_FALSE(s == u);
    CHECK_FALSE(u == s);
    CHECK(s != u);
    CHECK(u != s);
    CHECK(s < u);
    CHECK_FALSE(u < s);
    CHECK_FALSE(s > u);
    CHECK(u > s);
    CHECK(s <= u);
    CHECK_FALSE(u <= s);
    CHECK_FALSE(s >= u);
    CHECK(u >= s);
}
