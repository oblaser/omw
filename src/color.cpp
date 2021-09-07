/*
author         Oliver Blaser
date           07.09.2021
copyright      MIT - Copyright (c) 2021 Oliver Blaser
*/

#include <stdexcept>

#include "omw/defs.h"
#include "omw/color.h"

omw::Color::Color()
    : rValue(0), gValue(0), bValue(0), aValue(0)
{ }

omw::Color::Color(int color)
    : rValue(0), gValue(0), bValue(0), aValue(0)
{ }

omw::Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    : rValue(r), gValue(g), bValue(b), aValue(a)
{ }

omw::Color::Color(const omw::string& css)
    : rValue(0), gValue(0), bValue(0), aValue(0)
{
    set(css);
}

void omw::Color::set(int rgb)
{
    setARGB(0xFF000000 | rgb);
}

void omw::Color::set(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    rValue = r;
    gValue = g;
    bValue = b;
    aValue = a;
}

void omw::Color::set(const omw::string& css)
{
    constexpr size_t colStrLen = 6;
    size_t pos = 0;
    if (css[0] == '#') pos = 1;
    std::string colStr(css, pos, colStrLen);

    if (!omw::isHex(colStr)) throw std::invalid_argument(OMWi_DISPSTR("Argument has to be a hex string"));

    if (colStr.length() == 3)
    {
        asdf;
    }
    else if (colStr.length() == colStrLen)
    {
        int col = omw::hexstoi(colStr);
        set(col);
    }
    else throw std::out_of_range(OMWi_DISPSTR("Hex string has to be 3 or 6 digits long"));
}

void omw::Color::setARGB(int argb)
{
    uint8_t r = (argb >> 16) & 0x0FF;
    uint8_t g = (argb >> 8) & 0x0FF;
    uint8_t b = argb & 0x0FF;
    uint8_t a = (argb >> 24) & 0x0FF;
    set(r, g, b, a);
}

//! Format: `0x00RRGGBB`
int omw::Color::toRGB() const
{
    return (toARGB() & 0x00FFFFFF);
}

//! Format: `0xAARRGGBB`
int omw::Color::toARGB() const
{
    int col = aValue;
    col <<= 8;
    col |= rValue;
    col <<= 8;
    col |= gValue;
    col <<= 8;
    col |= bValue;
    return col;
}

std::string omw::Color::cssStr() const
{
    omw::string str = "#";
    str += omw::toHexStr(rValue);
    str += omw::toHexStr(gValue);
    str += omw::toHexStr(bValue);
    return str;
}

void omw::Color::from_win32(uint32_t winCol)
{
    uint8_t r = winCol & 0x0FF;
    uint8_t g = (winCol >> 8) & 0x0FF;
    uint8_t b = (winCol >> 16) & 0x0FF;
    set(r, g, b, 0xFF);
}

uint32_t omw::Color::to_win32() const
{
    uint32_t col = bValue;
    col <<= 8;
    col |= gValue;
    col <<= 8;
    col |= rValue;
    return col;
}

void omw::Color::from_wxW_RGB(uint32_t wxWCol)
{
    from_wxW_RGBA(0xFF000000 | wxWCol);
}

void omw::Color::from_wxW_RGBA(uint32_t wxWCol)
{
    uint8_t r = wxWCol & 0x0FF;
    uint8_t g = (wxWCol >> 8) & 0x0FF;
    uint8_t b = (wxWCol >> 16) & 0x0FF;
    uint8_t a = (wxWCol >> 24) & 0x0FF;
    set(r, g, b, a);
}

uint32_t omw::Color::to_wxW_RGB() const
{
    return (to_wxW_RGBA() & 0x00FFFFFF);
}

uint32_t omw::Color::to_wxW_RGBA() const
{
    uint32_t col = aValue;
    col <<= 8;
    col |= bValue;
    col <<= 8;
    col |= gValue;
    col <<= 8;
    col |= rValue;
    return col;
}
