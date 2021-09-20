/*
author         Oliver Blaser
date           14.08.2021
copyright      MIT - Copyright (c) 2021 Oliver Blaser
*/

#ifndef IG_OMW_VERSION_H
#define IG_OMW_VERSION_H

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
        explicit Version(const char* versionStr);
        explicit Version(const std::string& versionStr);

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
        static constexpr size_t dataSize = 3;
        int version[dataSize];

        void setData(const std::string& versionStr);
    };
}

#endif // IG_OMW_VERSION_H
