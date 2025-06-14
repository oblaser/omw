/*
author          Oliver Blaser
copyright       MIT - Copyright (c) 2024 Oliver Blaser
*/

#include "omw/windows/windows.h"
#ifdef OMW_PLAT_WIN


#include <stdexcept>
#include <string>
#include <vector>

#include "omw/string.h"
#include "omw/windows/error.h"
#include "omw/windows/exception.h"
#include "omw/windows/string.h"

#include <Windows.h>


namespace {

// clang-format off
    static_assert(
        (CP_ACP == omw::windows::ACP) &&
        (CP_OEMCP == omw::windows::OEMCP) &&
        (CP_MACCP == omw::windows::MACCP) &&
        (CP_THREAD_ACP == omw::windows::THREAD_ACP) &&
        (CP_SYMBOL == omw::windows::SYMBOLCP) &&
        (CP_UTF7 == omw::windows::UTF7CP) &&
        (CP_UTF8 == omw::windows::UTF8CP),
        "invalid code page definitions");
// clang-format on

// expected format: string1\0string2\0\0
std::vector<std::string> multiStringConvert(LPCWSTR multiStr)
{
    const WCHAR* p = multiStr;

    std::vector<const WCHAR*> wStrings;
    do {
        wStrings.push_back(p);
        while (*p != 0) { ++p; }
        ++p;
    }
    while (*p != 0);

    std::vector<std::string> strings;
    for (size_t i = 0; i < wStrings.size(); ++i) { strings.push_back(omw::windows::wstou8(wStrings[i])); }

    return strings;
}

std::vector<std::string> queryDosDevice_base(const WCHAR* deviceName)
{
    std::vector<WCHAR> buffer;
    buffer.resize(8192);

    bool querying = true;
    while (querying)
    {
        const DWORD r = QueryDosDeviceW(deviceName, buffer.data(), buffer.size());

        if (r == 0)
        {
            DWORD error = GetLastError();

            if (error == ERROR_INSUFFICIENT_BUFFER) { buffer.resize(buffer.size() * 2); }
            else
            {
                // TODO: add some error handling

                buffer.clear();
                buffer.push_back(0);
                buffer.push_back(0);

                querying = false;
            }
        }
        else { querying = false; }
    }

    return multiStringConvert(buffer.data());
}

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

} // namespace


//! @return
//!
//! \b Exceptions
//! - `omw::windows::wstou8()` is called and may throw exceptions
//!
std::vector<std::string> omw::windows::getAllDosDevices() { return queryDosDevice_base(nullptr); }

//! @param device Device, UTF-8 encoded
//! @return
//!
//! \b Exceptions
//! - `omw::windows::wstou8()` and `::u8tows()` is called and may throw exceptions
//!
std::vector<std::string> omw::windows::queryDosDevice(const std::string& device_u8) { return queryDosDevice_base(omw::windows::u8tows(device_u8).c_str()); }

//! @return Value of the performance counter
//!
//! See <a href="https://docs.microsoft.com/en-us/windows/win32/api/profileapi/nf-profileapi-queryperformancecounter"
//! target="_blank">QueryPerformanceCounter()</a>
//!
int64_t omw::windows::queryPerformanceCounter()
{
    LARGE_INTEGER value;
    QueryPerformanceCounter(&value);
    return value.QuadPart;
}

//! @return Frequency of the performance counter
//!
//! See <a href="https://docs.microsoft.com/en-us/windows/win32/api/profileapi/nf-profileapi-queryperformancefrequency"
//! target="_blank">QueryPerformanceFrequency()</a>
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
    return std::lround(omw::windows::perfCntrCalcDuration(startTick, endTick) * 1000.0);
}

uint32_t omw::windows::perfCntrCalcDuration_us(int64_t startTick)
{
    const int64_t endTick = omw::windows::perfCntrGetTick();
    return omw::windows::perfCntrCalcDuration_us(startTick, endTick);
}

uint32_t omw::windows::perfCntrCalcDuration_us(int64_t startTick, int64_t endTick)
{
    return std::lround(omw::windows::perfCntrCalcDuration(startTick, endTick) * 1000000.0);
}

//! @param t_s Duration in seconds
//! @return The number of ticks which represent the duration
//!
//! Calculates the number of ticks based on the \ref queryPerformanceFrequency() "frequency" of the performance counter.
//!
int64_t omw::windows::perfCntrCalcTickCount(double t_s)
{
    const double f = (double)omw::windows::queryPerformanceFrequency();
    const double ticks = t_s * f; // duration = number of ticks * period
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
int64_t omw::windows::perfCntrCalcTickCount_s(uint32_t t_s) { return omw::windows::perfCntrCalcTickCount(t_s); }

//! @param t_ms Duration in milliseconds
//! @return The number of ticks which represent the duration
//!
//! See perfCntrCalcTickCount().
//!
int64_t omw::windows::perfCntrCalcTickCount_ms(uint32_t t_ms) { return omw::windows::perfCntrCalcTickCount(t_ms / 1000.0); }

//! @param t_us Duration in microseconds
//! @return The number of ticks which represent the duration
//!
//! See perfCntrCalcTickCount().
//!
int64_t omw::windows::perfCntrCalcTickCount_us(uint32_t t_us) { return omw::windows::perfCntrCalcTickCount(t_us / 1000000.0); }

void omw::windows::perfCntrSleep(double t_s)
{
    int64_t startTick = omw::windows::perfCntrGetTick();
    const int64_t duration = omw::windows::perfCntrCalcTickCount(t_s);
    while (!omw::windows::perfCntrElapsed(startTick, duration)) {}
}

void omw::windows::perfCntrSleep_s(uint32_t t_s)
{
    int64_t startTick = omw::windows::perfCntrGetTick();
    const int64_t duration = omw::windows::perfCntrCalcTickCount_s(t_s);
    while (!omw::windows::perfCntrElapsed(startTick, duration)) {}
}

void omw::windows::perfCntrSleep_ms(uint32_t t_ms)
{
    int64_t startTick = omw::windows::perfCntrGetTick();
    const int64_t duration = omw::windows::perfCntrCalcTickCount_ms(t_ms);
    while (!omw::windows::perfCntrElapsed(startTick, duration)) {}
}

void omw::windows::perfCntrSleep_us(uint32_t t_us)
{
    int64_t startTick = omw::windows::perfCntrGetTick();
    const int64_t duration = omw::windows::perfCntrCalcTickCount_us(t_us);
    while (!omw::windows::perfCntrElapsed(startTick, duration)) {}
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
//! See also <a href="https://docs.microsoft.com/en-us/windows/console/setconsolemode" target="_blank">SetConsoleMode()</a> and
//! <b><tt>ENABLE_VIRTUAL_TERMINAL_PROCESSING</tt></b>
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

//! @return The code page on success, 0 otherwise
//!
//! See \ref omw_windows_consoleCodePage_infoText.
//!
omw::windows::codepage_t omw::windows::consoleGetInCodePage() { return GetConsoleCP(); }

//! @return The code page on success, 0 otherwise
//!
//! See \ref omw_windows_consoleCodePage_infoText.
//!
omw::windows::codepage_t omw::windows::consoleGetOutCodePage() { return GetConsoleOutputCP(); }

//! @return <tt>true</tt> on success, <tt>false</tt> otherwise
//!
//! See \ref omw_windows_consoleCodePage_infoText.
//!
bool omw::windows::consoleSetInCodePage(codepage_t cp) { return (SetConsoleCP(cp) != 0); }

//! @return <tt>true</tt> on success, <tt>false</tt> otherwise
//!
//! See \ref omw_windows_consoleCodePage_infoText.
//!
bool omw::windows::consoleSetOutCodePage(codepage_t cp) { return (SetConsoleOutputCP(cp) != 0); }

//! @brief Sets the input and output code page of the console.
//! @return <tt>true</tt> on success, <tt>false</tt> otherwise
//!
//! See \ref omw_windows_consoleCodePage_infoText.
//!
bool omw::windows::consoleSetCodePage(codepage_t cp) { return (omw::windows::consoleSetInCodePage(cp) && omw::windows::consoleSetOutCodePage(cp)); }


//! @return <tt>true</tt> on success, <tt>false</tt> otherwise
//!
//! Passes <b><tt>CP_UTF8</tt></b> to consoleSetCodePage().
//!
bool omw::windows::consoleSetCodePageUTF8() { return omw::windows::consoleSetCodePage(CP_UTF8); }


#endif // OMW_PLAT_WIN
