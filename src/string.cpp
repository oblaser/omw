/*
author         Oliver Blaser
date           07.09.2021
copyright      MIT - Copyright (c) 2021 Oliver Blaser
*/

#include <stdexcept>
#include <string>
#include <vector>

#include "omw/defs.h"
#include "omw/string.h"



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
{
}

omw::string::string(const char* str)
    : std::string(str)
{
}

omw::string::string(const std::string& str)
    : std::string(str)
{
}

omw::string::string(const char* first, const char* last)
    : std::string(first, last)
{
}

bool omw::string::isInteger() const
{
    return omw::isInteger(*this);
}

bool omw::string::isUInteger() const
{
    return omw::isUInteger(*this);
}

bool omw::string::isHex() const
{
    return omw::isHex(*this);
}

//! @param search Substring to be replaced
//! @param replace String for replacement
//! @param startPos From where to start searching
//! @return `*this`
omw::string& omw::string::replaceFirst(const omw::string& search, const omw::string& replace, size_type startPos)
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
omw::string& omw::string::replaceAll(const omw::string& search, const omw::string& replace, size_type startPos, size_type* nReplacements)
{
    size_type cnt = 0;

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
    else cnt = npos;

    if (nReplacements) *nReplacements = cnt;

    return *this;
}

//! @param pair Search and replace string pair
//! @param startPos From where to start searching
//! @param [out] nReplacements Number of occurrences
//! @return `*this`
omw::string& omw::string::replaceAll(const omw::StringReplacePair& pair, size_type startPos, size_type* nReplacements)
{
    return replaceAll(pair.search(), pair.replace(), startPos, nReplacements);
}

//! @param pairs Search and replace string pair vector
//! @param startPos From where to start searching
//! @param [out] nReplacementsTotal Total number of occurrences
//! @param [out] nReplacements Number of occurrences of specific replace pair
//! @return `*this`
omw::string& omw::string::replaceAll(const std::vector<omw::StringReplacePair>& pairs, size_type startPos, size_type* nReplacementsTotal, std::vector<size_type>* nReplacements)
{
    bool allInvalid = true;
    size_type cnt = 0;
    size_type tmpCnt;

    if (nReplacements) *nReplacements = std::vector<size_type>(pairs.size(), npos);

    for (size_t i = 0; i < pairs.size(); ++i)
    {
        replaceAll(pairs[i], startPos, &tmpCnt);
        if (nReplacements) nReplacements->at(i) = tmpCnt;
        if (tmpCnt != npos)
        {
            cnt += tmpCnt;
            allInvalid = false;
        }
    }

    if (allInvalid) cnt = npos;

    if (nReplacementsTotal) *nReplacementsTotal = cnt;

    return *this;
}

//! @param pairsBegin Pointer to first replace pair in array
//! @param pairsEnd Pointer to first replace pair behind the array
//! @param startPos From where to start searching
//! @param [out] nReplacementsTotal Total number of occurrences
//! @param [out] nReplacements Number of occurrences of specific replace pair
//! @return `*this`
//! 
//! Processes all replace pairs in range [`pairsBegin`, `pairsEnd`).
//! 
omw::string& omw::string::replaceAll(const omw::StringReplacePair* pairsBegin, const omw::StringReplacePair* pairsEnd, size_type startPos, size_type* nReplacementsTotal, std::vector<size_type>* nReplacements)
{
    return replaceAll(std::vector<omw::StringReplacePair>(pairsBegin, pairsEnd), startPos, nReplacementsTotal, nReplacements);
}

omw::string& omw::string::makeLower_ascii()
{
    for (size_type i = 0; i < length(); ++i)
    {
        value_type& c = this->at(i);
        if ((c >= 'A') && (c <= 'Z')) c += 32;
    }

    return *this;
}

omw::string& omw::string::makeLower_asciiExt()
{
    makeLower_ascii();

    const omw::StringReplacePair rp[] =
    {
        omw::StringReplacePair(omw::UTF8CP_Auml, omw::UTF8CP_auml),
        omw::StringReplacePair(omw::UTF8CP_Ouml, omw::UTF8CP_ouml),
        omw::StringReplacePair(omw::UTF8CP_Uuml, omw::UTF8CP_uuml)
    };

    return replaceAll(rp, rp + (sizeof(rp) / sizeof(rp[0])));
}

omw::string& omw::string::makeUpper_ascii()
{
    for (size_type i = 0; i < length(); ++i)
    {
        value_type& c = this->at(i);
        if ((c >= 'a') && (c <= 'z')) c -= 32;
    }

    return *this;
}

omw::string& omw::string::makeUpper_asciiExt()
{
    makeUpper_ascii();

    const omw::StringReplacePair rp[] =
    {
        omw::StringReplacePair(omw::UTF8CP_auml, omw::UTF8CP_Auml),
        omw::StringReplacePair(omw::UTF8CP_ouml, omw::UTF8CP_Ouml),
        omw::StringReplacePair(omw::UTF8CP_uuml, omw::UTF8CP_Uuml)
    };

    return replaceAll(rp, rp + (sizeof(rp) / sizeof(rp[0])));
}

omw::string omw::string::toLower_ascii() const
{
    omw::string s(this->c_str());
    return s.makeLower_ascii();
}

omw::string omw::string::toLower_asciiExt() const
{
    omw::string s(this->c_str());
    return s.makeLower_asciiExt();
}

omw::string omw::string::toUpper_ascii() const
{
    omw::string s(this->c_str());
    return s.makeUpper_ascii();
}

omw::string omw::string::toUpper_asciiExt() const
{
    omw::string s(this->c_str());
    return s.makeUpper_asciiExt();
}

omw::string& omw::string::makeUrlEncoded()
{
    const size_t count = 61;
    const char search[count] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 38, 39, 40, 41, 42, 43, 44, 47, 58, 59, 60, 61, 62, 63, 64, 91, 92, 93, 94, 96, 123, 124, 125, 127 };
    const omw::string replace[count] = { "%00", "%01", "%02", "%03", "%04", "%05", "%06", "%07", "%08", "%09", "%0A", "%0B", "%0C", "%0D", "%0E", "%0F", "%10", "%11", "%12", "%13", "%14", "%15", "%16", "%17", "%18", "%19", "%1A", "%1B", "%1C", "%1D", "%1E", "%1F", "%20", "%21", "%22", "%23", "%24", "%26", "%27", "%28", "%29", "%2A", "%2B", "%2C", "%2F", "%3A", "%3B", "%3C", "%3D", "%3E", "%3F", "%40", "%5B", "%5C", "%5D", "%5E", "%60", "%7B", "%7C", "%7D", "%7F" };

    replaceAll("%", "%25", 0, nullptr);
    for (size_t i = 0; i < count; ++i) replaceAll(omw::StringReplacePair(search[i], replace[i]), 0, nullptr);

    return *this;
}

omw::string omw::string::toUrlEncoded() const
{
    omw::string s(this->c_str());
    return s.makeUrlEncoded();
}



omw::string omw::to_string(bool value, bool textual)
{
    if (textual) return (value ? "true" : "false");
    return (value ? "1" : "0");
}

template<typename T1, typename T2>
std::string omw::to_string(const std::pair<T1, T2>& value, char sepChar)
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
bool omw::stob(const omw::string& boolStr)
{
    if (boolStr.toLower_ascii() == "true") return true;
    if (boolStr.toLower_ascii() == "false") return false;

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
//! - `std::invalid_argument` if the separator character was not found, is at the first or at the last position in the string
//! - <tt><a href="https://en.cppreference.com/w/cpp/string/basic_string/stol" target="_blank">std::stoi()</a></tt> is called and may throw `std::out_of_range` or `std::invalid_argument`
//! 
std::pair<int, int> omw::stoipair(const std::string& str, char sepChar)
{
    const std::string fnName = "stoipair";

    size_t sp = str.find(sepChar);

    if ((sp == 0) || (sp >= (str.length() - 1)) || (sp == std::string::npos)) throw std::invalid_argument(OMWi_DISPSTR(fnName + ": invalid separator char pos"));

    const std::string first = str.substr(0, sp);
    const std::string second = str.substr(sp + 1);

    if (!isInteger(first)) throw std::invalid_argument(OMWi_DISPSTR(fnName + ": first is not an integer"));
    if (!isInteger(second)) throw std::invalid_argument(OMWi_DISPSTR(fnName + ": second is not an integer"));

    return std::pair<int, int>(std::stoi(first), std::stoi(second));
}

// https://en.cppreference.com/w/cpp/string/basic_string/stoul
// https://en.cppreference.com/w/cpp/string/basic_string/stof


bool omw::isInteger(const std::string& str)
{
    size_t startPos = 0;

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
        for (size_t i = 0; i < str.length(); ++i)
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
        r = true;
        for (size_t i = 0; i < str.length(); ++i)
        {
            asdf;
        }
    }
    else r = false;

    return r;
}



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



int32_t omw::hexstoi(const std::string& str)
{
    const std::string fnName = "hexstoi";
    std::string hexstr(str, 0, 8);
    if (!omw::isHex(hexstr)) throw std::invalid_argument(OMWi_DISPSTR(fnName + ": not a hex string"));
    int32_t r = 0;

    asdf;

    return r;
}

int64_t omw::hexstoi64(const std::string& str)
{
    const std::string fnName = "hexstoi64";
    std::string hexstr(str, 0, 16);
    if (!omw::isHex(hexstr)) throw std::invalid_argument(OMWi_DISPSTR(fnName + ": not a hex string"));
    int32_t r = 0;

    asdf;

    return r;
}
