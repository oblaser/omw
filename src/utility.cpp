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


#define OMWi_IMPLEMENT_SHIFTLEFT(T) \
T r = value;                        \
shiftLeftAssign(r, n);              \
return r                            \
// end OMWi_IMPLEMENT_SHIFTLEFT

#define OMWi_IMPLEMENT_SHIFTRIGHT(T)    \
T r = value;                            \
shiftRightAssign(r, n);                 \
return r                                \
// end OMWi_IMPLEMENT_SHIFTRIGHT


namespace
{
    template <typename Ts, typename Tu, size_t nBits>
    void shiftLeftAssign(Ts& value, unsigned int n)
    {
        if (n < nBits)
        {
            const Tu tmp = static_cast<Tu>(value);
            value = static_cast<Ts>(tmp << n);
        }
        else value = 0;
    }

    template <typename Ts, typename Tu, size_t nBits>
    void shiftRightAssign_pos(Ts& value, unsigned int n)
    {
        if (n < nBits)
        {
            const Tu tmp = static_cast<Tu>(value);
            value = static_cast<Ts>(tmp >> n);
        }
        else value = 0;
    }

    template <typename Ts, typename Tu, size_t nBits>
    void shiftRightAssign_neg(Ts& value, unsigned int n)
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

    template <typename Ts, typename Tu, size_t nBits>
    void shiftRightAssign(Ts& value, unsigned int n)
    {
        Tu msb = 0x01;
        msb = msb << (nBits - 1);
        if (static_cast<Tu>(value) & msb) shiftRightAssign_neg<Ts, Tu, nBits>(value, n);
        else shiftRightAssign_pos<Ts, Tu, nBits>(value, n);
    }

    template <typename Tout, typename Tin>
    std::vector<Tout> convertByteVector(const std::vector<Tin>& v)
    {
        std::vector<Tout> r(0);
        for (std::vector<Tin>::size_type i = 0; i < v.size(); ++i) r.push_back(static_cast<Tout>(v[i]));
        return r;
    }
}



void omw::shiftLeftAssign(int8_t& value, unsigned int n)
{
    ::shiftLeftAssign<int8_t, uint8_t, 8>(value, n);
}

void omw::shiftLeftAssign(int16_t& value, unsigned int n)
{
    ::shiftLeftAssign<int16_t, uint16_t, 16>(value, n);
}

void omw::shiftLeftAssign(int32_t& value, unsigned int n)
{
    ::shiftLeftAssign<int32_t, uint32_t, 32>(value, n);
}

void omw::shiftLeftAssign(int64_t& value, unsigned int n)
{
    ::shiftLeftAssign<int64_t, uint64_t, 64>(value, n);
}

void omw::shiftLeftAssign(uint8_t& value, unsigned int n)
{
    if (n < 8) value = value << n;
    else value = 0;
}

void omw::shiftLeftAssign(uint16_t& value, unsigned int n)
{
    if (n < 16) value = value << n;
    else value = 0;
}

void omw::shiftLeftAssign(uint32_t& value, unsigned int n)
{
    if (n < 32) value = value << n;
    else value = 0;
}

void omw::shiftLeftAssign(uint64_t& value, unsigned int n)
{
    if (n < 64) value = value << n;
    else value = 0;
}

void omw::shiftRightAssign(int8_t& value, unsigned int n)
{
    ::shiftRightAssign<int8_t, uint8_t, 8>(value, n);
}

void omw::shiftRightAssign(int16_t& value, unsigned int n)
{
    ::shiftRightAssign<int16_t, uint16_t, 16>(value, n);
}

void omw::shiftRightAssign(int32_t& value, unsigned int n)
{
    ::shiftRightAssign<int32_t, uint32_t, 32>(value, n);
}

void omw::shiftRightAssign(int64_t& value, unsigned int n)
{
    ::shiftRightAssign<int64_t, uint64_t, 64>(value, n);
}

void omw::shiftRightAssign(uint8_t& value, unsigned int n)
{
    if (n < 8) value = value >> n;
    else value = 0;
}

void omw::shiftRightAssign(uint16_t& value, unsigned int n)
{
    if (n < 16) value = value >> n;
    else value = 0;
}

void omw::shiftRightAssign(uint32_t& value, unsigned int n)
{
    if (n < 32) value = value >> n;
    else value = 0;
}

void omw::shiftRightAssign(uint64_t& value, unsigned int n)
{
    if (n < 64) value = value >> n;
    else value = 0;
}

int8_t omw::shiftLeft(int8_t value, unsigned int n) { OMWi_IMPLEMENT_SHIFTLEFT(int8_t); }
int16_t omw::shiftLeft(int16_t value, unsigned int n) { OMWi_IMPLEMENT_SHIFTLEFT(int16_t); }
int32_t omw::shiftLeft(int32_t value, unsigned int n) { OMWi_IMPLEMENT_SHIFTLEFT(int32_t); }
int64_t omw::shiftLeft(int64_t value, unsigned int n) { OMWi_IMPLEMENT_SHIFTLEFT(int64_t); }
uint8_t omw::shiftLeft(uint8_t value, unsigned int n) { OMWi_IMPLEMENT_SHIFTLEFT(uint8_t); }
uint16_t omw::shiftLeft(uint16_t value, unsigned int n) { OMWi_IMPLEMENT_SHIFTLEFT(uint16_t); }
uint32_t omw::shiftLeft(uint32_t value, unsigned int n) { OMWi_IMPLEMENT_SHIFTLEFT(uint32_t); }
uint64_t omw::shiftLeft(uint64_t value, unsigned int n) { OMWi_IMPLEMENT_SHIFTLEFT(uint64_t); }
int8_t omw::shiftRight(int8_t value, unsigned int n) { OMWi_IMPLEMENT_SHIFTRIGHT(int8_t); }
int16_t omw::shiftRight(int16_t value, unsigned int n) { OMWi_IMPLEMENT_SHIFTRIGHT(int16_t); }
int32_t omw::shiftRight(int32_t value, unsigned int n) { OMWi_IMPLEMENT_SHIFTRIGHT(int32_t); }
int64_t omw::shiftRight(int64_t value, unsigned int n) { OMWi_IMPLEMENT_SHIFTRIGHT(int64_t); }
uint8_t omw::shiftRight(uint8_t value, unsigned int n) { OMWi_IMPLEMENT_SHIFTRIGHT(uint8_t); }
uint16_t omw::shiftRight(uint16_t value, unsigned int n) { OMWi_IMPLEMENT_SHIFTRIGHT(uint16_t); }
uint32_t omw::shiftRight(uint32_t value, unsigned int n) { OMWi_IMPLEMENT_SHIFTRIGHT(uint32_t); }
uint64_t omw::shiftRight(uint64_t value, unsigned int n) { OMWi_IMPLEMENT_SHIFTRIGHT(uint64_t); }



// /* or /*!
/*
* \fn void omw::toggle(bool& value)
* \param value The value to toggle
*
* Toggles a boolean value.
*/



std::vector<char> omw::convertByteVector(const std::vector<uint8_t>& v)
{
    return ::convertByteVector<char, uint8_t>(v);
}

std::vector<uint8_t> omw::convertByteVector(const std::vector<char>& v)
{
    return ::convertByteVector<uint8_t, char>(v);
}
