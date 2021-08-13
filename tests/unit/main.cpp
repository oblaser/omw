/*
author         Oliver Blaser
date           11.06.2021
copyright      MIT - Copyright (c) 2021 Oliver Blaser
*/

#include <iostream>

#include <omw/omw.h>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp> // $(sdk)/catch2/catch.hpp


TEST_CASE("omw lib")
{
    std::cout << std::endl << "Testing OMW ..." << std::endl;

    std::cout << std::endl << omw::info::infoTxt() << std::endl;

    int revision = 0;

#ifdef _DEBUG
    revision += 1000;
#endif

    CHECK(omw::info::version() == omw::Version(0, 1, revision));
}


#include "string.hpp"
#include "version.hpp"
#include "windows_envVar.hpp"
#include "windows_string.hpp"
