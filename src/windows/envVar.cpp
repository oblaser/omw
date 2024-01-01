/*
author          Oliver Blaser
date            31.12.2023
copyright       MIT - Copyright (c) 2023 Oliver Blaser
*/

#include "omw/windows/envVar.h"

#if OMW_PLAT_WIN

#include <stdexcept>
#include <string>
#include <vector>

#include "omw/windows/error.h"
#include "omw/windows/exception.h"
#include "omw/windows/string.h"

#include <Windows.h>


#define fnNamePrefix_getEnvironmentVariableW "omw::windows::getEnvironmentVariableW: "



/*!
* \var constexpr size_t omw::windows::envVarValueMaxSize
* \brief Max buffer size (including terminating null) of an environment variables value.
*
* See <a href="https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-getenvironmentvariable" target="_blank">GetEnvironmentVariable function (winbase.h)</a>.
*/

//! @brief Gets the value of an environment variable.
//! @param varName_u8 Name of the environment variable, UTF-8 encoded
//! @return Value of the environment variable, UTF-8 encoded
//! 
//! \b Exceptions
//! - omw::windows::envVar_not_found
//! - Calls `omw::windows::u8tows()` and `::wstou8()`, see \ref omw_windows_strConv_infoText
//! - Calls to `Allocator::allocate` may throw
//! 
std::string omw::windows::getEnvironmentVariable(const std::string& varName_u8)
{
    return omw::windows::wstou8(omw::windows::getEnvironmentVariableW(omw::windows::u8tows(varName_u8)));
}

//! @brief Gets the value of an environment variable.
//! @param varName_u8 Name of the environment variable, UTF-8 encoded
//! @return Value of the environment variable
//! 
//! \b Exceptions
//! - omw::windows::envVar_not_found
//! - Calls `omw::windows::u8tows()`, see \ref omw_windows_strConv_infoText
//! - Calls to `Allocator::allocate` may throw
//! 
std::wstring omw::windows::getEnvironmentVariableW(const std::string& varName_u8)
{
    return omw::windows::getEnvironmentVariableW(omw::windows::u8tows(varName_u8));
}

//! @brief Gets the value of an environment variable.
//! @param varName_u8 Name of the environment variable, UTF-8 encoded
//! @return Value of the environment variable
//! 
//! \b Exceptions
//! - omw::windows::envVar_not_found
//! - Calls `omw::windows::u8tows()`, see \ref omw_windows_strConv_infoText
//! - Calls to `Allocator::allocate` may throw
//! 
std::wstring omw::windows::getEnvironmentVariableW(const std::wstring& varName)
{
    using size_type = DWORD;
    static_assert(sizeof(std::vector<wchar_t>::size_type) >= sizeof(size_type), "invalid integer sizes"); // should always be true on Windows

#ifdef OMW_DEBUG
    // for unit tests
    constexpr size_type initialSize = 3;
#else // OMW_DEBUG
    constexpr size_type initialSize = 300;
#endif // OMW_DEBUG

    std::vector<wchar_t> buffer;

    DWORD res = initialSize;
    do
    {
        buffer = std::vector<wchar_t>(res, L'\0');

        res = GetEnvironmentVariableW(varName.c_str(), buffer.data(), static_cast<size_type>(buffer.size()));

        if (res == 0)
        {
            DWORD err = GetLastError();

            if (err == ERROR_ENVVAR_NOT_FOUND)
                throw omw::windows::envVar_not_found(fnNamePrefix_getEnvironmentVariableW OMWi_DISPSTR("environment variable not found"));
            else
                throw std::runtime_error(fnNamePrefix_getEnvironmentVariableW OMWi_DISPSTR("Windows API error, GetEnvironmentVariableW() GetLastError() returned ") + std::to_string(err));
        }
    }
    while (res > static_cast<size_type>(buffer.size()));

    return buffer.data();
}

//! @brief Gets the value of an environment variable.
//! @param varName Name of the environment variable
//! @return Value of the environment variable
//! 
//! Old implementation of this function!!!
//! 
//! \b Exceptions
//! - omw::windows::envVar_not_found
//! - omw::windows::invalid_unicode
//! - std::runtime_error
//! 
std::string omw::windows::deprecated::getEnvironmentVariable(const std::string& varName)
{
    ErrorCode ec;
    std::string value = getEnvironmentVariable(varName, ec);

    if (ec.code() == omw::windows::EC_OK) return value;
    else if (ec.code() == omw::windows::EC_ENVVAR_NOT_FOUND) throw omw::windows::envVar_not_found("omw::windows::getEnvironmentVariable: " + ec.msg());
    else if (ec.code() == omw::windows::EC_INV_UNICODE) throw omw::windows::invalid_unicode("omw::windows::getEnvironmentVariable: " + ec.msg());
    // else nop

    throw std::runtime_error("omw::windows::getEnvironmentVariable: " + ec.msg());
}

//! @brief Gets the value of an environment variable.
//! @param varName Name of the environment variable
//! @param [out] ec Error code
//! @return Value of the environment variable
//! 
//! Old implementation of this function!!!
//! 
//! Possible `ec.code()` values:
//! - `omw::windows::EC_OK`
//! - `omw::windows::EC_ENVVAR_NOT_FOUND`
//! - `omw::windows::EC_INV_UNICODE`
//! - `omw::windows::EC_INTERNAL`
//! - `omw::windows::EC_UNKNOWN_WIN`
//! 
std::string omw::windows::deprecated::getEnvironmentVariable(const std::string& varName, ErrorCode& ec)
{
    const size_t bufferSizeInitial = 300;
    const size_t bufferSizeGrow = 100;

    std::string value;
    std::vector<WCHAR> wVarName(300, 0);

    omw::windows::deprecated::utf8_to_wstr(varName, wVarName.data(), wVarName.size(), ec);

    if (ec.code() == omw::windows::EC_OK)
    {
        bool proc;
        std::vector<WCHAR> wVal(bufferSizeInitial, 0);

        proc = true;
        while (proc)
        {
            DWORD r = GetEnvironmentVariableW(wVarName.data(), wVal.data(), wVal.size());

            if (r == 0)
            {
                DWORD err = GetLastError();

                if (err == ERROR_ENVVAR_NOT_FOUND)
                {
                    ec = ErrorCode(omw::windows::EC_ENVVAR_NOT_FOUND, OMWi_DISPSTR("environment variable not found"));
                    value.clear();
                }
                else
                {
                    ec = ErrorCode(omw::windows::EC_UNKNOWN_WIN, OMWi_DISPSTR("Windows API error, GetEnvironmentVariableW() caused GetLastError() to return ") + std::to_string(err));
                    value.clear();
                }

                proc = false;
            }
            else if (r > wVal.size())
            {
                const size_t currentSize = wVal.size();

                if (currentSize < (omw::windows::deprecated::envVarValueMaxSize - bufferSizeGrow))
                {
                    wVal.resize((currentSize + bufferSizeGrow));
                }
                else
                {
                    ec = ErrorCode(omw::windows::EC_INTERNAL, OMWi_DISPSTR("value buffer too small"));
                    value.clear();
                    proc = false;
                }
            }
            else
            {
                omw::windows::deprecated::wstr_to_utf8(wVal.data(), value, ec);

                if (ec.code() == omw::windows::EC_OK)
                {
                    ec = ErrorCode(omw::windows::EC_OK, OMWi_DISPSTR("OK"));
                }
                else
                {
                    ec = ErrorCode(omw::windows::EC_INTERNAL, OMWi_DISPSTR("unable to convert back to UTF-8 string (" + ec.msg() + ")"));
                    value.clear();
                }

                proc = false;
            }
        }
    }
    else if (ec.code() == omw::windows::EC_INV_UNICODE)
    {
        ec = ErrorCode(omw::windows::EC_INV_UNICODE, OMWi_DISPSTR("invalid unicode in variable name"));
        value.clear();
    }
    else
    {
        ec = ErrorCode(omw::windows::EC_INTERNAL, OMWi_DISPSTR("unable to convert to wide string (" + ec.msg() + ")"));
        value.clear();
    }

    return value;
}

#endif // OMW_PLAT_WIN
