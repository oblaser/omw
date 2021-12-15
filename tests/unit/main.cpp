/*
author          Oliver Blaser
date            14.12.2021
copyright       MIT - Copyright (c) 2021 Oliver Blaser
*/

#include <iostream>

#include <omw/omw.h>
#include <omw/windows/windows.h>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>


TEST_CASE("omw lib")
{
#ifdef OMW_PLAT_WIN
    CHECK(omw::windows::consoleEnVirtualTermProc());
#endif

    std::cout << std::endl << "Testing OMW ..." << std::endl;

    std::cout << std::endl << omw::info::infoTxt() << std::endl;

    REQUIRE(omw::info::version() == omw::Version(0, 1, 1002));
}


#include "algorithm.hpp"
#include "cli.hpp"
#include "color.hpp"
#include "io_serialPort.hpp"
#include "string.hpp"
#include "utility.hpp"
#include "version.hpp"
#include "windows_envVar.hpp"
#include "windows_string.hpp"






#ifdef OMW_PLAT_WIN

#include <cmath>

TEST_CASE("windows.h beep() & some perfCntr..()")
{
    uint32_t freq1, freq2;
    const uint32_t dur = 200;

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

    CHECK(omw::windows::beep(freq1, dur));
    omw::windows::perfCntrSleep_ms(dur + 2);

    const auto start = omw::windows::perfCntrGetTick();
    CHECK(omw::windows::beep(freq2, dur, true));
    const auto stop = omw::windows::perfCntrGetTick();

    const double dDur = (double)dur / 1'000.0;
    const double measDur = omw::windows::perfCntrCalcDuration(start, stop);
    const double absError = std::abs(measDur - dDur);
    const double relError = absError / dDur;
    const double absErrorTh = 0.01; // 10ms
    const double relErrorTh = 0.01; // 1%

    std::cout << "\n" << omw::fgBrightBlack << "Beep Test" << std::endl;
    std::cout << "duration:\n";
    std::cout << "absolute error [s]: " << absError << " < " << absErrorTh << std::endl;
    std::cout << "relative error [%]: " << (relError * 100) << " < " << (relErrorTh * 100) << std::endl;
    std::cout << omw::normal << std::endl;

    CHECK(absError < absErrorTh);
    CHECK(relError < relErrorTh);
}

#endif
