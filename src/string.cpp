/*
author          Oliver Blaser
copyright       MIT - Copyright (c) 2023 Oliver Blaser
*/

#include <cctype>
#include <stdexcept>
#include <string>
#include <vector>

#include "omw/algorithm.h"
#include "omw/defs.h"
#include "omw/intdef.h"
#include "omw/string.h"



namespace {

template <typename T1, typename T2> std::string pair_to_string(const std::pair<T1, T2>& value, char delimiter)
{
    return (omw::toString(value.first) + delimiter + omw::toString(value.second));
}

// T has to be an integer type
template <typename T> T hexstointeger(const std::string& str, const std::string& fnName)
{
    const std::string exMsg_notHex(OMWi_DISPSTR(fnName + ": not a hex string"));
    const std::string hexDigits(omw::hexStrDigitsLower);

    const std::string hexStr = omw::toLower_ascii(str);
    const std::string::size_type hexStrLen = hexStr.length();
    const std::string::size_type maxLen = 2 * sizeof(T);

    T r = 0;

    if ((hexStrLen <= maxLen) && (hexStrLen > 0))
    {
        for (std::string::size_type i = 0; i < hexStrLen; ++i)
        {
            const std::string::size_type digitIdx = hexDigits.find(hexStr[hexStrLen - i - 1]);

            if (digitIdx == std::string::npos) throw std::invalid_argument(exMsg_notHex);

            T digitValue = (T)digitIdx;
            digitValue <<= (4 * (T)i);
            r |= digitValue;
        }
    }
    else
    {
        if (!omw::isHex(hexStr)) throw std::invalid_argument(exMsg_notHex);
        throw std::out_of_range(fnName);
    }

    return r;
}

omw::Base_Int128 hexstointeger128(const std::string& str, const std::string& fnName)
{
    const std::string exMsg_notHex(OMWi_DISPSTR(fnName + ": not a hex string"));

    const std::string& hexStr = str;
    const std::string::size_type hexStrLen = hexStr.length();
    const std::string::size_type maxLen = 32;

    omw::Base_Int128 r = 0;

    if ((hexStrLen <= maxLen) && (hexStrLen > 0))
    {
        if (hexStrLen <= 16)
        {
            const uint64_t hi = 0;
            const uint64_t lo = ::hexstointeger<uint64_t>(hexStr, fnName);
            r = omw::Base_Int128(hi, lo);
        }
        else
        {
            const std::string hiStr = hexStr.substr(0, hexStrLen - 16);
            const std::string loStr = hexStr.substr(hexStrLen - 16);
            const uint64_t hi = ::hexstointeger<uint64_t>(hiStr, fnName);
            const uint64_t lo = ::hexstointeger<uint64_t>(loStr, fnName);
            r = omw::Base_Int128(hi, lo);
        }
    }
    else
    {
        if (!omw::isHex(hexStr)) throw std::invalid_argument(exMsg_notHex);
        throw std::out_of_range(fnName);
    }

    return r;
}

//// out_t and in_t have to be std::vector<omw::string> and std::vector<std::string> or vice versa.
// template <class out_t, class in_t>
// out_t convertStringVector(const in_t& stringVector)
//{
//     out_t r;
//     r.reserve((out_t::size_type)stringVector.size());
//
//     for (in_t::size_type i = 0; i < stringVector.size(); ++i)
//     {
//         r.push_back(out_t::value_type(stringVector[i].c_str()));
//     }
//
//     return r;
// }

//// out_t has to be std::vector<omw::string> or std::vector<std::string>
// template <class out_t>
// out_t stringVector(const char* const* strings, size_t count)
//{
//     out_t r;
//     r.reserve(count);
//
//     for (size_t i = 0; i < count; ++i)
//     {
//         r.push_back(out_t::value_type(strings[i]));
//     }
//
//     return r;
// }

} // namespace



omw::StringVector omw::stringVector(const char* const * strings, omw::StringVector::size_type count)
{
    omw::StringVector r;
    r.reserve(count);
    for (omw::StringVector::size_type i = 0; i < count; ++i) { r.push_back(omw::StringVector::value_type(strings[i])); }
    return r;
}

omw::StringVector omw::stringVector(const std::string* strings, omw::StringVector::size_type count) { return omw::StringVector(strings, strings + count); }



/*!
 * \class omw::StringReplacePair
 *
 * Container that holds information for search and replace methods.
 *
 * Used by `omw::replaceFirst()` and `omw::replaceAll()`.
 */



std::string& omw::reverse(std::string& str)
{
    const std::string::size_type n = str.size();
    const std::string::size_type i_end = (n / 2);

    for (std::string::size_type i = 0; i < i_end; ++i)
    {
        const std::string::value_type tmp = str.at(i);
        str.at(i) = str.at(n - 1 - i);
        str.at(n - 1 - i) = tmp;
    }

    return str;
}

std::string omw::toReversed(const std::string& str)
{
    std::string res(str.length(), '\0');

    for (std::string::size_type i = 0; i < str.length(); ++i) { res[i] = str[str.length() - 1 - i]; }

    return res;
}



std::string& omw::lower_ascii(std::string& str)
{
    for (std::string::size_type i = 0; i < str.length(); ++i)
    {
        auto& c = str.at(i);

        if ((c >= 'A') && (c <= 'Z')) { c += 32; }
    }

    return str;
}

std::string& omw::lower_asciiExt(std::string& str)
{
    omw::lower_ascii(str);

    const omw::StringReplacePair rp[] = { omw::StringReplacePair(omw::UTF8CP_Auml, omw::UTF8CP_auml),
                                          omw::StringReplacePair(omw::UTF8CP_Ouml, omw::UTF8CP_ouml),
                                          omw::StringReplacePair(omw::UTF8CP_Uuml, omw::UTF8CP_uuml) };

    return omw::replaceAll(str, rp, (sizeof(rp) / sizeof(rp[0])));
}

std::string& omw::upper_ascii(std::string& str)
{
    for (std::string::size_type i = 0; i < str.length(); ++i)
    {
        auto& c = str.at(i);

        if ((c >= 'a') && (c <= 'z')) c -= 32;
    }

    return str;
}

std::string& omw::upper_asciiExt(std::string& str)
{
    omw::upper_ascii(str);

    const omw::StringReplacePair rp[] = { omw::StringReplacePair(omw::UTF8CP_auml, omw::UTF8CP_Auml),
                                          omw::StringReplacePair(omw::UTF8CP_ouml, omw::UTF8CP_Ouml),
                                          omw::StringReplacePair(omw::UTF8CP_uuml, omw::UTF8CP_Uuml) };

    return omw::replaceAll(str, rp, (sizeof(rp) / sizeof(rp[0])));
}

std::string omw::toLower_ascii(const std::string& str)
{
    std::string res = str;
    return omw::lower_ascii(res);
}

std::string omw::toLower_asciiExt(const std::string& str)
{
    std::string res = str;
    return omw::lower_asciiExt(res);
}

std::string omw::toUpper_ascii(const std::string& str)
{
    std::string res = str;
    return omw::upper_ascii(res);
}

std::string omw::toUpper_asciiExt(const std::string& str)
{
    std::string res = str;
    return omw::upper_asciiExt(res);
}



//! @param [in,out] str
//! @param search Substring to be replaced
//! @param replace String for replacement
//! @param startPos From where to start searching
//! @return The parameter `str`
std::string& omw::replaceFirst(std::string& str, const std::string& search, const std::string& replace, std::string::size_type startPos)
{
    std::string::size_type pos = str.find(search, startPos);
    if ((pos < str.length()) && (pos != std::string::npos)) str.replace(pos, search.length(), replace);
    return str;
}

//! @param [in,out] str
//! @param search Character to be replaced
//! @param replace Character for replacement
//! @param startPos From where to start searching
//! @param [out] nReplacements Number of occurrences
//! @return The parameter `str`
std::string& omw::replaceAll(std::string& str, char search, char replace, std::string::size_type startPos, size_t* nReplacements)
{
    size_t cnt = 0;

    for (size_t i = startPos; i < str.length(); ++i)
    {
        if (str.at(i) == search)
        {
            str.at(i) = replace;
            ++cnt;
        }
    }

    if (nReplacements) *nReplacements = cnt;

    return str;
}

//! @param [in,out] str
//! @param search Character to be replaced
//! @param replace String for replacement
//! @param startPos From where to start searching
//! @param [out] nReplacements Number of occurrences
//! @return The parameter `str`
std::string& omw::replaceAll(std::string& str, char search, const std::string& replace, std::string::size_type startPos, size_t* nReplacements)
{
    return omw::replaceAll(str, omw::StringReplacePair(search, replace), startPos, nReplacements);
}

//! @param [in,out] str
//! @param search Substring to be replaced
//! @param replace Character for replacement
//! @param startPos From where to start searching
//! @param [out] nReplacements Number of occurrences
//! @return The parameter `str`
std::string& omw::replaceAll(std::string& str, const std::string& search, char replace, std::string::size_type startPos, size_t* nReplacements)
{
    return omw::replaceAll(str, omw::StringReplacePair(search, replace), startPos, nReplacements);
}

//! @param [in,out] str
//! @param search Substring to be replaced
//! @param replace String for replacement
//! @param startPos From where to start searching
//! @param [out] nReplacements Number of occurrences
//! @return The parameter `str`
std::string& omw::replaceAll(std::string& str, const std::string& search, const std::string& replace, std::string::size_type startPos, size_t* nReplacements)
{
    size_t cnt = 0;

    if (search.length() > 0)
    {
        std::string::size_type pos = str.find(search, startPos);
        while ((pos < str.length()) && (pos != std::string::npos))
        {
            str.replace(pos, search.length(), replace);
            ++cnt;
            pos = str.find(search, pos + replace.length());
        }
    }
    else cnt = OMW_SIZE_MAX;

    if (nReplacements) *nReplacements = cnt;

    return str;
}

//! @param [in,out] str
//! @param pair Search and replace string pair
//! @param startPos From where to start searching
//! @param [out] nReplacements Number of occurrences
//! @return The parameter `str`
std::string& omw::replaceAll(std::string& str, const omw::StringReplacePair& pair, std::string::size_type startPos, size_t* nReplacements)
{
    return omw::replaceAll(str, pair.search(), pair.replace(), startPos, nReplacements);
}

//! @param [in,out] str
//! @param pairs Search and replace string pair vector
//! @param startPos From where to start searching
//! @param [out] nReplacementsTotal Total number of occurrences
//! @param [out] nReplacements Number of occurrences of specific replace pair
//! @return The parameter `str`
std::string& omw::replaceAll(std::string& str, const std::vector<omw::StringReplacePair>& pairs, std::string::size_type startPos, size_t* nReplacementsTotal,
                             std::vector<size_t>* nReplacements)
{
    bool allInvalid = true;
    size_t cnt = 0;
    size_t tmpCnt;

    if (nReplacements) *nReplacements = std::vector<size_t>(pairs.size(), OMW_SIZE_MAX);

    for (size_t i = 0; i < pairs.size(); ++i)
    {
        omw::replaceAll(str, pairs[i], startPos, &tmpCnt);
        if (nReplacements) nReplacements->at(i) = tmpCnt;
        if (tmpCnt != OMW_SIZE_MAX)
        {
            cnt += tmpCnt;
            allInvalid = false;
        }
    }

    if (allInvalid) cnt = OMW_SIZE_MAX;

    if (nReplacementsTotal) *nReplacementsTotal = cnt;

    return str;
}

//! @param [in,out] str
//! @param pairs Pointer to a replace pair array
//! @param count
//! @param startPos From where to start searching
//! @param [out] nReplacementsTotal Total number of occurrences
//! @param [out] nReplacements Number of occurrences of specific replace pair
//! @return The parameter `str`
std::string& omw::replaceAll(std::string& str, const omw::StringReplacePair* pairs, size_t count, std::string::size_type startPos, size_t* nReplacementsTotal,
                             std::vector<size_t>* nReplacements)
{
    return omw::replaceAll(str, std::vector<omw::StringReplacePair>(pairs, pairs + count), startPos, nReplacementsTotal, nReplacements);
}



std::string omw::toString(bool value, bool asText)
{
    if (asText) { return (value ? "true" : "false"); }

    return (value ? "1" : "0");
}

std::string omw::toString(const omw::int128_t& value)
{
    const omw::uint128_t tmp(value);
    return (value.isNegative() ? "-" + omw::toString(-tmp) : omw::toString(tmp));
}

std::string omw::toString(const omw::uint128_t& value)
{
    const std::string str = omw::toHexStr(omw::doubleDabble(value), 0);
    size_t startPos = 0;

    while ((str[startPos] == '0') && (startPos < (str.length() - 1))) { ++startPos; }

    return std::string(str, startPos);
}

std::string omw::toString(const std::pair<int32_t, int32_t>& value, char delimiter) { return ::pair_to_string(value, delimiter); }
std::string omw::toString(const std::pair<uint32_t, uint32_t>& value, char delimiter) { return ::pair_to_string(value, delimiter); }
std::string omw::toString(const std::pair<int64_t, int64_t>& value, char delimiter) { return ::pair_to_string(value, delimiter); }
std::string omw::toString(const std::pair<uint64_t, uint64_t>& value, char delimiter) { return ::pair_to_string(value, delimiter); }
std::string omw::toString(const std::pair<float, float>& value, char delimiter) { return ::pair_to_string(value, delimiter); }
std::string omw::toString(const std::pair<double, double>& value, char delimiter) { return ::pair_to_string(value, delimiter); }
std::string omw::toString(const std::pair<long double, long double>& value, char delimiter) { return ::pair_to_string(value, delimiter); }



//! @param str Boolean string representation
//! @return The string converted to `bool`
//!
//! \b true and \b 1 converts to `true`, \b false and \b 0 to `false`. The case of the characters is ignored.
//!
//! \b Exceptions
//! - `std::out_of_range` if the value isn't an element of `{ "0", "1", "true", "false" }`
//! - <tt><a href="https://en.cppreference.com/w/cpp/string/basic_string/stol" target="_blank">std::stoi()</a></tt> is called and may throw `std::out_of_range`
//! or `std::invalid_argument`
//!
bool omw::stob(const std::string& str)
{
    const std::string lowerStr = omw::toLower_ascii(str);
    if (lowerStr == "true") { return true; }
    if (lowerStr == "false") { return false; }

    const int boolInt = std::stoi(str);
    if (boolInt == 1) { return true; }
    if (boolInt == 0) { return false; }

    throw std::out_of_range("omw::stob");
}

//! @param str The string to convert
//! @param pos Address of an integer to store the number of characters processed
//! @param base The number base
//! @return The string converted to `size_t`
//!
//! Does not apply unsigned integer wraparound rules. Negative numbers throw an out of range exception.
//!
size_t omw::stoz(const std::string& str, size_t* pos, int base)
{
    size_t r;

    // #if (SIZE_MAX == UINT32_MAX) // (OMW_PBITW == 32u)
    //     using ull_t = unsigned long long;
    //     const ull_t value = std::stoull(str, pos, base);
    //     constexpr ull_t size_max = SIZE_MAX;
    //     if (value > size_max) throw std::out_of_range("omw::stoz");
    //     r = (size_t)value;
    // #elif (SIZE_MAX == UINT64_MAX) // (OMW_PBITW == 64u)
    //     r = std::stoull(str, pos, base);
    // #else

    if (sizeof(size_t) == sizeof(unsigned long))
    {
#if !OMW_CXX_MSVC
#pragma GCC diagnostic ignored "-Wuseless-cast"
#endif
        r = (size_t)std::stoul(str, pos, base);
    }
    else if (sizeof(size_t) == sizeof(unsigned long long))
    {
#if !OMW_CXX_MSVC
#pragma GCC diagnostic ignored "-Wuseless-cast"
#endif
        r = (size_t)std::stoull(str, pos, base);
    }

    static_assert(((sizeof(size_t) == sizeof(unsigned long)) || (sizeof(size_t) == sizeof(unsigned long long))), "weired platform!?");
    // else // some weired platform
    //{
    //     using ull_t = unsigned long long;
    //     const ull_t value = std::stoull(str, pos, base);
    //     constexpr ull_t size_max = SIZE_MAX;
    //     if (value > size_max) throw std::out_of_range("omw::stoz");
    //     r = (size_t)value;
    // }

    const char* p = str.c_str();
    while (std::isspace(*p)) { ++p; }
    if (*p == '-') { throw std::out_of_range("omw::stoz"); }

    // #endif

    return r;
}

//! @param str Pair string representation
//! @param delimiter Character between the two values
//! @return <tt><a href="https://en.cppreference.com/w/cpp/utility/pair" target="_blank">std::pair</a></tt> with the two values
//!
//! \b Exceptions
//! - `std::invalid_argument` if the separator character was not found or it is at the first or at the last position in the string
//! - <tt><a href="https://en.cppreference.com/w/cpp/string/basic_string/stol" target="_blank">std::stoi()</a></tt> is called and may throw `std::out_of_range`
//! or `std::invalid_argument`
//!
std::pair<int32_t, int32_t> omw::stoipair(const std::string& str, char delimiter)
{
    const std::string fnName = "omw::stoipair";

    std::string::size_type sp = str.find(delimiter);

    if ((sp == 0) || (sp >= (str.length() - 1)) || (sp == std::string::npos))
    {
        throw std::invalid_argument(OMWi_DISPSTR(fnName + ": invalid separator char pos"));
    }

    const std::string first = str.substr(0, sp);
    const std::string second = str.substr(sp + 1);

    if (!isInteger(first)) { throw std::invalid_argument(OMWi_DISPSTR(fnName + ": first is not an integer")); }
    if (!isInteger(second)) { throw std::invalid_argument(OMWi_DISPSTR(fnName + ": second is not an integer")); }

    return std::pair<int32_t, int32_t>(std::stoi(first), std::stoi(second));
}

std::pair<double, double> omw::stodpair(const std::string& str, char delimiter)
{
    const std::string fnName = "omw::stodpair";

    std::string::size_type sp = str.find(delimiter);

    if ((sp == 0) || (sp >= (str.length() - 1)) || (sp == std::string::npos))
    {
        throw std::invalid_argument(OMWi_DISPSTR(fnName + ": invalid separator char pos"));
    }

    const std::string first = str.substr(0, sp);
    const std::string second = str.substr(sp + 1);

    if (!isFloat(first)) { throw std::invalid_argument(OMWi_DISPSTR(fnName + ": first is not a double")); }
    if (!isFloat(second)) { throw std::invalid_argument(OMWi_DISPSTR(fnName + ": second is not a double")); }

    return std::pair<double, double>(std::stod(first), std::stod(second));
}

// omw::int128_t omw::stoi128(const std::string& str)
//{
//     reversed double dabble needed, wich is not implemented yet
// }
//
// omw::uint128_t omw::stoui128(const std::string& str)
//{
//     reversed double dabble needed, wich is not implemented yet
// }



std::string omw::toHexStr(int8_t value) { return omw::toHexStr((uint8_t)value); }
std::string omw::toHexStr(uint8_t value)
{
    const char r[] = { omw::hexStrDigits[(value >> 4) & 0x0F], omw::hexStrDigits[value & 0x0F], 0 };
    return r;
}
std::string omw::toHexStr(int16_t value) { return toHexStr((uint16_t)value); }
std::string omw::toHexStr(uint16_t value) { return toHexStr((uint8_t)(value >> 8)) + toHexStr((uint8_t)value); }
std::string omw::toHexStr(int32_t value) { return toHexStr((uint32_t)value); }
std::string omw::toHexStr(uint32_t value)
{
    return toHexStr((uint8_t)(value >> 24)) + toHexStr((uint8_t)(value >> 16)) + toHexStr((uint8_t)(value >> 8)) + toHexStr((uint8_t)value);
}
std::string omw::toHexStr(int64_t value) { return toHexStr((uint64_t)value); }
std::string omw::toHexStr(uint64_t value)
{
    return toHexStr((uint8_t)(value >> 56)) + toHexStr((uint8_t)(value >> 48)) + toHexStr((uint8_t)(value >> 40)) + toHexStr((uint8_t)(value >> 32)) +
           toHexStr((uint8_t)(value >> 24)) + toHexStr((uint8_t)(value >> 16)) + toHexStr((uint8_t)(value >> 8)) + toHexStr((uint8_t)value);
}
std::string omw::toHexStr(const omw::Base_Int128& value) { return omw::toHexStr(value.hi()) + omw::toHexStr(value.lo()); }
std::string omw::toHexStr(int16_t value, char delimiter) { return toHexStr((uint16_t)value, delimiter); }
std::string omw::toHexStr(uint16_t value, char delimiter) { return toHexStr((uint8_t)(value >> 8)) + delimiter + toHexStr((uint8_t)value); }
std::string omw::toHexStr(int32_t value, char delimiter) { return toHexStr((uint32_t)value, delimiter); }
std::string omw::toHexStr(uint32_t value, char delimiter)
{
    return toHexStr((uint8_t)(value >> 24)) + delimiter + toHexStr((uint8_t)(value >> 16)) + delimiter + toHexStr((uint8_t)(value >> 8)) + delimiter +
           toHexStr((uint8_t)value);
}
std::string omw::toHexStr(int64_t value, char delimiter) { return toHexStr((uint64_t)value, delimiter); }
std::string omw::toHexStr(uint64_t value, char delimiter)
{
    return toHexStr((uint8_t)(value >> 56)) + delimiter + toHexStr((uint8_t)(value >> 48)) + delimiter + toHexStr((uint8_t)(value >> 40)) + delimiter +
           toHexStr((uint8_t)(value >> 32)) + delimiter + toHexStr((uint8_t)(value >> 24)) + delimiter + toHexStr((uint8_t)(value >> 16)) + delimiter +
           toHexStr((uint8_t)(value >> 8)) + delimiter + toHexStr((uint8_t)value);
}
std::string omw::toHexStr(const omw::Base_Int128& value, char delimiter)
{
    return omw::toHexStr(value.hi(), delimiter) + delimiter + omw::toHexStr(value.lo(), delimiter);
}
std::string omw::toHexStr(const std::vector<char>& data, char delimiter) { return toHexStr(data.data(), data.size(), delimiter); }
std::string omw::toHexStr(const std::vector<uint8_t>& data, char delimiter) { return toHexStr(data.data(), data.size(), delimiter); }
std::string omw::toHexStr(const char* data, size_t count, char delimiter) { return toHexStr((const uint8_t*)data, count, delimiter); }
std::string omw::toHexStr(const uint8_t* data, size_t count, char delimiter)
{
    std::string str;

    for (size_t i = 0; i < count; ++i)
    {
        if ((i > 0) && (delimiter != 0)) str += delimiter;

        str += toHexStr(data[i]);
    }

    return str;
}

//! @param str Hexadecimal string representation
//! @return The corresponding value
//!
//! \b Exceptions
//! - `std::invalid_argument` if the string contains invalid characters
//! - `std::out_of_range` if the value would fall out of range
//!
int32_t omw::hexstoi(const std::string& str) { return hexstointeger<int32_t>(str, "omw::hexstoi"); }

//! @param str Hexadecimal string representation
//! @return The corresponding value
//!
//! \b Exceptions
//! - `std::invalid_argument` if the string contains invalid characters
//! - `std::out_of_range` if the value would fall out of range
//!
int64_t omw::hexstoi64(const std::string& str) { return hexstointeger<int64_t>(str, "omw::hexstoi64"); }

//! @param str Hexadecimal string representation
//! @return The corresponding value
//!
//! \b Exceptions
//! - `std::invalid_argument` if the string contains invalid characters
//! - `std::out_of_range` if the value would fall out of range
//!
omw::int128_t omw::hexstoi128(const std::string& str) { return hexstointeger128(str, "omw::hexstoi128"); }

//! @param str Hexadecimal string representation
//! @return The corresponding value
//!
//! \b Exceptions
//! - `std::invalid_argument` if the string contains invalid characters
//! - `std::out_of_range` if the value would fall out of range
//!
uint32_t omw::hexstoui(const std::string& str) { return hexstointeger<uint32_t>(str, "omw::hexstoui"); }

//! @param str Hexadecimal string representation
//! @return The corresponding value
//!
//! \b Exceptions
//! - `std::invalid_argument` if the string contains invalid characters
//! - `std::out_of_range` if the value would fall out of range
//!
uint64_t omw::hexstoui64(const std::string& str) { return hexstointeger<uint64_t>(str, "omw::hexstoui64"); }

//! @param str Hexadecimal string representation
//! @return The corresponding value
//!
//! \b Exceptions
//! - `std::invalid_argument` if the string contains invalid characters
//! - `std::out_of_range` if the value would fall out of range
//!
omw::uint128_t omw::hexstoui128(const std::string& str) { return hexstointeger128(str, "omw::hexstoui128"); }

// to be added to doc: delimiter = 0
// calls `omw::sepHexStr()`
//
// if string is empty an empty vector is returned
//
std::vector<uint8_t> omw::hexstovector(const std::string& str, char delimiter)
{
    std::vector<uint8_t> r(0);

    if (str.length() > 0)
    {
        const std::string fnName = "omw::hexstovector";

        std::string tmpStr;

        if (delimiter == 0)
        {
            delimiter = toHexStr_defaultDelimiter;
            tmpStr = omw::sepHexStr(str, toHexStr_defaultDelimiter);
        }
        else tmpStr = str;

        const std::vector<std::string> hexStrings = omw::split(tmpStr, delimiter);

        r.resize(hexStrings.size(), 0);
        for (size_t i = 0; i < hexStrings.size(); ++i)
        {
            uint32_t value = omw::hexstoui(hexStrings[i]);
            if (value > 0xFF) throw std::out_of_range(fnName);
            r[i] = (uint8_t)value;
        }
    }

    return r;
}

//!
//! Same as `omw::sepHexStr(const std::string&, char)` with `omw::toHexStr_defaultdelimiter`.
//!
std::string omw::sepHexStr(const std::string& str) { return omw::sepHexStr(str, omw::toHexStr_defaultDelimiter); }

//!
//! Separates a concatonated hex string by adding a delimiter between the bytes.
//!
//! Prepends a `0` if length is odd.
//!
//! Example:
//! ```
//! delimiter = '-'
//! 1223344 => 01-22-33-44
//! ```
//!
std::string omw::sepHexStr(const std::string& str, char delimiter)
{
    std::string tmp(str);
    if (tmp.length() & 0x01) { tmp = '0' + tmp; }
    return omw::join(omw::splitLen(tmp, 2), delimiter);
}

//!
//! Removes all `rmChar` from the string and returns `omw::sepHexStr(const std::string&, char)`.
//!
std::string omw::sepHexStr(const std::string& str, char rmChar, char delimiter)
{
    std::string hexstr = str;
    omw::replaceAll(hexstr, omw::StringReplacePair(rmChar, ""));
    return omw::sepHexStr(hexstr, delimiter);
}

//!
//! Removes all characters pointed to by `rmChars` from the string and returns `omw::sepHexStr(const std::string&, char)`.
//!
std::string omw::sepHexStr(const std::string& str, const char* rmChars, size_t count, char delimiter)
{
    std::vector<omw::StringReplacePair> replPairs;
    replPairs.reserve(count);

    for (size_t i = 0; i < count; ++i) { replPairs.push_back(omw::StringReplacePair(rmChars[i], "")); }

    std::string hexstr = str;
    omw::replaceAll(hexstr, replPairs);

    return omw::sepHexStr(hexstr, delimiter);
}

//!
//! Removes all characters in `rmChars` from the string and returns `omw::sepHexStr(const std::string&, char)`.
//!
std::string omw::sepHexStr(const std::string& str, const std::vector<char>& rmChars, char delimiter)
{
    return omw::sepHexStr(str, rmChars.data(), rmChars.size(), delimiter);
}

// ready, but not tested:
//
// omw::string omw::sepHexStr(const std::string& str, const std::vector<char>& rmChars, char delimiter)
//{
//    return omw::sepHexStr(str, rmChars.data(), rmChars.size(), delimiter);
//}
//
// omw::string omw::sepHexStr(const std::string& str, const char* rmString, char delimiter)
//{
//    omw::string hexstr = str;
//    hexstr.replaceAll(rmString, "");
//
//    return ::separateHexStr(hexstr, delimiter);
//}
//
// omw::string omw::sepHexStr(const std::string& str, const std::string& rmString, char delimiter)
//{
//    return omw::sepHexStr(str, rmString.c_str(), delimiter);
//}
//
// omw::string omw::sepHexStr(const std::string& str, const std::string* rmStrings, size_t count, char delimiter)
//{
//    std::vector<omw::StringReplacePair> replPairs;
//    replPairs.reserve(count);
//
//    for (size_t i = 0; i < count; ++i)
//    {
//        replPairs.push_back(omw::StringReplacePair(rmStrings[i], ""));
//    }
//
//    omw::string hexstr = str;
//    hexstr.replaceAll(replPairs);
//
//    return ::separateHexStr(hexstr, delimiter);
//}
//
// omw::string omw::sepHexStr(const std::string& str, const omw::stringVector_t& rmStrings, char delimiter)
//{
//    return omw::sepHexStr(str, rmStrings.data(), rmStrings.size(), delimiter);
//}

std::string omw::rmNonHex(const std::string& str)
{
    std::string r = str;
    omw::rmNonHex(r);
    return r;
}

void omw::rmNonHex(char* str)
{
    if (str)
    {
        std::string tmpStr = str;
        omw::rmNonHex(tmpStr);
        std::copy(tmpStr.c_str(), tmpStr.c_str() + tmpStr.size() + 1, str);
    }
}

void omw::rmNonHex(std::string& str)
{
    for (std::string::size_type i = 0; i < str.length();)
    {
        if (omw::isHex(str[i])) ++i;
        else str.erase(i, 1);
    }
}



omw::StringVector omw::split(const std::string& str, char delimiter, omw::StringVector::size_type maxTokenCount)
{
    omw::StringVector r(0);

    if (maxTokenCount > 0)
    {
        const omw::StringVector::size_type n = maxTokenCount - 1;
        std::string::size_type pos = 0;

        while (pos < std::string::npos)
        {
            if (r.size() < n)
            {
                const std::string::size_type end = str.find(delimiter, pos);
                r.push_back(str.substr(pos, end - pos));
                pos = end;
                if (pos < std::string::npos) ++pos;
            }
            else
            {
                r.push_back(str.substr(pos));
                pos = std::string::npos;
            }
        }
    }

    return r;
}

omw::StringVector omw::splitLen(const std::string& str, std::string::size_type tokenLength, omw::StringVector::size_type maxTokenCount)
{
    omw::StringVector r(0);

    if (maxTokenCount > 0)
    {
        const std::string::size_type len = str.length();
        std::string::size_type pos = 0;

        for (omw::StringVector::size_type iToken = 0; (iToken < maxTokenCount) && (pos < len); ++iToken)
        {
            r.push_back(str.substr(pos, tokenLength));
            pos += tokenLength;
        }

        if (pos < len) { r.back() += str.substr(pos); }
    }

    return r;
}

std::string omw::join(const omw::StringVector& strings)
{
    std::string r = "";

    for (omw::StringVector::size_type i = 0; i < strings.size(); ++i) { r += strings[i]; }

    return r;
}

std::string omw::join(const omw::StringVector& strings, char delimiter)
{
    std::string r = "";

    for (omw::StringVector::size_type i = 0; i < strings.size(); ++i)
    {
        if (i > 0) r += std::string(1, delimiter);
        r += strings[i];
    }

    return r;
}



//!
//! See `omw::isUInteger()`.
//!
bool omw::isInteger(const std::string& str)
{
    std::string::size_type startPos = 0;

    if (str.length() > 1)
    {
        if (str[0] == '-') startPos = 1;
    }

    return omw::isUInteger(std::string(str, startPos));
}

//!
//! Ignores leading zeros.
//!
//! An empty string returns `false`.
//!
bool omw::isUInteger(const std::string& str)
{
    bool r;

    if (str.length() > 0)
    {
        r = true;
        for (std::string::size_type i = 0; (i < str.length()) && r; ++i)
        {
            if ((str[i] < '0') || (str[i] > '9')) r = false;
        }
    }
    else r = false;

    return r;
}

//!
//! Exponential format is not yet supported.
//!
//! An empty string returns `false`.
//!
bool omw::isFloat(const std::string& str, char decimalPoint)
{
    bool r;

    if (str.length() > 0)
    {
        std::string::size_type startPos = 0;
        if (str[0] == '-') startPos = 1;

        unsigned cntDp = 0;
        r = (str.length() > startPos);

        for (std::string::size_type i = startPos; i < str.length(); ++i)
        {
            const char& c = str[i];

            if (((c < '0') || (c > '9')) && (c != decimalPoint))
            {
                r = false;
                break;
            }

            if (c == decimalPoint)
            {
                if (cntDp >= 1)
                {
                    r = false;
                    break;
                }

                ++cntDp;
            }
        }
    }
    else r = false;

    return r;
}

//!
//! An empty string returns `false`.
//!
bool omw::isHex(const std::string& str, std::string::size_type pos, std::string::size_type count)
{
    bool r = false;

    if ((pos < str.length()) && (count > 0))
    {
        r = true;
        for (std::string::size_type i = 0; (i < count) && ((pos + i) < str.length()); ++i)
        {
            const char& c = str[pos + i];

            if (!( // clang-format off
                ((c >= '0') && (c <= '9')) ||
                ((c >= 'A') && (c <= 'F')) ||
                ((c >= 'a') && (c <= 'f'))
                )) // clang-format on
            {
                r = false;
                break;
            }
        }
    }

    return r;
}



//! @param p Pointer to the position in the string
//! @return Number of new line characters at <tt>p</tt>, range: [0, 2]
//!
//! If \b p is `NULL`, 0 is returned.
//!
//! It's recommended to use `omw::peekNewLine(const char*, const char*)` to prevent access violations.
//!
size_t omw::peekNewLine(const char* p)
{
    size_t r;

    if (p)
    {
        if (*p == 0x0A) r = 1;                              // LF
        else if ((*p == 0x0D) && (*(p + 1) != 0x0A)) r = 1; // CR
        else if ((*p == 0x0D) && (*(p + 1) == 0x0A)) r = 2; // CR+LF
        else r = 0;
    }
    else r = 0;

    return r;
}

//! @param p Pointer to the position in the string
//! @param end Pointer to the first element after the last element of the string
//! @return Number of new line characters at <tt>p</tt>, range: [0, 2]
//!
//! If <b>end</b> is <tt>NULL</tt>, <tt>omw::peekNewLine(const char*)</tt> will be used, hence access violations may occure.
//!
//! If \b p is `NULL` or \b p is greater than or equal to \b end, 0 is returned.
//!
size_t omw::peekNewLine(const char* p, const char* end)
{
    size_t r;

    if (end)
    {
        if (p && ((end - p) > 0))
        {
            if (*p == 0x0A) r = 1; // LF
            else if (*p == 0x0D)
            {
                if ((end - p) > 1)
                {
                    if (*(p + 1) == 0x0A) r = 2; // CR+LF
                    else r = 1;                  // CR
                }
                else r = 1; // CR
            }
            else r = 0;
        }
        else r = 0;
    }
    else r = peekNewLine(p);

    return r;
}



//!
//! Reads the data to construct a string from a byte buffer.
//!
//! \b Exceptions
//! - `std::invalid_argument` if the data pointer is _null_
//!
std::string omw::readString(const uint8_t* data, size_t count)
{
    std::string str(count, '#');

    if (data)
    {
        for (size_t i = 0; i < count; ++i) str[i] = static_cast<char>(data[i]);
    }
    else throw std::invalid_argument("omw::readString");

    return str;
}

//!
//! Reads the data to construct a string from a byte buffer.
//!
//! \b Exceptions
//! - `std::invalid_argument` if count is greater than `data.size() - pos` or if `pos` is greater than `data.size()`
//!
std::string omw::readString(const std::vector<uint8_t>& data, std::vector<uint8_t>::size_type pos, std::vector<uint8_t>::size_type count)
{
    if (((data.size() - pos) < count) || (pos > data.size())) throw std::invalid_argument("omw::readString");
    return omw::readString(data.data() + pos, count);
}

//!
//! Writes a string to a byte buffer (without a _null_ terminator).
//!
//! \b Exceptions
//! - `std::invalid_argument` if the data or end pointer is invalid
//! - `std::out_of_range` if the string length is greater than `end - buffer`
//!
void omw::writeString(uint8_t* buffer, const uint8_t* end, const std::string& str)
{
    if (buffer && end && (buffer <= end))
    {
        if (static_cast<std::string::size_type>(end - buffer) >= str.length())
        {
            for (std::string::size_type i = 0; i < str.length(); ++i) buffer[i] = static_cast<uint8_t>(str[i]);
        }
        else throw std::out_of_range("omw::writeString");
    }
    else throw std::invalid_argument("omw::writeString");
}

//!
//! Writes a string to a byte buffer (without a _null_ terminator).
//!
//! \b Exceptions
//! - `std::invalid_argument` if `pos` is greater than the buffers size
//! - `std::out_of_range` if the buffer can not hold the string
//!
void omw::writeString(std::vector<uint8_t>& buffer, std::vector<uint8_t>::size_type pos, const std::string& str)
{
    return omw::writeString(buffer.data() + pos, buffer.data() + buffer.size(), str);
}
