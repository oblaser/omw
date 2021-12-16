/*
author          Oliver Blaser
date            13.12.2021
copyright       MIT - Copyright (c) 2021 Oliver Blaser
*/

#include <string>
#include <vector>

#include "omw/defs.h"
#include "omw/string.h"
#include "omw/version.h"

namespace
{
}



/*!
* \class omw::Version
*
* `#include <omw/version.h>`
*/

omw::Version::Version()
    : version{ 0, 0, 0 }
{}

omw::Version::Version(int major, int minor, int revision)
    : version{ major, minor, revision }
{}

//! @param versionStr A `major.minor.revision` formatted string
//! 
//! \b Exceptions
//! - `std::invalid_argument` on format violations
//! 
omw::Version::Version(const char* versionStr)
    : version{ 0, 0, 0 }
{
    setData(std::string(versionStr));
}

//! @param versionStr A `major.minor.revision` formatted string
//! 
//! \b Exceptions
//! - `std::invalid_argument` on format violations
//! 
omw::Version::Version(const std::string& versionStr)
    : version{ 0, 0, 0 }
{
    setData(versionStr);
}

int omw::Version::maj() const
{
    return version[0];
}

int omw::Version::min() const
{
    return version[1];
}

int omw::Version::rev() const
{
    return version[2];
}

//! @brief 
//! @return Pointer to the underlaying `int` array.
//! 
//! \[0]: major<br/>
//! \[1]: minor<br/>
//! \[2]: revision<br/>
//! 
const int* omw::Version::data() const
{
    return version;
}

//! @brief 
//! @return Size of the underlaying `int` array (allways 3).
size_t omw::Version::size() const
{
    return dataSize;
}

std::vector<int> omw::Version::toVector() const
{
    std::vector<int> v(version, version + dataSize);
    v.shrink_to_fit();
    return v;
}

//! @brief 
//! @return A `major.minor.revision` formatted string.
std::string omw::Version::toString() const
{
    return std::to_string(version[0]) + '.' + std::to_string(version[1]) + '.' + std::to_string(version[2]);
}

//! @param versionStr A `major.minor.revision` formatted string
//! 
//! \b Exceptions
//! - `std::invalid_argument` on format violations
//! 
void omw::Version::setData(const std::string& versionStr)
{
    try
    {
        const size_t sp1 = versionStr.find('.');
        const size_t sp2 = versionStr.find('.', sp1 + 1);

        if ((sp1 == 0) || ((sp2 - sp1) == 1) || (sp1 >= (versionStr.length() - 1)) ||
            (sp1 == std::string::npos) || (sp2 == std::string::npos))
        {
            throw - 1;
        }

        const std::string majStr = versionStr.substr(0, sp1);
        const std::string minStr = versionStr.substr(sp1 + 1, sp2 - sp1 - 1);
        const std::string revStr = versionStr.substr(sp2 + 1);

        if (!omw::isInteger(majStr) || !omw::isInteger(minStr) || !omw::isInteger(revStr))
        {
            throw - 1;
        }

        // perform all conversions before assigning the member array
        const int maj = std::stoi(majStr);
        const int min = std::stoi(minStr);
        const int rev = std::stoi(revStr);

        version[0] = maj;
        version[1] = min;
        version[2] = rev;
    }
    catch (...)
    {
        throw std::invalid_argument(OMWi_DISPSTR("invalid format"));
    }
}



bool omw::operator==(const omw::Version& a, const omw::Version& b)
{
    return (
        (a.maj() == b.maj()) &&
        (a.min() == b.min()) &&
        (a.rev() == b.rev())
        );
}

bool omw::operator!=(const omw::Version& a, const omw::Version& b)
{
    return !(a == b);
}

bool omw::operator<(const omw::Version& a, const omw::Version& b)
{
    bool r = false;

    if (a.maj() < b.maj()) r = true;
    else if (a.maj() == b.maj())
    {
        if (a.min() < b.min()) r = true;
        else if (a.min() == b.min())
        {
            if (a.rev() < b.rev()) r = true;
        }
    }

    return r;
}

bool omw::operator>(const omw::Version& a, const omw::Version& b)
{
    return (b < a);
}

bool omw::operator<=(const omw::Version& a, const omw::Version& b)
{
    return !(a > b);
}

bool omw::operator>=(const omw::Version& a, const omw::Version& b)
{
    return !(a < b);
}
