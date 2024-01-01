/*
author          Oliver Blaser
date            31.12.2023
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
#include "testUtil.h"

#include <omw/windows/string.h>



TEST_CASE("omw::windows string coversion functions")
{
    omw::windows::ErrorCode ec;
    const char str[] = "The five b\xC3\xB6xing wizards jump quickly.";
    const WCHAR wcs[] = L"The five b\x00F6xing wizards jump quickly.";
    std::string res;
    std::wstring wres;

    wres = omw::windows::u8tows(str);
    CHECK(wres.length() == 37);
    CHECK(wcscmp(wcs, wres.c_str()) == 0);

    res = omw::windows::wstou8(wcs);
    CHECK(res.length() == 38);
    CHECK(strcmp(str, res.c_str()) == 0);



    constexpr size_t destSize = 100;
    WCHAR wdest[destSize];
    char dest[destSize];

    for (size_t i = 0; i < destSize; ++i) { wdest[i] = 0; dest[i] = 0; }
    CHECK(omw::windows::deprecated::wstr_to_utf8(wcs, dest, destSize, ec) == 38);
    CHECK(ec.code() == omw::windows::EC_OK);
    CHECK(strcmp(str, dest) == 0);

    for (size_t i = 0; i < destSize; ++i) { wdest[i] = 0; dest[i] = 0; }
    CHECK(omw::windows::deprecated::utf8_to_wstr(str, wdest, destSize, ec) == 37);
    CHECK(ec.code() == omw::windows::EC_OK);
    CHECK(wcscmp(wcs, wdest) == 0);
}

TEST_CASE("omw::windows string coversion functions invalid unicode")
{
    omw::windows::ErrorCode ec;
    const char str[] = "The five \x80 boxing wizards jump quickly.";
    const WCHAR wcs[] = L"The five \xD800 boxing wizards jump quickly.";
    std::string res;
    std::wstring wres;
    
    std::wstring* pWTryCatchValue;
    TESTUTIL_TRYCATCH_SE_OPEN_DECLARE_VAL(std::wstring, pWTryCatchValue, L"abcd\xD800""efg");
    TESTUTIL_TRYCATCH_SE_CHECK(*pWTryCatchValue = omw::windows::u8tows(str), omw::windows::invalid_unicode);
    TESTUTIL_TRYCATCH_SE_CLOSE();

    std::string* pTryCatchValue;
    TESTUTIL_TRYCATCH_SE_OPEN_DECLARE_VAL(std::string, pTryCatchValue, "abcd\x80""efg");
    TESTUTIL_TRYCATCH_SE_CHECK(*pTryCatchValue = omw::windows::wstou8(wcs), omw::windows::invalid_unicode);
    TESTUTIL_TRYCATCH_SE_CLOSE();



    WCHAR wdest[512];
    char dest[512];

    CHECK(omw::windows::deprecated::wstr_to_utf8(wcs, dest, 512, ec) == 0);
    CHECK(ec.code() == omw::windows::EC_INV_UNICODE);

    CHECK(omw::windows::deprecated::utf8_to_wstr(str, wdest, 512, ec) == 0);
    CHECK(ec.code() == omw::windows::EC_INV_UNICODE);
}

TEST_CASE("omw::windows string coversion functions stress big string")
{
    // string sizes (aka test cases)
    const size_t sizes[] =
    {
        60,
        1024,
        100 * 1024
    };
    const size_t nTest = (sizeof(sizes) / sizeof(sizes[0]));

    constexpr char firstAlphChar = ' ';
    constexpr char lastAlphChar = '~';
    constexpr int alphabetSize = lastAlphChar - firstAlphChar + 1;

    for (size_t iTest = 0; iTest < nTest; ++iTest)
    {
        const size_t len = sizes[iTest];

        std::string str(len, 0);
        std::wstring wcs(len, 0);
        for (size_t i = 0; i < len ; ++i)
        {
            str[i] = (firstAlphChar + (i % alphabetSize));
            wcs[i] = (firstAlphChar + (i % alphabetSize)); // implicit (ASCII) char to wchar_t is OK
        }
        str.replace(len - 3, 1, "\xC3\x8A"); // ^E
        wcs.replace(len - 3, 1, L"\x00CA");  // ^E

        const auto wres = omw::windows::u8tows(str);
        CHECK(wres.length() == len);
        CHECK(wcscmp(wcs.c_str(), wres.c_str()) == 0);

        const auto res = omw::windows::wstou8(wcs);
        CHECK(res.length() == len + 1);
        CHECK(strcmp(str.c_str(), res.c_str()) == 0);
    }
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

        omw::windows::deprecated::wstr_to_utf8(wString.data(), string, ec);

        CHECK(ec.code() == omw::windows::EC_OK);
        CHECK(string.length() == (wStringSize - 1));
    }
}



#endif // OMW_PLAT_WIN
#endif // TEST_OMW_WINDOWS_STRING_H
