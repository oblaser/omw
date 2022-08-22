/*
author          Oliver Blaser
date            26.01.2022
copyright       MIT - Copyright (c) 2022 Oliver Blaser
*/

#include <algorithm>
#include <string>
#include <vector>

#include "omw/defs.h"
#include "omw/io/serialPort.h"
#include "omw/string.h"
#include "omw/version.h"
#include "omw/windows/windows.h"



namespace
{
#ifdef OMW_PLAT_WIN
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
#endif // OMW_PLAT_WIN
}


#ifdef OMWi_SERIAL_PORT_PREVIEW

omw::SerialPort::SerialPort()
{
}

#endif


omw::vector<omw::string> omw::preview::getSerialPortList(bool onlyCOMx)
{
    std::vector<omw::string> serialPorts;

#ifdef OMW_PLAT_WIN
    const std::vector<omw::string> devices = omw::windows::getAllDosDevices();
    
    for (size_t i = 0; i < devices.size(); ++i)
    {
        bool isC0C = false;

        if (!onlyCOMx) isC0C = ::isCom0com(devices[i]);

        if ((devices[i].compare(0, 3, "COM") == 0) || (!onlyCOMx && isC0C))
        {
            serialPorts.push_back(devices[i]);
        }
    }
#endif // OMW_PLAT_WIN

    return serialPorts;
}

void omw::preview::sortSerialPortList(std::vector<omw::string>& ports)
{
#ifdef OMW_PLAT_WIN

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

#else // OMW_PLAT_WIN

    std::sort(ports.begin(), ports.end());

#endif // OMW_PLAT_WIN
}

void omw::preview::sortSerialPortList(std::vector<std::string>& ports)
{
    omw::stringVector_t tmpPorts = omw::stringVector(ports);
    omw::preview::sortSerialPortList(tmpPorts);
    ports = omw::stdStringVector(tmpPorts);
}
