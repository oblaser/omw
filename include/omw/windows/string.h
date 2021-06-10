/*
author      Oliver Blaser
date        09.06.2021
copyright   MIT - Copyright (c) 2021 Oliver Blaser
*/

#ifndef OMW_WINDOWS_STRING_H
#define OMW_WINDOWS_STRING_H

#include "../../omw/defs.h"
#ifdef OMW_PLAT_WIN

#include <cstddef>
#include <string>

#include "../../omw/windows/error.h"

#include <Windows.h>

namespace omw
{
    namespace windows
    {
        size_t utf8_to_wstr(const std::string& src, LPWSTR dest, size_t destSize);
        size_t utf8_to_wstr(const std::string& src, LPWSTR dest, size_t destSize, omw::windows::ErrorCode& ec) noexcept;
        size_t wstr_to_utf8(LPCWCH src, char* dest, size_t destSize);
        size_t wstr_to_utf8(LPCWCH src, char* dest, size_t destSize, omw::windows::ErrorCode& ec) noexcept;
        void wstr_to_utf8(LPCWCH src, std::string& dest);
        void wstr_to_utf8(LPCWCH src, std::string& dest, omw::windows::ErrorCode& ec) noexcept;
    }
}

#endif // OMW_PLAT_WIN
#endif // OMW_WINDOWS_STRING_H
