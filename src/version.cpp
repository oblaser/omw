/*
author          Oliver Blaser
date            13.06.2025
copyright       MIT - Copyright (c) 2025 Oliver Blaser
*/

#include <algorithm>
#include <string>
#include <vector>

#include "omw/string.h"
#include "omw/version.h"



namespace semver {

// positive integer without leading zeros
bool isNumericIdentifier(const std::string& identifier)
{
    bool r;

    if (omw::isUInteger(identifier))
    {
        r = true;

        if ((identifier.length() > 1) && (identifier[0] == '0')) { r = false; }
    }
    else { r = false; }

    return r;
}

bool isNumericIdentifier(int32_t identifier) { return (identifier >= 0); }

// alpha numeric and hyphen
bool isAlphanumericIdentifier(const std::string& identifier)
{
    bool r = false;

    if (identifier.length() > 0)
    {
        r = true;

        for (std::string::size_type i = 0; (i < identifier.length()) && r; ++i)
        {
            if (!(omw::isAlnum(identifier[i]) || (identifier[i] == '-'))) { r = false; }
        }
    }

    return r;
}

// positive integer with or without leading zeros
bool isDigits(const std::string& identifier) { return omw::isUInteger(identifier); }

bool isPreReleaseIdentifier(const std::string& identifier)
{
    bool r;

    if (omw::isUInteger(identifier)) { r = semver::isNumericIdentifier(identifier); }
    else { r = semver::isAlphanumericIdentifier(identifier); }

    return r;
}

bool isBuildIdentifier(const std::string& identifier) { return (semver::isAlphanumericIdentifier(identifier) || semver::isDigits(identifier)); }

bool check(int32_t maj, int32_t min, int32_t pat)
{
    return (semver::isNumericIdentifier(maj) && semver::isNumericIdentifier(min) && semver::isNumericIdentifier(pat));
}

} // namespace semver



int omw::MajMinVer::compare(const omw::MajMinVer& other) const
{
    int r;

    if (this->major() < other.major()) { r = -1; }
    else if (this->major() == other.major())
    {
        if (this->minor() < other.minor()) { r = -1; }
        else if (this->minor() == other.minor()) { r = 0; }
        else { r = 1; }
    }
    else { r = 1; }

    return r;
}

void omw::MajMinVer::m_parse(const std::string& str)
{
    try
    {
        const omw::StringVector data = omw::stdStringVector(omw::split(str, '.'));

        if (data.size() == 2)
        {
            if (!(omw::isInteger(data[0]) && omw::isInteger(data[1]))) { throw -1; }

            try
            {
                m_major = std::stol(data[0]);
            }
            catch (...)
            {
                m_major = -1;
            }

            try
            {
                m_minor = std::stol(data[1]);
            }
            catch (...)
            {
                m_minor = -1;
            }
        }
        else { throw -1; }
    }
    catch (...)
    {
        m_major = -1;
        m_minor = -1;
    }
}



void omw::Semver::set(int32_t major, int32_t minor, int32_t patch, const char* preRelease, const char* build)
{
    m_major = major;
    m_minor = minor;
    m_patch = patch;

    m_parsePreRelease(preRelease);
    m_parseBuild(build);
}

void omw::Semver::set(int32_t major, int32_t minor, int32_t patch, const std::string& preRelease, const std::string& build)
{
    m_major = major;
    m_minor = minor;
    m_patch = patch;

    m_parsePreRelease(preRelease);
    m_parseBuild(build);
}

int omw::Semver::compare(const omw::Semver& other) const
{
    int r;

    if (this->major() < other.major()) { r = -1; }
    else if (this->major() == other.major())
    {
        if (this->minor() < other.minor()) { r = -1; }
        else if (this->minor() == other.minor())
        {
            if (this->patch() < other.patch()) { r = -1; }
            else if (this->patch() == other.patch())
            {
                const omw::StringVector& pra = this->preReleaseIdentifiers();
                const omw::StringVector& prb = other.preReleaseIdentifiers();
                const omw::StringVector::size_type n = std::min(pra.size(), prb.size());

                r = 0;

                if (n == 0)
                {
                    if (pra.size() > prb.size()) { r = -1; }
                    else if (pra.size() < prb.size()) { r = 1; }
                }

                for (omw::StringVector::size_type i = 0; (i < n) && (r == 0); ++i)
                {
                    const omw::string& tmpIdentifier_a = pra[i];
                    const omw::string& tmpIdentifier_b = prb[i];

                    const bool isnuma = semver::isNumericIdentifier(tmpIdentifier_a);
                    const bool isnumb = semver::isNumericIdentifier(tmpIdentifier_b);

                    if (isnuma && isnumb)
                    {
                        static_assert(sizeof(uint64_t) == sizeof(unsigned long long));
                        const uint64_t vala = std::stoull(tmpIdentifier_a);
                        const uint64_t valb = std::stoull(tmpIdentifier_b);

                        if (vala < valb) { r = -1; }
                        else if (vala > valb) { r = 1; }
                    }
                    else if (isnuma && !isnumb) { r = -1; }
                    else if (!isnuma && isnumb) { r = 1; }
                    else
                    {
                        if (tmpIdentifier_a < tmpIdentifier_b) { r = -1; }
                        else if (tmpIdentifier_a > tmpIdentifier_b) { r = 1; }
                    }
                }

                if (r == 0)
                {
                    if (pra.size() < prb.size()) { r = -1; }
                    else if (pra.size() > prb.size()) { r = 1; }
                }
            }
            else { r = 1; }
        }
        else { r = 1; }
    }
    else { r = 1; }

    return r;
}

std::string omw::Semver::toString() const
{
    std::string r = std::to_string(m_major) + '.' + std::to_string(m_minor) + '.' + std::to_string(m_patch);

    if (isPreRelease()) { r += '-' + preRelease(); }
    if (hasBuild()) { r += '+' + build(); }

    return r;
}

bool omw::Semver::isValid() const
{
    bool r = semver::check(m_major, m_minor, m_patch);

    for (omw::StringVector::size_type i = 0; (i < m_preRelease.size()) && r; ++i) { r = semver::isPreReleaseIdentifier(m_preRelease[i]); }

    for (omw::StringVector::size_type i = 0; (i < m_build.size()) && r; ++i) { r = semver::isBuildIdentifier(m_build[i]); }

    return r;
}

void omw::Semver::m_parse(const std::string& str)
{
    const std::string::size_type posHyphen = str.find('-');
    const std::string::size_type posPlus = str.find('+');
    std::string::size_type endVersion = std::string::npos;

    if (posPlus < std::string::npos)
    {
        endVersion = posPlus;
        m_parseBuild(str.substr(posPlus + 1));
    }
    else
    {
        m_build.clear();
        m_build.shrink_to_fit();
    }

    if (posHyphen < posPlus)
    {
        endVersion = posHyphen;
        const std::string::size_type posPreRel = posHyphen + 1;
        m_parsePreRelease(str.substr(posPreRel, posPlus - posPreRel));
    }
    else
    {
        m_preRelease.clear();
        m_preRelease.shrink_to_fit();
    }

    m_parseVersion(str.substr(0, endVersion));
}

void omw::Semver::m_parseBuild(const std::string& identifiers)
{
    if (!identifiers.empty()) { m_build = omw::stdStringVector(omw::split(identifiers, '.')); }
    else { m_build.clear(); }

    m_build.shrink_to_fit();
}

void omw::Semver::m_parsePreRelease(const std::string& identifiers)
{
    if (identifiers.length() > 0) { m_preRelease = omw::stdStringVector(omw::split(identifiers, '.')); }
    else { m_preRelease.clear(); }

    m_preRelease.shrink_to_fit();
}

void omw::Semver::m_parseVersion(const std::string& identifiers)
{
    try
    {
        const omw::StringVector data = omw::stdStringVector(omw::split(identifiers, '.'));

        if (data.size() == 3)
        {
            if (!(omw::isInteger(data[0]) && omw::isInteger(data[1]) && omw::isInteger(data[2]))) { throw -1; }

            try
            {
                m_major = std::stol(data[0]);
            }
            catch (...)
            {
                m_major = -1;
            }

            try
            {
                m_minor = std::stol(data[1]);
            }
            catch (...)
            {
                m_minor = -1;
            }

            try
            {
                m_patch = std::stol(data[2]);
            }
            catch (...)
            {
                m_patch = -1;
            }
        }
        else { throw -1; }
    }
    catch (...)
    {
        m_major = -1;
        m_minor = -1;
        m_patch = -1;
    }
}
