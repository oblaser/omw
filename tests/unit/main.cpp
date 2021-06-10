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
    CHECK(omw::string("+\"*%&/()=asdf(fdsf)").getUrlEncoded() == "%2B%22%2A%25%26%2F%28%29%3Dasdf%28fdsf%29");

    const char str[] = "a boy with a hat";
    omw::string replFirst(str);
    omw::string replAll(str);

    replFirst.replaceFirst("a", "#", 5);
    replAll.replaceAll("a", "#");
    CHECK(replFirst == "a boy with # hat");
    CHECK(replAll == "# boy with # h#t");

    replAll.replaceAll(" ", "_", 6);
    CHECK(replAll == "# boy with_#_h#t");
}