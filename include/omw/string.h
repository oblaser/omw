/*
author         Oliver Blaser
date           18.08.2021
copyright      MIT - Copyright (c) 2021 Oliver Blaser
*/

#ifndef OMW_STRING_H
#define OMW_STRING_H

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
    constexpr char UTF8CP_00C4[] = "\xC3\x84";
    constexpr char UTF8CP_00D6[] = "\xC3\x96";
    constexpr char UTF8CP_00DC[] = "\xC3\x9C";
    constexpr char UTF8CP_00E4[] = "\xC3\xA4";
    constexpr char UTF8CP_00F6[] = "\xC3\xB6";
    constexpr char UTF8CP_00FC[] = "\xC3\xBC";
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
    constexpr char hexStrDigits[] = "0123456789ABCDEF";
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
        //static bool isValidUTF8(const omw::string& str);

    public:
        string();
        string(const char* str);
        string(const std::string& str);
        string(const char* first, const char* last);
        virtual ~string() {}

        bool isInteger() const;
        bool isUInteger() const;

        omw::string& replaceFirst(const omw::string& search, const omw::string& replace, size_type startPos = 0);
        omw::string& replaceFirst(const omw::StringReplacePair& pair, size_type startPos = 0);

        omw::string& replaceAll(const omw::string& search, const omw::string& replace, size_type startPos = 0, size_type* nReplacements = nullptr);
        omw::string& replaceAll(const omw::StringReplacePair& pair, size_type startPos = 0, size_type* nReplacements = nullptr);
        omw::string& replaceAll(const std::vector<omw::StringReplacePair>& pairs, size_type startPos = 0, size_type* nReplacementsTotal = nullptr, std::vector<size_type>* nReplacements = nullptr);
        omw::string& replaceAll(const omw::StringReplacePair* pairsBegin, const omw::StringReplacePair* pairsEnd, size_type startPos = 0, size_type* nReplacementsTotal = nullptr, std::vector<size_type>* nReplacements = nullptr);

        //! \name Case Conversion
        //! Methods named `.._ascii` convert only A-Z and a-z. Those named `.._asciiExt` additionally convert some UTF-8 code points too.
        /// @{
        omw::string& makeLower_ascii();
        omw::string& makeLower_asciiExt();
        omw::string& makeUpper_ascii();
        omw::string& makeUpper_asciiExt();
        omw::string toLower_ascii() const;
        omw::string toLower_asciiExt() const;
        omw::string toUpper_ascii() const;
        omw::string toUpper_asciiExt() const;
        /// @}

        omw::string& makeUrlEncoded();
        omw::string toUrlEncoded() const;

        //bool isValidUTF8() const;
    };



    omw::string to_string(bool value, bool textual = false);

    template<typename T1, typename T2>
    std::string to_string(const std::pair<T1, T2>& value, char sepChar = pairtos_defaultSepChar);

    template std::string to_string(const std::pair<int, int>&, char);
    template std::string to_string(const std::pair<long, long>&, char);
    template std::string to_string(const std::pair<long long, long long>&, char);
    template std::string to_string(const std::pair<unsigned, unsigned>&, char);
    template std::string to_string(const std::pair<unsigned long, unsigned long>&, char);
    template std::string to_string(const std::pair<unsigned long long, unsigned long long>&, char);
    template std::string to_string(const std::pair<float, float>&, char);
    template std::string to_string(const std::pair<double, double>&, char);
    template std::string to_string(const std::pair<long double, long double>&, char);



    bool stob(const omw::string& boolStr);
    std::pair<int, int> stoipair(const std::string& str, char sepChar = pairtos_defaultSepChar);
    //std::pair<long, long> stolpair(const std::string& str, char sepChar = pairtos_defaultSepChar);
    //std::pair<long long, long long> stollpair(const std::string& str, char sepChar = pairtos_defaultSepChar);
    //std::pair<unsigned long, unsigned long> stoulpair(const std::string& str, char sepChar = pairtos_defaultSepChar);
    //std::pair<unsigned long long, unsigned long long> stoullpair(const std::string& str, char sepChar = pairtos_defaultSepChar);
    //std::pair<float, float> stofpair(const std::string& str, char sepChar = pairtos_defaultSepChar);
    //std::pair<double, double> stodpair(const std::string& str, char sepChar = pairtos_defaultSepChar);
    //std::pair<long double, long double> stoldpair(const std::string& str, char sepChar = pairtos_defaultSepChar);




    bool isInteger(const std::string& str);
    bool isUInteger(const std::string& str);



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
    omw::string toHexStr(const char* data, size_t count, char sepChar = toHexStr_defaultSepChar);
    omw::string toHexStr(const uint8_t* data, size_t count, char sepChar = toHexStr_defaultSepChar);
    
    /*! @} */
}

#endif // OMW_STRING_H
