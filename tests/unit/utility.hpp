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
    UTILITY_CHECK_SHIFTLEFTASSIGN_S();
    iv = 0x41; ir = 0x41;
    UTILITY_CHECK_SHIFTLEFTASSIGN_S();

    n = 2;
    iv = 0x81; ir = 0x04;
    UTILITY_CHECK_SHIFTLEFTASSIGN_S();
    iv = 0x41; ir = 0x04;
    UTILITY_CHECK_SHIFTLEFTASSIGN_S();

    n = 6;
    iv = 0x81; ir = 0x40;
    UTILITY_CHECK_SHIFTLEFTASSIGN_S();
    iv = 0x41; ir = 0x40;
    UTILITY_CHECK_SHIFTLEFTASSIGN_S();

    n = 7;
    iv = 0x81; ir = 0x80;
    UTILITY_CHECK_SHIFTLEFTASSIGN_S();
    iv = 0x41; ir = 0x80;
    UTILITY_CHECK_SHIFTLEFTASSIGN_S();

    n = 8;
    iv = 0x81; ir = 0x00;
    UTILITY_CHECK_SHIFTLEFTASSIGN_S();
    iv = 0x41; ir = 0x00;
    UTILITY_CHECK_SHIFTLEFTASSIGN_S();

    n = 9;
    iv = 0x81; ir = 0x00;
    UTILITY_CHECK_SHIFTLEFTASSIGN_S();
    iv = 0x41; ir = 0x00;
    UTILITY_CHECK_SHIFTLEFTASSIGN_S();

    iv = 1; ir = 2;



    uint8_t uiv;
    uint8_t uir;

    n = 0;
    uiv = 0x81; uir = 0x81;
    UTILITY_CHECK_SHIFTLEFTASSIGN_U();
    uiv = 0x41; uir = 0x41;
    UTILITY_CHECK_SHIFTLEFTASSIGN_U();

    n = 2;
    uiv = 0x81; uir = 0x04;
    UTILITY_CHECK_SHIFTLEFTASSIGN_U();
    uiv = 0x41; uir = 0x04;
    UTILITY_CHECK_SHIFTLEFTASSIGN_U();

    n = 6;
    uiv = 0x81; uir = 0x40;
    UTILITY_CHECK_SHIFTLEFTASSIGN_U();
    uiv = 0x41; uir = 0x40;
    UTILITY_CHECK_SHIFTLEFTASSIGN_U();

    n = 7;
    uiv = 0x81; uir = 0x80;
    UTILITY_CHECK_SHIFTLEFTASSIGN_U();
    uiv = 0x41; uir = 0x80;
    UTILITY_CHECK_SHIFTLEFTASSIGN_U();

    n = 8;
    uiv = 0x81; uir = 0x00;
    UTILITY_CHECK_SHIFTLEFTASSIGN_U();
    uiv = 0x41; uir = 0x00;
    UTILITY_CHECK_SHIFTLEFTASSIGN_U();

    n = 9;
    uiv = 0x81; uir = 0x00;
    UTILITY_CHECK_SHIFTLEFTASSIGN_U();
    uiv = 0x41; uir = 0x00;
    UTILITY_CHECK_SHIFTLEFTASSIGN_U();
}
TEST_CASE("utility.h shiftLeftAssign() 16-bit")
{
    size_t n;

    int16_t iv;
    int16_t ir;

    n = 0;
    iv = 0x8001; ir = 0x8001;
    UTILITY_CHECK_SHIFTLEFTASSIGN_S();
    iv = 0x4001; ir = 0x4001;
    UTILITY_CHECK_SHIFTLEFTASSIGN_S();

    n = 2;
    iv = 0x8001; ir = 0x0004;
    UTILITY_CHECK_SHIFTLEFTASSIGN_S();
    iv = 0x4001; ir = 0x0004;
    UTILITY_CHECK_SHIFTLEFTASSIGN_S();

    n = 14;
    iv = 0x8001; ir = 0x4000;
    UTILITY_CHECK_SHIFTLEFTASSIGN_S();
    iv = 0x4001; ir = 0x4000;
    UTILITY_CHECK_SHIFTLEFTASSIGN_S();

    n = 15;
    iv = 0x8001; ir = 0x8000;
    UTILITY_CHECK_SHIFTLEFTASSIGN_S();
    iv = 0x4001; ir = 0x8000;
    UTILITY_CHECK_SHIFTLEFTASSIGN_S();

    n = 16;
    iv = 0x8001; ir = 0x0000;
    UTILITY_CHECK_SHIFTLEFTASSIGN_S();
    iv = 0x4001; ir = 0x0000;
    UTILITY_CHECK_SHIFTLEFTASSIGN_S();

    n = 17;
    iv = 0x8001; ir = 0x0000;
    UTILITY_CHECK_SHIFTLEFTASSIGN_S();
    iv = 0x4001; ir = 0x0000;
    UTILITY_CHECK_SHIFTLEFTASSIGN_S();

    iv = 1; ir = 2;



    uint16_t uiv;
    uint16_t uir;

    n = 0;
    uiv = 0x8001; uir = 0x8001;
    UTILITY_CHECK_SHIFTLEFTASSIGN_U();
    uiv = 0x4001; uir = 0x4001;
    UTILITY_CHECK_SHIFTLEFTASSIGN_U();

    n = 2;
    uiv = 0x8001; uir = 0x0004;
    UTILITY_CHECK_SHIFTLEFTASSIGN_U();
    uiv = 0x4001; uir = 0x0004;
    UTILITY_CHECK_SHIFTLEFTASSIGN_U();

    n = 14;
    uiv = 0x8001; uir = 0x4000;
    UTILITY_CHECK_SHIFTLEFTASSIGN_U();
    uiv = 0x4001; uir = 0x4000;
    UTILITY_CHECK_SHIFTLEFTASSIGN_U();

    n = 15;
    uiv = 0x8001; uir = 0x8000;
    UTILITY_CHECK_SHIFTLEFTASSIGN_U();
    uiv = 0x4001; uir = 0x8000;
    UTILITY_CHECK_SHIFTLEFTASSIGN_U();

    n = 16;
    uiv = 0x8001; uir = 0x0000;
    UTILITY_CHECK_SHIFTLEFTASSIGN_U();
    uiv = 0x4001; uir = 0x0000;
    UTILITY_CHECK_SHIFTLEFTASSIGN_U();

    n = 17;
    uiv = 0x8001; uir = 0x0000;
    UTILITY_CHECK_SHIFTLEFTASSIGN_U();
    uiv = 0x4001; uir = 0x0000;
    UTILITY_CHECK_SHIFTLEFTASSIGN_U();
}
TEST_CASE("utility.h shiftLeftAssign() 32-bit")
{
    size_t n;

    int32_t iv;
    int32_t ir;

    n = 0;
    iv = 0x80000001; ir = 0x80000001;
    UTILITY_CHECK_SHIFTLEFTASSIGN_S();
    iv = 0x40000001; ir = 0x40000001;
    UTILITY_CHECK_SHIFTLEFTASSIGN_S();

    n = 2;
    iv = 0x80000001; ir = 0x00000004;
    UTILITY_CHECK_SHIFTLEFTASSIGN_S();
    iv = 0x40000001; ir = 0x00000004;
    UTILITY_CHECK_SHIFTLEFTASSIGN_S();

    n = 30;
    iv = 0x80000001; ir = 0x40000000;
    UTILITY_CHECK_SHIFTLEFTASSIGN_S();
    iv = 0x40000001; ir = 0x40000000;
    UTILITY_CHECK_SHIFTLEFTASSIGN_S();

    n = 31;
    iv = 0x80000001; ir = 0x80000000;
    UTILITY_CHECK_SHIFTLEFTASSIGN_S();
    iv = 0x40000001; ir = 0x80000000;
    UTILITY_CHECK_SHIFTLEFTASSIGN_S();

    n = 32;
    iv = 0x80000001; ir = 0x00000000;
    UTILITY_CHECK_SHIFTLEFTASSIGN_S();
    iv = 0x40000001; ir = 0x00000000;
    UTILITY_CHECK_SHIFTLEFTASSIGN_S();

    n = 33;
    iv = 0x80000001; ir = 0x00000000;
    UTILITY_CHECK_SHIFTLEFTASSIGN_S();
    iv = 0x40000001; ir = 0x00000000;
    UTILITY_CHECK_SHIFTLEFTASSIGN_S();

    iv = 1; ir = 2;



    uint32_t uiv;
    uint32_t uir;

    n = 0;
    uiv = 0x80000001; uir = 0x80000001;
    UTILITY_CHECK_SHIFTLEFTASSIGN_U();
    uiv = 0x40000001; uir = 0x40000001;
    UTILITY_CHECK_SHIFTLEFTASSIGN_U();

    n = 2;
    uiv = 0x80000001; uir = 0x00000004;
    UTILITY_CHECK_SHIFTLEFTASSIGN_U();
    uiv = 0x40000001; uir = 0x00000004;
    UTILITY_CHECK_SHIFTLEFTASSIGN_U();

    n = 30;
    uiv = 0x80000001; uir = 0x40000000;
    UTILITY_CHECK_SHIFTLEFTASSIGN_U();
    uiv = 0x40000001; uir = 0x40000000;
    UTILITY_CHECK_SHIFTLEFTASSIGN_U();

    n = 31;
    uiv = 0x80000001; uir = 0x80000000;
    UTILITY_CHECK_SHIFTLEFTASSIGN_U();
    uiv = 0x40000001; uir = 0x80000000;
    UTILITY_CHECK_SHIFTLEFTASSIGN_U();

    n = 32;
    uiv = 0x80000001; uir = 0x00000000;
    UTILITY_CHECK_SHIFTLEFTASSIGN_U();
    uiv = 0x40000001; uir = 0x00000000;
    UTILITY_CHECK_SHIFTLEFTASSIGN_U();

    n = 33;
    uiv = 0x80000001; uir = 0x00000000;
    UTILITY_CHECK_SHIFTLEFTASSIGN_U();
    uiv = 0x40000001; uir = 0x00000000;
    UTILITY_CHECK_SHIFTLEFTASSIGN_U();
}
TEST_CASE("utility.h shiftLeftAssign() 64-bit")
{
    size_t n;

    int64_t iv;
    int64_t ir;

    n = 0;
    iv = 0x8000000000000001; ir = 0x8000000000000001;
    UTILITY_CHECK_SHIFTLEFTASSIGN_S();
    iv = 0x4000000000000001; ir = 0x4000000000000001;
    UTILITY_CHECK_SHIFTLEFTASSIGN_S();

    n = 2;
    iv = 0x8000000000000001; ir = 0x0000000000000004;
    UTILITY_CHECK_SHIFTLEFTASSIGN_S();
    iv = 0x4000000000000001; ir = 0x0000000000000004;
    UTILITY_CHECK_SHIFTLEFTASSIGN_S();

    n = 62;
    iv = 0x8000000000000001; ir = 0x4000000000000000;
    UTILITY_CHECK_SHIFTLEFTASSIGN_S();
    iv = 0x4000000000000001; ir = 0x4000000000000000;
    UTILITY_CHECK_SHIFTLEFTASSIGN_S();

    n = 63;
    iv = 0x8000000000000001; ir = 0x8000000000000000;
    UTILITY_CHECK_SHIFTLEFTASSIGN_S();
    iv = 0x4000000000000001; ir = 0x8000000000000000;
    UTILITY_CHECK_SHIFTLEFTASSIGN_S();

    n = 64;
    iv = 0x8000000000000001; ir = 0x0000000000000000;
    UTILITY_CHECK_SHIFTLEFTASSIGN_S();
    iv = 0x4000000000000001; ir = 0x0000000000000000;
    UTILITY_CHECK_SHIFTLEFTASSIGN_S();

    n = 65;
    iv = 0x8000000000000001; ir = 0x0000000000000000;
    UTILITY_CHECK_SHIFTLEFTASSIGN_S();
    iv = 0x4000000000000001; ir = 0x0000000000000000;
    UTILITY_CHECK_SHIFTLEFTASSIGN_S();

    iv = 1; ir = 2;



    uint64_t uiv;
    uint64_t uir;

    n = 0;
    uiv = 0x8000000000000001; uir = 0x8000000000000001;
    UTILITY_CHECK_SHIFTLEFTASSIGN_U();
    uiv = 0x4000000000000001; uir = 0x4000000000000001;
    UTILITY_CHECK_SHIFTLEFTASSIGN_U();

    n = 2;
    uiv = 0x8000000000000001; uir = 0x0000000000000004;
    UTILITY_CHECK_SHIFTLEFTASSIGN_U();
    uiv = 0x4000000000000001; uir = 0x0000000000000004;
    UTILITY_CHECK_SHIFTLEFTASSIGN_U();

    n = 62;
    uiv = 0x8000000000000001; uir = 0x4000000000000000;
    UTILITY_CHECK_SHIFTLEFTASSIGN_U();
    uiv = 0x4000000000000001; uir = 0x4000000000000000;
    UTILITY_CHECK_SHIFTLEFTASSIGN_U();

    n = 63;
    uiv = 0x8000000000000001; uir = 0x8000000000000000;
    UTILITY_CHECK_SHIFTLEFTASSIGN_U();
    uiv = 0x4000000000000001; uir = 0x8000000000000000;
    UTILITY_CHECK_SHIFTLEFTASSIGN_U();

    n = 64;
    uiv = 0x8000000000000001; uir = 0x0000000000000000;
    UTILITY_CHECK_SHIFTLEFTASSIGN_U();
    uiv = 0x4000000000000001; uir = 0x0000000000000000;
    UTILITY_CHECK_SHIFTLEFTASSIGN_U();

    n = 65;
    uiv = 0x8000000000000001; uir = 0x0000000000000000;
    UTILITY_CHECK_SHIFTLEFTASSIGN_U();
    uiv = 0x4000000000000001; uir = 0x0000000000000000;
    UTILITY_CHECK_SHIFTLEFTASSIGN_U();
}

TEST_CASE("utility.h shiftRightAssign() 8-bit")
{
    size_t n;

    int8_t iv;
    int8_t ir;

    n = 0;
    iv = 0x81; ir = 0x81;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_S();
    iv = 0x41; ir = 0x41;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_S();

    n = 2;
    iv = 0x81; ir = 0xE0;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_S();
    iv = 0x41; ir = 0x10;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_S();

    n = 6;
    iv = 0x81; ir = 0xFE;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_S();
    iv = 0x41; ir = 0x01;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_S();

    n = 7;
    iv = 0x81; ir = 0xFF;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_S();
    iv = 0x41; ir = 0x00;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_S();

    n = 8;
    iv = 0x81; ir = 0xFF;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_S();
    iv = 0x41; ir = 0x00;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_S();

    n = 9;
    iv = 0x81; ir = 0xFF;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_S();
    iv = 0x41; ir = 0x00;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_S();

    iv = 1; ir = 2;



    uint8_t uiv;
    uint8_t uir;

    n = 0;
    uiv = 0x81; uir = 0x81;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_U();
    uiv = 0x41; uir = 0x41;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_U();

    n = 2;
    uiv = 0x81; uir = 0x20;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_U();
    uiv = 0x41; uir = 0x10;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_U();

    n = 6;
    uiv = 0x81; uir = 0x02;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_U();
    uiv = 0x41; uir = 0x01;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_U();

    n = 7;
    uiv = 0x81; uir = 0x01;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_U();
    uiv = 0x41; uir = 0x00;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_U();

    n = 8;
    uiv = 0x81; uir = 0x00;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_U();
    uiv = 0x41; uir = 0x00;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_U();

    n = 9;
    uiv = 0x81; uir = 0x00;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_U();
    uiv = 0x41; uir = 0x00;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_U();
}
TEST_CASE("utility.h shiftRightAssign() 16-bit")
{
    size_t n;

    int16_t iv;
    int16_t ir;

    n = 0;
    iv = 0x8001; ir = 0x8001;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_S();
    iv = 0x4001; ir = 0x4001;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_S();

    n = 2;
    iv = 0x8001; ir = 0xE000;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_S();
    iv = 0x4001; ir = 0x1000;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_S();

    n = 14;
    iv = 0x8001; ir = 0xFFFE;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_S();
    iv = 0x4001; ir = 0x0001;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_S();

    n = 15;
    iv = 0x8001; ir = 0xFFFF;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_S();
    iv = 0x4001; ir = 0x0000;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_S();

    n = 16;
    iv = 0x8001; ir = 0xFFFF;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_S();
    iv = 0x4001; ir = 0x0000;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_S();

    n = 17;
    iv = 0x8001; ir = 0xFFFF;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_S();
    iv = 0x4001; ir = 0x0000;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_S();

    iv = 1; ir = 2;



    uint16_t uiv;
    uint16_t uir;

    n = 0;
    uiv = 0x8001; uir = 0x8001;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_U();
    uiv = 0x4001; uir = 0x4001;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_U();

    n = 2;
    uiv = 0x8001; uir = 0x2000;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_U();
    uiv = 0x4001; uir = 0x1000;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_U();

    n = 14;
    uiv = 0x8001; uir = 0x0002;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_U();
    uiv = 0x4001; uir = 0x0001;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_U();

    n = 15;
    uiv = 0x8001; uir = 0x0001;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_U();
    uiv = 0x4001; uir = 0x0000;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_U();

    n = 16;
    uiv = 0x8001; uir = 0x0000;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_U();
    uiv = 0x4001; uir = 0x0000;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_U();

    n = 17;
    uiv = 0x8001; uir = 0x0000;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_U();
    uiv = 0x4001; uir = 0x0000;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_U();
}
TEST_CASE("utility.h shiftRightAssign() 32-bit")
{
    size_t n;

    int32_t iv;
    int32_t ir;

    n = 0;
    iv = 0x80000001; ir = 0x80000001;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_S();
    iv = 0x40000001; ir = 0x40000001;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_S();

    n = 2;
    iv = 0x80000001; ir = 0xE0000000;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_S();
    iv = 0x40000001; ir = 0x10000000;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_S();

    n = 30;
    iv = 0x80000001; ir = 0xFFFFFFFE;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_S();
    iv = 0x40000001; ir = 0x00000001;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_S();

    n = 31;
    iv = 0x80000001; ir = 0xFFFFFFFF;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_S();
    iv = 0x40000001; ir = 0x00000000;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_S();

    n = 32;
    iv = 0x80000001; ir = 0xFFFFFFFF;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_S();
    iv = 0x40000001; ir = 0x00000000;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_S();

    n = 33;
    iv = 0x80000001; ir = 0xFFFFFFFF;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_S();
    iv = 0x40000001; ir = 0x00000000;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_S();

    iv = 1; ir = 2;



    uint32_t uiv;
    uint32_t uir;

    n = 0;
    uiv = 0x80000001; uir = 0x80000001;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_U();
    uiv = 0x40000001; uir = 0x40000001;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_U();

    n = 2;
    uiv = 0x80000001; uir = 0x20000000;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_U();
    uiv = 0x40000001; uir = 0x10000000;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_U();

    n = 30;
    uiv = 0x80000001; uir = 0x00000002;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_U();
    uiv = 0x40000001; uir = 0x00000001;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_U();

    n = 31;
    uiv = 0x80000001; uir = 0x00000001;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_U();
    uiv = 0x40000001; uir = 0x00000000;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_U();

    n = 32;
    uiv = 0x80000001; uir = 0x00000000;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_U();
    uiv = 0x40000001; uir = 0x00000000;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_U();

    n = 33;
    uiv = 0x80000001; uir = 0x00000000;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_U();
    uiv = 0x40000001; uir = 0x00000000;
    UTILITY_CHECK_SHIFTRIGHTASSIGN_U();
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
