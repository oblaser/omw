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

#include "../omw/string.h"

namespace omw
{
    /*! \addtogroup grp_containersLib
    * @{
    */

    //! \name omw::vector Implementation Functions
    /// @{
    template <class T, class Allocator = std::allocator<T>>
    bool contains(const std::vector<T, Allocator>& v, const T& item)
    {
        bool r = false;
        for (std::vector<T, Allocator>::size_type i = 0; i < v.size(); ++i) { if (v[i] == item) { r = true; break; } }
        return r;
    }

    //template <class T, class Allocator = std::allocator<T>>
    //bool contains(const std::vector<T, Allocator>& v, const T::value_type* item)
    //{
    //    bool r = false;
    //    for (std::vector<T, Allocator>::size_type i = 0; i < v.size(); ++i) { if (v[i] == item) { r = true; break; } }
    //    return r;
    //}
    //template<> bool contains(const std::vector<std::string>&, const std::string::value_type*);
    //template<> bool contains(const std::vector<omw::string>&, const omw::string::value_type*);
    /// @}

    template <class T, class Allocator = std::allocator<T>>
    class vector : public std::vector<T, Allocator>
    {
#ifndef OMWi_DOXYGEN_PREDEFINE
    public:
        using value_type = typename std::vector<T, Allocator>::value_type; /*!< \brief \b `T` */
        using size_type = typename std::vector<T, Allocator>::size_type; /*!< \brief Usually `std::size_t` */
#endif // OMWi_DOXYGEN_PREDEFINE

    public:
        static constexpr size_type maxsz = static_cast<size_type>(-1);

    public:
        vector() : std::vector<T, Allocator>() {}
        explicit vector(size_type count) : std::vector<T, Allocator>(count) {}
        vector(size_type count, const T& value) : std::vector<T, Allocator>(count, value) {}
        vector(const T* first, const T* last) : std::vector<T, Allocator>(first, last) {}
        vector(std::initializer_list<T> init) : std::vector<T, Allocator>(init) {}
        vector(const std::vector<T, Allocator>& other) : std::vector<T, Allocator>(other) {}
        ~vector() {}

        bool contains(const T& item) const { return omw::contains(*this, item); }

        void reserveAdd(size_type addCap) { this->reserve(this->size() + addCap); }
    };

    /*! @} */
}

#endif // IG_OMW_VECTOR_H
