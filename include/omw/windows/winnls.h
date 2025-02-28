/*
author          Oliver Blaser
copyright       MIT - Copyright (c) 2024 Oliver Blaser
*/

#ifndef IG_OMW_WINDOWS_WINNLS_H
#define IG_OMW_WINDOWS_WINNLS_H

#include "../../omw/defs.h"
#ifdef OMW_PLAT_WIN


namespace omw {
namespace windows {

    /*! \addtogroup grp_windows
     * @{
     */

    //! Windows code pages are handled with type UINT (see e.g. SetConsoleCP), which is `unsigned int`, which in return is always equal to uint32_t on Windows
    //! (see https://en.cppreference.com/w/cpp/language/types#Data_models).
    using codepage_t = uint32_t;

    // from Win NLS
    enum WINNLS_CODEPAGE
    {
        ACP = 0,        //!< default to ANSI code page
        OEMCP = 1,      //!< default to OEM  code page
        MACCP = 2,      //!< default to MAC  code page
        THREAD_ACP = 3, //!< current thread's ANSI code page
        SYMBOLCP = 42,  //!< SYMBOL translations
        UTF7CP = 65000, //!< UTF-7 translation
        UTF8CP = 65001, //!< UTF-8 translation
    };

    /*! @} */

} // namespace windows
} // namespace omw


#endif // OMW_PLAT_WIN
#endif // IG_OMW_WINDOWS_WINNLS_H
