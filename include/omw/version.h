/*
author          Oliver Blaser
date            22.01.2022
copyright       MIT - Copyright (c) 2022 Oliver Blaser
*/

#ifndef IG_OMW_VERSION_H
#define IG_OMW_VERSION_H

#include <cstdint>
#include <string>

#include "../omw/string.h"

namespace omw
{
    /*! \addtogroup grp_utility_gpUtil
    * @{
    */

    class Version
    {
    public:
        Version();
        Version(int32_t major, int32_t minor, int32_t patch, const char* preRelease, const char* build = nullptr);
        Version(int32_t major, int32_t minor, int32_t patch, const std::string& preRelease = "", const std::string& build = "");
        Version(const char* str);
        Version(const std::string& str);
        virtual ~Version() {}

        void set(int32_t major, int32_t minor, int32_t patch, const char* preRelease, const char* build = nullptr);
        void set(int32_t major, int32_t minor, int32_t patch, const std::string& preRelease = "", const std::string& build = "");
        void set(const char* str);
        void set(const std::string& str);

        int32_t major() const;
        int32_t minor() const;
        int32_t patch() const;
        omw::string preRelease() const;
        const omw::stringVector_t& preReleaseIdentifiers() const;
        omw::string build() const;
        const omw::stringVector_t& buildIdentifiers() const;

        int compare(const omw::Version& b) const;

        omw::string toString() const;

        bool hasBuild() const;
        bool isPreRelease() const;
        bool isValid() const; /*!< Checks if the member values are compliant to _semver_. See `omw::Version`. */

    protected:
        int32_t m_maj;
        int32_t m_min;
        int32_t m_pat;
        omw::stringVector_t m_preRelease;
        omw::stringVector_t m_build;

        void parse(const omw::string& str);
        void parseBuild(const omw::string& identifiers);
        void parsePreRelease(const omw::string& identifiers);
        void parseVersion(const omw::string& identifiers);
    };

    //! \name Operators
    /// @{
    bool operator==(const omw::Version& a, const omw::Version& b);
    bool operator!=(const omw::Version& a, const omw::Version& b);
    bool operator<(const omw::Version& a, const omw::Version& b);
    bool operator>(const omw::Version& a, const omw::Version& b);
    bool operator<=(const omw::Version& a, const omw::Version& b);
    bool operator>=(const omw::Version& a, const omw::Version& b);
    /// @}

    /*! @} */
}

#endif // IG_OMW_VERSION_H
