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
}
TEST_CASE("utility.h shiftLeftAssign() 32-bit")
{
}
TEST_CASE("utility.h shiftLeftAssign() 64-bit")
{
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
}
TEST_CASE("utility.h shiftRightAssign() 32-bit")
{
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
