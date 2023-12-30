/*
author          Oliver Blaser
date            30.12.2023
copyright       MIT - Copyright (c) 2023 Oliver Blaser
*/

#ifndef TEST_OMW_WINDOWS_STRING_H
#define TEST_OMW_WINDOWS_STRING_H

#include <omw/defs.h>
#ifdef OMW_PLAT_WIN

#include <cstdint>
#include <string>
#include <vector>

#include "catch2/catch.hpp"

#include <omw/windows/string.h>



TEST_CASE("omw::windows string coversion functions")
{
    omw::windows::ErrorCode ec;
    const WCHAR wcs[] = L"The five b\x00F6xing wizards jump quickly.";
    const char str[] = "The five b\xC3\xB6xing wizards jump quickly.";
    std::wstring wres;
    std::string res;

    wres = omw::windows::u8tows(str);
    CHECK(wres.length() == 37);
    CHECK(wcscmp(wcs, wres.c_str()) == 0);

    //res = omw::windows::wstou8(wcs);
    //CHECK(res.length() == 38);
    //CHECK(strcmp(str, res.c_str()) == 0);



    constexpr size_t destSize = 100;
    WCHAR wdest[destSize];
    char dest[destSize];

    for (size_t i = 0; i < destSize; ++i) { wdest[i] = 0; dest[i] = 0; }
    CHECK(omw::windows::wstr_to_utf8(wcs, dest, destSize, ec) == 38);
    CHECK(ec.code() == omw::windows::EC_OK);
    CHECK(strcmp(str, dest) == 0);

    for (size_t i = 0; i < destSize; ++i) { wdest[i] = 0; dest[i] = 0; }
    CHECK(omw::windows::utf8_to_wstr(str, wdest, destSize, ec) == 37);
    CHECK(ec.code() == omw::windows::EC_OK);
    CHECK(wcscmp(wcs, wdest) == 0);
}

TEST_CASE("omw::windows string coversion functions invalid unicode")
{
    omw::windows::ErrorCode ec;
    const WCHAR wcs[] = L"The five \xD800 boxing wizards jump quickly.";
    const char str[] = "The five \x80 boxing wizards jump quickly.";
    std::wstring wres;
    std::string res;
    
    std::wstring* pWTryCatchValue;
    TESTUTIL_TRYCATCH_SE_OPEN_DECLARE_VAL(std::wstring, pWTryCatchValue, L"abcd\xD800""efg");
    TESTUTIL_TRYCATCH_SE_CHECK(*pWTryCatchValue = omw::windows::u8tows(str), omw::windows::invalid_unicode);
    TESTUTIL_TRYCATCH_SE_CLOSE();

    //std::string* pTryCatchValue;
    //TESTUTIL_TRYCATCH_SE_OPEN_DECLARE_VAL(std::string, pTryCatchValue, "abcd\x80""efg");
    //TESTUTIL_TRYCATCH_SE_CHECK(*pTryCatchValue = omw::windows::wstou8(wcs), omw::windows::invalid_unicode);
    //TESTUTIL_TRYCATCH_SE_CLOSE();



    WCHAR wdest[512];
    char dest[512];

    CHECK(omw::windows::wstr_to_utf8(wcs, dest, 512, ec) == 0);
    CHECK(ec.code() == omw::windows::EC_INV_UNICODE);

    CHECK(omw::windows::utf8_to_wstr(str, wdest, 512, ec) == 0);
    CHECK(ec.code() == omw::windows::EC_INV_UNICODE);
}

TEST_CASE("omw::windows string coversion functions stress big string")
{
    // TODO
    CHECK(true);
}

TEST_CASE("omw::windows::wstr_to_utf8(LPCWCH, std::string&, ErrorCode&) stress big string")
{
    const size_t wss[] =
    {
        1024,   // init size is 300 and grow is 100
        100 * 1024
    };
    const size_t nTest = (sizeof(wss) / sizeof(wss[0]));

    for (size_t iTest = 0; iTest < nTest; ++iTest)
    {

        const size_t wStringSize = wss[iTest];
        std::vector<WCHAR> wString(wStringSize, 0);

        for (size_t i = 0; i < wString.size(); ++i) wString[i] = (L'a' + (i % 26));
        wString[wString.size() - 1] = 0;

        omw::windows::ErrorCode ec;
        std::string string;

        omw::windows::wstr_to_utf8(wString.data(), string, ec);

        CHECK(ec.code() == omw::windows::EC_OK);
        CHECK(string.length() == (wStringSize - 1));
    }
}



#endif // OMW_PLAT_WIN
#endif // TEST_OMW_WINDOWS_STRING_H
