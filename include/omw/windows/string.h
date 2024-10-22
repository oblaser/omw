/*
author          Oliver Blaser
copyright       MIT - Copyright (c) 2024 Oliver Blaser
*/

#ifndef IG_OMW_WINDOWS_STRING_H
#define IG_OMW_WINDOWS_STRING_H

#include "../../omw/defs.h"
#ifdef OMW_PLAT_WIN

#include <cstddef>
#include <string>

#include "../../omw/windows/error.h"
#include "../../omw/windows/winnls.h"

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
        static inline std::wstring u8tows(const std::string& str) { return omw::windows::u8tows(str.c_str()); }

        std::string wstou8(const wchar_t* str);
        static inline std::string wstou8(const std::wstring& str) { return omw::windows::wstou8(str.c_str()); }

        std::wstring acptows(const char* str);
        static inline std::wstring acptows(const std::string& str) { return omw::windows::acptows(str.c_str()); }
        static inline std::string acptou8(const char* str) { return omw::windows::wstou8(omw::windows::acptows(str)); }
        static inline std::string acptou8(const std::string& str) { return omw::windows::wstou8(omw::windows::acptows(str)); }

        //std::wstring cptows(const char* str, unsigned int codepage);
        //static inline std::wstring cptows(const std::string& str, unsigned int codepage) { return omw::windows::cptows(str.c_str(), codepage); }
        //std::string wstocp(const wchar_t* str, unsigned int codepage);
        //static inline std::string wstocp(const std::wstring& str, unsigned int codepage) { return omw::windows::wstocp(str.c_str(), codepage); }
        //
        //static inline std::string cptou8(const char* str, unsigned int codepage) { return omw::windows::wstou8(omw::windows::cptows(str, codepage)); }
        //static inline std::string cptou8(const std::string& str, unsigned int codepage) { return omw::windows::cptou8(str.c_str(), codepage); }
        //static inline std::string u8tocp(const char* str, unsigned int codepage) { omw::windows::wstocp(omw::windows::u8tows(str), codepage); }
        //static inline std::string u8tocp(const std::string& str, unsigned int codepage) { return omw::windows::u8tocp(str.c_str(), codepage); }
        //
        //static inline std::wstring acptows(const char* str) { return omw::windows::cptows(str, omw::windows::ACP); }
        //static inline std::wstring acptows(const std::string& str) { return omw::windows::acptows(str.c_str()); }
        //static inline std::string wstoacp(const wchar_t* str) { return omw::windows::wstocp(str, omw::windows::ACP); }
        //static inline std::string wstoacp(const std::wstring& str) { return omw::windows::wstoacp(str.c_str()); }
        //
        //static inline std::string acptou8(const char* str) { return omw::windows::wstou8(omw::windows::acptows(str)); }
        //static inline std::string acptou8(const std::string& str) { return omw::windows::acptou8(str.c_str()); }
        //static inline std::string u8toacp(const char* str) { return omw::windows::wstoacp(omw::windows::u8tows(str)); }
        //static inline std::string u8toacp(const std::string& str) { return omw::windows::u8toacp(str.c_str()); }
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
