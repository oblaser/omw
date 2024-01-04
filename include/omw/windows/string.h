/*
author          Oliver Blaser
date            31.12.2023
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
        std::wstring u8tows(const char* str);
        static inline std::wstring u8tows(const std::string& str) { return u8tows(str.c_str()); }

        std::string wstou8(const wchar_t* str);
        static inline std::string wstou8(const std::wstring& str) { return wstou8(str.c_str()); }

        std::wstring acptows(const char* str);
        static inline std::wstring acptows(const std::string& str) { return omw::windows::acptows(str.c_str()); }
        static inline std::string acptou8(const char* str) { return omw::windows::wstou8(omw::windows::acptows(str)); }
        static inline std::string acptou8(const std::string& str) { return omw::windows::wstou8(omw::windows::acptows(str)); }
        /// @}

        namespace deprecated
        {
            size_t utf8_to_wstr(const char* src, wchar_t* dest, size_t destSize);
            size_t utf8_to_wstr(const char* src, wchar_t* dest, size_t destSize, omw::windows::ErrorCode& ec);
            static inline size_t utf8_to_wstr(const std::string& src, wchar_t* dest, size_t destSize) { return utf8_to_wstr(src.c_str(), dest, destSize); }
            static inline size_t utf8_to_wstr(const std::string& src, wchar_t* dest, size_t destSize, omw::windows::ErrorCode& ec) { return utf8_to_wstr(src.c_str(), dest, destSize, ec); }

            size_t wstr_to_utf8(const wchar_t* src, char* dest, size_t destSize);
            size_t wstr_to_utf8(const wchar_t* src, char* dest, size_t destSize, omw::windows::ErrorCode& ec);
            void wstr_to_utf8(const wchar_t* src, std::string& dest);
            void wstr_to_utf8(const wchar_t* src, std::string& dest, omw::windows::ErrorCode& ec);
        }

        /*! @} */
    }
}

#endif // OMW_PLAT_WIN
#endif // IG_OMW_WINDOWS_STRING_H
