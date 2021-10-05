/*
author         Oliver Blaser
date           06.10.2021
copyright      MIT - Copyright (c) 2021 Oliver Blaser
*/

#include <string>
#include <vector>

#include "omw/defs.h"
#include "omw/io/serialPort.h"
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



omw::io::SerialPort::SerialPort()
{
}



std::vector<omw::string> omw::io::getSerialPortList(bool onlyCOMx)
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
