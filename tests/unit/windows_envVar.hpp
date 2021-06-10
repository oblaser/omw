/*
author         Oliver Blaser
date           10.06.2021
copyright      MIT - Copyright (c) 2021 Oliver Blaser
*/

#ifndef TEST_OMW_WINDOWS_ENVVAR_H
#define TEST_OMW_WINDOWS_ENVVAR_H

#include <omw/defs.h>
#ifdef OMW_PLAT_WIN

#include <cstdint>
#include <string>

#include <catch2/catch.hpp>
#include <omw/windows/envVar.h>



TEST_CASE("omw::windows::getEnvironmentVariable() ")
{
    omw::windows::ErrorCode ec;
    std::string value;

    value = omw::windows::getEnvironmentVariable("noEnvVarName_123456", ec);
    CHECK(ec.code() == omw::windows::EC_ENVVAR_NOT_FOUND);
    CHECK(value.length() == 0);

    value = omw::windows::getEnvironmentVariable("windir", ec);
    CHECK(ec.code() == omw::windows::EC_OK);
    CHECK(value.length() == 10);
}



#endif // OMW_PLAT_WIN
#endif // TEST_OMW_WINDOWS_ENVVAR_H
