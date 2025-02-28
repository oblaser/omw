/*
author          Oliver Blaser
date            18.02.2022
copyright       MIT - Copyright (c) 2022 Oliver Blaser
*/

#include <algorithm>
#include <stdexcept>
#include <string>
#include <vector>

#include "omw/defs.h"
#include "omw/string.h"
#include "omw/version.h"


namespace {

#ifndef ___OMWi_REGION_semver_classification_functions

// positive integer without leading zeros
bool isNumericIdentifier(const std::string& identifier)
{
    bool r;

    if (omw::isUInteger(identifier))
    {
        r = true;

        if ((identifier.length() > 1) && (identifier[0] == '0')) { r = false; }
    }
    else r = false;

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
            if (!(omw::isAlnum(identifier[i]) || (identifier[i] == '-'))) r = false;
        }
    }

    return r;
}

// positive integer with or without leading zeros
bool isDigits(const std::string& identifier) { return omw::isUInteger(identifier); }

bool isPreReleaseIdentifier(const std::string& identifier)
{
    bool r;

    if (omw::isUInteger(identifier)) r = isNumericIdentifier(identifier);
    else r = isAlphanumericIdentifier(identifier);

    return r;
}

bool isBuildIdentifier(const std::string& identifier) { return (isAlphanumericIdentifier(identifier) || isDigits(identifier)); }

bool check(int32_t maj, int32_t min, int32_t pat) { return (isNumericIdentifier(maj) && isNumericIdentifier(min) && isNumericIdentifier(pat)); }

#endif // ___OMWi_REGION_semver_classification_functions

} // namespace


/*!
 * \class omw::Version
 * \brief Compliant to _semver_.
 *
 * `#include <omw/version.h>`
 *
 * Compliant to <a href="https://semver.org/spec/v2.0.0.html" target="_blank">Semantic Versioning 2.0.0</a>.
 */

//!
//! Creates an object with version \b `0.0.0`.
//!
omw::Version::Version()
    : m_maj(0), m_min(0), m_pat(0), m_preRelease(), m_build()
{}

omw::Version::Version(int32_t major, int32_t minor, int32_t patch, const char* preRelease, const char* build)
    : m_maj(0), m_min(0), m_pat(0), m_preRelease(), m_build()
{
    set(major, minor, patch, preRelease, build);
}

omw::Version::Version(int32_t major, int32_t minor, int32_t patch, const std::string& preRelease, const std::string& build)
    : m_maj(0), m_min(0), m_pat(0), m_preRelease(), m_build()
{
    set(major, minor, patch, preRelease, build);
}

omw::Version::Version(const char* str)
    : m_maj(0), m_min(0), m_pat(0), m_preRelease(), m_build()
{
    set(str);
}

omw::Version::Version(const std::string& str)
    : m_maj(0), m_min(0), m_pat(0), m_preRelease(), m_build()
{
    set(str);
}

void omw::Version::set(int32_t major, int32_t minor, int32_t patch, const char* preRelease, const char* build)
{
    m_maj = major;
    m_min = minor;
    m_pat = patch;

    parsePreRelease(preRelease ? preRelease : "");
    parseBuild(build ? build : "");
}

void omw::Version::set(int32_t major, int32_t minor, int32_t patch, const std::string& preRelease, const std::string& build)
{
    m_maj = major;
    m_min = minor;
    m_pat = patch;

    parsePreRelease(preRelease);
    parseBuild(build);
}

void omw::Version::set(const char* str) { parse(str ? str : ""); }

void omw::Version::set(const std::string& str) { parse(str); }

int32_t omw::Version::major() const { return m_maj; }

int32_t omw::Version::minor() const { return m_min; }

int32_t omw::Version::patch() const { return m_pat; }

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

const omw::stringVector_t& omw::Version::preReleaseIdentifiers() const { return m_preRelease; }

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

const omw::stringVector_t& omw::Version::buildIdentifiers() const { return m_build; }

//!
//! Compares according to the _semver_ rules.
//!
//! | Result | Return Value |
//! |:---:|:---:|
//! | `*this` < `b` | <0 |
//! | `*this` == `b` | 0 |
//! | `*this` > `b` | >0 |
//!
int omw::Version::compare(const omw::Version& b) const
{
    int r;

    if (this->major() < b.major()) { r = -1; }
    else if (this->major() == b.major())
    {
        if (this->minor() < b.minor()) { r = -1; }
        else if (this->minor() == b.minor())
        {
            if (this->patch() < b.patch()) { r = -1; }
            else if (this->patch() == b.patch())
            {
                const omw::stringVector_t& pra = this->preReleaseIdentifiers();
                const omw::stringVector_t& prb = b.preReleaseIdentifiers();
                const omw::stringVector_t::size_type n = std::min(pra.size(), prb.size());

                r = 0;

                if (n == 0)
                {
                    if (pra.size() > prb.size()) { r = -1; }
                    else if (pra.size() < prb.size()) { r = 1; }
                }

                for (omw::stringVector_t::size_type i = 0; (i < n) && (r == 0); ++i)
                {
                    const omw::string& tmpIdentifier_a = pra[i];
                    const omw::string& tmpIdentifier_b = prb[i];

                    const bool isnuma = isNumericIdentifier(tmpIdentifier_a);
                    const bool isnumb = isNumericIdentifier(tmpIdentifier_b);

                    if (isnuma && isnumb)
                    {
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

omw::string omw::Version::toString() const
{
    omw::string r = std::to_string(m_maj) + '.' + std::to_string(m_min) + '.' + std::to_string(m_pat);

    if (m_preRelease.size() > 0) { r += '-' + preRelease(); }
    if (m_build.size() > 0) { r += '+' + build(); }

    return r;
}

//!
//! Returns `true` if the version has build identifiers, otherwise `false`.
//!
bool omw::Version::hasBuild() const { return (m_build.size() > 0); }

//!
//! Returns `true` if the version has pre-release identifiers, otherwise `false`.
//!
bool omw::Version::isPreRelease() const { return (m_preRelease.size() > 0); }

bool omw::Version::isValid() const
{
    bool r = ::check(m_maj, m_min, m_pat);

    for (omw::stringVector_t::size_type i = 0; (i < m_preRelease.size()) && r; ++i) { r = ::isPreReleaseIdentifier(m_preRelease[i]); }

    for (omw::stringVector_t::size_type i = 0; (i < m_build.size()) && r; ++i) { r = ::isBuildIdentifier(m_build[i]); }

    return r;
}

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
    else { m_build = omw::stringVector_t(); }

    if (posHyphen < posPlus)
    {
        endVersion = posHyphen;
        const omw::string::size_type posPreRel = posHyphen + 1;
        parsePreRelease(str.substr(posPreRel, posPlus - posPreRel));
    }
    else { m_preRelease = omw::stringVector_t(); }

    parseVersion(str.substr(0, endVersion));
}

void omw::Version::parseBuild(const omw::string& identifiers)
{
    if (identifiers.length() > 0) { m_build = identifiers.split('.'); }
    else { m_build.clear(); }

    m_build.shrink_to_fit();
}

void omw::Version::parsePreRelease(const omw::string& identifiers)
{
    if (identifiers.length() > 0) { m_preRelease = identifiers.split('.'); }
    else { m_preRelease.clear(); }

    m_preRelease.shrink_to_fit();
}

void omw::Version::parseVersion(const omw::string& identifiers)
{
    try
    {
        const omw::stringVector_t data = identifiers.split('.');

        if (data.size() == 3)
        {
            if (!(omw::isInteger(data[0]) && omw::isInteger(data[1]) && omw::isInteger(data[2]))) { throw -1; }

            try
            {
                m_maj = std::stol(data[0]);
            }
            catch (...)
            {
                m_maj = -1;
            }

            try
            {
                m_min = std::stol(data[1]);
            }
            catch (...)
            {
                m_min = -1;
            }

            try
            {
                m_pat = std::stol(data[2]);
            }
            catch (...)
            {
                m_pat = -1;
            }
        }
        else { throw -1; }
    }
    catch (...)
    {
        m_maj = -1;
        m_min = -1;
        m_pat = -1;
    }
}
