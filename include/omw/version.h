/*
author         Oliver Blaser
date           09.06.2021
copyright      MIT - Copyright (c) 2021 Oliver Blaser
*/

#ifndef OMW_VERSION_H
#define OMW_VERSION_H

#include <iostream>
#include <string>
#include <vector>

namespace omw
{
    class Version
    {
    public:
        Version();
        Version(int major, int minor, int revision);

        int maj() const;
        int min() const;
        int rev() const;

        const int* data() const;
        size_t size() const;

        std::vector<int> toVector() const;
        std::string toString() const;

        friend bool operator<(const omw::Version& left, const omw::Version& right);
        friend bool operator>(const omw::Version& left, const omw::Version& right);
        friend bool operator<=(const omw::Version& left, const omw::Version& right);
        friend bool operator>=(const omw::Version& left, const omw::Version& right);
        friend bool operator==(const omw::Version& left, const omw::Version& right);
        friend bool operator!=(const omw::Version& left, const omw::Version& right);
        friend std::ostream& operator<<(std::ostream& os, const omw::Version& v);

    private:
        static const size_t dataSize = 3;
        int version[dataSize];
    };
}

#endif // OMW_VERSION_H
