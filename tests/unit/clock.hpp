/*
author          Oliver Blaser
date            16.02.2025
copyright       MIT - Copyright (c) 2025 Oliver Blaser
*/

#ifndef TEST_OMW_CLOCK_H
#define TEST_OMW_CLOCK_H

#include "catch2/catch.hpp"
#include "testUtil.h"

#include <omw/clock.h>
#include <omw/defs.h>

#ifdef OMW_PLAT_WIN
#include <Windows.h>
#else
#include <unistd.h>
#endif



TEST_CASE("clock.h omw::clock::get measure system sleep")
{
    omw::clock::timepoint_t start, duration;



    start = omw::clock::get();
#ifdef OMW_PLAT_WIN
    Sleep(1000);
#else
    sleep(1);
#endif
    duration = omw::clock::get() - start;

    CHECK(duration >= (950 * 1000ll));
    CHECK(duration <= (1050 * 1000ll));



    start = omw::clock::get();
#ifdef OMW_PLAT_WIN
    Sleep(10);
#else
    usleep(10 * 1000);
#endif
    duration = omw::clock::get() - start;

    CHECK(duration >= (9500ll));
    // CHECK(duration <= (10500ll));
    CHECK(duration <= (11 * 1000ll));
}

// TODO add test cases for elapsed_*() and fromTimespec()



#endif // TEST_OMW_CLI_H
