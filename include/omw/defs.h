/*
author         Oliver Blaser
date           30.09.2021
copyright      MIT - Copyright (c) 2021 Oliver Blaser
*/

#ifndef IG_OMW_DEFS_H
#define IG_OMW_DEFS_H


#include <cstddef>
#include <cstdint>


// platform
#if (defined(_WIN32) && !defined(_WIN64))
//! Defined as 1 if target is x86 Windows. Otherwise, undefined.
#define OMW_PLAT_WIN32 (1)
#endif
#ifdef _WIN64
//! Defined as 1 if target is x64 Windows. Otherwise, undefined.
#define OMW_PLAT_WIN64 (1)
#endif
#ifdef __unix__
//! Defined as 1 if `__unix__` is defined. Otherwise, undefined.
#define OMW_PLAT_UNIX (1)
#endif
#if (defined(OMW_PLAT_WIN32) || defined(OMW_PLAT_WIN64))
//! Defined as 1 if `OMW_PLAT_WIN32` or `OMW_PLAT_WIN64` is defined. Otherwise, undefined.
#define OMW_PLAT_WIN (1)
#endif

// debugging
#ifdef _DEBUG
#define OMW_DEBUG (1)
#else
#undef OMW_DEBUG
#endif



constexpr const char* OMWi_file_to_filename(const char* p)
{
    const char* fn = p;
    while (*p)
    {
#if defined(OMW_PLAT_WIN)
        if (*p++ == '\\') fn = p;
#else
        if (*p++ == '/') fn = p;
#endif
    }
    return fn;
}

//! @brief Macro wich returns the current source filename.
//! 
//! Similar to `__FILE__` but does not contain the full path.
#define OMW__FILENAME__     (OMWi_file_to_filename(__FILE__))





#define OMW_SIZE_MAX ((size_t)-1)






//
// internal use
//

#define OMWi_DISPSTR(x) (x)

// check for invalid combinations
#if ((defined(OMW_PLAT_WIN32) || defined(OMW_PLAT_WIN64) || defined(OMW_PLAT_WIN)) && defined(OMW_PLAT_UNIX))
#error invalid platform
#endif
#if (!defined(_DEBUG) && OMW_DEBUG)
#error invalid debug configuration
#endif

#endif // IG_OMW_DEFS_H
