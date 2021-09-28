/*
author         Oliver Blaser
date           28.09.2021
copyright      MIT - Copyright (c) 2021 Oliver Blaser
*/

#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

#include "omw/defs.h"
#include "omw/string.h"



namespace
{
    template <typename T>
    T hexstointeger(const omw::string& str, const std::string& fnName)
    {
        const std::string exMsg_notHex(OMWi_DISPSTR(fnName + ": not a hex string"));
        const omw::string hexDigits(omw::hexStrDigitsLower);

        omw::string::size_type pos = 0;
        while ((str[pos] == '0') && (pos < (str.length() - 1))) ++pos;

        const omw::string hexStr((omw::string(str, pos)).toLower_ascii());
        const omw::string::size_type hexStrLen = hexStr.length();
        const omw::string::size_type maxLen = 2 * sizeof(T);

        T r = 0;

        if ((hexStrLen <= maxLen) && (hexStrLen > 0))
        {
            for (omw::string::size_type i = 0; i < hexStrLen; ++i)
            {
                const omw::string::size_type digitIdx = hexDigits.find(hexStr[hexStrLen - i - 1]);

                if (digitIdx == omw::string::npos) throw std::invalid_argument(exMsg_notHex);

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
}



/*!
* \class omw::StringReplacePair
*
* Container that holds information for search and replace methods.
*
* Used by `omw::string::replaceFirst()` and `omw::string::replaceAll()`.
*/

omw::StringReplacePair::StringReplacePair()
    : searchElem(), replaceElem()
{
}

omw::StringReplacePair::StringReplacePair(const std::string& searchElement, const std::string& replaceElement)
    : searchElem(searchElement), replaceElem(replaceElement)
{
}

omw::StringReplacePair::StringReplacePair(const char searchElement, const std::string& replaceElement)
    : searchElem(1, searchElement), replaceElem(replaceElement)
{
}

omw::StringReplacePair::StringReplacePair(const std::string& searchElement, const char replaceElement)
    : searchElem(searchElement), replaceElem(1, replaceElement)
{
}

omw::StringReplacePair::StringReplacePair(const char searchElement, const char replaceElement)
    : searchElem(1, searchElement), replaceElem(1, replaceElement)
{
}

const std::string& omw::StringReplacePair::search() const
{
    return searchElem;
}

const std::string& omw::StringReplacePair::replace() const
{
    return replaceElem;
}



/*!
* \class omw::string
*
* A with `std::string` interchangeable class to add more functionalities.
* This class does not override/implement any virtual methods of the base class and has no attributes. It's basically a `std::string` with some more methods.
*/

//bool omw::string::isValidUTF8(const omw::string& str)
//{
//    return str.isValidUTF8();
//}

omw::string::string()
    : std::string()
{}

omw::string::string(const char* str)
    : std::string(str)
{}

omw::string::string(const char* str, std::string::size_type count)
    : std::string(str, count)
{}

omw::string::string(const std::string& other, std::string::size_type pos, std::string::size_type count)
    : std::string(other, pos, count)
{}

omw::string::string(const char* first, const char* last)
    : std::string(first, last)
{}

//! @param search Substring to be replaced
//! @param replace String for replacement
//! @param startPos From where to start searching
//! @return `*this`
omw::string& omw::string::replaceFirst(const std::string& search, const std::string& replace, size_type startPos)
{
    size_type pos = find(search, startPos);
    if ((pos < length()) && (pos != std::string::npos)) this->replace(pos, search.length(), replace);
    return *this;
}

//! @param pair Search and replace string pair
//! @param startPos From where to start searching
//! @return `*this`
omw::string& omw::string::replaceFirst(const omw::StringReplacePair& pair, size_type startPos)
{
    return replaceFirst(pair.search(), pair.replace(), startPos);
}

//! @param search Substring to be replaced
//! @param replace String for replacement
//! @param startPos From where to start searching
//! @param [out] nReplacements Number of occurrences
//! @return `*this`
omw::string& omw::string::replaceAll(const std::string& search, const std::string& replace, size_type startPos, size_t* nReplacements)
{
    size_t cnt = 0;

    if (search.length() > 0)
    {
        size_type pos = find(search, startPos);
        while ((pos < length()) && (pos != std::string::npos))
        {
            this->replace(pos, search.length(), replace);
            ++cnt;
            pos = find(search, pos + replace.length());
        }
    }
    else cnt = OMW_SIZE_MAX;

    if (nReplacements) *nReplacements = cnt;

    return *this;
}

//! @param pair Search and replace string pair
//! @param startPos From where to start searching
//! @param [out] nReplacements Number of occurrences
//! @return `*this`
omw::string& omw::string::replaceAll(const omw::StringReplacePair& pair, size_type startPos, size_t* nReplacements)
{
    return replaceAll(pair.search(), pair.replace(), startPos, nReplacements);
}

//! @param pairs Search and replace string pair vector
//! @param startPos From where to start searching
//! @param [out] nReplacementsTotal Total number of occurrences
//! @param [out] nReplacements Number of occurrences of specific replace pair
//! @return `*this`
omw::string& omw::string::replaceAll(const std::vector<omw::StringReplacePair>& pairs, size_type startPos, size_t* nReplacementsTotal, std::vector<size_t>* nReplacements)
{
    bool allInvalid = true;
    size_t cnt = 0;
    size_t tmpCnt;

    if (nReplacements) *nReplacements = std::vector<size_t>(pairs.size(), OMW_SIZE_MAX);

    for (size_t i = 0; i < pairs.size(); ++i)
    {
        replaceAll(pairs[i], startPos, &tmpCnt);
        if (nReplacements) nReplacements->at(i) = tmpCnt;
        if (tmpCnt != OMW_SIZE_MAX)
        {
            cnt += tmpCnt;
            allInvalid = false;
        }
    }

    if (allInvalid) cnt = OMW_SIZE_MAX;

    if (nReplacementsTotal) *nReplacementsTotal = cnt;

    return *this;
}

//! @param pairs Pointer to a replace pair array
//! @param count 
//! @param startPos From where to start searching
//! @param [out] nReplacementsTotal Total number of occurrences
//! @param [out] nReplacements Number of occurrences of specific replace pair
//! @return `*this`
omw::string& omw::string::replaceAll(const omw::StringReplacePair* pairs, size_t count, size_type startPos, size_t* nReplacementsTotal, std::vector<size_t>* nReplacements)
{
    return replaceAll(std::vector<omw::StringReplacePair>(pairs, pairs + count), startPos, nReplacementsTotal, nReplacements);
}

omw::string& omw::string::lower_ascii()
{
    for (size_type i = 0; i < length(); ++i)
    {
        value_type& c = this->at(i);
        if ((c >= 'A') && (c <= 'Z')) c += 32;
    }

    return *this;
}

omw::string& omw::string::lower_asciiExt()
{
    lower_ascii();

    const omw::StringReplacePair rp[] =
    {
        omw::StringReplacePair(omw::UTF8CP_Auml, omw::UTF8CP_auml),
        omw::StringReplacePair(omw::UTF8CP_Ouml, omw::UTF8CP_ouml),
        omw::StringReplacePair(omw::UTF8CP_Uuml, omw::UTF8CP_uuml)
    };

    return replaceAll(rp, (sizeof(rp) / sizeof(rp[0])));
}

omw::string& omw::string::upper_ascii()
{
    for (size_type i = 0; i < length(); ++i)
    {
        value_type& c = this->at(i);
        if ((c >= 'a') && (c <= 'z')) c -= 32;
    }

    return *this;
}

omw::string& omw::string::upper_asciiExt()
{
    upper_ascii();

    const omw::StringReplacePair rp[] =
    {
        omw::StringReplacePair(omw::UTF8CP_auml, omw::UTF8CP_Auml),
        omw::StringReplacePair(omw::UTF8CP_ouml, omw::UTF8CP_Ouml),
        omw::StringReplacePair(omw::UTF8CP_uuml, omw::UTF8CP_Uuml)
    };

    return replaceAll(rp, (sizeof(rp) / sizeof(rp[0])));
}

omw::string omw::string::toLower_ascii() const
{
    omw::string s(this->c_str());
    return s.lower_ascii();
}

omw::string omw::string::toLower_asciiExt() const
{
    omw::string s(this->c_str());
    return s.lower_asciiExt();
}

omw::string omw::string::toUpper_ascii() const
{
    omw::string s(this->c_str());
    return s.upper_ascii();
}

omw::string omw::string::toUpper_asciiExt() const
{
    omw::string s(this->c_str());
    return s.upper_asciiExt();
}

omw::string& omw::string::encodeUrl()
{
    constexpr size_t count = 61;
    const char search[count] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 38, 39, 40, 41, 42, 43, 44, 47, 58, 59, 60, 61, 62, 63, 64, 91, 92, 93, 94, 96, 123, 124, 125, 127 };
    const omw::string replace[count] = { "%00", "%01", "%02", "%03", "%04", "%05", "%06", "%07", "%08", "%09", "%0A", "%0B", "%0C", "%0D", "%0E", "%0F", "%10", "%11", "%12", "%13", "%14", "%15", "%16", "%17", "%18", "%19", "%1A", "%1B", "%1C", "%1D", "%1E", "%1F", "%20", "%21", "%22", "%23", "%24", "%26", "%27", "%28", "%29", "%2A", "%2B", "%2C", "%2F", "%3A", "%3B", "%3C", "%3D", "%3E", "%3F", "%40", "%5B", "%5C", "%5D", "%5E", "%60", "%7B", "%7C", "%7D", "%7F" };

    replaceAll("%", "%25", 0, nullptr);
    for (size_t i = 0; i < count; ++i) replaceAll(omw::StringReplacePair(search[i], replace[i]), 0, nullptr);

    return *this;
}

omw::string omw::string::toUrlEncoded() const
{
    omw::string s(this->c_str());
    return s.encodeUrl();
}



omw::string omw::to_string(bool value, bool textual)
{
    if (textual) return (value ? "true" : "false");
    return (value ? "1" : "0");
}

template<typename T1, typename T2>
omw::string omw::to_string(const std::pair<T1, T2>& value, char sepChar)
{
    return (std::to_string(value.first) + sepChar + std::to_string(value.second));
}



//! @param boolStr Boolean string representation
//! @return Bool value of the string
//! 
//! \b true and \b 1 converts to `true`, \b false and \b 0 to `false`. The input is not case sensitive.
//! 
//! \b Exceptions
//! - `std::out_of_range` if the value isn't element of `{ "0", "1", "true", "false" }`
//! - <tt><a href="https://en.cppreference.com/w/cpp/string/basic_string/stol" target="_blank">std::stoi()</a></tt> is called and may throw `std::out_of_range` or `std::invalid_argument`
//! 
bool omw::stob(const std::string& boolStr)
{
    const omw::string tmpStr = boolStr;
    if (tmpStr.toLower_ascii() == "true") return true;
    if (tmpStr.toLower_ascii() == "false") return false;

    int boolInt = std::stoi(boolStr);

    if (boolInt == 1) return true;
    if (boolInt == 0) return false;

    throw std::out_of_range("stob");
}

//! @param str Pair string representation
//! @param sepChar Character between the two values
//! @return <tt><a href="https://en.cppreference.com/w/cpp/utility/pair" target="_blank">std::pair</a></tt> with the two values
//! 
//! \b Exceptions
//! - `std::invalid_argument` if the separator character was not found or it is at the first or at the last position in the string
//! - <tt><a href="https://en.cppreference.com/w/cpp/string/basic_string/stol" target="_blank">std::stoi()</a></tt> is called and may throw `std::out_of_range` or `std::invalid_argument`
//! 
std::pair<int32_t, int32_t> omw::stoipair(const std::string& str, char sepChar)
{
    const std::string fnName = "stoipair";

    std::string::size_type sp = str.find(sepChar);

    if ((sp == 0) || (sp >= (str.length() - 1)) || (sp == std::string::npos)) throw std::invalid_argument(OMWi_DISPSTR(fnName + ": invalid separator char pos"));

    const std::string first = str.substr(0, sp);
    const std::string second = str.substr(sp + 1);

    if (!isInteger(first)) throw std::invalid_argument(OMWi_DISPSTR(fnName + ": first is not an integer"));
    if (!isInteger(second)) throw std::invalid_argument(OMWi_DISPSTR(fnName + ": second is not an integer"));

    return std::pair<int32_t, int32_t>(std::stoi(first), std::stoi(second));
}

// https://en.cppreference.com/w/cpp/string/basic_string/stoul
// https://en.cppreference.com/w/cpp/string/basic_string/stof



omw::string omw::toHexStr(int8_t value)
{
    return omw::toHexStr((uint8_t)value);
}

omw::string omw::toHexStr(uint8_t value)
{
    const char r[] = { omw::hexStrDigits[(value >> 4) & 0x0F], omw::hexStrDigits[value & 0x0F], 0 };
    return r;
}

omw::string omw::toHexStr(int16_t value)
{
    return toHexStr((uint16_t)value);
}

omw::string omw::toHexStr(uint16_t value)
{
    return toHexStr((uint8_t)(value >> 8)) + toHexStr((uint8_t)value);
}

omw::string omw::toHexStr(int32_t value)
{
    return toHexStr((uint32_t)value);
}

omw::string omw::toHexStr(uint32_t value)
{
    return toHexStr((uint8_t)(value >> 24)) + toHexStr((uint8_t)(value >> 16)) + toHexStr((uint8_t)(value >> 8)) + toHexStr((uint8_t)value);
}

omw::string omw::toHexStr(int64_t value)
{
    return toHexStr((uint64_t)value);
}

omw::string omw::toHexStr(uint64_t value)
{
    return toHexStr((uint8_t)(value >> 56)) + toHexStr((uint8_t)(value >> 48)) + toHexStr((uint8_t)(value >> 40)) + toHexStr((uint8_t)(value >> 32)) +
        toHexStr((uint8_t)(value >> 24)) + toHexStr((uint8_t)(value >> 16)) + toHexStr((uint8_t)(value >> 8)) + toHexStr((uint8_t)value);
}

omw::string omw::toHexStr(int16_t value, char sepChar)
{
    return toHexStr((uint16_t)value, sepChar);
}

omw::string omw::toHexStr(uint16_t value, char sepChar)
{
    return toHexStr((uint8_t)(value >> 8)) + sepChar + toHexStr((uint8_t)value);
}

omw::string omw::toHexStr(int32_t value, char sepChar)
{
    return toHexStr((uint32_t)value, sepChar);
}

omw::string omw::toHexStr(uint32_t value, char sepChar)
{
    return toHexStr((uint8_t)(value >> 24)) + sepChar + toHexStr((uint8_t)(value >> 16)) + sepChar + toHexStr((uint8_t)(value >> 8)) + sepChar + toHexStr((uint8_t)value);
}

omw::string omw::toHexStr(int64_t value, char sepChar)
{
    return toHexStr((uint64_t)value, sepChar);
}

omw::string omw::toHexStr(uint64_t value, char sepChar)
{
    return toHexStr((uint8_t)(value >> 56)) + sepChar + toHexStr((uint8_t)(value >> 48)) + sepChar + toHexStr((uint8_t)(value >> 40)) + sepChar + toHexStr((uint8_t)(value >> 32)) + sepChar +
        toHexStr((uint8_t)(value >> 24)) + sepChar + toHexStr((uint8_t)(value >> 16)) + sepChar + toHexStr((uint8_t)(value >> 8)) + sepChar + toHexStr((uint8_t)value);
}

omw::string omw::toHexStr(const std::vector<char>& data, char sepChar)
{
    return toHexStr(data.data(), data.size(), sepChar);
}

omw::string omw::toHexStr(const std::vector<uint8_t>& data, char sepChar)
{
    return toHexStr(data.data(), data.size(), sepChar);
}

omw::string omw::toHexStr(const char* data, size_t count, char sepChar)
{
    return toHexStr((const uint8_t*)data, count, sepChar);
}

omw::string omw::toHexStr(const uint8_t* data, size_t count, char sepChar)
{
    omw::string str;

    for (size_t i = 0; i < count; ++i)
    {
        if ((i > 0) && (sepChar != 0)) str += sepChar;

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
int32_t omw::hexstoi(const std::string& str)
{
    return hexstointeger<int32_t>(str, "hexstoi");
}

//! @param str Hexadecimal string representation
//! @return The corresponding value
//! 
//! \b Exceptions
//! - `std::invalid_argument` if the string contains invalid characters
//! - `std::out_of_range` if the value would fall out of range
//! 
int64_t omw::hexstoi64(const std::string& str)
{
    return hexstointeger<int64_t>(str, "hexstoi64");
}

//! @param str Hexadecimal string representation
//! @return The corresponding value
//! 
//! \b Exceptions
//! - `std::invalid_argument` if the string contains invalid characters
//! - `std::out_of_range` if the value would fall out of range
//! 
uint32_t omw::hexstoui(const std::string& str)
{
    return hexstointeger<uint32_t>(str, "hexstoui");
}

//! @param str Hexadecimal string representation
//! @return The corresponding value
//! 
//! \b Exceptions
//! - `std::invalid_argument` if the string contains invalid characters
//! - `std::out_of_range` if the value would fall out of range
//! 
uint64_t omw::hexstoui64(const std::string& str)
{
    return hexstointeger<uint64_t>(str, "hexstoui64");
}

std::vector<uint8_t> omw::hexstovector(const std::string& str, char sepChar)
{
    const std::string fnName = "hexstovector";

    std::vector<std::string> hexStrings;
    for (std::string::size_type pos = 0; pos != std::string::npos;)
    {
        const std::string::size_type sepCharPos = str.find(sepChar, pos);
        std::string::size_type count;

        if (sepCharPos != std::string::npos) count = sepCharPos - pos;
        else count = std::string::npos;

        hexStrings.push_back(std::string(str, pos, count));

        if (sepCharPos != std::string::npos) pos = sepCharPos + 1;
        else pos = std::string::npos;
    }

    std::vector<uint8_t> values;
    for (size_t i = 0; i < hexStrings.size(); ++i)
    {
        uint32_t value = omw::hexstoui(hexStrings[i]);
        if (value > 0xFF) throw std::out_of_range(fnName);
        values.push_back(value);
    }

    return values;
}



bool omw::isInteger(const std::string& str)
{
    std::string::size_type startPos = 0;

    if (str.length() > 1)
    {
        if (str[0] == '-') startPos = 1;
    }

    return omw::isUInteger(std::string(str, startPos));
}

bool omw::isUInteger(const std::string& str)
{
    bool r;

    if (str.length() > 0)
    {
        r = true;
        for (std::string::size_type i = 0; i < str.length(); ++i)
        {
            if ((str[i] < '0') || (str[i] > '9'))
            {
                r = false;
                break;
            }
        }
    }
    else r = false;

    return r;
}

bool omw::isHex(const std::string& str)
{
    bool r;

    if (str.length() > 0)
    {
        const omw::string hexDigits(omw::hexStrDigitsLower);
        omw::string tmpStr(str);
        tmpStr.lower_ascii();

        r = true;
        for (omw::string::size_type i = 0; (i < tmpStr.length()) && r; ++i)
        {
            if (hexDigits.find(tmpStr[i]) == omw::string::npos)
            {
                r = false;
            }
        }
    }
    else r = false;

    return r;
}
