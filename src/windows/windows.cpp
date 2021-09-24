/*
author      Oliver Blaser
date        24.09.2021
copyright   MIT - Copyright (c) 2021 Oliver Blaser
*/

#include "omw/windows/windows.h"

#ifdef OMW_PLAT_WIN

#include <stdexcept>
#include <string>
#include <vector>

#include "omw/string.h"
#include "omw/windows/error.h"
#include "omw/windows/exception.h"
#include "omw/windows/string.h"

#include <Windows.h>



namespace
{
    // expected format: string1\0string2\0\0
    std::vector<omw::string> multiStringConvert(LPCWSTR multiStr)
    {
        const WCHAR* p = multiStr;

        std::vector<const WCHAR*> wStrings;
        do
        {
            wStrings.push_back(p);
            while (*p != 0) ++p;
            ++p;
        }
        while (*p != 0);

        std::vector<omw::string> strings;
        for (size_t i = 0; i < wStrings.size(); ++i)
        {
            std::string tmpStr;
            omw::windows::wstr_to_utf8(wStrings[i], tmpStr);
            strings.push_back(tmpStr);
        }

        return strings;
    }

    std::vector<omw::string> queryDosDevice_base(const WCHAR* deviceName)
    {
        std::vector<WCHAR> buffer;
        buffer.resize(8192);

        bool querying = true;
        while (querying)
        {
            const DWORD r = QueryDosDeviceW(deviceName, buffer.data(), buffer.size());

            if (r == 0)
            {
                DWORD error = GetLastError();

                if (error == ERROR_INSUFFICIENT_BUFFER)
                {
                    buffer.resize(buffer.size() * 2);
                }
                else
                {
                    // TODO: add some error handling

                    buffer.clear();
                    buffer.push_back(0);
                    buffer.push_back(0);

                    querying = false;
                }
            }
            else
            {
                querying = false;
            }
        }

        return multiStringConvert(buffer.data());
    }
}



std::vector<omw::string> omw::windows::getAllDosDevices()
{
    return queryDosDevice_base(nullptr);
}

//! @param device 
//! @return
//! 
//! \b Exceptions
//! - `omw::windows::utf8_to_wstr()` is called and may throw exceptions
//!  
std::vector<omw::string> omw::windows::queryDosDevice(const std::string& device)
{
    constexpr size_t bufferSize = 512;
    WCHAR buffer[bufferSize];

    omw::windows::utf8_to_wstr(device, buffer, bufferSize);

    // TODO: buffer grow

    return queryDosDevice_base(buffer);
}


#endif // OMW_PLAT_WIN
