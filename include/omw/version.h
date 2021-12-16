/*
author          Oliver Blaser
date            15.12.2021
copyright       MIT - Copyright (c) 2021 Oliver Blaser
*/

#ifndef IG_OMW_VERSION_H
#define IG_OMW_VERSION_H

#include <iostream>
#include <string>
#include <vector>

namespace omw
{
    /*! \addtogroup grp_utility
    * @{
    */

    class Version
    {
    public:
        Version();
        Version(int major, int minor, int revision);
        explicit Version(const char* versionStr);
        explicit Version(const std::string& versionStr);

        int maj() const;
        int min() const;
        int rev() const;

        const int* data() const;
        size_t size() const;

        std::vector<int> toVector() const;
        std::string toString() const;

        template<class CharT, class Traits = std::char_traits<CharT>>
        friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const omw::Version& v)
        {
            // since the version string consists only out of ASCII chars, here is no std::basic_ostream<c,t>::widen() needed.
            return (os << v.toString().c_str());
        }

    private:
        static constexpr size_t dataSize = 3;
        int version[dataSize];

        void setData(const std::string& versionStr);
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
