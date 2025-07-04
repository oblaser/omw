/*
author          Oliver Blaser
date            27.01.2022
copyright       MIT - Copyright (c) 2022 Oliver Blaser
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
#include "omw/intdef.h"


namespace {

typedef uint64_t base_type;
static constexpr unsigned int baseTypeWith = 64;
static constexpr base_type baseTypeAllBits = OMW_64BIT_ALL;
static constexpr base_type baseTypeMSB = OMW_64BIT_MSB;
static constexpr unsigned int bitWidth = 128;

static constexpr size_t nBytes128 = 16; // 16 * 8 bit = 128 bit

int64_t to_i64(uint64_t value) noexcept { return *(reinterpret_cast<int64_t*>(&value)); }
uint64_t to_ui64(int64_t value) noexcept { return *(reinterpret_cast<uint64_t*>(&value)); }
uint32_t to_ui32(int32_t value) noexcept { return *(reinterpret_cast<uint32_t*>(&value)); }

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
    quad_ui32_to_128(h, l, to_ui32(valueHH), valueLH, valueHL, valueLL);
}

} // namespace


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

    if (m_l & baseTypeMSB) m_h = baseTypeAllBits;
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
    if (data && count > 0)
    {
        if (count > nBytes128) throw std::overflow_error("omw::Base_Int128::sets");

        if (data[0] & 0x80) set(baseTypeAllBits, baseTypeAllBits);
        else setu(0);

        readBuffer(data, count);
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
    if (data && count > 0)
    {
        if (count > nBytes128) throw std::overflow_error("omw::Base_Int128::setu");
        setu(0);
        readBuffer(data, count);
    }
}

int64_t omw::Base_Int128::highs() const { return ::to_i64(m_h); }

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
    const base_type l_old = m_l;
    m_h += b.hi();
    m_l += b.lo();
    if (m_l < l_old) { ++m_h; }
    return *this;
}

omw::Base_Int128& omw::Base_Int128::operator-=(const omw::Base_Int128& b)
{
    if (m_l < b.lo()) { --m_h; }
    m_h -= b.hi();
    m_l -= b.lo();
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
    if (count)
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
        else if (count < bitWidth)
        {
            m_h = m_l;
            m_h <<= (count - baseTypeWith);
            m_l = 0;
        }
        else // count >= 128
        {
            m_h = 0;
            m_l = 0;
        }
    }

    return *this;
}

omw::Base_Int128& omw::Base_Int128::operator++()
{
    ++m_l;
    if (m_l == 0) { ++m_h; }
    return *this;
}

omw::Base_Int128& omw::Base_Int128::operator--()
{
    --m_l;
    if (m_l == baseTypeAllBits) { --m_h; }
    return *this;
}

omw::Base_Int128 omw::Base_Int128::operator++(int)
{
    const omw::Base_Int128 tmp(*this);
    ++m_l;
    if (m_l == 0) { ++m_h; }
    return tmp;
}

omw::Base_Int128 omw::Base_Int128::operator--(int)
{
    const omw::Base_Int128 tmp(*this);
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

omw::SignedInt128::SignedInt128(const omw::Base_Int128& other)
    : omw::Base_Int128(other)
{}

bool omw::SignedInt128::isNegative() const { return (m_h & OMW_64BIT_MSB); }

//! @return `-1` if the value is negative, `1` otherwise
//!
//! Caution: This is not the mathematical sign (signum) function.
//!
int omw::SignedInt128::sign() const { return (isNegative() ? -1 : 1); }

omw::SignedInt128& omw::SignedInt128::operator=(const omw::SignedInt128& b)
{
    copy(b);
    return *this;
}

omw::SignedInt128& omw::SignedInt128::operator>>=(unsigned int count)
{
    if (count)
    {
        base_type mask_h;
        base_type mask_l;

#ifdef OMWi_INT_RIGHTSHIFT_DEBUG
        oldValue_h = m_h;
        oldValue_l = m_l;
#endif

        if (m_h & baseTypeMSB)
        {
            mask_h = baseTypeAllBits;
            mask_l = baseTypeAllBits;
        }
        else
        {
            mask_h = 0;
            mask_l = 0;
        }

        if (count < baseTypeWith)
        {
            base_type carry = m_h << (baseTypeWith - count);
            m_l >>= count;
            m_l |= carry;
            m_h >>= count;

            mask_h <<= (baseTypeWith - count);
            mask_l = 0;
        }
        else if (count == baseTypeWith)
        {
            m_l = m_h;
            m_h = 0;

            mask_l = 0;
        }
        else if (count < bitWidth)
        {
            m_l = m_h;
            m_l >>= (count - baseTypeWith);
            m_h = 0;

            mask_l <<= (bitWidth - count);
        }
        else // count >= 128
        {
            m_l = 0;
            m_h = 0;
        }

#ifdef OMWi_INT_RIGHTSHIFT_DEBUG
        lastMask_h = mask_h;
        lastMask_l = mask_l;
#endif

        m_h |= mask_h;
        m_l |= mask_l;
    }

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

omw::UnsignedInt128::UnsignedInt128(const omw::Base_Int128& other)
    : omw::Base_Int128(other)
{}

omw::UnsignedInt128& omw::UnsignedInt128::operator=(const omw::UnsignedInt128& b)
{
    copy(b);
    return *this;
}

omw::UnsignedInt128& omw::UnsignedInt128::operator>>=(unsigned int count)
{
    if (count)
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
        else if (count < bitWidth)
        {
            m_l = m_h;
            m_l >>= (count - baseTypeWith);
            m_h = 0;
        }
        else // count >= 128
        {
            m_l = 0;
            m_h = 0;
        }
    }

    return *this;
}



#ifndef ___OMWi_REGION_operators

#define OMWi_IMPLEMENT_OPERATOR_UNARY_PLUS(a) return a

#define OMWi_IMPLEMENT_OPERATOR_UNARY_MINUS(a) \
    omw::Base_Int128 r(~a.hi(), ~a.lo());      \
    ++r;                                       \
    return r

// SIA = Sign Independent Arithmetic
#define OMWi_IMPLEMENT_SIA_ASSIGN_ALIAS_OPERATOR(op, a, b) \
    omw::Base_Int128 r(a);                                 \
    r op## = b;                                            \
    return r

#define OMWi_IMPLEMENT_OPERATOR_BIT_NOT(a) return omw::Base_Int128(~a.hi(), ~a.lo())

#define OMWi_DEFINE_SIA_ASSIGN_ALIAS_OPERATOR(T, op) \
    T omw::operator op(const T & a, const omw::Base_Int128 & b) { OMWi_IMPLEMENT_SIA_ASSIGN_ALIAS_OPERATOR(op, a, b); }

#define OMWi_DEFINE_ALL_TYPES_SIA_ASSIGN_ALIAS_OPERATORS(op) \
    OMWi_DEFINE_SIA_ASSIGN_ALIAS_OPERATOR(omw::SignedInt128, op) OMWi_DEFINE_SIA_ASSIGN_ALIAS_OPERATOR(omw::UnsignedInt128, op)

#define OMWi_DEFINE_DEPENDENT_COMPARSION_OPERATORS(Ta, Tb)               \
    bool omw::operator!=(const Ta& a, const Tb& b) { return !(a == b); } \
    bool omw::operator>(const Ta& a, const Tb& b) { return (b < a); }    \
    bool omw::operator<=(const Ta& a, const Tb& b) { return !(a > b); }  \
    bool omw::operator>=(const Ta& a, const Tb& b) { return !(a < b); }



//!
//! Does nothing else than returning `a`.
//!
omw::SignedInt128 omw::operator+(const omw::SignedInt128& a) { OMWi_IMPLEMENT_OPERATOR_UNARY_PLUS(a); }

//!
//! Does nothing else than returning `a`.
//!
omw::UnsignedInt128 omw::operator+(const omw::UnsignedInt128& a) { OMWi_IMPLEMENT_OPERATOR_UNARY_PLUS(a); }

//!
//! Returns the two's complement of `a`.
//!
omw::SignedInt128 omw::operator-(const omw::SignedInt128& a) { OMWi_IMPLEMENT_OPERATOR_UNARY_MINUS(a); }

//!
//! Returns the two's complement of `a`.
//!
omw::UnsignedInt128 omw::operator-(const omw::UnsignedInt128& a) { OMWi_IMPLEMENT_OPERATOR_UNARY_MINUS(a); }

// clang-format off
OMWi_DEFINE_ALL_TYPES_SIA_ASSIGN_ALIAS_OPERATORS(+)
OMWi_DEFINE_ALL_TYPES_SIA_ASSIGN_ALIAS_OPERATORS(-)

omw::SignedInt128 omw::operator~(const omw::SignedInt128& a) { OMWi_IMPLEMENT_OPERATOR_BIT_NOT(a); }
omw::UnsignedInt128 omw::operator~(const omw::UnsignedInt128& a) { OMWi_IMPLEMENT_OPERATOR_BIT_NOT(a); }

OMWi_DEFINE_ALL_TYPES_SIA_ASSIGN_ALIAS_OPERATORS(&)
OMWi_DEFINE_ALL_TYPES_SIA_ASSIGN_ALIAS_OPERATORS(|)
OMWi_DEFINE_ALL_TYPES_SIA_ASSIGN_ALIAS_OPERATORS(^)
    // clang-format on

    omw::SignedInt128 omw::operator<<(const omw::SignedInt128 & a, unsigned int count)
{
    omw::SignedInt128 r(a);
    r <<= count;
    return r;
}

omw::UnsignedInt128 omw::operator<<(const omw::UnsignedInt128& a, unsigned int count)
{
    omw::UnsignedInt128 r(a);
    r <<= count;
    return r;
}

omw::SignedInt128 omw::operator>>(const omw::SignedInt128& a, unsigned int count)
{
    omw::SignedInt128 r(a);
    r >>= count;
    return r;
}

omw::UnsignedInt128 omw::operator>>(const omw::UnsignedInt128& a, unsigned int count)
{
    omw::UnsignedInt128 r(a);
    r >>= count;
    return r;
}



bool omw::operator==(const omw::SignedInt128& a, const omw::SignedInt128& b) { return ((a.hi() == b.hi()) && (a.lo() == b.lo())); }

bool omw::operator<(const omw::SignedInt128& a, const omw::SignedInt128& b) { return ((a.his() < b.his()) || ((a.his() == b.his()) && (a.lo() < b.lo()))); }

bool omw::operator==(const omw::SignedInt128& a, const omw::UnsignedInt128& b) { return (!a.isNegative() && (a.hi() == b.hi()) && (a.lo() == b.lo())); }

bool omw::operator<(const omw::SignedInt128& a, const omw::UnsignedInt128& b)
{
    return ((a.hi() & OMW_64BIT_MSB) || (b.hi() & OMW_64BIT_MSB) || (a.hi() < b.hi()) || ((a.hi() == b.hi()) && (a.lo() < b.lo())));
}

bool omw::operator==(const omw::UnsignedInt128& a, const omw::SignedInt128& b) { return (b == a); }

bool omw::operator<(const omw::UnsignedInt128& a, const omw::SignedInt128& b)
{
    return (!(a.hi() & OMW_64BIT_MSB) && !(b.hi() & OMW_64BIT_MSB) && ((a.hi() < b.hi()) || ((a.hi() == b.hi()) && (a.lo() < b.lo()))));
}

bool omw::operator==(const omw::UnsignedInt128& a, const omw::UnsignedInt128& b) { return ((a.hi() == b.hi()) && (a.lo() == b.lo())); }

bool omw::operator<(const omw::UnsignedInt128& a, const omw::UnsignedInt128& b) { return ((a.hi() < b.hi()) || ((a.hi() == b.hi()) && (a.lo() < b.lo()))); }

// clang-format off
OMWi_DEFINE_DEPENDENT_COMPARSION_OPERATORS(omw::SignedInt128, omw::SignedInt128)
OMWi_DEFINE_DEPENDENT_COMPARSION_OPERATORS(omw::SignedInt128, omw::UnsignedInt128)
OMWi_DEFINE_DEPENDENT_COMPARSION_OPERATORS(omw::UnsignedInt128, omw::SignedInt128)
OMWi_DEFINE_DEPENDENT_COMPARSION_OPERATORS(omw::UnsignedInt128, omw::UnsignedInt128)
// clang-format on


#endif // ___OMWi_REGION_operators
