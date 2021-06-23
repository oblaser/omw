/*
author         Oliver Blaser
date           11.06.2021
copyright      MIT - Copyright (c) 2021 Oliver Blaser
*/

#include <cstddef>
#include <string>

#include "omw/string.h"



omw::string::string()
    : std::string()
{
}

omw::string::string(const char* str)
    : std::string(str)
{
}

omw::string::string(const std::string& str)
    : std::string(str)
{
}

omw::string& omw::string::replaceFirst(const omw::string& search, const omw::string& replace, size_t startPos)
{
    size_t pos = find(search, startPos);
    if ((pos < length()) && (pos != std::string::npos)) this->replace(pos, search.length(), replace);
    return *this;
}

omw::string& omw::string::replaceAll(const omw::string& search, const omw::string& replace, size_t startPos, size_t* occ)
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

omw::string& omw::string::replaceAll(char search, const omw::string& replace, size_t startPos, size_t* occ)
{
    const char srch[2] = { search, 0 };
    return replaceAll(srch, replace, startPos, occ);
}

omw::string& omw::string::replaceAll(const omw::string& search, char replace, size_t startPos, size_t* occ)
{
    const char repl[2] = { replace, 0 };
    return replaceAll(search, repl, startPos, occ);
}

omw::string& omw::string::replaceAll(char search, char replace, omw::string::size_type startPos, size_t* occ)
{
    const char src[2] = { search, 0 };
    const char repl[2] = { replace, 0 };
    return replaceAll(src, repl, startPos, occ);
}

omw::string& omw::string::replaceAll(const omw::string* search, const omw::string* replace, size_t count, size_t startPos, size_t* occ)
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

omw::string& omw::string::replaceAll(const char* search, const omw::string* replace, size_t count, size_t startPos, size_t* occ)
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

omw::string& omw::string::replaceAll(const omw::string* search, const char* replace, size_t count, size_t startPos, size_t* occ)
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

omw::string omw::string::getUrlEncoded() const
{
    const size_t count = 61;
    const char search[count] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 38, 39, 40, 41, 42, 43, 44, 47, 58, 59, 60, 61, 62, 63, 64, 91, 92, 93, 94, 96, 123, 124, 125, 127 };
    const omw::string replace[count] = { "%00", "%01", "%02", "%03", "%04", "%05", "%06", "%07", "%08", "%09", "%0A", "%0B", "%0C", "%0D", "%0E", "%0F", "%10", "%11", "%12", "%13", "%14", "%15", "%16", "%17", "%18", "%19", "%1A", "%1B", "%1C", "%1D", "%1E", "%1F", "%20", "%21", "%22", "%23", "%24", "%26", "%27", "%28", "%29", "%2A", "%2B", "%2C", "%2F", "%3A", "%3B", "%3C", "%3D", "%3E", "%3F", "%40", "%5B", "%5C", "%5D", "%5E", "%60", "%7B", "%7C", "%7D", "%7F" };

    omw::string r(*this);
    r.replaceAll('%', "%25", 0, nullptr);
    r.replaceAll(search, replace, count, 0, nullptr);
    return r;
}
