/*
author          Oliver Blaser
date            06.12.2021
copyright       MIT - Copyright (c) 2021 Oliver Blaser
*/

#include <iostream>

#include <omw/omw.h>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp> // $(sdk)/catch2/catch.hpp


TEST_CASE("omw lib")
{
    std::cout << std::endl << "Testing OMW ..." << std::endl;

    std::cout << std::endl << omw::info::infoTxt() << std::endl;

    REQUIRE(omw::info::version() == omw::Version(0, 1, 1001));
}


#include "algorithm.hpp"
#include "cli.hpp"
#include "color.hpp"
#include "string.hpp"
#include "utility.hpp"
#include "version.hpp"
#include "windows_envVar.hpp"
#include "windows_string.hpp"





#include <cmath>
#include <omw/windows/windows.h>

#ifdef OMW_PLAT_WIN

TEST_CASE("windows.h")
{
    uint32_t freq1, freq2;

    if (omw::info::version().rev() < 1000)
    {
        freq1 = 700;
        freq2 = 900;
    }
    else
    {
        freq1 = 20000;
        freq2 = 20000;
    }

    CHECK(omw::windows::beep(freq1, 200));
    omw::windows::perfCntrSleep_ms(205);

    const uint32_t dur = 200;
    const auto start = omw::windows::perfCntrGetTick();
    CHECK(omw::windows::beep(freq2, dur, true));
    const auto stop = omw::windows::perfCntrGetTick();

    const double dDur = (double)dur / 1'000.0;
    const double measDur = omw::windows::perfCntrCalcDuration(start, stop);
    const double absError = std::abs(measDur - dDur);
    const double relError = absError / dDur;
    const double absErrorTh = 0.01; // 10ms
    const double relErrorTh = 0.01; // 1%

    std::cout << "\nBeep Test" << std::endl;
    std::cout << "duration:\n";
    std::cout << "absolute error [s]: " << absError << " < " << absErrorTh << std::endl;
    std::cout << "relative error [%]: " << (relError * 100) << " < " << (relErrorTh * 100) << std::endl;
    std::cout << std::endl;

    CHECK(absError < absErrorTh);
    CHECK(relError < relErrorTh);

}

#endif
