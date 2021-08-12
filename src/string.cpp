/*
author         Oliver Blaser
date           12.08.2021
copyright      MIT - Copyright (c) 2021 Oliver Blaser
*/

#include <cstddef>
#include <string>

#include "omw/string.h"



/*!
* \class omw::Basic_StringReplacePair
* \brief
*/

template<class CharT, class Traits, class Allocator>
omw::Basic_StringReplacePair<CharT, Traits, Allocator>::Basic_StringReplacePair()
    : searchString(), replaceString()
{
}

template<class CharT, class Traits, class Allocator>
omw::Basic_StringReplacePair<CharT, Traits, Allocator>::Basic_StringReplacePair(const std::basic_string<CharT, Traits, Allocator>& search, const std::basic_string<CharT, Traits, Allocator>& replace)
    : searchString(search), replaceString(replace)
{
}

template<class CharT, class Traits, class Allocator>
const std::basic_string<CharT, Traits, Allocator>& omw::Basic_StringReplacePair<CharT, Traits, Allocator>::searchStr() const
{
    return searchString;
}

template<class CharT, class Traits, class Allocator>
const std::basic_string<CharT, Traits, Allocator>& omw::Basic_StringReplacePair<CharT, Traits, Allocator>::replaceStr() const
{
    return replaceString;
}



/*!
* \class omw::basic_string
* \brief A with `std::basic_string` interchangeable class to add more functionalities.
*
* This class does not override/implement any virtual methods of the base class. So it's a `std::basic_string` with some more methods.
*/

template<class CharT, class Traits, class Allocator>
omw::basic_string<CharT, Traits, Allocator>::basic_string()
    : std::basic_string()
{
}

template<class CharT, class Traits, class Allocator>
omw::basic_string<CharT, Traits, Allocator>::basic_string(const CharT* str)
    : std::basic_string(str)
{
}

template<class CharT, class Traits, class Allocator>
omw::basic_string<CharT, Traits, Allocator>& omw::basic_string<CharT, Traits, Allocator>::replaceFirst(const omw::basic_string<CharT, Traits, Allocator>& search, const omw::basic_string<CharT, Traits, Allocator>& replace, size_type startPos)
{
    size_type pos = find(search, startPos);
    if ((pos < length()) && (pos != npos)) this->replace(pos, search.length(), replace);
    return *this;
}

template<class CharT, class Traits, class Allocator>
inline omw::basic_string<CharT, Traits, Allocator>& omw::basic_string<CharT, Traits, Allocator>::replaceFirst(const StringReplacePair_type& pair, size_type startPos)
{
    return replaceFirst(pair.searchStr(), pair.replaceStr(), startPos);
}

template<class CharT, class Traits, class Allocator>
omw::basic_string<CharT, Traits, Allocator>& omw::basic_string<CharT, Traits, Allocator>::replaceAll(const omw::basic_string<CharT, Traits, Allocator>& search, const omw::basic_string<CharT, Traits, Allocator>& replace, size_type startPos, size_type* cntReplacements)
{
    size_type cnt = 0;

    if ((search.length() > 0) || (replace.length() > 0))
    {
        size_type pos = find(search, startPos);
        while ((pos < length()) && (pos != npos))
        {
            this->replace(pos, search.length(), replace);
            ++cnt;
            pos = find(search, pos + replace.length());
        }
    }

    if (cntReplacements) *cntReplacements = cnt;

    return *this;
}



/*!
* \class omw::string
* \brief An implementation of `omw::basic_string`.
*/








/*!
* \class omw::OMWi_string
* \brief A with `std::string` interchangeable class to add more functionalities.
*
* This class does not override/implement any virtual methods of the base class. So it's a `std::string` with some more methods.
*/

omw::OMWi_string::OMWi_string()
    : std::string()
{
}

omw::OMWi_string::OMWi_string(const char* str)
    : std::string(str)
{
}

omw::OMWi_string::OMWi_string(const std::string& str)
    : std::string(str)
{
}

omw::OMWi_string& omw::OMWi_string::replaceFirst(const omw::OMWi_string& search, const omw::OMWi_string& replace, size_t startPos)
{
    size_t pos = find(search, startPos);
    if ((pos < length()) && (pos != npos)) this->replace(pos, search.length(), replace);
    return *this;
}

omw::OMWi_string& omw::OMWi_string::replaceAll(const omw::OMWi_string& search, const omw::OMWi_string& replace, size_t startPos, size_t* occ)
{
    size_t cnt = 0;

    if (search.length() > 0)
    {
        size_t pos = find(search, startPos);
        while ((pos < length()) && (pos != std::string::npos))
        {
            this->replace(pos, search.length(), replace);
            ++cnt;
            pos = find(search, pos + replace.length());
        }
    }

    if (occ) *occ = cnt;
    return *this;
}

omw::OMWi_string& omw::OMWi_string::replaceAll(char search, const omw::OMWi_string& replace, size_t startPos, size_t* occ)
{
    const char srch[2] = { search, 0 };
    return replaceAll(srch, replace, startPos, occ);
}

omw::OMWi_string& omw::OMWi_string::replaceAll(const omw::OMWi_string& search, char replace, size_t startPos, size_t* occ)
{
    const char repl[2] = { replace, 0 };
    return replaceAll(search, repl, startPos, occ);
}

omw::OMWi_string& omw::OMWi_string::replaceAll(char search, char replace, size_t startPos, size_t* occ)
{
    const char src[2] = { search, 0 };
    const char repl[2] = { replace, 0 };
    return replaceAll(src, repl, startPos, occ);
}

omw::OMWi_string& omw::OMWi_string::replaceAll(const omw::OMWi_string* search, const omw::OMWi_string* replace, size_t count, size_t startPos, size_t* occ)
{
    size_t cnt = 0;

    for (size_t i = 0; i < count; ++i)
    {
        size_t tmpCnt;
        replaceAll(search[i], replace[i], startPos, &tmpCnt);
        cnt += tmpCnt;
    }

    if (occ) *occ = cnt;
    return *this;
}

omw::OMWi_string& omw::OMWi_string::replaceAll(const char* search, const omw::OMWi_string* replace, size_t count, size_t startPos, size_t* occ)
{
    size_t cnt = 0;

    for (size_t i = 0; i < count; ++i)
    {
        size_t tmpCnt;
        replaceAll(search[i], replace[i], startPos, &tmpCnt);
        cnt += tmpCnt;
    }

    if (occ) *occ = cnt;
    return *this;
}

omw::OMWi_string& omw::OMWi_string::replaceAll(const omw::OMWi_string* search, const char* replace, size_t count, size_t startPos, size_t* occ)
{
    size_t cnt = 0;

    for (size_t i = 0; i < count; ++i)
    {
        size_t tmpCnt;
        replaceAll(search[i], replace[i], startPos, &tmpCnt);
        cnt += tmpCnt;
    }

    if (occ) *occ = cnt;
    return *this;
}

omw::OMWi_string omw::OMWi_string::getUrlEncoded() const
{
    const size_t count = 61;
    const char search[count] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 38, 39, 40, 41, 42, 43, 44, 47, 58, 59, 60, 61, 62, 63, 64, 91, 92, 93, 94, 96, 123, 124, 125, 127 };
    const omw::OMWi_string replace[count] = { "%00", "%01", "%02", "%03", "%04", "%05", "%06", "%07", "%08", "%09", "%0A", "%0B", "%0C", "%0D", "%0E", "%0F", "%10", "%11", "%12", "%13", "%14", "%15", "%16", "%17", "%18", "%19", "%1A", "%1B", "%1C", "%1D", "%1E", "%1F", "%20", "%21", "%22", "%23", "%24", "%26", "%27", "%28", "%29", "%2A", "%2B", "%2C", "%2F", "%3A", "%3B", "%3C", "%3D", "%3E", "%3F", "%40", "%5B", "%5C", "%5D", "%5E", "%60", "%7B", "%7C", "%7D", "%7F" };

    omw::OMWi_string r(*this);
    r.replaceAll('%', "%25", 0, nullptr);
    r.replaceAll(search, replace, count, 0, nullptr);
    return r;
}
