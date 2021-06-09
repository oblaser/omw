/*
author         Oliver Blaser
date           08.06.2021
copyright      MIT - Copyright (c) 2021 Oliver Blaser
*/

#ifndef OMW_DEFS_H
#define OMW_DEFS_H


// platform
#ifdef _WIN32
#define OMW_PLAT_WIN32 (1)
#endif
#ifdef _WIN64
#define OMW_PLAT_WIN64 (1)
#endif
#ifdef __unix__
#define OMW_PLAT_UNIX (1)
#endif
#if (OMW_PLAT_WIN32 || OMW_PLAT_WIN64)
#define OMW_PLAT_WIN (1)
#endif

// debugging
#ifdef _DEBUG
#define OMW_DEBUG (1)
#endif


constexpr const char* OMWi_file_to_filename(const char* p)
{
    const char* fn = p;
    while (*p)
    {
#if OMW_PLAT_WIN
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





//
// internal use
//

#define OMWi_DISPSTR(x) (x)

// check for invalid combinations
#if ((OMW_PLAT_WIN32 || OMW_PLAT_WIN64 || OMW_PLAT_WIN) && OMW_PLAT_UNIX)
#error invalid platform
#endif
#ifndef _DEBUG
#if OMW_DEBUG
#error invalid debug configuration
#endif
#endif

#endif // OMW_DEFS_H
