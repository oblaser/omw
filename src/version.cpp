/*
author          Oliver Blaser
date            21.12.2021
copyright       MIT - Copyright (c) 2021 Oliver Blaser
*/

#include <stdexcept>
#include <string>
#include <vector>

#include "omw/defs.h"
#include "omw/string.h"
#include "omw/version.h"


#define OMWi_THROW_INVALID_FORMAT() \
throw std::invalid_argument(OMWi_DISPSTR("omw::Version: invalid format"))


namespace
{
    namespace semver
    {
        // positive integer without leading zeros
        bool isNumeric(const omw::string& identifier)
        {
            bool r;

            if (omw::isUInteger(identifier))
            {
                r = true;

                if (identifier.length() > 1)
                {
                    if (identifier[0] == '0') r = false;
                }
            }
            else r = false;

            return r;
        }

        // alpha numeric and hyphen
        bool isAlphaNumeric(const omw::string& identifier)
        {
            bool r = true;

            for (omw::string::size_type i = 0; (i < identifier.length()) && r; ++i)
            {
                if (!(omw::isAlnum(identifier[i]) || (identifier[i] == '-'))) r = false;
            }

            return r;
        }

        // positive integer with or without leading zeros
        bool isDigits(const omw::string& identifier)
        {
            return omw::isUInteger(identifier);
        }
    }

    // a < b   =>  -1
    // a = b   =>   0
    // a > b   =>   1
    int cmp(const omw::Version& a, const omw::Version& b)
    {
        int r = 0;

        if (a.major() < b.major()) r = -1;
        else if (a.major() == b.major())
        {
            if (a.minor() < b.minor()) r = -1;
            else if (a.minor() == b.minor())
            {
                if (a.patch() < b.patch()) r = -1;
                else if (a.patch() == b.patch())
                {
                    r = 0;
                    // TODO implement pre-release identifier compare
                }
                else r = 1;
            }
            else r = 1;
        }
        else r = 1;

        return r;
    }
}



/*!
* \class omw::Version
* \brief Compilant to _semver_.
*
* `#include <omw/version.h>`
*
* Compliant to <a href="https://semver.org/" target="_blank">Semantic Versioning 2.0.0</a>.
*/

//! 
//! Creates an object with version \b `0.0.0`.
//! 
omw::Version::Version()
    : m_maj(0), m_min(0), m_pat(0), m_preRelease(), m_build()
{
}

//! 
//! \b Exceptions
//! - `std::invalid_argument` if the pre-release or build string is not formatted correctly
//! 
omw::Version::Version(uint32_t major, uint32_t minor, uint32_t patch, const char* preRelease, const char* build)
    : m_maj(major), m_min(minor), m_pat(patch), m_preRelease(), m_build()
{
    if (preRelease) parsePreRelease(preRelease);
    if (build) parsePreRelease(build);
}

//! 
//! \b Exceptions
//! - `std::invalid_argument` if the pre-release or build string is not formatted correctly
//! 
omw::Version::Version(uint32_t major, uint32_t minor, uint32_t patch, const omw::string& preRelease, const omw::string& build)
    : m_maj(major), m_min(minor), m_pat(patch), m_preRelease(), m_build()
{
    parsePreRelease(preRelease);
    parsePreRelease(build);
}

//! 
//! \b Exceptions
//! - `std::invalid_argument` if the semver string is not formatted correctly
//! 
omw::Version::Version(const char* str)
    : m_maj(0), m_min(0), m_pat(0), m_preRelease(), m_build()
{
    parse(str);
}

//! 
//! \b Exceptions
//! - `std::invalid_argument` if the semver string is not formatted correctly
//! 
omw::Version::Version(const omw::string& str)
    : m_maj(0), m_min(0), m_pat(0), m_preRelease(), m_build()
{
    parse(str);
}

uint32_t omw::Version::major() const
{
    return m_maj;
}

uint32_t omw::Version::minor() const
{
    return m_min;
}

uint32_t omw::Version::patch() const
{
    return m_pat;
}

omw::string omw::Version::preRelease() const
{
    omw::string r = "";

    for (omw::stringVector_t::size_type i = 0; i < m_preRelease.size(); ++i)
    {
        if (i > 0) r += '.';
        r += m_preRelease[i];
    }

    return r;
}

const omw::stringVector_t& omw::Version::preReleaseIdentifiers() const
{
    return m_preRelease;
}

omw::string omw::Version::build() const
{
    omw::string r = "";

    for (omw::stringVector_t::size_type i = 0; i < m_build.size(); ++i)
    {
        if (i > 0) r += '.';
        r += m_build[i];
    }

    return r;
}

const omw::stringVector_t& omw::Version::buildIdentifiers() const
{
    return m_build;
}

omw::string omw::Version::toString() const
{
    omw::string r = omw::to_string(m_maj) + '.' + omw::to_string(m_min) + '.' + omw::to_string(m_pat);
    if (m_preRelease.size() > 0) r += '-' + preRelease();
    if (m_build.size() > 0) r += '+' + build();
    return r;
}

bool omw::Version::isPreRelease() const
{
    return (m_preRelease.size() > 0);
}

// trowing std::invalid_argument
void omw::Version::parse(const omw::string& str)
{
    const omw::string::size_type posHyphen = str.find('-');
    const omw::string::size_type posPlus = str.find('+');
    omw::string::size_type endVersion = omw::string::npos;

    if (posPlus < omw::string::npos)
    {
        endVersion = posPlus;
        parseBuild(str.substr(posPlus + 1));
    }
    else m_build = omw::stringVector_t();

    if (posHyphen < posPlus)
    {
        endVersion = posHyphen;
        const omw::string::size_type posPreRel = posHyphen + 1;
        parsePreRelease(str.substr(posPreRel, posPlus - posPreRel));
    }
    else m_preRelease = omw::stringVector_t();

    parseVersion(str.substr(0, endVersion));
}

// trowing std::invalid_argument
void omw::Version::parseBuild(const omw::string& identifiers)
{
    m_build.clear();

    if (identifiers.length() > 0)
    {
        const omw::stringVector_t data = identifiers.split('.');

        for (omw::stringVector_t::size_type i = 0; i < data.size(); ++i)
        {
            const omw::stringVector_t::value_type& tmpData = data[i];
            if (::semver::isAlphaNumeric(tmpData) || ::semver::isDigits(tmpData)) m_build.push_back(tmpData);
            else OMWi_THROW_INVALID_FORMAT();
        }

        m_build.shrink_to_fit();
    }
}

// trowing std::invalid_argument
void omw::Version::parsePreRelease(const omw::string& identifiers)
{
    m_preRelease.clear();

    if (identifiers.length() > 0)
    {
        const omw::stringVector_t data = identifiers.split('.');

        for (omw::stringVector_t::size_type i = 0; i < data.size(); ++i)
        {
            const omw::stringVector_t::value_type& tmpData = data[i];
            if (::semver::isAlphaNumeric(tmpData) || ::semver::isNumeric(tmpData)) m_preRelease.push_back(tmpData);
            else OMWi_THROW_INVALID_FORMAT();
        }

        m_preRelease.shrink_to_fit();
    }
}

// trowing std::invalid_argument
void omw::Version::parseVersion(const omw::string& identifiers)
{
    try
    {
        const omw::stringVector_t data = identifiers.split('.', 3);

        if (data.size() == 3)
        {
            if (::semver::isNumeric(data[0]) && ::semver::isNumeric(data[1]) && ::semver::isNumeric(data[2]))
            {
                m_maj = (uint32_t)std::stoull(data[0]);
                m_min = (uint32_t)std::stoull(data[1]);
                m_pat = (uint32_t)std::stoull(data[2]);
            }
            else throw - 1;
        }
        else throw - 1;
    }
    catch (...)
    {
        OMWi_THROW_INVALID_FORMAT();
    }
}



//! @return `true` if major, minor, patch and all pre-release identifiers are the same for `a` and `b`, otherwise `false`.
//! 
//! Build identifiers are ignored.
//! 
bool omw::operator==(const omw::Version& a, const omw::Version& b)
{
    return (
        (a.major() == b.major()) &&
        (a.minor() == b.minor()) &&
        (a.patch() == b.patch()) &&
        (a.preRelease() == b.preRelease())
        );
}

//! 
//! Build identifiers are ignored.
//! 
bool omw::operator!=(const omw::Version& a, const omw::Version& b) { return !(a == b); }

//! 
//! Build identifiers are ignored.
//! 
bool omw::operator<(const omw::Version& a, const omw::Version& b)
{
    return (::cmp(a, b) < 0);
}

//! 
//! Build identifiers are ignored.
//! 
bool omw::operator>(const omw::Version& a, const omw::Version& b) { return (b < a); }

//! 
//! Build identifiers are ignored.
//! 
bool omw::operator<=(const omw::Version& a, const omw::Version& b) { return !(a > b); }

//! 
//! Build identifiers are ignored.
//! 
bool omw::operator>=(const omw::Version& a, const omw::Version& b) { return !(a < b); }
