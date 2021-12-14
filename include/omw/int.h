/*
author          Oliver Blaser
date            13.12.2021
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

    class SignedInt128;
    class UnsignedInt128;

    class Base_Int128
    {
    public:
        Base_Int128();
        Base_Int128(const omw::Base_Int128& other);
        Base_Int128(int64_t value);
        Base_Int128(uint64_t valueH, uint64_t valueL);
        Base_Int128(uint32_t valueHH, uint32_t valueLH, uint32_t valueHL, uint32_t valueLL);
        virtual ~Base_Int128() {}

        void set(int value);
        void set(unsigned int value);
        void set(uint64_t valueH, uint64_t valueL);
        void set(uint32_t valueHH, uint32_t valueLH, uint32_t valueHL, uint32_t valueLL);
        void set(const uint8_t* data, size_t count);

        //! \name set signed
        /// @{
        void sets(int64_t value);
        void sets(int64_t valueH, uint64_t valueL);
        void sets(int32_t valueHH, uint32_t valueLH, uint32_t valueHL, uint32_t valueLL);
        void sets(const uint8_t* data, size_t count);
        /// @}

        //! \name set unsigned
        /// @{
        void setu(uint64_t value);
        void setu(const uint8_t* data, size_t count);
        /// @}

        uint64_t high() const { return m_h; }
        uint64_t hi() const { return high(); }
        uint64_t low() const { return m_l; }
        uint64_t lo() const { return low(); }

    protected:
        uint64_t m_h;
        uint64_t m_l;

        void copy(const omw::Base_Int128& other);

    private:
        void readBuffer(const uint8_t* data, size_t count);

    public:
        omw::Base_Int128& operator+=(const omw::Base_Int128& b);
        omw::Base_Int128& operator-=(const omw::Base_Int128& b);
        //omw::Base_Int128& operator*=(const omw::Base_Int128& b);
        //omw::Base_Int128& operator/=(const omw::Base_Int128& b);
        //omw::Base_Int128& operator%=(const omw::Base_Int128& b);
        omw::Base_Int128& operator&=(const omw::Base_Int128& b);
        omw::Base_Int128& operator|=(const omw::Base_Int128& b);
        omw::Base_Int128& operator^=(const omw::Base_Int128& b);
        omw::Base_Int128& operator<<=(unsigned int count);
        omw::Base_Int128& operator>>=(unsigned int count);

        omw::Base_Int128& operator++();
        omw::Base_Int128& operator--();
        omw::Base_Int128 operator++(int);
        omw::Base_Int128 operator--(int);

    public:
        friend omw::Base_Int128 operator+(const omw::Base_Int128& a);
        friend omw::SignedInt128 operator+(const omw::SignedInt128& a);
        friend omw::UnsignedInt128 operator+(const omw::UnsignedInt128& a);

        friend omw::Base_Int128 operator-(const omw::Base_Int128& a);
        friend omw::SignedInt128 operator-(const omw::SignedInt128& a);
        friend omw::UnsignedInt128 operator-(const omw::UnsignedInt128& a);

        friend omw::Base_Int128 operator+(const omw::Base_Int128& a, const omw::Base_Int128& b);
        friend omw::SignedInt128 operator+(const omw::SignedInt128& a, const omw::Base_Int128& b);
        friend omw::UnsignedInt128 operator+(const omw::UnsignedInt128& a, const omw::Base_Int128& b);

        friend omw::Base_Int128 operator-(const omw::Base_Int128& a, const omw::Base_Int128& b);
        friend omw::SignedInt128 operator-(const omw::SignedInt128& a, const omw::Base_Int128& b);
        friend omw::UnsignedInt128 operator-(const omw::UnsignedInt128& a, const omw::Base_Int128& b);

        //friend omw::Base_Int128 operator*(const omw::Base_Int128& a, const omw::Base_Int128& b);
        //friend omw::SignedInt128 operator(const omw::SignedInt128& a, const omw::Base_Int128& b);
        //friend omw::UnsignedInt128 operator(const omw::UnsignedInt128& a, const omw::Base_Int128& b);

        //friend omw::Base_Int128 operator/(const omw::Base_Int128& a, const omw::Base_Int128& b);
        //friend omw::SignedInt128 operator/(const omw::SignedInt128& a, const omw::Base_Int128& b);
        //friend omw::UnsignedInt128 operator/(const omw::UnsignedInt128& a, const omw::Base_Int128& b);

        //friend omw::Base_Int128 operator%(const omw::Base_Int128& a, const omw::Base_Int128& b);
        //friend omw::SignedInt128 operator%(const omw::SignedInt128& a, const omw::Base_Int128& b);
        //friend omw::UnsignedInt128 operator%(const omw::UnsignedInt128& a, const omw::Base_Int128& b);

        friend omw::Base_Int128 operator~(const omw::Base_Int128& a);
        friend omw::SignedInt128 operator~(const omw::SignedInt128& a);
        friend omw::UnsignedInt128 operator~(const omw::UnsignedInt128& a);

        friend omw::Base_Int128 operator&(const omw::Base_Int128& a, const omw::Base_Int128& b);
        friend omw::SignedInt128 operator&(const omw::SignedInt128& a, const omw::Base_Int128& b);
        friend omw::UnsignedInt128 operator&(const omw::UnsignedInt128& a, const omw::Base_Int128& b);

        friend omw::Base_Int128 operator|(const omw::Base_Int128& a, const omw::Base_Int128& b);
        friend omw::SignedInt128 operator|(const omw::SignedInt128& a, const omw::Base_Int128& b);
        friend omw::UnsignedInt128 operator|(const omw::UnsignedInt128& a, const omw::Base_Int128& b);

        friend omw::Base_Int128 operator^(const omw::Base_Int128& a, const omw::Base_Int128& b);
        friend omw::SignedInt128 operator^(const omw::SignedInt128& a, const omw::Base_Int128& b);
        friend omw::UnsignedInt128 operator^(const omw::UnsignedInt128& a, const omw::Base_Int128& b);

        friend omw::Base_Int128 operator<<(const omw::Base_Int128& val, unsigned int count);
        friend omw::SignedInt128 operator<<(const omw::SignedInt128& a, const omw::Base_Int128& b);
        friend omw::UnsignedInt128 operator<<(const omw::UnsignedInt128& a, const omw::Base_Int128& b);

        friend omw::Base_Int128 operator>>(const omw::Base_Int128& val, unsigned int count);
        friend omw::SignedInt128 operator>>(const omw::SignedInt128& a, const omw::Base_Int128& b);
        friend omw::UnsignedInt128 operator>>(const omw::UnsignedInt128& a, const omw::Base_Int128& b);

        explicit operator bool() const { return (m_h || m_l); }

        friend bool operator==(const omw::SignedInt128& a, const omw::SignedInt128& b);
        friend bool operator==(const omw::SignedInt128& a, const omw::UnsignedInt128& b);
        friend bool operator==(const omw::UnsignedInt128& a, const omw::SignedInt128& b);
        friend bool operator==(const omw::UnsignedInt128& a, const omw::UnsignedInt128& b);
        friend bool operator==(int a, const omw::SignedInt128& b) { return (omw::SignedInt128(a) == b); }
        friend bool operator==(int a, const omw::UnsignedInt128& b) { return (omw::SignedInt128(a) == b); }
        friend bool operator==(const omw::SignedInt128& a, int b) { return (a == omw::SignedInt128(b)); }
        friend bool operator==(const omw::UnsignedInt128& a, int b) { return (a == omw::SignedInt128(b)); }

        friend bool operator!=(const omw::SignedInt128& a, const omw::SignedInt128& b);
        friend bool operator!=(const omw::SignedInt128& a, const omw::UnsignedInt128& b);
        friend bool operator!=(const omw::UnsignedInt128& a, const omw::SignedInt128& b);
        friend bool operator!=(const omw::UnsignedInt128& a, const omw::UnsignedInt128& b);
        friend bool operator!=(int a, const omw::SignedInt128& b);
        friend bool operator!=(int a, const omw::UnsignedInt128& b);
        friend bool operator!=(const omw::SignedInt128& a, int b);
        friend bool operator!=(const omw::UnsignedInt128& a, int b);

        friend bool operator<(const omw::SignedInt128& a, const omw::SignedInt128& b);
        friend bool operator<(const omw::SignedInt128& a, const omw::UnsignedInt128& b);
        friend bool operator<(const omw::UnsignedInt128& a, const omw::SignedInt128& b);
        friend bool operator<(const omw::UnsignedInt128& a, const omw::UnsignedInt128& b);
        friend bool operator<(int a, const omw::SignedInt128& b);
        friend bool operator<(int a, const omw::UnsignedInt128& b);
        friend bool operator<(const omw::SignedInt128& a, int b);
        friend bool operator<(const omw::UnsignedInt128& a, int b);

        friend bool operator>(const omw::SignedInt128& a, const omw::SignedInt128& b);
        friend bool operator>(const omw::SignedInt128& a, const omw::UnsignedInt128& b);
        friend bool operator>(const omw::UnsignedInt128& a, const omw::SignedInt128& b);
        friend bool operator>(const omw::UnsignedInt128& a, const omw::UnsignedInt128& b);
        friend bool operator>(int a, const omw::SignedInt128& b);
        friend bool operator>(int a, const omw::UnsignedInt128& b);
        friend bool operator>(const omw::SignedInt128& a, int b);
        friend bool operator>(const omw::UnsignedInt128& a, int b);

        friend bool operator<=(const omw::SignedInt128& a, const omw::SignedInt128& b);
        friend bool operator<=(const omw::SignedInt128& a, const omw::UnsignedInt128& b);
        friend bool operator<=(const omw::UnsignedInt128& a, const omw::SignedInt128& b);
        friend bool operator<=(const omw::UnsignedInt128& a, const omw::UnsignedInt128& b);
        friend bool operator<=(int a, const omw::SignedInt128& b);
        friend bool operator<=(int a, const omw::UnsignedInt128& b);
        friend bool operator<=(const omw::SignedInt128& a, int b);
        friend bool operator<=(const omw::UnsignedInt128& a, int b);

        friend bool operator>=(const omw::SignedInt128& a, const omw::SignedInt128& b);
        friend bool operator>=(const omw::SignedInt128& a, const omw::UnsignedInt128& b);
        friend bool operator>=(const omw::UnsignedInt128& a, const omw::SignedInt128& b);
        friend bool operator>=(const omw::UnsignedInt128& a, const omw::UnsignedInt128& b);
        friend bool operator>=(int a, const omw::SignedInt128& b);
        friend bool operator>=(int a, const omw::UnsignedInt128& b);
        friend bool operator>=(const omw::SignedInt128& a, int b);
        friend bool operator>=(const omw::UnsignedInt128& a, int b);
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
        explicit SignedInt128(const omw::Base_Int128& other);
        virtual ~SignedInt128() {}

        using omw::Base_Int128::set;
        void set(int64_t value);

        int64_t high() const;
        uint64_t high_ui() const { return m_h; }
        int64_t hi() const { return high(); }
        uint64_t hi_ui() const { return high_ui(); }

        bool isNegative() const;
        int sign() const;

        explicit operator omw::UnsignedInt128() const;

    public:
        omw::SignedInt128& operator+=(const omw::SignedInt128& b);
        omw::SignedInt128& operator-=(const omw::SignedInt128& b);
        //omw::SignedInt128& operator*=(const omw::SignedInt128& b);
        //omw::SignedInt128& operator/=(const omw::SignedInt128& b);
        //omw::SignedInt128& operator%=(const omw::SignedInt128& b);
        omw::SignedInt128& operator&=(const omw::SignedInt128& b);
        omw::SignedInt128& operator|=(const omw::SignedInt128& b);
        omw::SignedInt128& operator^=(const omw::SignedInt128& b);
        omw::SignedInt128& operator<<=(unsigned int count);
        omw::SignedInt128& operator>>=(unsigned int count);

        omw::SignedInt128& operator++();
        omw::SignedInt128& operator--();
        omw::SignedInt128 operator++(int);
        omw::SignedInt128 operator--(int);
    };

    class UnsignedInt128 : public omw::Base_Int128
    {
    public:
        UnsignedInt128();
        UnsignedInt128(const omw::UnsignedInt128& other);
        UnsignedInt128(uint64_t value);
        UnsignedInt128(uint64_t valueH, uint64_t valueL);
        UnsignedInt128(uint32_t valueHH, uint32_t valueLH, uint32_t valueHL, uint32_t valueLL);
        UnsignedInt128(const uint8_t* data, size_t count);
        explicit UnsignedInt128(const omw::Base_Int128& other);
        virtual ~UnsignedInt128() {}

        using omw::Base_Int128::set;
        void set(uint64_t value);

        explicit operator omw::SignedInt128() const;

    public:
        omw::UnsignedInt128& operator+=(const omw::UnsignedInt128& b);
        omw::UnsignedInt128& operator-=(const omw::UnsignedInt128& b);
        //omw::UnsignedInt128& operator*=(const omw::UnsignedInt128& b);
        //omw::UnsignedInt128& operator/=(const omw::UnsignedInt128& b);
        //omw::UnsignedInt128& operator%=(const omw::UnsignedInt128& b);
        omw::UnsignedInt128& operator&=(const omw::UnsignedInt128& b);
        omw::UnsignedInt128& operator|=(const omw::UnsignedInt128& b);
        omw::UnsignedInt128& operator^=(const omw::UnsignedInt128& b);
        omw::UnsignedInt128& operator<<=(unsigned int count);
        omw::UnsignedInt128& operator>>=(unsigned int count);

        omw::UnsignedInt128& operator++();
        omw::UnsignedInt128& operator--();
        omw::UnsignedInt128 operator++(int);
        omw::UnsignedInt128 operator--(int);
    };

    using int128_t = omw::SignedInt128;
    using uint128_t = omw::UnsignedInt128;

    /*! @} */

    // move to bitset.h
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

#ifndef OMWi_DOXYGEN_EXCLUDE_FROM_DOC
template<class T>
T OMWi_128bit_all() { return T(OMW_64BIT_ALL, OMW_64BIT_ALL); }
template omw::int128_t OMWi_128bit_all();
template omw::uint128_t OMWi_128bit_all();
template<class T>
T OMWi_128bit_lsb() { return T(0, OMW_64BIT_LSB); }
template omw::int128_t OMWi_128bit_lsb();
template omw::uint128_t OMWi_128bit_lsb();
template<class T>
T OMWi_128bit_msb() { return T(OMW_64BIT_ALL, OMW_64BIT_ALL); }
template omw::int128_t OMWi_128bit_msb();
template omw::uint128_t OMWi_128bit_msb();
#endif // OMWi_DOXYGEN_EXCLUDE_FROM_DOC

//! @param type Either <tt><b>omw::int128_t</b></tt> (`omw::SignedInt128`) or <tt><b>omw::uint128_t</b></tt> (`omw::UnsignedInt128`)
#define OMW_128BIT_ALL(type) (OMWi_128bit_all<type>())
//! @param type Either <tt><b>omw::int128_t</b></tt> (`omw::SignedInt128`) or <tt><b>omw::uint128_t</b></tt> (`omw::UnsignedInt128`)
#define OMW_128BIT_LSB(type) (OMWi_128bit_lsb<type>())
//! @param type Either <tt><b>omw::int128_t</b></tt> (`omw::SignedInt128`) or <tt><b>omw::uint128_t</b></tt> (`omw::UnsignedInt128`)
#define OMW_128BIT_MSB(type) (OMWi_128bit_msb<type>())

#define OMW_INT128_MIN (omw::int128_t(OMW_64BIT_MSB, 0))
#define OMW_INT128_MAX (omw::int128_t(~OMW_64BIT_MSB, OMW_64BIT_ALL))
#define OMW_UINT128_MAX (omw::uint128_t(OMW_64BIT_ALL, OMW_64BIT_ALL))

/*! @} */

#endif // IG_OMW_OMWINT_H
