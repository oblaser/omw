/*
author          Oliver Blaser
date            13.03.2023
copyright       MIT - Copyright (c) 2023 Oliver Blaser
*/

#ifndef IG_OMW_VECTOR_H
#define IG_OMW_VECTOR_H

#include <cstddef>
#include <cstdint>
#include <initializer_list>
#include <memory>
#include <string>
#include <vector>


namespace omw {

/*! \addtogroup grp_containersLib
 * @{
 */

//! \name omw::vector Implementation Functions
/// @{
template <class T, class Allocator = std::allocator<T>> bool contains(const typename std::vector<T, Allocator>& vector, const T& item)
{
    bool r = false;

    for (typename std::vector<T, Allocator>::size_type i = 0; i < vector.size(); ++i)
    {
        if (vector[i] == item)
        {
            r = true;
            break;
        }
    }

    return r;
}

// template <class T, class Allocator = std::allocator<T>>
// bool contains(const std::vector<T, Allocator>& v, const T::value_type* item)
//{
//     bool r = false;
//     for (std::vector<T, Allocator>::size_type i = 0; i < v.size(); ++i) { if (v[i] == item) { r = true; break; } }
//     return r;
// }
// template<> bool contains(const std::vector<std::string>&, const std::string::value_type*);
/// @}

/**
 * @brief Reserves additional memory.
 *
 * <tt>vector.<a href="https://en.cppreference.com/w/cpp/container/vector/reserve" target="_blank">reserve</a>(vector.<a
 * href="https://en.cppreference.com/w/cpp/container/vector/size" target="_blank">size()</a> + additionalCapacity)</tt>
 *
 * @tparam T
 * @tparam Allocator
 * @param vector
 * @param additionalCapacity
 */
template <class T, class Allocator = std::allocator<T>>
void reserveAdditional(typename std::vector<T, Allocator>& vector, typename std::vector<T, Allocator>::size_type additionalCapacity)
{
    vector.reserve(vector.size() + additionalCapacity);
}

/*! @} */

} // namespace omw


#endif // IG_OMW_VECTOR_H
