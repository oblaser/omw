/*
author         Oliver Blaser
date           11.06.2021
copyright      MIT - Copyright (c) 2021 Oliver Blaser
*/

#ifndef OMW_STRING_H
#define OMW_STRING_H

#include <cstddef>
#include <string>

namespace omw
{
    class string : public std::string
    {
    public:
        string();
        string(const char* str);
        string(const std::string& str);
        virtual ~string() {}

        virtual omw::string& replaceFirst(const omw::string& search, const omw::string& replace, size_t startPos = 0);

        virtual omw::string& replaceAll(const omw::string& search, const omw::string& replace, size_t startPos = 0, size_t* occ = nullptr); // occurrences
        virtual omw::string& replaceAll(char search, const omw::string& replace, size_t startPos = 0, size_t* occ = nullptr);
        virtual omw::string& replaceAll(const omw::string& search, char replace, size_t startPos = 0, size_t* occ = nullptr);
        virtual omw::string& replaceAll(char search, char replace, omw::string::size_type startPos = 0, size_t* occ = nullptr);

        virtual omw::string& replaceAll(const omw::string* search, const omw::string* replace, size_t count, size_t startPos = 0, size_t* occ = nullptr);
        virtual omw::string& replaceAll(const char* search, const omw::string* replace, size_t count, size_t startPos = 0, size_t* occ = nullptr);
        virtual omw::string& replaceAll(const omw::string* search, const char* replace, size_t count, size_t startPos = 0, size_t* occ = nullptr);
        //virtual omw::string& replaceAll(const char* search, const char* replace, omw::string::size_type count, omw::string::size_type startPos = 0, size_t* occ = nullptr);

        virtual omw::string getUrlEncoded() const;
    };
}

#endif // OMW_STRING_H
