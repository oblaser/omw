/*
author         Oliver Blaser
date           09.06.2021
copyright      MIT - Copyright (c) 2021 Oliver Blaser
*/

#include <string>
#include <vector>

#include "version.h"



omw::Version::Version()
{
    version[0] = 0;
    version[1] = 0;
    version[2] = 0;
}

omw::Version::Version(int major, int minor, int revision)
{
    version[0] = major;
    version[1] = minor;
    version[2] = revision;
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

const int* omw::Version::data() const
{
    return version;
}

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

//! @brief Returns a `major.minor.revision` formatted string.
//! @return 
std::string omw::Version::toString() const
{
    return std::to_string(version[0]) + '.' + std::to_string(version[1]) + '.' + std::to_string(version[2]);
}

bool omw::operator<(const omw::Version& left, const omw::Version& right)
{
    if (left.maj() > right.maj()) return false;
    if (left.maj() < right.maj()) return true;

    if (left.min() > right.min()) return false;
    if (left.min() < right.min()) return true;

    if (left.rev() > right.rev()) return false;
    if (left.rev() < right.rev()) return true;

    return false;
}

bool omw::operator>(const omw::Version& left, const omw::Version& right)
{
    return (!(left < right) && !(left == right));
}

bool omw::operator<=(const omw::Version& left, const omw::Version& right)
{
    return (!(left > right));
}

bool omw::operator>=(const omw::Version& left, const omw::Version& right)
{
    return (!(left < right));
}

bool omw::operator==(const omw::Version& left, const omw::Version& right)
{
    return (
        (left.maj() == right.maj()) &&
        (left.min() == right.min()) &&
        (left.rev() == right.rev())
        );
}

bool omw::operator!=(const omw::Version& left, const omw::Version& right)
{
    return (!(left == right));
}

std::ostream& omw::operator<<(std::ostream& os, const omw::Version& v)
{
    os << v.toString();
    return os;
}
