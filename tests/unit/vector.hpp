/*
author          Oliver Blaser
date            13.03.2023
copyright       MIT - Copyright (c) 2023 Oliver Blaser
*/

#ifndef TEST_OMW_VECTOR_H
#define TEST_OMW_VECTOR_H

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <vector>

#include "catch2/catch.hpp"

#include <omw/vector.h>



TEST_CASE("vector.h omw::contains()")
{
    const std::vector<int> vInt = { 1, 5, 9 };
    CHECK(omw::contains(vInt, 1));
    CHECK_FALSE(omw::contains(vInt, 0));

    const std::vector<std::string> vStdString = { "the", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog" };
    CHECK(omw::contains(vStdString, std::string("fox")));
    CHECK_FALSE(omw::contains(vStdString, std::string("boat")));

    const omw::vector<omw::string> vString = { "pack", "my", "box", "with", "five", "dozen", "liquor", "jugs" };
    CHECK(omw::contains(vString, omw::string("five")));
    CHECK_FALSE(omw::contains(vString, omw::string("boat")));
}

TEST_CASE("vector.h omw::vector ctor")
{
    constexpr size_t dataSize = 10;
    const int data[dataSize] = { 0, 11, 22, 33, 44, 55, 66, 77, 88, 99 };
    const std::vector<int> r(data, data + dataSize);
    const std::vector<int> r_omw(data, data + dataSize);

    CHECK(r_omw == r);
    CHECK(omw::vector<int>(r) == r);
    CHECK(omw::vector<int>(r) == r_omw);
    
    omw::vector<int> v = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    std::for_each(v.begin(), v.end(), [](int& val) { val *= 11; });
    CHECK(v == r);
}

TEST_CASE("vector.h omw::vector::contains()")
{
    const omw::vector<int> vInt = { 1, 5, 9 };
    CHECK(vInt.contains(1));
    CHECK_FALSE(vInt.contains(0));

    const omw::vector<std::string> vStdString = { "the", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog" };
    CHECK(vStdString.contains("fox"));
    CHECK_FALSE(vStdString.contains("boat"));

    const omw::vector<omw::string> vString = { "pack", "my", "box", "with", "five", "dozen", "liquor", "jugs" };
    CHECK(vString.contains("five"));
    CHECK_FALSE(vString.contains("boat"));
}

#if (defined(OMW_DEBUG) && 0) // || 1
#include <iostream>
#define UTILITY_TEST_VECRESERVEMORE_COUTEN 1
#endif
TEST_CASE("vector.h vector.h omw::vector::reserveAdd()")
{
    omw::vector<int> v;

#ifdef UTILITY_TEST_VECRESERVEMORE_COUTEN
    std::cout << v.capacity() << std::endl;
#endif
    v.reserveAdd(5);
#ifdef UTILITY_TEST_VECRESERVEMORE_COUTEN
    std::cout << v.capacity() << std::endl;
#endif
    CHECK(v.capacity() >= (v.size() + 5));


    v.assign(50, -1);
#ifdef UTILITY_TEST_VECRESERVEMORE_COUTEN
    std::cout << v.capacity() << std::endl;
#endif
    v.reserveAdd(20);
#ifdef UTILITY_TEST_VECRESERVEMORE_COUTEN
    std::cout << v.capacity() << std::endl;
#endif
    CHECK(v.capacity() >= (v.size() + 20));


    v.shrink_to_fit();
#ifdef UTILITY_TEST_VECRESERVEMORE_COUTEN
    std::cout << v.capacity() << std::endl;
#endif
    v.reserveAdd(3);
#ifdef UTILITY_TEST_VECRESERVEMORE_COUTEN
    std::cout << v.capacity() << std::endl;
#endif
    CHECK(v.capacity() >= (v.size() + 3));


    for (size_t i = 0; i < 100; ++i) v.push_back(3);
#ifdef UTILITY_TEST_VECRESERVEMORE_COUTEN
    std::cout << v.capacity() << std::endl;
#endif
    v.reserveAdd(3);
#ifdef UTILITY_TEST_VECRESERVEMORE_COUTEN
    std::cout << v.capacity() << std::endl;
#endif
    CHECK(v.capacity() >= (v.size() + 3));


    v.shrink_to_fit();
#ifdef UTILITY_TEST_VECRESERVEMORE_COUTEN
    std::cout << v.capacity() << std::endl;
#endif
    v.reserveAdd(3);
#ifdef UTILITY_TEST_VECRESERVEMORE_COUTEN
    std::cout << v.capacity() << std::endl;
#endif
    CHECK(v.capacity() >= (v.size() + 3));
}



#endif // TEST_OMW_VECTOR_H
