/*
author          Oliver Blaser
date            25.01.2022
copyright       MIT - Copyright (c) 2022 Oliver Blaser
*/

/*!
* \file
* \brief Some macro definitions.
*
* See also \ref grp_macro.
*/

#ifndef IG_OMW_DEFS_H
#define IG_OMW_DEFS_H

/*! \addtogroup grp_macro
* @{
*/



//! \name Compiler
//! 
//! `#include <omw/defs.h>`
//! 
//! Only one is defined, depending which compiler is used.
//! To check if any compiler is detected check if `OMW_CXX_UNKNOWN` is not defined.
//! 
/// @{

#ifndef OMWi_DOXYGEN_PREDEFINE

#if defined(__clang__)
#define OMW_CXX_CLANG (1)
#elif defined(__GNUC__) || defined(__GNUG__)
#define OMW_CXX_GCC (1)
#elif defined(_MSC_VER)
#define OMW_CXX_MSVC (1)
#elif defined(__MINGW32__)
#define OMW_CXX_MINGW32 (1)
#elif defined(__MINGW64__)
#define OMW_CXX_MINGW64 (1)
#elif defined(__EMSCRIPTEN__)
#define OMW_CXX_EMSCRIPTEN (1)
#else
#define OMW_CXX_UNKNOWN (1)
#endif

#else // OMWi_DOXYGEN_PREDEFINE
#define OMW_CXX_CLANG (1)
#define OMW_CXX_GCC (1)
#define OMW_CXX_MSVC (1)
#define OMW_CXX_MINGW32 (1)
#define OMW_CXX_MINGW64 (1)
#define OMW_CXX_EMSCRIPTEN (1)
#define OMW_CXX_UNKNOWN (1)
#endif // OMWi_DOXYGEN_PREDEFINE

/// @}



//! \name Platform
//! `#include <omw/defs.h>`
/// @{

#ifndef OMWi_DOXYGEN_PREDEFINE

#ifdef _WIN32
#define OMW_PLAT_WIN (1)
#ifdef _WIN64
#define OMW_PLAT_WIN64 (1)
#else // _WIN64
#define OMW_PLAT_WIN32 (1)
#endif // _WIN64
#endif // _WIN32

#if (defined(__unix__) || defined(__unix))
#define OMW_PLAT_UNIX (1)
#include <unistd.h>
#ifdef _POSIX_VERSION
#define OMW_PLAT_POSIX (1)
#endif // _POSIX_VERSION
#endif // Unix

#ifdef __linux__
#define OMW_PLAT_LINUX (1)
#endif // __linux__

#if (defined(__APPLE__) && defined(__MACH__))
#define OMW_PLAT_APPLE (1)
#endif // Apple



#if (defined(OMW_PLAT_UNIX) || defined(OMW_PLAT_APPLE))
#include <sys/param.h>
#ifdef BSD
#define OMW_PLAT_BSD (1)
#endif // BSD
#endif // Unix or Apple

#if !(defined(OMW_PLAT_WIN) || defined(OMW_PLAT_UNIX) || defined(OMW_PLAT_LINUX) || defined(OMW_PLAT_APPLE))
#define OMW_PLAT_UNKNOWN (1)
#endif



#else // OMWi_DOXYGEN_PREDEFINE
#define OMW_PLAT_WIN (1)
#define OMW_PLAT_WIN32 (1)
#define OMW_PLAT_WIN64 (1)
#define OMW_PLAT_UNIX (1)
#define OMW_PLAT_POSIX (1)
#define OMW_PLAT_LINUX (1)
#define OMW_PLAT_APPLE (1)
#define OMW_PLAT_BSD (1)
#define OMW_PLAT_UNKNOWN (1)
#endif // OMWi_DOXYGEN_PREDEFINE

/// @}



//! \name Processor Architecture
//! `#include <omw/defs.h>`
/// @{

#ifndef OMWi_DOXYGEN_PREDEFINE

#ifdef OMW_CXX_MSVC

#if defined(_M_IX86)
#define OMW_PARCH_x86_32 (1)
#elif (defined(_M_AMD64) || defined(_M_X64))
#define OMW_PARCH_x86_64 (1)
#elif defined(_M_ARM64)
#define OMW_PARCH_ARM64 (1)
#elif defined(_M_ARM)
#define OMW_PARCH_ARM32 (1)
#else
#define OMW_PARCH_UNKNOWN (1)
#endif

#else // OMW_CXX_MSVC

#if defined(__i386__)
#define OMW_PARCH_x86_32 (1)
#elif defined(__x86_64__)
#define OMW_PARCH_x86_64 (1)
#elif defined(__aarch64__)
#define OMW_PARCH_ARM64 (1)
#elif defined(__arm__)
#define OMW_PARCH_ARM32 (1)
#elif defined(__powerpc64__)
#define OMW_PARCH_POWERPC (1)
#else
#define OMW_PARCH_UNKNOWN (1)
#endif

#endif // OMW_CXX_MSVC



#else // OMWi_DOXYGEN_PREDEFINE
#define OMW_PARCH_x86_32 (1)
#define OMW_PARCH_x86_64 (1)
#define OMW_PARCH_ARM32 (1)
#define OMW_PARCH_ARM64 (1)
#define OMW_PARCH_POWERPC (1)
#define OMW_PARCH_UNKNOWN (1)
#endif // OMWi_DOXYGEN_PREDEFINE

/// @}



//! \name C++ Standard Version
//! `#include <omw/defs.h>`
/// @{

#define OMW_CPPSTD_98 (199711L)
#define OMW_CPPSTD_11 (201103L)
#define OMW_CPPSTD_14 (201402L)
#define OMW_CPPSTD_17 (201703L)
#define OMW_CPPSTD_20 (202002L)

//! 
//! C++23 isn't released yet! Thus the value may change in the future.
//! 
#define OMW_CPPSTD_23 (202100L)

#ifndef OMWi_DOXYGEN_PREDEFINE

#ifdef OMW_CXX_MSVC
#define OMW_CPPSTD (_MSVC_LANG)
#else // _MSC_VER
#define OMW_CPPSTD (__cplusplus)
#endif // _MSC_VER

#else // OMWi_DOXYGEN_PREDEFINE
#define OMW_CPPSTD
#endif // OMWi_DOXYGEN_PREDEFINE

/// @}


//! \name Misc
//! `#include <omw/defs.h>`
/// @{

#ifdef _DEBUG
#define OMW_DEBUG (1)
#endif // _DEBUG

#if (OMW_CPPSTD >= OMW_CPPSTD_14)
#define OMW__FILENAME__     (OMWi_file_to_filename(__FILE__))
#endif

#ifdef OMWi_DOXYGEN_PREDEFINE
#define OMW_DEBUG (1)
#endif // OMWi_DOXYGEN_PREDEFINE

/// @}

/*! @} */





//##############################################################################
//
//      Things below might not be of interest for users
// 
//##############################################################################



//==============================================================================
//
// internal
//

#ifndef OMWi_DOXYGEN_PREDEFINE

#define OMWi_DISPSTR(x) (x)

#ifdef OMW__FILENAME__
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
#endif // OMW__FILENAME__

#endif // OMWi_DOXYGEN_PREDEFINE



//==============================================================================
//
// doc
//


/*!
* \def OMW_PLAT_WIN32
* Defined as `1` if target is 32-bit Windows, otherwise undefined.
*/
/*!
* \def OMW_PLAT_WIN64
* Defined as `1` if target is 64-bit Windows, otherwise undefined.
*/
/*!
* \def OMW_PLAT_WIN
* Defined as `1` if `OMW_PLAT_WIN32` or `OMW_PLAT_WIN64` is defined, otherwise undefined.
*/


/*!
* \def OMW_CPPSTD
* 
* Used to compare against `OMW_CPPSTD_xx`.
* 
* If MSVC is used it's defined as an alias for the MSVC specific macro `_MSVC_LANG`, otherwise it's an alias for `__cplusplus`.
*/


/*!
* \def OMW_DEBUG
* Defined as `1` if `_DEBUG` is defined, otherwise undefined.
*/
/*!
* \def OMW__FILENAME__
* _since C++14_
* 
* Returns the filename of the current file as `const char*`.
* Similar to `__FILE__`, but does not contain the full path.
*/


#endif // IG_OMW_DEFS_H
