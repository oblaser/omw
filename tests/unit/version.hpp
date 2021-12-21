/*
author         Oliver Blaser
date           21.12.2021
copyright      MIT - Copyright (c) 2021 Oliver Blaser
*/

#ifndef TEST_OMW_VERSION_H
#define TEST_OMW_VERSION_H

#include <cstdint>
#include <string>
#include <vector>

#include "catch2/catch.hpp"

#include <omw/version.h>



TEST_CASE("omw::Version ctor")
{
    omw::Version v;

    v = omw::Version("12.34.56");
    CHECK(v.major() == 12);
    CHECK(v.minor() == 34);
    CHECK(v.patch() == 56);


    TESTUTIL_TRYCATCH_DECLARE_VAL(omw::Version, omw::Version("1.2.3"));
    TESTUTIL_TRYCATCH_CHECK(omw::Version("1.2.-3"), std::invalid_argument);

    try {
        v = omw::Version("1.2-.3");
        CHECK(false);
    }
    catch (...) {
        CHECK(true);
    }

    try {
        v = omw::Version("d1.2.3");
        CHECK(false);
    }
    catch (...) {
        CHECK(true);
    }

    try {
        v = omw::Version("1.2.p3");
        CHECK(false);
    }
    catch (...) {
        CHECK(true);
    }

    try {
        v = omw::Version("1.23");
        CHECK(false);
    }
    catch (...) {
        CHECK(true);
    }
}

TEST_CASE("omw::Version coversion functions")
{
    CHECK(omw::Version(0, 0, 0).toString() == std::string("0.0.0"));
    CHECK(omw::Version(0, 12, 34).toString() == std::string("0.12.34"));
    CHECK(omw::Version(UINT32_MAX, INT32_MAX, INT32_MIN).toString() == std::string("4294967295.2147483647.2147483648"));
}

TEST_CASE("omw::Version compare operators")
{
    const omw::Version v000(0, 0, 0);
    const omw::Version v001(0, 0, 1);
    const omw::Version v010(0, 1, 0);
    const omw::Version v011(0, 1, 1);
    const omw::Version v100(1, 0, 0);
    const omw::Version v101(1, 0, 1);
    const omw::Version v110(1, 1, 0);
    const omw::Version v111(1, 1, 1);

    CHECK_FALSE(v011 == v000);
    CHECK_FALSE(v011 == v001);
    CHECK_FALSE(v011 == v010);
    CHECK(v011 == v011);
    CHECK_FALSE(v011 == v100);
    CHECK_FALSE(v011 == v101);
    CHECK_FALSE(v011 == v110);
    CHECK_FALSE(v011 == v111);

    CHECK(v011 != v000);
    CHECK(v011 != v001);
    CHECK(v011 != v010);
    CHECK_FALSE(v011 != v011);
    CHECK(v011 != v100);
    CHECK(v011 != v101);
    CHECK(v011 != v110);
    CHECK(v011 != v111);

    CHECK_FALSE(v011 < v000);
    CHECK_FALSE(v011 < v001);
    CHECK_FALSE(v011 < v010);
    CHECK_FALSE(v011 < v011);
    CHECK(v011 < v100);
    CHECK(v011 < v101);
    CHECK(v011 < v110);
    CHECK(v011 < v111);

    CHECK_FALSE(v011 <= v000);
    CHECK_FALSE(v011 <= v001);
    CHECK_FALSE(v011 <= v010);
    CHECK(v011 <= v011);
    CHECK(v011 <= v100);
    CHECK(v011 <= v101);
    CHECK(v011 <= v110);
    CHECK(v011 <= v111);

    CHECK(v011 > v000);
    CHECK(v011 > v001);
    CHECK(v011 > v010);
    CHECK_FALSE(v011 > v011);
    CHECK_FALSE(v011 > v100);
    CHECK_FALSE(v011 > v101);
    CHECK_FALSE(v011 > v110);
    CHECK_FALSE(v011 > v111);

    CHECK(v011 >= v000);
    CHECK(v011 >= v001);
    CHECK(v011 >= v010);
    CHECK(v011 >= v011);
    CHECK_FALSE(v011 >= v100);
    CHECK_FALSE(v011 >= v101);
    CHECK_FALSE(v011 >= v110);
    CHECK_FALSE(v011 >= v111);
}



#endif // TEST_OMW_VERSION_H
