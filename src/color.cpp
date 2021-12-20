/*
author          Oliver Blaser
date            20.12.2021
copyright       MIT - Copyright (c) 2021 Oliver Blaser
*/

#include <cmath>
#include <stdexcept>

#include "omw/defs.h"
#include "omw/color.h"



/*!
* \class omw::Color
*
* TODO: insert description.
*
* A color object is considered valid when any value was set. Either with one of the `set()` or `set..()` functions or with one of the constructors. However the default constructor creates an invalid object.
*/

omw::Color::Color()
    : validity(false), rValue(0), gValue(0), bValue(0), aValue(0xFF)
{}

//! @param rgb Integer representation of the color
//! 
//! Format: `0x00RRGGBB`
//! 
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

//! @param css Hex string
//! 
//! Format: `"#RRGGBB"` or `"#RGB"`, with or without a leading `#`.
//! 
//! \b Exceptions
//! - `std::invalid_argument` if the string does not match the format
//! - `omw::hexstoi()` is called and may throw `std::out_of_range` or `std::invalid_argument`
//! 
omw::Color::Color(const std::string& css)
    : validity(false), rValue(0), gValue(0), bValue(0), aValue(0xFF)
{
    set(css);
}

//! @param css Hex string
//! 
//! Format: `"#RRGGBB"` or `"#RGB"`, with or without a leading `#`.
//! 
//! \b Exceptions
//! - `std::invalid_argument` if the string does not match the format
//! - `omw::hexstoi()` is called and may throw `std::out_of_range` or `std::invalid_argument`
//! 
omw::Color::Color(const char* css)
    : validity(false), rValue(0), gValue(0), bValue(0), aValue(0xFF)
{
    set(css);
}

bool omw::Color::isValid() const
{
    return validity;
}

//! @param state Validity
//! 
//! Marks the object as valid or invalid. The color attributes keep their values.
//! 
void omw::Color::validate(bool state)
{
    validity = state;
}

//! @brief Invalidates the object.
//! 
//! The color attributes keep their values.
//! 
void omw::Color::invalidate()
{
    validate(false);
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

//! @param rgb Integer representation of the color
//! 
//! Format: `0x00RRGGBB`
//! 
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

void omw::Color::set(const omw::Color& color)
{
    setARGB(color.toARGB());
}

//! @param css Hex string
//! 
//! Format: `"#RRGGBB"` or `"#RGB"`, with or without a leading `#`.
//! 
//! \b Exceptions
//! - `std::invalid_argument` if the string does not match the format
//! - `omw::hexstoi()` is called and may throw `std::out_of_range` or `std::invalid_argument`
//! 
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
    else throw std::invalid_argument(OMWi_DISPSTR("omw::Color::set: Hex string has to be 3 or 6 digits long"));

    set(col);
}

//! @param css Hex string
//! 
//! Format: `"#RRGGBB"` or `"#RGB"`, with or without a leading `#`.
//! 
//! \b Exceptions
//! - `std::invalid_argument` if the string does not match the format
//! - `omw::hexstoi()` is called and may throw `std::out_of_range` or `std::invalid_argument`
//! 
void omw::Color::set(const char* css)
{
    const std::string tmpStr(css);
    set(tmpStr);
}

//! @param argb Value
//! 
//! Format: `0xAARRGGBB`
//! 
void omw::Color::setARGB(int32_t argb)
{
    set((argb >> 16) & 0xFF,
        (argb >> 8) & 0xFF,
        argb & 0xFF,
        (argb >> 24) & 0xFF);
}

void omw::Color::setR(uint8_t value)
{
    rValue = value;
    validity = true;
}

void omw::Color::setG(uint8_t value)
{
    gValue = value;
    validity = true;
}

void omw::Color::setB(uint8_t value)
{
    bValue = value;
    validity = true;
}

void omw::Color::setA(uint8_t value)
{
    aValue = value;
    validity = true;
}

//! @return The red value of the color
uint8_t omw::Color::r() const
{
    return rValue;
}

//! @return The green value of the color
uint8_t omw::Color::g() const
{
    return gValue;
}

//! @return The blue value of the color
uint8_t omw::Color::b() const
{
    return bValue;
}

//! @return The alpha value of the color
uint8_t omw::Color::a() const
{
    return aValue;
}

//! @return An integer RGB representation of the color
//! 
//! Format: `0x00RRGGBB`
//! 
int32_t omw::Color::toRGB() const
{
    return (toARGB() & 0x00FFFFFF);
}

//! @return An integer ARGB representation of the color
//! 
//! Format: `0xAARRGGBB`
//! 
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

//! @return A string representation of the color
//! 
//! Format: `"RRGGBB"`
//! 
omw::string omw::Color::toString() const
{
    omw::string str = "";
    str += omw::toHexStr(r());
    str += omw::toHexStr(g());
    str += omw::toHexStr(b());
    return str;
}

//! @return A string representation of the color
//! 
//! Format: `"AARRGGBB"`
//! 
omw::string omw::Color::toStringARGB() const
{
    return omw::toHexStr(toARGB());
}

//! @return A CSS string representation of the color
//! 
//! Format: `"#RRGGBB"`
//! 
omw::string omw::Color::toCssStr() const
{
    omw::string str = "#";
    str += omw::toHexStr(r());
    str += omw::toHexStr(g());
    str += omw::toHexStr(b());
    return str;
}

//! @param operand A
//! @return `*this`
//! 
//! Calculates the alpha composit of A over B, where `*this` is B and the operand is A.
//! 
//! If one of the colors is invalid, the result is also invalid. However all color values are computed anyway.
//! 
omw::Color& omw::Color::operator+=(const omw::Color& operand)
{
    const bool thisWasInvalid = !this->isValid();

    //  if (a.a() == 0xFF) this->set(a.r(), a.g(), a.b(), a.a());
    //  else if (a.a() > 0)
    //  {
    //      const float aa = (float)a.a() / 255;
    //      const float ab = (float)this->a() / 255;
    //      const float ar = aa + ab * ((float)1 - aa);
    //  
    //      const float ca[3] = { (float)a.r() / 255, (float)a.g() / 255, (float)a.b() / 255 };
    //      const float cb[3] = { (float)this->r() / 255, (float)this->g() / 255, (float)this->b() / 255 };
    //      float cr[3];
    //      for (size_t i = 0; i < 3; ++i) cr[i] = ((ca[i] * aa) + (cb[i] * ab * ((float)1 - aa))) / ar;
    //  
    //      const uint8_t comp_r = (uint8_t)std::lround(cr[0] * 255);
    //      const uint8_t comp_g = (uint8_t)std::lround(cr[1] * 255);
    //      const uint8_t comp_b = (uint8_t)std::lround(cr[2] * 255);
    //      const uint8_t comp_a = (uint8_t)std::lround(ar * 255);
    //  
    //      this->set(comp_r, comp_g, comp_b, comp_a);
    //  }
    //  // else /*nop*/;  a has no impact

    this->setARGB(omw::alphaComposit(operand.toARGB(), this->toARGB()));

    if (thisWasInvalid || !operand.isValid()) this->invalidate();
    return *this;
}

//! 
//! See omw::fromWinColor()
//! 
void omw::Color::from_win(uint32_t winCol)
{
    uint8_t r = winCol & 0xFF;
    uint8_t g = (winCol >> 8) & 0xFF;
    uint8_t b = (winCol >> 16) & 0xFF;
    set(r, g, b, 0xFF);
}

//! 
//! See omw::fromWinColor()
//! 
uint32_t omw::Color::to_win() const
{
    uint32_t col = b();
    col <<= 8;
    col |= g();
    col <<= 8;
    col |= r();
    return col;
}

//! Format: `0xBBGGRR`
//! See <a href="https://docs.wxwidgets.org/3.0/classwx_colour.html" target="_blank">wxColour Class Reference</a>
void omw::Color::from_wxW_RGB(uint32_t wxWCol)
{
    from_wxW_RGBA(0xFF000000 | wxWCol);
}

//! 
//! See omw::fromWxColor()
//! 
void omw::Color::from_wxW_RGBA(uint32_t wxWCol)
{
    uint8_t r = wxWCol & 0xFF;
    uint8_t g = (wxWCol >> 8) & 0xFF;
    uint8_t b = (wxWCol >> 16) & 0xFF;
    uint8_t a = (wxWCol >> 24) & 0xFF;
    set(r, g, b, a);
}

//! Format: `0xBBGGRR`
//! See <a href="https://docs.wxwidgets.org/3.0/classwx_colour.html" target="_blank">wxColour Class Reference</a>
uint32_t omw::Color::to_wxW_RGB() const
{
    return (to_wxW_RGBA() & 0x00FFFFFF);
}

//! 
//! See omw::fromWxColor()
//! 
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



//! @param lhs B
//! @param rhs A
//! @return Alpha composit of A over B
//! 
//! If one of the colors is invalid, the result is also invalid. However all color values are computed anyway.
//! 
omw::Color omw::operator+(const omw::Color& lhs, const omw::Color& rhs)
{
    omw::Color r(lhs);
    r += rhs;
    return r;
}

//! 
//! Checks for equality of the validity and the color values.
//!  
bool omw::operator==(const omw::Color& lhs, const omw::Color& rhs)
{
    return ((lhs.isValid() == rhs.isValid()) && (lhs.toARGB() == rhs.toARGB()));
}

//! 
//! See `omw::operator==(const omw::Color&, const omw::Color&)`.
//! 
bool omw::operator!=(const omw::Color& lhs, const omw::Color& rhs)
{
    return !(lhs == rhs);
}



//! @return Alpha composit of A over B
//! 
//! Format: `0xAACCCCCC` where CCCCCC is any combination of RR, GG and BB, and has to be consistent for input and return values.
//! 
int32_t omw::alphaComposit(int32_t a_ACCC, int32_t b_ACCC)
{
    const uint8_t tmpA[] =
    {
        (uint8_t)((a_ACCC >> 24) & 0xFF),   // alpha
        (uint8_t)((a_ACCC >> 16) & 0xFF),   // color component 1
        (uint8_t)((a_ACCC >> 8) & 0xFF),    // color component 2
        (uint8_t)(a_ACCC & 0xFF)            // color component 3
    };

    const uint8_t tmpB[] =
    {
        (uint8_t)((b_ACCC >> 24) & 0xFF),
        (uint8_t)((b_ACCC >> 16) & 0xFF),
        (uint8_t)((b_ACCC >> 8) & 0xFF),
        (uint8_t)(b_ACCC & 0xFF)
    };

    int32_t result;

    if (tmpA[0] == 0xFF) result = a_ACCC;
    else if (tmpA[0] > 0)
    {
        const float aa = (float)tmpA[0] / 255;
        const float ab = (float)tmpB[0] / 255;
        const float ar = aa + ab * ((float)1 - aa);

        const float ca[3] = { (float)tmpA[1] / 255, (float)tmpA[2] / 255, (float)tmpA[3] / 255 };
        const float cb[3] = { (float)tmpB[1] / 255, (float)tmpB[2] / 255, (float)tmpB[3] / 255 };
        float cr[3];

        for (size_t i = 0; i < 3; ++i) cr[i] = ((ca[i] * aa) + (cb[i] * ab * ((float)1 - aa))) / ar;

        result = std::lround(ar * 255);
        result <<= 8;
        result |= std::lround(cr[0] * 255);
        result <<= 8;
        result |= std::lround(cr[1] * 255);
        result <<= 8;
        result |= std::lround(cr[2] * 255);
    }
    else result = b_ACCC;

    return result;
}

//! @return Alpha composit of A over B
//! 
//! If one of the colors is invalid, the return value is also invalid. However all color values are computed anyway.
//! 
omw::Color omw::alphaComposit(const omw::Color& a, const omw::Color& b)
{
    return b + a;
}

//! @brief Writes the alpha composit of A over B to B.
//! @param a_ACCC 
//! @param b_ACCC [in/out] 
//! 
//! Format: `0xAACCCCCC` where CCCCCC is any combination of RR, GG and BB, and has to be consistent for input and output values.
//! 
void omw::alphaComposit_apply(int32_t a_ACCC, int32_t& b_ACCC)
{
    b_ACCC = omw::alphaComposit(a_ACCC, b_ACCC);
}

//! @brief Writes the alpha composit of A over B to B.
//! @param a 
//! @param b  [in/out] 
//! 
//! If one of the colors is invalid, the result is also invalid. However all color values are computed anyway.
//! 
void omw::alphaComposit_apply(const omw::Color& a, omw::Color& b)
{
    b += a;
}



//! @brief Converts from a Windows API color.
//! 
//! Format: `0xBBGGRR`
//! 
//! See <a href="https://docs.microsoft.com/en-us/windows/win32/gdi/colorref" target="_blank">COLORREF</a>
//! 
omw::Color omw::fromWinColor(uint32_t winCol)
{
    omw::Color r;
    r.from_win(winCol);
    return r;
}

//! @brief Converts from a wxWidgets API color.
//! 
//! Format: `0xAABBGGRR`
//! 
//! See <a href="https://docs.wxwidgets.org/3.0/classwx_colour.html" target="_blank">wxColour Class Reference</a>
//! 
omw::Color omw::fromWxColor(uint32_t wxRGBA)
{
    omw::Color r;
    r.from_wxW_RGBA(wxRGBA);
    return r;
}
