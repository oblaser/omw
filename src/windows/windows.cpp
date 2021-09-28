/*
author      Oliver Blaser
date        28.09.2021
copyright   MIT - Copyright (c) 2021 Oliver Blaser
*/

#include "omw/windows/windows.h"

#ifdef OMW_PLAT_WIN

#include <stdexcept>
#include <string>
#include <vector>

#include "omw/defs.h"
#include "omw/windows/error.h"
#include "omw/windows/exception.h"
#include "omw/string.h"



//! @return Value of the performance counter
//! 
//! See <a href="https://docs.microsoft.com/en-us/windows/win32/api/profileapi/nf-profileapi-queryperformancecounter" target="_blank">QueryPerformanceCounter()</a>
//! 
int64_t omw::windows::queryPerformanceCounter()
{
    LARGE_INTEGER value;
    QueryPerformanceCounter(&value);
    return value.QuadPart;
}

//! @return Frequency of the performance counter
//! 
//! See <a href="https://docs.microsoft.com/en-us/windows/win32/api/profileapi/nf-profileapi-queryperformancefrequency" target="_blank">QueryPerformanceFrequency()</a>
//! 
int64_t omw::windows::queryPerformanceFrequency()
{
    LARGE_INTEGER f;
    QueryPerformanceFrequency(&f);
    return f.QuadPart;
}

/*!
* \fn int64_t omw::windows::perfCntrGetTick()
* \return Value of the performance counter
*
* Alias for queryPerformanceCounter().
*/

//! @param t_s Duration in seconds
//! @return The number of ticks which represent the duration
//! 
//! Calculates the number of ticks based on the \ref queryPerformanceFrequency() "frequency" of the performance counter.
//! 
int64_t omw::windows::perfCntrCalcTickCount(double t_s)
{
    const double f = (double)omw::windows::queryPerformanceFrequency();
    const double ticks = t_s * f;   // duration = number of ticks * period
                                    // t = ticks * 1/f  <=>  ticks = t * f
    int64_t result;

    if ((ticks > 0.0) && (ticks <= (double)(INT64_MAX))) result = std::llround(ticks);
    else result = -1;

    return result;
}

//! @param t_s Duration in seconds
//! @return The number of ticks which represent the duration
//! 
//! See perfCntrCalcTickCount().
//! 
int64_t omw::windows::perfCntrCalcTickCount_s(uint32_t t_s)
{
    return omw::windows::perfCntrCalcTickCount(t_s);
}

//! @param t_ms Duration in milliseconds
//! @return The number of ticks which represent the duration
//! 
//! See perfCntrCalcTickCount().
//! 
int64_t omw::windows::perfCntrCalcTickCount_ms(uint32_t t_ms)
{
    return omw::windows::perfCntrCalcTickCount(t_ms / 1'000.0);
}

//! @param t_us Duration in microseconds
//! @return The number of ticks which represent the duration
//! 
//! See perfCntrCalcTickCount().
//! 
int64_t omw::windows::perfCntrCalcTickCount_us(uint32_t t_us)
{
    return omw::windows::perfCntrCalcTickCount(t_us / 1'000'000.0);
}

/*!
* \fn bool omw::windows::perfCntrElapsed(int64_t& oldTick, int64_t tickDuration)
* \param [in, out] oldTick Reference to the variable that holds the last tick value
* \param tickDuration The number of ticks which represent the duration between two elapsed events
* \return `true` if the time has elapsed, otherwise `false`
* 
* The `oldTick` variable should be initialized with the return value of perfCntrGetTick().
* The `tickDuration` should be calculated once by perfCntrCalcTickCount() or `perfCntrCalcTickCount_..()`.
*/



#endif // OMW_PLAT_WIN
