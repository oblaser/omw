/*
author          Oliver Blaser
date            11.12.2021
copyright       MIT - Copyright (c) 2021 Oliver Blaser
*/

#ifndef TEST_OMW_MATH_H
#define TEST_OMW_MATH_H

#include <string>
#include <vector>

#include "catch2/catch.hpp"
#include "testUtil.h"

#include <omw/math.h>



TEST_CASE("math.h max() min()")
{
    constexpr int a = 3;
    constexpr int b = 1;
    constexpr int c = 8;
    constexpr int d = -6;

    constexpr int max2 = omw::max(a, b);
    constexpr int max3 = omw::max(a, b, c);
    constexpr int max4 = omw::max(a, b, c, d);

    constexpr int min2 = omw::min(a, b);
    constexpr int min3 = omw::min(a, b, c);
    constexpr int min4 = omw::min(a, b, c, d);

    CHECK(max2 == 3);
    CHECK(max3 == 8);
    CHECK(max4 == 8);

    CHECK(min2 == 1);
    CHECK(min3 == 1);
    CHECK(min4 == -6);
}

TEST_CASE("math.h max() min() int128_t")
{
    const omw::int128_t a = 3;
    const omw::int128_t b = 1;
    const omw::int128_t c = 8;
    const omw::int128_t d = -6;

    const omw::int128_t max2 = omw::max(a, b);
    const omw::int128_t max3 = omw::max(a, b, c);
    const omw::int128_t max4 = omw::max(a, b, c, d);

    const omw::int128_t min2 = omw::min(a, b);
    const omw::int128_t min3 = omw::min(a, b, c);
    const omw::int128_t min4 = omw::min(a, b, c, d);

    CHECK(max2 == omw::int128_t(0, 3));
    CHECK(max3 == omw::int128_t(0, 8));
    CHECK(max4 == omw::int128_t(0, 8));

    CHECK(min2 == omw::int128_t(0, 1));
    CHECK(min3 == omw::int128_t(0, 1));
    CHECK(min4 == omw::int128_t(0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFA));
}

TEST_CASE("math.h max() min() uint128_t")
{
    const omw::uint128_t a = 3;
    const omw::uint128_t b = 1;
    const omw::uint128_t c = 8;
    const omw::uint128_t d = -6;

    const omw::uint128_t max2 = omw::max(a, b);
    const omw::uint128_t max3 = omw::max(a, b, c);
    const omw::uint128_t max4 = omw::max(a, b, c, d);

    const omw::uint128_t min2 = omw::min(a, b);
    const omw::uint128_t min3 = omw::min(a, b, c);
    const omw::uint128_t min4 = omw::min(a, b, c, d);

    CHECK(max2 == omw::uint128_t(0, 3));
    CHECK(max3 == omw::uint128_t(0, 8));
    CHECK(max4 == omw::uint128_t(0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFA));

    CHECK(min2 == omw::uint128_t(0, 1));
    CHECK(min3 == omw::uint128_t(0, 1));
    CHECK(min4 == omw::uint128_t(0, 1));
}

TEST_CASE("math.h sign() sgn()")
{
}



#endif // TEST_OMW_MATH_H
