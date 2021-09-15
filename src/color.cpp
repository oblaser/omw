/*
author         Oliver Blaser
date           15.09.2021
copyright      MIT - Copyright (c) 2021 Oliver Blaser
*/

#include <cmath>
#include <stdexcept>

#include "omw/defs.h"
#include "omw/color.h"

omw::Color::Color()
    : validity(false), rValue(0), gValue(0), bValue(0), aValue(0xFF)
{}

//! Format: `0x00RRGGBB`
omw::Color::Color(int32_t rgb)
    : validity(false), rValue(0), gValue(0), bValue(0), aValue(0xFF)
{
    set(rgb);
}

omw::Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    : validity(false), rValue(r), gValue(g), bValue(b), aValue(a)
{
    validity = true;
}

//! Format: `"RRGGBB"` or `"#RRGGBB"`
omw::Color::Color(const std::string& css)
    : validity(false), rValue(0), gValue(0), bValue(0), aValue(0xFF)
{
    set(css);
}

//! Format: `"RRGGBB"` or `"#RRGGBB"`
omw::Color::Color(const char* css)
    : validity(false), rValue(0), gValue(0), bValue(0), aValue(0xFF)
{
    set(css);
}

//! A color object is considered valid when any value was set. Either with one of the `set()` or `set..()` functions or with the constructor.
bool omw::Color::isValid() const
{
    return validity;
}

//! Invalidates the object. RGBA values keep their content.
void omw::Color::invalidate()
{
    validity = false;
}

//! Sets R, G and B to 0, alpha to 0xFF and invalidates the object.
void omw::Color::clear()
{
    set(0, 0, 0, 0xFF);
    invalidate();
}

//! Sets the alpha value to 0xFF. Does not change the validity.
void omw::Color::opaque()
{
    aValue = 0xFF;
}

//! Sets the alpha value to 0. Does not change the validity.
void omw::Color::transparent()
{
    aValue = 0;
}

//! Format: `0x00RRGGBB`
void omw::Color::set(int32_t rgb)
{
    setARGB(0xFF000000 | rgb);
}

void omw::Color::set(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    rValue = r;
    gValue = g;
    bValue = b;
    aValue = a;

    validity = true;
}

//! Format: `"RRGGBB"` or `"#RRGGBB"`
void omw::Color::set(const std::string& css)
{
    constexpr size_t colStrLen = 6;
    size_t pos = 0;
    if (css.length() > 0)
    {
        if (css[0] == '#') pos = 1;
    }

    omw::string colStr(css, pos);
    int32_t col;

    if (colStr.length() == 3)
    {
        const char tmpColStr[] = { colStr[0], colStr[0], colStr[1], colStr[1], colStr[2], colStr[2], 0 };
        col = omw::hexstoi(tmpColStr);
    }
    else if (colStr.length() == colStrLen)
    {
        col = omw::hexstoi(colStr);
    }
    else throw std::out_of_range(OMWi_DISPSTR("Hex string has to be 3 or 6 digits long"));

    set(col);
}

//! Format: `"RRGGBB"` or `"#RRGGBB"`
void omw::Color::set(const char* css)
{
    const std::string tmpStr(css);
    set(tmpStr);
}

//! Format: `0xAARRGGBB`
void omw::Color::setARGB(int32_t argb)
{
    uint8_t r = (argb >> 16) & 0x0FF;
    uint8_t g = (argb >> 8) & 0x0FF;
    uint8_t b = argb & 0x0FF;
    uint8_t a = (argb >> 24) & 0x0FF;
    set(r, g, b, a);
}

void omw::Color::setR(uint8_t value)
{
    set(value, gValue, bValue, aValue);
}

void omw::Color::setG(uint8_t value)
{
    set(rValue, value, bValue, aValue);
}

void omw::Color::setB(uint8_t value)
{
    set(rValue, gValue, value, aValue);
}

void omw::Color::setA(uint8_t value)
{
    set(rValue, gValue, bValue, value);
}

uint8_t omw::Color::r() const
{
    return rValue;
}

uint8_t omw::Color::g() const
{
    return gValue;
}

uint8_t omw::Color::b() const
{
    return bValue;
}

uint8_t omw::Color::a() const
{
    return aValue;
}

//! Format: `0x00RRGGBB`
int32_t omw::Color::toRGB() const
{
    return (toARGB() & 0x00FFFFFF);
}

//! Format: `0xAARRGGBB`
int32_t omw::Color::toARGB() const
{
    int32_t col = a();
    col <<= 8;
    col |= r();
    col <<= 8;
    col |= g();
    col <<= 8;
    col |= b();
    return col;
}

//! Format: `"RRGGBB"`
omw::string omw::Color::toString() const
{
    omw::string str = "";
    str += omw::toHexStr(r());
    str += omw::toHexStr(g());
    str += omw::toHexStr(b());
    return str;
}

//! Format: `"#RRGGBB"`
omw::string omw::Color::toCssStr() const
{
    omw::string str = "#";
    str += omw::toHexStr(r());
    str += omw::toHexStr(g());
    str += omw::toHexStr(b());
    return str;
}

omw::Color& omw::Color::operator+=(const omw::Color& addend)
{
    const bool thisWasInvalid = !this->isValid();

    if (addend.a() == 0xFF)
    {
        uint8_t r = addend.r();
        uint8_t g = addend.g();
        uint8_t b = addend.b();

        this->set(this->r() + r, this->g() + g, this->b() + b, this->a());
    }
    else if (addend.a() > 0)
    {
        double tmpr = addend.r();
        double tmpg = addend.g();
        double tmpb = addend.b();

        const double k = (double)addend.a() / 255;
        tmpr *= k;
        tmpg *= k;
        tmpb *= k;

        uint8_t r = std::lround(tmpr);
        uint8_t g = std::lround(tmpg);
        uint8_t b = std::lround(tmpb);

        this->set(this->r() + r, this->g() + g, this->b() + b, this->a());
    }
    // else /*nop*/;  addend has no impact

    if (thisWasInvalid || !addend.isValid()) this->invalidate();
    return *this;
}

omw::Color& omw::Color::operator-=(const omw::Color& subtrahend)
{
    const bool thisWasInvalid = !this->isValid();

    if (subtrahend.a() == 0xFF)
    {
        uint8_t r = subtrahend.r();
        uint8_t g = subtrahend.g();
        uint8_t b = subtrahend.b();

        this->set(this->r() - r, this->g() - g, this->b() - b, this->a());
    }
    else if (subtrahend.a() > 0)
    {
        double tmpr = subtrahend.r();
        double tmpg = subtrahend.g();
        double tmpb = subtrahend.b();

        const double k = (double)subtrahend.a() / 255;
        tmpr *= k;
        tmpg *= k;
        tmpb *= k;

        uint8_t r = std::lround(tmpr);
        uint8_t g = std::lround(tmpg);
        uint8_t b = std::lround(tmpb);

        this->set(this->r() - r, this->g() - g, this->b() - b, this->a());
    }
    // else /*nop*/;  subtrahend has no impact

    if (thisWasInvalid || !subtrahend.isValid()) this->invalidate();
    return *this;
}

omw::Color omw::operator+(const omw::Color& lAddend, const omw::Color& rAddend)
{
    omw::Color r(lAddend);
    r += rAddend;
    return r;
}

omw::Color omw::operator-(const omw::Color& minuend, const omw::Color& subtrahend)
{
    omw::Color r(minuend);
    r -= subtrahend;
    return r;
}

bool omw::operator==(const omw::Color& left, const omw::Color& right)
{
    return ((left.isValid() == right.isValid()) && (left.toARGB() == right.toARGB()));
}

bool omw::operator!=(const omw::Color& left, const omw::Color& right)
{
    return !(left == right);
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
    uint32_t col = b();
    col <<= 8;
    col |= g();
    col <<= 8;
    col |= r();
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
    uint32_t col = a();
    col <<= 8;
    col |= b();
    col <<= 8;
    col |= g();
    col <<= 8;
    col |= r();
    return col;
}
