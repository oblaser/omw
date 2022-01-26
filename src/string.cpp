/*
author          Oliver Blaser
date            25.01.2022
copyright       MIT - Copyright (c) 2022 Oliver Blaser
*/

#include <stdexcept>
#include <string>
#include <vector>

#include "omw/algorithm.h"
#include "omw/defs.h"
#include "omw/string.h"



#define OMWi_CONVERT_STRING_VECTOR(out_t, in_t, stringVector)   \
out_t r;                                                        \
r.reserve((out_t::size_type)stringVector.size());               \
for (in_t::size_type i = 0; i < stringVector.size(); ++i)       \
{                                                               \
    r.push_back(out_t::value_type(stringVector[i].c_str()));    \
}                                                               \
return r                                                        \
// end OMWi_CONVERT_STRING_VECTOR

#define OMWi_CREATE_STRING_VECTOR(out_t, strings, count)    \
out_t r;                                                    \
r.reserve(count);                                           \
for (size_t i = 0; i < count; ++i)                          \
{                                                           \
    r.push_back(out_t::value_type(strings[i]));             \
}                                                           \
return r                                                    \
// end OMWi_CREATE_STRING_VECTOR



namespace
{
    template<typename T1, typename T2>
    omw::string pair_to_string(const std::pair<T1, T2>& value, char delimiter)
    {
        return (std::to_string(value.first) + delimiter + std::to_string(value.second));
    }

    // T has to be an integer type
    template <typename T>
    T hexstointeger(const omw::string& str, const std::string& fnName)
    {
        const std::string exMsg_notHex(OMWi_DISPSTR(fnName + ": not a hex string"));
        const omw::string hexDigits(omw::hexStrDigitsLower);

        const omw::string hexStr = str.toLower_ascii();
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
    omw::Base_Int128 hexstointeger128(const omw::string& str, const std::string& fnName)
    {
        const std::string exMsg_notHex(OMWi_DISPSTR(fnName + ": not a hex string"));

        const omw::string& hexStr = str;
        const omw::string::size_type hexStrLen = hexStr.length();
        const omw::string::size_type maxLen = 32;

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
                const omw::string hiStr = hexStr.substr(0, hexStrLen - 16);
                const omw::string loStr = hexStr.substr(hexStrLen - 16);
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
    //template <class out_t, class in_t>
    //out_t convertStringVector(const in_t& stringVector)
    //{
    //    out_t r;
    //    r.reserve((out_t::size_type)stringVector.size());
    //
    //    for (in_t::size_type i = 0; i < stringVector.size(); ++i)
    //    {
    //        r.push_back(out_t::value_type(stringVector[i].c_str()));
    //    }
    //
    //    return r;
    //}

    //// out_t has to be std::vector<omw::string> or std::vector<std::string>
    //template <class out_t>
    //out_t stringVector(const char* const* strings, size_t count)
    //{
    //    out_t r;
    //    r.reserve(count);
    //
    //    for (size_t i = 0; i < count; ++i)
    //    {
    //        r.push_back(out_t::value_type(strings[i]));
    //    }
    //
    //    return r;
    //}
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
* This class does not override/implement any (virtual) methods of the base class and has no attributes. It's basically a `std::string` with some more methods.
* However the two constructors which take the other string as a `char` pointer behave defined if a _null_ pointer is passed.
*/

//bool omw::string::isValidUTF8(const omw::string& str)
//{
//    return str.isValidUTF8();
//}

omw::string::string()
    : std::string()
{}

omw::string::string(omw::string::size_type count, char c)
    : std::string(count, c)
{}

omw::string::string(const char* str)
    : std::string(str ? str : "")
{}

omw::string::string(const char* str, omw::string::size_type count)
    : std::string(str ? str : "", str ? count : 0)
{}

omw::string::string(const std::string& other)
    : std::string(other)
{}

omw::string::string(const std::string& other, std::string::size_type pos, std::string::size_type count)
    : std::string(other, pos, count)
{}

omw::string::string(const char* first, const char* last)
    : std::string(first, last)
{}

//! 
//! Used if an implicit conversion to `std::string` is not possible (e.g. passing an `omw::string` to a function parameter of type `std::filesystem::path`).
//! 
std::string& omw::string::std()
{
    return *this;
}

const std::string& omw::string::std() const
{
    return *this;
}

#ifdef OMWi_DOXYGEN_PREDEFINE
/*!
* \fn omw::string::contains(char ch) const
* _until C++23_<br/>_since C++23_ Defined in std::string
*
* Defined in the header.
*/

/*!
* \fn omw::string::contains(const char* str) const
* _until C++23_<br/>_since C++23_ Defined in std::string
*
* Defined in the header.
*/

/*!
* \fn omw::string::contains(const std::string& str) const
* _until C++17_
*
* Defined in the header.
*/

/*!
* \fn omw::string::contains(std::string_view sv) const
* _since C++17_<br/>_until C++23_<br/>_since C++23_ Defined in std::string
*
* Defined in the header.
*/
#endif // OMWi_DOXYGEN_PREDEFINE

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

//! @param search Character to be replaced
//! @param replace Character for replacement
//! @param startPos From where to start searching
//! @param [out] nReplacements Number of occurrences
//! @return `*this`
omw::string& omw::string::replaceAll(char search, char replace, size_type startPos, size_t* nReplacements)
{
    size_t cnt = 0;

    for (size_t i = startPos; i < length(); ++i)
    {
        if (at(i) == search)
        {
            at(i) = replace;
            ++cnt;
        }
    }

    if (nReplacements) *nReplacements = cnt;

    return *this;
}

//! @param search Character to be replaced
//! @param replace String for replacement
//! @param startPos From where to start searching
//! @param [out] nReplacements Number of occurrences
//! @return `*this`
omw::string& omw::string::replaceAll(char search, const std::string& replace, size_type startPos, size_t* nReplacements)
{
    return replaceAll(omw::StringReplacePair(search, replace), startPos, nReplacements);
}

//! @param search Substring to be replaced
//! @param replace Character for replacement
//! @param startPos From where to start searching
//! @param [out] nReplacements Number of occurrences
//! @return `*this`
omw::string& omw::string::replaceAll(const std::string& search, char replace, size_type startPos, size_t* nReplacements)
{
    return replaceAll(omw::StringReplacePair(search, replace), startPos, nReplacements);
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
    else cnt = SIZE_MAX;

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

    if (nReplacements) *nReplacements = std::vector<size_t>(pairs.size(), SIZE_MAX);

    for (size_t i = 0; i < pairs.size(); ++i)
    {
        replaceAll(pairs[i], startPos, &tmpCnt);
        if (nReplacements) nReplacements->at(i) = tmpCnt;
        if (tmpCnt != SIZE_MAX)
        {
            cnt += tmpCnt;
            allInvalid = false;
        }
    }

    if (allInvalid) cnt = SIZE_MAX;

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

omw::stringVector_t omw::string::split(char delimiter, omw::stringVector_t::size_type maxTokenCount) const
{
    omw::stringVector_t r(0);

    if (maxTokenCount > 0)
    {
        const omw::stringVector_t::size_type n = maxTokenCount - 1;
        omw::string::size_type pos = 0;

        while (pos < omw::string::npos)
        {
            if (r.size() < n)
            {
                const omw::string::size_type end = this->find(delimiter, pos);
                r.push_back(this->substr(pos, end - pos));
                pos = end;
                if (pos < omw::string::npos) ++pos;
            }
            else
            {
                r.push_back(this->substr(pos));
                pos = omw::string::npos;
            }
        }
    }

    return r;
}

omw::stringVector_t omw::string::splitLen(omw::string::size_type tokenLength, omw::stringVector_t::size_type maxTokenCount) const
{
    omw::stringVector_t r(0);

    if (maxTokenCount > 0)
    {
        const omw::string::size_type len = this->length();
        omw::string::size_type pos = 0;

        for (omw::stringVector_t::size_type iToken = 0; (iToken < maxTokenCount) && (pos < len); ++iToken)
        {
            r.push_back(this->substr(pos, tokenLength));
            pos += tokenLength;
        }

        if (pos < len)
        {
            r[r.size() - 1] += this->substr(pos);
        }
    }

    return r;
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



omw::string omw::to_string(int32_t value)
{
    return std::to_string(value);
}

omw::string omw::to_string(uint32_t value)
{
    return std::to_string(value);
}

omw::string omw::to_string(int64_t value)
{
    return std::to_string(value);
}

omw::string omw::to_string(uint64_t value)
{
    return std::to_string(value);
}

omw::string omw::to_string(float value)
{
    return std::to_string(value);
}

omw::string omw::to_string(double value)
{
    return std::to_string(value);
}

omw::string omw::to_string(long double value)
{
    return std::to_string(value);
}

omw::string omw::to_string(bool value, bool asText)
{
    if (asText) return (value ? "true" : "false");
    return (value ? "1" : "0");
}

omw::string omw::to_string(const omw::int128_t& value)
{
    const omw::uint128_t tmp(value);
    return (value.isNegative() ? "-" + omw::to_string(-tmp) : omw::to_string(tmp));
}

omw::string omw::to_string(const omw::uint128_t& value)
{
    omw::string str = omw::toHexStr(omw::doubleDabble(value), 0);
    size_t startPos = 0;
    while ((str[startPos] == '0') && (startPos < (str.length() - 1))) ++startPos;
    return omw::string(str, startPos);
}

omw::string omw::to_string(const std::pair<int32_t, int32_t>& value, char delimiter)
{
    return ::pair_to_string(value, delimiter);
}

omw::string omw::to_string(const std::pair<uint32_t, uint32_t>& value, char delimiter)
{
    return ::pair_to_string(value, delimiter);
}

omw::string omw::to_string(const std::pair<int64_t, int64_t>& value, char delimiter)
{
    return ::pair_to_string(value, delimiter);
}

omw::string omw::to_string(const std::pair<uint64_t, uint64_t>& value, char delimiter)
{
    return ::pair_to_string(value, delimiter);
}

omw::string omw::to_string(const std::pair<float, float>& value, char delimiter)
{
    return ::pair_to_string(value, delimiter);
}

omw::string omw::to_string(const std::pair<double, double>& value, char delimiter)
{
    return ::pair_to_string(value, delimiter);
}

omw::string omw::to_string(const std::pair<long double, long double>& value, char delimiter)
{
    return ::pair_to_string(value, delimiter);
}



//! @param boolStr Boolean string representation
//! @return Bool value of the string
//! 
//! \b true and \b 1 converts to `true`, \b false and \b 0 to `false`. The input is not case sensitive.
//! 
//! \b Exceptions
//! - `std::out_of_range` if the value isn't an element of `{ "0", "1", "true", "false" }`
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

    throw std::out_of_range("omw::stob");
}

//! @param str Pair string representation
//! @param delimiter Character between the two values
//! @return <tt><a href="https://en.cppreference.com/w/cpp/utility/pair" target="_blank">std::pair</a></tt> with the two values
//! 
//! \b Exceptions
//! - `std::invalid_argument` if the separator character was not found or it is at the first or at the last position in the string
//! - <tt><a href="https://en.cppreference.com/w/cpp/string/basic_string/stol" target="_blank">std::stoi()</a></tt> is called and may throw `std::out_of_range` or `std::invalid_argument`
//! 
std::pair<int32_t, int32_t> omw::stoipair(const std::string& str, char delimiter)
{
    const std::string fnName = "omw::stoipair";

    std::string::size_type sp = str.find(delimiter);

    if ((sp == 0) || (sp >= (str.length() - 1)) || (sp == std::string::npos)) throw std::invalid_argument(OMWi_DISPSTR(fnName + ": invalid separator char pos"));

    const std::string first = str.substr(0, sp);
    const std::string second = str.substr(sp + 1);

    if (!isInteger(first)) throw std::invalid_argument(OMWi_DISPSTR(fnName + ": first is not an integer"));
    if (!isInteger(second)) throw std::invalid_argument(OMWi_DISPSTR(fnName + ": second is not an integer"));

    return std::pair<int32_t, int32_t>(std::stoi(first), std::stoi(second));
}

//omw::int128_t omw::stoi128(const std::string& str)
//{
//    reversed double dabble needed, wich is not implemented yet
//}
//
//omw::uint128_t omw::stoui128(const std::string& str)
//{
//    reversed double dabble needed, wich is not implemented yet
//}



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

omw::string omw::toHexStr(const omw::Base_Int128& value)
{
    return omw::toHexStr(value.hi()) + omw::toHexStr(value.lo());
}

omw::string omw::toHexStr(int16_t value, char delimiter)
{
    return toHexStr((uint16_t)value, delimiter);
}

omw::string omw::toHexStr(uint16_t value, char delimiter)
{
    return toHexStr((uint8_t)(value >> 8)) + delimiter + toHexStr((uint8_t)value);
}

omw::string omw::toHexStr(int32_t value, char delimiter)
{
    return toHexStr((uint32_t)value, delimiter);
}

omw::string omw::toHexStr(uint32_t value, char delimiter)
{
    return toHexStr((uint8_t)(value >> 24)) + delimiter + toHexStr((uint8_t)(value >> 16)) + delimiter + toHexStr((uint8_t)(value >> 8)) + delimiter + toHexStr((uint8_t)value);
}

omw::string omw::toHexStr(int64_t value, char delimiter)
{
    return toHexStr((uint64_t)value, delimiter);
}

omw::string omw::toHexStr(uint64_t value, char delimiter)
{
    return toHexStr((uint8_t)(value >> 56)) + delimiter + toHexStr((uint8_t)(value >> 48)) + delimiter + toHexStr((uint8_t)(value >> 40)) + delimiter + toHexStr((uint8_t)(value >> 32)) + delimiter +
        toHexStr((uint8_t)(value >> 24)) + delimiter + toHexStr((uint8_t)(value >> 16)) + delimiter + toHexStr((uint8_t)(value >> 8)) + delimiter + toHexStr((uint8_t)value);
}

omw::string omw::toHexStr(const omw::Base_Int128& value, char delimiter)
{
    return omw::toHexStr(value.hi(), delimiter) + delimiter + omw::toHexStr(value.lo(), delimiter);
}

omw::string omw::toHexStr(const std::vector<char>& data, char delimiter)
{
    return toHexStr(data.data(), data.size(), delimiter);
}

omw::string omw::toHexStr(const std::vector<uint8_t>& data, char delimiter)
{
    return toHexStr(data.data(), data.size(), delimiter);
}

omw::string omw::toHexStr(const char* data, size_t count, char delimiter)
{
    return toHexStr((const uint8_t*)data, count, delimiter);
}

omw::string omw::toHexStr(const uint8_t* data, size_t count, char delimiter)
{
    omw::string str;

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
int32_t omw::hexstoi(const std::string& str)
{
    return hexstointeger<int32_t>(str, "omw::hexstoi");
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
    return hexstointeger<int64_t>(str, "omw::hexstoi64");
}

//! @param str Hexadecimal string representation
//! @return The corresponding value
//! 
//! \b Exceptions
//! - `std::invalid_argument` if the string contains invalid characters
//! - `std::out_of_range` if the value would fall out of range
//! 
omw::int128_t omw::hexstoi128(const std::string& str)
{
    return hexstointeger128(str, "omw::hexstoi128");
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
    return hexstointeger<uint32_t>(str, "omw::hexstoui");
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
    return hexstointeger<uint64_t>(str, "omw::hexstoui64");
}

//! @param str Hexadecimal string representation
//! @return The corresponding value
//! 
//! \b Exceptions
//! - `std::invalid_argument` if the string contains invalid characters
//! - `std::out_of_range` if the value would fall out of range
//! 
omw::uint128_t omw::hexstoui128(const std::string& str)
{
    return hexstointeger128(str, "omw::hexstoui128");
}

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

        omw::string tmpStr;

        if (delimiter == 0)
        {
            delimiter = toHexStr_defaultDelimiter;
            tmpStr = omw::sepHexStr(str, toHexStr_defaultDelimiter);
        }
        else tmpStr = str;

        const std::vector<omw::string> hexStrings = tmpStr.split(delimiter);

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
omw::string omw::sepHexStr(const std::string& str)
{
    return omw::sepHexStr(str, omw::toHexStr_defaultDelimiter);
}

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
omw::string omw::sepHexStr(const std::string& str, char delimiter)
{
    omw::string tmp(str);
    if (tmp.length() & 0x01) tmp = '0' + tmp;
    return omw::join(tmp.splitLen(2), delimiter);
}

//! 
//! Removes all `rmChar` from the string and returns `omw::sepHexStr(const std::string&, char)`.
//! 
omw::string omw::sepHexStr(const std::string& str, char rmChar, char delimiter)
{
    omw::string hexstr = str;
    hexstr.replaceAll(omw::StringReplacePair(rmChar, ""));

    return omw::sepHexStr(hexstr, delimiter);
}

//! 
//! Removes all characters pointed to by `rmChars` from the string and returns `omw::sepHexStr(const std::string&, char)`.
//! 
omw::string omw::sepHexStr(const std::string& str, const char* rmChars, size_t count, char delimiter)
{
    std::vector<omw::StringReplacePair> replPairs;
    replPairs.reserve(count);

    for (size_t i = 0; i < count; ++i)
    {
        replPairs.push_back(omw::StringReplacePair(rmChars[i], ""));
    }

    omw::string hexstr = str;
    hexstr.replaceAll(replPairs);

    return omw::sepHexStr(hexstr, delimiter);
}

//! 
//! Removes all characters in `rmChars` from the string and returns `omw::sepHexStr(const std::string&, char)`.
//! 
omw::string omw::sepHexStr(const std::string& str, const std::vector<char>& rmChars, char delimiter)
{
    return omw::sepHexStr(str, rmChars.data(), rmChars.size(), delimiter);
}

// ready, but not tested:
// 
//omw::string omw::sepHexStr(const std::string& str, const std::vector<char>& rmChars, char delimiter)
//{
//    return omw::sepHexStr(str, rmChars.data(), rmChars.size(), delimiter);
//}
//
//omw::string omw::sepHexStr(const std::string& str, const char* rmString, char delimiter)
//{
//    omw::string hexstr = str;
//    hexstr.replaceAll(rmString, "");
//
//    return ::separateHexStr(hexstr, delimiter);
//}
//
//omw::string omw::sepHexStr(const std::string& str, const std::string& rmString, char delimiter)
//{
//    return omw::sepHexStr(str, rmString.c_str(), delimiter);
//}
//
//omw::string omw::sepHexStr(const std::string& str, const std::string* rmStrings, size_t count, char delimiter)
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
//omw::string omw::sepHexStr(const std::string& str, const omw::stringVector_t& rmStrings, char delimiter)
//{
//    return omw::sepHexStr(str, rmStrings.data(), rmStrings.size(), delimiter);
//}

omw::string omw::rmNonHex(const std::string& str)
{
    omw::string r = str;
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
    for (std::string::size_type i = 0; i < str.length(); )
    {
        if (omw::isHex(str[i])) ++i;
        else str.erase(i, 1);
    }
}



omw::string omw::join(const omw::stringVector_t& strings)
{
    omw::string r = "";

    for (omw::stringVector_t::size_type i = 0; i < strings.size(); ++i)
    {
        r += strings[i];
    }

    return r;
}

omw::string omw::join(const omw::stringVector_t& strings, char delimiter)
{
    omw::string r = "";

    for (omw::stringVector_t::size_type i = 0; i < strings.size(); ++i)
    {
        if (i > 0) r += omw::string(1, delimiter);
        r += strings[i];
    }

    return r;
}



omw::stringVector_t omw::stringVector(const char* const* strings, size_t count)
{
    //return ::stringVector<omw::stringVector_t>(strings, count);

    OMWi_CREATE_STRING_VECTOR(omw::stringVector_t, strings, count);
}

omw::stringVector_t omw::stringVector(const std::string* strings, size_t count)
{
    std::vector<const char*> v;
    v.reserve(count);

    for (size_t i = 0; i < count; ++i)
    {
        v.push_back((strings + i)->c_str());
    }

    //return ::stringVector<omw::stringVector_t>(v.data(), count);

    OMWi_CREATE_STRING_VECTOR(omw::stringVector_t, v.data(), count);
}

omw::stringVector_t omw::stringVector(const omw::string* strings, size_t count)
{
    return omw::stringVector_t(strings, strings + count);
}

omw::stringVector_t omw::stringVector(const omw::stdStringVector_t& strvec)
{
    //return convertStringVector<omw::stringVector_t, omw::stdStringVector_t>(strvec);

    OMWi_CONVERT_STRING_VECTOR(omw::stringVector_t, omw::stdStringVector_t, strvec);
}

omw::stdStringVector_t omw::stdStringVector(const char* const* strings, size_t count)
{
    //return ::stringVector<omw::stdStringVector_t>(strings, count);

    OMWi_CREATE_STRING_VECTOR(omw::stdStringVector_t, strings, count);
}

omw::stdStringVector_t omw::stdStringVector(const std::string* strings, size_t count)
{
    return omw::stdStringVector_t(strings, strings + count);
}

omw::stdStringVector_t omw::stdStringVector(const omw::string* strings, size_t count)
{
    std::vector<const char*> v;
    v.reserve(count);

    for (size_t i = 0; i < count; ++i)
    {
        v.push_back((strings + i)->c_str());
    }

    //return ::stringVector<omw::stdStringVector_t>(v.data(), count);

    OMWi_CREATE_STRING_VECTOR(omw::stdStringVector_t, v.data(), count);
}

omw::stdStringVector_t omw::stdStringVector(const omw::stringVector_t& strvec)
{
    //return convertStringVector<omw::stdStringVector_t, omw::stringVector_t>(strvec);

    OMWi_CONVERT_STRING_VECTOR(omw::stdStringVector_t, omw::stringVector_t, strvec);
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
//! An empty string returns `false`.
//! 
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
            r = hexDigits.contains(tmpStr[i]);
        }
    }
    else r = false;

    return r;
}



//! @param p Pointer to the position in the string
//! @return Number of new line characters at <tt>p</tt>, range: [0, 2]
//! 
//! It's recommended to use `omw::peekNewLine(const char*, const char*)` to prevent access violations.
//! 
size_t omw::peekNewLine(const char* p)
{
    size_t r;

    if (p)
    {
        if (*p == 0x0A) r = 1; // LF
        else if ((*p == 0x0D) && (*(p + 1) != 0x0A)) r = 1; // CR
        else if ((*p == 0x0D) && (*(p + 1) == 0x0A)) r = 2; // CR+LF
        else r = 0;
    }
    else r = 0;

    return r;
}

//! @param p Pointer to the position in the string
//! @param end Pointer to the first position beyond the string
//! @return Number of new line characters at <tt>p</tt>, range: [0, 2]
//! 
//! If <b><tt>end</tt></b> is <tt>NULL</tt>, <tt>omw::peekNewLine(const char*)</tt> will be used, hence access violations may occure.
//! 
//! Does not throw an exception, but return 0 if the pointers are invalid.
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
                    else r = 1; // CR
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
omw::string omw::readString(const uint8_t* data, size_t count)
{
    omw::string str(count, '#');

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
omw::string omw::readString(const std::vector<uint8_t>& data, std::vector<uint8_t>::size_type pos, std::vector<uint8_t>::size_type count)
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
