/*
author         Oliver Blaser
date           15.09.2021
copyright      MIT - Copyright (c) 2021 Oliver Blaser
*/

#ifndef OMW_COLOR_H
#define OMW_COLOR_H

#include <cstdint>

#include "../omw/string.h"

namespace omw
{
    class Color
    {
    public:
        Color();
        Color(int32_t rgb);
        Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 0xFF);
        Color(const std::string& css);
        Color(const char* css);
        virtual ~Color() {}

        bool isValid() const;
        void invalidate();

        void clear();
        void opaque();
        void transparent();

        void set(int32_t rgb);
        void set(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 0xFF);
        void set(const std::string& css);
        void set(const char* css);
        void setARGB(int32_t argb);
        void setR(uint8_t value);
        void setG(uint8_t value);
        void setB(uint8_t value);
        void setA(uint8_t value);

        uint8_t r() const;
        uint8_t g() const;
        uint8_t b() const;
        uint8_t a() const;
        int32_t toRGB() const;
        int32_t toARGB() const;

        omw::string toString() const;
        omw::string toCssStr() const;

        omw::Color& operator+=(const omw::Color& addend);
        omw::Color& operator-=(const omw::Color& subtrahend);
        friend omw::Color operator+(const omw::Color& lAddend, const omw::Color& rAddend);
        friend omw::Color operator-(const omw::Color& minuend, const omw::Color& subtrahend);
        friend bool operator==(const omw::Color& left, const omw::Color& right);
        friend bool operator!=(const omw::Color& left, const omw::Color& right);

        void from_win32(uint32_t winCol);
        uint32_t to_win32() const;
        void from_wxW_RGB(uint32_t wxWCol);
        void from_wxW_RGBA(uint32_t wxWCol);
        uint32_t to_wxW_RGB() const;
        uint32_t to_wxW_RGBA() const;

    private:
        bool validity;
        uint8_t rValue;
        uint8_t gValue;
        uint8_t bValue;
        uint8_t aValue;
    };
}

#endif // OMW_COLOR_H
