/*
author          Oliver Blaser
date            13.06.2025
copyright       MIT - Copyright (c) 2025 Oliver Blaser
*/

#ifndef IG_OMW_VERSION_H
#define IG_OMW_VERSION_H

#include <cstdint>
#include <string>

#include "../omw/string.h"


namespace omw {

/*! \addtogroup grp_utility_gpUtil
 * @{
 */

class MajMinVer
{
public:
    /**
     * Creates an object with version `0.0`.
     */
    MajMinVer()
        : m_major(0), m_minor(0)
    {}

    MajMinVer(int32_t major, int32_t minor)
        : m_major(major), m_minor(minor)
    {}

    MajMinVer(const char* str)
        : m_major(-1), m_minor(-1)
    {
        m_parse(str);
    }

    MajMinVer(const std::string& str)
        : m_major(-1), m_minor(-1)
    {
        m_parse(str);
    }

    virtual ~MajMinVer() {}

    virtual void set(const char* str) { m_parse(str); }
    virtual void set(const std::string& str) { m_parse(str); }
    void set(int32_t major, int32_t minor)
    {
        m_major = major;
        m_minor = minor;
    }

    int32_t major() const { return m_major; }
    int32_t minor() const { return m_minor; }

    /**
     * | Result             | Return Value |
     * |:------------------:|:------------:|
     * | `*this` < `other`  |     <0       |
     * | `*this` == `other` |      0       |
     * | `*this` > `other`  |     >0       |
     */
    int compare(const omw::MajMinVer& other) const;

    virtual std::string toString() const { return std::to_string(m_major) + '.' + std::to_string(m_minor); }

    /**
     * Checks if the member values are not negative.
     */
    virtual bool isValid() const { return ((m_major >= 0) && (m_minor >= 0)); }

protected:
    int32_t m_major;
    int32_t m_minor;

    virtual void m_parse(const char* str) { m_parse(std::string(str ? str : "")); };
    virtual void m_parse(const std::string& str);
};

/**
 * @class omw::Semver
 * @brief Compliant to _semver_.
 *
 * `#include <omw/version.h>`
 *
 * Compliant to <a href="https://semver.org/spec/v2.0.0.html" target="_blank">Semantic Versioning 2.0.0</a>.
 */
class Semver
{
public:
    /**
     * Creates an object with version `0.0.0`.
     */
    Semver()
        : m_major(0), m_minor(0), m_patch(0), m_preRelease(), m_build()
    {}

    Semver(int32_t major, int32_t minor, int32_t patch, const char* preRelease = nullptr, const char* build = nullptr)
        : m_major(major), m_minor(minor), m_patch(patch), m_preRelease(), m_build()
    {
        m_parsePreRelease(preRelease);
        m_parseBuild(build);
    }

    Semver(int32_t major, int32_t minor, int32_t patch, const std::string& preRelease, const std::string& build = "")
        : m_major(major), m_minor(minor), m_patch(patch), m_preRelease(), m_build()
    {
        m_parsePreRelease(preRelease);
        m_parseBuild(build);
    }

    Semver(const char* str)
        : m_major(-1), m_minor(-1), m_patch(-1), m_preRelease(), m_build()
    {
        m_parse(str);
    }

    Semver(const std::string& str)
        : m_major(-1), m_minor(-1), m_patch(-1), m_preRelease(), m_build()
    {
        m_parse(str);
    }

    virtual ~Semver() {}

    virtual void set(const char* str) { m_parse(str); }
    virtual void set(const std::string& str) { m_parse(str); }
    void set(int32_t major, int32_t minor, int32_t patch, const char* preRelease = nullptr, const char* build = nullptr);
    void set(int32_t major, int32_t minor, int32_t patch, const std::string& preRelease, const std::string& build = "");

    int32_t major() const { return m_major; }
    int32_t minor() const { return m_minor; }
    int32_t patch() const { return m_patch; }
    std::string preRelease() const { return omw::join(m_preRelease, '.'); }
    std::string build() const { return omw::join(m_build, '.'); }

    const omw::StringVector& preReleaseIdentifiers() const { return m_preRelease; }
    const omw::StringVector& buildIdentifiers() const { return m_build; }

    /**
     * Compares according to the _semver_ rules.
     *
     * | Result             | Return Value |
     * |:------------------:|:------------:|
     * | `*this` < `other`  |     <0       |
     * | `*this` == `other` |      0       |
     * | `*this` > `other`  |     >0       |
     */
    int compare(const omw::Semver& other) const;

    virtual std::string toString() const;

    bool hasBuild() const { return !m_build.empty(); }
    bool isPreRelease() const { return !m_preRelease.empty(); }

    /**
     * Checks if the member values are compliant to _semver_.
     */
    virtual bool isValid() const;

protected:
    int32_t m_major;
    int32_t m_minor;
    int32_t m_patch;
    omw::StringVector m_preRelease;
    omw::StringVector m_build;

    virtual void m_parse(const char* str) { m_parse(std::string(str ? str : "")); };
    virtual void m_parse(const std::string& str);

    virtual void m_parseBuild(const char* identifiers) { m_parseBuild(std::string(identifiers ? identifiers : "")); }
    virtual void m_parseBuild(const std::string& identifiers);

    virtual void m_parsePreRelease(const char* identifiers) { m_parsePreRelease(std::string(identifiers ? identifiers : "")); }
    virtual void m_parsePreRelease(const std::string& identifiers);

    virtual void m_parseVersion(const char* identifiers) { m_parseVersion(std::string(identifiers ? identifiers : "")); }
    virtual void m_parseVersion(const std::string& identifiers);
};


//! \name Operators
/// @{

static inline bool operator==(const omw::MajMinVer& a, const omw::MajMinVer& b) { return (a.compare(b) == 0); }
static inline bool operator!=(const omw::MajMinVer& a, const omw::MajMinVer& b) { return !(a == b); }
static inline bool operator<(const omw::MajMinVer& a, const omw::MajMinVer& b) { return (a.compare(b) < 0); }
static inline bool operator>(const omw::MajMinVer& a, const omw::MajMinVer& b) { return (b < a); }
static inline bool operator<=(const omw::MajMinVer& a, const omw::MajMinVer& b) { return !(a > b); }
static inline bool operator>=(const omw::MajMinVer& a, const omw::MajMinVer& b) { return !(a < b); }

static inline bool operator==(const omw::Semver& a, const omw::Semver& b) { return (a.compare(b) == 0); }
static inline bool operator!=(const omw::Semver& a, const omw::Semver& b) { return !(a == b); }
static inline bool operator<(const omw::Semver& a, const omw::Semver& b) { return (a.compare(b) < 0); }
static inline bool operator>(const omw::Semver& a, const omw::Semver& b) { return (b < a); }
static inline bool operator<=(const omw::Semver& a, const omw::Semver& b) { return !(a > b); }
static inline bool operator>=(const omw::Semver& a, const omw::Semver& b) { return !(a < b); }

/// @}


/*! @} */

} // namespace omw


#endif // IG_OMW_VERSION_H
