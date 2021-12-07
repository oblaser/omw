/*
author          Oliver Blaser
date            07.12.2021
copyright       MIT - Copyright (c) 2021 Oliver Blaser
*/

#ifndef IG_OMW_WINDOWS_WINDOWS_H
#define IG_OMW_WINDOWS_WINDOWS_H

#include "../../omw/defs.h"
#ifdef OMW_PLAT_WIN

#include <cstdint>

#include "../../omw/windows/envVar.h"
#include "../../omw/windows/error.h"
#include "../../omw/windows/exception.h"
#include "../../omw/windows/string.h"

#include <Windows.h>

namespace omw
{
    namespace windows
    {
        //! \name Performance Counter
        /// @{
        int64_t queryPerformanceCounter();
        int64_t queryPerformanceFrequency();

        double perfCntrCalcDuration(int64_t startTick, int64_t endTick);
        uint32_t perfCntrCalcDuration_s(int64_t startTick);
        uint32_t perfCntrCalcDuration_s(int64_t startTick, int64_t endTick);
        uint32_t perfCntrCalcDuration_ms(int64_t startTick);
        uint32_t perfCntrCalcDuration_ms(int64_t startTick, int64_t endTick);
        uint32_t perfCntrCalcDuration_us(int64_t startTick);
        uint32_t perfCntrCalcDuration_us(int64_t startTick, int64_t endTick);
        int64_t perfCntrCalcTickCount(double t_s);
        int64_t perfCntrCalcTickCount_s(uint32_t t_s);
        int64_t perfCntrCalcTickCount_ms(uint32_t t_ms);
        int64_t perfCntrCalcTickCount_us(uint32_t t_us);
        void perfCntrSleep(double t_s);
        void perfCntrSleep_s(uint32_t t_s);
        void perfCntrSleep_ms(uint32_t t_ms);
        void perfCntrSleep_us(uint32_t t_us);
        inline int64_t perfCntrGetTick()
        {
            return omw::windows::queryPerformanceCounter();
        }
        inline bool perfCntrElapsed(int64_t& oldTick, int64_t tickDuration)
        {
            bool r;
            const int64_t tick = omw::windows::perfCntrGetTick();
            if ((tick - oldTick) >= tickDuration) { r = true; oldTick = tick; }
            else r = false;
            return r;
        }
        /// @}

        bool beep(uint32_t frequency, uint32_t duration_ms, bool blocking = false);

        bool consoleEnableVT100();
    }
}

#endif // OMW_PLAT_WIN
#endif // IG_OMW_WINDOWS_WINDOWS_H
