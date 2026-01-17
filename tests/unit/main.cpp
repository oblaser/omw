/*
author          Oliver Blaser
date            30.12.2025
copyright       MIT - Copyright (c) 2025 Oliver Blaser
*/

#include <iostream>

#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include <omw/cli.h>
#include <omw/defs.h>
#include <omw/omw.h>
#include <omw/windows/windows.h>


TEST_CASE("omw lib")
{
    std::cout << std::endl << "Testing OMW - C++" << std::to_string(OMW_CPPSTD).substr(2, 2) << " (" << OMW_CPPSTD << ')' << std::endl;

    std::cout << std::endl << omw::info::infoTxt() << std::endl;

    CHECK(omw::info::version() == omw::Semver(0, 3, 1, "alpha"));
    CHECK(OMW_VERSION_ID == 260117);

    CHECK(omw::info::version() == omw::Semver(OMW_VERSION_MAJ, OMW_VERSION_MIN, OMW_VERSION_PAT, OMW_VERSION_PRSTR));
}



#ifdef OMW_PLAT_WIN

#include <cmath>

TEST_CASE("windows.h beep() & some perfCntr..()")
{
    uint32_t freq1, freq2;
    const uint32_t dur = 200;

    if (!omw::info::version().isPreRelease())
    {
        freq1 = 700;
        freq2 = 900;
    }
    else
    {
        freq1 = 22000;
        freq2 = 22000;
    }

    CHECK(omw::windows::beep(freq1, dur));
    omw::windows::perfCntrSleep_ms(dur + 2);

    const auto start = omw::windows::perfCntrGetTick();
    CHECK(omw::windows::beep(freq2, dur, true));
    const auto stop = omw::windows::perfCntrGetTick();

    const double dDur = (double)dur / 1000.0;
    const double measDur = omw::windows::perfCntrCalcDuration(start, stop);
    const double absError = std::abs(measDur - dDur);
    const double relError = absError / dDur;
#ifdef OMW_DEBUG
    const double absErrorTh = 0.01; // 10ms
    const double relErrorTh = 0.05; // 5%
#else
    const double absErrorTh = 0.005; // 5ms
    const double relErrorTh = 0.02;  // 2%
#endif

    std::cout << "\n" << omw::fgBrightBlack << "Beep Test" << std::endl;
    std::cout << "duration:\n";
    std::cout << "absolute error [s]: " << absError << " < " << absErrorTh << std::endl;
    std::cout << "relative error [%]: " << (relError * 100) << " < " << (relErrorTh * 100) << std::endl;
    std::cout << omw::normal << std::endl;

    CHECK(absError < absErrorTh);
    CHECK(relError < relErrorTh);
}

#endif
