/*
author          Oliver Blaser
date            09.06.2021
copyright       MIT - Copyright (c) 2021 Oliver Blaser
*/

#ifndef IG_OMW_WINDOWS_ENVVAR_H
#define IG_OMW_WINDOWS_ENVVAR_H

#include "../../omw/defs.h"
#ifdef OMW_PLAT_WIN

#include <cstddef>
#include <string>

#include "../../omw/windows/error.h"

namespace omw
{
    namespace windows
    {
        constexpr size_t envVarValueMaxSize = 32767;

        //! \name Environment Variables
        /// @{
        std::string getEnvironmentVariable(const std::string& varName);
        std::string getEnvironmentVariable(const std::string& varName, omw::windows::ErrorCode& ec);
        /// @}
    }
}

#endif // OMW_PLAT_WIN
#endif // IG_OMW_WINDOWS_ENVVAR_H
