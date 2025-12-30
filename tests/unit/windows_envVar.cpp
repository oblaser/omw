/*
author          Oliver Blaser
date            31.12.2023
copyright       MIT - Copyright (c) 2023 Oliver Blaser
*/

#include <omw/defs.h>
#ifdef OMW_PLAT_WIN

#include <cctype>
#include <string>

#include "catch2/catch.hpp"
#include "testUtil.h"

#include <omw/windows/envVar.h>
#include <omw/windows/exception.h>



TEST_CASE("omw::windows::getEnvironmentVariable()")
{
    std::string* pTryCatchValue;
    TESTUTIL_TRYCATCH_SE_OPEN_DECLARE_VAL(std::string, pTryCatchValue, "abcdefg");
    TESTUTIL_TRYCATCH_SE_CHECK(*pTryCatchValue = omw::windows::getEnvironmentVariable("noEnvVarName_123456"), omw::windows::envVar_not_found);
    TESTUTIL_TRYCATCH_SE_CLOSE();

    std::string value = omw::windows::getEnvironmentVariable("windir");
    CHECK(value.length() == 10);

    for (size_t i = 0; i < value.length(); ++i)
    {
        unsigned char c = value[i];
        c = std::tolower(c);
        value[i] = c;
    }

    CHECK(std::string(":\\windows") == std::string(value, 1));
}



#endif // OMW_PLAT_WIN
