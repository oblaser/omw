/*
author          Oliver Blaser
date            10.01.2022
copyright       MIT - Copyright (c) 2022 Oliver Blaser
*/


#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "omw/int.h"
#include "omw/utility.h"

namespace
{
    template <class Ts, class Tu, size_t nBits>
    void shiftLeftAssign(Ts& value, size_t n)
    {
        if (n < nBits)
        {
            const Tu tmp = static_cast<Tu>(value);
            value = static_cast<Ts>(tmp << n);
        }
        else value = 0;
    }

    template <class Ts, class Tu, size_t nBits>
    void shiftRightAssign_pos(Ts& value, size_t n)
    {
        if (n < nBits)
        {
            const Tu tmp = static_cast<Tu>(value);
            value = static_cast<Ts>(tmp >> n);
        }
        else value = 0;
    }

    template <class Ts, class Tu, size_t nBits>
    void shiftRightAssign_neg(Ts& value, size_t n)
    {
        if (n < nBits)
        {
            constexpr Tu ff = static_cast<Tu>(-1);
            Tu tmp = static_cast<Tu>(value);
            tmp = tmp >> n;
            tmp |= (ff << (nBits - n));
            value = static_cast<Ts>(tmp);
        }
        else value = -1;
    }

    template <class Ts, class Tu, size_t nBits>
    void shiftRightAssign(Ts& value, size_t n)
    {
        Tu msb = 1;
        msb = msb << (nBits - 1);
        if (static_cast<Tu>(value) & msb) shiftRightAssign_neg<Ts, Tu, nBits>(value, n);
        else shiftRightAssign_pos<Ts, Tu, nBits>(value, n);
    }
}



//! 
//! Until C++20 the left shift of negative signed values is undefined. These functions implement a C++20 compliant left shift.
//! In addition, if `n` is greater than or equal to the number of bits of the values type, `value` is set to `0`.
//! 
//! See also <a href="https://en.cppreference.com/w/cpp/language/operator_arithmetic#Bitwise_shift_operators" target="_blank">Bitwise shift operators</a> at cppreference.com.
//! 
void omw::shiftLeftAssign(int8_t& value, size_t n)
{
    ::shiftLeftAssign<int8_t, uint8_t, 8>(value, n);
}

//! 
//! See `omw::shiftLeftAssign(int8_t&, size_t)`.
//! 
void omw::shiftLeftAssign(int16_t& value, size_t n)
{
    ::shiftLeftAssign<int16_t, uint16_t, 16>(value, n);
}

//! 
//! See `omw::shiftLeftAssign(int8_t&, size_t)`.
//! 
void omw::shiftLeftAssign(int32_t& value, size_t n)
{
    ::shiftLeftAssign<int32_t, uint32_t, 32 >(value, n);
}

//! 
//! See `omw::shiftLeftAssign(int8_t&, size_t)`.
//! 
void omw::shiftLeftAssign(int64_t& value, size_t n)
{
    ::shiftLeftAssign<int64_t, uint64_t, 64>(value, n);
}

//! 
//! The unsigned overloads are needed if these shift functions are used in templates.
//! 
//! If `n` is greater than or equal to the number of bits of the values type, `value` is set to `0`.
//! 
void omw::shiftLeftAssign(uint8_t& value, size_t n)
{
    if (n < 8) value = value << n;
    else value = 0;
}

//! 
//! See `omw::shiftLeftAssign(uint8_t&, size_t)`.
//! 
void omw::shiftLeftAssign(uint16_t& value, size_t n)
{
    if (n < 16) value = value << n;
    else value = 0;
}

//! 
//! See `omw::shiftLeftAssign(uint8_t&, size_t)`.
//! 
void omw::shiftLeftAssign(uint32_t& value, size_t n)
{
    if (n < 32) value = value << n;
    else value = 0;
}

//! 
//! See `omw::shiftLeftAssign(uint8_t&, size_t)`.
//! 
void omw::shiftLeftAssign(uint64_t& value, size_t n)
{
    if (n < 64) value = value << n;
    else value = 0;
}

//! 
//! Until C++20 the right shift of negative signed values is implementation-undefined. These functions implement a C++20 compliant right shift.
//! In addition, if `n` is greater than or equal to the number of bits of the values type, `value` is set to `0` (or to `-1` if the value was negative before the operation).
//! 
//! See also <a href="https://en.cppreference.com/w/cpp/language/operator_arithmetic#Bitwise_shift_operators" target="_blank">Bitwise shift operators</a> at cppreference.com.
//! 
void omw::shiftRightAssign(int8_t& value, size_t n)
{
    ::shiftRightAssign<int8_t, uint8_t, 8>(value, n);
}

//! 
//! See `omw::shiftRightAssign(int8_t&, size_t)`.
//! 
void omw::shiftRightAssign(int16_t& value, size_t n)
{
    ::shiftRightAssign<int16_t, uint16_t, 16>(value, n);
}

//! 
//! See `omw::shiftRightAssign(int8_t&, size_t)`.
//! 
void omw::shiftRightAssign(int32_t& value, size_t n)
{
    ::shiftRightAssign<int32_t, uint32_t, 32 >(value, n);
}

//! 
//! See `omw::shiftRightAssign(int8_t&, size_t)`.
//! 
void omw::shiftRightAssign(int64_t& value, size_t n)
{
    ::shiftRightAssign<int64_t, uint64_t, 64 >(value, n);
}

//! 
//! See `omw::shiftLeftAssign(uint8_t&, size_t)`.
//! 
void omw::shiftRightAssign(uint8_t& value, size_t n)
{
    if (n < 8) value = value >> n;
    else value = 0;
}

//! 
//! See `omw::shiftLeftAssign(uint8_t&, size_t)`.
//! 
void omw::shiftRightAssign(uint16_t& value, size_t n)
{
    if (n < 16) value = value >> n;
    else value = 0;
}

//! 
//! See `omw::shiftLeftAssign(uint8_t&, size_t)`.
//! 
void omw::shiftRightAssign(uint32_t& value, size_t n)
{
    if (n < 32) value = value >> n;
    else value = 0;
}

//! 
//! See `omw::shiftLeftAssign(uint8_t&, size_t)`.
//! 
void omw::shiftRightAssign(uint64_t& value, size_t n)
{
    if (n < 64) value = value >> n;
    else value = 0;
}



// /* or /*!
/*
* \fn void omw::toggle(bool& value)
* \param value The value to toggle
*
* Toggles a boolean value.
*/
