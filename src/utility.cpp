/*
author          Oliver Blaser
date            27.12.2021
copyright       MIT - Copyright (c) 2021 Oliver Blaser
*/

#include <string>
#include <vector>

#include "omw/utility.h"

namespace
{
}


// /* or /*!
/*
* \fn void omw::toggle(bool& value)
* \param value The value to toggle
* 
* Toggles a boolean value.
*/

std::vector<uint8_t> omw::toVector(const std::string& str)
{
    std::vector<uint8_t> r(str.length(), 0);

    for (std::vector<uint8_t>::size_type i = 0; i < r.size(); ++i)
    {
        r[i] = static_cast<uint8_t>(str[i]);
    }

    return r;
}

std::vector<uint8_t> omw::toVector(const omw::Base_Int128& val)
{
    std::vector<uint8_t> r(16);

    const uint64_t h = val.hi();
    const uint64_t l = val.lo();

    r[0] = static_cast<uint8_t>((h >> 56) & 0xFF);
    r[1] = static_cast<uint8_t>((h >> 48) & 0xFF);
    r[2] = static_cast<uint8_t>((h >> 40) & 0xFF);
    r[3] = static_cast<uint8_t>((h >> 32) & 0xFF);
    r[4] = static_cast<uint8_t>((h >> 24) & 0xFF);
    r[5] = static_cast<uint8_t>((h >> 16) & 0xFF);
    r[6] = static_cast<uint8_t>((h >> 8) & 0xFF);
    r[7] = static_cast<uint8_t>(h & 0xFF);

    r[8] = static_cast<uint8_t>((l >> 56) & 0xFF);
    r[9] = static_cast<uint8_t>((l >> 48) & 0xFF);
    r[10] = static_cast<uint8_t>((l >> 40) & 0xFF);
    r[11] = static_cast<uint8_t>((l >> 32) & 0xFF);
    r[12] = static_cast<uint8_t>((l >> 24) & 0xFF);
    r[13] = static_cast<uint8_t>((l >> 16) & 0xFF);
    r[14] = static_cast<uint8_t>((l >> 8) & 0xFF);
    r[15] = static_cast<uint8_t>(l & 0xFF);

    return r;
}
