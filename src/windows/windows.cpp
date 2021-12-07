/*
author          Oliver Blaser
date            07.12.2021
copyright       MIT - Copyright (c) 2021 Oliver Blaser
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

#include <Windows.h>


namespace
{
    typedef struct
    {
        DWORD f;
        DWORD t;
    } beepThreadParams_t;

    DWORD WINAPI beep_thread(__in LPVOID lpParameter)
    {
        const beepThreadParams_t* const p = (beepThreadParams_t*)lpParameter;
        return (Beep(p->f, p->t) ? 0 : 1);
    }
}



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

double omw::windows::perfCntrCalcDuration(int64_t startTick, int64_t endTick)
{
    const double f = (double)omw::windows::queryPerformanceFrequency();
    const double ticks = (double)(endTick - startTick);
    return ticks / f;
}

uint32_t omw::windows::perfCntrCalcDuration_s(int64_t startTick)
{
    const int64_t endTick = omw::windows::perfCntrGetTick();
    return omw::windows::perfCntrCalcDuration_s(startTick, endTick);
}

uint32_t omw::windows::perfCntrCalcDuration_s(int64_t startTick, int64_t endTick)
{
    return std::lround(omw::windows::perfCntrCalcDuration(startTick, endTick));
}

uint32_t omw::windows::perfCntrCalcDuration_ms(int64_t startTick)
{
    const int64_t endTick = omw::windows::perfCntrGetTick();
    return omw::windows::perfCntrCalcDuration_ms(startTick, endTick);
}

uint32_t omw::windows::perfCntrCalcDuration_ms(int64_t startTick, int64_t endTick)
{
    return std::lround(omw::windows::perfCntrCalcDuration(startTick, endTick) * 1'000.0);
}

uint32_t omw::windows::perfCntrCalcDuration_us(int64_t startTick)
{
    const int64_t endTick = omw::windows::perfCntrGetTick();
    return omw::windows::perfCntrCalcDuration_us(startTick, endTick);
}

uint32_t omw::windows::perfCntrCalcDuration_us(int64_t startTick, int64_t endTick)
{
    return std::lround(omw::windows::perfCntrCalcDuration(startTick, endTick) * 1'000'000.0);
}

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

void omw::windows::perfCntrSleep(double t_s)
{
    int64_t startTick = omw::windows::perfCntrGetTick();
    const int64_t duration = omw::windows::perfCntrCalcTickCount(t_s);
    while (!omw::windows::perfCntrElapsed(startTick, duration));
}

void omw::windows::perfCntrSleep_s(uint32_t t_s)
{
    int64_t startTick = omw::windows::perfCntrGetTick();
    const int64_t duration = omw::windows::perfCntrCalcTickCount_s(t_s);
    while (!omw::windows::perfCntrElapsed(startTick, duration));
}

void omw::windows::perfCntrSleep_ms(uint32_t t_ms)
{
    int64_t startTick = omw::windows::perfCntrGetTick();
    const int64_t duration = omw::windows::perfCntrCalcTickCount_ms(t_ms);
    while (!omw::windows::perfCntrElapsed(startTick, duration));
}

void omw::windows::perfCntrSleep_us(uint32_t t_us)
{
    int64_t startTick = omw::windows::perfCntrGetTick();
    const int64_t duration = omw::windows::perfCntrCalcTickCount_us(t_us);
    while (!omw::windows::perfCntrElapsed(startTick, duration));
}

/*!
* \fn int64_t omw::windows::perfCntrGetTick()
* \return Value of the performance counter
*
* Alias for queryPerformanceCounter().
*/

/*!
* \fn bool omw::windows::perfCntrElapsed(int64_t& oldTick, int64_t tickDuration)
* \param [in, out] oldTick Reference to the variable that holds the last tick value
* \param tickDuration The number of ticks which represent the duration between two elapsed events
* \return `true` if the time has elapsed, otherwise `false`
*
* The `oldTick` variable should be initialized with the return value of perfCntrGetTick().
* The `tickDuration` should be calculated once by perfCntrCalcTickCount() or `perfCntrCalcTickCount_..()`.
*/



//! @param frequency In range [37, 32'767]
//! @param duration_ms 
//! @param blocking 
//! @return <tt>true</tt> on success, <tt>false</tt> otherwise
bool omw::windows::beep(uint32_t frequency, uint32_t duration_ms, bool blocking)
{
    bool r;

    if (blocking) r = (Beep(frequency, duration_ms) != 0);
    else
    {
        DWORD threadId;
        HANDLE threadHandle;
        static ::beepThreadParams_t params;

        params.f = frequency;
        params.t = duration_ms;

        threadHandle = CreateThread(0, 0, ::beep_thread, &params, 0, &threadId);

        r = (threadHandle != NULL);
    }

    return r;
}

//! @return <tt>true</tt> on success, <tt>false</tt> otherwise
//! 
//! <a href="https://docs.microsoft.com/en-us/windows/console/setconsolemode" target="_blank">SetConsoleMode()</a> <b><tt>|= ENABLE_VIRTUAL_TERMINAL_PROCESSING</tt></b>
//! 
bool omw::windows::consoleEnVirtualTermProc()
{
    bool r = false;

    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

    if (handle != INVALID_HANDLE_VALUE)
    {
        DWORD mode = 0;

        if (GetConsoleMode(handle, &mode))
        {
            mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

            if (SetConsoleMode(handle, mode)) r = true;
        }
    }

    return r;
}

//! @param cp Code page identifier
//! @return <tt>true</tt> on success, <tt>false</tt> otherwise
//! 
//! Sets the input and output code page of the console.
//! 
//! <a href="https://docs.microsoft.com/en-us/windows/console/setconsolecp" target="_blank">SetConsoleCP()</a>.
//! <a href="https://docs.microsoft.com/en-us/windows/console/setconsoleoutputcp" target="_blank">SetConsoleOutputCP()</a>.
//! 
//! See the list of <a href="https://docs.microsoft.com/en-us/windows/win32/intl/code-page-identifiers" target="_blank">code page identifier</a>.
//! 
bool omw::windows::consoleSetCodePage(uint32_t cp)
{
    return (SetConsoleCP((UINT)cp) && SetConsoleOutputCP((UINT)cp));
}


//! @return <tt>true</tt> on success, <tt>false</tt> otherwise
//! 
//! See consoleSetCodePage().
//! 
bool omw::windows::consoleSetCodePageUTF8()
{
    return omw::windows::consoleSetCodePage(65001);
}



#endif // OMW_PLAT_WIN
