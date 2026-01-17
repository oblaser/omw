/*
author          Oliver Blaser
copyright       MIT - Copyright (c) 2023 Oliver Blaser
*/

#ifndef IG_OMW_STRING_H
#define IG_OMW_STRING_H

#include <cstddef>
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

#include "../omw/defs.h"
#include "../omw/int.h"
#include "../omw/vector.h"


#if OMW_CPPSTD >= OMW_CPPSTD_20
#define OMW_STDSTRING_CONSTEXPR constexpr
#else
#define OMW_STDSTRING_CONSTEXPR
#endif


/*! \addtogroup grp_stringLib
 * @{
 */

//! \name UTF-8 Byte Strings
/// @{
#define OMW_UTF8CP_00B0 "\xC2\xB0"
#define OMW_UTF8CP_00C4 "\xC3\x84"
#define OMW_UTF8CP_00D6 "\xC3\x96"
#define OMW_UTF8CP_00DC "\xC3\x9C"
#define OMW_UTF8CP_00E4 "\xC3\xA4"
#define OMW_UTF8CP_00F6 "\xC3\xB6"
#define OMW_UTF8CP_00FC "\xC3\xBC"
#define OMW_UTF8CP_2580 "\xE2\x96\x80"
#define OMW_UTF8CP_2584 "\xE2\x96\x84"
#define OMW_UTF8CP_2588 "\xE2\x96\x88"
/// @}

//! \name UFT-8 Byte String Aliases
/// @{
#define OMW_UTF8CP_deg  OMW_UTF8CP_00B0
#define OMW_UTF8CP_Auml OMW_UTF8CP_00C4
#define OMW_UTF8CP_Ouml OMW_UTF8CP_00D6
#define OMW_UTF8CP_Uuml OMW_UTF8CP_00DC
#define OMW_UTF8CP_auml OMW_UTF8CP_00E4
#define OMW_UTF8CP_ouml OMW_UTF8CP_00F6
#define OMW_UTF8CP_uuml OMW_UTF8CP_00FC
/// @}

/*! @} */


namespace omw {

/*! \addtogroup grp_stringLib
 * @{
 */

//! \name UTF-8 Byte Strings
/// @{
const char* const UTF8CP_00C4 = OMW_UTF8CP_00C4;
const char* const UTF8CP_00D6 = OMW_UTF8CP_00D6;
const char* const UTF8CP_00DC = OMW_UTF8CP_00DC;
const char* const UTF8CP_00E4 = OMW_UTF8CP_00E4;
const char* const UTF8CP_00F6 = OMW_UTF8CP_00F6;
const char* const UTF8CP_00FC = OMW_UTF8CP_00FC;
const char* const UTF8CP_2580 = OMW_UTF8CP_2580;
const char* const UTF8CP_2584 = OMW_UTF8CP_2584;
const char* const UTF8CP_2588 = OMW_UTF8CP_2588;
/// @}

//! \name UFT-8 Byte String Aliases
/// @{
const char* const UTF8CP_Auml = omw::UTF8CP_00C4;
const char* const UTF8CP_Ouml = omw::UTF8CP_00D6;
const char* const UTF8CP_Uuml = omw::UTF8CP_00DC;
const char* const UTF8CP_auml = omw::UTF8CP_00E4;
const char* const UTF8CP_ouml = omw::UTF8CP_00F6;
const char* const UTF8CP_uuml = omw::UTF8CP_00FC;
/// @}

constexpr char pairtos_defaultDelimiter = ';';
const char* const hexStrDigitsUpper = "0123456789ABCDEF";
const char* const hexStrDigitsLower = "0123456789abcdef";
const char* const hexStrDigits = hexStrDigitsUpper;
constexpr char toHexStr_defaultDelimiter = 0x20;



//! \name String Vectors
/// @{

using StringVector = std::vector<std::string>;
constexpr omw::StringVector::size_type StringVector_npos = static_cast<StringVector::size_type>(-1);

omw::StringVector stringVector(const char* const * strings, omw::StringVector::size_type count);
omw::StringVector stringVector(const std::string* strings, omw::StringVector::size_type count);

/// @}



class StringReplacePair
{
public:
    StringReplacePair()
        : m_s(), m_r()
    {}

    StringReplacePair(const std::string& searchElement, const std::string& replaceElement)
        : m_s(searchElement), m_r(replaceElement)
    {}

    StringReplacePair(const char searchElement, const std::string& replaceElement)
        : m_s(1, searchElement), m_r(replaceElement)
    {}

    StringReplacePair(const std::string& searchElement, const char replaceElement)
        : m_s(searchElement), m_r(1, replaceElement)
    {}

    StringReplacePair(const char searchElement, const char replaceElement)
        : m_s(1, searchElement), m_r(1, replaceElement)
    {}

    virtual ~StringReplacePair() {}

    const std::string& search() const { return m_s; }
    const std::string& replace() const { return m_r; }

private:
    std::string m_s;
    std::string m_r;
};



/**
 * Reverses (swaps) the content of the string.
 *
 * Converts `abcd` to `dcba`, and `xyz` to `zyx`.
 */
std::string& reverse(std::string& str);

/**
 * @brief
 *
 * @param str
 * @return std::string
 */
std::string toReversed(const std::string& str);



//! \name Case Conversion
//! Methods named `.._ascii` convert only A-Z and a-z. Those named `.._asciiExt` additionally convert some UTF-8 code points.
/// @{

// std::string& lower(std::string& str); // reserved name for future complete UTF-8 implementation
std::string& lower_ascii(std::string& str);
std::string& lower_asciiExt(std::string& str);

// std::string& upper(std::string& str); // reserved name for future complete UTF-8 implementation
std::string& upper_ascii(std::string& str);
std::string& upper_asciiExt(std::string& str);

// std::string toLower(const std::string& str); // reserved name for future complete UTF-8 implementation
std::string toLower_ascii(const std::string& str);
std::string toLower_asciiExt(const std::string& str);

// std::string toUpper(const std::string& str); // reserved name for future complete UTF-8 implementation
std::string toUpper_ascii(const std::string& str);
std::string toUpper_asciiExt(const std::string& str);

/// @}



//! \name Find and Replace
/// @{
inline OMW_STDSTRING_CONSTEXPR bool contains(const std::string& str, char ch) { return (str.find(ch) != std::string::npos); }
inline OMW_STDSTRING_CONSTEXPR bool contains(const std::string& str, const char* s) { return (str.find(s) != std::string::npos); }
#if (OMW_CPPSTD < OMW_CPPSTD_17)
inline OMW_STDSTRING_CONSTEXPR bool contains(const std::string& str, const std::string& s) { return (str.find(s) != std::string::npos); }
#else
inline OMW_STDSTRING_CONSTEXPR bool contains(const std::string& str, const std::string_view& sv) { return (str.find(sv) != std::string::npos); }
#endif

std::string& replaceFirst(std::string& str, const std::string& search, const std::string& replace, std::string::size_type startPos = 0);
inline std::string& replaceFirst(std::string& str, const omw::StringReplacePair& pair, std::string::size_type startPos = 0)
{
    return omw::replaceFirst(str, pair.search(), pair.replace(), startPos);
}

std::string& replaceAll(std::string& str, char search, char replace, std::string::size_type startPos = 0, size_t* nReplacements = nullptr);
std::string& replaceAll(std::string& str, char search, const std::string& replace, std::string::size_type startPos = 0, size_t* nReplacements = nullptr);
std::string& replaceAll(std::string& str, const std::string& search, char replace, std::string::size_type startPos = 0, size_t* nReplacements = nullptr);
std::string& replaceAll(std::string& str, const std::string& search, const std::string& replace, std::string::size_type startPos = 0,
                        size_t* nReplacements = nullptr);
std::string& replaceAll(std::string& str, const omw::StringReplacePair& pair, std::string::size_type startPos = 0, size_t* nReplacements = nullptr);
std::string& replaceAll(std::string& str, const std::vector<omw::StringReplacePair>& pairs, std::string::size_type startPos = 0,
                        size_t* nReplacementsTotal = nullptr, std::vector<size_t>* nReplacements = nullptr);
std::string& replaceAll(std::string& str, const omw::StringReplacePair* pairs, size_t count, std::string::size_type startPos = 0,
                        size_t* nReplacementsTotal = nullptr, std::vector<size_t>* nReplacements = nullptr);
/// @}



//! \name Convert To String
/// @{
inline std::string toString(int32_t value) { return std::to_string(value); }
inline std::string toString(uint32_t value) { return std::to_string(value); }
inline std::string toString(int64_t value) { return std::to_string(value); }
inline std::string toString(uint64_t value) { return std::to_string(value); }
inline std::string toString(float value) { return std::to_string(value); }
inline std::string toString(double value) { return std::to_string(value); }
inline std::string toString(long double value) { return std::to_string(value); }

std::string toString(bool value, bool asText = true);
std::string toString(const omw::int128_t& value);
std::string toString(const omw::uint128_t& value);
std::string toString(const std::pair<int32_t, int32_t>& value, char delimiter = pairtos_defaultDelimiter);
std::string toString(const std::pair<uint32_t, uint32_t>& value, char delimiter = pairtos_defaultDelimiter);
std::string toString(const std::pair<int64_t, int64_t>& value, char delimiter = pairtos_defaultDelimiter);
std::string toString(const std::pair<uint64_t, uint64_t>& value, char delimiter = pairtos_defaultDelimiter);
std::string toString(const std::pair<float, float>& value, char delimiter = pairtos_defaultDelimiter);
std::string toString(const std::pair<double, double>& value, char delimiter = pairtos_defaultDelimiter);
std::string toString(const std::pair<long double, long double>& value, char delimiter = pairtos_defaultDelimiter);
/// @}


//! \name Convert From String
/// @{
bool stob(const std::string& str);

size_t stoz(const std::string& str, size_t* pos = nullptr, int base = 10);

std::pair<int32_t, int32_t> stoipair(const std::string& str, char delimiter = pairtos_defaultDelimiter);
// std::pair<uint32_t, uint32_t> stouipair(const std::string& str, char delimiter = pairtos_defaultDelimiter);
// std::pair<int64_t, int64_t> stoi64pair(const std::string& str, char delimiter = pairtos_defaultDelimiter);
// std::pair<uint64_t, uint64_t> stoui64pair(const std::string& str, char delimiter = pairtos_defaultDelimiter);
// std::pair<float, float> stofpair(const std::string& str, char delimiter = pairtos_defaultDelimiter);
std::pair<double, double> stodpair(const std::string& str, char delimiter = pairtos_defaultDelimiter);
// std::pair<long double, long double> stoldpair(const std::string& str, char delimiter = pairtos_defaultDelimiter);

// omw::int128_t stoi128(const std::string& str);
// omw::uint128_t stoui128(const std::string& str);
/// @}



//! \name Hex Strings
/// @{
std::string toHexStr(int8_t value);
std::string toHexStr(uint8_t value);
std::string toHexStr(int16_t value);
std::string toHexStr(uint16_t value);
std::string toHexStr(int32_t value);
std::string toHexStr(uint32_t value);
std::string toHexStr(int64_t value);
std::string toHexStr(uint64_t value);
std::string toHexStr(const omw::Base_Int128& value);
std::string toHexStr(int16_t value, char delimiter);
std::string toHexStr(uint16_t value, char delimiter);
std::string toHexStr(int32_t value, char delimiter);
std::string toHexStr(uint32_t value, char delimiter);
std::string toHexStr(int64_t value, char delimiter);
std::string toHexStr(uint64_t value, char delimiter);
std::string toHexStr(const omw::Base_Int128& value, char delimiter);
std::string toHexStr(const std::vector<char>& data, char delimiter = toHexStr_defaultDelimiter);
std::string toHexStr(const std::vector<uint8_t>& data, char delimiter = toHexStr_defaultDelimiter);
std::string toHexStr(const char* data, size_t count, char delimiter = toHexStr_defaultDelimiter);
std::string toHexStr(const uint8_t* data, size_t count, char delimiter = toHexStr_defaultDelimiter);

int32_t hexstoi(const std::string& str);
int64_t hexstoi64(const std::string& str);
omw::int128_t hexstoi128(const std::string& str);
uint32_t hexstoui(const std::string& str);
uint64_t hexstoui64(const std::string& str);
omw::uint128_t hexstoui128(const std::string& str);
std::vector<uint8_t> hexstovector(const std::string& str, char delimiter = toHexStr_defaultDelimiter);

std::string sepHexStr(const std::string& str);
std::string sepHexStr(const std::string& str, char delimiter);
std::string sepHexStr(const std::string& str, char rmChar, char delimiter);
std::string sepHexStr(const std::string& str, const char* rmChars, size_t count, char delimiter = toHexStr_defaultDelimiter);
std::string sepHexStr(const std::string& str, const std::vector<char>& rmChars, char delimiter = toHexStr_defaultDelimiter);
// std::string sepHexStr(const std::string& str, const char* rmString, char delimiter = toHexStr_defaultDelimiter);
// std::string sepHexStr(const std::string& str, const std::string& rmString, char delimiter = toHexStr_defaultDelimiter);
// std::string sepHexStr(const std::string& str, const std::string* rmStrings, size_t count, char delimiter = toHexStr_defaultDelimiter);
// std::string sepHexStr(const std::string& str, const std::string* rmStrings, size_t count, char delimiter = toHexStr_defaultDelimiter);
// std::string sepHexStr(const std::string& str, const omw::stdStringVector_t& rmStrings, char delimiter = toHexStr_defaultDelimiter);
// std::string sepHexStr(const std::string& str, const omw::stringVector_t& rmStrings, char delimiter = toHexStr_defaultDelimiter);

std::string rmNonHex(const std::string& str);
void rmNonHex(char* str);
void rmNonHex(std::string& str);
/// @}



omw::StringVector split(const std::string& str, char delimiter, omw::StringVector::size_type maxTokenCount = omw::StringVector_npos);

static inline omw::StringVector split(const char* str, char delimiter, omw::StringVector::size_type maxTokenCount = omw::StringVector_npos)
{
    return (str ? omw::split(std::string(str), delimiter, maxTokenCount) : omw::StringVector());
}



omw::StringVector split(const std::string& str, const std::string& delimiter, omw::StringVector::size_type maxTokenCount = omw::StringVector_npos);

static inline omw::StringVector split(const std::string& str, const char* delimiter, omw::StringVector::size_type maxTokenCount = omw::StringVector_npos)
{
    return (delimiter ? omw::split(str, std::string(delimiter), maxTokenCount) : omw::StringVector(1, str));
}

static inline omw::StringVector split(const char* str, const std::string& delimiter, omw::StringVector::size_type maxTokenCount = omw::StringVector_npos)
{
    return (str ? omw::split(std::string(str), delimiter, maxTokenCount) : omw::StringVector());
}

static inline omw::StringVector split(const char* str, const char* delimiter, omw::StringVector::size_type maxTokenCount = omw::StringVector_npos)
{
    return (str ? omw::split(std::string(str), delimiter, maxTokenCount) : omw::StringVector());
}



omw::StringVector splitLen(const std::string& str, std::string::size_type tokenLength, omw::StringVector::size_type maxTokenCount = omw::StringVector_npos);

static inline omw::StringVector splitLen(const char* str, std::string::size_type tokenLength,
                                         omw::StringVector::size_type maxTokenCount = omw::StringVector_npos)
{
    return (str ? omw::splitLen(std::string(str), tokenLength, maxTokenCount) : omw::StringVector());
}



// TODO check overloads
// omw::string join(const std::string* strings, size_t count, char delimiter = '\0');
// omw::string join(const std::string* strings, size_t count, const char* delimiter);
// omw::string join(const std::string* strings, size_t count, const std::string& delimiter);
// omw::string join(const omw::stdStringVector_t& strings);
// omw::string join(const omw::stdStringVector_t& strings, char delimiter);
// omw::string join(const omw::stdStringVector_t& strings, const char* delimiter);
// omw::string join(const omw::stdStringVector_t& strings, const std::string& delimiter);
// omw::string join(const omw::stringVector_t& strings);
std::string join(const omw::StringVector& strings);
std::string join(const omw::StringVector& strings, char delimiter);
// omw::string join(const omw::stringVector_t& strings, const char* delimiter);
// omw::string join(const omw::stringVector_t& strings, const std::string& delimiter);



// bool isValidUTF8(const std::string& str);



//! \name Character Classification
/// @{
constexpr bool isBlank(char ch) { return ((ch == 0x09) || (ch == 0x20)); }
constexpr bool isCntrl(char ch) { return (((ch >= 0x00) && (ch <= 0x1F)) || (ch == 0x7F)); }
constexpr bool isDigit(char ch) { return ((ch >= 0x30) && (ch <= 0x39)); }
constexpr bool isGraph(char ch) { return ((ch >= 0x21) && (ch <= 0x7E)); }
constexpr bool isHex(char ch)
{
    // clang-format off
    return (
            ((ch >= 0x30) && (ch <= 0x39)) ||
            ((ch >= 0x41) && (ch <= 0x46)) ||
            ((ch >= 0x61) && (ch <= 0x66))
        );
    // clang-format on
}
constexpr bool isLower(char ch) { return ((ch >= 0x61) && (ch <= 0x7A)); }
constexpr bool isNull(char ch) { return (ch == 0x00); }
constexpr bool isPrint(char ch) { return ((ch >= 0x20) && (ch <= 0x7E)); }
constexpr bool isPunct(char ch)
{
    // clang-format off
    return (
            ((ch >= 0x21) && (ch <= 0x2F)) ||
            ((ch >= 0x3A) && (ch <= 0x40)) ||
            ((ch >= 0x5B) && (ch <= 0x60)) ||
            ((ch >= 0x7B) && (ch <= 0x7E))
        );
    // clang-format on
}
constexpr bool isSpace(char ch) { return (((ch >= 0x09) && (ch <= 0x0D)) || (ch == 0x20)); }
constexpr bool isUpper(char ch) { return ((ch >= 0x41) && (ch <= 0x5A)); }
constexpr bool isAlpha(char ch) { return (isLower(ch) || isUpper(ch)); }
constexpr bool isAlnum(char ch) { return (isAlpha(ch) || isDigit(ch)); }

// same for UTF-8:
// bool is...(const char* utf8); // utf8 = UTF-8 byte string (e.g. "\xC3\xA4")
/// @}

//! \name String Classification
/// @{
bool isInteger(const std::string& str);
bool isUInteger(const std::string& str);
bool isFloat(const std::string& str, char decimalPoint = '.');
bool isHex(const std::string& str, std::string::size_type pos = 0, std::string::size_type count = std::string::npos);
/// @}

size_t peekNewLine(const char* p);
size_t peekNewLine(const char* p, const char* end);

std::string readString(const uint8_t* data, size_t count);
std::string readString(const std::vector<uint8_t>& data, std::vector<uint8_t>::size_type pos, std::vector<uint8_t>::size_type count);
void writeString(uint8_t* buffer, const uint8_t* end, const std::string& str);
void writeString(std::vector<uint8_t>& buffer, std::vector<uint8_t>::size_type pos, const std::string& str);



/*! @} */

} // namespace omw


#endif // IG_OMW_STRING_H
