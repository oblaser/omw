/*
author          Oliver Blaser
date            17.12.2021
copyright       MIT - Copyright (c) 2021 Oliver Blaser
*/

#ifndef TEST_OMW_ALGORITHM_H
#define TEST_OMW_ALGORITHM_H

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include "catch2/catch.hpp"
#include "testUtil.h"

#include <omw/algorithm.h>
#include <omw/cli.h>
#include <omw/int.h>
#include <omw/string.h>



class DoubleDabbleTestRecord
{
public:
    DoubleDabbleTestRecord(const omw::string& expectedResult, uint64_t valueH, uint64_t valueL)
        : value128(valueH, valueL), value64H(valueH), value64L(valueL), expResult(expectedResult)
    {
        value32H = (uint32_t)(valueH >> 32);
        value32HM = (uint32_t)valueH;
        value32LM = (uint32_t)(valueL >> 32);
        value32L = (uint32_t)valueL;

        value8buffer[0] = (uint8_t)(value32H >> 24);
        value8buffer[1] = (uint8_t)(value32H >> 16);
        value8buffer[2] = (uint8_t)(value32H >> 8);
        value8buffer[3] = (uint8_t)(value32H);
        value8buffer[4] = (uint8_t)(value32HM >> 24);
        value8buffer[5] = (uint8_t)(value32HM >> 16);
        value8buffer[6] = (uint8_t)(value32HM >> 8);
        value8buffer[7] = (uint8_t)(value32HM);
        value8buffer[8] = (uint8_t)(value32LM >> 24);
        value8buffer[9] = (uint8_t)(value32LM >> 16);
        value8buffer[10] = (uint8_t)(value32LM >> 8);
        value8buffer[11] = (uint8_t)(value32LM);
        value8buffer[12] = (uint8_t)(value32L >> 24);
        value8buffer[13] = (uint8_t)(value32L >> 16);
        value8buffer[14] = (uint8_t)(value32L >> 8);
        value8buffer[15] = (uint8_t)(value32L);
    }
    virtual ~DoubleDabbleTestRecord() {}

    omw::uint128_t value128;
    uint8_t value8buffer[16];
    uint32_t value32H;
    uint32_t value32HM;
    uint32_t value32LM;
    uint32_t value32L;
    uint64_t value64H;
    uint64_t value64L;

    omw::string expResult;
};

TEST_CASE("algorithm.h doubleDabble128()")
{
    // https://www.convzone.com/hex-to-decimal/

    std::vector<DoubleDabbleTestRecord> testRecords =
    {
        DoubleDabbleTestRecord("0000000000000000000000000000000000000001", 0x00, 0x01),
        DoubleDabbleTestRecord("0000000000000000000009223372036854775808", 0x00, INT64_MIN),
        DoubleDabbleTestRecord("00000000000000000000000000000000000" + omw::to_string(0xFFFF), 0x00, 0xFFFF),
        DoubleDabbleTestRecord("000000000000000000000000000000" + omw::to_string(INT32_MAX), 0x00, INT32_MAX),
        DoubleDabbleTestRecord("0000000000000001208925819614629174706175", 0xFFFF, 0xFFFFFFFFFFFFFFFF),
        DoubleDabbleTestRecord("0000000000000000604462909807314587354597", 0x8000, 0x00000000000005E5),
        DoubleDabbleTestRecord("0340282366920938463463374607431768211455", 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF),
        DoubleDabbleTestRecord("0001512366075204170929049582354406559215", 0x0123456789abcdef, 0x0123456789abcdef),
        DoubleDabbleTestRecord("0000000000000000000000000000000000000000", 0x00, 0x00)
    };

    bool stdOut = false;

    for (size_t i = 0; i < testRecords.size(); ++i)
    {
        const DoubleDabbleTestRecord& tr = testRecords[i];

        const omw::string resStr = omw::toHexStr(omw::doubleDabble128(tr.value8buffer, 16), 0);
        const omw::string ovrld_a = omw::toHexStr(omw::doubleDabble128(tr.value32H, tr.value32HM, tr.value32LM, tr.value32L), 0);
        const omw::string ovrld_b = omw::toHexStr(omw::doubleDabble128(tr.value64H, tr.value64L), 0);
        const omw::string ovrld_c = omw::toHexStr(omw::doubleDabble(tr.value128), 0);

        const bool resEqExpres = (resStr == tr.expResult);
        const bool allOverloadsEq = (
            (resStr == ovrld_a) &&
            (resStr == ovrld_b) &&
            (resStr == ovrld_c));

        CHECK(resStr == tr.expResult);
        CHECK(allOverloadsEq);

        if (!(resEqExpres && allOverloadsEq))
        {
            std::cout << omw::fgBrightCyan << "double dabble test record #" << i << omw::normal << "\n" << std::endl;
            stdOut = true;
        }
    }

    if (stdOut) std::cout << std::endl;

    const uint8_t alignTest[] = { 0x02, 0x01 };
    const std::vector<uint8_t> alignTestExpResult = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x05, 0x13 };
    CHECK(omw::doubleDabble128(alignTest, sizeof(alignTest)) == alignTestExpResult);
}



#endif // TEST_OMW_ALGORITHM_H
