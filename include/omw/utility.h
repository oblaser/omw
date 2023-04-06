/*
author          Oliver Blaser
date            06.04.2022
copyright       MIT - Copyright (c) 2023 Oliver Blaser
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

    void shiftLeftAssign(int8_t& value, unsigned int n);
    void shiftLeftAssign(int16_t& value, unsigned int n);
    void shiftLeftAssign(int32_t& value, unsigned int n); /*!< See \ref grp_utility_langSupport_section_bitShiftOp in \ref grp_utility_langSupport. */
    void shiftLeftAssign(int64_t& value, unsigned int n);
    void shiftLeftAssign(uint8_t& value, unsigned int n);
    void shiftLeftAssign(uint16_t& value, unsigned int n);
    void shiftLeftAssign(uint32_t& value, unsigned int n);
    void shiftLeftAssign(uint64_t& value, unsigned int n);
    void shiftRightAssign(int8_t& value, unsigned int n);
    void shiftRightAssign(int16_t& value, unsigned int n);
    void shiftRightAssign(int32_t& value, unsigned int n); /*!< See \ref grp_utility_langSupport_section_bitShiftOp in \ref grp_utility_langSupport. */
    void shiftRightAssign(int64_t& value, unsigned int n);
    void shiftRightAssign(uint8_t& value, unsigned int n);
    void shiftRightAssign(uint16_t& value, unsigned int n);
    void shiftRightAssign(uint32_t& value, unsigned int n);
    void shiftRightAssign(uint64_t& value, unsigned int n);
    int8_t shiftLeft(int8_t value, unsigned int n);
    int16_t shiftLeft(int16_t value, unsigned int n);
    int32_t shiftLeft(int32_t value, unsigned int n); /*!< See \ref grp_utility_langSupport_section_bitShiftOp in \ref grp_utility_langSupport. */
    int64_t shiftLeft(int64_t value, unsigned int n);
    uint8_t shiftLeft(uint8_t value, unsigned int n);
    uint16_t shiftLeft(uint16_t value, unsigned int n);
    uint32_t shiftLeft(uint32_t value, unsigned int n);
    uint64_t shiftLeft(uint64_t value, unsigned int n);
    int8_t shiftRight(int8_t value, unsigned int n);
    int16_t shiftRight(int16_t value, unsigned int n);
    int32_t shiftRight(int32_t value, unsigned int n); /*!< See \ref grp_utility_langSupport_section_bitShiftOp in \ref grp_utility_langSupport. */
    int64_t shiftRight(int64_t value, unsigned int n);
    uint8_t shiftRight(uint8_t value, unsigned int n);
    uint16_t shiftRight(uint16_t value, unsigned int n);
    uint32_t shiftRight(uint32_t value, unsigned int n);
    uint64_t shiftRight(uint64_t value, unsigned int n);

    // grp_utility_langSupport
    /*! @} */



    /*! \addtogroup grp_utility_gpUtil
    * @{
    */

    class Base_Nullable
    {
    public:
        Base_Nullable() : m_isNull(true) {}
        explicit Base_Nullable(bool isNull) : m_isNull(isNull) {}
        virtual ~Base_Nullable() {}

        bool isNull() const { return m_isNull; }
        
        virtual void makeNull() { m_isNull = true; }

    protected:
        void setIsNull(bool isNull) { m_isNull = isNull; }

    private:
        bool m_isNull;
    };

    template <typename T>
    class Nullable : public Base_Nullable
    {
    public:
        using value_type = T;
        using reference = value_type&;
        using const_reference = const value_type&;

    public:
        Nullable() : Base_Nullable(), m_value() {}
        Nullable(const_reference value) : Base_Nullable(false), m_value(value) {}
        virtual ~Nullable() {}

        const_reference get(const_reference fallback) const { return (isNull() ? fallback : m_value); }
        void set(const_reference value) { setIsNull(false); m_value = value; }

        virtual void free() { m_value = value_type(); }
        virtual void makeNull() { free(); Base_Nullable::makeNull(); }

        explicit operator value_type() const { return m_value; }

    protected:
        value_type m_value;
    };
    
    inline bool isNull(const omw::Base_Nullable& value) { return value.isNull(); }



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

    // grp_utility_gpUtil
    /*! @} */
}

#endif // IG_OMW_UTILITY_H
