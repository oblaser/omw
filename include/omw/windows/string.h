/*
author          Oliver Blaser
date            17.12.2023
copyright       MIT - Copyright (c) 2023 Oliver Blaser
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
        /*! \addtogroup grp_windows
        * @{
        */

        //! \name String Conversion
        /// @{
        size_t utf8_to_wstr(const char* src, wchar_t* dest, size_t destSize);
        size_t utf8_to_wstr(const char* src, wchar_t* dest, size_t destSize, omw::windows::ErrorCode& ec);
        static inline size_t utf8_to_wstr(const std::string& src, wchar_t* dest, size_t destSize) { return utf8_to_wstr(src.c_str(), dest, destSize); }
        static inline size_t utf8_to_wstr(const std::string& src, wchar_t* dest, size_t destSize, omw::windows::ErrorCode& ec) { return utf8_to_wstr(src.c_str(), dest, destSize, ec); }

        size_t wstr_to_utf8(const wchar_t* src, char* dest, size_t destSize);
        size_t wstr_to_utf8(const wchar_t* src, char* dest, size_t destSize, omw::windows::ErrorCode& ec);
        void wstr_to_utf8(const wchar_t* src, std::string& dest);
        void wstr_to_utf8(const wchar_t* src, std::string& dest, omw::windows::ErrorCode& ec);
        /// @}

        /*! @} */
    }
}

#endif // OMW_PLAT_WIN
#endif // IG_OMW_WINDOWS_STRING_H
