/*
author          Oliver Blaser
date            17.12.2021
copyright       MIT - Copyright (c) 2021 Oliver Blaser
*/

#ifndef TEST_OMW_OMWINT_H
#define TEST_OMW_OMWINT_H

#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

#include "catch2/catch.hpp"
#include "testUtil.h"

#include <omw/int.h>


namespace
{
    bool eq(const omw::Base_Int128& val, uint64_t h, uint64_t l) { return ((val.hi() == h) && (val.lo() == l)); }
    bool eqs(const omw::Base_Int128& val, int64_t h, uint64_t l) { return ((val.his() == h) && (val.lo() == l)); }
}


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

    CHECK(eq(OMW_128BIT_ALL, UINT64_MAX, UINT64_MAX));
    CHECK(eq(OMW_128BIT_LSB, 0, 1));
    CHECK(eqs(OMW_128BIT_MSB, INT64_MIN, 0));

    CHECK(eqs(OMW_INT128_MIN, INT64_MIN, 0));
    CHECK(eq(OMW_INT128_MAX, INT64_MAX, UINT64_MAX));
    CHECK(eq(OMW_UINT128_MAX, UINT64_MAX, UINT64_MAX));
}



TEST_CASE("int.h omw::Base_Int128 ctor")
{
    CHECK(eq(omw::Base_Int128(), 0, 0));

    CHECK(eq(omw::Base_Int128(0), 0, 0));
    CHECK(eq(omw::Base_Int128(1), 0, 1));
    CHECK(eq(omw::Base_Int128(123), 0, 123));
    CHECK(eq(omw::Base_Int128(-123), UINT64_MAX, -123));
    CHECK(eq(omw::Base_Int128(-1), UINT64_MAX, UINT64_MAX));
    CHECK(eq(omw::Base_Int128(INT32_MIN), UINT64_MAX, INT32_MIN));
    CHECK(eq(omw::Base_Int128(INT32_MAX), 0, INT32_MAX));
    CHECK(eq(omw::Base_Int128(UINT32_MAX), 0, UINT32_MAX));
    CHECK(eq(omw::Base_Int128(UINT64_MAX), UINT64_MAX, UINT64_MAX));
    CHECK(eq(omw::Base_Int128(INT64_MAX), 0, INT64_MAX));
    CHECK(eq(omw::Base_Int128(INT64_MIN), UINT64_MAX, INT64_MIN));

    CHECK(eq(omw::Base_Int128(0, 0), 0, 0));
    CHECK(eq(omw::Base_Int128(0x0123456789abcdef, 0xa0b1c2d3e4f56789), 0x0123456789abcdef, 0xa0b1c2d3e4f56789));
    CHECK(eq(omw::Base_Int128(0x1234567890abcdef, 0xa0b1c2d3e4f56789), 0x1234567890abcdef, 0xa0b1c2d3e4f56789));
    CHECK(eq(omw::Base_Int128(0xa0b1c2d3e4f56789, 0x1234567890abcdef), 0xa0b1c2d3e4f56789, 0x1234567890abcdef));

    CHECK(eq(omw::Base_Int128(0, 0, 0, 0), 0, 0));
    CHECK(eq(omw::Base_Int128(0x01234567, 0x12345678, 0xABCDEF01, 0x98765432), 0x0123456712345678, 0xABCDEF0198765432));
    CHECK(eq(omw::Base_Int128(0xABCDEF01, 0x12345678, 0x01234567, 0x98765432), 0xABCDEF0112345678, 0x0123456798765432));
    CHECK(eq(omw::Base_Int128(0x98765432, 0x12345678, 0xABCDEF01, 0x01234567), 0x9876543212345678, 0xABCDEF0101234567));
}

TEST_CASE("int.h omw::Base_Int128 set")
{
    omw::Base_Int128 x;
    CHECK(eq(x, 0, 0));



    x.set(0, 0);
    CHECK(eq(x, 0, 0));

    x.set(0x0123456789abcdef, 0xa0b1c2d3e4f56789);
    CHECK(eq(x, 0x0123456789abcdef, 0xa0b1c2d3e4f56789));

    x.set(0x1234567890abcdef, 0xa0b1c2d3e4f56789);
    CHECK(eq(x, 0x1234567890abcdef, 0xa0b1c2d3e4f56789));

    x.set(0xa0b1c2d3e4f56789, 0x1234567890abcdef);
    CHECK(eq(x, 0xa0b1c2d3e4f56789, 0x1234567890abcdef));



    x.set(0, 0, 0, 0);
    CHECK(eq(x, 0, 0));

    x.set(0x01234567, 0x12345678, 0xABCDEF01, 0x98765432);
    CHECK(eq(x, 0x0123456712345678, 0xABCDEF0198765432));

    x.set(0xABCDEF01, 0x12345678, 0x01234567, 0x98765432);
    CHECK(eq(x, 0xABCDEF0112345678, 0x0123456798765432));

    x.set(0x98765432, 0x12345678, 0xABCDEF01, 0x01234567);
    CHECK(eq(x, 0x9876543212345678, 0xABCDEF0101234567));
}

TEST_CASE("int.h omw::Base_Int128 sets")
{
    omw::Base_Int128 x;
    CHECK(eq(x, 0, 0));



    x.sets(0);
    CHECK(eq(x, 0, 0));

    x.sets(123);
    CHECK(eq(x, 0, 123));

    x.sets(-1);
    CHECK(eq(x, UINT64_MAX, UINT64_MAX));

    x.sets(-123);
    CHECK(eq(x, UINT64_MAX, 0xFFFFFFFFFFFFFF85));

    x.sets(INT32_MIN);
    CHECK(eq(x, UINT64_MAX, 0xFFFFFFFF80000000));

    x.sets(INT32_MAX);
    CHECK(eq(x, 0, 0x07FFFFFFF));

    x.sets(UINT32_MAX);
    CHECK(eq(x, 0, UINT32_MAX));

    x.sets(INT64_MIN);
    CHECK(eq(x, UINT64_MAX, 0x8000000000000000));

    x.sets(INT64_MAX);
    CHECK(eq(x, 0, 0x7FFFFFFFFFFFFFFF));

    x.sets(UINT64_MAX);
    CHECK(eq(x, UINT64_MAX, UINT64_MAX));



    x.sets(1, 0);
    CHECK(eq(x, 1, 0));

    x.sets(0x0123456789abcdef, 0xa0b1c2d3e4f56789);
    CHECK(eq(x, 0x0123456789abcdef, 0xa0b1c2d3e4f56789));

    x.sets(0x1234567890abcdef, 0xa0b1c2d3e4f56789);
    CHECK(eq(x, 0x1234567890abcdef, 0xa0b1c2d3e4f56789));

    x.sets(0xa0b1c2d3e4f56789, 0x1234567890abcdef);
    CHECK(eq(x, 0xa0b1c2d3e4f56789, 0x1234567890abcdef));



    x.sets(0, 0, 0, 0);
    CHECK(eq(x, 0, 0));

    x.sets(0x01234567, 0x12345678, 0xABCDEF01, 0x98765432);
    CHECK(eq(x, 0x0123456712345678, 0xABCDEF0198765432));

    x.sets(0xABCDEF01, 0x12345678, 0x01234567, 0x98765432);
    CHECK(eq(x, 0xABCDEF0112345678, 0x0123456798765432));

    x.sets(0x98765432, 0x12345678, 0xABCDEF01, 0x01234567);
    CHECK(eq(x, 0x9876543212345678, 0xABCDEF0101234567));



    const uint8_t data[20] = { 0x78, 0x90, 0x34, 0xAB, 0xCD, 0x56, 0xEF, 0x12, 0x49, 0x21, 0x87, 0x37, 0x94, 0x54, 0xBE, 0xFA, 123, 54, 87, 10 };

    x.set(123, 456);
    x.sets(nullptr, 0);
    CHECK(eq(x, 123, 456));
    x.sets(nullptr, 2);
    CHECK(eq(x, 123, 456));
    x.sets(data, 0);
    CHECK(eq(x, 123, 456));

    x.sets(data, 2);
    CHECK(eq(x, 0, 0x7890));
    x.sets(data, 16);
    CHECK(eq(x, 0x789034ABCD56EF12, 0x492187379454BEFA));
    x.sets(data + 1, 16);
    CHECK(eq(x, 0x9034ABCD56EF1249, 0x2187379454BEFA7B));
    x.sets(data + 5, 5);
    CHECK(eq(x, 0, 0x56EF124921));

    x.sets(data + 1, 15);
    CHECK(eq(x, 0xFF9034ABCD56EF12, 0x492187379454BEFA));
    x.sets(data + 1, 4);
    CHECK(eq(x, UINT64_MAX, 0xFFFFFFFF9034ABCD));

    x.set(123, 456);
    try { x.sets(data, 17); }
    catch (std::overflow_error& ex) { const char* const msg = ex.what(); CHECK(1 == 1); }
    catch (...) { CHECK(1 != 1); }
    CHECK(eq(x, 123, 456));
    try { x.sets(data, -1); }
    catch (std::overflow_error& ex) { const char* const msg = ex.what(); CHECK(1 == 1); }
    catch (...) { CHECK(1 != 1); }
    CHECK(eq(x, 123, 456));
}

TEST_CASE("int.h omw::Base_Int128 setu")
{
    omw::Base_Int128 x;
    CHECK(eq(x, 0, 0));



    x.setu(0);
    CHECK(eq(x, 0, 0));

    x.setu(123);
    CHECK(eq(x, 0, 123));

    x.setu(-1);
    CHECK(eq(x, 0, UINT64_MAX));

    x.setu(-123);
    CHECK(eq(x, 0, 0xFFFFFFFFFFFFFF85));

    x.setu(INT32_MIN);
    CHECK(eq(x, 0, 0xFFFFFFFF80000000));

    x.setu(0x80000000);
    CHECK(eq(x, 0, 0x80000000));

    x.setu(INT32_MAX);
    CHECK(eq(x, 0, 0x7FFFFFFF));

    x.setu(UINT32_MAX);
    CHECK(eq(x, 0, 0xFFFFFFFF));

    x.setu(INT64_MIN);
    CHECK(eq(x, 0, 0x8000000000000000));

    x.setu(INT64_MAX);
    CHECK(eq(x, 0, 0x7FFFFFFFFFFFFFFF));

    x.setu(UINT64_MAX);
    CHECK(eq(x, 0, UINT64_MAX));



    const uint8_t data[20] = { 0x78, 0x90, 0x34, 0xAB, 0xCD, 0x56, 0xEF, 0x12, 0x49, 0x21, 0x87, 0x37, 0x94, 0x54, 0xBE, 0xFA, 123, 54, 87, 10 };

    x.set(123, 456);
    x.setu(nullptr, 0);
    CHECK(eq(x, 123, 456));
    x.setu(nullptr, 2);
    CHECK(eq(x, 123, 456));
    x.setu(data, 0);
    CHECK(eq(x, 123, 456));

    x.setu(data, 2);
    CHECK(eq(x, 0, 0x7890));
    x.setu(data, 16);
    CHECK(eq(x, 0x789034ABCD56EF12, 0x492187379454BEFA));
    x.setu(data + 1, 16);
    CHECK(eq(x, 0x9034ABCD56EF1249, 0x2187379454BEFA7B));
    x.setu(data + 5, 5);
    CHECK(eq(x, 0, 0x56EF124921));

    x.setu(data + 1, 15);
    CHECK(eq(x, 0x009034ABCD56EF12, 0x492187379454BEFA));
    x.setu(data + 1, 4);
    CHECK(eq(x, 0, 0x9034ABCD));

    x.set(123, 456);
    try { x.setu(data, 17); }
    catch (std::overflow_error& ex) { const char* const msg = ex.what(); CHECK(1 == 1); }
    catch (...) { CHECK(1 != 1); }
    CHECK(eq(x, 123, 456));
    try { x.setu(data, -1); }
    catch (std::overflow_error& ex) { const char* const msg = ex.what(); CHECK(1 == 1); }
    catch (...) { CHECK(1 != 1); }
    CHECK(eq(x, 123, 456));
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
    x += omw::Base_Int128(0, 54);
    CHECK(eq(x, 0, 54));
    x -= omw::Base_Int128(0, 47);
    CHECK(eq(x, 0, 7));
    x += omw::Base_Int128(0, 123);
    CHECK(eq(x, 0, 130));
    x -= omw::Base_Int128(0, 63);
    CHECK(eq(x, 0, 67));

    x.set(0, 0);
    x += omw::Base_Int128(0, 5);
    CHECK(eq(x, 0, 5));
    x -= omw::Base_Int128(0, 8);
    CHECK(eq(x, UINT64_MAX, UINT64_MAX - 2));
    x += omw::Base_Int128(UINT64_MAX, UINT64_MAX);
    CHECK(eq(x, UINT64_MAX, UINT64_MAX - 3));

    x.set(0, UINT64_MAX - 2);
    x += omw::Base_Int128(0, 6);
    CHECK(eq(x, 1, 3));
    x -= omw::Base_Int128(0, UINT64_MAX);
    CHECK(eq(x, 0, 4));
    x -= omw::Base_Int128(UINT64_MAX, UINT64_MAX);
    CHECK(eq(x, 0, 5));


    // &= |= ^=
    x.set(0, 0);
    x |= omw::Base_Int128(0xFFFFFFFF5555AAAA, 0x12345678);
    CHECK(eq(x, 0xFFFFFFFF5555AAAA, 0x12345678));
    x &= omw::Base_Int128(0x5555AAAA00FF00FF, 0xFFFF0000FFFF0000);
    CHECK(eq(x, 0x5555AAAA005500AA, 0x12340000));
    x ^= omw::Base_Int128(0x55AA00FF0AAF055F, 0x987600009999ABCD);
    CHECK(eq(x, 0x00FFAA550AFA05F5, 0x987600008BADABCD));


    // <<=
    x.set(0, 1);
    x <<= 3;
    CHECK(eq(x, 0, 8));
    x.set(1, 0);
    x <<= 3;
    CHECK(eq(x, 8, 0));
    x.set(0, 0xA5);
    x <<= 32;
    CHECK(eq(x, 0, 0xA500000000));
    x.set(0, 1);
    x <<= 65;
    CHECK(eq(x, 2, 0));
    x.set(UINT64_MAX, UINT64_MAX);
    x <<= 127;
    CHECK(eq(x, 0x8000000000000000, 0));
    x.set(0, 1);
    x <<= 128;
    CHECK(eq(x, 0, 0));
    x.set(UINT64_MAX, UINT64_MAX);
    x <<= 128;
    CHECK(eq(x, 0, 0));
    x.set(0, 0x12345678);
    x <<= 32;
    CHECK(eq(x, 0, 0x1234567800000000));
    x.set(0x1234567800000000, 0x12345678);
    x <<= 48;
    CHECK(eq(x, 0x1234, 0x5678000000000000));


    // >>=
    x.set(0x800000000000, 0);
    x >>= 3;
    CHECK(eq(x, 0x100000000000, 0));
    x.set(0, 0x800000000000);
    x >>= 3;
    CHECK(eq(x, 0, 0x100000000000));
    x.set(0, 0xA500000000);
    x >>= 32;
    CHECK(eq(x, 0, 0xA5));
    x.set(0x800000000000, 1);
    x >>= 65;
    CHECK(eq(x, 0, 0x400000000000));
    x.set(UINT64_MAX, UINT64_MAX);
    x >>= 127;
    CHECK(eq(x, 0, 1));
    x.set(0x800000000000, 0);
    x >>= 128;
    CHECK(eq(x, 0, 0));
    x.set(UINT64_MAX, UINT64_MAX);
    x >>= 128;
    CHECK(eq(x, 0, 0));
    x.set(0x1234567800000000, 0);
    x >>= 32;
    CHECK(eq(x, 0x12345678, 0));
    x.set(0x1234567800000000, 123456);
    x >>= 48;
    CHECK(eq(x, 0x1234, 0x5678000000000000));


    // a++
    x.set(0, 0xFFFFFFFFFFFFFFFD);
    CHECK(eq(x++, 0, 0xFFFFFFFFFFFFFFFD));
    CHECK(eq(x++, 0, 0xFFFFFFFFFFFFFFFE));
    CHECK(eq(x++, 0, 0xFFFFFFFFFFFFFFFF));
    CHECK(eq(x++, 1, 0));
    CHECK(eq(x, 1, 1));

    x.set(0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFD);
    CHECK(eq(x++, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFD));
    CHECK(eq(x++, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFE));
    CHECK(eq(x++, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF));
    CHECK(eq(x++, 0, 0));
    CHECK(eq(x, 0, 1));


    // ++a
    x.set(0, 0xFFFFFFFFFFFFFFFC);
    CHECK(eq(++x, 0, 0xFFFFFFFFFFFFFFFD));
    CHECK(eq(++x, 0, 0xFFFFFFFFFFFFFFFE));
    CHECK(eq(++x, 0, 0xFFFFFFFFFFFFFFFF));
    CHECK(eq(++x, 1, 0));
    CHECK(eq(++x, 1, 1));

    x.set(0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFC);
    CHECK(eq(++x, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFD));
    CHECK(eq(++x, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFE));
    CHECK(eq(++x, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF));
    CHECK(eq(++x, 0, 0));
    CHECK(eq(++x, 0, 1));


    // a--
    x.set(1, 1);
    CHECK(eq(x--, 1, 1));
    CHECK(eq(x--, 1, 0));
    CHECK(eq(x--, 0, 0xFFFFFFFFFFFFFFFF));
    CHECK(eq(x--, 0, 0xFFFFFFFFFFFFFFFE));
    CHECK(eq(x, 0, 0xFFFFFFFFFFFFFFFD));

    x.set(0, 1);
    CHECK(eq(x--, 0, 1));
    CHECK(eq(x--, 0, 0));
    CHECK(eq(x--, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF));
    CHECK(eq(x--, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFE));
    CHECK(eq(x, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFD));


    // --a
    x.set(1, 2);
    CHECK(eq(--x, 1, 1));
    CHECK(eq(--x, 1, 0));
    CHECK(eq(--x, 0, 0xFFFFFFFFFFFFFFFF));
    CHECK(eq(--x, 0, 0xFFFFFFFFFFFFFFFE));
    CHECK(eq(--x, 0, 0xFFFFFFFFFFFFFFFD));

    x.set(0, 2);
    CHECK(eq(--x, 0, 1));
    CHECK(eq(--x, 0, 0));
    CHECK(eq(--x, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF));
    CHECK(eq(--x, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFE));
    CHECK(eq(--x, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFD));
}



TEST_CASE("int.h omw::SignedInt128")
{
}



TEST_CASE("int.h omw::UnsignedInt128")
{
}



TEST_CASE("int.h arithmetic operators")
{
}

TEST_CASE("int.h compairson operators")
{
}



#endif // TEST_OMW_OMWINT_H
