/*
author         Oliver Blaser
date           12.08.2021
copyright      MIT - Copyright (c) 2021 Oliver Blaser
*/

#include <string>
#include <vector>

#include "omw/string.h"



omw::StringReplacePair::StringReplacePair()
    : searchElem(), replaceElem()
{
}

omw::StringReplacePair::StringReplacePair(const std::string& searchElement, const std::string& replaceElement)
    : searchElem(searchElement), replaceElem(replaceElement)
{
}

omw::StringReplacePair::StringReplacePair(const char searchElement, const std::string& replaceElement)
    : searchElem(1, searchElement), replaceElem(replaceElement)
{
}

omw::StringReplacePair::StringReplacePair(const std::string& searchElement, const char replaceElement)
    : searchElem(searchElement), replaceElem(1, replaceElement)
{
}

omw::StringReplacePair::StringReplacePair(const char searchElement, const char replaceElement)
    : searchElem(1, searchElement), replaceElem(1, replaceElement)
{
}

const std::string& omw::StringReplacePair::search() const
{
    return searchElem;
}

const std::string& omw::StringReplacePair::replace() const
{
    return replaceElem;
}



//bool omw::string::isValidUTF8(const omw::string& str)
//{
//    return str.isValidUTF8();
//}

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

omw::string::string(const char* first, const char* last)
    : std::string(first, last)
{
}

omw::string& omw::string::replaceFirst(const omw::string& search, const omw::string& replace, size_type startPos)
{
    size_type pos = find(search, startPos);
    if ((pos < length()) && (pos != std::string::npos)) this->replace(pos, search.length(), replace);
    return *this;
}

inline omw::string& omw::string::replaceFirst(const omw::StringReplacePair& pair, size_type startPos)
{
    return replaceFirst(pair.search(), pair.replace(), startPos);
}

//! @brief 
//! @param search 
//! @param replace 
//! @param startPos 
//! @param [out] nReplacements 
//! @return 
omw::string& omw::string::replaceAll(const omw::string& search, const omw::string& replace, size_type startPos, size_type* nReplacements)
{
    size_type cnt = 0;

    if (search.length() > 0)
    {
        size_type pos = find(search, startPos);
        while ((pos < length()) && (pos != std::string::npos))
        {
            this->replace(pos, search.length(), replace);
            ++cnt;
            pos = find(search, pos + replace.length());
        }
    }
    else cnt = npos;

    if (nReplacements) *nReplacements = cnt;

    return *this;
}

//! @brief 
//! @param pair 
//! @param startPos 
//! @param [out] nReplacements 
//! @return 
inline omw::string& omw::string::replaceAll(const omw::StringReplacePair& pair, size_type startPos, size_type* nReplacements)
{
    return replaceAll(pair.search(), pair.replace(), startPos, nReplacements);
}

//! @brief 
//! @param pairs 
//! @param startPos 
//! @param [out] nReplacementsTotal 
//! @param [out] nReplacements 
//! @return 
inline omw::string& omw::string::replaceAll(const std::vector<omw::StringReplacePair>& pairs, size_type startPos, size_type* nReplacementsTotal, std::vector<size_type>* nReplacements)
{
    bool allInvalid = true;
    size_type cnt = 0;
    size_type tmpCnt;

    if (nReplacements) *nReplacements = std::vector<size_type>(pairs.size(), npos);

    for (size_t i = 0; i < pairs.size(); ++i)
    {
        replaceAll(pairs[i], startPos, &tmpCnt);
        if (nReplacements) nReplacements->at(i) = tmpCnt;
        if (tmpCnt != npos)
        {
            cnt += tmpCnt;
            allInvalid = false;
        }
    }

    if (allInvalid) cnt = npos;

    if (nReplacementsTotal) *nReplacementsTotal = cnt;

    return *this;
}

//! @brief 
//! @param pairsBegin 
//! @param pairsEnd 
//! @param startPos 
//! @param [out] nReplacementsTotal 
//! @param [out] nReplacements 
//! @return 
inline omw::string& omw::string::replaceAll(const omw::StringReplacePair* pairsBegin, const omw::StringReplacePair* pairsEnd, size_type startPos, size_type* nReplacementsTotal, std::vector<size_type>* nReplacements)
{
    return replaceAll(std::vector<omw::StringReplacePair>(pairsBegin, pairsEnd), startPos, nReplacementsTotal, nReplacements);
}

omw::string& omw::string::makeUrlEncoded()
{
    const size_t count = 61;
    const char search[count] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 38, 39, 40, 41, 42, 43, 44, 47, 58, 59, 60, 61, 62, 63, 64, 91, 92, 93, 94, 96, 123, 124, 125, 127 };
    const omw::string replace[count] = { "%00", "%01", "%02", "%03", "%04", "%05", "%06", "%07", "%08", "%09", "%0A", "%0B", "%0C", "%0D", "%0E", "%0F", "%10", "%11", "%12", "%13", "%14", "%15", "%16", "%17", "%18", "%19", "%1A", "%1B", "%1C", "%1D", "%1E", "%1F", "%20", "%21", "%22", "%23", "%24", "%26", "%27", "%28", "%29", "%2A", "%2B", "%2C", "%2F", "%3A", "%3B", "%3C", "%3D", "%3E", "%3F", "%40", "%5B", "%5C", "%5D", "%5E", "%60", "%7B", "%7C", "%7D", "%7F" };
    
    replaceAll("%", "%25", 0, nullptr);
    for (size_t i = 0; i < count; ++i) replaceAll(omw::StringReplacePair(search[i], replace[i]), 0, nullptr);

    return *this;
}

inline omw::string omw::string::getUrlEncoded() const
{
    omw::string s(this->c_str());
    s.makeUrlEncoded();
    return s;
}
