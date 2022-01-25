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

    template<class T, class Allocator = std::allocator<T>>
    class vector : public std::vector<T, Allocator>
    {
    public:
        using value_type = typename std::vector<T, Allocator>::value_type; /*!< \brief \b `T` */
        using size_type = typename std::vector<T, Allocator>::size_type; /*!< \brief Usually `std::size_t` */

        static constexpr size_type maxSize = static_cast<size_type>(-1);

    public:
        vector() : std::vector<T, Allocator>() {}
        vector(size_type count) : std::vector<T, Allocator>(count) {}
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

    using ByteVector = typename omw::vector<uint8_t>; /*!< `omw::vector` of type `uint8_t`. */
    using CharVector = typename omw::vector<char>; /*!< `omw::vector` of type `char`. */

    omw::ByteVector toByteVector(const std::vector<char>& v);
    omw::CharVector toCharVector(const std::vector<uint8_t>& v);

    /*! @} */
}

#endif // IG_OMW_VECTOR_H
