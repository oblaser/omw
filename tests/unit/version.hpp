/*
author         Oliver Blaser
date           14.06.2021
copyright      MIT - Copyright (c) 2021 Oliver Blaser
*/

#ifndef TEST_OMW_VERSION_H
#define TEST_OMW_VERSION_H

#include <cstdint>
#include <string>
#include <vector>

#include <catch2/catch.hpp>
#include <omw/omw.h>



TEST_CASE("omw::Version ctor")
{
    omw::Version v;
    std::vector<int> version;
    std::vector<int> vec;

    v = omw::Version("1.2.3");
    version = std::vector<int>(v.data(), v.data() + v.size());
    vec = std::vector<int>({ 1, 2, 3 });
    CHECK(version == vec);

    v = omw::Version("1.-2.-3");
    version = std::vector<int>(v.data(), v.data() + v.size());
    vec = std::vector<int>({ 1, -2, -3 });
    CHECK(version == vec);

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
    CHECK(omw::Version(UINT32_MAX, INT32_MAX, INT32_MIN).toString() == std::string("-1.2147483647.-2147483648"));



    const std::vector<int> v = omw::Version(123, 456, 789).toVector();
    const std::vector<int> vec = { 123, 456, 789 };

    bool eq = true;
    for (size_t i = 0; i < v.size(); ++i)
    {
        if (v[i] != vec[i]) eq = false;
    }

    CHECK(v.capacity() == 3);
    CHECK(eq);
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
