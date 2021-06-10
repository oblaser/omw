/*
author         Oliver Blaser
date           09.06.2021
copyright      MIT - Copyright (c) 2021 Oliver Blaser
*/

#include <iostream>

#include <omw/omw.h>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp> // $(sdk)/catch2/catch.hpp


TEST_CASE("omw lib")
{
    CHECK(omw::info::version() == omw::Version(0, 0, 0));

    std::cout << std::endl << "Testing OMW ..." << std::endl;
    
    std::cout << std::endl << omw::info::infoTxt() << std::endl;
}


#include "version.hpp"
#include "windows_string.hpp"
#include "windows_envVar.hpp"

#include <omw/string.h>

TEST_CASE("omw/string.h")
{
    std::string str = omw::testFunc(123);
    CHECK(str == "123");
    CHECK(str.length() == 3);
}