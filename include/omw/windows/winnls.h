/*
author          Oliver Blaser
date            06.01.2024
copyright       MIT - Copyright (c) 2024 Oliver Blaser
*/

#ifndef IG_OMW_WINDOWS_WINNLS_H
#define IG_OMW_WINDOWS_WINNLS_H

#include "../../omw/defs.h"
#ifdef OMW_PLAT_WIN

namespace omw
{
    namespace windows
    {
        /*! \addtogroup grp_windows
        * @{
        */

        // from Win NLS
        enum WINNLS_CODEPAGE
        {
            ACP = 0,
            OEMCP = 1,
            MACCP = 2,
            THREAD_ACP = 3,
            SYMBOLCP = 42,
            UTF7CP = 65000,
            UTF8CP = 65001,
        };

        /*! @} */
    }
}

#endif // OMW_PLAT_WIN
#endif // IG_OMW_WINDOWS_WINNLS_H
