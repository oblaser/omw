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

namespace omw
{
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



    using stdStringVector_t = std::vector<std::string>;
    constexpr omw::stdStringVector_t::size_type stdStringVector_npos = static_cast<omw::stdStringVector_t::size_type>(-1);

    class string;
    using stringVector_t = std::vector<omw::string>;
    constexpr omw::stringVector_t::size_type stringVector_npos = static_cast<omw::stringVector_t::size_type>(-1);



    class StringReplacePair
    {
    public:
        StringReplacePair() : m_s(), m_r() {}
        StringReplacePair(const std::string& searchElement, const std::string& replaceElement) : m_s(searchElement), m_r(replaceElement) {}
        StringReplacePair(const char searchElement, const std::string& replaceElement) : m_s(1, searchElement), m_r(replaceElement) {}
        StringReplacePair(const std::string& searchElement, const char replaceElement) : m_s(searchElement), m_r(1, replaceElement) {}
        StringReplacePair(const char searchElement, const char replaceElement) : m_s(1, searchElement), m_r(1, replaceElement) {}
        virtual ~StringReplacePair() {}

        const std::string& search() const { return m_s; }
        const std::string& replace() const { return m_r; }

    private:
        std::string m_s;
        std::string m_r;
    };



    //! \name omw::string Implementation Functions
    /// @{
    inline OMW_STDSTRING_CONSTEXPR bool contains(const std::string& str, char ch) { return (str.find(ch) != std::string::npos); }
    inline OMW_STDSTRING_CONSTEXPR bool contains(const std::string& str, const char* s) { return (str.find(s) != std::string::npos); }
#if (OMW_CPPSTD < OMW_CPPSTD_17)
    inline OMW_STDSTRING_CONSTEXPR bool contains(const std::string& str, const std::string& s) { return (str.find(s) != std::string::npos); }
#else
    inline OMW_STDSTRING_CONSTEXPR bool contains(const std::string& str, const std::string_view& sv) { return (str.find(sv) != std::string::npos); }
#endif

    omw::stringVector_t split(const std::string& str, char delimiter, omw::stringVector_t::size_type maxTokenCount = omw::stringVector_npos);
    static inline omw::stringVector_t split(const char* str, char delimiter, omw::stringVector_t::size_type maxTokenCount = omw::stringVector_npos) { return (str ? omw::split(std::string(str), delimiter, maxTokenCount) : omw::stringVector_t()); }
    omw::stringVector_t splitLen(const std::string& str, std::string::size_type tokenLength, omw::stringVector_t::size_type maxTokenCount = omw::stringVector_npos);
    static inline omw::stringVector_t splitLen(const char* str, std::string::size_type tokenLength, omw::stringVector_t::size_type maxTokenCount = omw::stringVector_npos) { return (str ? omw::splitLen(std::string(str), tokenLength, maxTokenCount) : omw::stringVector_t()); }
    /// @}



    class string : public std::string
    {
    public:
        string();
        string(omw::string::size_type count, char c);
        string(const char* str);
        string(const char* str, omw::string::size_type count);
        string(const std::string& other);
        string(const std::string& other, std::string::size_type pos, std::string::size_type count = std::string::npos);
        string(const char* first, const char* last);
        ~string() {}

        std::string& std();
        const std::string& std() const;

#ifndef OMWi_DOXYGEN_PREDEFINE
#if (OMW_CPPSTD < OMW_CPPSTD_23)
        bool contains(char ch) const { return (this->find(ch) != omw::string::npos); }
        bool contains(const char* str) const { return (this->find(str) != omw::string::npos); }
#if (OMW_CPPSTD < OMW_CPPSTD_17)
        bool contains(const std::string& str) const { return (this->find(str) != omw::string::npos); }
#else // < C++17
        bool contains(std::string_view sv) const { return (this->find(sv) != omw::string::npos); }
#endif // < C++17
#endif // < C++23
#else // OMWi_DOXYGEN_PREDEFINE
        bool contains(char ch) const;
        bool contains(const char* str) const;
        bool contains(const std::string& str) const;
        bool contains(std::string_view sv) const;
#endif // OMWi_DOXYGEN_PREDEFINE

        omw::string& replaceFirst(const std::string& search, const std::string& replace, size_type startPos = 0);
        omw::string& replaceFirst(const omw::StringReplacePair& pair, size_type startPos = 0);

        omw::string& replaceAll(char search, char replace, size_type startPos = 0, size_t* nReplacements = nullptr);
        omw::string& replaceAll(char search, const std::string& replace, size_type startPos = 0, size_t* nReplacements = nullptr);
        omw::string& replaceAll(const std::string& search, char replace, size_type startPos = 0, size_t* nReplacements = nullptr);
        omw::string& replaceAll(const std::string& search, const std::string& replace, size_type startPos = 0, size_t* nReplacements = nullptr);
        omw::string& replaceAll(const omw::StringReplacePair& pair, size_type startPos = 0, size_t* nReplacements = nullptr);
        omw::string& replaceAll(const std::vector<omw::StringReplacePair>& pairs, size_type startPos = 0, size_t* nReplacementsTotal = nullptr, std::vector<size_t>* nReplacements = nullptr);
        omw::string& replaceAll(const omw::StringReplacePair* pairs, size_t count, size_type startPos = 0, size_t* nReplacementsTotal = nullptr, std::vector<size_t>* nReplacements = nullptr);

        omw::string& reverse();
        omw::string reversed() const;

        omw::stringVector_t split(char delimiter, omw::stringVector_t::size_type maxTokenCount = omw::stringVector_npos) const;
        //omw::stringVector_t split(const char* delimiter, omw::stringVector_t::size_type maxTokenCount = omw::stringVector_npos) const;
        //omw::stringVector_t split(const std::string& delimiter, omw::stringVector_t::size_type maxTokenCount = omw::stringVector_npos) const;
        omw::stringVector_t splitLen(omw::string::size_type tokenLength, omw::stringVector_t::size_type maxTokenCount = omw::stringVector_npos) const;

        //! \name Case Conversion
        //! Methods named `.._ascii` convert only A-Z and a-z. Those named `.._asciiExt` additionally convert some UTF-8 code points.
        /// @{
        //omw::string& lower(); // reserved name
        omw::string& lower_ascii();
        omw::string& lower_asciiExt();
        //omw::string& upper(); // reserved name
        omw::string& upper_ascii();
        omw::string& upper_asciiExt();
        //omw::string toLower() const; // reserved name
        omw::string toLower_ascii() const;
        omw::string toLower_asciiExt() const;
        //omw::string toUpper() const; // reserved name
        omw::string toUpper_ascii() const;
        omw::string toUpper_asciiExt() const;
        /// @}
    };



    //! \name Find and Replace
    /// @{
    std::string& replaceFirst(std::string& str, const std::string& search, const std::string& replace, std::string::size_type startPos = 0);
    inline std::string& replaceFirst(std::string& str, const omw::StringReplacePair& pair, std::string::size_type startPos = 0) { return omw::replaceFirst(str, pair.search(), pair.replace(), startPos); }

    std::string& replaceAll(std::string& str, char search, char replace, std::string::size_type startPos = 0, size_t* nReplacements = nullptr);
    std::string& replaceAll(std::string& str, char search, const std::string& replace, std::string::size_type startPos = 0, size_t* nReplacements = nullptr);
    std::string& replaceAll(std::string& str, const std::string& search, char replace, std::string::size_type startPos = 0, size_t* nReplacements = nullptr);
    std::string& replaceAll(std::string& str, const std::string& search, const std::string& replace, std::string::size_type startPos = 0, size_t* nReplacements = nullptr);
    std::string& replaceAll(std::string& str, const omw::StringReplacePair& pair, std::string::size_type startPos = 0, size_t* nReplacements = nullptr);
    std::string& replaceAll(std::string& str, const std::vector<omw::StringReplacePair>& pairs, std::string::size_type startPos = 0, size_t* nReplacementsTotal = nullptr, std::vector<size_t>* nReplacements = nullptr);
    std::string& replaceAll(std::string& str, const omw::StringReplacePair* pairs, size_t count, std::string::size_type startPos = 0, size_t* nReplacementsTotal = nullptr, std::vector<size_t>* nReplacements = nullptr);
    /// @}



    //! \name Convert To String
    /// @{
    inline omw::string to_string(int32_t value) { return std::to_string(value); }
    inline omw::string to_string(uint32_t value) { return std::to_string(value); }
    inline omw::string to_string(int64_t value) { return std::to_string(value); }
    inline omw::string to_string(uint64_t value) { return std::to_string(value); }
    inline omw::string to_string(float value) { return std::to_string(value); }
    inline omw::string to_string(double value) { return std::to_string(value); }
    inline omw::string to_string(long double value) { return std::to_string(value); }

    omw::string to_string(bool value, bool asText = true);
    omw::string to_string(const omw::int128_t& value);
    omw::string to_string(const omw::uint128_t& value);
    omw::string to_string(const std::pair<int32_t, int32_t>& value, char delimiter = pairtos_defaultDelimiter);
    omw::string to_string(const std::pair<uint32_t, uint32_t>& value, char delimiter = pairtos_defaultDelimiter);
    omw::string to_string(const std::pair<int64_t, int64_t>& value, char delimiter = pairtos_defaultDelimiter);
    omw::string to_string(const std::pair<uint64_t, uint64_t>& value, char delimiter = pairtos_defaultDelimiter);
    omw::string to_string(const std::pair<float, float>& value, char delimiter = pairtos_defaultDelimiter);
    omw::string to_string(const std::pair<double, double>& value, char delimiter = pairtos_defaultDelimiter);
    omw::string to_string(const std::pair<long double, long double>& value, char delimiter = pairtos_defaultDelimiter);
    /// @}


    //! \name Convert From String
    /// @{
    bool stob(const std::string& str);

    size_t stoz(const std::string& str, size_t* pos = nullptr, int base = 10);

    std::pair<int32_t, int32_t> stoipair(const std::string& str, char delimiter = pairtos_defaultDelimiter);
    //std::pair<uint32_t, uint32_t> stouipair(const std::string& str, char delimiter = pairtos_defaultDelimiter);
    //std::pair<int64_t, int64_t> stoi64pair(const std::string& str, char delimiter = pairtos_defaultDelimiter);
    //std::pair<uint64_t, uint64_t> stoui64pair(const std::string& str, char delimiter = pairtos_defaultDelimiter);
    //std::pair<float, float> stofpair(const std::string& str, char delimiter = pairtos_defaultDelimiter);
    std::pair<double, double> stodpair(const std::string& str, char delimiter = pairtos_defaultDelimiter);
    //std::pair<long double, long double> stoldpair(const std::string& str, char delimiter = pairtos_defaultDelimiter);

    //omw::int128_t stoi128(const std::string& str);
    //omw::uint128_t stoui128(const std::string& str);
    /// @}



    //! \name Hex Strings
    /// @{
    omw::string toHexStr(int8_t value);
    omw::string toHexStr(uint8_t value);
    omw::string toHexStr(int16_t value);
    omw::string toHexStr(uint16_t value);
    omw::string toHexStr(int32_t value);
    omw::string toHexStr(uint32_t value);
    omw::string toHexStr(int64_t value);
    omw::string toHexStr(uint64_t value);
    omw::string toHexStr(const omw::Base_Int128& value);
    omw::string toHexStr(int16_t value, char delimiter);
    omw::string toHexStr(uint16_t value, char delimiter);
    omw::string toHexStr(int32_t value, char delimiter);
    omw::string toHexStr(uint32_t value, char delimiter);
    omw::string toHexStr(int64_t value, char delimiter);
    omw::string toHexStr(uint64_t value, char delimiter);
    omw::string toHexStr(const omw::Base_Int128& value, char delimiter);
    omw::string toHexStr(const std::vector<char>& data, char delimiter = toHexStr_defaultDelimiter);
    omw::string toHexStr(const std::vector<uint8_t>& data, char delimiter = toHexStr_defaultDelimiter);
    omw::string toHexStr(const char* data, size_t count, char delimiter = toHexStr_defaultDelimiter);
    omw::string toHexStr(const uint8_t* data, size_t count, char delimiter = toHexStr_defaultDelimiter);

    int32_t hexstoi(const std::string& str);
    int64_t hexstoi64(const std::string& str);
    omw::int128_t hexstoi128(const std::string& str);
    uint32_t hexstoui(const std::string& str);
    uint64_t hexstoui64(const std::string& str);
    omw::uint128_t hexstoui128(const std::string& str);
    std::vector<uint8_t> hexstovector(const std::string& str, char delimiter = toHexStr_defaultDelimiter);

    omw::string sepHexStr(const std::string& str);
    omw::string sepHexStr(const std::string& str, char delimiter);
    omw::string sepHexStr(const std::string& str, char rmChar, char delimiter);
    omw::string sepHexStr(const std::string& str, const char* rmChars, size_t count, char delimiter = toHexStr_defaultDelimiter);
    omw::string sepHexStr(const std::string& str, const std::vector<char>& rmChars, char delimiter = toHexStr_defaultDelimiter);
    //omw::string sepHexStr(const std::string& str, const char* rmString, char delimiter = toHexStr_defaultDelimiter);
    //omw::string sepHexStr(const std::string& str, const std::string& rmString, char delimiter = toHexStr_defaultDelimiter);
    //omw::string sepHexStr(const std::string& str, const std::string* rmStrings, size_t count, char delimiter = toHexStr_defaultDelimiter);
    //omw::string sepHexStr(const std::string& str, const omw::string* rmStrings, size_t count, char delimiter = toHexStr_defaultDelimiter);
    //omw::string sepHexStr(const std::string& str, const omw::stdStringVector_t& rmStrings, char delimiter = toHexStr_defaultDelimiter);
    //omw::string sepHexStr(const std::string& str, const omw::stringVector_t& rmStrings, char delimiter = toHexStr_defaultDelimiter);

    omw::string rmNonHex(const std::string& str);
    void rmNonHex(char* str);
    void rmNonHex(std::string& str);
    /// @}



    // TODO check overloads
    //omw::string join(const std::string* strings, size_t count, char delimiter = '\0');
    //omw::string join(const std::string* strings, size_t count, const char* delimiter);
    //omw::string join(const std::string* strings, size_t count, const std::string& delimiter);
    //omw::string join(const omw::stdStringVector_t& strings);
    //omw::string join(const omw::stdStringVector_t& strings, char delimiter);
    //omw::string join(const omw::stdStringVector_t& strings, const char* delimiter);
    //omw::string join(const omw::stdStringVector_t& strings, const std::string& delimiter);
    //omw::string join(const omw::stringVector_t& strings);
    omw::string join(const omw::stringVector_t& strings);
    omw::string join(const omw::stringVector_t& strings, char delimiter);
    //omw::string join(const omw::stringVector_t& strings, const char* delimiter);
    //omw::string join(const omw::stringVector_t& strings, const std::string& delimiter);



    //! \name String Vectors
    /// @{
    omw::stringVector_t stringVector(const char* const* strings, size_t count);
    omw::stringVector_t stringVector(const std::string* strings, size_t count);
    omw::stringVector_t stringVector(const omw::string* strings, size_t count);
    omw::stringVector_t stringVector(const omw::stdStringVector_t& strvec);

    omw::stdStringVector_t stdStringVector(const char* const* strings, size_t count);
    omw::stdStringVector_t stdStringVector(const std::string* strings, size_t count);
    omw::stdStringVector_t stdStringVector(const omw::string* strings, size_t count);
    omw::stdStringVector_t stdStringVector(const omw::stringVector_t& strvec);
    /// @}



    //bool isValidUTF8(const std::string& str);



    //! \name Character Classification
    /// @{
    constexpr bool isBlank(char ch) { return ((ch == 0x09) || (ch == 0x20)); }
    constexpr bool isCntrl(char ch) { return (((ch >= 0x00) && (ch <= 0x1F)) || (ch == 0x7F)); }
    constexpr bool isDigit(char ch) { return ((ch >= 0x30) && (ch <= 0x39)); }
    constexpr bool isGraph(char ch) { return ((ch >= 0x21) && (ch <= 0x7E)); }
    constexpr bool isHex(char ch)
    {
        return (((ch >= 0x30) && (ch <= 0x39)) || ((ch >= 0x41) && (ch <= 0x46)) ||
            ((ch >= 0x61) && (ch <= 0x66)));
    }
    constexpr bool isLower(char ch) { return ((ch >= 0x61) && (ch <= 0x7A)); }
    constexpr bool isNull(char ch) { return (ch == 0x00); }
    constexpr bool isPrint(char ch) { return ((ch >= 0x20) && (ch <= 0x7E)); }
    constexpr bool isPunct(char ch)
    {
        return (((ch >= 0x21) && (ch <= 0x2F)) || ((ch >= 0x3A) && (ch <= 0x40)) ||
            ((ch >= 0x5B) && (ch <= 0x60)) || ((ch >= 0x7B) && (ch <= 0x7E)));
    }
    constexpr bool isSpace(char ch) { return (((ch >= 0x09) && (ch <= 0x0D)) || (ch == 0x20)); }
    constexpr bool isUpper(char ch) { return ((ch >= 0x41) && (ch <= 0x5A)); }
    constexpr bool isAlpha(char ch) { return (isLower(ch) || isUpper(ch)); }
    constexpr bool isAlnum(char ch) { return (isAlpha(ch) || isDigit(ch)); }

    // same for UTF-8:
    //bool is...(const char* utf8); // utf8 = UTF-8 byte string (e.g. "\xC3\xA4")
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

    omw::string readString(const uint8_t* data, size_t count);
    omw::string readString(const std::vector<uint8_t>& data, std::vector<uint8_t>::size_type pos, std::vector<uint8_t>::size_type count);
    void writeString(uint8_t* buffer, const uint8_t* end, const std::string& str);
    void writeString(std::vector<uint8_t>& buffer, std::vector<uint8_t>::size_type pos, const std::string& str);



    /*! @} */
}

#endif // IG_OMW_STRING_H
