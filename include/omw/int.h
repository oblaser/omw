/*
author          Oliver Blaser
date            15.12.2021
copyright       MIT - Copyright (c) 2021 Oliver Blaser
*/

#ifndef IG_OMW_OMWINT_H
#define IG_OMW_OMWINT_H

#include <cstdint>



/*! \addtogroup grp_utility_typeSupport
* @{
*/

#define OMW_8BIT_ALL (0xFF)
#define OMW_8BIT_LSB (0x01)
#define OMW_8BIT_MSB (0x80)

#define OMW_16BIT_ALL (0xFFFF)
#define OMW_16BIT_LSB (0x00001)
#define OMW_16BIT_MSB (0x80000)

#define OMW_32BIT_ALL (0xFFFFFFFF)
#define OMW_32BIT_LSB (0x00000001)
#define OMW_32BIT_MSB (0x80000000)

#define OMW_64BIT_ALL (0xFFFFFFFFFFFFFFFF)
#define OMW_64BIT_LSB (0x0000000000000001)
#define OMW_64BIT_MSB (0x8000000000000000)

/*! @} */

namespace omw
{
    /*! \addtogroup grp_utility_typeSupport
    * @{
    */

    class Base_Int128
    {
    public:
        Base_Int128();
        Base_Int128(const omw::Base_Int128& other);
        explicit Base_Int128(int64_t value);
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

        explicit operator bool() const { return (m_h || m_l); }

    protected:
        static constexpr size_t baseTypeWith = 64;
        using base_type = uint64_t;
        static constexpr base_type baseTypeAllBits = OMW_64BIT_ALL;
        base_type m_h;
        base_type m_l;

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
        omw::Base_Int128& operator<<=(unsigned int count);
        omw::Base_Int128& operator>>=(unsigned int count);

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
        SignedInt128(const uint8_t* data, size_t count);
        SignedInt128(const omw::Base_Int128& other);
        virtual ~SignedInt128() {}

        bool isNegative() const;
        int sign() const;

    public:
        //! \name Operators
        /// @{
        omw::SignedInt128& operator=(const omw::SignedInt128& b);
        /// @}
    };

    class UnsignedInt128 : public omw::Base_Int128
    {
    public:
        UnsignedInt128();
        UnsignedInt128(const omw::UnsignedInt128& other);
        UnsignedInt128(int64_t value);
        UnsignedInt128(uint64_t valueH, uint64_t valueL);
        UnsignedInt128(uint32_t valueHH, uint32_t valueLH, uint32_t valueHL, uint32_t valueLL);
        UnsignedInt128(const uint8_t* data, size_t count);
        UnsignedInt128(const omw::Base_Int128& other);
        virtual ~UnsignedInt128() {}

    public:
        //! \name Operators
        /// @{
        omw::UnsignedInt128& operator=(const omw::UnsignedInt128& b);
        /// @}
    };

    //! \name Operators
    /// @{
    omw::SignedInt128 operator+(const omw::SignedInt128& a);
    omw::UnsignedInt128 operator+(const omw::UnsignedInt128& a);

    omw::SignedInt128 operator-(const omw::SignedInt128& a);
    omw::UnsignedInt128 operator-(const omw::UnsignedInt128& a);

    omw::Base_Int128 operator+(const omw::Base_Int128& a, const omw::Base_Int128& b);
    omw::SignedInt128 operator+(const omw::SignedInt128& a, const omw::SignedInt128& b);
    omw::UnsignedInt128 operator+(const omw::UnsignedInt128& a, const omw::UnsignedInt128& b);

    omw::Base_Int128 operator-(const omw::Base_Int128& a, const omw::Base_Int128& b);
    omw::SignedInt128 operator-(const omw::SignedInt128& a, const omw::SignedInt128& b);
    omw::UnsignedInt128 operator-(const omw::UnsignedInt128& a, const omw::UnsignedInt128& b);

    omw::SignedInt128 operator~(const omw::SignedInt128& a);
    omw::UnsignedInt128 operator~(const omw::UnsignedInt128& a);

    omw::Base_Int128 operator&(const omw::Base_Int128& a, const omw::Base_Int128& b);
    omw::SignedInt128 operator&(const omw::SignedInt128& a, const omw::SignedInt128& b);
    omw::UnsignedInt128 operator&(const omw::UnsignedInt128& a, const omw::UnsignedInt128& b);

    omw::Base_Int128 operator|(const omw::Base_Int128& a, const omw::Base_Int128& b);
    omw::SignedInt128 operator|(const omw::SignedInt128& a, const omw::SignedInt128& b);
    omw::UnsignedInt128 operator|(const omw::UnsignedInt128& a, const omw::UnsignedInt128& b);

    omw::Base_Int128 operator^(const omw::Base_Int128& a, const omw::Base_Int128& b);
    omw::SignedInt128 operator^(const omw::SignedInt128& a, const omw::SignedInt128& b);
    omw::UnsignedInt128 operator^(const omw::UnsignedInt128& a, const omw::UnsignedInt128& b);

    omw::Base_Int128 operator<<(const omw::Base_Int128& a, unsigned int count);
    omw::SignedInt128 operator<<(const omw::SignedInt128& a, unsigned int count);
    omw::UnsignedInt128 operator<<(const omw::UnsignedInt128& a, unsigned int count);

    omw::Base_Int128 operator>>(const omw::Base_Int128& a, unsigned int count);
    omw::SignedInt128 operator>>(const omw::SignedInt128& a, unsigned int count);
    omw::UnsignedInt128 operator>>(const omw::UnsignedInt128& a, unsigned int count);

    bool operator==(const omw::SignedInt128& a, const omw::SignedInt128& b);
    bool operator!=(const omw::SignedInt128& a, const omw::SignedInt128& b);
    bool operator<(const omw::SignedInt128& a, const omw::SignedInt128& b);
    bool operator>(const omw::SignedInt128& a, const omw::SignedInt128& b);
    bool operator<=(const omw::SignedInt128& a, const omw::SignedInt128& b);
    bool operator>=(const omw::SignedInt128& a, const omw::SignedInt128& b);

    bool operator==(const omw::SignedInt128& a, const omw::UnsignedInt128& b); /*!< Takes care of the signedness. */
    bool operator!=(const omw::SignedInt128& a, const omw::UnsignedInt128& b);
    bool operator<(const omw::SignedInt128& a, const omw::UnsignedInt128& b);
    bool operator>(const omw::SignedInt128& a, const omw::UnsignedInt128& b);
    bool operator<=(const omw::SignedInt128& a, const omw::UnsignedInt128& b);
    bool operator>=(const omw::SignedInt128& a, const omw::UnsignedInt128& b);

    bool operator==(const omw::UnsignedInt128& a, const omw::SignedInt128& b);
    bool operator!=(const omw::UnsignedInt128& a, const omw::SignedInt128& b);
    bool operator<(const omw::UnsignedInt128& a, const omw::SignedInt128& b);
    bool operator>(const omw::UnsignedInt128& a, const omw::SignedInt128& b);
    bool operator<=(const omw::UnsignedInt128& a, const omw::SignedInt128& b);
    bool operator>=(const omw::UnsignedInt128& a, const omw::SignedInt128& b);

    bool operator==(const omw::UnsignedInt128& a, const omw::UnsignedInt128& b);
    bool operator!=(const omw::UnsignedInt128& a, const omw::UnsignedInt128& b);
    bool operator<(const omw::UnsignedInt128& a, const omw::UnsignedInt128& b);
    bool operator>(const omw::UnsignedInt128& a, const omw::UnsignedInt128& b);
    bool operator<=(const omw::UnsignedInt128& a, const omw::UnsignedInt128& b);
    bool operator>=(const omw::UnsignedInt128& a, const omw::UnsignedInt128& b);
    /// @}

    using int128_t = omw::SignedInt128;
    using uint128_t = omw::UnsignedInt128;

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

/*! \addtogroup grp_utility_typeSupport
* @{
*/

#define OMW_128BIT_ALL (omw::Base_Int128(OMW_64BIT_ALL, OMW_64BIT_ALL))
#define OMW_128BIT_LSB (omw::Base_Int128(0, OMW_64BIT_LSB))
#define OMW_128BIT_MSB (omw::Base_Int128(OMW_64BIT_MSB, 0))

#define OMW_INT128_MIN (omw::int128_t(OMW_64BIT_MSB, 0))
#define OMW_INT128_MAX (omw::int128_t(~OMW_64BIT_MSB, OMW_64BIT_ALL))
#define OMW_UINT128_MAX (omw::uint128_t(OMW_64BIT_ALL, OMW_64BIT_ALL))

/*! @} */

#endif // IG_OMW_OMWINT_H
