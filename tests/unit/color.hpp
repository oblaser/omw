/*
author         Oliver Blaser
date           15.09.2021
copyright      MIT - Copyright (c) 2021 Oliver Blaser
*/

#ifndef TEST_OMW_COLOR_H
#define TEST_OMW_COLOR_H

#include <cstdint>
#include <stdexcept>

#include "testUtil.h"

#include <catch2/catch.hpp>
#include <omw/color.h>


TEST_CASE("color.h omw::Color ctor")
{
    omw::Color col1;
    CHECK(col1.isValid() == false);
    CHECK(col1.r() == 0);
    CHECK(col1.g() == 0);
    CHECK(col1.b() == 0);
    CHECK(col1.a() == 255);

    col1 = omw::Color(1, 2, 3);
    CHECK(col1.isValid() == true);
    CHECK(col1.r() == 1);
    CHECK(col1.g() == 2);
    CHECK(col1.b() == 3);
    CHECK(col1.a() == 255);

    col1 = omw::Color();
    CHECK(col1.isValid() == false);


    omw::Color col2;
    CHECK(col2.isValid() == false);

    col2 = omw::Color(10, 11, 12, 50);
    CHECK(col2.isValid() == true);
    CHECK(col2.r() == 10);
    CHECK(col2.g() == 11);
    CHECK(col2.b() == 12);
    CHECK(col2.a() == 50);


    omw::Color col3;
    CHECK(col3.isValid() == false);

    col3 = omw::Color(0x11223344);
    CHECK(col3.isValid() == true);
    CHECK(col3.r() == 0x22);
    CHECK(col3.g() == 0x33);
    CHECK(col3.b() == 0x44);
    CHECK(col3.a() == 255);


    omw::Color col4;
    CHECK(col4.isValid() == false);

    col4 = omw::Color("#123456");
    CHECK(col4.isValid() == true);
    CHECK(col4.r() == 0x12);
    CHECK(col4.g() == 0x34);
    CHECK(col4.b() == 0x56);
    CHECK(col4.a() == 255);
}

TEST_CASE("color.h omw::Color implicit ctor")
{
    omw::Color other(0x12ab34);
    omw::Color col;

    col = other;
    CHECK(col.r() == 0x12);
    CHECK(col.g() == 0xAB);
    CHECK(col.b() == 0x34);
    CHECK(col.a() == 255);

    col = "#fab";
    CHECK(col.r() == 0xFF);
    CHECK(col.g() == 0xAA);
    CHECK(col.b() == 0xBB);
    CHECK(col.a() == 255);

    const std::string colorStr1("432105");
    col = colorStr1;
    CHECK(col.r() == 0x43);
    CHECK(col.g() == 0x21);
    CHECK(col.b() == 0x05);
    CHECK(col.a() == 255);

    const omw::string colorStr2("#42a3c8");
    col = colorStr2;
    CHECK(col.r() == 0x42);
    CHECK(col.g() == 0xA3);
    CHECK(col.b() == 0xC8);
    CHECK(col.a() == 255);

    col = 258;
    CHECK(col.r() == 0);
    CHECK(col.g() == 1);
    CHECK(col.b() == 2);
    CHECK(col.a() == 255);

    col = 0xEA01CB;
    CHECK(col.r() == 0xEA);
    CHECK(col.g() == 1);
    CHECK(col.b() == 0xCB);
    CHECK(col.a() == 255);
}

TEST_CASE("color.h omw::Color::set()")
{
    omw::Color col1;
    CHECK(col1.isValid() == false);

    col1.set(1, 2, 3);
    CHECK(col1.isValid() == true);
    CHECK(col1.r() == 1);
    CHECK(col1.g() == 2);
    CHECK(col1.b() == 3);
    CHECK(col1.a() == 255);


    omw::Color col2;
    CHECK(col2.isValid() == false);

    col2.set(10, 11, 12, 50);
    CHECK(col2.isValid() == true);
    CHECK(col2.r() == 10);
    CHECK(col2.g() == 11);
    CHECK(col2.b() == 12);
    CHECK(col2.a() == 50);


    omw::Color col3;
    CHECK(col3.isValid() == false);

    col3.set(0x11223344);
    CHECK(col3.isValid() == true);
    CHECK(col3.r() == 0x22);
    CHECK(col3.g() == 0x33);
    CHECK(col3.b() == 0x44);
    CHECK(col3.a() == 255);


    omw::Color col4;
    CHECK(col4.isValid() == false);

    col4.set("#123456");
    CHECK(col4.isValid() == true);
    CHECK(col4.r() == 0x12);
    CHECK(col4.g() == 0x34);
    CHECK(col4.b() == 0x56);
    CHECK(col4.a() == 255);

    col4.set("abCDef");
    CHECK(col4.r() == 0xAB);
    CHECK(col4.g() == 0xCD);
    CHECK(col4.b() == 0xEF);
    CHECK(col4.a() == 255);

    col4.set("#123");
    CHECK(col4.r() == 0x11);
    CHECK(col4.g() == 0x22);
    CHECK(col4.b() == 0x33);
    CHECK(col4.a() == 255);

    col4.set("987");
    CHECK(col4.r() == 0x99);
    CHECK(col4.g() == 0x88);
    CHECK(col4.b() == 0x77);
    CHECK(col4.a() == 255);
}

TEST_CASE("color.h omw::Color::setARGB()")
{
    omw::Color col1;
    CHECK(col1.isValid() == false);

    col1.setARGB(0x11223344);
    CHECK(col1.isValid() == true);
    CHECK(col1.r() == 0x22);
    CHECK(col1.g() == 0x33);
    CHECK(col1.b() == 0x44);
    CHECK(col1.a() == 0x11);
}

TEST_CASE("color.h omw::Color::set..()")
{
    omw::Color col1;
    CHECK(col1.isValid() == false);

    col1.setR(78);
    CHECK(col1.isValid() == true);
    CHECK(col1.r() == 78);
    CHECK(col1.g() == 0);
    CHECK(col1.b() == 0);
    CHECK(col1.a() == 255);


    omw::Color col2;
    CHECK(col2.isValid() == false);

    col2.setG(78);
    CHECK(col2.isValid() == true);
    CHECK(col2.r() == 0);
    CHECK(col2.g() == 78);
    CHECK(col2.b() == 0);
    CHECK(col2.a() == 255);


    omw::Color col3;
    CHECK(col3.isValid() == false);

    col3.setB(78);
    CHECK(col3.isValid() == true);
    CHECK(col3.r() == 0);
    CHECK(col3.g() == 0);
    CHECK(col3.b() == 78);
    CHECK(col3.a() == 255);


    omw::Color col4;
    CHECK(col4.isValid() == false);

    col4.setA(78);
    CHECK(col4.isValid() == true);
    CHECK(col4.r() == 0);
    CHECK(col4.g() == 0);
    CHECK(col4.b() == 0);
    CHECK(col4.a() == 78);
}

TEST_CASE("color.h omw::Color get components")
{
    omw::Color col(12, 34, 56, 78);
    CHECK(col.r() == 12);
    CHECK(col.g() == 34);
    CHECK(col.b() == 56);
    CHECK(col.a() == 78);
}

TEST_CASE("color.h omw::Color to integer")
{
    omw::Color col;

    col.set(0x98, 0x76, 0x54, 0);
    CHECK(col.toRGB() == 0x00987654);
    CHECK(col.toARGB() == 0x00987654);

    col.set(0x12, 0x34, 0x56, 0x3F);
    CHECK(col.toRGB() == 0x00123456);
    CHECK(col.toARGB() == 0x3F123456);

    col.set(0xAB, 0xCD, 0xEF);
    CHECK(col.toRGB() == 0x00ABCDEF);
    CHECK(col.toARGB() == 0xFFABCDEF);
}

TEST_CASE("color.h omw::Color to string")
{
    omw::Color col;

    col.set(0x98, 0x76, 0x54, 0);
    CHECK(col.toString() == "987654");
    CHECK(col.toCssStr() == "#987654");

    col.set(0x12, 0x34, 0x56, 0x3F);
    CHECK(col.toString() == "123456");
    CHECK(col.toCssStr() == "#123456");

    col.set(0xAB, 0xCD, 0xEF);
    CHECK(col.toString() == "ABCDEF");
    CHECK(col.toCssStr() == "#ABCDEF");
}

TEST_CASE("color.h omw::Color operators")
{
    omw::Color col;

    col.set(4, 5, 6);
    CHECK(col == 0x040506);
    CHECK(col == "#040506");
    CHECK(0x040506 == col);
    CHECK("#040506" == col);

    col.set(4, 5, 6, 200);
    CHECK_FALSE(col == 0x040506);
    CHECK_FALSE(col == "#040506");
    CHECK(col != 0x040506);
    CHECK(col != "#040506");
    CHECK_FALSE(0x040506 == col);
    CHECK_FALSE("#040506" == col);
    CHECK(0x040506 != col);
    CHECK("#040506" != col);


    col.set(4, 5, 6, 200);
    omw::Color result;

    result = col + 0x101010;
    CHECK(result.r() == 20);
    CHECK(result.g() == 21);
    CHECK(result.b() == 22);
    CHECK(result.a() == 200);

    result = 0x101010 + omw::Color(100, 80, 10, 60);
    CHECK(result.r() == 40);
    CHECK(result.g() == 35);
    CHECK(result.b() == 18);
    CHECK(result.a() == 255);

    result = "101010" + omw::Color(100, 80, 10);
    CHECK(result.r() == 116);
    CHECK(result.g() == 96);
    CHECK(result.b() == 26);
    CHECK(result.a() == 255);

    result = "F0FEF5" + omw::Color(16, 5, 47);
    CHECK(result.r() == 0);
    CHECK(result.g() == 3);
    CHECK(result.b() == 36);
    CHECK(result.a() == 255);


    col.set(100, 80, 20, 200);

    result = col - 0x101010;
    CHECK(result.r() == 84);
    CHECK(result.g() == 64);
    CHECK(result.b() == 4);
    CHECK(result.a() == 200);

    result = 0x101010 - omw::Color(100, 80, 10, 25);
    CHECK(result.r() == 6);
    CHECK(result.g() == 8);
    CHECK(result.b() == 15);
    CHECK(result.a() == 255);

    result = "#101010" - omw::Color(1, 2, 3);
    CHECK(result.r() == 15);
    CHECK(result.g() == 14);
    CHECK(result.b() == 13);
    CHECK(result.a() == 255);

    result = "#101010" - omw::Color(17, 59, 214);
    CHECK(result.r() == 255);
    CHECK(result.g() == 213);
    CHECK(result.b() == 58);
    CHECK(result.a() == 255);
}

TEST_CASE("color.h omw::Color win32 support")
{
    omw::Color col(1, 2, 3, 4);
    CHECK(col.to_win32() == 0x00030201);

    col.from_win32(0xABCDEF);
    CHECK(col == omw::Color(0xEF, 0xCD, 0xAB, 255));
}

TEST_CASE("color.h omw::Color wxWidgets support")
{
    omw::Color col;

    col = omw::Color(1, 2, 3);
    CHECK(col.to_wxW_RGB() == 0x00030201);
    CHECK(col.to_wxW_RGBA() == 0xFF030201);

    col = omw::Color(1, 2, 3, 4);
    CHECK(col.to_wxW_RGB() == 0x00030201);
    CHECK(col.to_wxW_RGBA() == 0x04030201);

    col.from_wxW_RGB(0xABCDEF);
    CHECK(col == omw::Color(0xEF, 0xCD, 0xAB, 255));

    col.from_wxW_RGB(0x12ABCDEF);
    CHECK(col == omw::Color(0xEF, 0xCD, 0xAB, 255));

    col.from_wxW_RGBA(0xABCDEF);
    CHECK(col == omw::Color(0xEF, 0xCD, 0xAB, 0));

    col.from_wxW_RGBA(0x10ABCDEF);
    CHECK(col == omw::Color(0xEF, 0xCD, 0xAB, 16));
}


#endif // TEST_OMW_COLOR_H
