/*
author          Oliver Blaser
date            27.01.2022
copyright       MIT - Copyright (c) 2022 Oliver Blaser
*/

#ifndef IG_OMW_INT_H
#define IG_OMW_INT_H

#include <cstddef>
#include <cstdint>

#include "../omw/intdef.h"

//#define OMWi_INT_RIGHTSHIFT_DEBUG (1) // def/undef

namespace omw
{
    /*! \addtogroup grp_utility_langSupport_typeSupport
    * @{
    */

    class Base_Int128
    {
    public:
        Base_Int128();
        Base_Int128(const omw::Base_Int128& other);
        Base_Int128(int64_t value);
        Base_Int128(uint64_t valueH, uint64_t valueL);
        Base_Int128(uint32_t valueHH, uint32_t valueLH, uint32_t valueHL, uint32_t valueLL);
        virtual ~Base_Int128() {}

        void set(uint64_t valueH, uint64_t valueL);
        void set(uint32_t valueHH, uint32_t valueLH, uint32_t valueHL, uint32_t valueLL);
        void sets(int64_t value);
        void sets(int64_t valueH, uint64_t valueL);
        void sets(int32_t valueHH, uint32_t valueLH, uint32_t valueHL, uint32_t valueLL);
        void sets(const uint8_t* data, size_t count);
        void setu(uint64_t value);
        void setu(const uint8_t* data, size_t count);

        uint64_t high() const { return m_h; }
        uint64_t hi() const { return high(); }
        int64_t highs() const;
        int64_t his() const { return highs(); }
        uint64_t low() const { return m_l; }
        uint64_t lo() const { return low(); }

        explicit operator bool() const { return (m_h || m_l); } /*!< If the value is 0, `false` is returned. `true` for any other value. */

    protected:
        uint64_t m_h;
        uint64_t m_l;

        void copy(const omw::Base_Int128& other);

    private:
        void readBuffer(const uint8_t* data, size_t count);

    public:
        //! \name Operators
        /// @{
        omw::Base_Int128& operator+=(const omw::Base_Int128& b);
        omw::Base_Int128& operator-=(const omw::Base_Int128& b);
        omw::Base_Int128& operator&=(const omw::Base_Int128& b);
        omw::Base_Int128& operator|=(const omw::Base_Int128& b);
        omw::Base_Int128& operator^=(const omw::Base_Int128& b);
        omw::Base_Int128& operator<<=(unsigned int count); /*!< See \ref grp_utility_langSupport_section_bitShiftOp in \ref grp_utility_langSupport. */

        omw::Base_Int128& operator++();
        omw::Base_Int128& operator--();
        omw::Base_Int128 operator++(int);
        omw::Base_Int128 operator--(int);
        /// @}
    };

    class SignedInt128 : public omw::Base_Int128
    {
    public:
        SignedInt128();
        SignedInt128(const omw::SignedInt128& other);
        SignedInt128(int64_t value);
        SignedInt128(uint64_t valueH, uint64_t valueL);
        SignedInt128(uint32_t valueHH, uint32_t valueLH, uint32_t valueHL, uint32_t valueLL);
        SignedInt128(const omw::Base_Int128& other);
        virtual ~SignedInt128() {}

        bool isNegative() const;
        int sign() const;

    public:
        //! \name Operators
        /// @{
        omw::SignedInt128& operator=(const omw::SignedInt128& b);
        omw::SignedInt128& operator>>=(unsigned int count); /*!< See \ref grp_utility_langSupport_section_bitShiftOp in \ref grp_utility_langSupport. */
        /// @}

#ifdef OMWi_INT_RIGHTSHIFT_DEBUG
        uint64_t oldValue_h, oldValue_l;
        uint64_t lastMask_h, lastMask_l;
#endif
    };

    class UnsignedInt128 : public omw::Base_Int128
    {
    public:
        UnsignedInt128();
        UnsignedInt128(const omw::UnsignedInt128& other);
        UnsignedInt128(int64_t value);
        UnsignedInt128(uint64_t valueH, uint64_t valueL);
        UnsignedInt128(uint32_t valueHH, uint32_t valueLH, uint32_t valueHL, uint32_t valueLL);
        UnsignedInt128(const omw::Base_Int128& other);
        virtual ~UnsignedInt128() {}

    public:
        //! \name Operators
        /// @{
        omw::UnsignedInt128& operator=(const omw::UnsignedInt128& b);
        omw::UnsignedInt128& operator>>=(unsigned int count); /*!< See \ref grp_utility_langSupport_section_bitShiftOp in \ref grp_utility_langSupport. */
        /// @}
    };

    //! \name Operators
    /// @{
    omw::SignedInt128 operator+(const omw::SignedInt128& a);
    omw::UnsignedInt128 operator+(const omw::UnsignedInt128& a);

    omw::SignedInt128 operator-(const omw::SignedInt128& a);
    omw::UnsignedInt128 operator-(const omw::UnsignedInt128& a);

    omw::SignedInt128 operator+(const omw::SignedInt128& a, const omw::Base_Int128& b);
    omw::UnsignedInt128 operator+(const omw::UnsignedInt128& a, const omw::Base_Int128& b);

    omw::SignedInt128 operator-(const omw::SignedInt128& a, const omw::Base_Int128& b);
    omw::UnsignedInt128 operator-(const omw::UnsignedInt128& a, const omw::Base_Int128& b);

    omw::SignedInt128 operator~(const omw::SignedInt128& a);
    omw::UnsignedInt128 operator~(const omw::UnsignedInt128& a);

    omw::SignedInt128 operator&(const omw::SignedInt128& a, const omw::Base_Int128& b);
    omw::UnsignedInt128 operator&(const omw::UnsignedInt128& a, const omw::Base_Int128& b);

    omw::SignedInt128 operator|(const omw::SignedInt128& a, const omw::Base_Int128& b);
    omw::UnsignedInt128 operator|(const omw::UnsignedInt128& a, const omw::Base_Int128& b);

    omw::SignedInt128 operator^(const omw::SignedInt128& a, const omw::Base_Int128& b);
    omw::UnsignedInt128 operator^(const omw::UnsignedInt128& a, const omw::Base_Int128& b);

    omw::SignedInt128 operator<<(const omw::SignedInt128& a, unsigned int count); /*!< See \ref grp_utility_langSupport_section_bitShiftOp in \ref grp_utility_langSupport. */
    omw::UnsignedInt128 operator<<(const omw::UnsignedInt128& a, unsigned int count); /*!< See \ref grp_utility_langSupport_section_bitShiftOp in \ref grp_utility_langSupport. */

    omw::SignedInt128 operator>>(const omw::SignedInt128& a, unsigned int count); /*!< See \ref grp_utility_langSupport_section_bitShiftOp in \ref grp_utility_langSupport. */
    omw::UnsignedInt128 operator>>(const omw::UnsignedInt128& a, unsigned int count); /*!< See \ref grp_utility_langSupport_section_bitShiftOp in \ref grp_utility_langSupport. */

    // All combinations of the comparison operators are needed to achieve sign awareness.
    bool operator==(const omw::SignedInt128& a, const omw::SignedInt128& b);
    bool operator!=(const omw::SignedInt128& a, const omw::SignedInt128& b);
    bool operator<(const omw::SignedInt128& a, const omw::SignedInt128& b);
    bool operator>(const omw::SignedInt128& a, const omw::SignedInt128& b);
    bool operator<=(const omw::SignedInt128& a, const omw::SignedInt128& b);
    bool operator>=(const omw::SignedInt128& a, const omw::SignedInt128& b);

    bool operator==(const omw::SignedInt128& a, const omw::UnsignedInt128& b);
    bool operator!=(const omw::SignedInt128& a, const omw::UnsignedInt128& b); /*!< Sign aware, see `omw::operator==(const omw::SignedInt128&, const omw::UnsignedInt128&)`. */
    bool operator<(const omw::SignedInt128& a, const omw::UnsignedInt128& b); /*!< Sign aware, see `omw::operator==(const omw::SignedInt128&, const omw::UnsignedInt128&)`. */
    bool operator>(const omw::SignedInt128& a, const omw::UnsignedInt128& b); /*!< Sign aware, see `omw::operator==(const omw::SignedInt128&, const omw::UnsignedInt128&)`. */
    bool operator<=(const omw::SignedInt128& a, const omw::UnsignedInt128& b); /*!< Sign aware, see `omw::operator==(const omw::SignedInt128&, const omw::UnsignedInt128&)`. */
    bool operator>=(const omw::SignedInt128& a, const omw::UnsignedInt128& b); /*!< Sign aware, see `omw::operator==(const omw::SignedInt128&, const omw::UnsignedInt128&)`. */

    bool operator==(const omw::UnsignedInt128& a, const omw::SignedInt128& b); /*!< Sign aware, see `omw::operator==(const omw::SignedInt128&, const omw::UnsignedInt128&)`. */
    bool operator!=(const omw::UnsignedInt128& a, const omw::SignedInt128& b); /*!< Sign aware, see `omw::operator==(const omw::SignedInt128&, const omw::UnsignedInt128&)`. */
    bool operator<(const omw::UnsignedInt128& a, const omw::SignedInt128& b); /*!< Sign aware, see `omw::operator==(const omw::SignedInt128&, const omw::UnsignedInt128&)`. */
    bool operator>(const omw::UnsignedInt128& a, const omw::SignedInt128& b); /*!< Sign aware, see `omw::operator==(const omw::SignedInt128&, const omw::UnsignedInt128&)`. */
    bool operator<=(const omw::UnsignedInt128& a, const omw::SignedInt128& b); /*!< Sign aware, see `omw::operator==(const omw::SignedInt128&, const omw::UnsignedInt128&)`. */
    bool operator>=(const omw::UnsignedInt128& a, const omw::SignedInt128& b); /*!< Sign aware, see `omw::operator==(const omw::SignedInt128&, const omw::UnsignedInt128&)`. */

    bool operator==(const omw::UnsignedInt128& a, const omw::UnsignedInt128& b);
    bool operator!=(const omw::UnsignedInt128& a, const omw::UnsignedInt128& b);
    bool operator<(const omw::UnsignedInt128& a, const omw::UnsignedInt128& b);
    bool operator>(const omw::UnsignedInt128& a, const omw::UnsignedInt128& b);
    bool operator<=(const omw::UnsignedInt128& a, const omw::UnsignedInt128& b);
    bool operator>=(const omw::UnsignedInt128& a, const omw::UnsignedInt128& b);
    /// @}

    using int128_t = omw::SignedInt128; /*!< Signed 128-bit integer type (`omw::SignedInt128`) */
    using uint128_t = omw::UnsignedInt128; /*!< Unsigned 128-bit integer type (`omw::UnsignedInt128`) */

    /*! @} */

    // move to bitset.h
    // 
    // bitset[0] = LSB / throws std::overflow_error if the value can not be represented
    //template<size_t N>
    //int128_t bitset_to_int128(const std::bitset<N>& bitset);
    //template<size_t N>
    //int128_t bitset_to_uint128(const std::bitset<N>& bitset);
    //template<size_t N>
    //std::bitset<N> to_bitset(const omw::Base_Int128& value);
}

/*! \addtogroup grp_utility_langSupport_typeSupport
* @{
*/

#define OMW_128BIT_ALL (omw::Base_Int128(OMW_64BIT_ALL, OMW_64BIT_ALL))
#define OMW_128BIT_LSB (omw::Base_Int128(0, OMW_64BIT_LSB))
#define OMW_128BIT_MSB (omw::Base_Int128(OMW_64BIT_MSB, 0))

#define OMW_INT128_MIN (omw::int128_t(OMW_64BIT_MSB, 0))
#define OMW_INT128_MAX (omw::int128_t(~OMW_64BIT_MSB, OMW_64BIT_ALL))
#define OMW_UINT128_MAX (omw::uint128_t(OMW_64BIT_ALL, OMW_64BIT_ALL))

/*! @} */

#endif // IG_OMW_INT_H
