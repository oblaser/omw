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
    const char str[] = "a boy with a hat";

    //omw::basic_string<char> replFirst(str);
    omw::string replFirst = str;

    replFirst.replaceFirst("a", "#", 5);
    //CHECK(replFirst == "a boy with # hat");





    /*CHECK(omw::OMWi_string("+\"*%&/()=asdf(fdsf)").getUrlEncoded() == "%2B%22%2A%25%26%2F%28%29%3Dasdf%28fdsf%29");

    omw::OMWi_string OMWi_replFirst(str);
    omw::OMWi_string OMWi_replAll(str);

    OMWi_replFirst.replaceFirst("a", "#", 5);
    OMWi_replAll.replaceAll("a", "#");
    CHECK(OMWi_replFirst == "a boy with # hat");
    CHECK(OMWi_replAll == "# boy with # h#t");

    OMWi_replAll.replaceAll(" ", "_", 6);
    CHECK(OMWi_replAll == "# boy with_#_h#t");*/
}