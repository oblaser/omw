/*
author         Oliver Blaser
date           11.06.2021
copyright      MIT - Copyright (c) 2021 Oliver Blaser
*/

#ifndef TEST_OMW_STRING_H
#define TEST_OMW_STRING_H

#include <cstdint>
#include <string>

#include <catch2/catch.hpp>
#include <omw/string.h>



TEST_CASE("string.h omw::string URL encoded")
{
    CHECK(omw::string("+\"*%&/()=asdf(fdsf)").getUrlEncoded() == "%2B%22%2A%25%26%2F%28%29%3Dasdf%28fdsf%29");
}

TEST_CASE("string.h omw::string")
{
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



#endif // TEST_OMW_STRING_H
