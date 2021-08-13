/*
author      Oliver Blaser
date        13.08.2021
copyright   MIT - Copyright (c) 2021 Oliver Blaser
*/

#ifndef OMW_WINDOWS_RESOURCES_H
#define OMW_WINDOWS_RESOURCES_H

#include "../../omw/defs.h"
#ifdef OMW_PLAT_WIN

#include <cstdint>
#include <string>
#include <vector>

#include "../../omw/windows/error.h"



namespace omw
{
    namespace windows
    {
        std::vector<uint8_t> getBinaryResource(int idr);
        std::vector<uint8_t> getBinaryResource(int idr, omw::windows::ErrorCode& ec) noexcept;
        std::string getTextResource(int idr);
        std::string getTextResource(int idr, omw::windows::ErrorCode& ec) noexcept;

        const uint8_t* getResource(int idr, int type, size_t* size);
        const uint8_t* getResource(int idr, int type, size_t* size, omw::windows::ErrorCode& ec) noexcept;
        std::vector<uint8_t> getResource(int idr, int type);
        std::vector<uint8_t> getResource(int idr, int type, omw::windows::ErrorCode& ec) noexcept;

        int getResourceTypeBin();
        int getResourceTypeText();
    }
}

#endif // OMW_PLAT_WIN
#endif // OMW_WINDOWS_RESOURCES_H
