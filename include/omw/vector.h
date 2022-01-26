/*
author          Oliver Blaser
date            25.01.2022
copyright       MIT - Copyright (c) 2022 Oliver Blaser
*/

#ifndef IG_OMW_VECTOR_H
#define IG_OMW_VECTOR_H

#include <cstddef>
#include <cstdint>
#include <initializer_list>
#include <memory>
#include <vector>

namespace omw
{
    /*! \addtogroup grp_containersLib
    * @{
    */

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

        bool contains(const T& item) const
        {
            bool r = false;
            for (size_type i = 0; (i < this->size()) && !r; ++i)
                if (this->at(i) == item) r = true;
            return r;
        }

        void reserveAdd(size_type addCap) { this->reserve(this->size() + addCap); }
    };

    /*! @} */
}

#endif // IG_OMW_VECTOR_H
