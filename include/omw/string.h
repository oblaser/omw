/*
author         Oliver Blaser
date           14.09.2021
copyright      MIT - Copyright (c) 2021 Oliver Blaser
*/

#ifndef OMW_STRING_H
#define OMW_STRING_H

#include <cstdint>
#include <string>
#include <utility>
#include <vector>

namespace omw
{
    /*! \addtogroup grp_stringsLib
    * @{
    */

    //! \name UTF-8 Code Points
    /// @{
    const char* const UTF8CP_00C4 = "\xC3\x84";
    const char* const UTF8CP_00D6 = "\xC3\x96";
    const char* const UTF8CP_00DC = "\xC3\x9C";
    const char* const UTF8CP_00E4 = "\xC3\xA4";
    const char* const UTF8CP_00F6 = "\xC3\xB6";
    const char* const UTF8CP_00FC = "\xC3\xBC";
    /// @}

    //! \name UFT-8 Code Point Aliases
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
        string(const char* str);
        string(const char* str, size_type count);
        string(const std::string& other, size_type pos = 0, size_type count = npos);
        string(const char* first, const char* last);
        virtual ~string() {}

        omw::string& replaceFirst(const omw::string& search, const omw::string& replace, size_type startPos = 0);
        omw::string& replaceFirst(const omw::StringReplacePair& pair, size_type startPos = 0);

        omw::string& replaceAll(const omw::string& search, const omw::string& replace, size_type startPos = 0, size_type* nReplacements = nullptr);
        omw::string& replaceAll(const omw::StringReplacePair& pair, size_type startPos = 0, size_type* nReplacements = nullptr);
        omw::string& replaceAll(const std::vector<omw::StringReplacePair>& pairs, size_type startPos = 0, size_type* nReplacementsTotal = nullptr, std::vector<size_type>* nReplacements = nullptr);
        omw::string& replaceAll(const omw::StringReplacePair* pairsBegin, const omw::StringReplacePair* pairsEnd, size_type startPos = 0, size_type* nReplacementsTotal = nullptr, std::vector<size_type>* nReplacements = nullptr);

        //! \name Case Conversion
        //! Methods named `.._ascii` convert only A-Z and a-z. Those named `.._asciiExt` additionally convert some UTF-8 code points too.
        /// @{
        omw::string& lower_ascii();
        omw::string& lower_asciiExt();
        omw::string& upper_ascii();
        omw::string& upper_asciiExt();
        omw::string toLower_ascii() const;
        omw::string toLower_asciiExt() const;
        omw::string toUpper_ascii() const;
        omw::string toUpper_asciiExt() const;
        /// @}

        omw::string& encodeUrl();
        omw::string toUrlEncoded() const;
    };



    omw::string to_string(bool value, bool textual = true);

    template<typename T1, typename T2>
    omw::string to_string(const std::pair<T1, T2>& value, char sepChar = pairtos_defaultSepChar);

    template omw::string to_string(const std::pair<int32_t, int32_t>&, char);
    template omw::string to_string(const std::pair<int64_t, int64_t>&, char);
    template omw::string to_string(const std::pair<uint32_t, uint32_t>&, char);
    template omw::string to_string(const std::pair<uint64_t, uint64_t>&, char);
    template omw::string to_string(const std::pair<float, float>&, char);
    template omw::string to_string(const std::pair<double, double>&, char);
    template omw::string to_string(const std::pair<long double, long double>&, char);



    bool stob(const omw::string& boolStr);
    std::pair<int32_t, int32_t> stoipair(const omw::string& str, char sepChar = pairtos_defaultSepChar);
    //std::pair<int64_t, int64_t> stoi64pair(const omw::string& str, char sepChar = pairtos_defaultSepChar);
    //std::pair<uint32_t, uint32_t> stouipair(const omw::string& str, char sepChar = pairtos_defaultSepChar);
    //std::pair<uint64_t, uint64_t> stoui64pair(const omw::string& str, char sepChar = pairtos_defaultSepChar);
    //std::pair<float, float> stofpair(const omw::string& str, char sepChar = pairtos_defaultSepChar);
    //std::pair<double, double> stodpair(const omw::string& str, char sepChar = pairtos_defaultSepChar);
    //std::pair<long double, long double> stoldpair(const omw::string& str, char sepChar = pairtos_defaultSepChar);



    omw::string toHexStr(int8_t value);
    omw::string toHexStr(uint8_t value);
    omw::string toHexStr(int16_t value);
    omw::string toHexStr(uint16_t value);
    omw::string toHexStr(int32_t value);
    omw::string toHexStr(uint32_t value);
    omw::string toHexStr(int64_t value);
    omw::string toHexStr(uint64_t value);
    omw::string toHexStr(const std::vector<char>& data, char sepChar = toHexStr_defaultSepChar);
    omw::string toHexStr(const std::vector<uint8_t>& data, char sepChar = toHexStr_defaultSepChar);
    omw::string toHexStr(const char* data, omw::string::size_type count, char sepChar = toHexStr_defaultSepChar);
    omw::string toHexStr(const uint8_t* data, omw::string::size_type count, char sepChar = toHexStr_defaultSepChar);

    int32_t hexstoi(const omw::string& str);
    int64_t hexstoi64(const omw::string& str);
    uint32_t hexstoui(const omw::string& str);
    uint64_t hexstoui64(const omw::string& str);
    std::vector<uint8_t> hexstovector(const omw::string& str, char sepChar = toHexStr_defaultSepChar);



    //bool isValidUTF8(const omw::string& str);
    bool isInteger(const omw::string& str);
    bool isUInteger(const omw::string& str);
    bool isHex(const omw::string& str);

    /*! @} */
}

#endif // OMW_STRING_H
