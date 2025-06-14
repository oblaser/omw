/*
author          Oliver Blaser
date            27.01.2022
copyright       MIT - Copyright (c) 2022 Oliver Blaser
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
    std::vector<std::string> ports = { "COM23", "vCOM43", "vCOM4", "AVC2", "COM4", "vCOM6", "COM1", "com0com3" };

#ifdef OMW_PLAT_WIN
    const std::vector<std::string> expectedResult = { "COM1", "COM4", "COM23", "AVC2", "com0com3", "vCOM4", "vCOM43", "vCOM6" };
#else  // OMW_PLAT_WIN
    const std::vector<std::string> expectedResult = { "AVC2", "COM1", "COM23", "COM4", "com0com3", "vCOM4", "vCOM43", "vCOM6" };
#endif // OMW_PLAT_WIN

    omw::preview::sortSerialPortList(ports);
    CHECK(ports == expectedResult);
}


#endif // TEST_OMW_IO_SERIALPORT_H
