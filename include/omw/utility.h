/*
author          Oliver Blaser
date            27.12.2021
copyright       MIT - Copyright (c) 2021 Oliver Blaser
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
    /*! \addtogroup grp_utility
    * @{
    */

    inline void toggle(bool& value) { value = !value; }
    inline void toggle(int& value) { value = (value ? 0 : 1); }

    template <class Type>
    bool vectorContains(const std::vector<Type>& v, const Type& item)
    {
        bool r = false;

        for (size_t i = 0; (i < v.size()) && !r; ++i)
        {
            if (v[i] == item) r = true;
        }

        return r;
    }

    std::vector<char> convertVector_i8(const std::vector<uint8_t>& v);
    std::vector<uint8_t> convertVector_ui8(const std::vector<char>& v);

    std::vector<uint8_t> toVector(const std::string& str);
    std::vector<uint8_t> toVector(const omw::Base_Int128& val);

    // grp_utility
    /*! @} */
}

#endif // IG_OMW_UTILITY_H
