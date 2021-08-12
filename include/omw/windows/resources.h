/*
author      Oliver Blaser
date        28.06.2021
copyright   MIT - Copyright (c) 2021 Oliver Blaser
*/

#ifndef OMW_WINDOWS_RESOURCES_H
#define OMW_WINDOWS_RESOURCES_H

#include "../../omw/defs.h"
#ifdef OMW_PLAT_WIN

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace omw
{
    namespace windows
    {
        template <typename DataType, typename SizeType = size_t>
        class Basic_Resource
        {
        public:
            using size_type = SizeType;

        public:
            Basic_Resource();
            Basic_Resource(int idr, int type);
            virtual ~Basic_Resource() {}
            
            const DataType* begin() const;
            const DataType* data() const;
            const DataType* end() const;
            size_type size() const;

        protected:
            virtual void load(int idr, int type);

        protected:
            const void* resData;
            size_type resSize;
        };

        using BinaryResource = omw::windows::Basic_Resource<uint8_t>;
        using StringResource = omw::windows::Basic_Resource<char>;

        omw::windows::BinaryResource getBinaryResource(int idr);
        omw::windows::StringResource getStringResource(int idr);

        std::vector<char> getResource(int idr, int type);
        int getResourceTypeBin();
        int getResourceTypeText();
    }
}

#endif // OMW_PLAT_WIN
#endif // OMW_WINDOWS_RESOURCES_H
