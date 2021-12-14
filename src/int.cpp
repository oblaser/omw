/*
author          Oliver Blaser
date            13.12.2021
copyright       MIT - Copyright (c) 2021 Oliver Blaser
*/

#include <stdexcept>

#include "omw/int.h"

#define N_BYTES_128 (16) // 16 * 8 bit = 128 bit

namespace
{
    int64_t to_i64(uint64_t value) noexcept { return *(reinterpret_cast<int64_t*>(&value)); }
    uint64_t to_ui64(int64_t value) noexcept { return *(reinterpret_cast<uint64_t*>(&value)); }

    void quad_ui32_to_128(uint64_t& h, uint64_t& l, uint32_t valueHH, uint32_t valueLH, uint32_t valueHL, uint32_t valueLL)
    {
        h = valueHH;
        h <<= 32;
        h |= valueLH;

        l = valueHL;
        l <<= 32;
        l |= valueLL;
    }
    void quad_i32_to_128(uint64_t& h, uint64_t& l, int32_t valueHH, uint32_t valueLH, uint32_t valueHL, uint32_t valueLL)
    {
        quad_ui32_to_128(h, l, to_ui64(valueHH), valueLH, valueHL, valueLL);
    }

    void func()
    {
        omw::uint128_t a = 9;
        omw::uint128_t b = OMW_128BIT_MSB(omw::uint128_t);

        if (a) { b = 10; }
        if (!a && 3) { b = 10; }

        char chr = 4;
        omw::uint128_t c = omw::uint128_t(chr);
        c = omw::uint128_t(-5);
        omw::int128_t sc = omw::int128_t(chr);
        c = (a + b);
        c = 300000000 + b;
        c = 3 + b;
        c = a + 4;

        c = 3 + 3;

        c += 5;

        omw::int128_t x = -1;
        x.set(2);
    }
}



omw::Base_Int128::Base_Int128()
    : m_h(0), m_l(0)
{}

omw::Base_Int128::Base_Int128(const omw::Base_Int128& other)
    : m_h(0), m_l(0)
{
    copy(other);
}

omw::Base_Int128::Base_Int128(int64_t value)
    : m_h(0), m_l(0)
{
    sets(value);
}

omw::Base_Int128::Base_Int128(uint64_t valueH, uint64_t valueL)
    : m_h(valueH), m_l(valueL)
{}

omw::Base_Int128::Base_Int128(uint32_t valueHH, uint32_t valueLH, uint32_t valueHL, uint32_t valueLL)
    : m_h(0), m_l(0)
{
    set(valueHH, valueLH, valueHL, valueLL);
}

void omw::Base_Int128::set(int value)
{
    sets(value);
}

void omw::Base_Int128::set(unsigned int value)
{
    m_h = 0;
    m_l = value;
}

void omw::Base_Int128::set(uint64_t valueH, uint64_t valueL)
{
    m_h = valueH;
    m_l = valueL;
}

void omw::Base_Int128::set(uint32_t valueHH, uint32_t valueLH, uint32_t valueHL, uint32_t valueLL)
{
    quad_ui32_to_128(m_h, m_l, valueHH, valueLH, valueHL, valueLL);
}

//! @param data Pointer to a big endian byte buffer
//! @param count Number of bytes to read
//! 
//! Parses the value from a byte buffer.
//! 
//! Alias for `omw::Base_Int128::setu(const uint8_t*, size_t)`.
//! 
void omw::Base_Int128::set(const uint8_t* data, size_t count)
{
    setu(data, count);
}

void omw::Base_Int128::sets(int64_t value)
{
    m_l = ::to_ui64(value);

    if (m_l & OMW_64BIT_MSB) m_h = OMW_64BIT_ALL;
    else m_h = 0;
}

void omw::Base_Int128::sets(int64_t valueH, uint64_t valueL)
{
    m_h = ::to_ui64(valueH);
    m_l = valueL;
}

void omw::Base_Int128::sets(int32_t valueHH, uint32_t valueLH, uint32_t valueHL, uint32_t valueLL)
{
    quad_i32_to_128(m_h, m_l, valueHH, valueLH, valueHL, valueLL);
}

//! @param data Pointer to a big endian byte buffer
//! @param count Number of bytes to read
//! 
//! Parses the value from a byte buffer.
//! 
//! If `data` or `count` is `0`, the object remains unchanged.
//! 
//! \b Exceptions
//! - `std::overflow_error` if count is greater than 16
//! 
void omw::Base_Int128::sets(const uint8_t* data, size_t count)
{
    if (data)
    {
        if (count > 0)
        {
            if (count > N_BYTES_128) throw std::overflow_error("omw::Base_Int128::sets");

            if (data[0] & 0x80) set(OMW_64BIT_ALL, OMW_64BIT_ALL);
            else setu(0);

            readBuffer(data, count);
        }
    }
}

void omw::Base_Int128::setu(uint64_t value)
{
    m_h = 0;
    m_l = value;
}

//! @param data Pointer to a big endian byte buffer
//! @param count Number of bytes to read
//! 
//! Parses the value from a byte buffer.
//! 
//! If `data` or `count` is `0`, the object remains unchanged.
//! 
//! \b Exceptions
//! - `std::overflow_error` if count is greater than 16
//! 
void omw::Base_Int128::setu(const uint8_t* data, size_t count)
{
    if (data)
    {
        if (count > 0)
        {
            if (count > N_BYTES_128) throw std::overflow_error("omw::Base_Int128::setu");

            setu(0);
            readBuffer(data, count);
        }
    }
}

void omw::Base_Int128::copy(const omw::Base_Int128& other)
{
    this->m_h = other.hi();
    this->m_l = other.lo();
}

void omw::Base_Int128::readBuffer(const uint8_t* data, size_t count)
{
    for (size_t i = 0; i < count; ++i)
    {
        *this <<= 8;
        *this |= data[i];
    }
}

omw::Base_Int128& omw::Base_Int128::operator+=(const omw::Base_Int128& b)
{
    const omw::Base_Int128 r = *this + b;
    this->copy(r);
    return *this;
}

omw::Base_Int128& omw::Base_Int128::operator-=(const omw::Base_Int128& b)
{
    const omw::Base_Int128 r = *this - b;
    this->copy(r);
    return *this;
}

omw::Base_Int128& omw::Base_Int128::operator++()
{
    *this += omw::Base_Int128(0, 1);
    return *this;
}

omw::Base_Int128& omw::Base_Int128::operator--()
{
    *this -= omw::Base_Int128(0, 1);
    return *this;
}

omw::Base_Int128 omw::Base_Int128::operator++(int)
{
    const omw::Base_Int128 tmp = *this;
    ++(*this);
    return tmp;
}

omw::Base_Int128 omw::Base_Int128::operator--(int)
{
    const omw::Base_Int128 tmp = *this;
    --(*this);
    return tmp;
}



omw::SignedInt128::SignedInt128()
    : omw::Base_Int128()
{}

omw::SignedInt128::SignedInt128(const omw::SignedInt128& other)
    : omw::Base_Int128(other)
{}

//! @param value 
//! 
//! Uses `omw::Base_Int128::sets(int64_t)` to initialize.
//! 
omw::SignedInt128::SignedInt128(int64_t value)
    : omw::Base_Int128()
{
    sets(value);
}

omw::SignedInt128::SignedInt128(uint64_t valueH, uint64_t valueL)
    : omw::Base_Int128(valueH, valueL)
{}

omw::SignedInt128::SignedInt128(uint32_t valueHH, uint32_t valueLH, uint32_t valueHL, uint32_t valueLL)
    : omw::Base_Int128(valueHH, valueLH, valueHL, valueLL)
{}

//! @param data 
//! @param count 
//! 
//! Uses `omw::Base_Int128::sets(const uint8_t*, size_t)` to initialize.
//! 
omw::SignedInt128::SignedInt128(const uint8_t* data, size_t count)
    : omw::Base_Int128()
{
    sets(data, count);
}

omw::SignedInt128::SignedInt128(const omw::Base_Int128& other)
    : omw::Base_Int128(other)
{}

//! @param value 
//! 
//! See `omw::Base_Int128::sets(int64_t)`.
//! 
void omw::SignedInt128::set(int64_t value)
{
    sets(value);
}

int64_t omw::SignedInt128::high() const
{
    return ::to_i64(m_h);
}

bool omw::SignedInt128::isNegative() const
{
    return (high_ui() & OMW_64BIT_MSB);
}

//! @return `-1` if the value is negative, `1` otherwise
//! 
//! Caution! For the mathematical sign (signum) function see `omw::sign()`.
//! 
int omw::SignedInt128::sign() const
{
    return (isNegative() ? -1 : 1);
}

//! @brief Bit equal conversion to `omw::UnsignedInt128`.
omw::SignedInt128::operator omw::UnsignedInt128() const
{
    return omw::UnsignedInt128(*this);
}



omw::UnsignedInt128::UnsignedInt128()
    : omw::Base_Int128()
{}

omw::UnsignedInt128::UnsignedInt128(const omw::UnsignedInt128& other)
    : omw::Base_Int128(other)
{}

omw::UnsignedInt128::UnsignedInt128(uint64_t value)
    : omw::Base_Int128(0, value)
{}

omw::UnsignedInt128::UnsignedInt128(uint64_t valueH, uint64_t valueL)
    : omw::Base_Int128(valueH, valueL)
{}

omw::UnsignedInt128::UnsignedInt128(uint32_t valueHH, uint32_t valueLH, uint32_t valueHL, uint32_t valueLL)
    : omw::Base_Int128(valueHH, valueLH, valueHL, valueLL)
{}

//! @param data 
//! @param count 
//! 
//! Uses `omw::Base_Int128::setu(const uint8_t*, size_t)` to initialize.
//! 
omw::UnsignedInt128::UnsignedInt128(const uint8_t* data, size_t count)
    : omw::Base_Int128()
{
    setu(data, count);
}

omw::UnsignedInt128::UnsignedInt128(const omw::Base_Int128& other)
    : omw::Base_Int128(other)
{}

void omw::UnsignedInt128::set(uint64_t value)
{
    m_h = 0;
    m_l = value;
}

//! @brief Bit equal conversion to `omw::SignedInt128`.
omw::UnsignedInt128::operator omw::SignedInt128() const
{
    return omw::SignedInt128(*this);
}



omw::Base_Int128 omw::operator+(const omw::Base_Int128& a)
{
    return a;
}

omw::SignedInt128 omw::operator+(const omw::SignedInt128& a)
{
    return a;
}

omw::UnsignedInt128 omw::operator+(const omw::UnsignedInt128& a)
{
    return omw::UnsignedInt128();
}

omw::Base_Int128 omw::operator-(const omw::Base_Int128& a)
{
    omw::Base_Int128 tmp = ~a;
    ++tmp;
    return tmp;
}

omw::SignedInt128 omw::operator-(const omw::SignedInt128& a)
{
    const omw::Base_Int128 tmp = a;
    return omw::SignedInt128(-tmp);
}

omw::UnsignedInt128 omw::operator-(const omw::UnsignedInt128& a)
{
    const omw::Base_Int128 tmp = a;
    return omw::UnsignedInt128(-tmp);
}

omw::Base_Int128 omw::operator+(const omw::Base_Int128& a, const omw::Base_Int128& b)
{
    uint64_t h = a.hi() + b.hi();
    uint64_t l = a.lo() + b.lo();
    if (l == 0) ++h;
    return omw::Base_Int128(h, l);
}

omw::SignedInt128 omw::operator+(const omw::SignedInt128& a, const omw::Base_Int128& b)
{
    const omw::Base_Int128 tmpA = a;
    return omw::SignedInt128(tmpA + b);
}

omw::UnsignedInt128 omw::operator+(const omw::UnsignedInt128& a, const omw::Base_Int128& b)
{
    const omw::Base_Int128 tmpA = a;
    return omw::UnsignedInt128(tmpA + b);
}

omw::Base_Int128 omw::operator-(const omw::Base_Int128& a, const omw::Base_Int128& b)
{
    return a + -b;
}

omw::SignedInt128 omw::operator-(const omw::SignedInt128& a, const omw::Base_Int128& b)
{
    const omw::Base_Int128 tmpA = a;
    return omw::SignedInt128(tmpA - b);
}

omw::UnsignedInt128 omw::operator-(const omw::UnsignedInt128& a, const omw::Base_Int128& b)
{
    const omw::Base_Int128 tmpA = a;
    return omw::UnsignedInt128(tmpA - b);
}

omw::Base_Int128 omw::operator~(const omw::Base_Int128& a)
{
    return omw::Base_Int128(~a.hi(), ~a.lo());
}

omw::SignedInt128 omw::operator~(const omw::SignedInt128& a)
{
    omw::Base_Int128 tmp = a;
    return omw::SignedInt128(~tmp);
}

omw::UnsignedInt128 omw::operator~(const omw::UnsignedInt128& a)
{
    omw::Base_Int128 tmp = a;
    return omw::UnsignedInt128(~tmp);
}

bool omw::operator==(const omw::SignedInt128& a, const omw::SignedInt128& b)
{
    return ((a.hi() == b.hi()) && (a.lo() == b.lo()));
}
