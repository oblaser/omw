/*
author          Oliver Blaser
date            07.01.2022
copyright       MIT - Copyright (c) 2022 Oliver Blaser
*/

#ifndef IG_OMW_UTILITY_H
#define IG_OMW_UTILITY_H

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "../omw/int.h"

namespace omw
{
    /*! \addtogroup grp_utility_gpUtil
    * @{
    */

    inline void toggle(bool& value) { value = !value; }
    inline void toggle(int& value) { value = (value ? 0 : 1); }

    template <class Type>
    bool vectorContains(const std::vector<Type>& v, const Type& item)
    {
        bool r = false;
        for (size_t i = 0; (i < v.size()) && !r; ++i)
            if (v[i] == item) r = true;
        return r;
    }

    std::vector<char> convertByteVector(const std::vector<uint8_t>& v);
    std::vector<uint8_t> convertByteVector(const std::vector<char>& v);

    // grp_utility
    /*! @} */
}

#endif // IG_OMW_UTILITY_H
