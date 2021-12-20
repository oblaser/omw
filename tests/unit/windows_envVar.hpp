/*
author         Oliver Blaser
date           13.08.2021
copyright      MIT - Copyright (c) 2021 Oliver Blaser
*/

#ifndef TEST_OMW_WINDOWS_ENVVAR_H
#define TEST_OMW_WINDOWS_ENVVAR_H

#include <omw/defs.h>
#ifdef OMW_PLAT_WIN

#include <cctype>
#include <string>

#include "catch2/catch.hpp"

#include <omw/windows/envVar.h>



TEST_CASE("omw::windows::getEnvironmentVariable()")
{
    omw::windows::ErrorCode ec;
    std::string value;

    value = omw::windows::getEnvironmentVariable("noEnvVarName_123456", ec);
    CHECK(ec.code() == omw::windows::EC_ENVVAR_NOT_FOUND);
    CHECK(value.length() == 0);

    value = omw::windows::getEnvironmentVariable("windir", ec);
    CHECK(ec.code() == omw::windows::EC_OK);
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
#endif // TEST_OMW_WINDOWS_ENVVAR_H
