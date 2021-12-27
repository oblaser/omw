/*
author          Oliver Blaser
date            27.12.2021
copyright       MIT - Copyright (c) 2021 Oliver Blaser
*/

#ifndef IG_OMW_VERSION_H
#define IG_OMW_VERSION_H

#include <cstdint>

#include "../omw/string.h"

namespace omw
{
    /*! \addtogroup grp_utility
    * @{
    */

    class Version
    {
    public:
        Version();
        Version(uint32_t major, uint32_t minor, uint32_t patch, const char* preRelease, const char* build = nullptr);
        Version(uint32_t major, uint32_t minor, uint32_t patch, const omw::string& preRelease = "", const omw::string& build = "");
        explicit Version(const char* str);
        explicit Version(const omw::string& str);
        virtual ~Version() {}

        uint32_t major() const;
        uint32_t minor() const;
        uint32_t patch() const;
        omw::string preRelease() const;
        const omw::stringVector_t& preReleaseIdentifiers() const;
        omw::string build() const;
        const omw::stringVector_t& buildIdentifiers() const;

        omw::string toString() const;

        bool isPreRelease() const;
        bool isValid() const;

    protected:
        uint32_t m_maj;
        uint32_t m_min;
        uint32_t m_pat;
        omw::stringVector_t m_build;
        omw::stringVector_t m_preRelease;

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
