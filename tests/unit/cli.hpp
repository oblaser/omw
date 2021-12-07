/*
author          Oliver Blaser
date            07.12.2021
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
    CHECK(omw::ansiesc::csiChar == '[');
    CHECK(omw::ansiesc::stChar == '\\');
    CHECK(omw::ansiesc::oscChar == ']');
    CHECK(omw::ansiesc::sosChar == 'X');
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

TEST_CASE("cli.h SGR")
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

    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[10m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[11m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[12m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[13m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[14m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[15m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[16m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[17m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[18m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[19m") == 0);

    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[20m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[21m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[22m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[23m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[24m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[25m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[26m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[27m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[28m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[29m") == 0);

    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[30m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[31m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[32m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[33m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[34m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[35m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[36m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[37m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[38m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[39m") == 0);

    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[40m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[41m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[42m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[43m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[44m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[45m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[46m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[47m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[48m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[49m") == 0);

    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[50m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[51m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[52m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[53m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[54m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[55m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[56m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[57m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[58m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[59m") == 0);

    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[60m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[61m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[62m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[63m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[64m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[65m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[66m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[67m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[68m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[69m") == 0);

    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[70m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[71m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[72m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[73m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[74m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[75m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[76m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[77m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[78m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[79m") == 0);

    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[80m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[81m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[82m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[83m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[84m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[85m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[86m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[87m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[88m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[89m") == 0);

    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[90m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[91m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[92m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[93m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[94m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[95m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[96m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[97m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[98m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[99m") == 0);

    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[100m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[101m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[102m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[103m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[104m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[105m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[106m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[107m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[108m") == 0);
    //CHECK(tu::strcmp(omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::), "\033[109m") == 0);
}


#endif // TEST_OMW_CLI_H
