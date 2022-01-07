/*
author          Oliver Blaser
date            07.01.2022
copyright       MIT - Copyright (c) 2022 Oliver Blaser
*/

#ifndef IG_OMW_ENCODING_H
#define IG_OMW_ENCODING_H

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "../omw/defs.h"
#include "../omw/int.h"
#include "../omw/string.h"

namespace omw
{
    /*! \addtogroup grp_utility_gpUtil_encoding
    * @{
    */

    namespace bcd
    {
    }

    namespace bigEndian
    {
        int16_t decode_i16(const uint8_t* data, size_t count = 2);
        uint16_t decode_ui16(const uint8_t* data, size_t count = 2);
        int32_t decode_i32(const uint8_t* data, size_t count = 4);
        uint32_t decode_ui32(const uint8_t* data, size_t count = 4);
        int64_t decode_i64(const uint8_t* data, size_t count = 8);
        uint64_t decode_ui64(const uint8_t* data, size_t count = 8);
        omw::int128_t decode_i128(const uint8_t* data, size_t count = 16);
        omw::uint128_t decode_ui128(const uint8_t* data, size_t count = 16);

        void encode_16(uint8_t* buffer, int16_t value);
        void encode_16(uint8_t* buffer, uint16_t value);
        void encode_32(uint8_t* buffer, int32_t value);
        void encode_32(uint8_t* buffer, uint32_t value);
        void encode_64(uint8_t* buffer, int64_t value);
        void encode_64(uint8_t* buffer, uint64_t value);
        void encode_128(uint8_t* buffer, const omw::Base_Int128& value);
    }

    namespace url
    {
        //omw::string decode();
        omw::string encode(const std::string& str);
    }

    /*! @} */
}

#endif // IG_OMW_ENCODING_H
