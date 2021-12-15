/*
author          Oliver Blaser
date            15.12.2021
copyright       MIT - Copyright (c) 2021 Oliver Blaser
*/

#ifndef IG_OMW_STRING_H
#define IG_OMW_STRING_H

#include <cstdint>
#include <string>
#include <utility>
#include <vector>

#include "../omw/defs.h"
#include "../omw/int.h"


#ifndef OMWi_DOXYGEN_EXCLUDE_FROM_DOC
#define OMWi_STRING_IMPLEMENT_CONTAINS (1)
#if defined(_MSVC_LANG)
#if (_MSVC_LANG > 202002L)
#undef OMWi_STRING_IMPLEMENT_CONTAINS
#endif
#elif defined(__cplusplus)
#if (__cplusplus > 202100L)
#undef OMWi_STRING_IMPLEMENT_CONTAINS
#endif
#endif
#endif // OMWi_DOXYGEN_EXCLUDE_FROM_DOC


namespace omw
{
    /*! \addtogroup grp_stringLib
    * @{
    */

    //! \name UTF-8 Byte Strings
    /// @{
    const char* const UTF8CP_00C4 = "\xC3\x84";
    const char* const UTF8CP_00D6 = "\xC3\x96";
    const char* const UTF8CP_00DC = "\xC3\x9C";
    const char* const UTF8CP_00E4 = "\xC3\xA4";
    const char* const UTF8CP_00F6 = "\xC3\xB6";
    const char* const UTF8CP_00FC = "\xC3\xBC";
    const char* const UTF8CP_2580 = "\xE2\x96\x80";
    const char* const UTF8CP_2584 = "\xE2\x96\x84";
    const char* const UTF8CP_2588 = "\xE2\x96\x88";
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

    constexpr char pairtos_defaultSepChar = ';';
    const char* const hexStrDigitsUpper = "0123456789ABCDEF";
    const char* const hexStrDigitsLower = "0123456789abcdef";
    const char* const hexStrDigits = hexStrDigitsUpper;
    constexpr char toHexStr_defaultSepChar = 0x20;



    using stdStringVector_t = std::vector<std::string>;
    using stdStringVector_size_type = omw::stdStringVector_t::size_type;
    constexpr stdStringVector_size_type stdStringVector_npos = (omw::stdStringVector_size_type)-1;

    class string;
    using stringVector_t = std::vector<omw::string>;
    using stringVector_size_type = omw::stringVector_t::size_type;
    constexpr stringVector_size_type stringVector_npos = (omw::stringVector_size_type)-1;



    class StringReplacePair
    {
    public:
        StringReplacePair();
        StringReplacePair(const std::string& searchElement, const std::string& replaceElement);
        StringReplacePair(const char searchElement, const std::string& replaceElement);
        StringReplacePair(const std::string& searchElement, const char replaceElement);
        StringReplacePair(const char searchElement, const char replaceElement);
        virtual ~StringReplacePair() {}

        const std::string& search() const;
        const std::string& replace() const;

    private:
        std::string searchElem;
        std::string replaceElem;
    };

    class string : public std::string
    {
    public:
        string();
        string(std::string::size_type count, char c);
        string(const char* str);
        string(const char* str, std::string::size_type count);
        string(const std::string& other, std::string::size_type pos = 0, std::string::size_type count = std::string::npos);
        string(const char* first, const char* last);
        virtual ~string() {}

#ifdef OMWi_STRING_IMPLEMENT_CONTAINS
        bool contains(char ch) const;
        bool contains(const char* str) const;
        bool contains(const std::string& str) const;
#endif

        omw::string& replaceFirst(const std::string& search, const std::string& replace, size_type startPos = 0);
        omw::string& replaceFirst(const omw::StringReplacePair& pair, size_type startPos = 0);

        omw::string& replaceAll(char search, char replace, size_type startPos = 0, size_t* nReplacements = nullptr);
        omw::string& replaceAll(char search, const std::string& replace, size_type startPos = 0, size_t* nReplacements = nullptr);
        omw::string& replaceAll(const std::string& search, char replace, size_type startPos = 0, size_t* nReplacements = nullptr);
        omw::string& replaceAll(const std::string& search, const std::string& replace, size_type startPos = 0, size_t* nReplacements = nullptr);
        omw::string& replaceAll(const omw::StringReplacePair& pair, size_type startPos = 0, size_t* nReplacements = nullptr);
        omw::string& replaceAll(const std::vector<omw::StringReplacePair>& pairs, size_type startPos = 0, size_t* nReplacementsTotal = nullptr, std::vector<size_t>* nReplacements = nullptr);
        omw::string& replaceAll(const omw::StringReplacePair* pairs, size_t count, size_type startPos = 0, size_t* nReplacementsTotal = nullptr, std::vector<size_t>* nReplacements = nullptr);

        omw::stringVector_t split(omw::string::size_type tokenLength, omw::stringVector_size_type maxTokenCount = omw::stringVector_npos) const;
        //omw::stringVector_t split(char sepChar, omw::stringVector_size_type maxTokenCount = omw::stringVector_npos) const;
        //omw::stringVector_t split(const char* sepString, omw::stringVector_size_type maxTokenCount = omw::stringVector_npos) const;
        //omw::stringVector_t split(const std::string& sepString, omw::stringVector_size_type maxTokenCount = omw::stringVector_npos) const;

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

        omw::string& encodeUrl();
        omw::string toUrlEncoded() const;
    };



    //! \name Convert To String
    /// @{
    omw::string to_string(int32_t value);
    omw::string to_string(uint32_t value);
    omw::string to_string(int64_t value);
    omw::string to_string(uint64_t value);
    omw::string to_string(float value);
    omw::string to_string(double value);
    omw::string to_string(long double value);

    omw::string to_string(bool value, bool asText = true);
    omw::string to_string(const omw::int128_t& value);
    omw::string to_string(const omw::uint128_t& value);
    omw::string to_string(const std::pair<int32_t, int32_t>& value, char sepChar = pairtos_defaultSepChar);
    omw::string to_string(const std::pair<uint32_t, uint32_t>& value, char sepChar = pairtos_defaultSepChar);
    omw::string to_string(const std::pair<int64_t, int64_t>& value, char sepChar = pairtos_defaultSepChar);
    omw::string to_string(const std::pair<uint64_t, uint64_t>& value, char sepChar = pairtos_defaultSepChar);
    omw::string to_string(const std::pair<float, float>& value, char sepChar = pairtos_defaultSepChar);
    omw::string to_string(const std::pair<double, double>& value, char sepChar = pairtos_defaultSepChar);
    omw::string to_string(const std::pair<long double, long double>& value, char sepChar = pairtos_defaultSepChar);

    omw::string i128tos(int64_t valueH, uint64_t valueL);
    omw::string i128tos(int32_t valueHH, uint32_t valueLH, uint32_t valueHL, uint32_t valueLL);
    omw::string i128tos(const uint8_t* data, size_t count);
    omw::string ui128tos(uint64_t valueH, uint64_t valueL);
    omw::string ui128tos(uint32_t valueHH, uint32_t valueLH, uint32_t valueHL, uint32_t valueLL);
    omw::string ui128tos(const uint8_t* data, size_t count);
    /// @}


    //! \name Convert From String
    /// @{
    bool stob(const std::string& boolStr);
    std::pair<int32_t, int32_t> stoipair(const std::string& str, char sepChar = pairtos_defaultSepChar);
    //std::pair<uint32_t, uint32_t> stouipair(const std::string& str, char sepChar = pairtos_defaultSepChar);
    //std::pair<int64_t, int64_t> stoi64pair(const std::string& str, char sepChar = pairtos_defaultSepChar);
    //std::pair<uint64_t, uint64_t> stoui64pair(const std::string& str, char sepChar = pairtos_defaultSepChar);
    //std::pair<float, float> stofpair(const std::string& str, char sepChar = pairtos_defaultSepChar);
    //std::pair<double, double> stodpair(const std::string& str, char sepChar = pairtos_defaultSepChar);
    //std::pair<long double, long double> stoldpair(const std::string& str, char sepChar = pairtos_defaultSepChar);
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
    omw::string toHexStr(int16_t value, char sepChar);
    omw::string toHexStr(uint16_t value, char sepChar);
    omw::string toHexStr(int32_t value, char sepChar);
    omw::string toHexStr(uint32_t value, char sepChar);
    omw::string toHexStr(int64_t value, char sepChar);
    omw::string toHexStr(uint64_t value, char sepChar);
    omw::string toHexStr(const std::vector<char>& data, char sepChar = toHexStr_defaultSepChar);
    omw::string toHexStr(const std::vector<uint8_t>& data, char sepChar = toHexStr_defaultSepChar);
    omw::string toHexStr(const char* data, size_t count, char sepChar = toHexStr_defaultSepChar);
    omw::string toHexStr(const uint8_t* data, size_t count, char sepChar = toHexStr_defaultSepChar);

    int32_t hexstoi(const std::string& str);
    int64_t hexstoi64(const std::string& str);
    uint32_t hexstoui(const std::string& str);
    uint64_t hexstoui64(const std::string& str);
    std::vector<uint8_t> hexstovector(const std::string& str, char sepChar = toHexStr_defaultSepChar);

    omw::string sepHexStr(const std::string& str);
    omw::string sepHexStr(const std::string& str, char sepChar);
    omw::string sepHexStr(const std::string& str, char rmChar, char sepChar);
    omw::string sepHexStr(const std::string& str, const char* rmChars, size_t count, char sepChar = toHexStr_defaultSepChar);
    omw::string sepHexStr(const std::string& str, const std::vector<char>& rmChars, char sepChar = toHexStr_defaultSepChar);
    //omw::string sepHexStr(const std::string& str, const char* rmString, char sepChar = toHexStr_defaultSepChar);
    //omw::string sepHexStr(const std::string& str, const std::string& rmString, char sepChar = toHexStr_defaultSepChar);
    //omw::string sepHexStr(const std::string& str, const std::string* rmStrings, size_t count, char sepChar = toHexStr_defaultSepChar);
    //omw::string sepHexStr(const std::string& str, const omw::string* rmStrings, size_t count, char sepChar = toHexStr_defaultSepChar);
    //omw::string sepHexStr(const std::string& str, const omw::stdStringVector_t& rmStrings, char sepChar = toHexStr_defaultSepChar);
    //omw::string sepHexStr(const std::string& str, const omw::stringVector_t& rmStrings, char sepChar = toHexStr_defaultSepChar);

    omw::string rmNonHex(const std::string& str);
    void rmNonHex(char* str);
    void rmNonHex(std::string& str);
    /// @}



    // TODO check overloads
    //omw::string join(const std::string* strings, size_t count, char sepChar = '\0');
    //omw::string join(const std::string* strings, size_t count, const char* sepString);
    //omw::string join(const std::string* strings, size_t count, const std::string& sepString);
    //omw::string join(const omw::stdStringVector_t& strings);
    //omw::string join(const omw::stdStringVector_t& strings, char sepChar);
    //omw::string join(const omw::stdStringVector_t& strings, const char* sepString);
    //omw::string join(const omw::stdStringVector_t& strings, const std::string& sepString);
    //omw::string join(const omw::stringVector_t& strings);
    omw::string join(const omw::stringVector_t& strings);
    omw::string join(const omw::stringVector_t& strings, char sepChar);
    //omw::string join(const omw::stringVector_t& strings, const char* sepString);
    //omw::string join(const omw::stringVector_t& strings, const std::string& sepString);



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
    constexpr bool isWhitespace(char ch) { return isSpace(ch); }
    constexpr bool isAlpha(char ch) { return (isLower(ch) || isUpper(ch)); }
    constexpr bool isAlnum(char ch) { return (isAlpha(ch) || isDigit(ch)); }

    // same for UTF-8:
    //bool is...(const char* utf8cp); // utf8cp = UTF-8 code point (e.g. "\xC3\xA4")
    /// @}

    //! \name String Classification
    /// @{
    bool isInteger(const std::string& str);
    bool isUInteger(const std::string& str);
    bool isHex(const std::string& str);
    /// @}

    size_t peekNewLine(const char* p);
    size_t peekNewLine(const char* p, const char* end);



    /*! @} */
}

#endif // IG_OMW_STRING_H
