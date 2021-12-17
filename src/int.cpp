/*
author          Oliver Blaser
date            15.12.2021
copyright       MIT - Copyright (c) 2021 Oliver Blaser
*/

/*
* Operator Implementation Philosophy
*
* Operators declared inside a class do not use any other overloaded
* operators. Operators declared outside a class do not use each
* other (except comparsion operators), but can use operators declared
* inside a class.
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
}



omw::Base_Int128::Base_Int128()
    : m_h(0), m_l(0)
{}

omw::Base_Int128::Base_Int128(const omw::Base_Int128& other)
    : m_h(0), m_l(0)
{
    copy(other);
}

//! 
//! Uses `omw::Base_Int128::sets(int64_t)` to initialize.
//! 
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

void omw::Base_Int128::set(uint64_t valueH, uint64_t valueL)
{
    m_h = valueH;
    m_l = valueL;
}

void omw::Base_Int128::set(uint32_t valueHH, uint32_t valueLH, uint32_t valueHL, uint32_t valueLL)
{
    quad_ui32_to_128(m_h, m_l, valueHH, valueLH, valueHL, valueLL);
}

//! 
//! Extends the sign bit.
//! 
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
//! Interprets the value from a byte buffer as signed: The sign bit (MSB of `data[0]`) is extended.
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

//! 
//! Does not extend the sign bit.
//! 
void omw::Base_Int128::setu(uint64_t value)
{
    m_h = 0;
    m_l = value;
}

//! @param data Pointer to a big endian byte buffer
//! @param count Number of bytes to read
//! 
//! Interprets the value from a byte buffer as unsigned.
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

int64_t omw::Base_Int128::highs() const
{
    return ::to_i64(m_h);
}

void omw::Base_Int128::copy(const omw::Base_Int128& other)
{
    m_h = other.hi();
    m_l = other.lo();
}

void omw::Base_Int128::readBuffer(const uint8_t* data, size_t count)
{
    for (size_t i = 0; i < count; ++i)
    {
        *this <<= 8;
        *this |= omw::Base_Int128(0, data[i]);
    }
}

omw::Base_Int128& omw::Base_Int128::operator+=(const omw::Base_Int128& b)
{
    m_h += b.hi();
    m_l += b.lo();
    if (m_l == 0) { ++m_h; }
    return *this;
}

omw::Base_Int128& omw::Base_Int128::operator-=(const omw::Base_Int128& b)
{
    m_h -= b.hi();
    m_l -= b.lo();
    if (m_l == baseTypeAllBits) { --m_h; }
    return *this;
}

omw::Base_Int128& omw::Base_Int128::operator&=(const omw::Base_Int128& b)
{
    m_h &= b.hi();
    m_l &= b.lo();
    return *this;
}

omw::Base_Int128& omw::Base_Int128::operator|=(const omw::Base_Int128& b)
{
    m_h |= b.hi();
    m_l |= b.lo();
    return *this;
}

omw::Base_Int128& omw::Base_Int128::operator^=(const omw::Base_Int128& b)
{
    m_h ^= b.hi();
    m_l ^= b.lo();
    return *this;
}

omw::Base_Int128& omw::Base_Int128::operator<<=(unsigned int count)
{
    if (count < baseTypeWith)
    {
        base_type carry = m_l >> (baseTypeWith - count);
        m_h <<= count;
        m_h |= carry;
        m_l <<= count;
    }
    else if (count == baseTypeWith)
    {
        m_h = m_l;
        m_l = 0;
    }
    else // count > baseTypeWith
    {
        m_h = m_l;
        m_h <<= (count - baseTypeWith);
        m_l = 0;
    }

    return *this;
}

omw::Base_Int128& omw::Base_Int128::operator>>=(unsigned int count)
{
    if (count < baseTypeWith)
    {
        base_type carry = m_h << (baseTypeWith - count);
        m_l >>= count;
        m_l |= carry;
        m_h >>= count;
    }
    else if (count == baseTypeWith)
    {
        m_l = m_h;
        m_h = 0;
    }
    else // count > baseTypeWith
    {
        m_l = m_h;
        m_l >>= (count - baseTypeWith);
        m_h = 0;
    }

    return *this;
}

omw::Base_Int128& omw::Base_Int128::operator++()
{
    ++m_h;
    ++m_l;
    if (m_l == 0) { ++m_h; }
    return *this;
}

omw::Base_Int128& omw::Base_Int128::operator--()
{
    --m_h;
    --m_l;
    if (m_l == baseTypeAllBits) { --m_h; }
    return *this;
}

omw::Base_Int128 omw::Base_Int128::operator++(int)
{
    const omw::Base_Int128 tmp(*this);
    ++m_h;
    ++m_l;
    if (m_l == 0) { ++m_h; }
    return tmp;
}

omw::Base_Int128 omw::Base_Int128::operator--(int)
{
    const omw::Base_Int128 tmp(*this);
    --m_h;
    --m_l;
    if (m_l == baseTypeAllBits) { --m_h; }
    return tmp;
}



omw::SignedInt128::SignedInt128()
    : omw::Base_Int128()
{}

omw::SignedInt128::SignedInt128(const omw::SignedInt128& other)
    : omw::Base_Int128(other)
{}

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

bool omw::SignedInt128::isNegative() const
{
    return (m_h & OMW_64BIT_MSB);
}

//! @return `-1` if the value is negative, `1` otherwise
//! 
//! Caution: This is not the mathematical sign (signum) function.
//! 
int omw::SignedInt128::sign() const
{
    return (isNegative() ? -1 : 1);
}

omw::SignedInt128& omw::SignedInt128::operator=(const omw::SignedInt128& b)
{
    copy(b);
    return *this;
}



omw::UnsignedInt128::UnsignedInt128()
    : omw::Base_Int128()
{}

omw::UnsignedInt128::UnsignedInt128(const omw::UnsignedInt128& other)
    : omw::Base_Int128(other)
{}

//! 
//! Uses `omw::Base_Int128::sets(int64_t)` to initialize.
//! 
omw::UnsignedInt128::UnsignedInt128(int64_t value)
    : omw::Base_Int128()
{
    sets(value);
}

omw::UnsignedInt128::UnsignedInt128(uint64_t valueH, uint64_t valueL)
    : omw::Base_Int128(valueH, valueL)
{}

omw::UnsignedInt128::UnsignedInt128(uint32_t valueHH, uint32_t valueLH, uint32_t valueHL, uint32_t valueLL)
    : omw::Base_Int128(valueHH, valueLH, valueHL, valueLL)
{}

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

omw::UnsignedInt128& omw::UnsignedInt128::operator=(const omw::UnsignedInt128& b)
{
    copy(b);
    return *this;
}



#pragma region operators

#define OMWi_IMPLEMENT_OPERATOR_UNARY_PLUS(a)   \
return a                                        \
// end OMWi_IMPLEMENT_OPERATOR_UNARY_PLUS

#define OMWi_IMPLEMENT_OPERATOR_UNARY_MINUS(a)  \
omw::Base_Int128 r(~a.hi(), ~a.lo());           \
++r;                                            \
return r                                        \
// end OMWi_IMPLEMENT_OPERATOR_UNARY_MINUS

// SIA = Sign Independent Arithmetic
#define OMWi_IMPLEMENT_SIA_ASSIGN_ALIAS_OPERATOR(op, a, b) \
omw::Base_Int128 r(a);                          \
r op##= b;                                      \
return r                                        \
// end OMWi_IMPLEMENT_SIA_ASSIGN_ALIAS_OPERATOR

#define OMWi_IMPLEMENT_OPERATOR_BIT_NOT(a)  \
return omw::Base_Int128(~a.hi(), ~a.lo())   \
// end OMWi_IMPLEMENT_OPERATOR_BIT_NOT

#define OMWi_DEFINE_SIA_ASSIGN_ALIAS_OPERATOR(T, op) \
T omw::operator op (const T& a, const T& b) { OMWi_IMPLEMENT_SIA_ASSIGN_ALIAS_OPERATOR(op, a, b); } \
// end OMWi_DEFINE_SIA_ASSIGN_ALIAS_OPERATOR

#define OMWi_DEFINE_SIA_SHIFT_ASSIGN_ALIAS_OPERATOR(T, op)  \
T omw::operator op (const T& a, unsigned int count) { OMWi_IMPLEMENT_SIA_ASSIGN_ALIAS_OPERATOR(op, a, count); } \
// end OMWi_DEFINE_SIA_SHIFT_ASSIGN_ALIAS_OPERATOR

#define OMWi_DEFINE_ALL_TYPES_SIA_ASSIGN_ALIAS_OPERATORS(op)    \
OMWi_DEFINE_SIA_ASSIGN_ALIAS_OPERATOR(omw::Base_Int128, op)     \
OMWi_DEFINE_SIA_ASSIGN_ALIAS_OPERATOR(omw::SignedInt128, op)    \
OMWi_DEFINE_SIA_ASSIGN_ALIAS_OPERATOR(omw::UnsignedInt128, op)  \
// end OMWi_DEFINE_ALL_TYPES_SIA_ASSIGN_ALIAS_OPERATORS

#define OMWi_DEFINE_ALL_TYPES_SIA_SHIFT_ASSIGN_ALIAS_OPERATORS(op)      \
OMWi_DEFINE_SIA_SHIFT_ASSIGN_ALIAS_OPERATOR(omw::Base_Int128, op)       \
OMWi_DEFINE_SIA_SHIFT_ASSIGN_ALIAS_OPERATOR(omw::SignedInt128, op)      \
OMWi_DEFINE_SIA_SHIFT_ASSIGN_ALIAS_OPERATOR(omw::UnsignedInt128, op)    \
// end OMWi_DEFINE_ALL_TYPES_SIA_SHIFT_ASSIGN_ALIAS_OPERATORS

#define OMWi_DEFINE_DEPENDENT_COMPARSION_OPERATORS(Ta, Tb)              \
bool omw::operator!=(const Ta& a, const Tb& b) { return !(a == b); }    \
bool omw::operator>(const Ta& a, const Tb& b) { return (b < a); }       \
bool omw::operator<=(const Ta& a, const Tb& b) { return !(a > b); }     \
bool omw::operator>=(const Ta& a, const Tb& b) { return !(a < b); }     \
// end OMWi_DEFINE_NOT_EQUAL_OPERATOR



omw::SignedInt128 omw::operator+(const omw::SignedInt128& a) { OMWi_IMPLEMENT_OPERATOR_UNARY_PLUS(a); }
omw::UnsignedInt128 omw::operator+(const omw::UnsignedInt128& a) { OMWi_IMPLEMENT_OPERATOR_UNARY_PLUS(a); }
omw::SignedInt128 omw::operator-(const omw::SignedInt128& a) { OMWi_IMPLEMENT_OPERATOR_UNARY_MINUS(a); }
omw::UnsignedInt128 omw::operator-(const omw::UnsignedInt128& a) { OMWi_IMPLEMENT_OPERATOR_UNARY_MINUS(a); }

OMWi_DEFINE_ALL_TYPES_SIA_ASSIGN_ALIAS_OPERATORS(+)
OMWi_DEFINE_ALL_TYPES_SIA_ASSIGN_ALIAS_OPERATORS(-)

omw::SignedInt128 omw::operator~(const omw::SignedInt128& a) { OMWi_IMPLEMENT_OPERATOR_BIT_NOT(a); }
omw::UnsignedInt128 omw::operator~(const omw::UnsignedInt128& a) { OMWi_IMPLEMENT_OPERATOR_BIT_NOT(a); }

OMWi_DEFINE_ALL_TYPES_SIA_ASSIGN_ALIAS_OPERATORS(&)
OMWi_DEFINE_ALL_TYPES_SIA_ASSIGN_ALIAS_OPERATORS(|)
OMWi_DEFINE_ALL_TYPES_SIA_ASSIGN_ALIAS_OPERATORS(^)
OMWi_DEFINE_ALL_TYPES_SIA_SHIFT_ASSIGN_ALIAS_OPERATORS(<<)
OMWi_DEFINE_ALL_TYPES_SIA_SHIFT_ASSIGN_ALIAS_OPERATORS(>>)





bool omw::operator==(const omw::SignedInt128& a, const omw::SignedInt128& b)
{
    return ((a.hi() == b.hi()) && (a.lo() == b.lo()));
}

bool omw::operator<(const omw::SignedInt128& a, const omw::SignedInt128& b)
{
    return ((a.his() < b.his()) ||
        ((a.his() == b.his()) && (a.lo() < b.lo())));
}

bool omw::operator==(const omw::UnsignedInt128& a, const omw::UnsignedInt128& b)
{
    return ((a.hi() == b.hi()) && (a.lo() == b.lo()));
}

bool omw::operator<(const omw::UnsignedInt128& a, const omw::UnsignedInt128& b)
{
    return ((a.hi() < b.hi()) ||
        ((a.hi() == b.hi()) && (a.lo() < b.lo())));
}

//! 
//! Sign aware comparsion operator. Negative signed integers compare always
//! less than unsigned integers. Unsigned integers grater than the maximal
//! signed value compare always greater than signed integers. Signed and
//! unsigned integers only compare equal if their represented value is the
//! same.
//! 
bool omw::operator==(const omw::SignedInt128& a, const omw::UnsignedInt128& b)
{
    return (!a.isNegative() && (a.hi() == b.hi()) && (a.lo() == b.lo()));
}

bool omw::operator<(const omw::SignedInt128& a, const omw::UnsignedInt128& b)
{
    return ((a.hi() & OMW_64BIT_MSB) ||
        (b.hi() & OMW_64BIT_MSB) ||
        (a.hi() < b.hi()) ||
        ((a.hi() == b.hi()) && (a.lo() < b.lo()))
        );
}

OMWi_DEFINE_DEPENDENT_COMPARSION_OPERATORS(omw::SignedInt128, omw::SignedInt128)
OMWi_DEFINE_DEPENDENT_COMPARSION_OPERATORS(omw::SignedInt128, omw::UnsignedInt128)
bool omw::operator==(const omw::UnsignedInt128& a, const omw::SignedInt128& b) { return (b == a); }
bool omw::operator<(const omw::UnsignedInt128& a, const omw::SignedInt128& b) { return (b > a); }
OMWi_DEFINE_DEPENDENT_COMPARSION_OPERATORS(omw::UnsignedInt128, omw::SignedInt128)
OMWi_DEFINE_DEPENDENT_COMPARSION_OPERATORS(omw::UnsignedInt128, omw::UnsignedInt128)

#pragma endregion operators
