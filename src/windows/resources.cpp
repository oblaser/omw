/*
author      Oliver Blaser
date        28.06.2021
copyright   MIT - Copyright (c) 2021 Oliver Blaser
*/

#include "omw/windows/resources.h"

#ifdef OMW_PLAT_WIN

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "omw/windows/resources_rc.h"

#include <Windows.h>



template<typename DataType, typename SizeType>
inline omw::windows::Basic_Resource<DataType, SizeType>::Basic_Resource()
    : resData(nullptr), resSize(0)
{
}

template<typename DataType, typename SizeType>
omw::windows::Basic_Resource<DataType, SizeType>::Basic_Resource(int idr, int type)
    : resData(nullptr), resSize(0)
{
    load(idr, type);
}

template<typename DataType, typename SizeType>
const DataType* omw::windows::Basic_Resource<DataType, SizeType>::begin() const
{
    return resData;
}

template<typename DataType, typename SizeType>
const DataType* omw::windows::Basic_Resource<DataType, SizeType>::data() const
{
    return resData;
}

template<typename DataType, typename SizeType>
const DataType* omw::windows::Basic_Resource<DataType, SizeType>::end() const
{
    return resData + resSize;
}

template<typename DataType, typename SizeType>
SizeType omw::windows::Basic_Resource<DataType, SizeType>::size() const
{
    return resSize;
}

template<typename DataType, typename SizeType>
void omw::windows::Basic_Resource<DataType, SizeType>::load(int idr, int type)
{

    // TODO: error handling

    HMODULE handle = GetModuleHandle(NULL);
    HRSRC rc = FindResource(handle, MAKEINTRESOURCE(idr), MAKEINTRESOURCE(type));
    HGLOBAL rcData = LoadResource(handle, rc);

    resSize = SizeofResource(handle, rc);
    resData = LockResource(rcData);
}



omw::windows::BinaryResource omw::windows::getBinaryResource(int idr)
{
    return omw::windows::BinaryResource(idr, OMW_RCT_BINFILE);
}

omw::windows::StringResource omw::windows::getStringResource(int idr)
{
    return omw::windows::StringResource(idr, OMW_RCT_TEXTFILE);
}

std::vector<char> omw::windows::getResource(int idr, int type)
{
    // TODO: error handling

    HMODULE handle = GetModuleHandle(NULL);
    HRSRC rc = FindResource(handle, MAKEINTRESOURCE(idr), MAKEINTRESOURCE(type));
    HGLOBAL rcData = LoadResource(handle, rc);

    DWORD size = SizeofResource(handle, rc);
    void* data = LockResource(rcData);


    return std::vector<char>((const char*)data, (const char*)data + size);
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
