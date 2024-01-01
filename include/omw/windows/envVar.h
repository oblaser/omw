/*
author          Oliver Blaser
date            31.12.2023
copyright       MIT - Copyright (c) 2023 Oliver Blaser
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
        /*! \addtogroup grp_windows
        * @{
        */

        //! \name Environment Variables
        /// @{
        std::string getEnvironmentVariable(const std::string& varName_u8);
        std::wstring getEnvironmentVariableW(const std::string& varName_u8);
        std::wstring getEnvironmentVariableW(const std::wstring& varName);
        /// @}

        namespace deprecated
        {
            constexpr size_t envVarValueMaxSize = 32767;

            std::string getEnvironmentVariable(const std::string& varName);
            std::string getEnvironmentVariable(const std::string& varName, omw::windows::ErrorCode& ec);
        }

        /*! @} */
    }
}

#endif // OMW_PLAT_WIN
#endif // IG_OMW_WINDOWS_ENVVAR_H
