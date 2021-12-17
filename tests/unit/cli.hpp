/*
author          Oliver Blaser
date            17.12.2021
copyright       MIT - Copyright (c) 2021 Oliver Blaser
*/

#ifndef TEST_OMW_CLI_H
#define TEST_OMW_CLI_H

#include <string>
#include <vector>

#include "testUtil.h"

#include <catch2/catch.hpp>
#include <omw/cli.h>



TEST_CASE("cli.h ANSI ESC")
{
    CHECK(omw::ansiesc::argSepChar == ';');
    CHECK(omw::ansiesc::escChar == '\033');

    CHECK(omw::ansiesc::singleShiftTwo == 'N');
    CHECK(omw::ansiesc::singleShiftThree == 'O');
    CHECK(omw::ansiesc::deviceControlString == 'P');
    CHECK(omw::ansiesc::controlSequenceIntroducer == '[');
    CHECK(omw::ansiesc::stringTerminator == '\\');
    CHECK(omw::ansiesc::osCommand == ']');
    CHECK(omw::ansiesc::startOfString == 'X');
    CHECK(omw::ansiesc::privacyMessage == '^');
    CHECK(omw::ansiesc::appProgramCommand == '_');
}

TEST_CASE("cli.h ANSI ESC mode and sequence builder")
{
    // check initial state
    CHECK(omw::ansiesc::getMode() == omw::ansiesc::MODE_DEFAULT);
#ifdef _WIN32
    CHECK(omw::ansiesc::isEnabled() == false);
#else
    CHECK(omw::ansiesc::isEnabled() == true);
#endif

    omw::ansiesc::enable();
    CHECK(omw::ansiesc::getMode() == omw::ansiesc::MODE_ENABLED);
    CHECK(omw::ansiesc::isEnabled() == true);

    omw::ansiesc::disable();
    CHECK(omw::ansiesc::getMode() == omw::ansiesc::MODE_DISABLED);
    CHECK(omw::ansiesc::isEnabled() == false);

    omw::ansiesc::setMode(omw::ansiesc::MODE_DEFAULT);
    CHECK(omw::ansiesc::getMode() == omw::ansiesc::MODE_DEFAULT);
#ifdef _WIN32
    CHECK(omw::ansiesc::isEnabled() == false);
#else
    CHECK(omw::ansiesc::isEnabled() == true);
#endif

    omw::ansiesc::setMode(omw::ansiesc::MODE_ENABLED);
    CHECK(omw::ansiesc::getMode() == omw::ansiesc::MODE_ENABLED);
    CHECK(omw::ansiesc::isEnabled() == true);

    CHECK(tu::strcmp(omw::ansiesc::seq('?'), "\033?") == 0);
    CHECK(tu::strcmp(omw::ansiesc::seq('#', "<arg>"), "\033#<arg>") == 0);
    CHECK(tu::strcmp(omw::ansiesc::seq('&', std::to_string(-56)), "\033&-56") == 0);

    omw::ansiesc::setMode(omw::ansiesc::MODE_DISABLED);
    CHECK(omw::ansiesc::getMode() == omw::ansiesc::MODE_DISABLED);
    CHECK(omw::ansiesc::isEnabled() == false);

    CHECK(tu::strcmp(omw::ansiesc::seq('?'), "") == 0);
    CHECK(tu::strcmp(omw::ansiesc::seq('#', "<arg>"), "") == 0);
    CHECK(tu::strcmp(omw::ansiesc::seq('&', std::to_string(-56)), "") == 0);



    omw::ansiesc::enable(); // needed for the next test cases
}

TEST_CASE("cli.h CSI sequence biulders")
{
    CHECK(tu::strcmp(omw::ansiesc::csi::seq('?'), "\033[?") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::seq('#', "<arg>"), "\033[<arg>#") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::seq('&', 5), "\033[5&") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::seq('%', 8, 4), "\033[8;4%") == 0);
}

TEST_CASE("cli.h CSI Sequence Types")
{
    CHECK(tu::strcmp(omw::ansiesc::csi::seq(omw::ansiesc::csi::cursorBack, 1), "\033[1D") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::seq(omw::ansiesc::csi::cursorDown, 5), "\033[5B") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::seq(omw::ansiesc::csi::cursorFwd), "\033[C") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::seq(omw::ansiesc::csi::cursorPos, 2, 3), "\033[2;3H") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::seq(omw::ansiesc::csi::cursorUp), "\033[A") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::seq(omw::ansiesc::csi::eraseDisplay, omw::ansiesc::csi::fromCurToBegin), "\033[1J") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::seq(omw::ansiesc::csi::eraseDisplay, omw::ansiesc::csi::fromCurToEnd), "\033[0J") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::seq(omw::ansiesc::csi::eraseDisplay, omw::ansiesc::csi::entire), "\033[2J") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::seq(omw::ansiesc::csi::eraseDisplay, omw::ansiesc::csi::entireAndScrlBk), "\033[3J") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::seq(omw::ansiesc::csi::eraseLine, omw::ansiesc::csi::fromCurToBegin), "\033[1K") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::seq(omw::ansiesc::csi::eraseLine, omw::ansiesc::csi::fromCurToEnd), "\033[0K") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::seq(omw::ansiesc::csi::eraseLine, omw::ansiesc::csi::entire), "\033[2K") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::seq(omw::ansiesc::csi::scrollDown, 8), "\033[8T") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::seq(omw::ansiesc::csi::scrollUp, 6), "\033[6S") == 0);
}

TEST_CASE("cli.h SGR sequence biulders")
{
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(), "\033[m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq("<arg>"), "\033[<arg>m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(1), "\033[1m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(1, 2, 3), "\033[1;2;3m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(9, 8, 7, 6, 5), "\033[9;8;7;6;5m") == 0);

    const int sgr1[] = { 28, 7, 21, 5, 4 };
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(sgr1, (sizeof(sgr1) / sizeof(sgr1[0]))), "\033[28;7;21;5;4m") == 0);

    const std::vector<int> sgr2 = { 4, 59, 6, 16, 45, 68, 7 };
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(sgr2), "\033[4;59;6;16;45;68;7m") == 0);
}

TEST_CASE("cli.h SGR parameters and arguments")
{
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::reset), "\033[0m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::bold), "\033[1m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::faint), "\033[2m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::italic), "\033[3m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::underline), "\033[4m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::blinkSlow), "\033[5m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::blinkFast), "\033[6m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::reverseVideo), "\033[7m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::conceal), "\033[8m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::strike), "\033[9m") == 0);

    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::defaultFont), "\033[10m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::font0), "\033[10m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::font1), "\033[11m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::font2), "\033[12m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::font3), "\033[13m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::font4), "\033[14m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::font5), "\033[15m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::font6), "\033[16m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::font7), "\033[17m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::font8), "\033[18m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::font9), "\033[19m") == 0);

    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::fraktur), "\033[20m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[21m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::boldFaintOff), "\033[22m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::boldOff), "\033[22m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::faintOff), "\033[22m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::italicFrakturOff), "\033[23m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::italicOff), "\033[23m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::frakturOff), "\033[23m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::underlineOff), "\033[24m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::blinkOff), "\033[25m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[26m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::reverseVideoOff), "\033[27m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::concealOff), "\033[28m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::reveal), "\033[28m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::strikeOff), "\033[29m") == 0);

    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::fgColorBlack), "\033[30m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::fgColorRed), "\033[31m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::fgColorGreen), "\033[32m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::fgColorYellow), "\033[33m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::fgColorBlue), "\033[34m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::fgColorMagenta), "\033[35m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::fgColorCyan), "\033[36m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::fgColorWhite), "\033[37m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::setForeColor, omw::ansiesc::csi::sgr::setColor_8bit, 40), "\033[38;5;40m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::setForeColor, omw::ansiesc::csi::sgr::setColor_rgb, 1, 2, 3), "\033[38;2;1;2;3m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::defaultForeColor), "\033[39m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::fgColorDefault), "\033[39m") == 0);

    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::bgColorBlack), "\033[40m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::bgColorRed), "\033[41m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::bgColorGreen), "\033[42m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::bgColorYellow), "\033[43m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::bgColorBlue), "\033[44m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::bgColorMagenta), "\033[45m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::bgColorCyan), "\033[46m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::bgColorWhite), "\033[47m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::setBackColor, omw::ansiesc::csi::sgr::setColor_8bit, 36), "\033[48;5;36m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::setBackColor, omw::ansiesc::csi::sgr::setColor_rgb, 9, 8, 7), "\033[48;2;9;8;7m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::defaultBackColor), "\033[49m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::bgColorDefault), "\033[49m") == 0);

    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[50m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::framed), "\033[51m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::encircled), "\033[52m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::overlined), "\033[53m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::framedEncircledOff), "\033[54m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::framedOff), "\033[54m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::encircledOff), "\033[54m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::overlinedOff), "\033[55m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[56m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[57m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::setUnderlineColor, omw::ansiesc::csi::sgr::setColor_8bit, 60), "\033[58;5;60m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::setUnderlineColor, omw::ansiesc::csi::sgr::setColor_rgb, 5, 4, 2), "\033[58;2;5;4;2m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::defaultUnderlineColor), "\033[59m") == 0);

    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[70m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[71m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[72m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::super), "\033[73m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::sub), "\033[74m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::superSubOff), "\033[75m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::superOff), "\033[75m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::subOff), "\033[75m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[76m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[77m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[78m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[79m") == 0);

    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::fgColorBrightBlack), "\033[90m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::fgColorBrightRed), "\033[91m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::fgColorBrightGreen), "\033[92m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::fgColorBrightYellow), "\033[93m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::fgColorBrightBlue), "\033[94m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::fgColorBrightMagenta), "\033[95m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::fgColorBrightCyan), "\033[96m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::fgColorBrightWhite), "\033[97m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[98m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[99m") == 0);

    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::bgColorBrightBlack), "\033[100m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::bgColorBrightRed), "\033[101m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::bgColorBrightGreen), "\033[102m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::bgColorBrightYellow), "\033[103m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::bgColorBrightBlue), "\033[104m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::bgColorBrightMagenta), "\033[105m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::bgColorBrightCyan), "\033[106m") == 0);
    CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::bgColorBrightWhite), "\033[107m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[108m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[109m") == 0);
}

TEST_CASE("cli.h SGR")
{
    for (size_t i = 0; i < 10; ++i)
    {
        CHECK(tu::strcmp(omw::font(i).arg(), "\033[" + omw::to_string(omw::ansiesc::csi::sgr::font_base + i) + "m") == 0);
    }
}

#ifdef OMW_PLAT_WIN
TEST_CASE("set ansiesc mode")
{
    omw::ansiesc::enable(omw::windows::consoleEnVirtualTermProc());
    CHECK(1 == 1);
}
#endif


#endif // TEST_OMW_CLI_H
