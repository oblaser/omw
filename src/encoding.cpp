/*
author          Oliver Blaser
date            11.01.2022
copyright       MIT - Copyright (c) 2022 Oliver Blaser
*/

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

#include "omw/defs.h"
#include "omw/encoding.h"
#include "omw/int.h"
#include "omw/string.h"
#include "omw/utility.h"


namespace
{
    // Exceptions
    // - `std::invalid_argument`
    // - `std::overflow_error`
    template <typename T>
    T bigEndian_decodes(const uint8_t* data, size_t count, const std::string& fnName)
    {
        T r;

        if (data && count > 0)
        {
            if (data[0] & 0x80) r = -1;
            else r = 0;

            if (count > sizeof(T)) throw std::overflow_error(fnName);

            for (size_t i = 0; i < count; ++i)
            {
                omw::shiftLeftAssign(r, 8);
                r |= static_cast<T>(data[i]);
            }
        }
        else throw std::invalid_argument(fnName);

        return r;
    }

    // Exceptions
    // - `std::invalid_argument`
    // - `std::overflow_error`
    template <typename T>
    T bigEndian_decodeu(const uint8_t* data, size_t count, const std::string& fnName)
    {
        T r;

        if (data && count > 0)
        {
            r = 0;

            if (count > sizeof(T)) throw std::overflow_error(fnName);

            for (size_t i = 0; i < count; ++i)
            {
                omw::shiftLeftAssign(r, 8);
                r |= static_cast<T>(data[i]);
            }
        }
        else throw std::invalid_argument(fnName);

        return r;
    }
}



/* !
* \namespace omw::bcd
*
* `#include <omw/encoding.h>`
*
* Converts between BCD formated byte buffers and their integral values.
*/



/*!
* \namespace omw::bigEndian
*
* `#include <omw/encoding.h>`
*
* \section ns_omw_bigEndian_section_decodeFn Decode Functions
*
* \b Exceptions
* - `std::invalid_argument` if the data pointer is `NULL` or count equals zero
* - `std::overflow_error` if the number of bytes to be decoded is grater than the size of the return type
*
* \section ns_omw_bigEndian_section_encodeFn Encode Functions
*
* Writes the encoded value to `[buffer, buffer + sizeof(value)`.
*
* \b Exceptions
* - `std::invalid_argument` if the destination or end pointer is `NULL`
* - `std::out_of_range` if the destination can not hold the encoded data
*/

//! 
//! See \ref ns_omw_bigEndian_section_decodeFn.
//! 
int16_t omw::bigEndian::decode_i16(const uint8_t* data, size_t count)
{
    return ::bigEndian_decodes<int16_t>(data, count, "omw::bigEndian::decode_i16");
}

//! 
//! See \ref ns_omw_bigEndian_section_decodeFn.
//! 
uint16_t omw::bigEndian::decode_ui16(const uint8_t* data, size_t count)
{
    return ::bigEndian_decodeu<uint16_t>(data, count, "omw::bigEndian::decode_ui16");
}

//! 
//! See \ref ns_omw_bigEndian_section_decodeFn.
//! 
int32_t omw::bigEndian::decode_i32(const uint8_t* data, size_t count)
{
    return ::bigEndian_decodes<int32_t>(data, count, "omw::bigEndian::decode_i32");
}

//! 
//! See \ref ns_omw_bigEndian_section_decodeFn.
//! 
uint32_t omw::bigEndian::decode_ui32(const uint8_t* data, size_t count)
{
    return ::bigEndian_decodeu<uint32_t>(data, count, "omw::bigEndian::decode_ui32");
}

//! 
//! See \ref ns_omw_bigEndian_section_decodeFn.
//! 
int64_t omw::bigEndian::decode_i64(const uint8_t* data, size_t count)
{
    return ::bigEndian_decodes<int64_t>(data, count, "omw::bigEndian::decode_i64");
}

//! 
//! See \ref ns_omw_bigEndian_section_decodeFn.
//! 
uint64_t omw::bigEndian::decode_ui64(const uint8_t* data, size_t count)
{
    return ::bigEndian_decodeu<uint64_t>(data, count, "omw::bigEndian::decode_ui64");
}

//! 
//! See \ref ns_omw_bigEndian_section_decodeFn.
//! 
omw::int128_t omw::bigEndian::decode_i128(const uint8_t* data, size_t count)
{
    const char* const fnName = "omw::bigEndian::decode_i128";

    omw::int128_t r;

    if (data && count > 0)
    {
        if (data[0] & 0x80) r.sets(-1);
        else r.setu(0);

        if (count > 16) throw std::overflow_error(fnName);

        for (size_t i = 0; i < count; ++i)
        {
            r <<= 8;
            r |= omw::int128_t(0, data[i]);
        }
    }
    else throw std::invalid_argument(fnName);

    return r;
}

//! 
//! See \ref ns_omw_bigEndian_section_decodeFn.
//! 
omw::uint128_t omw::bigEndian::decode_ui128(const uint8_t* data, size_t count)
{
    const char* const fnName = "omw::bigEndian::decode_ui128";

    omw::uint128_t r;

    if (data && count > 0)
    {
        r.setu(0);

        if (count > 16) throw std::overflow_error(fnName);

        for (size_t i = 0; i < count; ++i)
        {
            r <<= 8;
            r |= omw::uint128_t(0, data[i]);
        }
    }
    else throw std::invalid_argument(fnName);

    return r;
}

//! 
//! See \ref ns_omw_bigEndian_section_encodeFn.
//! 
void omw::bigEndian::encode_16(uint8_t* buffer, const uint8_t* end, int16_t value)
{
    omw::bigEndian::encode_16(buffer, end, static_cast<uint16_t>(value));
}

//! 
//! See \ref ns_omw_bigEndian_section_encodeFn.
//! 
void omw::bigEndian::encode_16(uint8_t* buffer, const uint8_t* end, uint16_t value)
{
    if (buffer && end && (buffer <= end))
    {
        if ((end - buffer) >= 2)
        {
            buffer[0] = static_cast<uint8_t>((value >> 8) & 0xFF);
            buffer[1] = static_cast<uint8_t>(value & 0xFF);
        }
        else throw std::out_of_range("omw::bigEndian::encode_16");
    }
    else throw std::invalid_argument("omw::bigEndian::encode_16");
}

//! 
//! See \ref ns_omw_bigEndian_section_encodeFn.
//! 
void omw::bigEndian::encode_32(uint8_t* buffer, const uint8_t* end, int32_t value)
{
    omw::bigEndian::encode_32(buffer, end, static_cast<uint32_t>(value));
}

//! 
//! See \ref ns_omw_bigEndian_section_encodeFn.
//! 
void omw::bigEndian::encode_32(uint8_t* buffer, const uint8_t* end, uint32_t value)
{
    if (buffer && end && (buffer <= end))
    {
        if ((end - buffer) >= 4)
        {
            buffer[0] = static_cast<uint8_t>((value >> 24) & 0xFF);
            buffer[1] = static_cast<uint8_t>((value >> 16) & 0xFF);
            buffer[2] = static_cast<uint8_t>((value >> 8) & 0xFF);
            buffer[3] = static_cast<uint8_t>(value & 0xFF);
        }
        else throw std::out_of_range("omw::bigEndian::encode_32");
    }
    else throw std::invalid_argument("omw::bigEndian::encode_32");
}

//! 
//! See \ref ns_omw_bigEndian_section_encodeFn.
//! 
void omw::bigEndian::encode_64(uint8_t* buffer, const uint8_t* end, int64_t value)
{
    omw::bigEndian::encode_64(buffer, end, static_cast<uint64_t>(value));
}

//! 
//! See \ref ns_omw_bigEndian_section_encodeFn.
//! 
void omw::bigEndian::encode_64(uint8_t* buffer, const uint8_t* end, uint64_t value)
{
    if (buffer && end && (buffer <= end))
    {
        if ((end - buffer) >= 8)
        {
            buffer[0] = static_cast<uint8_t>((value >> 56) & 0xFF);
            buffer[1] = static_cast<uint8_t>((value >> 48) & 0xFF);
            buffer[2] = static_cast<uint8_t>((value >> 40) & 0xFF);
            buffer[3] = static_cast<uint8_t>((value >> 32) & 0xFF);
            buffer[4] = static_cast<uint8_t>((value >> 24) & 0xFF);
            buffer[5] = static_cast<uint8_t>((value >> 16) & 0xFF);
            buffer[6] = static_cast<uint8_t>((value >> 8) & 0xFF);
            buffer[7] = static_cast<uint8_t>(value & 0xFF);
        }
        else throw std::out_of_range("omw::bigEndian::encode_64");
    }
    else throw std::invalid_argument("omw::bigEndian::encode_64");
}

//! 
//! See \ref ns_omw_bigEndian_section_encodeFn.
//! 
void omw::bigEndian::encode_128(uint8_t* buffer, const uint8_t* end, const omw::Base_Int128& value)
{
    if (buffer && end && (buffer <= end))
    {
        if ((end - buffer) >= 16)
        {
            const uint64_t h = value.hi();
            const uint64_t l = value.lo();

            buffer[0] = static_cast<uint8_t>((h >> 56) & 0xFF);
            buffer[1] = static_cast<uint8_t>((h >> 48) & 0xFF);
            buffer[2] = static_cast<uint8_t>((h >> 40) & 0xFF);
            buffer[3] = static_cast<uint8_t>((h >> 32) & 0xFF);
            buffer[4] = static_cast<uint8_t>((h >> 24) & 0xFF);
            buffer[5] = static_cast<uint8_t>((h >> 16) & 0xFF);
            buffer[6] = static_cast<uint8_t>((h >> 8) & 0xFF);
            buffer[7] = static_cast<uint8_t>(h & 0xFF);

            buffer[8] = static_cast<uint8_t>((l >> 56) & 0xFF);
            buffer[9] = static_cast<uint8_t>((l >> 48) & 0xFF);
            buffer[10] = static_cast<uint8_t>((l >> 40) & 0xFF);
            buffer[11] = static_cast<uint8_t>((l >> 32) & 0xFF);
            buffer[12] = static_cast<uint8_t>((l >> 24) & 0xFF);
            buffer[13] = static_cast<uint8_t>((l >> 16) & 0xFF);
            buffer[14] = static_cast<uint8_t>((l >> 8) & 0xFF);
            buffer[15] = static_cast<uint8_t>(l & 0xFF);
        }
        else throw std::out_of_range("omw::bigEndian::encode_128");
    }
    else throw std::invalid_argument("omw::bigEndian::encode_128");
}



/*!
* \namespace omw::url
*
* Replaces the reserved characters with the percent escaped hex format.
*/

omw::string omw::url::encode(const std::string& str)
{
    omw::string r = str;

    constexpr size_t count = 61;
    const char search[count] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 38, 39, 40, 41, 42, 43, 44, 47, 58, 59, 60, 61, 62, 63, 64, 91, 92, 93, 94, 96, 123, 124, 125, 127 };
    const omw::string replace[count] = { "%00", "%01", "%02", "%03", "%04", "%05", "%06", "%07", "%08", "%09", "%0A", "%0B", "%0C", "%0D", "%0E", "%0F", "%10", "%11", "%12", "%13", "%14", "%15", "%16", "%17", "%18", "%19", "%1A", "%1B", "%1C", "%1D", "%1E", "%1F", "%20", "%21", "%22", "%23", "%24", "%26", "%27", "%28", "%29", "%2A", "%2B", "%2C", "%2F", "%3A", "%3B", "%3C", "%3D", "%3E", "%3F", "%40", "%5B", "%5C", "%5D", "%5E", "%60", "%7B", "%7C", "%7D", "%7F" };

    r.replaceAll("%", "%25", 0, nullptr);
    for (size_t i = 0; i < count; ++i) r.replaceAll(omw::StringReplacePair(search[i], replace[i]), 0, nullptr);

    return r;
}
