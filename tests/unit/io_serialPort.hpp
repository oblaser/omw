/*
author          Oliver Blaser
date            08.12.2021
copyright       MIT - Copyright (c) 2021 Oliver Blaser
*/

#ifndef TEST_OMW_IO_SERIALPORT_H
#define TEST_OMW_IO_SERIALPORT_H

#include <string>
#include <vector>

#include "catch2/catch.hpp"
#include "testUtil.h"

#include <omw/io/serialPort.h>
#include <omw/string.h>


TEST_CASE("serialPort.h sortSerialPortList()")
{
    std::vector<omw::string> ports =
    {
        "COM23",
        "vCOM43",
        "vCOM4",
        "AVC2",
        "COM4",
        "vCOM6",
        "COM1",
        "com0com3"
    };
    std::vector<std::string> stdPorts = omw::stdStringVector(ports);

#ifdef OMW_PLAT_WIN
    const std::vector<omw::string> expectedResult =
    {
        "COM1",
        "COM4",
        "COM23",
        "AVC2",
        "com0com3",
        "vCOM4",
        "vCOM43",
        "vCOM6"
    };
#else // OMW_PLAT_WIN
    const std::vector<omw::string> expectedResult =
    {
        "AVC2",
        "COM1",
        "COM23",
        "COM4",
        "com0com3",
        "vCOM4",
        "vCOM43",
        "vCOM6"
    };
#endif // OMW_PLAT_WIN
    const std::vector<std::string> stdExpectedResult = omw::stdStringVector(expectedResult);

    omw::sortSerialPortList(ports);
    CHECK(ports == expectedResult);

    omw::sortSerialPortList(stdPorts);
    CHECK(stdPorts == stdExpectedResult);
}


#endif // TEST_OMW_IO_SERIALPORT_H
