/*
author          Oliver Blaser
date            10.01.2022
copyright       MIT - Copyright (c) 2022 Oliver Blaser
*/

#ifndef IG_OMW_UTILITY_H
#define IG_OMW_UTILITY_H

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace omw
{
    /*! \addtogroup grp_utility_langSupport
    * @{
    */

    //int8_t shiftLeft(int8_t value, size_t n);
    //int16_t shiftLeft(int16_t value, size_t n);
    //int32_t shiftLeft(int32_t value, size_t n);
    //int64_t shiftLeft(int64_t value, size_t n);
    //uint8_t shiftLeft(uint8_t value, size_t n);
    //uint16_t shiftLeft(uint16_t value, size_t n);
    //uint32_t shiftLeft(uint32_t value, size_t n);
    //uint64_t shiftLeft(uint64_t value, size_t n);
    //int8_t shiftRight(int8_t value, size_t n);
    //int16_t shiftRight(int16_t value, size_t n);
    //int32_t shiftRight(int32_t value, size_t n);
    //int64_t shiftRight(int64_t value, size_t n);
    //uint8_t shiftRight(uint8_t value, size_t n);
    //uint16_t shiftRight(uint16_t value, size_t n);
    //uint32_t shiftRight(uint32_t value, size_t n);
    //uint64_t shiftRight(uint64_t value, size_t n);
    void shiftLeftAssign(int8_t& value, size_t n);
    void shiftLeftAssign(int16_t& value, size_t n);
    void shiftLeftAssign(int32_t& value, size_t n);
    void shiftLeftAssign(int64_t& value, size_t n);
    void shiftLeftAssign(uint8_t& value, size_t n);
    void shiftLeftAssign(uint16_t& value, size_t n);
    void shiftLeftAssign(uint32_t& value, size_t n);
    void shiftLeftAssign(uint64_t& value, size_t n);
    void shiftRightAssign(int8_t& value, size_t n);
    void shiftRightAssign(int16_t& value, size_t n);
    void shiftRightAssign(int32_t& value, size_t n);
    void shiftRightAssign(int64_t& value, size_t n);
    void shiftRightAssign(uint8_t& value, size_t n);
    void shiftRightAssign(uint16_t& value, size_t n);
    void shiftRightAssign(uint32_t& value, size_t n);
    void shiftRightAssign(uint64_t& value, size_t n);

    // grp_utility_langSupport
    /*! @} */



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

    // grp_utility_gpUtil
    /*! @} */
}

#endif // IG_OMW_UTILITY_H
