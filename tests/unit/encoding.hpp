/*
author          Oliver Blaser
date            07.01.2022
copyright       MIT - Copyright (c) 2022 Oliver Blaser
*/

#ifndef TEST_OMW_ENCODING_H
#define TEST_OMW_ENCODING_H

#include <string>
#include <vector>

#include "catch2/catch.hpp"
#include "testUtil.h"

#include <omw/encoding.h>


TEST_CASE("encoding.h omw::url")
{
    const omw::string str = "+\"*%&/()=asdf(fdsf)";
    const omw::string enc = "%2B%22%2A%25%26%2F%28%29%3Dasdf%28fdsf%29";

    CHECK(omw::url::encode(str) == enc);
    CHECK(omw::url::encode(omw::url::encode(str)) == "%252B%2522%252A%2525%2526%252F%2528%2529%253Dasdf%2528fdsf%2529");
}


#endif // TEST_OMW_ENCODING_H
