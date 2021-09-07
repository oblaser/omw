/*
author      Oliver Blaser
date        07.09.2021
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


//! @param colorId Microsoft Color ID
//! See <https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getsyscolor> for color IDs.
omw::Color omw::windows::getSysColor(int colorId)
{
    DWORD winCol = GetSysColor(colorId);
    omw::Color col;
    col.from_win32(winCol);
    return col;
}


#endif // OMW_PLAT_WIN
