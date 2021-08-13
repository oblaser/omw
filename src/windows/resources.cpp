/*
author      Oliver Blaser
date        13.08.2021
copyright   MIT - Copyright (c) 2021 Oliver Blaser
*/

#include "omw/windows/resources.h"

#ifdef OMW_PLAT_WIN

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "omw/windows/exception.h"
#include "omw/windows/resources_rc.h"

#include <Windows.h>



std::vector<uint8_t> omw::windows::getBinaryResource(int idr)
{
    return getResource(idr, OMW_RCT_BINFILE);
}

std::vector<uint8_t> omw::windows::getBinaryResource(int idr, omw::windows::ErrorCode& ec) noexcept
{
    return getResource(idr, OMW_RCT_BINFILE, ec);
}

std::string omw::windows::getTextResource(int idr)
{
    size_t size;
    const char* data = (const char*)getResource(idr, OMW_RCT_TEXTFILE, &size);

    return std::string(data, data + size);
}

std::string omw::windows::getTextResource(int idr, omw::windows::ErrorCode& ec) noexcept
{
    size_t size;
    const char* data = (const char*)getResource(idr, OMW_RCT_TEXTFILE, &size, ec);

    return std::string(data, data + size);
}

const uint8_t* omw::windows::getResource(int idr, int type, size_t* size)
{
    ErrorCode ec;
    const uint8_t* data = getResource(idr, type, size, ec);

    if (ec.good()) return data;
    else if (ec.code() == omw::windows::EC_RESOURCE_NOT_FOUND) throw omw::windows::resource_not_found(ec.msg());
    // else nop (EC_RESOURCE_NOT_LOADED throws std::runtime_error)

    throw std::runtime_error(ec.msg());
}

const uint8_t* omw::windows::getResource(int idr, int type, size_t* size, omw::windows::ErrorCode& ec) noexcept
{
    const uint8_t* data = nullptr;

    HMODULE handle = GetModuleHandleW(NULL);
    HRSRC rc = FindResourceW(handle, MAKEINTRESOURCEW(idr), MAKEINTRESOURCEW(type));

    if (rc)
    {
        HGLOBAL rcData = LoadResource(handle, rc);

        const size_t tmpSize = SizeofResource(handle, rc);
        data = (uint8_t*)LockResource(rcData);

        if (size) *size = tmpSize;

        if (rcData && tmpSize && data) ec = ErrorCode(omw::windows::EC_OK, OMWi_DISPSTR("OK"));
        else ec = ErrorCode(omw::windows::EC_RESOURCE_NOT_LOADED, OMWi_DISPSTR("could not load resource"));
    }
    else ec = ErrorCode(omw::windows::EC_RESOURCE_NOT_FOUND, OMWi_DISPSTR("resource not found"));

    return data;
}

std::vector<uint8_t> omw::windows::getResource(int idr, int type)
{
    size_t size;
    const uint8_t* data = getResource(idr, type, &size);

    return std::vector<uint8_t>(data, data + size);
}

std::vector<uint8_t> omw::windows::getResource(int idr, int type, omw::windows::ErrorCode& ec) noexcept
{
    std::vector<uint8_t> r;
    size_t size;
    const uint8_t* data = getResource(idr, type, &size, ec);

    if (ec.good()) r = std::vector<uint8_t>(data, data + size);

    return r;
}

int omw::windows::getResourceTypeBin()
{
    return OMW_RCT_BINFILE;
}

int omw::windows::getResourceTypeText()
{
    return OMW_RCT_TEXTFILE;
}


#endif // OMW_PLAT_WIN
