/*
author         Oliver Blaser
date           07.09.2021
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
        Color(int rgb);
        Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 0xFF);
        Color(const omw::string& css);
        virtual ~Color() {}

        void set(int rgb);
        void set(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 0xFF);
        void set(const omw::string& css);
        void setARGB(int argb);

        uint8_t r() const;
        uint8_t g() const;
        uint8_t b() const;
        uint8_t a() const;

        int toRGB() const;
        int toARGB() const;

        std::string cssStr() const;

        void from_win32(uint32_t winCol);
        uint32_t to_win32() const;
        void from_wxW_RGB(uint32_t wxWCol);
        void from_wxW_RGBA(uint32_t wxWCol);
        uint32_t to_wxW_RGB() const;
        uint32_t to_wxW_RGBA() const;

    private:
        uint8_t rValue;
        uint8_t gValue;
        uint8_t bValue;
        uint8_t aValue;
    };
}

#endif // OMW_COLOR_H
