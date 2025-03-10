/*
author          Oliver Blaser
copyright       MIT - Copyright (c) 2025 Oliver Blaser
*/

#ifndef IG_OMW_CLOCK_H
#define IG_OMW_CLOCK_H

#include <cstdint>
#include <ctime>

#include "../omw/defs.h"

#if OMW_PLAT_UNIX
#include <time.h>
#endif


/*! \addtogroup grp_clockLib
 * @{
 */

#define OMW_SECOND_s (1)
#define OMW_MINUTE_s (60 * OMW_SECOND_s)
#define OMW_HOUR_s   (60 * OMW_MINUTE_s)
#define OMW_DAY_s    (24 * OMW_HOUR_s)

#define OMW_SECOND_ms (OMW_SECOND_s * 1000)
#define OMW_MINUTE_ms (OMW_MINUTE_s * 1000)
#define OMW_HOUR_ms   (OMW_HOUR_s * 1000)
#define OMW_DAY_ms    (OMW_DAY_s * 1000)

#define OMW_SECOND_us (OMW_SECOND_ms * 1000)
#define OMW_MINUTE_us (OMW_MINUTE_ms * 1000)
#define OMW_HOUR_us   (OMW_HOUR_ms * 1000ll)
#define OMW_DAY_us    (OMW_DAY_ms * 1000ll)

#define OMW_TIMEPOINT_MIN (INT64_MIN)
#define OMW_TIMEPOINT_MAX (INT64_MAX)

/*! @} */


namespace omw {
namespace clock {

    /*! \addtogroup grp_clockLib
     * @{
     */

    /**
     * @brief Counter value with 1us resolution.
     */
    using timepoint_t = int64_t;
    // int64 max = 9'223'372'036'854'775'807
    //                    10'000'000'000'000 ms = approx 316 years
    //                10'000'000'000'000'000 us = approx 316 years


    constexpr timepoint_t timepoint_min = OMW_TIMEPOINT_MIN;
    constexpr timepoint_t timepoint_max = OMW_TIMEPOINT_MAX;

    constexpr timepoint_t second_s = OMW_SECOND_s;
    constexpr timepoint_t minute_s = OMW_MINUTE_s;
    constexpr timepoint_t hour_s = OMW_HOUR_s;
    constexpr timepoint_t day_s = OMW_DAY_s;

    constexpr timepoint_t second_ms = OMW_SECOND_ms;
    constexpr timepoint_t minute_ms = OMW_MINUTE_ms;
    constexpr timepoint_t hour_ms = OMW_HOUR_ms;
    constexpr timepoint_t day_ms = OMW_DAY_ms;

    constexpr timepoint_t second_us = OMW_SECOND_us;
    constexpr timepoint_t minute_us = OMW_MINUTE_us;
    constexpr timepoint_t hour_us = OMW_HOUR_us;
    constexpr timepoint_t day_us = OMW_DAY_us;


    /**
     * @brief Returns the current counter value.
     *
     * - Unix: `CLOCK_MONOTONIC`
     * - Linux: `CLOCK_BOOTTIME`
     * - Windows: `PerformanceCounter`
     */
    timepoint_t now();

    static inline bool elapsed_us(timepoint_t now_us, timepoint_t start_us, timepoint_t interval_us) { return ((now_us - start_us) >= interval_us); }

    static inline bool elapsed_ms(timepoint_t now_us, timepoint_t start_us, int64_t interval_ms)
    {
        return elapsed_us(now_us, start_us, ((timepoint_t)interval_ms * 1000ll));
    }

    /**
     * See \ref timespec for parameter description.
     */
    static inline timepoint_t fromTimespec(time_t tv_sec, long long tv_nsec)
    {
        timepoint_t us = (timepoint_t)tv_sec * second_us;

        // According to the GNU spec tv_nsec describes "the number of nanoseconds elapsed since the time given by the tv_sec member". This means that the nsec
        // field goes always forwards in time, and is not added to the magnitude of the seconds since epoch.
        us += (timepoint_t)tv_nsec / 1000ll;

        return us;
    }

#if OMW_PLAT_UNIX || (OMW_CPPSTD >= OMW_CPPSTD_17) || defined(OMWi_DOXYGEN_PREDEFINE)
    static inline timepoint_t fromTimespec(const struct timespec& tspec) { return fromTimespec(tspec.tv_sec, tspec.tv_nsec); }
    static inline timepoint_t fromTimespec(const struct timespec* tspec) { return fromTimespec(tspec->tv_sec, tspec->tv_nsec); }
#endif

    /*! @} */

} // namespace clock
} // namespace omw


#endif // IG_OMW_CLOCK_H
