/*
author          Oliver Blaser
date            15.12.2021
copyright       MIT - Copyright (c) 2021 Oliver Blaser
*/

#ifndef IG_OMW_WINDOWS_STRING_H
#define IG_OMW_WINDOWS_STRING_H

#include "../../omw/defs.h"
#ifdef OMW_PLAT_WIN

#include <cstddef>
#include <string>

#include "../../omw/windows/error.h"

namespace omw
{
    namespace windows
    {
        //! \name String Conversion
        /// @{
        size_t utf8_to_wstr(const std::string& src, void* LPWSTR_dest, size_t destSize);
        size_t utf8_to_wstr(const std::string& src, void* LPWSTR_dest, size_t destSize, omw::windows::ErrorCode& ec);
        size_t wstr_to_utf8(const void* LPCWCH_src, char* dest, size_t destSize);
        size_t wstr_to_utf8(const void* LPCWCH_src, char* dest, size_t destSize, omw::windows::ErrorCode& ec);
        void wstr_to_utf8(const void* LPCWCH_src, std::string& dest);
        void wstr_to_utf8(const void* LPCWCH_src, std::string& dest, omw::windows::ErrorCode& ec);
        /// @}
    }
}

#endif // OMW_PLAT_WIN
#endif // IG_OMW_WINDOWS_STRING_H
