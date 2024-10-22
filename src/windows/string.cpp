/*
author          Oliver Blaser
date            06.01.2024
copyright       MIT - Copyright (c) 2024 Oliver Blaser
*/

#include "omw/windows/string.h"

#ifdef OMW_PLAT_WIN

#include <stdexcept>
#include <string>
#include <vector>

#include "omw/defs.h"
#include "omw/windows/error.h"
#include "omw/windows/exception.h"
#include "..\..\include\omw\string.h"

#include <Windows.h>


#define INITIAL_BUFFER_SIZE (300)
#define INITIAL_INC_SIZE    (50)

#define u8tows_fnNamePrefix "omw::windows::u8tows: "
#define wstou8_fnNamePrefix "omw::windows::wstou8: "
#define wstocp_fnNamePrefix "omw::windows::wstocp: "
#define cptows_fnNamePrefix "omw::windows::cptows: "



//! @param str The input UTF-8 string
//! @return The converted wide char string
//! 
//! Converts an UTF-8 string to a Windows API compatible wide char string.
//! 
//! Throwing function, see \ref omw_windows_strConv_infoText.
//! 
std::wstring omw::windows::u8tows(const char* str)
{
    using size_type = std::vector<wchar_t>::size_type;
    static_assert(sizeof(size_type) >= sizeof(int), "invalid integer sizes"); // should always be true on Windows

    std::vector<wchar_t> buffer;

    if (str)
    {
        constexpr size_type initialSize = INITIAL_BUFFER_SIZE;
        size_type incSize = INITIAL_INC_SIZE;
        int res;
        constexpr int maxDestSize = INT_MAX;
        int destSize;

        buffer = std::vector<wchar_t>(initialSize, L'\0');

        do
        {
            if (buffer.size() > static_cast<size_type>(maxDestSize)) destSize = maxDestSize;
            else destSize = static_cast<int>(buffer.size());

            res = MultiByteToWideChar(CP_UTF8, MB_PRECOMPOSED | MB_ERR_INVALID_CHARS, str, -1, buffer.data(), destSize);

            if (res <= 0)
            {
                const DWORD err = GetLastError();

                if (err == ERROR_INSUFFICIENT_BUFFER)
                {
                    if (destSize == maxDestSize) throw std::length_error(u8tows_fnNamePrefix OMWi_DISPSTR("src is too long"));

                    buffer = std::vector<wchar_t>(initialSize + incSize, L'\0');
                    incSize *= 2;
                }
                else if (err == ERROR_INVALID_PARAMETER)
                {
                    throw std::invalid_argument(u8tows_fnNamePrefix OMWi_DISPSTR("invalid arguments"));
                }
                else if (err == ERROR_NO_UNICODE_TRANSLATION)
                {
                    throw omw::windows::invalid_unicode(u8tows_fnNamePrefix OMWi_DISPSTR("invalid unicode in src"));
                }
                else if (err == ERROR_INVALID_FLAGS)
                {
                    throw std::runtime_error(u8tows_fnNamePrefix OMWi_DISPSTR("internal error (invalid flags)"));
                }
                else if (res < 0)
                {
                    throw std::runtime_error(u8tows_fnNamePrefix OMWi_DISPSTR("Windows API error, MultiByteToWideChar() ") + std::to_string(res) + OMWi_DISPSTR(", GetLastError() ") + std::to_string(err));
                }
                else
                {
                    throw std::runtime_error(u8tows_fnNamePrefix OMWi_DISPSTR("internal error"));
                }
            }
        }
        while (res <= 0);
    }
    else throw std::invalid_argument(u8tows_fnNamePrefix OMWi_DISPSTR("src is NULL"));

    return buffer.data();
}

//! @param str The input wide char string
//! @return The converted UTF-8 string
//! 
//! Converts a Windows API compatible wide char string to an UTF-8 string.
//! 
//! Throwing function, see \ref omw_windows_strConv_infoText.
//! 
std::string omw::windows::wstou8(const wchar_t* str)
{
    using size_type = std::vector<char>::size_type;
    static_assert(sizeof(size_type) >= sizeof(int), "invalid integer sizes"); // should always be true on Windows

    std::vector<char> buffer;

    if (str)
    {
        constexpr size_type initialSize = INITIAL_BUFFER_SIZE;
        size_type incSize = INITIAL_INC_SIZE;
        int res;
        constexpr int maxDestSize = INT_MAX;
        int destSize;

        buffer = std::vector<char>(initialSize, '\0');

        do
        {
            if (buffer.size() > static_cast<size_type>(maxDestSize)) destSize = maxDestSize;
            else destSize = static_cast<int>(buffer.size());

            res = WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, str, -1, buffer.data(), destSize, NULL, NULL);

            if (res <= 0)
            {
                const DWORD err = GetLastError();

                if (err == ERROR_INSUFFICIENT_BUFFER)
                {
                    if (destSize == maxDestSize) throw std::length_error(wstou8_fnNamePrefix OMWi_DISPSTR("src is too long"));

                    buffer = std::vector<char>(initialSize + incSize, '\0');
                    incSize *= 2;
                }
                else if (err == ERROR_INVALID_PARAMETER)
                {
                    throw std::invalid_argument(wstou8_fnNamePrefix OMWi_DISPSTR("invalid arguments"));
                }
                else if (err == ERROR_NO_UNICODE_TRANSLATION)
                {
                    throw omw::windows::invalid_unicode(wstou8_fnNamePrefix OMWi_DISPSTR("invalid unicode in src"));
                }
                else if (err == ERROR_INVALID_FLAGS)
                {
                    throw std::runtime_error(wstou8_fnNamePrefix OMWi_DISPSTR("internal error (invalid flags)"));
                }
                else if (res < 0)
                {
                    throw std::runtime_error(wstou8_fnNamePrefix OMWi_DISPSTR("Windows API error, WideCharToMultiByte() ") + std::to_string(res) + OMWi_DISPSTR(", GetLastError() ") + std::to_string(err));
                }
                else
                {
                    throw std::runtime_error(wstou8_fnNamePrefix OMWi_DISPSTR("internal error"));
                }
            }
        }
        while (res <= 0);
    }
    else throw std::invalid_argument(wstou8_fnNamePrefix OMWi_DISPSTR("src is NULL"));

    return buffer.data();
}

#if 0
//! @param str 
//! @param codepage One of omw::windows::WINNLS_CODEPAGE or a MS code page
//! @return 
//! 
//! See https://learn.microsoft.com/en-us/windows/win32/intl/code-page-identifiers for available code pages.
//! 
//! Throwing function, see \ref omw_windows_strConv_infoText.
//! 
std::wstring omw::windows::cptows(const char* str, unsigned int codepage)
{
}

//! @param str 
//! @param codepage One of omw::windows::WINNLS_CODEPAGE or a MS code page 
//! @return 
//! 
//! See https://learn.microsoft.com/en-us/windows/win32/intl/code-page-identifiers for available code pages.
//! 
//! Throwing function, see \ref omw_windows_strConv_infoText.
//! 
std::string omw::windows::wstocp(const wchar_t* str, unsigned int codepage)
{
}
#endif

//! @param src The input string
//! @param [out] dest Pointer (`LPWSTR`) to the output buffer (`WCHAR[]`)
//! @param destSize Size of the destination buffer (number of `WCHAR`)
//! @return Number of wide chars written to dest (not including the terminating null character)
//! 
//! Converts an UTF-8 string to a Windows API compatible wide string.
//! 
//! Throwing function, see \ref omw_windows_strConv_infoText.
//! 
size_t omw::windows::deprecated::utf8_to_wstr(const char* src, wchar_t* dest, size_t destSize)
{
    size_t r;
    ErrorCode ec;

    r = utf8_to_wstr(src, dest, destSize, ec);

    if (ec.code() == omw::windows::EC_OK) return r;
    else if (ec.code() == omw::windows::EC_STRCONV_DEST_BUFFER_SIZE) throw std::range_error("omw::windows::utf8_to_wstr: " + ec.msg());
    else if (ec.code() == omw::windows::EC_INV_ARG) throw std::invalid_argument("omw::windows::utf8_to_wstr: " + ec.msg());
    else if (ec.code() == omw::windows::EC_INV_UNICODE) throw omw::windows::invalid_unicode("omw::windows::utf8_to_wstr: " + ec.msg());
    //else nop

    throw std::runtime_error("omw::windows::utf8_to_wstr: " + ec.msg());
}

//! @param src The input string
//! @param [out] dest Pointer (`LPWSTR`) to the output buffer (`WCHAR[]`)
//! @param destSize Size of the destination buffer (number of `WCHAR`)
//! @param [out] ec See \ref omw_windows_strConv_infoText
//! @return Number of wide chars written to dest (not including the terminating null character)
//! 
//! Converts an UTF-8 string to a Windows API compatible wide string.
//! 
size_t omw::windows::deprecated::utf8_to_wstr(const char* src, wchar_t* dest, size_t destSize, ErrorCode& ec)
{
    int r;

    if (destSize > (size_t)INT_MAX) destSize = INT_MAX;

    r = MultiByteToWideChar(CP_UTF8, MB_PRECOMPOSED | MB_ERR_INVALID_CHARS, src, -1, dest, (int)destSize);

    if (r <= 0)
    {
        DWORD err = GetLastError();

        std::string msg = OMWi_DISPSTR("internal error");

        if (err == ERROR_INSUFFICIENT_BUFFER)
        {
            ec = ErrorCode(omw::windows::EC_STRCONV_DEST_BUFFER_SIZE, OMWi_DISPSTR("dest buffer too small"));
            return 0;
        }
        else if (err == ERROR_INVALID_PARAMETER)
        {
            ec = ErrorCode(omw::windows::EC_INV_ARG, OMWi_DISPSTR("invalid arguments"));
            return 0;
        }
        else if (err == ERROR_NO_UNICODE_TRANSLATION)
        {
            ec = ErrorCode(omw::windows::EC_INV_UNICODE, OMWi_DISPSTR("invalid unicode in src"));
            return 0;
        }
        else if (err == ERROR_INVALID_FLAGS) msg += OMWi_DISPSTR(" (invalid flags)");
        else if (r < 0)
        {
            ec = ErrorCode(omw::windows::EC_UNKNOWN_WIN, OMWi_DISPSTR("Windows API error, MultiByteToWideChar() returned ") + std::to_string(r));
            return 0;
        }
        //else nop

        ec = ErrorCode(omw::windows::EC_INTERNAL, msg);
        return 0;
    }

    ec = ErrorCode(omw::windows::EC_OK, OMWi_DISPSTR("OK"));

    return r - 1;
}

//! @param src The input string (`LPCWCH`)
//! @param [out] dest Pointer to the output buffer
//! @param destSize Size of the destination buffer
//! @return Number of bytes written to dest (not including the terminating null character)
//! 
//! Converts a Windows API compatible wide string to an UTF-8 string.
//! 
//! Throwing function, see \ref omw_windows_strConv_infoText.
//! 
size_t omw::windows::deprecated::wstr_to_utf8(const wchar_t* src, char* dest, size_t destSize)
{
    size_t r;
    ErrorCode ec;

    r = wstr_to_utf8(src, dest, destSize, ec);

    if (ec.code() == omw::windows::EC_OK) return r;
    else if (ec.code() == omw::windows::EC_STRCONV_DEST_BUFFER_SIZE) throw std::range_error("omw::windows::wstr_to_utf8: " + ec.msg());
    else if (ec.code() == omw::windows::EC_INV_ARG) throw std::invalid_argument("omw::windows::wstr_to_utf8: " + ec.msg());
    else if (ec.code() == omw::windows::EC_INV_UNICODE) throw omw::windows::invalid_unicode("omw::windows::wstr_to_utf8: " + ec.msg());
    //else nop

    throw std::runtime_error("omw::windows::wstr_to_utf8: " + ec.msg());
}

//! @param src The input string (`LPCWCH`)
//! @param [out] dest Pointer to the output buffer
//! @param destSize Size of the destination buffer
//! @param [out] ec See \ref omw_windows_strConv_infoText
//! @return Number of bytes written to dest (not including the terminating null character)
//! 
//! Converts a Windows API compatible wide string to an UTF-8 string.
//! 
size_t omw::windows::deprecated::wstr_to_utf8(const wchar_t* src, char* dest, size_t destSize, ErrorCode& ec)
{
    int r;

    if (destSize > (size_t)INT_MAX) destSize = INT_MAX;

    r = WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, src, -1, dest, (int)destSize, NULL, NULL);

    if (r <= 0)
    {
        DWORD err = GetLastError();

        std::string msg = OMWi_DISPSTR("internal error");

        if (err == ERROR_INSUFFICIENT_BUFFER)
        {
            ec = ErrorCode(omw::windows::EC_STRCONV_DEST_BUFFER_SIZE, OMWi_DISPSTR("dest buffer too small"));
            return 0;
        }
        else if (err == ERROR_INVALID_PARAMETER)
        {
            ec = ErrorCode(omw::windows::EC_INV_ARG, OMWi_DISPSTR("invalid arguments"));
            return 0;
        }
        else if (err == ERROR_NO_UNICODE_TRANSLATION)
        {
            ec = ErrorCode(omw::windows::EC_INV_UNICODE, OMWi_DISPSTR("invalid unicode in src"));
            return 0;
        }
        else if (err == ERROR_INVALID_FLAGS) msg += OMWi_DISPSTR(" (invalid flags)");
        else if (r < 0)
        {
            ec = ErrorCode(omw::windows::EC_UNKNOWN_WIN, OMWi_DISPSTR("Windows API error, WideCharToMultiByte() returned ") + std::to_string(r));
            return 0;
        }
        //else nop

        ec = ErrorCode(omw::windows::EC_INTERNAL, msg);
        return 0;
    }

    ec = ErrorCode(omw::windows::EC_OK, OMWi_DISPSTR("OK"));

    return r - 1;
}

//! @param src The input string (`LPCWCH`)
//! @param [out] dest Reference to the output string
//! 
//! Converts a Windows API compatible wide string to an UTF-8 string.
//! 
//! Throwing function, see \ref omw_windows_strConv_infoText.
//! 
void omw::windows::deprecated::wstr_to_utf8(const wchar_t* src, std::string& dest)
{
    ErrorCode ec;

    wstr_to_utf8(src, dest, ec);

    if (ec.code() == omw::windows::EC_OK) return;
    else if (ec.code() == omw::windows::EC_STRCONV_DEST_BUFFER_SIZE) throw std::range_error("omw::windows::wstr_to_utf8: " + ec.msg());
    else if (ec.code() == omw::windows::EC_INV_ARG) throw std::invalid_argument("omw::windows::wstr_to_utf8: " + ec.msg());
    else if (ec.code() == omw::windows::EC_INV_UNICODE) throw omw::windows::invalid_unicode("omw::windows::wstr_to_utf8: " + ec.msg());
    //else nop

    throw std::runtime_error("omw::windows::wstr_to_utf8: " + ec.msg());
}

//! @param src The input string (`LPCWCH`)
//! @param [out] dest Reference to the output string
//! @param [out] ec See \ref omw_windows_strConv_infoText
//! 
//! Converts a Windows API compatible wide string to an UTF-8 string.
//! 
void omw::windows::deprecated::wstr_to_utf8(const wchar_t* src, std::string& dest, ErrorCode& ec)
{
    const size_t bufferSizeInitial = 300;   // adapt unit test "windows_string.hpp" if
    const size_t bufferSizeGrow = 100;      // one of these values change

    bool proc;
    std::vector<char> buffer(bufferSizeInitial, 0);
    size_t maxSize = 0;

    for (size_t i = 0; i < (sizeof(maxSize) * 8); ++i)
    {
        maxSize <<= 1;
        maxSize |= (size_t)0x01;
    }

    if ((buffer.max_size() - 1) < maxSize) maxSize = buffer.max_size() - 1;
    if (dest.max_size() < maxSize) maxSize = dest.max_size();

    proc = true;
    while (proc)
    {
        wstr_to_utf8(src, buffer.data(), buffer.size(), ec);

        if (ec.code() == omw::windows::EC_STRCONV_DEST_BUFFER_SIZE)
        {
            const size_t currentSize = buffer.size();

            if (currentSize < (maxSize - bufferSizeGrow))
            {
                buffer.assign((currentSize + bufferSizeGrow), 0);
            }
            else proc = false;
        }
        else proc = false;
    }

    dest = std::string(buffer.data());
}

#endif // OMW_PLAT_WIN
