/*
author          Oliver Blaser
date            13.12.2021
copyright       MIT - Copyright (c) 2021 Oliver Blaser
*/

#ifndef IG_OMW_DEFS_H
#define IG_OMW_DEFS_H

/*! \addtogroup grp_macro
* @{
*/


//! \name Misc
/// @{
#ifdef _DEBUG
#define OMW_DEBUG (1)
#else
#undef OMW_DEBUG
#endif
#ifdef OMWi_DOXYGEN_EXCLUDE_FROM_DOC
#define OMW_DEBUG (1)
#endif // OMWi_DOXYGEN_EXCLUDE_FROM_DOC
/*!
* \def OMW_DEBUG
* \brief Defined as `1` if `_DEBUG` is defined, undefined otherwise.
*/



//! @brief Returns the filename of the current file as `const char*`.
//! 
//! Similar to `__FILE__`, but does not contain the full path.
//! 
#define OMW__FILENAME__     (OMWi_file_to_filename(__FILE__))

/// @}



//! \name Platform
/// @{
#ifdef OMWi_DOXYGEN_EXCLUDE_FROM_DOC
#define OMW_PLAT_WIN32 (1)
#endif // OMWi_DOXYGEN_EXCLUDE_FROM_DOC

#if (defined(_WIN32) && !defined(_WIN64))
#define OMW_PLAT_WIN32 (1)
#endif
#ifdef _WIN64
#define OMW_PLAT_WIN64 (1)
#endif
#ifdef __unix__
#define OMW_PLAT_UNIX (1)
#endif
#if (defined(OMW_PLAT_WIN32) || defined(OMW_PLAT_WIN64))
#define OMW_PLAT_WIN (1)
#endif

/*!
* \def OMW_PLAT_WIN32
* \brief Defined as `1` if target is 32-bit Windows, undefined otherwise.
*/
/*!
* \def OMW_PLAT_WIN64
* \brief Defined as `1` if target is 64-bit Windows, undefined otherwise.
*/
/*!
* \def OMW_PLAT_UNIX
* \brief Defined as `1` if `__unix__` is defined, undefined otherwise.
*/
/*!
* \def OMW_PLAT_WIN
* \brief Defined as `1` if `OMW_PLAT_WIN32` or `OMW_PLAT_WIN64` is defined, undefined otherwise.
*/
/// @}

/*! @} */



//
// internal
//

#ifndef OMWi_DOXYGEN_EXCLUDE_FROM_DOC

#define OMWi_DISPSTR(x) (x)

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

#endif // OMWi_DOXYGEN_EXCLUDE_FROM_DOC

// check for invalid combinations
#if ((defined(OMW_PLAT_WIN32) || defined(OMW_PLAT_WIN64) || defined(OMW_PLAT_WIN)) && defined(OMW_PLAT_UNIX))
#error invalid platform
#endif
#if (!defined(_DEBUG) && OMW_DEBUG)
#error invalid debug configuration
#endif

#endif // IG_OMW_DEFS_H
