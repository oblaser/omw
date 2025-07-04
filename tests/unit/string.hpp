/*
author          Oliver Blaser
copyright       MIT - Copyright (c) 2023 Oliver Blaser
*/

#ifndef TEST_OMW_STRING_H
#define TEST_OMW_STRING_H

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <string>
#include <vector>

#include "catch2/catch.hpp"
#include "testUtil.h"

#include <omw/int.h>
#include <omw/string.h>



TEST_CASE("string.h omw::StringVector")
{
    static_assert(sizeof(omw::StringVector_npos) == sizeof(size_t), "weired!?");
    CHECK(omw::StringVector_npos == SIZE_MAX);
}



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



TEST_CASE("string.h omw::contains()")
{
    char chr;
    const char* ptr;
    std::string str;
    std::string omwstr;

    const std::string s("The quick brown fox jumps over the lazy dog");

    chr = 'q';
    ptr = "ox j";
    str = "The q";
    omwstr = "ck bro";
    CHECK(omw::contains(s, chr));
    CHECK(omw::contains(s, ptr));
    CHECK(omw::contains(s, str));
    CHECK(omw::contains(s, omwstr));

    chr = 'x';
    ptr = "jump";
    str = "az";
    omwstr = "ps ove";
    CHECK(omw::contains(s, chr));
    CHECK(omw::contains(s, ptr));
    CHECK(omw::contains(s, str));
    CHECK(omw::contains(s, omwstr));

    chr = '-';
    ptr = "mobile";
    str = "cellphone";
    omwstr = "case";
    CHECK_FALSE(omw::contains(s, chr));
    CHECK_FALSE(omw::contains(s, ptr));
    CHECK_FALSE(omw::contains(s, str));
    CHECK_FALSE(omw::contains(s, omwstr));
}

TEST_CASE("string.h omw::replaceFirst()")
{
    const char str[] = "a boy with a hat";
    std::string s;

    s = str;
    omw::replaceFirst(s, "t", "#");
    CHECK(s == "a boy wi#h a hat");
    omw::replaceFirst(s, "t", "#");
    CHECK(s == "a boy wi#h a ha#");

    s = str;
    omw::replaceFirst(s, "t", "#", 9);
    CHECK(s == "a boy with a ha#");

    s = str;
    omw::replaceFirst(s, omw::StringReplacePair('t', "[?]"), 9);
    CHECK(s == "a boy with a ha[?]");



    s = str;
    omw::replaceFirst(s, "", "$");
    CHECK(s == "$a boy with a hat");

    s = str;
    omw::replaceFirst(s, "t", "");
    CHECK(s == "a boy wih a hat");

    s = str;
    omw::replaceFirst(s, "", "");
    CHECK(s == "a boy with a hat");
}

TEST_CASE("string.h omw::replaceAll()")
{
    const char str[] = "a boy with a hat";
    std::string s;
    size_t nReplacements;

#ifndef ___OMWi_REGION_char_char
    s = str;
    omw::replaceAll(s, 'a', 'X', 0, &nReplacements);
    CHECK(s == "X boy with X hXt");
    CHECK(nReplacements == 3);

    s = str;
    omw::replaceAll(s, 'a', 'X', 5, &nReplacements);
    CHECK(s == "a boy with X hXt");
    CHECK(nReplacements == 2);

    s = str;
    omw::replaceAll(s, 'q', '#', 1, &nReplacements);
    CHECK(s == str);
    CHECK(nReplacements == 0);


    s = str;
    omw::replaceAll(s, '\0', '#', 0, &nReplacements);
    CHECK(s == str);
    CHECK(nReplacements == 0);

    s = str;
    omw::replaceAll(s, 't', '\0', 0, &nReplacements);
    CHECK(s == std::string("a boy wi\0h a ha\0", std::strlen(str)));
    CHECK(nReplacements == 2);
#endif // ___OMWi_REGION_char_char

#ifndef ___OMWi_REGION_char_string
    s = str;
    omw::replaceAll(s, 'a', "XYZ ", 0, &nReplacements);
    CHECK(s == "XYZ  boy with XYZ  hXYZ t");
    CHECK(nReplacements == 3);

    s = str;
    omw::replaceAll(s, 'a', "XYZ ", 5, &nReplacements);
    CHECK(s == "a boy with XYZ  hXYZ t");
    CHECK(nReplacements == 2);

    s = str;
    omw::replaceAll(s, 'q', "#", 1, &nReplacements);
    CHECK(s == str);
    CHECK(nReplacements == 0);


    s = str;
    omw::replaceAll(s, '\0', "$", 0, &nReplacements);
    CHECK(s == str);
    CHECK(nReplacements == 0);

    s = str;
    omw::replaceAll(s, 't', "", 0, &nReplacements);
    CHECK(s == "a boy wih a ha");
    CHECK(nReplacements == 2);
#endif // ___OMWi_REGION_char_string

#ifndef ___OMWi_REGION_string_char
    s = str;
    omw::replaceAll(s, "a ", 'X', 0, &nReplacements);
    CHECK(s == "Xboy with Xhat");
    CHECK(nReplacements == 2);

    s = str;
    omw::replaceAll(s, "a ", 'X', 5, &nReplacements);
    CHECK(s == "a boy with Xhat");
    CHECK(nReplacements == 1);

    s = str;
    omw::replaceAll(s, "ABCDEFGHI", '#', 1, &nReplacements);
    CHECK(s == str);
    CHECK(nReplacements == 0);


    s = str;
    omw::replaceAll(s, "", '$', 0, &nReplacements);
    CHECK(s == str);
    CHECK(nReplacements == std::string::npos);

    s = str;
    omw::replaceAll(s, "t", '\0', 0, &nReplacements);
    CHECK(s == std::string("a boy wi\0h a ha\0", std::strlen(str)));
    CHECK(nReplacements == 2);
#endif // ___OMWi_REGION_string_char

#ifndef ___OMWi_REGION_string_string
    s = str;
    omw::replaceAll(s, "a ", "XYZ ", 0, &nReplacements);
    CHECK(s == "XYZ boy with XYZ hat");
    CHECK(nReplacements == 2);

    s = str;
    omw::replaceAll(s, "a ", "XYZ ", 5, &nReplacements);
    CHECK(s == "a boy with XYZ hat");
    CHECK(nReplacements == 1);

    s = str;
    omw::replaceAll(s, "ABCDEFGHI", "#", 1, &nReplacements);
    CHECK(s == str);
    CHECK(nReplacements == 0);

    s = str;
    omw::replaceAll(s, omw::StringReplacePair('a', "XYZ"), 11, &nReplacements);
    CHECK(s == "a boy with XYZ hXYZt");
    CHECK(nReplacements == 2);


    s = str;
    omw::replaceAll(s, "", "$", 0, &nReplacements);
    CHECK(s == str);
    CHECK(nReplacements == std::string::npos);

    s = str;
    omw::replaceAll(s, "t", "", 0, &nReplacements);
    CHECK(s == "a boy wih a ha");
    CHECK(nReplacements == 2);

    s = str;
    omw::replaceAll(s, "", "", 0, &nReplacements);
    CHECK(s == str);
    CHECK(nReplacements == std::string::npos);

    s = str;
    omw::replaceAll(s, "", "", 3, &nReplacements);
    CHECK(s == str);
    CHECK(nReplacements == std::string::npos);
#endif // ___OMWi_REGION_string_string


    const omw::StringReplacePair rp1('a', "#t#");
    const omw::StringReplacePair rp2('t', "# #");
    const omw::StringReplacePair rp3("##", '$');

    std::vector<omw::StringReplacePair> rpv;
    std::vector<size_t> nrv;

    rpv = { rp1, rp2, rp3 };

    s = str;
    omw::replaceAll(s, rpv);
    CHECK(s == "$ $ boy wi# #h $ $ h$ $# #");

    s = str;
    omw::replaceAll(s, rpv, 0, &nReplacements, &nrv);
    CHECK(s == "$ $ boy wi# #h $ $ h$ $# #");
    CHECK(nReplacements == 14);
    CHECK(nrv == std::vector<size_t>({ 3, 5, 6 }));

    s = str;
    omw::replaceAll(s, rpv, 10, &nReplacements, &nrv);
    CHECK(s == "a boy with $ $ h$ $# #");
    CHECK(nReplacements == 9);
    CHECK(nrv == std::vector<size_t>({ 2, 3, 4 }));

    s = str;
    omw::replaceAll(s, rpv, 10, &nReplacements);
    CHECK(s == "a boy with $ $ h$ $# #");
    CHECK(nReplacements == 9);

    s = str;
    omw::replaceAll(s, rpv, 0, nullptr, &nrv);
    CHECK(s == "$ $ boy wi# #h $ $ h$ $# #");
    CHECK(nrv == std::vector<size_t>({ 3, 5, 6 }));



    rpv = { rp3, rp2, rp1 };
    s = str;
    omw::replaceAll(s, rpv, 10);
    CHECK(s == "a boy with #t# h#t## #");



    rpv = { rp3, omw::StringReplacePair("ABCDEFGHI", "#"), omw::StringReplacePair("XYZ", "@") };
    s = str;
    omw::replaceAll(s, rpv, 0, &nReplacements, &nrv);
    CHECK(s == str);
    CHECK(nReplacements == 0);
    CHECK(nrv == std::vector<size_t>({ 0, 0, 0 }));

    rpv = { rp3, omw::StringReplacePair("", "#"), omw::StringReplacePair("", "@") };
    s = str;
    omw::replaceAll(s, rpv, 0, &nReplacements, &nrv);
    CHECK(s == str);
    CHECK(nReplacements == 0);
    CHECK(nrv == std::vector<size_t>({ 0, std::string::npos, std::string::npos }));

    rpv = { omw::StringReplacePair("", "#"), omw::StringReplacePair("", "@"), omw::StringReplacePair("", "$") };
    s = str;
    omw::replaceAll(s, rpv, 0, &nReplacements, &nrv);
    CHECK(s == str);
    CHECK(nReplacements == std::string::npos);
    CHECK(nrv == std::vector<size_t>({ std::string::npos, std::string::npos, std::string::npos }));
}

TEST_CASE("string.h omw::reverse()")
{
    std::string s;

    s = "abcd";
    omw::reverse(s);
    CHECK(s == "dcba");

    s = "QWERT";
    omw::reverse(s);
    CHECK(s == "TREWQ");
}

TEST_CASE("string.h omw::toReversed()")
{
    std::string s;
    const std::string& cr = s;

    s = "abcd";
    CHECK(omw::toReversed(cr) == "dcba");

    s = "QWERT";
    CHECK(omw::toReversed(cr) == "TREWQ");
}

TEST_CASE("string.h omw::split()")
{
    const std::string s("The quick brown fox jumps over the lazy dog");
    omw::StringVector t;
    size_t n;

    t = omw::split(s, ' ');
    n = 9;
    REQUIRE(t.size() == n);
    CHECK(t[0] == "The");
    CHECK(t[1] == "quick");
    CHECK(t[2] == "brown");
    CHECK(t[3] == "fox");
    CHECK(t[4] == "jumps");
    CHECK(t[5] == "over");
    CHECK(t[6] == "the");
    CHECK(t[7] == "lazy");
    CHECK(t[8] == "dog");

    t = omw::split(s, ' ', 0);
    n = 0;
    REQUIRE(t.size() == n);

    t = omw::split(s, ' ', 5);
    n = 5;
    REQUIRE(t.size() == n);
    CHECK(t[0] == "The");
    CHECK(t[1] == "quick");
    CHECK(t[2] == "brown");
    CHECK(t[3] == "fox");
    CHECK(t[4] == "jumps over the lazy dog");

    t = omw::split(s, 'o');
    n = 5;
    REQUIRE(t.size() == n);
    CHECK(t[0] == "The quick br");
    CHECK(t[1] == "wn f");
    CHECK(t[2] == "x jumps ");
    CHECK(t[3] == "ver the lazy d");
    CHECK(t[4] == "g");

    t = omw::split(s, 'T');
    n = 2;
    REQUIRE(t.size() == n);
    CHECK(t[0] == "");
    CHECK(t[1] == "he quick brown fox jumps over the lazy dog");
}

TEST_CASE("string.h omw::splitLen()")
{
    const std::string s("The quick brown fox jumps over the lazy dog");
    std::vector<std::string> t;
    size_t n;
    size_t tokenLen;

    n = 0;
    tokenLen = 3;
    t = omw::splitLen(s, tokenLen, 0);
    CHECK(t.size() == n);

    n = 43;
    tokenLen = 1;
    t = omw::splitLen(s, tokenLen);
    REQUIRE(t.size() == n);
    for (size_t i = 0; i < n; ++i)
    {
        REQUIRE(t[i].length() == 1);
        CHECK(t[i][0] == s[i]);
    }

    n = 43;
    tokenLen = 1;
    t = omw::splitLen(s, tokenLen, n);
    REQUIRE(t.size() == n);
    for (size_t i = 0; i < (n - 1); ++i)
    {
        REQUIRE(t[i].length() == 1);
        CHECK(t[i][0] == s[i]);
    }
    CHECK(t[(n - 1)] == "g");

    n = 38;
    tokenLen = 1;
    t = omw::splitLen(s, tokenLen, n);
    REQUIRE(t.size() == n);
    for (size_t i = 0; i < (n - 1); ++i)
    {
        REQUIRE(t[i].length() == 1);
        CHECK(t[i][0] == s[i]);
    }
    CHECK(t[(n - 1)] == "zy dog");

    n = 5;
    tokenLen = 2;
    t = omw::splitLen(s, tokenLen, n);
    REQUIRE(t.size() == n);
    for (size_t i = 0; i < (n - 1); ++i)
    {
        REQUIRE(t[i].length() == 2);
        CHECK(t[i][0] == s[i * 2 + 0]);
        CHECK(t[i][1] == s[i * 2 + 1]);
    }
    CHECK(t[(n - 1)] == "k brown fox jumps over the lazy dog");
}

TEST_CASE("string.h case conversion")
{
    const std::string mixed = "0123 ThE QuIcK BrOwN FoX JuMpS OvEr tHe lAzY DoG. 456 =\xC3\x84-\xC3\x96 * \xC3\x9C 789 \xC3\xA4\xC3\xB6\xC3\xBC#";
    const std::string lower = "0123 the quick brown fox jumps over the lazy dog. 456 =\xC3\x84-\xC3\x96 * \xC3\x9C 789 \xC3\xA4\xC3\xB6\xC3\xBC#";
    const std::string lowerExt = "0123 the quick brown fox jumps over the lazy dog. 456 =\xC3\xA4-\xC3\xB6 * \xC3\xBC 789 \xC3\xA4\xC3\xB6\xC3\xBC#";
    const std::string upper = "0123 THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG. 456 =\xC3\x84-\xC3\x96 * \xC3\x9C 789 \xC3\xA4\xC3\xB6\xC3\xBC#";
    const std::string upperExt = "0123 THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG. 456 =\xC3\x84-\xC3\x96 * \xC3\x9C 789 \xC3\x84\xC3\x96\xC3\x9C#";

    CHECK(omw::toLower_ascii(mixed) == lower);
    CHECK(omw::toLower_asciiExt(mixed) == lowerExt);
    CHECK(omw::toUpper_ascii(mixed) == upper);
    CHECK(omw::toUpper_asciiExt(mixed) == upperExt);

    std::string s = mixed;
    omw::lower_ascii(s);
    CHECK(s == lower);

    s = mixed;
    omw::lower_asciiExt(s);
    CHECK(s == lowerExt);

    s = mixed;
    omw::upper_ascii(s);
    CHECK(s == upper);

    s = mixed;
    omw::upper_asciiExt(s);
    CHECK(s == upperExt);
}

TEST_CASE("string.h toString()")
{
    const int32_t i32 = -1234567890;
    const uint32_t ui32 = 1234567890;
    const int64_t i64 = -1234567890123456;
    const uint64_t ui64 = 1234567890123456;
    const float f = 1.41421f;
    const double d = 2.71828;
    const long double ld = 3.14159l;

    CHECK(omw::toString(i32) == std::to_string(i32));
    CHECK(omw::toString(ui32) == std::to_string(ui32));
    CHECK(omw::toString(i64) == std::to_string(i64));
    CHECK(omw::toString(ui64) == std::to_string(ui64));
    CHECK(omw::toString(0xFFFFFFFFFFFFFFFF) == std::to_string(0xFFFFFFFFFFFFFFFF));
    CHECK(omw::toString(f) == std::to_string(f));
    CHECK(omw::toString(d) == std::to_string(d));
    CHECK(omw::toString(ld) == std::to_string(ld));



    CHECK(omw::toString(omw::int128_t(0)) == "0");
    CHECK(omw::toString(omw::uint128_t(0)) == "0");
    CHECK(omw::toString(omw::int128_t(i32)) == std::to_string(i32));
    CHECK(omw::toString(omw::uint128_t(ui32)) == std::to_string(ui32));
    CHECK(omw::toString(omw::int128_t(i64)) == std::to_string(i64));
    CHECK(omw::toString(omw::uint128_t(ui64)) == std::to_string(ui64));
    CHECK(omw::toString(omw::int128_t(0xFFFFFFFFFFFFFFFF)) == "-1");
    CHECK(omw::toString(omw::uint128_t(0xFFFFFFFFFFFFFFFF)) == "340282366920938463463374607431768211455");

    CHECK(omw::toString(omw::int128_t(1, 0)) == "18446744073709551616");
    CHECK(omw::toString(omw::int128_t(0, 0xFFFFFFFFFFFFFFFF)) == "18446744073709551615");
    CHECK(omw::toString(omw::int128_t(0x7FFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF)) == "170141183460469231731687303715884105727");
    CHECK(omw::toString(omw::int128_t(0x8000000000000000, 0)) == "-170141183460469231731687303715884105728");
    CHECK(omw::toString(omw::int128_t(0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF)) == "-1");

    CHECK(omw::toString(omw::uint128_t(1, 0)) == "18446744073709551616");
    CHECK(omw::toString(omw::uint128_t(0, 0xFFFFFFFFFFFFFFFF)) == "18446744073709551615");
    CHECK(omw::toString(omw::uint128_t(0x7FFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF)) == "170141183460469231731687303715884105727");
    CHECK(omw::toString(omw::uint128_t(0x8000000000000000, 0)) == "170141183460469231731687303715884105728");
    CHECK(omw::toString(omw::uint128_t(0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF)) == "340282366920938463463374607431768211455");



    CHECK(omw::toString(false) == "false");
    CHECK(omw::toString(true) == "true");
    CHECK(omw::toString(false, false) == "0");
    CHECK(omw::toString(false, true) == "false");
    CHECK(omw::toString(true, false) == "1");
    CHECK(omw::toString(true, true) == "true");



    std::pair<int, int> pair1(-1, 123);
    CHECK(omw::toString(pair1) == "-1;123");

    std::pair<double, double> pair2(3.14159265, 123);
    CHECK(omw::toString(pair2, '/') == "3.141593/123.000000");
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

TEST_CASE("string.h stoz()")
{
    TESTUTIL_TRYCATCH_DECLARE_VAL(size_t, 45678);

    if (sizeof(size_t) == 4)
    {
        CHECK(omw::stoz("0") == 0);
        CHECK(omw::stoz("   123asdf") == 123);
        CHECK(omw::stoz("4294967295") == UINT32_MAX);
        CHECK(omw::stoz("4294967295") == SIZE_MAX);

        TESTUTIL_TRYCATCH_CHECK(omw::stoz("asdf"), std::invalid_argument);
        TESTUTIL_TRYCATCH_CHECK(omw::stoz("-170141183460469231731687303715884105728"), std::out_of_range);
        TESTUTIL_TRYCATCH_CHECK(omw::stoz("-9223372036854775809"), std::out_of_range);
        TESTUTIL_TRYCATCH_CHECK(omw::stoz("-9223372036854775808"), std::out_of_range);
        TESTUTIL_TRYCATCH_CHECK(omw::stoz("  -456asdf"), std::out_of_range);
        TESTUTIL_TRYCATCH_CHECK(omw::stoz("-1"), std::out_of_range);
        TESTUTIL_TRYCATCH_CHECK(omw::stoz("4294967296"), std::out_of_range);
        TESTUTIL_TRYCATCH_CHECK(omw::stoz("18446744073709551615"), std::out_of_range);
        TESTUTIL_TRYCATCH_CHECK(omw::stoz("18446744073709551616"), std::out_of_range);
    }
    else if (sizeof(size_t) == 8)
    {
        CHECK(omw::stoz("0") == 0);
        CHECK(omw::stoz("   123asdf") == 123);
        CHECK(omw::stoz("18446744073709551615") == UINT64_MAX);
        CHECK(omw::stoz("18446744073709551615") == SIZE_MAX);

        TESTUTIL_TRYCATCH_CHECK(omw::stoz("asdf"), std::invalid_argument);
        TESTUTIL_TRYCATCH_CHECK(omw::stoz("-170141183460469231731687303715884105728"), std::out_of_range);
        TESTUTIL_TRYCATCH_CHECK(omw::stoz("-9223372036854775809"), std::out_of_range);
        TESTUTIL_TRYCATCH_CHECK(omw::stoz("-9223372036854775808"), std::out_of_range);
        TESTUTIL_TRYCATCH_CHECK(omw::stoz("  -456asdf"), std::out_of_range);
        TESTUTIL_TRYCATCH_CHECK(omw::stoz("-1"), std::out_of_range);
        TESTUTIL_TRYCATCH_CHECK(omw::stoz("18446744073709551616"), std::out_of_range);
        TESTUTIL_TRYCATCH_CHECK(omw::stoz("340282366920938463463374607431768211455"), std::out_of_range);
    }
    else { CHECK(false); }
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
    TESTUTIL_TRYCATCH_CHECK(omw::stoipair("abc;123"), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::stoipair("123;abc"), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::stoipair(";abc"), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::stoipair("abc"), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::stoipair("1234"), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::stoipair("0;2200000000"), std::out_of_range);
    TESTUTIL_TRYCATCH_CHECK(omw::stoipair("2200000000;123"), std::out_of_range);
}

TEST_CASE("string.h stodpair()")
{
    CHECK(std::pair<double, double>(-1.567, 123) == omw::stodpair("-1.567#123", '#'));

    // TODO check max integer in double (9007199254740991 ?)



    const auto maxStr = std::to_string(std::stod("1.7976931348623157e+308")); // abs(min) = abs(max) so only max is needed

    typedef std::pair<double, double> dpair;
    TESTUTIL_TRYCATCH_DECLARE_VAL(dpair, dpair(0.1234, -1.234));
    TESTUTIL_TRYCATCH_CHECK(omw::stodpair("-1 123"), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::stodpair(";123"), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::stodpair("123;"), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::stodpair(";"), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::stoipair("abc;123"), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::stoipair("123;abc"), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::stoipair(";abc"), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::stoipair("abc"), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::stoipair("1234"), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::stodpair("0;1" + maxStr), std::out_of_range);
    TESTUTIL_TRYCATCH_CHECK(omw::stodpair("-1" + maxStr + ";123"), std::out_of_range);
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
    CHECK(omw::toHexStr(omw::int128_t(0x987654321015157A, 0x0123456789ABCDEF)) == "987654321015157A0123456789ABCDEF");
    CHECK(omw::toHexStr(omw::uint128_t(0x987654321015157A, 0x0123456789ABCDEF)) == "987654321015157A0123456789ABCDEF");

    CHECK(omw::toHexStr((int16_t)0x5678, '-') == "56-78");
    CHECK(omw::toHexStr((uint16_t)0x5678, ' ') == "56 78");
    CHECK(omw::toHexStr((int32_t)0x89ABCDEF, ' ') == "89 AB CD EF");
    CHECK(omw::toHexStr((uint32_t)0x89ABCDEF, '+') == "89+AB+CD+EF");
    CHECK(omw::toHexStr((int64_t)0x0123456789ABCDEF, 't') == "01t23t45t67t89tABtCDtEF");
    CHECK(omw::toHexStr((uint64_t)0x0123456789ABCDEF, '-') == "01-23-45-67-89-AB-CD-EF");
    CHECK(omw::toHexStr(omw::int128_t(0x987654321015157A, 0x0123456789ABCDEF), '-') == "98-76-54-32-10-15-15-7A-01-23-45-67-89-AB-CD-EF");
    CHECK(omw::toHexStr(omw::uint128_t(0x987654321015157A, 0x0123456789ABCDEF), '-') == "98-76-54-32-10-15-15-7A-01-23-45-67-89-AB-CD-EF");

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

    TESTUTIL_TRYCATCH_DECLARE_VAL(int32_t, 0x11112);
    TESTUTIL_TRYCATCH_CHECK(omw::hexstoi(""), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::hexstoi("0xF0"), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::hexstoi(" ff"), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::hexstoi("0FFffFFff"), std::out_of_range);
    TESTUTIL_TRYCATCH_CHECK(omw::hexstoi("100000000"), std::out_of_range);
    TESTUTIL_TRYCATCH_CHECK(omw::hexstoi("0x100000000"), std::invalid_argument);
}

TEST_CASE("string.h hexstoui()")
{
    CHECK(omw::hexstoui("0") == 0);
    CHECK(omw::hexstoui("000") == 0);
    CHECK(omw::hexstoui("ff") == 255);
    CHECK(omw::hexstoui("FFffFFff") == 4294967295);
    CHECK(omw::hexstoui("FFffFFfe") == 4294967294);

    TESTUTIL_TRYCATCH_DECLARE_VAL(uint32_t, 0x11112);
    TESTUTIL_TRYCATCH_CHECK(omw::hexstoui(""), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::hexstoui("0xF0"), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::hexstoui(" ff"), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::hexstoui("0FFffFFff"), std::out_of_range);
    TESTUTIL_TRYCATCH_CHECK(omw::hexstoui("100000000"), std::out_of_range);
    TESTUTIL_TRYCATCH_CHECK(omw::hexstoui("0x100000000"), std::invalid_argument);
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

    TESTUTIL_TRYCATCH_DECLARE_VAL(int64_t, 0x11112);
    TESTUTIL_TRYCATCH_CHECK(omw::hexstoi64(""), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::hexstoi64("0xF0"), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::hexstoi64(" ff"), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::hexstoi64("0ffffFFFFffffFFFF"), std::out_of_range);
    TESTUTIL_TRYCATCH_CHECK(omw::hexstoi64("10000000000000000"), std::out_of_range);
    TESTUTIL_TRYCATCH_CHECK(omw::hexstoi64("0x10000000000000000"), std::invalid_argument);
}

TEST_CASE("string.h hexstoui64()")
{
    CHECK(omw::hexstoui64("0") == 0);
    CHECK(omw::hexstoui64("000") == 0);
    CHECK(omw::hexstoui64("ff") == 255);
    CHECK(omw::hexstoui64("FFffFFff") == 4294967295);
    CHECK(omw::hexstoui64("FFffFFfe") == 4294967294);
    CHECK(omw::hexstoui64("ffffFFFFffffFFFF") == 18446744073709551615u);
    CHECK(omw::hexstoui64("ffffFFFFffffFFFe") == 18446744073709551614u);

    TESTUTIL_TRYCATCH_DECLARE_VAL(uint64_t, 0x11112);
    TESTUTIL_TRYCATCH_CHECK(omw::hexstoui64(""), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::hexstoui64("0xF0"), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::hexstoui64(" ff"), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::hexstoui64("0ffffFFFFffffFFFF"), std::out_of_range);
    TESTUTIL_TRYCATCH_CHECK(omw::hexstoui64("10000000000000000"), std::out_of_range);
    TESTUTIL_TRYCATCH_CHECK(omw::hexstoui64("0x10000000000000000"), std::invalid_argument);
}

TEST_CASE("string.h hexstoi128()")
{
    CHECK(omw::hexstoi128("0") == omw::int128_t(0, 0));
    CHECK(omw::hexstoi128("000") == omw::int128_t(0, 0));
    CHECK(omw::hexstoi128("ff") == omw::int128_t(0, 255));
    CHECK(omw::hexstoi128("FFffFFff") == omw::int128_t(0, 4294967295));
    CHECK(omw::hexstoi128("FFffFFfe") == omw::int128_t(0, 4294967294));
    CHECK(omw::hexstoi128("ffffFFFFffffFFFF") == omw::int128_t(0, -1));
    CHECK(omw::hexstoi128("ffffFFFFffffFFFe") == omw::int128_t(0, -2));
    CHECK(omw::hexstoi128("000ffffFFFFffffFFFF") == omw::int128_t(0, -1));
    CHECK(omw::hexstoi128("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF") == omw::int128_t(-1, -1));
    CHECK(omw::hexstoi128("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFe") == omw::int128_t(-1, -2));

    TESTUTIL_TRYCATCH_DECLARE_VAL(omw::int128_t, 0x11112);
    TESTUTIL_TRYCATCH_CHECK(omw::hexstoi128(""), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::hexstoi128("0xF0"), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::hexstoi128(" ff"), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::hexstoi128("0FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF"), std::out_of_range);
    TESTUTIL_TRYCATCH_CHECK(omw::hexstoi128("100000000000000000000000000000000"), std::out_of_range);
    TESTUTIL_TRYCATCH_CHECK(omw::hexstoi128("0x100000000000000000000000000000000"), std::invalid_argument);
}

TEST_CASE("string.h hexstoui128()")
{
    CHECK(omw::hexstoui128("0") == omw::uint128_t(0, 0));
    CHECK(omw::hexstoui128("000") == omw::uint128_t(0, 0));
    CHECK(omw::hexstoui128("ff") == omw::uint128_t(0, 255));
    CHECK(omw::hexstoui128("FFffFFff") == omw::uint128_t(0, 4294967295));
    CHECK(omw::hexstoui128("FFffFFfe") == omw::uint128_t(0, 4294967294));
    CHECK(omw::hexstoui128("ffffFFFFffffFFFF") == omw::uint128_t(0, -1));
    CHECK(omw::hexstoui128("ffffFFFFffffFFFe") == omw::uint128_t(0, -2));
    CHECK(omw::hexstoui128("000ffffFFFFffffFFFF") == omw::uint128_t(0, -1));
    CHECK(omw::hexstoui128("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF") == omw::uint128_t(-1, -1));
    CHECK(omw::hexstoui128("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFe") == omw::uint128_t(-1, -2));

    TESTUTIL_TRYCATCH_DECLARE_VAL(omw::uint128_t, 0x11112);
    TESTUTIL_TRYCATCH_CHECK(omw::hexstoui128(""), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::hexstoui128("0xF0"), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::hexstoui128(" ff"), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::hexstoui128("0FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF"), std::out_of_range);
    TESTUTIL_TRYCATCH_CHECK(omw::hexstoui128("100000000000000000000000000000000"), std::out_of_range);
    TESTUTIL_TRYCATCH_CHECK(omw::hexstoui128("0x100000000000000000000000000000000"), std::invalid_argument);
}

TEST_CASE("string.h hexstovector()")
{
    const std::vector<uint8_t> vector = { 0x00, 0x05, 0xA5, 'c', 'B' };
    CHECK(omw::hexstovector("00 05 a5 63 42") == vector);
    CHECK(omw::hexstovector("0005a56342", 0) == vector);
    CHECK(omw::hexstovector("00-05-a5-63-42", '-') == vector);
    CHECK(omw::hexstovector("0 5 a5 63 042") == vector);

    const std::vector<uint8_t> initialVector = { 0 };
    TESTUTIL_TRYCATCH_DECLARE_VAL(std::vector<uint8_t>, initialVector);
    TESTUTIL_TRYCATCH_CHECK(omw::hexstovector("00.05.a5.63-42", '.'), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::hexstovector("00.05.a5.63+42", '.'), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::hexstovector("00.05.a5$63.42", '.'), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::hexstovector("00.05.a5.100.42", '.'), std::out_of_range);
}

TEST_CASE("string.h sepHexStr()")
{
    const char* const r_sp = "01 23 ab 45 cd 67 ef 89";
    const char* const r_hy = "01-23-ab-45-cd-67-ef-89";

    const char* h_p;
    std::string h_std;

    h_p = "0123ab45cd67ef89";
    h_std = h_p;
    CHECK(omw::sepHexStr(h_p) == r_sp);
    CHECK(omw::sepHexStr(h_std) == r_sp);
    CHECK(omw::sepHexStr(h_p, '-') == r_hy);
    CHECK(omw::sepHexStr(h_std, '-') == r_hy);

    h_p = "123ab45cd67ef89";
    h_std = h_p;
    CHECK(omw::sepHexStr(h_p) == r_sp);
    CHECK(omw::sepHexStr(h_std) == r_sp);
    CHECK(omw::sepHexStr(h_p, '-') == r_hy);
    CHECK(omw::sepHexStr(h_std, '-') == r_hy);

    h_p = "012*3ab45cd67ef*8*9";
    h_std = h_p;
    CHECK(omw::sepHexStr(h_p, '*', omw::toHexStr_defaultDelimiter) == r_sp);
    CHECK(omw::sepHexStr(h_std, '*', omw::toHexStr_defaultDelimiter) == r_sp);
    CHECK(omw::sepHexStr(h_p, '*', '-') == r_hy);
    CHECK(omw::sepHexStr(h_std, '*', '-') == r_hy);

    const char* const rmChars = "*-o";
    h_p = "0-12*3ab45-cdo67ef*8*9";
    h_std = h_p;
    CHECK(omw::sepHexStr(h_p, rmChars, 3) == r_sp);
    CHECK(omw::sepHexStr(h_std, rmChars, 3) == r_sp);
    CHECK(omw::sepHexStr(h_p, rmChars, 3, '-') == r_hy);
    CHECK(omw::sepHexStr(h_std, rmChars, 3, '-') == r_hy);

    const std::vector<char> rmChrV(rmChars, rmChars + 3);
    CHECK(omw::sepHexStr(h_p, rmChrV) == r_sp);
    CHECK(omw::sepHexStr(h_std, rmChrV) == r_sp);
    CHECK(omw::sepHexStr(h_p, rmChrV, '-') == r_hy);
    CHECK(omw::sepHexStr(h_std, rmChrV, '-') == r_hy);

    CHECK(omw::sepHexStr(h_p, "*-o/&%", 6) == r_sp);
    CHECK_FALSE(omw::sepHexStr(h_p, "*-oa", 4) == r_sp);
}

TEST_CASE("string.h rmNonHex()")
{
    const std::string result = "adfe";

    {
        const char cbuffer[] = "asdf&qwertz-";
        const char* cp = cbuffer;
        const std::string cs = cp;
        CHECK(omw::rmNonHex(cp) == result);
        CHECK(omw::rmNonHex(cs) == result);

        char buffer[] = "asdf&qwertz-";
        char* p = buffer;
        std::string s = p;
        omw::rmNonHex(p);
        omw::rmNonHex(s);
        CHECK(result == buffer);
        CHECK(s == result);
    }

    {
        const char cbuffer[] = "adfe";
        const char* cp = cbuffer;
        const std::string cs = cp;
        CHECK(omw::rmNonHex(cp) == result);
        CHECK(omw::rmNonHex(cs) == result);

        char buffer[] = "adfe";
        char* p = buffer;
        std::string s = p;
        omw::rmNonHex(p);
        omw::rmNonHex(s);
        CHECK(result == buffer);
        CHECK(s == result);
    }
}

TEST_CASE("string.h join()")
{
    constexpr size_t count = 3;
    const std::string tokens[count] = { "asdf", "456", "%&/" };

    std::vector<std::string> t(tokens, tokens + count);
    CHECK(omw::join(t) == "asdf456%&/");
    CHECK(omw::join(t, '-') == "asdf-456-%&/");
    CHECK(omw::join(std::vector<std::string>()) == "");
}

TEST_CASE("string.h String Vectors")
{
    constexpr size_t count = 3;
    const char* t_p[count] = { "asdf", "456", "%&/" };
    const std::string t_std[count] = { t_p[0], t_p[1], t_p[2] };

    const std::vector<std::string> v_std = { t_p[0], t_p[1], t_p[2] };
    const omw::StringVector v_omw = { t_p[0], t_p[1], t_p[2] };

    CHECK(omw::stringVector(t_p, count) == v_omw);
    CHECK(omw::stringVector(t_std, count) == v_omw);

    CHECK(omw::stringVector(t_p, count) == v_std);
    CHECK(omw::stringVector(t_std, count) == v_std);
}

TEST_CASE("string.h Character Classification")
{
    char c;

    for (size_t i = 0; i < 256; ++i)
    {
        c = (char)i;

        CHECK(omw::isAlnum(c) == (0 != std::isalnum(static_cast<unsigned char>(i))));
        CHECK(omw::isAlpha(c) == (0 != std::isalpha(static_cast<unsigned char>(i))));
        CHECK(omw::isBlank(c) == (0 != std::isblank(static_cast<unsigned char>(i))));
        CHECK(omw::isCntrl(c) == (0 != std::iscntrl(static_cast<unsigned char>(i))));
        CHECK(omw::isDigit(c) == (0 != std::isdigit(static_cast<unsigned char>(i))));
        CHECK(omw::isGraph(c) == (0 != std::isgraph(static_cast<unsigned char>(i))));
        CHECK(omw::isHex(c) == (0 != std::isxdigit(static_cast<unsigned char>(i))));
        CHECK(omw::isLower(c) == (0 != std::islower(static_cast<unsigned char>(i))));
        CHECK(omw::isNull(c) == (i == 0));
        CHECK(omw::isPrint(c) == (0 != std::isprint(static_cast<unsigned char>(i))));
        CHECK(omw::isPunct(c) == (0 != std::ispunct(static_cast<unsigned char>(i))));
        CHECK(omw::isSpace(c) == (0 != std::isspace(static_cast<unsigned char>(i))));
        CHECK(omw::isUpper(c) == (0 != std::isupper(static_cast<unsigned char>(i))));
    }
}



TEST_CASE("string.h isInteger()")
{
    CHECK(omw::isInteger("a123") == false);
    CHECK(omw::isInteger("a") == false);
    CHECK(omw::isInteger("abc") == false);
    CHECK(omw::isInteger("-") == false);
    CHECK(omw::isInteger("-abc") == false);
    CHECK(omw::isInteger("123abc") == false);
    CHECK(omw::isInteger("123 abc") == false);
    CHECK(omw::isInteger("-123abc") == false);
    CHECK(omw::isInteger("-123 abc") == false);
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
    CHECK(omw::isUInteger("123 abc") == false);
    CHECK(omw::isUInteger("-123abc") == false);
    CHECK(omw::isUInteger("-123 abc") == false);
    CHECK(omw::isUInteger("0") == true);
    CHECK(omw::isUInteger("-0") == false);
    CHECK(omw::isUInteger("-1") == false);
    CHECK(omw::isUInteger("-123") == false);
    CHECK(omw::isUInteger("1") == true);
    CHECK(omw::isUInteger("123") == true);
}

TEST_CASE("string.h isFloat()")
{
    // TODO improve isFloat test case

    CHECK(omw::isFloat("1234") == true);
    CHECK(omw::isFloat("-1234") == true);
    CHECK(omw::isFloat("0") == true);
    CHECK(omw::isFloat("-0") == true);

    CHECK(omw::isFloat("1.234") == true);
    CHECK(omw::isFloat("-1.234") == true);
    CHECK(omw::isFloat("0.0") == true);
    CHECK(omw::isFloat("-0.0") == true);
    CHECK(omw::isFloat(".0") == true);
    CHECK(omw::isFloat("-.0") == true);
    CHECK(omw::isFloat("0.") == true);
    CHECK(omw::isFloat("-0.") == true);

    CHECK(omw::isFloat("") == false);
    CHECK(omw::isFloat("-") == false);
}

TEST_CASE("string.h isHex()")
{
    const std::string s1 = "3F";
    const char* p1 = "3F5";

    CHECK(omw::isHex(s1) == true);
    CHECK(omw::isHex(p1) == true);
    CHECK(omw::isHex("0123456789ABCDEF") == true);
    CHECK(omw::isHex("0123456789abcdef") == true);
    CHECK(omw::isHex("0123456789ABCDEF0123") == true);

    CHECK(omw::isHex("") == false);
    CHECK(omw::isHex("0x3F") == false);

    for (int c = 0; c <= 0xFF; ++c)
    {
        const char chr = (char)c;
        const char hexStr[] = { '5', 'a', chr, 0 };
        bool expectedResult;

        if (((chr >= '0') && (chr <= '9')) || ((chr >= 'A') && (chr <= 'F')) || ((chr >= 'a') && (chr <= 'f'))) { expectedResult = true; }
        else expectedResult = false;

        CHECK(omw::isHex(chr) == expectedResult);

        if (chr == 0) expectedResult = true;
        CHECK(omw::isHex(hexStr) == expectedResult);
    }

    const char* substrTest = "AB-06CD;12345-a4d902q";

    CHECK(omw::isHex(substrTest) == false);
    CHECK(omw::isHex(substrTest, 0, 2) == true);
    CHECK(omw::isHex(substrTest, 0, 3) == false);
    CHECK(omw::isHex(substrTest, 3, 4) == true);
    CHECK(omw::isHex(substrTest, 8, 5) == true);
    CHECK(omw::isHex(substrTest, 8, 6) == false);
    CHECK(omw::isHex(substrTest, 14, 6) == true);
    CHECK(omw::isHex(substrTest, 14, 7) == false);
    CHECK(omw::isHex(substrTest, 20, 1) == false);
    CHECK(omw::isHex(substrTest, 20, 2) == false);

    substrTest = "12345-a4d902";

    CHECK(omw::isHex(substrTest) == false);
    CHECK(omw::isHex(substrTest, 6) == true);
    CHECK(omw::isHex(substrTest, 6, 100) == true);
    CHECK(omw::isHex(substrTest, 5, 100) == false);

    CHECK(omw::isHex(substrTest, 12) == false);
    CHECK(omw::isHex(substrTest, 13) == false);
    CHECK(omw::isHex(substrTest, 12, 5) == false);
    CHECK(omw::isHex(substrTest, 1, 0) == false);
    CHECK(omw::isHex("1234", 0, 5) == true);
}



TEST_CASE("string.h peekNewLine()")
{
    const char* str;
    const char* end;
    size_t pos;



    const char lf1[] = { 'a', 's', 'd', 'f', '\n', 'a', 's', 'd', 'f', '\n', '\n', 'a', 's', 'd', 'f' };
    str = lf1;
    end = str + sizeof(lf1);
    pos = 0;
    CHECK(omw::peekNewLine(str + pos) == 0);
    CHECK(omw::peekNewLine(str + pos, end) == 0);
    pos = 4;
    CHECK(omw::peekNewLine(str + pos) == 1);
    CHECK(omw::peekNewLine(str + pos, end) == 1);
    pos = 5;
    CHECK(omw::peekNewLine(str + pos) == 0);
    CHECK(omw::peekNewLine(str + pos, end) == 0);
    pos = 9;
    CHECK(omw::peekNewLine(str + pos) == 1);
    CHECK(omw::peekNewLine(str + pos, end) == 1);
    pos = 10;
    CHECK(omw::peekNewLine(str + pos) == 1);
    CHECK(omw::peekNewLine(str + pos, end) == 1);
    pos = 14;
    // CHECK(omw::peekNewLine(str + pos) == 0); // access violation
    CHECK(omw::peekNewLine(str + pos, end) == 0);



    const char lf2[] = { 'a', 's', 'd', 'f', '\n', 'a', 's', 'd', 'f', '\n', '\n', 'a', 's', 'd', 'f', '\n' };
    str = lf2;
    end = str + sizeof(lf2);
    pos = 0;
    CHECK(omw::peekNewLine(str + pos) == 0);
    CHECK(omw::peekNewLine(str + pos, end) == 0);
    pos = 4;
    CHECK(omw::peekNewLine(str + pos) == 1);
    CHECK(omw::peekNewLine(str + pos, end) == 1);
    pos = 5;
    CHECK(omw::peekNewLine(str + pos) == 0);
    CHECK(omw::peekNewLine(str + pos, end) == 0);
    pos = 9;
    CHECK(omw::peekNewLine(str + pos) == 1);
    CHECK(omw::peekNewLine(str + pos, end) == 1);
    pos = 10;
    CHECK(omw::peekNewLine(str + pos) == 1);
    CHECK(omw::peekNewLine(str + pos, end) == 1);
    pos = 15;
    // CHECK(omw::peekNewLine(str + pos) == 1); // access violation
    CHECK(omw::peekNewLine(str + pos, end) == 1);



    const char cr1[] = { 'a', 's', 'd', 'f', '\r', 'a', 's', 'd', 'f', '\r', '\r', 'a', 's', 'd', 'f' };
    str = cr1;
    end = str + sizeof(cr1);
    pos = 0;
    CHECK(omw::peekNewLine(str + pos) == 0);
    CHECK(omw::peekNewLine(str + pos, end) == 0);
    pos = 4;
    CHECK(omw::peekNewLine(str + pos) == 1);
    CHECK(omw::peekNewLine(str + pos, end) == 1);
    pos = 5;
    CHECK(omw::peekNewLine(str + pos) == 0);
    CHECK(omw::peekNewLine(str + pos, end) == 0);
    pos = 9;
    CHECK(omw::peekNewLine(str + pos) == 1);
    CHECK(omw::peekNewLine(str + pos, end) == 1);
    pos = 10;
    CHECK(omw::peekNewLine(str + pos) == 1);
    CHECK(omw::peekNewLine(str + pos, end) == 1);
    pos = 14;
    // CHECK(omw::peekNewLine(str + pos) == 0); // access violation
    CHECK(omw::peekNewLine(str + pos, end) == 0);


    const char cr2[] = { 'a', 's', 'd', 'f', '\r', 'a', 's', 'd', 'f', '\r', '\r', 'a', 's', 'd', 'f', '\r' };
    str = cr2;
    end = str + sizeof(cr2);
    pos = 0;
    CHECK(omw::peekNewLine(str + pos) == 0);
    CHECK(omw::peekNewLine(str + pos, end) == 0);
    pos = 4;
    CHECK(omw::peekNewLine(str + pos) == 1);
    CHECK(omw::peekNewLine(str + pos, end) == 1);
    pos = 5;
    CHECK(omw::peekNewLine(str + pos) == 0);
    CHECK(omw::peekNewLine(str + pos, end) == 0);
    pos = 9;
    CHECK(omw::peekNewLine(str + pos) == 1);
    CHECK(omw::peekNewLine(str + pos, end) == 1);
    pos = 10;
    CHECK(omw::peekNewLine(str + pos) == 1);
    CHECK(omw::peekNewLine(str + pos, end) == 1);
    pos = 15;
    // CHECK(omw::peekNewLine(str + pos) == 1); // access violation
    CHECK(omw::peekNewLine(str + pos, end) == 1);



    const char crlf1[] = { 'a', 's', 'd', 'f', '\r', '\n', 'a', 's', 'd', 'f', '\r', '\n', '\r', '\n', 'a', 's', 'd', 'f' };
    str = crlf1;
    end = str + sizeof(crlf1);
    pos = 0;
    CHECK(omw::peekNewLine(str + pos) == 0);
    CHECK(omw::peekNewLine(str + pos, end) == 0);
    pos = 4;
    CHECK(omw::peekNewLine(str + pos) == 2);
    CHECK(omw::peekNewLine(str + pos, end) == 2);
    pos = 5;
    CHECK(omw::peekNewLine(str + pos) == 1);
    CHECK(omw::peekNewLine(str + pos, end) == 1);
    pos = 6;
    CHECK(omw::peekNewLine(str + pos) == 0);
    CHECK(omw::peekNewLine(str + pos, end) == 0);
    pos = 10;
    CHECK(omw::peekNewLine(str + pos) == 2);
    CHECK(omw::peekNewLine(str + pos, end) == 2);
    pos = 11;
    CHECK(omw::peekNewLine(str + pos) == 1);
    CHECK(omw::peekNewLine(str + pos, end) == 1);
    pos = 12;
    CHECK(omw::peekNewLine(str + pos) == 2);
    CHECK(omw::peekNewLine(str + pos, end) == 2);
    pos = 13;
    CHECK(omw::peekNewLine(str + pos) == 1);
    CHECK(omw::peekNewLine(str + pos, end) == 1);
    pos = 17;
    // CHECK(omw::peekNewLine(str + pos) == 0); // access violation
    CHECK(omw::peekNewLine(str + pos, end) == 0);



    const char crlf2[] = { 'a', 's', 'd', 'f', '\r', '\n', 'a', 's', 'd', 'f', '\r', '\n', '\r', '\n', 'a', 's', 'd', 'f', '\r', '\n' };
    str = crlf2;
    end = str + sizeof(crlf2);
    pos = 0;
    CHECK(omw::peekNewLine(str + pos) == 0);
    CHECK(omw::peekNewLine(str + pos, end) == 0);
    pos = 4;
    CHECK(omw::peekNewLine(str + pos) == 2);
    CHECK(omw::peekNewLine(str + pos, end) == 2);
    pos = 5;
    CHECK(omw::peekNewLine(str + pos) == 1);
    CHECK(omw::peekNewLine(str + pos, end) == 1);
    pos = 6;
    CHECK(omw::peekNewLine(str + pos) == 0);
    CHECK(omw::peekNewLine(str + pos, end) == 0);
    pos = 10;
    CHECK(omw::peekNewLine(str + pos) == 2);
    CHECK(omw::peekNewLine(str + pos, end) == 2);
    pos = 11;
    CHECK(omw::peekNewLine(str + pos) == 1);
    CHECK(omw::peekNewLine(str + pos, end) == 1);
    pos = 12;
    CHECK(omw::peekNewLine(str + pos) == 2);
    CHECK(omw::peekNewLine(str + pos, end) == 2);
    pos = 13;
    CHECK(omw::peekNewLine(str + pos) == 1);
    CHECK(omw::peekNewLine(str + pos, end) == 1);
    pos = 18;
    CHECK(omw::peekNewLine(str + pos) == 2);
    CHECK(omw::peekNewLine(str + pos, end) == 2);
    pos = 19;
    // CHECK(omw::peekNewLine(str + pos) == 1); // access violation
    CHECK(omw::peekNewLine(str + pos, end) == 1);
}



TEST_CASE("string.h readString()")
{
    // "The quick brown fox jumps over the lazy dog."
    constexpr size_t size = 44;
    const uint8_t data[size] = { 0x54, 0x68, 0x65, 0x20, 0x71, 0x75, 0x69, 0x63, 0x6b, 0x20, 0x62, 0x72, 0x6f, 0x77, 0x6e,
                                 0x20, 0x66, 0x6f, 0x78, 0x20, 0x6a, 0x75, 0x6d, 0x70, 0x73, 0x20, 0x6f, 0x76, 0x65, 0x72,
                                 0x20, 0x74, 0x68, 0x65, 0x20, 0x6c, 0x61, 0x7a, 0x79, 0x20, 0x64, 0x6f, 0x67, 0x2e };
    const std::vector<uint8_t> vec(data, data + size);

    CHECK(omw::readString(data, 5) == "The q");
    CHECK(omw::readString(vec, 0, 5) == "The q");

    CHECK(omw::readString(data + 7, 5) == "ck br");
    CHECK(omw::readString(vec, 7, 5) == "ck br");

    CHECK(omw::readString(data + 31, 13) == "the lazy dog.");
    CHECK(omw::readString(vec, 31, 13) == "the lazy dog.");

    CHECK(omw::readString(data + size, 0) == "");
    CHECK(omw::readString(vec, size, 0) == "");

    TESTUTIL_TRYCATCH_OPEN_DECLARE_VAL(std::string, "abcd");
    TESTUTIL_TRYCATCH_CHECK(omw::readString(nullptr, 3), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::readString(vec, size - 1, 2), std::invalid_argument);
    TESTUTIL_TRYCATCH_CHECK(omw::readString(vec, size + 1, 0), std::invalid_argument);
    TESTUTIL_TRYCATCH_CLOSE();
}



TEST_CASE("string.h writeString() pointer")
{
    std::vector<uint8_t> b;
    std::vector<uint8_t> r;

    b = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99 };
    r = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99 };
    omw::writeString(b.data(), b.data() + b.size(), "");
    CHECK(b == r);

    b = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99 };
    r = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99 };
    omw::writeString(b.data() + b.size(), b.data() + b.size(), "");
    CHECK(b == r);

    b = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99 };
    r = { 0x41, 0x42, 0x43, 0x44, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99 };
    omw::writeString(b.data(), b.data() + b.size(), "ABCD");
    CHECK(b == r);

    b = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99 };
    r = { 0x00, 0x11, 0x22, 0x61, 0x62, 0x63, 0x64, 0x77, 0x88, 0x99 };
    omw::writeString(b.data() + 3, b.data() + b.size(), "abcd");
    CHECK(b == r);

    b = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99 };
    r = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x31, 0x32, 0x33, 0x34 };
    omw::writeString(b.data() + 6, b.data() + b.size(), "1234");
    CHECK(b == r);

    std::vector<uint8_t>* p_tcv; // TryCatchValue
    const std::vector<uint8_t> initial = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    TESTUTIL_TRYCATCH_SE_DECLARE_VAL(std::vector<uint8_t>, p_tcv, initial);
    TESTUTIL_TRYCATCH_SE_CHECK((omw::writeString(nullptr, p_tcv->data() + p_tcv->size(), "")), std::invalid_argument);
    TESTUTIL_TRYCATCH_SE_CHECK((omw::writeString(p_tcv->data() + p_tcv->size(), nullptr, "")), std::invalid_argument);
    TESTUTIL_TRYCATCH_SE_CHECK((omw::writeString(p_tcv->data() + p_tcv->size() + 1, p_tcv->data() + p_tcv->size(), "")), std::invalid_argument);
    TESTUTIL_TRYCATCH_SE_CHECK((omw::writeString(p_tcv->data() + p_tcv->size(), p_tcv->data() + p_tcv->size(), "a")), std::out_of_range);
    TESTUTIL_TRYCATCH_SE_CHECK((omw::writeString(p_tcv->data() + p_tcv->size() - 1, p_tcv->data() + p_tcv->size(), "ab")), std::out_of_range);
}



TEST_CASE("string.h writeString() vector")
{
    std::vector<uint8_t> b;
    std::vector<uint8_t> r;

    b = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99 };
    r = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99 };
    omw::writeString(b, 0, "");
    CHECK(b == r);

    b = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99 };
    r = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99 };
    omw::writeString(b, b.size(), "");
    CHECK(b == r);

    b = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99 };
    r = { 0x41, 0x42, 0x43, 0x44, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99 };
    omw::writeString(b, 0, "ABCD");
    CHECK(b == r);

    b = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99 };
    r = { 0x00, 0x11, 0x22, 0x61, 0x62, 0x63, 0x64, 0x77, 0x88, 0x99 };
    omw::writeString(b, 3, "abcd");
    CHECK(b == r);

    b = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99 };
    r = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x31, 0x32, 0x33, 0x34 };
    omw::writeString(b, 6, "1234");
    CHECK(b == r);

    std::vector<uint8_t>* p_tcv; // TryCatchValue
    const std::vector<uint8_t> initial = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    TESTUTIL_TRYCATCH_SE_DECLARE_VAL(std::vector<uint8_t>, p_tcv, initial);
    TESTUTIL_TRYCATCH_SE_CHECK((omw::writeString(*p_tcv, p_tcv->size() + 1, "")), std::invalid_argument);
    TESTUTIL_TRYCATCH_SE_CHECK((omw::writeString(*p_tcv, p_tcv->size(), "a")), std::out_of_range);
    TESTUTIL_TRYCATCH_SE_CHECK((omw::writeString(*p_tcv, p_tcv->size() - 1, "ab")), std::out_of_range);
}



#endif // TEST_OMW_STRING_H
