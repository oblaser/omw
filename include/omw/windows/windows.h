/*
author      Oliver Blaser
date        07.09.2021
copyright   MIT - Copyright (c) 2021 Oliver Blaser
*/

#ifndef OMW_WINDOWS_WINDOWS_H
#define OMW_WINDOWS_WINDOWS_H

#include "../../omw/defs.h"
#ifdef OMW_PLAT_WIN

#include "../../omw/color.h"

#include <Windows.h>

namespace omw
{
    namespace windows
    {
        omw::Color getSysColor(int colorId);
    }
}

#endif // OMW_PLAT_WIN
#endif // OMW_WINDOWS_WINDOWS_H
