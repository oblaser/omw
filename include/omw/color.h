/*
author         Oliver Blaser
date           17.09.2021
copyright      MIT - Copyright (c) 2021 Oliver Blaser
*/

#ifndef IG_OMW_COLOR_H
#define IG_OMW_COLOR_H

#include <cstdint>

#include "../omw/string.h"

namespace omw
{
    /*! \addtogroup grp_colorLib
    * @{
    */

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
        void validate(bool state = true);
        void invalidate();

        void clear();
        void opaque();
        void transparent();

        void set(int32_t rgb);
        void set(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 0xFF);
        void set(const omw::Color& color);
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
        omw::string toStringARGB() const;
        omw::string toCssStr() const;

        omw::Color& operator+=(const omw::Color& operand);
        friend omw::Color operator+(const omw::Color& lhs, const omw::Color& rhs);
        friend bool operator==(const omw::Color& left, const omw::Color& right);
        friend bool operator!=(const omw::Color& left, const omw::Color& right);

        //! \name Windows API Support
        /// @{
        void from_win(uint32_t winCol);
        uint32_t to_win() const;
        /// @}
        //! \name wxWidgets API Support
        /// @{
        void from_wxW_RGB(uint32_t wxWCol);
        void from_wxW_RGBA(uint32_t wxWCol);
        uint32_t to_wxW_RGB() const;
        uint32_t to_wxW_RGBA() const;
        /// @}

    private:
        bool validity;
        uint8_t rValue;
        uint8_t gValue;
        uint8_t bValue;
        uint8_t aValue;
    };



    int32_t alphaComposit(int32_t a_ACCC, int32_t b_ACCC);
    omw::Color alphaComposit(const omw::Color& a, const omw::Color& b);
    void alphaComposit_apply(int32_t a_ACCC, int32_t& b_ACCC);
    void alphaComposit_apply(const omw::Color& a, omw::Color& b);



    omw::Color fromWinColor(uint32_t winCol);
    omw::Color fromWxColor(uint32_t wxRGBA);



    //! @brief Predefined Colors
    namespace colors
    {
        constexpr int32_t transparent_argb = 0x00FFFFFF;
        constexpr int32_t aliceBlue_argb = 0xFFF0F8FF;
        constexpr int32_t antiqueWhite_argb = 0xFFFAEBD7;
        constexpr int32_t aqua_argb = 0xFF00FFFF;
        constexpr int32_t aquamarine_argb = 0xFF7FFFD4;
        constexpr int32_t azure_argb = 0xFFF0FFFF;
        constexpr int32_t beige_argb = 0xFFF5F5DC;
        constexpr int32_t bisque_argb = 0xFFFFE4C4;
        constexpr int32_t black_argb = 0xFF000000;
        constexpr int32_t blanchedAlmond_argb = 0xFFFFEBCD;
        constexpr int32_t blue_argb = 0xFF0000FF;
        constexpr int32_t blueViolet_argb = 0xFF8A2BE2;
        constexpr int32_t brown_argb = 0xFFA52A2A;
        constexpr int32_t burlyWood_argb = 0xFFDEB887;
        constexpr int32_t cadetBlue_argb = 0xFF5F9EA0;
        constexpr int32_t chartreuse_argb = 0xFF7FFF00;
        constexpr int32_t chocolate_argb = 0xFFD2691E;
        constexpr int32_t coral_argb = 0xFFFF7F50;
        constexpr int32_t cornflowerBlue_argb = 0xFF6495ED;
        constexpr int32_t cornsilk_argb = 0xFFFFF8DC;
        constexpr int32_t crimson_argb = 0xFFDC143C;
        constexpr int32_t cyan_argb = 0xFF00FFFF;
        constexpr int32_t darkBlue_argb = 0xFF00008B;
        constexpr int32_t darkCyan_argb = 0xFF008B8B;
        constexpr int32_t darkGoldenrod_argb = 0xFFB8860B;
        constexpr int32_t darkGray_argb = 0xFFA9A9A9;
        constexpr int32_t darkGreen_argb = 0xFF006400;
        constexpr int32_t darkKhaki_argb = 0xFFBDB76B;
        constexpr int32_t darkMagenta_argb = 0xFF8B008B;
        constexpr int32_t darkOliveGreen_argb = 0xFF556B2F;
        constexpr int32_t darkOrange_argb = 0xFFFF8C00;
        constexpr int32_t darkOrchid_argb = 0xFF9932CC;
        constexpr int32_t darkRed_argb = 0xFF8B0000;
        constexpr int32_t darkSalmon_argb = 0xFFE9967A;
        constexpr int32_t darkSeaGreen_argb = 0xFF8FBC8F;
        constexpr int32_t darkSlateBlue_argb = 0xFF483D8B;
        constexpr int32_t darkSlateGray_argb = 0xFF2F4F4F;
        constexpr int32_t darkTurquoise_argb = 0xFF00CED1;
        constexpr int32_t darkViolet_argb = 0xFF9400D3;
        constexpr int32_t deepPink_argb = 0xFFFF1493;
        constexpr int32_t deepSkyBlue_argb = 0xFF00BFFF;
        constexpr int32_t dimGray_argb = 0xFF696969;
        constexpr int32_t dodgerBlue_argb = 0xFF1E90FF;
        constexpr int32_t firebrick_argb = 0xFFB22222;
        constexpr int32_t floralWhite_argb = 0xFFFFFAF0;
        constexpr int32_t forestGreen_argb = 0xFF228B22;
        constexpr int32_t fuchsia_argb = 0xFFFF00FF;
        constexpr int32_t gainsboro_argb = 0xFFDCDCDC;
        constexpr int32_t ghostWhite_argb = 0xFFF8F8FF;
        constexpr int32_t gold_argb = 0xFFFFD700;
        constexpr int32_t goldenrod_argb = 0xFFDAA520;
        constexpr int32_t gray_argb = 0xFF808080;
        constexpr int32_t green_argb = 0xFF008000;
        constexpr int32_t greenYellow_argb = 0xFFADFF2F;
        constexpr int32_t honeydew_argb = 0xFFF0FFF0;
        constexpr int32_t hotPink_argb = 0xFFFF69B4;
        constexpr int32_t indianRed_argb = 0xFFCD5C5C;
        constexpr int32_t indigo_argb = 0xFF4B0082;
        constexpr int32_t ivory_argb = 0xFFFFFFF0;
        constexpr int32_t khaki_argb = 0xFFF0E68C;
        constexpr int32_t lavender_argb = 0xFFE6E6FA;
        constexpr int32_t lavenderBlush_argb = 0xFFFFF0F5;
        constexpr int32_t lawnGreen_argb = 0xFF7CFC00;
        constexpr int32_t lemonChiffon_argb = 0xFFFFFACD;
        constexpr int32_t lightBlue_argb = 0xFFADD8E6;
        constexpr int32_t lightCoral_argb = 0xFFF08080;
        constexpr int32_t lightCyan_argb = 0xFFE0FFFF;
        constexpr int32_t lightGoldenrodYellow_argb = 0xFFFAFAD2;
        constexpr int32_t lightGray_argb = 0xFFD3D3D3;
        constexpr int32_t lightGreen_argb = 0xFF90EE90;
        constexpr int32_t lightPink_argb = 0xFFFFB6C1;
        constexpr int32_t lightSalmon_argb = 0xFFFFA07A;
        constexpr int32_t lightSeaGreen_argb = 0xFF20B2AA;
        constexpr int32_t lightSkyBlue_argb = 0xFF87CEFA;
        constexpr int32_t lightSlateGray_argb = 0xFF778899;
        constexpr int32_t lightSteelBlue_argb = 0xFFB0C4DE;
        constexpr int32_t lightYellow_argb = 0xFFFFFFE0;
        constexpr int32_t lime_argb = 0xFF00FF00;
        constexpr int32_t limeGreen_argb = 0xFF32CD32;
        constexpr int32_t linen_argb = 0xFFFAF0E6;
        constexpr int32_t magenta_argb = 0xFFFF00FF;
        constexpr int32_t maroon_argb = 0xFF800000;
        constexpr int32_t mediumAquamarine_argb = 0xFF66CDAA;
        constexpr int32_t mediumBlue_argb = 0xFF0000CD;
        constexpr int32_t mediumOrchid_argb = 0xFFBA55D3;
        constexpr int32_t mediumPurple_argb = 0xFF9370DB;
        constexpr int32_t mediumSeaGreen_argb = 0xFF3CB371;
        constexpr int32_t mediumSlateBlue_argb = 0xFF7B68EE;
        constexpr int32_t mediumSpringGreen_argb = 0xFF00FA9A;
        constexpr int32_t mediumTurquoise_argb = 0xFF48D1CC;
        constexpr int32_t mediumVioletRed_argb = 0xFFC71585;
        constexpr int32_t midnightBlue_argb = 0xFF191970;
        constexpr int32_t mintCream_argb = 0xFFF5FFFA;
        constexpr int32_t mistyRose_argb = 0xFFFFE4E1;
        constexpr int32_t moccasin_argb = 0xFFFFE4B5;
        constexpr int32_t navajoWhite_argb = 0xFFFFDEAD;
        constexpr int32_t navy_argb = 0xFF000080;
        constexpr int32_t oldLace_argb = 0xFFFDF5E6;
        constexpr int32_t olive_argb = 0xFF808000;
        constexpr int32_t oliveDrab_argb = 0xFF6B8E23;
        constexpr int32_t orange_argb = 0xFFFFA500;
        constexpr int32_t orangeRed_argb = 0xFFFF4500;
        constexpr int32_t orchid_argb = 0xFFDA70D6;
        constexpr int32_t paleGoldenrod_argb = 0xFFEEE8AA;
        constexpr int32_t paleGreen_argb = 0xFF98FB98;
        constexpr int32_t paleTurquoise_argb = 0xFFAFEEEE;
        constexpr int32_t paleVioletRed_argb = 0xFFDB7093;
        constexpr int32_t papayaWhip_argb = 0xFFFFEFD5;
        constexpr int32_t peachPuff_argb = 0xFFFFDAB9;
        constexpr int32_t peru_argb = 0xFFCD853F;
        constexpr int32_t pink_argb = 0xFFFFC0CB;
        constexpr int32_t plum_argb = 0xFFDDA0DD;
        constexpr int32_t powderBlue_argb = 0xFFB0E0E6;
        constexpr int32_t purple_argb = 0xFF800080;
        constexpr int32_t red_argb = 0xFFFF0000;
        constexpr int32_t rosyBrown_argb = 0xFFBC8F8F;
        constexpr int32_t royalBlue_argb = 0xFF4169E1;
        constexpr int32_t saddleBrown_argb = 0xFF8B4513;
        constexpr int32_t salmon_argb = 0xFFFA8072;
        constexpr int32_t sandyBrown_argb = 0xFFF4A460;
        constexpr int32_t seaGreen_argb = 0xFF2E8B57;
        constexpr int32_t seaShell_argb = 0xFFFFF5EE;
        constexpr int32_t sienna_argb = 0xFFA0522D;
        constexpr int32_t silver_argb = 0xFFC0C0C0;
        constexpr int32_t skyBlue_argb = 0xFF87CEEB;
        constexpr int32_t slateBlue_argb = 0xFF6A5ACD;
        constexpr int32_t slateGray_argb = 0xFF708090;
        constexpr int32_t snow_argb = 0xFFFFFAFA;
        constexpr int32_t springGreen_argb = 0xFF00FF7F;
        constexpr int32_t steelBlue_argb = 0xFF4682B4;
        constexpr int32_t tan_argb = 0xFFD2B48C;
        constexpr int32_t teal_argb = 0xFF008080;
        constexpr int32_t thistle_argb = 0xFFD8BFD8;
        constexpr int32_t tomato_argb = 0xFFFF6347;
        constexpr int32_t turquoise_argb = 0xFF40E0D0;
        constexpr int32_t violet_argb = 0xFFEE82EE;
        constexpr int32_t wheat_argb = 0xFFF5DEB3;
        constexpr int32_t white_argb = 0xFFFFFFFF;
        constexpr int32_t whiteSmoke_argb = 0xFFF5F5F5;
        constexpr int32_t yellow_argb = 0xFFFFFF00;
        constexpr int32_t yellowGreen_argb = 0xFF9ACD32;

        const omw::Color transparent = omw::Color(255, 255, 255, 0);
        const omw::Color aliceBlue = omw::Color(aliceBlue_argb);
        const omw::Color antiqueWhite = omw::Color(antiqueWhite_argb);
        const omw::Color aqua = omw::Color(aqua_argb);
        const omw::Color aquamarine = omw::Color(aquamarine_argb);
        const omw::Color azure = omw::Color(azure_argb);
        const omw::Color beige = omw::Color(beige_argb);
        const omw::Color bisque = omw::Color(bisque_argb);
        const omw::Color black = omw::Color(black_argb);
        const omw::Color blanchedAlmond = omw::Color(blanchedAlmond_argb);
        const omw::Color blue = omw::Color(blue_argb);
        const omw::Color blueViolet = omw::Color(blueViolet_argb);
        const omw::Color brown = omw::Color(brown_argb);
        const omw::Color burlyWood = omw::Color(burlyWood_argb);
        const omw::Color cadetBlue = omw::Color(cadetBlue_argb);
        const omw::Color chartreuse = omw::Color(chartreuse_argb);
        const omw::Color chocolate = omw::Color(chocolate_argb);
        const omw::Color coral = omw::Color(coral_argb);
        const omw::Color cornflowerBlue = omw::Color(cornflowerBlue_argb);
        const omw::Color cornsilk = omw::Color(cornsilk_argb);
        const omw::Color crimson = omw::Color(crimson_argb);
        const omw::Color cyan = omw::Color(cyan_argb);
        const omw::Color darkBlue = omw::Color(darkBlue_argb);
        const omw::Color darkCyan = omw::Color(darkCyan_argb);
        const omw::Color darkGoldenrod = omw::Color(darkGoldenrod_argb);
        const omw::Color darkGray = omw::Color(darkGray_argb);
        const omw::Color darkGreen = omw::Color(darkGreen_argb);
        const omw::Color darkKhaki = omw::Color(darkKhaki_argb);
        const omw::Color darkMagenta = omw::Color(darkMagenta_argb);
        const omw::Color darkOliveGreen = omw::Color(darkOliveGreen_argb);
        const omw::Color darkOrange = omw::Color(darkOrange_argb);
        const omw::Color darkOrchid = omw::Color(darkOrchid_argb);
        const omw::Color darkRed = omw::Color(darkRed_argb);
        const omw::Color darkSalmon = omw::Color(darkSalmon_argb);
        const omw::Color darkSeaGreen = omw::Color(darkSeaGreen_argb);
        const omw::Color darkSlateBlue = omw::Color(darkSlateBlue_argb);
        const omw::Color darkSlateGray = omw::Color(darkSlateGray_argb);
        const omw::Color darkTurquoise = omw::Color(darkTurquoise_argb);
        const omw::Color darkViolet = omw::Color(darkViolet_argb);
        const omw::Color deepPink = omw::Color(deepPink_argb);
        const omw::Color deepSkyBlue = omw::Color(deepSkyBlue_argb);
        const omw::Color dimGray = omw::Color(dimGray_argb);
        const omw::Color dodgerBlue = omw::Color(dodgerBlue_argb);
        const omw::Color firebrick = omw::Color(firebrick_argb);
        const omw::Color floralWhite = omw::Color(floralWhite_argb);
        const omw::Color forestGreen = omw::Color(forestGreen_argb);
        const omw::Color fuchsia = omw::Color(fuchsia_argb);
        const omw::Color gainsboro = omw::Color(gainsboro_argb);
        const omw::Color ghostWhite = omw::Color(ghostWhite_argb);
        const omw::Color gold = omw::Color(gold_argb);
        const omw::Color goldenrod = omw::Color(goldenrod_argb);
        const omw::Color gray = omw::Color(gray_argb);
        const omw::Color green = omw::Color(green_argb);
        const omw::Color greenYellow = omw::Color(greenYellow_argb);
        const omw::Color honeydew = omw::Color(honeydew_argb);
        const omw::Color hotPink = omw::Color(hotPink_argb);
        const omw::Color indianRed = omw::Color(indianRed_argb);
        const omw::Color indigo = omw::Color(indigo_argb);
        const omw::Color ivory = omw::Color(ivory_argb);
        const omw::Color khaki = omw::Color(khaki_argb);
        const omw::Color lavender = omw::Color(lavender_argb);
        const omw::Color lavenderBlush = omw::Color(lavenderBlush_argb);
        const omw::Color lawnGreen = omw::Color(lawnGreen_argb);
        const omw::Color lemonChiffon = omw::Color(lemonChiffon_argb);
        const omw::Color lightBlue = omw::Color(lightBlue_argb);
        const omw::Color lightCoral = omw::Color(lightCoral_argb);
        const omw::Color lightCyan = omw::Color(lightCyan_argb);
        const omw::Color lightGoldenrodYellow = omw::Color(lightGoldenrodYellow_argb);
        const omw::Color lightGray = omw::Color(lightGray_argb);
        const omw::Color lightGreen = omw::Color(lightGreen_argb);
        const omw::Color lightPink = omw::Color(lightPink_argb);
        const omw::Color lightSalmon = omw::Color(lightSalmon_argb);
        const omw::Color lightSeaGreen = omw::Color(lightSeaGreen_argb);
        const omw::Color lightSkyBlue = omw::Color(lightSkyBlue_argb);
        const omw::Color lightSlateGray = omw::Color(lightSlateGray_argb);
        const omw::Color lightSteelBlue = omw::Color(lightSteelBlue_argb);
        const omw::Color lightYellow = omw::Color(lightYellow_argb);
        const omw::Color lime = omw::Color(lime_argb);
        const omw::Color limeGreen = omw::Color(limeGreen_argb);
        const omw::Color linen = omw::Color(linen_argb);
        const omw::Color magenta = omw::Color(magenta_argb);
        const omw::Color maroon = omw::Color(maroon_argb);
        const omw::Color mediumAquamarine = omw::Color(mediumAquamarine_argb);
        const omw::Color mediumBlue = omw::Color(mediumBlue_argb);
        const omw::Color mediumOrchid = omw::Color(mediumOrchid_argb);
        const omw::Color mediumPurple = omw::Color(mediumPurple_argb);
        const omw::Color mediumSeaGreen = omw::Color(mediumSeaGreen_argb);
        const omw::Color mediumSlateBlue = omw::Color(mediumSlateBlue_argb);
        const omw::Color mediumSpringGreen = omw::Color(mediumSpringGreen_argb);
        const omw::Color mediumTurquoise = omw::Color(mediumTurquoise_argb);
        const omw::Color mediumVioletRed = omw::Color(mediumVioletRed_argb);
        const omw::Color midnightBlue = omw::Color(midnightBlue_argb);
        const omw::Color mintCream = omw::Color(mintCream_argb);
        const omw::Color mistyRose = omw::Color(mistyRose_argb);
        const omw::Color moccasin = omw::Color(moccasin_argb);
        const omw::Color navajoWhite = omw::Color(navajoWhite_argb);
        const omw::Color navy = omw::Color(navy_argb);
        const omw::Color oldLace = omw::Color(oldLace_argb);
        const omw::Color olive = omw::Color(olive_argb);
        const omw::Color oliveDrab = omw::Color(oliveDrab_argb);
        const omw::Color orange = omw::Color(orange_argb);
        const omw::Color orangeRed = omw::Color(orangeRed_argb);
        const omw::Color orchid = omw::Color(orchid_argb);
        const omw::Color paleGoldenrod = omw::Color(paleGoldenrod_argb);
        const omw::Color paleGreen = omw::Color(paleGreen_argb);
        const omw::Color paleTurquoise = omw::Color(paleTurquoise_argb);
        const omw::Color paleVioletRed = omw::Color(paleVioletRed_argb);
        const omw::Color papayaWhip = omw::Color(papayaWhip_argb);
        const omw::Color peachPuff = omw::Color(peachPuff_argb);
        const omw::Color peru = omw::Color(peru_argb);
        const omw::Color pink = omw::Color(pink_argb);
        const omw::Color plum = omw::Color(plum_argb);
        const omw::Color powderBlue = omw::Color(powderBlue_argb);
        const omw::Color purple = omw::Color(purple_argb);
        const omw::Color red = omw::Color(red_argb);
        const omw::Color rosyBrown = omw::Color(rosyBrown_argb);
        const omw::Color royalBlue = omw::Color(royalBlue_argb);
        const omw::Color saddleBrown = omw::Color(saddleBrown_argb);
        const omw::Color salmon = omw::Color(salmon_argb);
        const omw::Color sandyBrown = omw::Color(sandyBrown_argb);
        const omw::Color seaGreen = omw::Color(seaGreen_argb);
        const omw::Color seaShell = omw::Color(seaShell_argb);
        const omw::Color sienna = omw::Color(sienna_argb);
        const omw::Color silver = omw::Color(silver_argb);
        const omw::Color skyBlue = omw::Color(skyBlue_argb);
        const omw::Color slateBlue = omw::Color(slateBlue_argb);
        const omw::Color slateGray = omw::Color(slateGray_argb);
        const omw::Color snow = omw::Color(snow_argb);
        const omw::Color springGreen = omw::Color(springGreen_argb);
        const omw::Color steelBlue = omw::Color(steelBlue_argb);
        const omw::Color tan = omw::Color(tan_argb);
        const omw::Color teal = omw::Color(teal_argb);
        const omw::Color thistle = omw::Color(thistle_argb);
        const omw::Color tomato = omw::Color(tomato_argb);
        const omw::Color turquoise = omw::Color(turquoise_argb);
        const omw::Color violet = omw::Color(violet_argb);
        const omw::Color wheat = omw::Color(wheat_argb);
        const omw::Color white = omw::Color(white_argb);
        const omw::Color whiteSmoke = omw::Color(whiteSmoke_argb);
        const omw::Color yellow = omw::Color(yellow_argb);
        const omw::Color yellowGreen = omw::Color(yellowGreen_argb);

        //! @brief Native Windows colors
        //! 
        //! Defined on all platforms.
        //! 
        namespace windows
        {
            constexpr int32_t activeBorder_argb = 0xFFB4B4B4;
            constexpr int32_t activeCaption_argb = 0xFF99B4D1;
            constexpr int32_t activeCaptionText_argb = 0xFF000000;
            constexpr int32_t appWorkspace_argb = 0xFFABABAB;
            constexpr int32_t buttonFace_argb = 0xFFF0F0F0;
            constexpr int32_t buttonHighlight_argb = 0xFFFFFFFF;
            constexpr int32_t buttonShadow_argb = 0xFFA0A0A0;
            constexpr int32_t control_argb = 0xFFF0F0F0;
            constexpr int32_t controlDark_argb = 0xFFA0A0A0;
            constexpr int32_t controlDarkDark_argb = 0xFF696969;
            constexpr int32_t controlLight_argb = 0xFFE3E3E3;
            constexpr int32_t controlLightLight_argb = 0xFFFFFFFF;
            constexpr int32_t controlText_argb = 0xFF000000;
            constexpr int32_t desktop_argb = 0xFF000000;
            constexpr int32_t gradientActiveCaption_argb = 0xFFB9D1EA;
            constexpr int32_t gradientInactiveCaption_argb = 0xFFD7E4F2;
            constexpr int32_t grayText_argb = 0xFF6D6D6D;
            constexpr int32_t highlight_argb = 0xFF0078D7;
            constexpr int32_t highlightText_argb = 0xFFFFFFFF;
            constexpr int32_t hotTrack_argb = 0xFF0066CC;
            constexpr int32_t inactiveBorder_argb = 0xFFF4F7FC;
            constexpr int32_t inactiveCaption_argb = 0xFFBFCDDB;
            constexpr int32_t inactiveCaptionText_argb = 0xFF000000;
            constexpr int32_t info_argb = 0xFFFFFFE1;
            constexpr int32_t infoText_argb = 0xFF000000;
            constexpr int32_t menu_argb = 0xFFF0F0F0;
            constexpr int32_t menuBar_argb = 0xFFF0F0F0;
            constexpr int32_t menuHighlight_argb = 0xFF0078D7;
            constexpr int32_t menuText_argb = 0xFF000000;
            constexpr int32_t scrollBar_argb = 0xFFC8C8C8;
            constexpr int32_t window_argb = 0xFFFFFFFF;
            constexpr int32_t windowFrame_argb = 0xFF646464;
            constexpr int32_t windowText_argb = 0xFF000000;

            const omw::Color activeBorder = omw::Color(activeBorder_argb);
            const omw::Color activeCaption = omw::Color(activeCaption_argb);
            const omw::Color activeCaptionText = omw::Color(activeCaptionText_argb);
            const omw::Color appWorkspace = omw::Color(appWorkspace_argb);
            const omw::Color buttonFace = omw::Color(buttonFace_argb);
            const omw::Color buttonHighlight = omw::Color(buttonHighlight_argb);
            const omw::Color buttonShadow = omw::Color(buttonShadow_argb);
            const omw::Color control = omw::Color(control_argb);
            const omw::Color controlDark = omw::Color(controlDark_argb);
            const omw::Color controlDarkDark = omw::Color(controlDarkDark_argb);
            const omw::Color controlLight = omw::Color(controlLight_argb);
            const omw::Color controlLightLight = omw::Color(controlLightLight_argb);
            const omw::Color controlText = omw::Color(controlText_argb);
            const omw::Color desktop = omw::Color(desktop_argb);
            const omw::Color gradientActiveCaption = omw::Color(gradientActiveCaption_argb);
            const omw::Color gradientInactiveCaption = omw::Color(gradientInactiveCaption_argb);
            const omw::Color grayText = omw::Color(grayText_argb);
            const omw::Color highlight = omw::Color(highlight_argb);
            const omw::Color highlightText = omw::Color(highlightText_argb);
            const omw::Color hotTrack = omw::Color(hotTrack_argb);
            const omw::Color inactiveBorder = omw::Color(inactiveBorder_argb);
            const omw::Color inactiveCaption = omw::Color(inactiveCaption_argb);
            const omw::Color inactiveCaptionText = omw::Color(inactiveCaptionText_argb);
            const omw::Color info = omw::Color(info_argb);
            const omw::Color infoText = omw::Color(infoText_argb);
            const omw::Color menu = omw::Color(menu_argb);
            const omw::Color menuBar = omw::Color(menuBar_argb);
            const omw::Color menuHighlight = omw::Color(menuHighlight_argb);
            const omw::Color menuText = omw::Color(menuText_argb);
            const omw::Color scrollBar = omw::Color(scrollBar_argb);
            const omw::Color window = omw::Color(window_argb);
            const omw::Color windowFrame = omw::Color(windowFrame_argb);
            const omw::Color windowText = omw::Color(windowText_argb);
        }
    }

    /*! @} */
}

#endif // IG_OMW_COLOR_H
