/*
author         Oliver Blaser
date           14.07.2021
copyright      MIT - Copyright (c) 2021 Oliver Blaser
*/

#ifndef TEST_OMW_STRING_H
#define TEST_OMW_STRING_H

#include <cstring>
#include <stdexcept>
#include <string>
#include <vector>

#include "testUtil.h"

#include <catch2/catch.hpp>
#include <omw/string.h>



TEST_CASE("string.h omw::StringReplacePair")
{
    const char s1[] = "search1";
    const char r1[] = "replace1";

    const char s2 = '2';
    const char r2[] = "replace2";

    const char s3[] = "search3";
    const char r3 = '3';

    const char s4 = '4';
    const char r4 = 'r';

    omw::StringReplacePair p1(s1, r1);
    omw::StringReplacePair p2(s2, r2);
    omw::StringReplacePair p3(s3, r3);
    omw::StringReplacePair p4;
    omw::StringReplacePair& p4r = p4;
    p4r = omw::StringReplacePair(s4, r4);
    omw::StringReplacePair p5(p4r);

    CHECK(s1 == p1.search());
    CHECK(r1 == p1.replace());

    CHECK(std::string(1, s2) == p2.search());
    CHECK(r2 == p2.replace());

    CHECK(s3 == p3.search());
    CHECK(std::string(1, r3) == p3.replace());

    CHECK(std::string(1, s4) == p4.search());
    CHECK(std::string(1, r4) == p4.replace());

    CHECK(std::string(1, s4) == p5.search());
    CHECK(std::string(1, r4) == p5.replace());
}



TEST_CASE("string.h omw::string ctor")
{
    const char str[] = "a boy with a hat";
    const std::string stdstr(str);
    const omw::string omwstr = std::string(3, 'a');
    const std::string stdfromomw = omwstr;

    CHECK(std::strcmp(omw::string().c_str(), "") == 0);
    CHECK(std::strcmp(omw::string(str).c_str(), str) == 0);
    CHECK(std::strcmp(omw::string(stdstr).c_str(), str) == 0);
    CHECK(std::strcmp(omw::string(str, str + std::strlen(str)).c_str(), str) == 0);
    CHECK(std::strcmp(omwstr.c_str(), "aaa") == 0);
    CHECK(std::strcmp(stdfromomw.c_str(), "aaa") == 0);
}

TEST_CASE("string.h omw::string::replaceFirst()")
{
    const char str[] = "a boy with a hat";
    omw::string s;

    s = str;
    s.replaceFirst("t", "#");
    CHECK(s == "a boy wi#h a hat");
    s.replaceFirst("t", "#");
    CHECK(s == "a boy wi#h a ha#");

    s = str;
    s.replaceFirst("t", "#", 9);
    CHECK(s == "a boy with a ha#");

    s = str;
    s.replaceFirst(omw::StringReplacePair('t', "[?]"), 9);
    CHECK(s == "a boy with a ha[?]");



    s = str;
    s.replaceFirst("", "$");
    CHECK(s == "$a boy with a hat");

    s = str;
    s.replaceFirst("t", "");
    CHECK(s == "a boy wih a hat");

    s = str;
    s.replaceFirst("", "");
    CHECK(s == "a boy with a hat");
}

TEST_CASE("string.h omw::string::replaceAll()")
{
    const char str[] = "a boy with a hat";
    omw::string s;
    size_t nReplacements;

    s = str;
    s.replaceAll("a ", "XYZ ", 0, &nReplacements);
    CHECK(s == "XYZ boy with XYZ hat");
    CHECK(nReplacements == 2);

    s = str;
    s.replaceAll("a ", "XYZ ", 5, &nReplacements);
    CHECK(s == "a boy with XYZ hat");
    CHECK(nReplacements == 1);

    s = str;
    s.replaceAll("ABCDEFGHI", "#", 1, &nReplacements);
    CHECK(s == str);
    CHECK(nReplacements == 0);

    s = str;
    s.replaceAll(omw::StringReplacePair('a', "XYZ"), 11, &nReplacements);
    CHECK(s == "a boy with XYZ hXYZt");
    CHECK(nReplacements == 2);



    s = str;
    s.replaceAll("", "$", 0, &nReplacements);
    CHECK(s == str);
    CHECK(nReplacements == omw::string::npos);

    s = str;
    s.replaceAll("t", "", 0, &nReplacements);
    CHECK(s == "a boy wih a ha");
    CHECK(nReplacements == 2);

    s = str;
    s.replaceAll("", "", 0, &nReplacements);
    CHECK(s == str);
    CHECK(nReplacements == omw::string::npos);

    s = str;
    s.replaceAll("", "", 3, &nReplacements);
    CHECK(s == str);
    CHECK(nReplacements == omw::string::npos);



    const omw::StringReplacePair rp1('a', "#t#");
    const omw::StringReplacePair rp2('t', "# #");
    const omw::StringReplacePair rp3("##", '$');

    std::vector<omw::StringReplacePair> rpv;
    std::vector<size_t> nrv;

    rpv = { rp1, rp2, rp3 };

    s = str;
    s.replaceAll(rpv);
    CHECK(s == "$ $ boy wi# #h $ $ h$ $# #");

    s = str;
    s.replaceAll(rpv, 0, &nReplacements, &nrv);
    CHECK(s == "$ $ boy wi# #h $ $ h$ $# #");
    CHECK(nReplacements == 14);
    CHECK(nrv == std::vector<size_t>({ 3, 5, 6 }));

    s = str;
    s.replaceAll(rpv, 10, &nReplacements, &nrv);
    CHECK(s == "a boy with $ $ h$ $# #");
    CHECK(nReplacements == 9);
    CHECK(nrv == std::vector<size_t>({ 2, 3, 4 }));

    s = str;
    s.replaceAll(rpv, 10, &nReplacements);
    CHECK(s == "a boy with $ $ h$ $# #");
    CHECK(nReplacements == 9);

    s = str;
    s.replaceAll(rpv, 0, nullptr, &nrv);
    CHECK(s == "$ $ boy wi# #h $ $ h$ $# #");
    CHECK(nrv == std::vector<size_t>({ 3, 5, 6 }));



    rpv = { rp3, rp2, rp1 };
    s = str;
    s.replaceAll(rpv, 10);
    CHECK(s == "a boy with #t# h#t## #");



    rpv = { rp3, omw::StringReplacePair("ABCDEFGHI", "#"), omw::StringReplacePair("XYZ", "@") };
    s = str;
    s.replaceAll(rpv, 0, &nReplacements, &nrv);
    CHECK(s == str);
    CHECK(nReplacements == 0);
    CHECK(nrv == std::vector<size_t>({ 0, 0, 0 }));

    rpv = { rp3, omw::StringReplacePair("", "#"), omw::StringReplacePair("", "@") };
    s = str;
    s.replaceAll(rpv, 0, &nReplacements, &nrv);
    CHECK(s == str);
    CHECK(nReplacements == 0);
    CHECK(nrv == std::vector<size_t>({ 0, omw::string::npos, omw::string::npos }));

    rpv = { omw::StringReplacePair("", "#"), omw::StringReplacePair("", "@"), omw::StringReplacePair("", "$") };
    s = str;
    s.replaceAll(rpv, 0, &nReplacements, &nrv);
    CHECK(s == str);
    CHECK(nReplacements == omw::string::npos);
    CHECK(nrv == std::vector<size_t>({ omw::string::npos, omw::string::npos, omw::string::npos }));
}

TEST_CASE("string.h omw::string case conversion")
{
    const omw::string mixed = "0123 ThE QuIcK BrOwN FoX JuMpS OvEr tHe lAzY DoG. 456 =\xC3\x84-\xC3\x96 * \xC3\x9C 789 \xC3\xA4\xC3\xB6\xC3\xBC#";
    const omw::string lower = "0123 the quick brown fox jumps over the lazy dog. 456 =\xC3\x84-\xC3\x96 * \xC3\x9C 789 \xC3\xA4\xC3\xB6\xC3\xBC#";
    const omw::string lowerExt = "0123 the quick brown fox jumps over the lazy dog. 456 =\xC3\xA4-\xC3\xB6 * \xC3\xBC 789 \xC3\xA4\xC3\xB6\xC3\xBC#";
    const omw::string upper = "0123 THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG. 456 =\xC3\x84-\xC3\x96 * \xC3\x9C 789 \xC3\xA4\xC3\xB6\xC3\xBC#";
    const omw::string upperExt = "0123 THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG. 456 =\xC3\x84-\xC3\x96 * \xC3\x9C 789 \xC3\x84\xC3\x96\xC3\x9C#";

    CHECK(mixed.toLower_ascii() == lower);
    CHECK(mixed.toLower_asciiExt() == lowerExt);
    CHECK(mixed.toUpper_ascii() == upper);
    CHECK(mixed.toUpper_asciiExt() == upperExt);

    omw::string s = mixed;
    s.lower_ascii();
    CHECK(s == lower);
    s = mixed;
    s.lower_asciiExt();
    CHECK(s == lowerExt);
    s = mixed;
    s.upper_ascii();
    CHECK(s == upper);
    s = mixed;
    s.upper_asciiExt();
    CHECK(s == upperExt);
}

TEST_CASE("string.h omw::string URL encoded")
{
    const std::string str = "+\"*%&/()=asdf(fdsf)";
    const std::string enc = "%2B%22%2A%25%26%2F%28%29%3Dasdf%28fdsf%29";

    omw::string s1(str);
    s1.encodeUrl();

    const omw::string s2(str);

    CHECK(s1 == enc);
    CHECK(s2.toUrlEncoded() == enc);
    CHECK(s1.toUrlEncoded() == "%252B%2522%252A%2525%2526%252F%2528%2529%253Dasdf%2528fdsf%2529");
}

TEST_CASE("string.h to_string()")
{
    CHECK(omw::to_string(false, false) == "0");
    CHECK(omw::to_string(false, true) == "false");
    CHECK(omw::to_string(true, false) == "1");
    CHECK(omw::to_string(true, true) == "true");

    std::pair<int, int> pair1(-1, 123);
    CHECK(omw::to_string(pair1) == "-1;123");

    std::pair<double, double> pair2(3.14159265, 123);
    CHECK(omw::to_string(pair2, '/') == "3.141593/123.000000");
}

TEST_CASE("string.h stob()")
{
    CHECK(omw::stob("0") == false);
    CHECK(omw::stob("false") == false);
    CHECK(omw::stob("fAlsE") == false);
    CHECK(omw::stob("FALSE") == false);

    CHECK(omw::stob("1") == true);
    CHECK(omw::stob("true") == true);
    CHECK(omw::stob("TrUe") == true);
    CHECK(omw::stob("TRUE") == true);


    TESTUTIL_TRYCATCH_DECLARE_VAL(bool, true);
    TESTUTIL_TRYCATCH_CHECK(omw::stob("fsef"), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::stob("2"), std::out_of_range);
    TESTUTIL_TRYCATCH_CHECK(omw::stob("-1"), std::out_of_range);
}

TEST_CASE("string.h stoipair()")
{
    CHECK(std::pair<int32_t, int32_t>(-1, 123) == omw::stoipair("-1#123", '#'));

    typedef std::pair<int32_t, int32_t> ipair;
    TESTUTIL_TRYCATCH_DECLARE_VAL(ipair, ipair(0x11112, -1234));
    TESTUTIL_TRYCATCH_CHECK(omw::stoipair("-1 123"), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::stoipair(";123"), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::stoipair("123;"), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::stoipair(";"), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::stoipair("0;2200000000"), std::out_of_range);
    TESTUTIL_TRYCATCH_CHECK(omw::stoipair("2200000000;123"), std::out_of_range);
}

TEST_CASE("string.h toHexStr()")
{
    CHECK(omw::toHexStr((int8_t)0xBC) == "BC");
    CHECK(omw::toHexStr((uint8_t)0xBC) == "BC");
    CHECK(omw::toHexStr((int16_t)0x5678) == "5678");
    CHECK(omw::toHexStr((uint16_t)0x5678) == "5678");
    CHECK(omw::toHexStr((int32_t)0x89ABCDEF) == "89ABCDEF");
    CHECK(omw::toHexStr((uint32_t)0x89ABCDEF) == "89ABCDEF");
    CHECK(omw::toHexStr((int64_t)0x0123456789ABCDEF) == "0123456789ABCDEF");
    CHECK(omw::toHexStr((uint64_t)0x0123456789ABCDEF) == "0123456789ABCDEF");

    std::vector<char> vecC = { 0x30, 0x35, 'A', 'b' };
    CHECK(omw::toHexStr(vecC) == "30 35 41 62");
    CHECK(omw::toHexStr(vecC, '-') == "30-35-41-62");
    CHECK(omw::toHexStr(vecC.data(), vecC.size()) == "30 35 41 62");
    CHECK(omw::toHexStr(vecC.data(), vecC.size(), '-') == "30-35-41-62");

    std::vector<uint8_t> vecUC = { 0x30, 0x35, 'A', 'b' };
    CHECK(omw::toHexStr(vecUC) == "30 35 41 62");
    CHECK(omw::toHexStr(vecUC, '-') == "30-35-41-62");
    CHECK(omw::toHexStr(vecUC.data(), vecUC.size()) == "30 35 41 62");
    CHECK(omw::toHexStr(vecUC.data(), vecUC.size(), '-') == "30-35-41-62");
}

TEST_CASE("string.h hexstoi()")
{
    CHECK(omw::hexstoi("0") == 0);
    CHECK(omw::hexstoi("000") == 0);
    CHECK(omw::hexstoi("ff") == 255);
    CHECK(omw::hexstoi("FFffFFff") == -1);
    CHECK(omw::hexstoi("FFffFFfe") == -2);
    CHECK(omw::hexstoi("0FFffFFff") == -1);

    TESTUTIL_TRYCATCH_DECLARE_VAL(int32_t, 0x11112);
    TESTUTIL_TRYCATCH_CHECK(omw::hexstoi(""), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::hexstoi("0xF0"), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::hexstoi(" ff"), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::hexstoi("100000000"), std::out_of_range);
}

TEST_CASE("string.h hexstoui()")
{
    CHECK(omw::hexstoui("0") == 0);
    CHECK(omw::hexstoui("000") == 0);
    CHECK(omw::hexstoui("ff") == 255);
    CHECK(omw::hexstoui("FFffFFff") == 4294967295);
    CHECK(omw::hexstoui("FFffFFfe") == 4294967294);
    CHECK(omw::hexstoui("0FFffFFff") == 4294967295);

    TESTUTIL_TRYCATCH_DECLARE_VAL(uint32_t, 0x11112);
    TESTUTIL_TRYCATCH_CHECK(omw::hexstoui(""), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::hexstoui("0xF0"), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::hexstoui(" ff"), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::hexstoui("100000000"), std::out_of_range);
}

TEST_CASE("string.h hexstoi64()")
{
    CHECK(omw::hexstoi64("0") == 0);
    CHECK(omw::hexstoi64("000") == 0);
    CHECK(omw::hexstoi64("ff") == 255);
    CHECK(omw::hexstoi64("FFffFFff") == 4294967295);
    CHECK(omw::hexstoi64("FFffFFfe") == 4294967294);
    CHECK(omw::hexstoi64("ffffFFFFffffFFFF") == -1);
    CHECK(omw::hexstoi64("ffffFFFFffffFFFe") == -2);
    CHECK(omw::hexstoi64("0ffffFFFFffffFFFF") == -1);

    TESTUTIL_TRYCATCH_DECLARE_VAL(int64_t, 0x11112);
    TESTUTIL_TRYCATCH_CHECK(omw::hexstoi64(""), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::hexstoi64("0xF0"), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::hexstoi64(" ff"), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::hexstoi64("10000000000000000"), std::out_of_range);
}

TEST_CASE("string.h hexstoui64()")
{
    CHECK(omw::hexstoui64("0") == 0);
    CHECK(omw::hexstoui64("000") == 0);
    CHECK(omw::hexstoui64("ff") == 255);
    CHECK(omw::hexstoui64("FFffFFff") == 4294967295);
    CHECK(omw::hexstoui64("FFffFFfe") == 4294967294);
    CHECK(omw::hexstoui64("ffffFFFFffffFFFF") == 18446744073709551615);
    CHECK(omw::hexstoui64("ffffFFFFffffFFFe") == 18446744073709551614);
    CHECK(omw::hexstoui64("0ffffFFFFffffFFFF") == 18446744073709551615);

    TESTUTIL_TRYCATCH_DECLARE_VAL(uint64_t, 0x11112);
    TESTUTIL_TRYCATCH_CHECK(omw::hexstoui64(""), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::hexstoui64("0xF0"), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::hexstoui64(" ff"), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::hexstoui64("10000000000000000"), std::out_of_range);
}

TEST_CASE("string.h hexstovector()")
{
    const std::vector<uint8_t> vector = { 0x00, 0x05, 0xA5, 'c', 'B' };
    CHECK(omw::hexstovector("00 05 a5 63 42") == vector);
    CHECK(omw::hexstovector("00-05-a5-63-42", '-') == vector);
    CHECK(omw::hexstovector("0 5 a5 63 042") == vector);

    const std::vector<uint8_t> initialVector = { 0 };
    TESTUTIL_TRYCATCH_DECLARE_VAL(std::vector<uint8_t>, initialVector);
    TESTUTIL_TRYCATCH_CHECK(omw::hexstovector("00 05 a5 63-42"), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::hexstovector("00 05 a5 100 42"), std::out_of_range);
}

TEST_CASE("string.h isInteger()")
{
    CHECK(omw::isInteger("a123") == false);
    CHECK(omw::isInteger("a") == false);
    CHECK(omw::isInteger("abc") == false);
    CHECK(omw::isInteger("-") == false);
    CHECK(omw::isInteger("-abc") == false);
    CHECK(omw::isInteger("123abc") == false);
    CHECK(omw::isInteger("-123abc") == false);
    CHECK(omw::isInteger("0") == true);
    CHECK(omw::isInteger("-0") == true);
    CHECK(omw::isInteger("-1") == true);
    CHECK(omw::isInteger("-123") == true);
    CHECK(omw::isInteger("1") == true);
    CHECK(omw::isInteger("123") == true);

    CHECK(omw::isUInteger("a123") == false);
    CHECK(omw::isUInteger("a") == false);
    CHECK(omw::isUInteger("abc") == false);
    CHECK(omw::isUInteger("-") == false);
    CHECK(omw::isUInteger("-abc") == false);
    CHECK(omw::isUInteger("123abc") == false);
    CHECK(omw::isUInteger("-123abc") == false);
    CHECK(omw::isUInteger("0") == true);
    CHECK(omw::isUInteger("-0") == false);
    CHECK(omw::isUInteger("-1") == false);
    CHECK(omw::isUInteger("-123") == false);
    CHECK(omw::isUInteger("1") == true);
    CHECK(omw::isUInteger("123") == true);
}

TEST_CASE("string.h isHex()")
{
    CHECK(omw::isHex("3F") == true);
    CHECK(omw::isHex("3F5") == true);
    CHECK(omw::isHex("0123456789ABCDEF") == true);
    CHECK(omw::isHex("0123456789abcdef") == true);
    CHECK(omw::isHex("0123456789ABCDEF0123") == true);

    CHECK(omw::isHex("") == false);
    CHECK(omw::isHex("0x3F") == false);

    for (int c = 0; c <= 0xFF; ++c)
    {
        const char hexStr[] = { '5', 'a', (char)c, 0 };
        bool expectedResult;

        if (((c >= '0') && (c <= '9')) ||
            ((c >= 'A') && (c <= 'F')) ||
            ((c >= 'a') && (c <= 'f')) ||
            (c == 0))
        {
            expectedResult = true;
        }
        else expectedResult = false;

        CHECK(omw::isHex(hexStr) == expectedResult);
    }
}



#endif // TEST_OMW_STRING_H
