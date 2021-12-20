/*
author          Oliver Blaser
date            06.12.2021
copyright       MIT - Copyright (c) 2021 Oliver Blaser
*/

#ifndef TEST_OMW_UTIL_H
#define TEST_OMW_UTIL_H

#include <string>
#include <vector>

#include "catch2/catch.hpp"
#include "testUtil.h"

#include <omw/string.h>
#include <omw/utility.h>



TEST_CASE("utility.h toggle()")
{
    bool b = false;
    omw::toggle(b);
    CHECK(b == true);
    omw::toggle(b);
    CHECK(b == false);
    omw::toggle(b);
    CHECK(b == true);

    int i = 123;
    omw::toggle(i);
    CHECK(i == 0);
    omw::toggle(i);
    CHECK(i == 1);
    omw::toggle(i);
    CHECK(i == 0);
}

TEST_CASE("utility.h vectorContains()")
{
    const std::vector<int> vInt = { 1, 5, 9 };
    CHECK(omw::vectorContains(vInt, 1));
    CHECK_FALSE(omw::vectorContains(vInt, 0));

    const std::vector<std::string> vStdString = { "the", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog" };
    CHECK(omw::vectorContains(vStdString, std::string("fox")));
    CHECK_FALSE(omw::vectorContains(vStdString, std::string("boat")));

    const std::vector<omw::string> vString = { "pack", "my", "box", "with", "five", "dozen", "liquor", "jugs" };
    CHECK(omw::vectorContains(vString, omw::string("five")));
    CHECK_FALSE(omw::vectorContains(vString, omw::string("boat")));
}



#endif // TEST_OMW_UTIL_H
