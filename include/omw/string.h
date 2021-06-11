/*
author         Oliver Blaser
date           10.06.2021
copyright      MIT - Copyright (c) 2021 Oliver Blaser
*/

#ifndef OMW_STRING_H
#define OMW_STRING_H

#include <cstddef>
#include <string>

namespace omw
{
    template <class CharT, class Traits = std::char_traits<CharT>, class Allocator = std::allocator<CharT>>
    class basic_string : public std::basic_string<CharT, Traits, Allocator>
    {
    public:
        basic_string();
        basic_string(const CharT* str);
        basic_string(const basic_string& other) = default;
        basic_string(basic_string&& other) = default;
        virtual ~basic_string() {}

        virtual basic_string& replaceFirst(const basic_string& search, const basic_string& replace, size_type startPos = 0);
    };

    using string = omw::basic_string<char>;





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
        virtual omw::OMWi_string& replaceAll(const char* search, const char* replace, size_t count, size_t startPos = 0, size_t* occ = nullptr);

        virtual omw::OMWi_string getUrlEncoded() const;
    };
}

#endif // OMW_STRING_H
