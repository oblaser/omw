/*
author          Oliver Blaser
date            16.02.2025
copyright       MIT - Copyright (c) 2025 Oliver Blaser
*/

#ifndef TEST_OMW_CLOCK_H
#define TEST_OMW_CLOCK_H

#include <cstdint>

#include "catch2/catch.hpp"
#include "testUtil.h"

#include <omw/clock.h>
#include <omw/defs.h>

#ifdef OMW_PLAT_WIN
#include <Windows.h>
#else
#include <time.h>
#include <unistd.h>
#endif



TEST_CASE("clock.h constant expressions")
{
    CHECK(OMW_SECOND_s == 1);
    CHECK(OMW_MINUTE_s == 60);
    CHECK(OMW_HOUR_s == 3600);
    CHECK(OMW_DAY_s == 86400);

    CHECK(OMW_SECOND_ms == 1000);
    CHECK(OMW_MINUTE_ms == 60000);
    CHECK(OMW_HOUR_ms == 3600000);
    CHECK(OMW_DAY_ms == 86400000);

    CHECK(OMW_SECOND_us == 1000000);
    CHECK(OMW_MINUTE_us == 60000000);
    CHECK(OMW_HOUR_us == 3600000000ll);
    CHECK(OMW_DAY_us == 86400000000ll);

    CHECK(OMW_TIMEPOINT_MIN == INT64_MIN);
    CHECK(OMW_TIMEPOINT_MAX == INT64_MAX);



    CHECK(omw::clock::second_s == OMW_SECOND_s);
    CHECK(omw::clock::minute_s == OMW_MINUTE_s);
    CHECK(omw::clock::hour_s == OMW_HOUR_s);
    CHECK(omw::clock::day_s == OMW_DAY_s);

    CHECK(omw::clock::second_ms == OMW_SECOND_ms);
    CHECK(omw::clock::minute_ms == OMW_MINUTE_ms);
    CHECK(omw::clock::hour_ms == OMW_HOUR_ms);
    CHECK(omw::clock::day_ms == OMW_DAY_ms);

    CHECK(omw::clock::second_us == OMW_SECOND_us);
    CHECK(omw::clock::minute_us == OMW_MINUTE_us);
    CHECK(omw::clock::hour_us == OMW_HOUR_us);
    CHECK(omw::clock::day_us == OMW_DAY_us);

    CHECK(omw::clock::timepoint_min == OMW_TIMEPOINT_MIN);
    CHECK(omw::clock::timepoint_max == OMW_TIMEPOINT_MAX);
}

TEST_CASE("clock.h omw::clock::now() measure system sleep")
{
    omw::clock::timepoint_t start, duration;



    start = omw::clock::now();
#ifdef OMW_PLAT_WIN
    Sleep(1000);
#else
    sleep(1);
#endif
    duration = omw::clock::now() - start;

    CHECK(duration >= (990 * 1000ll));
    CHECK(duration <= (1050 * 1000ll));



    start = omw::clock::now();
#ifdef OMW_PLAT_WIN
    Sleep(10);
#else
    usleep(10 * 1000);
#endif
    duration = omw::clock::now() - start;

    CHECK(duration >= (9900ll));

#ifdef OMW_PLAT_WIN
    CHECK(duration <= (12000ll));
#else
    CHECK(duration <= (10500ll));
#endif
}

TEST_CASE("clock.h omw::clock::elapsed_..()")
{
    const omw::clock::timepoint_t tpStart = omw::clock::now();
    omw::clock::timepoint_t tpEnd;

    tpEnd = tpStart + 1;
    CHECK(omw::clock::elapsed_ms(tpEnd, tpStart, 0) == true);
    CHECK(omw::clock::elapsed_us(tpEnd, tpStart, 0) == true);
    CHECK(omw::clock::elapsed_ms(tpEnd, tpStart, 1) == false);
    CHECK(omw::clock::elapsed_us(tpEnd, tpStart, 1) == true);
    CHECK(omw::clock::elapsed_ms(tpEnd, tpStart, 2) == false);
    CHECK(omw::clock::elapsed_us(tpEnd, tpStart, 2) == false);

    tpEnd = tpStart + 10000;
    CHECK(omw::clock::elapsed_ms(tpEnd, tpStart, 0) == true);
    CHECK(omw::clock::elapsed_us(tpEnd, tpStart, 0) == true);
    CHECK(omw::clock::elapsed_ms(tpEnd, tpStart, 1) == true);
    CHECK(omw::clock::elapsed_us(tpEnd, tpStart, 1) == true);

    CHECK(omw::clock::elapsed_ms(tpEnd, tpStart, 9) == true);
    CHECK(omw::clock::elapsed_us(tpEnd, tpStart, 9999) == true);

    CHECK(omw::clock::elapsed_ms(tpEnd, tpStart, 10) == true);
    CHECK(omw::clock::elapsed_us(tpEnd, tpStart, 10000) == true);

    CHECK(omw::clock::elapsed_ms(tpEnd, tpStart, 11) == false);
    CHECK(omw::clock::elapsed_us(tpEnd, tpStart, 10001) == false);

    CHECK(omw::clock::elapsed_ms(tpEnd, tpStart, 12) == false);
    CHECK(omw::clock::elapsed_us(tpEnd, tpStart, 10002) == false);

    CHECK(omw::clock::elapsed_ms(tpEnd, tpStart, 100) == false);
    CHECK(omw::clock::elapsed_us(tpEnd, tpStart, 100000) == false);
}

TEST_CASE("clock.h omw::clock::fromTimespec()")
{
    time_t sec;
    int32_t nsec;

#if OMW_PLAT_UNIX || (OMW_CPPSTD >= OMW_CPPSTD_17)
    struct timespec tspec;
#endif



    sec = 123;
    nsec = 456789;

    CHECK(omw::clock::fromTimespec(sec, nsec) == 123000456);
    CHECK(omw::clock::fromTimespec(sec, nsec) == omw::clock::fromTimespec(123, 456000));

#if OMW_PLAT_UNIX || (OMW_CPPSTD >= OMW_CPPSTD_17)
    tspec.tv_sec = sec;
    tspec.tv_nsec = nsec;
    CHECK(omw::clock::fromTimespec(sec, nsec) == omw::clock::fromTimespec(tspec));
    CHECK(omw::clock::fromTimespec(sec, nsec) == omw::clock::fromTimespec(&tspec));
#endif



    sec = 3;
    nsec = 999;

    CHECK(omw::clock::fromTimespec(sec, nsec) == 3000000);

#if OMW_PLAT_UNIX || (OMW_CPPSTD >= OMW_CPPSTD_17)
    tspec.tv_sec = sec;
    tspec.tv_nsec = nsec;
    CHECK(omw::clock::fromTimespec(sec, nsec) == omw::clock::fromTimespec(tspec));
    CHECK(omw::clock::fromTimespec(sec, nsec) == omw::clock::fromTimespec(&tspec));
#endif



    sec = -5;
    nsec = 999999999;

    CHECK(omw::clock::fromTimespec(sec, nsec) == -4000001);

#if OMW_PLAT_UNIX || (OMW_CPPSTD >= OMW_CPPSTD_17)
    tspec.tv_sec = sec;
    tspec.tv_nsec = nsec;
    CHECK(omw::clock::fromTimespec(sec, nsec) == omw::clock::fromTimespec(tspec));
    CHECK(omw::clock::fromTimespec(sec, nsec) == omw::clock::fromTimespec(&tspec));
#endif



    sec = -3;
    nsec = 123000987;

    CHECK(omw::clock::fromTimespec(sec, nsec) == -2877000);

#if OMW_PLAT_UNIX || (OMW_CPPSTD >= OMW_CPPSTD_17)
    tspec.tv_sec = sec;
    tspec.tv_nsec = nsec;
    CHECK(omw::clock::fromTimespec(sec, nsec) == omw::clock::fromTimespec(tspec));
    CHECK(omw::clock::fromTimespec(sec, nsec) == omw::clock::fromTimespec(&tspec));
#endif



    sec = -123;
    nsec = 456012345;

    CHECK(omw::clock::fromTimespec(sec, nsec) == -122543988);

#if OMW_PLAT_UNIX || (OMW_CPPSTD >= OMW_CPPSTD_17)
    tspec.tv_sec = sec;
    tspec.tv_nsec = nsec;
    CHECK(omw::clock::fromTimespec(sec, nsec) == omw::clock::fromTimespec(tspec));
    CHECK(omw::clock::fromTimespec(sec, nsec) == omw::clock::fromTimespec(&tspec));
#endif
}



#endif // TEST_OMW_CLI_H
