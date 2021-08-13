/*
author         Oliver Blaser
date           12.08.2021
copyright      MIT - Copyright (c) 2021 Oliver Blaser
*/

#ifndef OMW_STRING_H
#define OMW_STRING_H

#include <string>
#include <vector>

namespace omw
{
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

        virtual omw::string& replaceFirst(const omw::string& search, const omw::string& replace, size_type startPos = 0);
        virtual inline omw::string& replaceFirst(const omw::StringReplacePair& pair, size_type startPos = 0);

        virtual omw::string& replaceAll(const omw::string& search, const omw::string& replace, size_type startPos = 0, size_type* nReplacements = nullptr);
        virtual inline omw::string& replaceAll(const omw::StringReplacePair& pair, size_type startPos = 0, size_type* nReplacements = nullptr);
        virtual inline omw::string& replaceAll(const std::vector<omw::StringReplacePair>& pairs, size_type startPos = 0, size_type* nReplacementsTotal = nullptr, std::vector<size_type>* nReplacements = nullptr);
        virtual inline omw::string& replaceAll(const omw::StringReplacePair* pairsBegin, const omw::StringReplacePair* pairsEnd, size_type startPos = 0, size_type* nReplacementsTotal = nullptr, std::vector<size_type>* nReplacements = nullptr);

        virtual omw::string& makeUrlEncoded();
        virtual inline omw::string getUrlEncoded() const;

        //bool isValidUTF8() const;
    };
}

#endif // OMW_STRING_H
