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
}

#if (defined(OMW_DEBUG) && 0) // || 1
#include <iostream>
#define UTILITY_TEST_VECRESERVEMORE_COUTEN 1
#endif
TEST_CASE("vector.h omw::reserveAdditional()")
{
    std::vector<int> v;

#ifdef UTILITY_TEST_VECRESERVEMORE_COUTEN
    std::cout << v.capacity() << std::endl;
#endif
    omw::reserveAdditional(v, 5);
#ifdef UTILITY_TEST_VECRESERVEMORE_COUTEN
    std::cout << v.capacity() << std::endl;
#endif
    CHECK(v.capacity() >= (v.size() + 5));


    v.assign(50, -1);
#ifdef UTILITY_TEST_VECRESERVEMORE_COUTEN
    std::cout << v.capacity() << std::endl;
#endif
    omw::reserveAdditional(v, 20);
#ifdef UTILITY_TEST_VECRESERVEMORE_COUTEN
    std::cout << v.capacity() << std::endl;
#endif
    CHECK(v.capacity() >= (v.size() + 20));


    v.shrink_to_fit();
#ifdef UTILITY_TEST_VECRESERVEMORE_COUTEN
    std::cout << v.capacity() << std::endl;
#endif
    omw::reserveAdditional(v, 3);
#ifdef UTILITY_TEST_VECRESERVEMORE_COUTEN
    std::cout << v.capacity() << std::endl;
#endif
    CHECK(v.capacity() >= (v.size() + 3));


    for (size_t i = 0; i < 100; ++i) v.push_back(3);
#ifdef UTILITY_TEST_VECRESERVEMORE_COUTEN
    std::cout << v.capacity() << std::endl;
#endif
    omw::reserveAdditional(v, 3);
#ifdef UTILITY_TEST_VECRESERVEMORE_COUTEN
    std::cout << v.capacity() << std::endl;
#endif
    CHECK(v.capacity() >= (v.size() + 3));


    v.shrink_to_fit();
#ifdef UTILITY_TEST_VECRESERVEMORE_COUTEN
    std::cout << v.capacity() << std::endl;
#endif
    omw::reserveAdditional(v, 3);
#ifdef UTILITY_TEST_VECRESERVEMORE_COUTEN
    std::cout << v.capacity() << std::endl;
#endif
    CHECK(v.capacity() >= (v.size() + 3));
}



#endif // TEST_OMW_VECTOR_H
