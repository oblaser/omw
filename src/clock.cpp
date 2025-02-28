/*
author          Oliver Blaser
copyright       MIT - Copyright (c) 2025 Oliver Blaser
*/

#include <cstdint>

#include "omw/clock.h"
#include "omw/defs.h"
#include "omw/windows/windows.h"

#if defined(OMW_PLAT_UNIX) || defined(OMW_PLAT_LINUX)
#include <time.h>
#endif // UNIX || LINUX



omw::clock::timepoint_t omw::clock::now()
{
    timepoint_t r = 0;

#if defined(OMW_PLAT_UNIX)

#ifdef OMW_PLAT_LINUX
    constexpr clockid_t clockId = CLOCK_BOOTTIME;
#else
    constexpr clockid_t clockId = CLOCK_MONOTONIC;
#endif

    struct timespec tp;
    if (clock_gettime(clockId, &tp) == 0) { r = fromTimespec(tp.tv_sec, tp.tv_nsec); }
    else { r = 0; }

#elif defined(OMW_PLAT_WIN)

    static int64_t freq = 0;
    if (!freq) { freq = omw::windows::queryPerformanceFrequency(); }

    r = (omw::windows::queryPerformanceCounter() * 1000000ll) / freq;

#else // OMW_PLAT_
#error "platform not supported"
#endif // OMW_PLAT_

    return r;
}
