/*
author         Oliver Blaser
date           13.08.2021
copyright      MIT - Copyright (c) 2021 Oliver Blaser
*/

#ifndef OMW_STRING_H
#define OMW_STRING_H

#include <string>
#include <vector>


namespace omw
{
    constexpr char UTF8CP_Auml[] = "\xC3\x84";          /*!< UTF-8 code point U+00C4 */
    constexpr char UTF8CP_Ouml[] = "\xC3\x96";          /*!< UTF-8 code point U+00D6 */
    constexpr char UTF8CP_Uuml[] = "\xC3\x9C";          /*!< UTF-8 code point U+00DC */
    constexpr char UTF8CP_auml[] = "\xC3\xA4";          /*!< UTF-8 code point U+00E4 */
    constexpr char UTF8CP_ouml[] = "\xC3\xB6";          /*!< UTF-8 code point U+00F6 */
    constexpr char UTF8CP_uuml[] = "\xC3\xBC";          /*!< UTF-8 code point U+00FC */

    constexpr char hexStrDigits[] = "0123456789ABCDEF";

    //! @brief Default character between 8bit hex strings of multibyte hex strings.
    constexpr char toHexStr_defaultJoinChar = 0x20;

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

        omw::string& replaceFirst(const omw::string& search, const omw::string& replace, size_type startPos = 0);
        omw::string& replaceFirst(const omw::StringReplacePair& pair, size_type startPos = 0);

        omw::string& replaceAll(const omw::string& search, const omw::string& replace, size_type startPos = 0, size_type* nReplacements = nullptr);
        omw::string& replaceAll(const omw::StringReplacePair& pair, size_type startPos = 0, size_type* nReplacements = nullptr);
        omw::string& replaceAll(const std::vector<omw::StringReplacePair>& pairs, size_type startPos = 0, size_type* nReplacementsTotal = nullptr, std::vector<size_type>* nReplacements = nullptr);
        omw::string& replaceAll(const omw::StringReplacePair* pairsBegin, const omw::StringReplacePair* pairsEnd, size_type startPos = 0, size_type* nReplacementsTotal = nullptr, std::vector<size_type>* nReplacements = nullptr);

        omw::string& makeLower_ascii();
        omw::string& makeLower_asciiExt();
        omw::string& makeUpper_ascii();
        omw::string& makeUpper_asciiExt();
        omw::string toLower_ascii() const;
        omw::string toLower_asciiExt() const;
        omw::string toUpper_ascii() const;
        omw::string toUpper_asciiExt() const;

        omw::string& makeUrlEncoded();
        omw::string toUrlEncoded() const;

        //bool isValidUTF8() const;
    };

    omw::string toHexStr(int8_t value);
    omw::string toHexStr(uint8_t value);
    omw::string toHexStr(int16_t value);
    omw::string toHexStr(uint16_t value);
    omw::string toHexStr(int32_t value);
    omw::string toHexStr(uint32_t value);
    omw::string toHexStr(int64_t value);
    omw::string toHexStr(uint64_t value);
    omw::string toHexStr(const std::vector<char>& data, char joinChar = toHexStr_defaultJoinChar);
    omw::string toHexStr(const std::vector<uint8_t>& data, char joinChar = toHexStr_defaultJoinChar);
    omw::string toHexStr(const char* data, size_t count, char joinChar = toHexStr_defaultJoinChar);
    omw::string toHexStr(const uint8_t* data, size_t count, char joinChar = toHexStr_defaultJoinChar);
}


#endif // OMW_STRING_H
