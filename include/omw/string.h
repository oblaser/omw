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
    template <class CharT, class Traits = std::char_traits<CharT>, class Allocator = std::allocator<CharT>>
    class Basic_StringReplacePair
    {
    public:
        Basic_StringReplacePair();
        Basic_StringReplacePair(const std::basic_string<CharT, Traits, Allocator>& search, const std::basic_string<CharT, Traits, Allocator>& replace);
        Basic_StringReplacePair(const omw::Basic_StringReplacePair<CharT, Traits, Allocator>& other) = default;
        Basic_StringReplacePair(omw::Basic_StringReplacePair<CharT, Traits, Allocator>&& other) = default;
        virtual ~Basic_StringReplacePair() {}

        const std::basic_string<CharT, Traits, Allocator>& searchStr() const;
        const std::basic_string<CharT, Traits, Allocator>& replaceStr() const;

    protected:
        std::basic_string<CharT, Traits, Allocator> searchString;
        std::basic_string<CharT, Traits, Allocator> replaceString;
    };

    //using StringReplacePair = omw::Basic_StringReplacePair<char>;
    //using WStringReplacePair = omw::Basic_StringReplacePair<wchar_t>;

    template <class CharT, class Traits = std::char_traits<CharT>, class Allocator = std::allocator<CharT>>
    class basic_string : public std::basic_string<CharT, Traits, Allocator>
    {
    public:
        using StringReplacePair_type = omw::Basic_StringReplacePair<CharT, Traits, Allocator>;

    public:
        basic_string();
        basic_string(const CharT* str);
        basic_string(const omw::basic_string<CharT, Traits, Allocator>& other) = default;
        basic_string(omw::basic_string<CharT, Traits, Allocator>&& other) = default;
        virtual ~basic_string() {}

        omw::basic_string<CharT, Traits, Allocator>& replaceFirst(const omw::basic_string<CharT, Traits, Allocator>& search, const omw::basic_string<CharT, Traits, Allocator>& replace, size_type startPos = 0);
        inline omw::basic_string<CharT, Traits, Allocator>& replaceFirst(const StringReplacePair_type& pair, size_type startPos = 0);

        omw::basic_string<CharT, Traits, Allocator>& replaceAll(const omw::basic_string<CharT, Traits, Allocator>& search, const omw::basic_string<CharT, Traits, Allocator>& replace, size_type startPos = 0, size_type* cntReplacements = nullptr);
    };

    using string = omw::basic_string<char>;
    //using wstring = omw::basic_string<wchar_t>;





    // OMWi_string was previously called string
    class OMWi_string : public std::string
    {
    public:
        OMWi_string();
        OMWi_string(const char* str);
        OMWi_string(const std::string& str);
        virtual ~OMWi_string() {}

        virtual omw::OMWi_string& replaceFirst(const omw::OMWi_string& search, const omw::OMWi_string& replace, size_t startPos = 0);

        virtual omw::OMWi_string& replaceAll(const omw::OMWi_string& search, const omw::OMWi_string& replace, size_t startPos = 0, size_t* occ = nullptr); // occurrences
        virtual omw::OMWi_string& replaceAll(char search, const omw::OMWi_string& replace, size_t startPos = 0, size_t* occ = nullptr);
        virtual omw::OMWi_string& replaceAll(const omw::OMWi_string& search, char replace, size_t startPos = 0, size_t* occ = nullptr);
        virtual omw::OMWi_string& replaceAll(char search, char replace, size_t startPos = 0, size_t* occ = nullptr);

        virtual omw::OMWi_string& replaceAll(const omw::OMWi_string* search, const omw::OMWi_string* replace, size_t count, size_t startPos = 0, size_t* occ = nullptr);
        virtual omw::OMWi_string& replaceAll(const char* search, const omw::OMWi_string* replace, size_t count, size_t startPos = 0, size_t* occ = nullptr);
        virtual omw::OMWi_string& replaceAll(const omw::OMWi_string* search, const char* replace, size_t count, size_t startPos = 0, size_t* occ = nullptr);
        //virtual omw::OMWi_string& replaceAll(const char* search, const char* replace, size_t count, size_t startPos = 0, size_t* occ = nullptr);

        virtual omw::OMWi_string getUrlEncoded() const;
    };
}

#endif // OMW_STRING_H
