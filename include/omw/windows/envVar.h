/*
author      Oliver Blaser
date        09.06.2021
copyright   MIT - Copyright (c) 2021 Oliver Blaser
*/

#ifndef OMW_WINDOWS_ENVVAR_H
#define OMW_WINDOWS_ENVVAR_H

#include "../../omw/defs.h"
#ifdef OMW_PLAT_WIN

#include <cstddef>
#include <string>

#include "../../omw/windows/error.h"

#include <Windows.h>

namespace omw
{
    namespace windows
    {
        constexpr size_t envVarValueMaxSize = 32767;

        std::string getEnvironmentVariable(const std::string& varName);
        std::string getEnvironmentVariable(const std::string& varName, ErrorCode& ec) noexcept;
    }
}

#endif // OMW_PLAT_WIN
#endif // OMW_WINDOWS_ENVVAR_H
