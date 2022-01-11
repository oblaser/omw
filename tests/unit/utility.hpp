/*
author          Oliver Blaser
date            11.01.2022
copyright       MIT - Copyright (c) 2022 Oliver Blaser
*/

#ifndef TEST_OMW_UTIL_H
#define TEST_OMW_UTIL_H

#include <string>
#include <vector>

#include "catch2/catch.hpp"
#include "testUtil.h"

#include <omw/string.h>
#include <omw/utility.h>



#define UTILITY_CHECK_SHIFTLEFTASSIGN_S()   \
omw::shiftLeftAssign(iv, n);                \
CHECK(iv == ir)                             \
// end UTILITY_CHECK_SHIFTLEFTASSIGN_S

#define UTILITY_CHECK_SHIFTLEFTASSIGN_U()   \
omw::shiftLeftAssign(uiv, n);               \
CHECK(uiv == uir)                           \
// end UTILITY_CHECK_SHIFTLEFTASSIGN_U

#define UTILITY_CHECK_SHIFTRIGHTASSIGN_S()  \
omw::shiftRightAssign(iv, n);               \
CHECK(iv == ir)                             \
// end UTILITY_CHECK_SHIFTRIGHTASSIGN_S

#define UTILITY_CHECK_SHIFTRIGHTASSIGN_U()  \
omw::shiftRightAssign(uiv, n);              \
CHECK(uiv == uir)                           \
// end UTILITY_CHECK_SHIFTRIGHTASSIGN_S



TEST_CASE("utility.h shiftLeftAssign() 8-bit")
{
    size_t n;

    int8_t iv;
    int8_t ir;

    n = 0;
    iv = 0x81; ir = 0x81;
    omw::shiftLeftAssign(iv, n);
    CHECK(iv == ir);
    iv = 0x41; ir = 0x41;
    omw::shiftLeftAssign(iv, n);
    CHECK(iv == ir);

    n = 2;
    iv = 0x81; ir = 0x04;
    omw::shiftLeftAssign(iv, n);
    CHECK(iv == ir);
    iv = 0x41; ir = 0x04;
    omw::shiftLeftAssign(iv, n);
    CHECK(iv == ir);

    n = 6;
    iv = 0x81; ir = 0x40;
    omw::shiftLeftAssign(iv, n);
    CHECK(iv == ir);
    iv = 0x41; ir = 0x40;
    omw::shiftLeftAssign(iv, n);
    CHECK(iv == ir);

    n = 7;
    iv = 0x81; ir = 0x80;
    omw::shiftLeftAssign(iv, n);
    CHECK(iv == ir);
    iv = 0x41; ir = 0x80;
    omw::shiftLeftAssign(iv, n);
    CHECK(iv == ir);

    n = 8;
    iv = 0x81; ir = 0x00;
    omw::shiftLeftAssign(iv, n);
    CHECK(iv == ir);
    iv = 0x41; ir = 0x00;
    omw::shiftLeftAssign(iv, n);
    CHECK(iv == ir);

    n = 9;
    iv = 0x81; ir = 0x00;
    omw::shiftLeftAssign(iv, n);
    CHECK(iv == ir);
    iv = 0x41; ir = 0x00;
    omw::shiftLeftAssign(iv, n);
    CHECK(iv == ir);



    uint8_t uiv;
    uint8_t uir;

    n = 0;
    uiv = 0x81; uir = 0x81;
    omw::shiftLeftAssign(uiv, n);
    CHECK(uiv == uir);
    uiv = 0x41; uir = 0x41;
    omw::shiftLeftAssign(uiv, n);
    CHECK(uiv == uir);

    n = 2;
    uiv = 0x81; uir = 0x04;
    omw::shiftLeftAssign(uiv, n);
    CHECK(uiv == uir);
    uiv = 0x41; uir = 0x04;
    omw::shiftLeftAssign(uiv, n);
    CHECK(uiv == uir);

    n = 6;
    uiv = 0x81; uir = 0x40;
    omw::shiftLeftAssign(uiv, n);
    CHECK(uiv == uir);
    uiv = 0x41; uir = 0x40;
    omw::shiftLeftAssign(uiv, n);
    CHECK(uiv == uir);

    n = 7;
    uiv = 0x81; uir = 0x80;
    omw::shiftLeftAssign(uiv, n);
    CHECK(uiv == uir);
    uiv = 0x41; uir = 0x80;
    omw::shiftLeftAssign(uiv, n);
    CHECK(uiv == uir);

    n = 8;
    uiv = 0x81; uir = 0x00;
    omw::shiftLeftAssign(uiv, n);
    CHECK(uiv == uir);
    uiv = 0x41; uir = 0x00;
    omw::shiftLeftAssign(uiv, n);
    CHECK(uiv == uir);

    n = 9;
    uiv = 0x81; uir = 0x00;
    omw::shiftLeftAssign(uiv, n);
    CHECK(uiv == uir);
    uiv = 0x41; uir = 0x00;
    omw::shiftLeftAssign(uiv, n);
    CHECK(uiv == uir);
}
TEST_CASE("utility.h shiftLeftAssign() 16-bit")
{
    size_t n;

    int16_t iv;
    int16_t ir;

    n = 0;
    iv = 0x8001; ir = 0x8001;
    omw::shiftLeftAssign(iv, n);
    CHECK(iv == ir);
    iv = 0x4001; ir = 0x4001;
    omw::shiftLeftAssign(iv, n);
    CHECK(iv == ir);

    n = 2;
    iv = 0x8001; ir = 0x0004;
    omw::shiftLeftAssign(iv, n);
    CHECK(iv == ir);
    iv = 0x4001; ir = 0x0004;
    omw::shiftLeftAssign(iv, n);
    CHECK(iv == ir);

    n = 14;
    iv = 0x8001; ir = 0x4000;
    omw::shiftLeftAssign(iv, n);
    CHECK(iv == ir);
    iv = 0x4001; ir = 0x4000;
    omw::shiftLeftAssign(iv, n);
    CHECK(iv == ir);

    n = 15;
    iv = 0x8001; ir = 0x8000;
    omw::shiftLeftAssign(iv, n);
    CHECK(iv == ir);
    iv = 0x4001; ir = 0x8000;
    omw::shiftLeftAssign(iv, n);
    CHECK(iv == ir);

    n = 16;
    iv = 0x8001; ir = 0x0000;
    omw::shiftLeftAssign(iv, n);
    CHECK(iv == ir);
    iv = 0x4001; ir = 0x0000;
    omw::shiftLeftAssign(iv, n);
    CHECK(iv == ir);

    n = 17;
    iv = 0x8001; ir = 0x0000;
    omw::shiftLeftAssign(iv, n);
    CHECK(iv == ir);
    iv = 0x4001; ir = 0x0000;
    omw::shiftLeftAssign(iv, n);
    CHECK(iv == ir);



    uint16_t uiv;
    uint16_t uir;

    n = 0;
    uiv = 0x8001; uir = 0x8001;
    omw::shiftLeftAssign(uiv, n);
    CHECK(uiv == uir);
    uiv = 0x4001; uir = 0x4001;
    omw::shiftLeftAssign(uiv, n);
    CHECK(uiv == uir);

    n = 2;
    uiv = 0x8001; uir = 0x0004;
    omw::shiftLeftAssign(uiv, n);
    CHECK(uiv == uir);
    uiv = 0x4001; uir = 0x0004;
    omw::shiftLeftAssign(uiv, n);
    CHECK(uiv == uir);

    n = 14;
    uiv = 0x8001; uir = 0x4000;
    omw::shiftLeftAssign(uiv, n);
    CHECK(uiv == uir);
    uiv = 0x4001; uir = 0x4000;
    omw::shiftLeftAssign(uiv, n);
    CHECK(uiv == uir);

    n = 15;
    uiv = 0x8001; uir = 0x8000;
    omw::shiftLeftAssign(uiv, n);
    CHECK(uiv == uir);
    uiv = 0x4001; uir = 0x8000;
    omw::shiftLeftAssign(uiv, n);
    CHECK(uiv == uir);

    n = 16;
    uiv = 0x8001; uir = 0x0000;
    omw::shiftLeftAssign(uiv, n);
    CHECK(uiv == uir);
    uiv = 0x4001; uir = 0x0000;
    omw::shiftLeftAssign(uiv, n);
    CHECK(uiv == uir);

    n = 17;
    uiv = 0x8001; uir = 0x0000;
    omw::shiftLeftAssign(uiv, n);
    CHECK(uiv == uir);
    uiv = 0x4001; uir = 0x0000;
    omw::shiftLeftAssign(uiv, n);
    CHECK(uiv == uir);
}
TEST_CASE("utility.h shiftLeftAssign() 32-bit")
{
    size_t n;

    int32_t iv;
    int32_t ir;

    n = 0;
    iv = 0x80000001; ir = 0x80000001;
    omw::shiftLeftAssign(iv, n);
    CHECK(iv == ir);
    iv = 0x40000001; ir = 0x40000001;
    omw::shiftLeftAssign(iv, n);
    CHECK(iv == ir);

    n = 2;
    iv = 0x80000001; ir = 0x00000004;
    omw::shiftLeftAssign(iv, n);
    CHECK(iv == ir);
    iv = 0x40000001; ir = 0x00000004;
    omw::shiftLeftAssign(iv, n);
    CHECK(iv == ir);

    n = 30;
    iv = 0x80000001; ir = 0x40000000;
    omw::shiftLeftAssign(iv, n);
    CHECK(iv == ir);
    iv = 0x40000001; ir = 0x40000000;
    omw::shiftLeftAssign(iv, n);
    CHECK(iv == ir);

    n = 31;
    iv = 0x80000001; ir = 0x80000000;
    omw::shiftLeftAssign(iv, n);
    CHECK(iv == ir);
    iv = 0x40000001; ir = 0x80000000;
    omw::shiftLeftAssign(iv, n);
    CHECK(iv == ir);

    n = 32;
    iv = 0x80000001; ir = 0x00000000;
    omw::shiftLeftAssign(iv, n);
    CHECK(iv == ir);
    iv = 0x40000001; ir = 0x00000000;
    omw::shiftLeftAssign(iv, n);
    CHECK(iv == ir);

    n = 33;
    iv = 0x80000001; ir = 0x00000000;
    omw::shiftLeftAssign(iv, n);
    CHECK(iv == ir);
    iv = 0x40000001; ir = 0x00000000;
    omw::shiftLeftAssign(iv, n);
    CHECK(iv == ir);



    uint32_t uiv;
    uint32_t uir;

    n = 0;
    uiv = 0x80000001; uir = 0x80000001;
    omw::shiftLeftAssign(uiv, n);
    CHECK(uiv == uir);
    uiv = 0x40000001; uir = 0x40000001;
    omw::shiftLeftAssign(uiv, n);
    CHECK(uiv == uir);

    n = 2;
    uiv = 0x80000001; uir = 0x00000004;
    omw::shiftLeftAssign(uiv, n);
    CHECK(uiv == uir);
    uiv = 0x40000001; uir = 0x00000004;
    omw::shiftLeftAssign(uiv, n);
    CHECK(uiv == uir);

    n = 30;
    uiv = 0x80000001; uir = 0x40000000;
    omw::shiftLeftAssign(uiv, n);
    CHECK(uiv == uir);
    uiv = 0x40000001; uir = 0x40000000;
    omw::shiftLeftAssign(uiv, n);
    CHECK(uiv == uir);

    n = 31;
    uiv = 0x80000001; uir = 0x80000000;
    omw::shiftLeftAssign(uiv, n);
    CHECK(uiv == uir);
    uiv = 0x40000001; uir = 0x80000000;
    omw::shiftLeftAssign(uiv, n);
    CHECK(uiv == uir);

    n = 32;
    uiv = 0x80000001; uir = 0x00000000;
    omw::shiftLeftAssign(uiv, n);
    CHECK(uiv == uir);
    uiv = 0x40000001; uir = 0x00000000;
    omw::shiftLeftAssign(uiv, n);
    CHECK(uiv == uir);

    n = 33;
    uiv = 0x80000001; uir = 0x00000000;
    omw::shiftLeftAssign(uiv, n);
    CHECK(uiv == uir);
    uiv = 0x40000001; uir = 0x00000000;
    omw::shiftLeftAssign(uiv, n);
    CHECK(uiv == uir);
}
TEST_CASE("utility.h shiftLeftAssign() 64-bit")
{
    size_t n;

    int64_t iv;
    int64_t ir;

    n = 0;
    iv = 0x8000000000000001; ir = 0x8000000000000001;
    omw::shiftLeftAssign(iv, n);
    CHECK(iv == ir);
    iv = 0x4000000000000001; ir = 0x4000000000000001;
    omw::shiftLeftAssign(iv, n);
    CHECK(iv == ir);

    n = 2;
    iv = 0x8000000000000001; ir = 0x0000000000000004;
    omw::shiftLeftAssign(iv, n);
    CHECK(iv == ir);
    iv = 0x4000000000000001; ir = 0x0000000000000004;
    omw::shiftLeftAssign(iv, n);
    CHECK(iv == ir);

    n = 62;
    iv = 0x8000000000000001; ir = 0x4000000000000000;
    omw::shiftLeftAssign(iv, n);
    CHECK(iv == ir);
    iv = 0x4000000000000001; ir = 0x4000000000000000;
    omw::shiftLeftAssign(iv, n);
    CHECK(iv == ir);

    n = 63;
    iv = 0x8000000000000001; ir = 0x8000000000000000;
    omw::shiftLeftAssign(iv, n);
    CHECK(iv == ir);
    iv = 0x4000000000000001; ir = 0x8000000000000000;
    omw::shiftLeftAssign(iv, n);
    CHECK(iv == ir);

    n = 64;
    iv = 0x8000000000000001; ir = 0x0000000000000000;
    omw::shiftLeftAssign(iv, n);
    CHECK(iv == ir);
    iv = 0x4000000000000001; ir = 0x0000000000000000;
    omw::shiftLeftAssign(iv, n);
    CHECK(iv == ir);

    n = 65;
    iv = 0x8000000000000001; ir = 0x0000000000000000;
    omw::shiftLeftAssign(iv, n);
    CHECK(iv == ir);
    iv = 0x4000000000000001; ir = 0x0000000000000000;
    omw::shiftLeftAssign(iv, n);
    CHECK(iv == ir);



    uint64_t uiv;
    uint64_t uir;

    n = 0;
    uiv = 0x8000000000000001; uir = 0x8000000000000001;
    omw::shiftLeftAssign(uiv, n);
    CHECK(uiv == uir);
    uiv = 0x4000000000000001; uir = 0x4000000000000001;
    omw::shiftLeftAssign(uiv, n);
    CHECK(uiv == uir);

    n = 2;
    uiv = 0x8000000000000001; uir = 0x0000000000000004;
    omw::shiftLeftAssign(uiv, n);
    CHECK(uiv == uir);
    uiv = 0x4000000000000001; uir = 0x0000000000000004;
    omw::shiftLeftAssign(uiv, n);
    CHECK(uiv == uir);

    n = 62;
    uiv = 0x8000000000000001; uir = 0x4000000000000000;
    omw::shiftLeftAssign(uiv, n);
    CHECK(uiv == uir);
    uiv = 0x4000000000000001; uir = 0x4000000000000000;
    omw::shiftLeftAssign(uiv, n);
    CHECK(uiv == uir);

    n = 63;
    uiv = 0x8000000000000001; uir = 0x8000000000000000;
    omw::shiftLeftAssign(uiv, n);
    CHECK(uiv == uir);
    uiv = 0x4000000000000001; uir = 0x8000000000000000;
    omw::shiftLeftAssign(uiv, n);
    CHECK(uiv == uir);

    n = 64;
    uiv = 0x8000000000000001; uir = 0x0000000000000000;
    omw::shiftLeftAssign(uiv, n);
    CHECK(uiv == uir);
    uiv = 0x4000000000000001; uir = 0x0000000000000000;
    omw::shiftLeftAssign(uiv, n);
    CHECK(uiv == uir);

    n = 65;
    uiv = 0x8000000000000001; uir = 0x0000000000000000;
    omw::shiftLeftAssign(uiv, n);
    CHECK(uiv == uir);
    uiv = 0x4000000000000001; uir = 0x0000000000000000;
    omw::shiftLeftAssign(uiv, n);
    CHECK(uiv == uir);
}

TEST_CASE("utility.h shiftRightAssign() 8-bit")
{
    size_t n;

    int8_t iv;
    int8_t ir;

    n = 0;
    iv = 0x81; ir = 0x81;
    omw::shiftRightAssign(iv, n);
    CHECK(iv == ir);
    iv = 0x41; ir = 0x41;
    omw::shiftRightAssign(iv, n);
    CHECK(iv == ir);

    n = 2;
    iv = 0x81; ir = 0xE0;
    omw::shiftRightAssign(iv, n);
    CHECK(iv == ir);
    iv = 0x41; ir = 0x10;
    omw::shiftRightAssign(iv, n);
    CHECK(iv == ir);

    n = 6;
    iv = 0x81; ir = 0xFE;
    omw::shiftRightAssign(iv, n);
    CHECK(iv == ir);
    iv = 0x41; ir = 0x01;
    omw::shiftRightAssign(iv, n);
    CHECK(iv == ir);

    n = 7;
    iv = 0x81; ir = 0xFF;
    omw::shiftRightAssign(iv, n);
    CHECK(iv == ir);
    iv = 0x41; ir = 0x00;
    omw::shiftRightAssign(iv, n);
    CHECK(iv == ir);

    n = 8;
    iv = 0x81; ir = 0xFF;
    omw::shiftRightAssign(iv, n);
    CHECK(iv == ir);
    iv = 0x41; ir = 0x00;
    omw::shiftRightAssign(iv, n);
    CHECK(iv == ir);

    n = 9;
    iv = 0x81; ir = 0xFF;
    omw::shiftRightAssign(iv, n);
    CHECK(iv == ir);
    iv = 0x41; ir = 0x00;
    omw::shiftRightAssign(iv, n);
    CHECK(iv == ir);



    uint8_t uiv;
    uint8_t uir;

    n = 0;
    uiv = 0x81; uir = 0x81;
    omw::shiftRightAssign(uiv, n);
    CHECK(uiv == uir);
    uiv = 0x41; uir = 0x41;
    omw::shiftRightAssign(uiv, n);
    CHECK(uiv == uir);

    n = 2;
    uiv = 0x81; uir = 0x20;
    omw::shiftRightAssign(uiv, n);
    CHECK(uiv == uir);
    uiv = 0x41; uir = 0x10;
    omw::shiftRightAssign(uiv, n);
    CHECK(uiv == uir);

    n = 6;
    uiv = 0x81; uir = 0x02;
    omw::shiftRightAssign(uiv, n);
    CHECK(uiv == uir);
    uiv = 0x41; uir = 0x01;
    omw::shiftRightAssign(uiv, n);
    CHECK(uiv == uir);

    n = 7;
    uiv = 0x81; uir = 0x01;
    omw::shiftRightAssign(uiv, n);
    CHECK(uiv == uir);
    uiv = 0x41; uir = 0x00;
    omw::shiftRightAssign(uiv, n);
    CHECK(uiv == uir);

    n = 8;
    uiv = 0x81; uir = 0x00;
    omw::shiftRightAssign(uiv, n);
    CHECK(uiv == uir);
    uiv = 0x41; uir = 0x00;
    omw::shiftRightAssign(uiv, n);
    CHECK(uiv == uir);

    n = 9;
    uiv = 0x81; uir = 0x00;
    omw::shiftRightAssign(uiv, n);
    CHECK(uiv == uir);
    uiv = 0x41; uir = 0x00;
    omw::shiftRightAssign(uiv, n);
    CHECK(uiv == uir);
}
TEST_CASE("utility.h shiftRightAssign() 16-bit")
{
    size_t n;

    int16_t iv;
    int16_t ir;

    n = 0;
    iv = 0x8001; ir = 0x8001;
    omw::shiftRightAssign(iv, n);
    CHECK(iv == ir);
    iv = 0x4001; ir = 0x4001;
    omw::shiftRightAssign(iv, n);
    CHECK(iv == ir);

    n = 2;
    iv = 0x8001; ir = 0xE000;
    omw::shiftRightAssign(iv, n);
    CHECK(iv == ir);
    iv = 0x4001; ir = 0x1000;
    omw::shiftRightAssign(iv, n);
    CHECK(iv == ir);

    n = 14;
    iv = 0x8001; ir = 0xFFFE;
    omw::shiftRightAssign(iv, n);
    CHECK(iv == ir);
    iv = 0x4001; ir = 0x0001;
    omw::shiftRightAssign(iv, n);
    CHECK(iv == ir);

    n = 15;
    iv = 0x8001; ir = 0xFFFF;
    omw::shiftRightAssign(iv, n);
    CHECK(iv == ir);
    iv = 0x4001; ir = 0x0000;
    omw::shiftRightAssign(iv, n);
    CHECK(iv == ir);

    n = 16;
    iv = 0x8001; ir = 0xFFFF;
    omw::shiftRightAssign(iv, n);
    CHECK(iv == ir);
    iv = 0x4001; ir = 0x0000;
    omw::shiftRightAssign(iv, n);
    CHECK(iv == ir);

    n = 17;
    iv = 0x8001; ir = 0xFFFF;
    omw::shiftRightAssign(iv, n);
    CHECK(iv == ir);
    iv = 0x4001; ir = 0x0000;
    omw::shiftRightAssign(iv, n);
    CHECK(iv == ir);



    uint16_t uiv;
    uint16_t uir;

    n = 0;
    uiv = 0x8001; uir = 0x8001;
    omw::shiftRightAssign(uiv, n);
    CHECK(uiv == uir);
    uiv = 0x4001; uir = 0x4001;
    omw::shiftRightAssign(uiv, n);
    CHECK(uiv == uir);

    n = 2;
    uiv = 0x8001; uir = 0x2000;
    omw::shiftRightAssign(uiv, n);
    CHECK(uiv == uir);
    uiv = 0x41; uir = 0x10;
    omw::shiftRightAssign(uiv, n);
    CHECK(uiv == uir);

    n = 14;
    uiv = 0x8001; uir = 0x0002;
    omw::shiftRightAssign(uiv, n);
    CHECK(uiv == uir);
    uiv = 0x4001; uir = 0x0001;
    omw::shiftRightAssign(uiv, n);
    CHECK(uiv == uir);

    n = 15;
    uiv = 0x8001; uir = 0x0001;
    omw::shiftRightAssign(uiv, n);
    CHECK(uiv == uir);
    uiv = 0x4001; uir = 0x0000;
    omw::shiftRightAssign(uiv, n);
    CHECK(uiv == uir);

    n = 16;
    uiv = 0x8001; uir = 0x0000;
    omw::shiftRightAssign(uiv, n);
    CHECK(uiv == uir);
    uiv = 0x4001; uir = 0x0000;
    omw::shiftRightAssign(uiv, n);
    CHECK(uiv == uir);

    n = 17;
    uiv = 0x8001; uir = 0x0000;
    omw::shiftRightAssign(uiv, n);
    CHECK(uiv == uir);
    uiv = 0x4001; uir = 0x0000;
    omw::shiftRightAssign(uiv, n);
    CHECK(uiv == uir);
}
TEST_CASE("utility.h shiftRightAssign() 32-bit")
{
    size_t n;

    int32_t iv;
    int32_t ir;

    n = 0;
    iv = 0x80000001; ir = 0x80000001;
    omw::shiftRightAssign(iv, n);
    CHECK(iv == ir);
    iv = 0x40000001; ir = 0x40000001;
    omw::shiftRightAssign(iv, n);
    CHECK(iv == ir);

    n = 2;
    iv = 0x80000001; ir = 0xE0000000;
    omw::shiftRightAssign(iv, n);
    CHECK(iv == ir);
    iv = 0x40000001; ir = 0x10000000;
    omw::shiftRightAssign(iv, n);
    CHECK(iv == ir);

    n = 30;
    iv = 0x80000001; ir = 0xFFFFFFFE;
    omw::shiftRightAssign(iv, n);
    CHECK(iv == ir);
    iv = 0x40000001; ir = 0x00000001;
    omw::shiftRightAssign(iv, n);
    CHECK(iv == ir);

    n = 31;
    iv = 0x80000001; ir = 0xFFFFFFFF;
    omw::shiftRightAssign(iv, n);
    CHECK(iv == ir);
    iv = 0x40000001; ir = 0x00000000;
    omw::shiftRightAssign(iv, n);
    CHECK(iv == ir);

    n = 32;
    iv = 0x80000001; ir = 0xFFFFFFFF;
    omw::shiftRightAssign(iv, n);
    CHECK(iv == ir);
    iv = 0x40000001; ir = 0x00000000;
    omw::shiftRightAssign(iv, n);
    CHECK(iv == ir);

    n = 33;
    iv = 0x80000001; ir = 0xFFFFFFFF;
    omw::shiftRightAssign(iv, n);
    CHECK(iv == ir);
    iv = 0x40000001; ir = 0x00000000;
    omw::shiftRightAssign(iv, n);
    CHECK(iv == ir);



    uint32_t uiv;
    uint32_t uir;

    n = 0;
    uiv = 0x80000001; uir = 0x80000001;
    omw::shiftRightAssign(uiv, n);
    CHECK(uiv == uir);
    uiv = 0x40000001; uir = 0x40000001;
    omw::shiftRightAssign(uiv, n);
    CHECK(uiv == uir);

    n = 2;
    uiv = 0x80000001; uir = 0x20000000;
    omw::shiftRightAssign(uiv, n);
    CHECK(uiv == uir);
    uiv = 0x41; uir = 0x10;
    omw::shiftRightAssign(uiv, n);
    CHECK(uiv == uir);

    n = 30;
    uiv = 0x80000001; uir = 0x00000002;
    omw::shiftRightAssign(uiv, n);
    CHECK(uiv == uir);
    uiv = 0x40000001; uir = 0x00000001;
    omw::shiftRightAssign(uiv, n);
    CHECK(uiv == uir);

    n = 31;
    uiv = 0x80000001; uir = 0x00000001;
    omw::shiftRightAssign(uiv, n);
    CHECK(uiv == uir);
    uiv = 0x40000001; uir = 0x00000000;
    omw::shiftRightAssign(uiv, n);
    CHECK(uiv == uir);

    n = 32;
    uiv = 0x80000001; uir = 0x00000000;
    omw::shiftRightAssign(uiv, n);
    CHECK(uiv == uir);
    uiv = 0x40000001; uir = 0x00000000;
    omw::shiftRightAssign(uiv, n);
    CHECK(uiv == uir);

    n = 33;
    uiv = 0x80000001; uir = 0x00000000;
    omw::shiftRightAssign(uiv, n);
    CHECK(uiv == uir);
    uiv = 0x40000001; uir = 0x00000000;
    omw::shiftRightAssign(uiv, n);
    CHECK(uiv == uir);
}
TEST_CASE("utility.h shiftRightAssign() 64-bit")
{
}

TEST_CASE("utility.h shiftLeft() 8-bit")
{
}
TEST_CASE("utility.h shiftLeft() 16-bit")
{
}
TEST_CASE("utility.h shiftLeft() 32-bit")
{
}
TEST_CASE("utility.h shiftLeft() 64-bit")
{
}

TEST_CASE("utility.h shiftRight() 8-bit") 
{
}
TEST_CASE("utility.h shiftRight() 16-bit") 
{
}
TEST_CASE("utility.h shiftRight() 32-bit") 
{
}
TEST_CASE("utility.h shiftRight() 64-bit") 
{
}



TEST_CASE("utility.h toggle()")
{
    bool b = false;
    omw::toggle(b);
    CHECK(b == true);
    omw::toggle(b);
    CHECK(b == false);
    omw::toggle(b);
    CHECK(b == true);

    int i = 123;
    omw::toggle(i);
    CHECK(i == 0);
    omw::toggle(i);
    CHECK(i == 1);
    omw::toggle(i);
    CHECK(i == 0);
}



TEST_CASE("utility.h vectorContains()")
{
    const std::vector<int> vInt = { 1, 5, 9 };
    CHECK(omw::vectorContains(vInt, 1));
    CHECK_FALSE(omw::vectorContains(vInt, 0));

    const std::vector<std::string> vStdString = { "the", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog" };
    CHECK(omw::vectorContains(vStdString, std::string("fox")));
    CHECK_FALSE(omw::vectorContains(vStdString, std::string("boat")));

    const std::vector<omw::string> vString = { "pack", "my", "box", "with", "five", "dozen", "liquor", "jugs" };
    CHECK(omw::vectorContains(vString, omw::string("five")));
    CHECK_FALSE(omw::vectorContains(vString, omw::string("boat")));
}



#endif // TEST_OMW_UTIL_H
