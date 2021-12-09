/*
author          Oliver Blaser
date            08.12.2021
copyright       MIT - Copyright (c) 2021 Oliver Blaser
*/

#include <algorithm>
#include <string>
#include <vector>

#include "omw/defs.h"
#include "omw/io/serialPort.h"
#include "omw/string.h"
#include "omw/windows/windows.h"



namespace
{
    bool isCom0com(const std::string& device)
    {
        const omw::string tmpDevice = (omw::string(device)).toLower_asciiExt();
        const std::vector<omw::string> info = omw::windows::queryDosDevice(device);

        for (size_t i = 0; i < info.size(); ++i)
        {
            const omw::string tmpInfo = info[i].toLower_asciiExt();

            if (tmpInfo.contains("com0com") && !tmpDevice.contains("com0com#port#"))
            {
                return true;
            }
        }

        return false;
    }
}


#ifndef OMWi_SERIAL_PORT_PREVIEW

omw::SerialPort::SerialPort()
{
}

#endif


std::vector<omw::string> omw::getSerialPortList(bool onlyCOMx)
{
    const std::vector<omw::string> devices = omw::windows::getAllDosDevices();
    std::vector<omw::string> serialPorts;

    for (size_t i = 0; i < devices.size(); ++i)
    {
        bool isC0C = false;

        if (!onlyCOMx) isC0C = ::isCom0com(devices[i]);

        if ((devices[i].compare(0, 3, "COM") == 0) || (!onlyCOMx && isC0C))
        {
            serialPorts.push_back(devices[i]);
        }
    }

    return serialPorts;
}

void omw::sortSerialPortList(std::vector<omw::string>& ports)
{
#if /*simple*/ 0
    std::sort(ports.begin(), ports.end());
#else
    const char* const comStr = "COM";
    std::vector<int> comPorts;
    std::vector<omw::string> otherPorts;

    for (size_t i = 0; i < ports.size(); ++i)
    {
        try
        {
            omw::string port = ports[i];

            if (port.compare(0, 3, comStr) == 0)
            {
                const omw::string intStr = port.substr(3);

                if (omw::isUInteger(intStr)) comPorts.push_back(std::stoi(intStr));
                else throw (-1);
            }
            else throw (-1);
        }
        catch (...) { otherPorts.push_back(ports[i]); }
    }

    std::sort(comPorts.begin(), comPorts.end());
    std::sort(otherPorts.begin(), otherPorts.end());

    ports.clear();
    ports.reserve(comPorts.size() + otherPorts.size());

    for (size_t i = 0; i < comPorts.size(); ++i)
    {
        ports.push_back(comStr + std::to_string(comPorts[i]));
    }

    for (size_t i = 0; i < otherPorts.size(); ++i)
    {
        ports.push_back(otherPorts[i]);
    }
#endif
}

void omw::sortSerialPortList(std::vector<std::string>& ports)
{
    omw::stringVector_t tmpPorts = omw::stringVector(ports);
    omw::sortSerialPortList(tmpPorts);
    ports = omw::stdStringVector(tmpPorts);
}
