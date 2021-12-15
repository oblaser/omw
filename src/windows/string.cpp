/*
author          Oliver Blaser
date            15.12.2021
copyright       MIT - Copyright (c) 2021 Oliver Blaser
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



//! @brief Converts an UTF-8 string to a Windows API compatible wide string.
//! @param src The input string
//! @param [out] LPWSTR_dest Pointer (`LPWSTR`) to the output buffer (`WCHAR[]`)
//! @param destSize Size of the destination buffer (number of `WCHAR`)
//! @return Number of wide chars written to dest (not including the terminating null character)
//! 
//! The \b src argument can also be of type <tt>const char*</tt> (implicit <tt>std::string()</tt> constructor).
//! 
//! Throwing function, see \ref omw_windows_strConv_infoText.
//! 
size_t omw::windows::utf8_to_wstr(const std::string& src, void* LPWSTR_dest, size_t destSize)
{
    LPWSTR dest = reinterpret_cast<LPWSTR>(LPWSTR_dest);

    size_t r;
    ErrorCode ec;

    r = utf8_to_wstr(src, dest, destSize, ec);

    if (ec.code() == omw::windows::EC_OK) return r;
    else if (ec.code() == omw::windows::EC_STRCONV_DEST_BUFFER_SIZE) throw std::range_error(ec.msg());
    else if (ec.code() == omw::windows::EC_INV_ARG) throw std::invalid_argument(ec.msg());
    else if (ec.code() == omw::windows::EC_INV_UNICODE) throw omw::windows::invalid_unicode(ec.msg());
    //else nop

    throw std::runtime_error(ec.msg());
}

//! @brief Converts an UTF-8 string to a Windows API compatible wide string.
//! @param src The input string
//! @param [out] LPWSTR_dest Pointer (`LPWSTR`) to the output buffer (`WCHAR[]`)
//! @param destSize Size of the destination buffer (number of `WCHAR`)
//! @param [out] ec See \ref omw_windows_strConv_infoText
//! @return Number of wide chars written to dest (not including the terminating null character)
//! 
//! The \b src argument can also be of type <tt>const char*</tt> (implicit <tt>std::string()</tt> constructor).
//! 
size_t omw::windows::utf8_to_wstr(const std::string& src, void* LPWSTR_dest, size_t destSize, ErrorCode& ec)
{
    LPWSTR dest = reinterpret_cast<LPWSTR>(LPWSTR_dest);

    int r;

    if (destSize > (size_t)INT_MAX) destSize = INT_MAX;

    r = MultiByteToWideChar(CP_UTF8, MB_PRECOMPOSED | MB_ERR_INVALID_CHARS, src.c_str(), -1, dest, (int)destSize);

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

//! @brief Converts a Windows API compatible wide string to an UTF-8 string.
//! @param src The input string (`LPCWCH`)
//! @param [out] dest Pointer to the output buffer
//! @param destSize Size of the destination buffer
//! @return Number of bytes written to dest (not including the terminating null character)
//! 
//! Throwing function, see \ref omw_windows_strConv_infoText.
//! 
size_t omw::windows::wstr_to_utf8(const void* LPCWCH_src, char* dest, size_t destSize)
{
    LPCWCH src = reinterpret_cast<LPCWCH>(LPCWCH_src);

    size_t r;
    ErrorCode ec;

    r = wstr_to_utf8(src, dest, destSize, ec);

    if (ec.code() == omw::windows::EC_OK) return r;
    else if (ec.code() == omw::windows::EC_STRCONV_DEST_BUFFER_SIZE) throw std::range_error(ec.msg());
    else if (ec.code() == omw::windows::EC_INV_ARG) throw std::invalid_argument(ec.msg());
    else if (ec.code() == omw::windows::EC_INV_UNICODE) throw omw::windows::invalid_unicode(ec.msg());
    //else nop

    throw std::runtime_error(ec.msg());
}

//! @brief Converts a Windows API compatible wide string to an UTF-8 string.
//! @param src The input string (`LPCWCH`)
//! @param [out] dest Pointer to the output buffer
//! @param destSize Size of the destination buffer
//! @param [out] ec See \ref omw_windows_strConv_infoText
//! @return Number of bytes written to dest (not including the terminating null character)
size_t omw::windows::wstr_to_utf8(const void* LPCWCH_src, char* dest, size_t destSize, ErrorCode& ec)
{
    LPCWCH src = reinterpret_cast<LPCWCH>(LPCWCH_src);

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

//! @brief Converts a Windows API compatible wide string to an UTF-8 string.
//! @param src The input string (`LPCWCH`)
//! @param [out] dest Reference to the output string
//! 
//! Throwing function, see \ref omw_windows_strConv_infoText.
//! 
void omw::windows::wstr_to_utf8(const void* LPCWCH_src, std::string& dest)
{
    LPCWCH src = reinterpret_cast<LPCWCH>(LPCWCH_src);

    ErrorCode ec;

    wstr_to_utf8(src, dest, ec);

    if (ec.code() == omw::windows::EC_OK) return;
    else if (ec.code() == omw::windows::EC_STRCONV_DEST_BUFFER_SIZE) throw std::range_error(ec.msg());
    else if (ec.code() == omw::windows::EC_INV_ARG) throw std::invalid_argument(ec.msg());
    else if (ec.code() == omw::windows::EC_INV_UNICODE) throw omw::windows::invalid_unicode(ec.msg());
    //else nop

    throw std::runtime_error(ec.msg());
}

//! @brief Converts a Windows API compatible wide string to an UTF-8 string.
//! @param src The input string (`LPCWCH`)
//! @param [out] dest Reference to the output string
//! @param [out] ec See \ref omw_windows_strConv_infoText
void omw::windows::wstr_to_utf8(const void* LPCWCH_src, std::string& dest, ErrorCode& ec)
{
    LPCWCH src = reinterpret_cast<LPCWCH>(LPCWCH_src);

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
