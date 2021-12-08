/*
author          Oliver Blaser
date            07.12.2021
copyright       MIT - Copyright (c) 2021 Oliver Blaser
*/

#ifndef IG_OMW_CLI_H
#define IG_OMW_CLI_H

#include <iostream>
#include <string>
#include <vector>

#include "../omw/color.h"
#include "../omw/defs.h"
#include "../omw/string.h"


#ifndef DOXYGEN_EXCLUDE_FROM_DOC
// TODO: move to stream.cpp/.h or similar, and document it properly
namespace omw
{
    class ostream_manip_t
    {
    public:
        ostream_manip_t(const omw::string& argument) : m_arg(argument) {}
        virtual ~ostream_manip_t() {}

        const omw::string& arg() const { return m_arg; }

        template<class CharT, class Traits = std::char_traits<CharT>>
        friend inline std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const omw::ostream_manip_t& manip) { return (os << manip.arg()); }

    protected:
        omw::string m_arg;
    };

    //template<class CharT, class Traits = std::char_traits<CharT>>
    //inline std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const omw::ostream_manip_t& manip) { return (os << manip.arg()); }
}
#endif // DOXYGEN_EXCLUDE_FROM_DOC


namespace omw
{
    /*! \addtogroup grp_cli
    * @{
    */


    //! @brief ANSI Escape Sequences
    //! 
    //! Further information on <a href="https://en.wikipedia.org/wiki/ANSI_escape_code" target="_blank">ANSI Escape Code (Wikipedia)</a>.
    //! 
    namespace ansiesc
    {
        constexpr char argSepChar = ';';

        constexpr char escChar = '\x1B';

        constexpr char csiChar = '[';
        constexpr char stChar = '\\';
        constexpr char oscChar = ']';
        constexpr char sosChar = 'X';

        //! @brief CSI (Control Sequence Introducer)
        namespace csi
        {
            //! \name Control Sequence Types
            /// @{
            constexpr char CUU = 'A';
            constexpr char CUD = 'B';
            constexpr char CUF = 'C';
            constexpr char CUB = 'D';
            constexpr char CUP = 'H';
            constexpr char ED = 'J';
            constexpr char EL = 'K';
            constexpr char SU = 'S';
            constexpr char SD = 'T';
            constexpr char HVP = 'f';
            constexpr char SGR = 'm';
            /// @}

            //! \name Control Sequence Type Aliases
            /// @{
            constexpr char cursorUp = CUU;
            constexpr char cursorDown = CUD;
            constexpr char cursorFwd = CUF;
            constexpr char cursorBack = CUB;
            constexpr char cursorPos = CUP;
            constexpr char eraseDisplay = ED;
            constexpr char eraseLine = EL;
            constexpr char scrollUp = SU;
            constexpr char scrollDown = SD;
            /// @}

            //! \name Arguments
            /// @{
            constexpr int fromCurToEnd = 0;
            constexpr int fromCurToBegin = 1;
            constexpr int entire = 2;
            constexpr int entireAndScrlBk = 3;
            /// @}

            inline omw::string seq(char cs, const omw::string& arg = "") { return (omw::string(1, omw::ansiesc::escChar) + omw::ansiesc::csiChar + arg + cs); }
            inline omw::string seq(char cs, int arg) { return omw::ansiesc::csi::seq(cs, omw::to_string(arg)); }
            inline omw::string seq(char cs, int arg0, int arg1)
            {
                return omw::ansiesc::csi::seq(cs, omw::to_string(arg0) + omw::ansiesc::argSepChar + omw::to_string(arg1));
            }

            //! @brief SGR (Select Graphic Rendition)
            namespace sgr
            {
                constexpr int font_base = 10;
                constexpr int foreground_base = 30;
                constexpr int background_base = 40;
                constexpr int brightForeground_base = 90;
                constexpr int brightBackground_base = 100;

                constexpr int colorBlack = 0;
                constexpr int colorRed = 1;
                constexpr int colorGreen = 2;
                constexpr int colorYellow = 3;
                constexpr int colorBlue = 4;
                constexpr int colorMagenta = 5;
                constexpr int colorCyan = 6;
                constexpr int colorWhite = 7;

                //! \name Parameters
                /// @{
                constexpr int reset = 0;
                constexpr int bold = 1;
                constexpr int faint = 2;
                constexpr int italic = 3;
                constexpr int underline = 4;
                constexpr int blinkSlow = 5;
                constexpr int blinkFast = 6;
                constexpr int reverseVideo = 7;
                constexpr int conceal = 8;
                constexpr int strike = 9;
                constexpr int defaultFont = font_base;
                constexpr int font0 = font_base + 0;
                constexpr int font1 = font_base + 1;
                constexpr int font2 = font_base + 2;
                constexpr int font3 = font_base + 3;
                constexpr int font4 = font_base + 4;
                constexpr int font5 = font_base + 5;
                constexpr int font6 = font_base + 6;
                constexpr int font7 = font_base + 7;
                constexpr int font8 = font_base + 8;
                constexpr int font9 = font_base + 9;
                constexpr int fraktur = 20;
                constexpr int boldFaintOff = 22;
                constexpr int boldOff = boldFaintOff;
                constexpr int faintOff = boldFaintOff;
                constexpr int italicFrakturOff = 23;
                constexpr int italicOff = italicFrakturOff;
                constexpr int frakturOff = italicFrakturOff;
                constexpr int underlineOff = 24;
                constexpr int blinkOff = 25;
                constexpr int reverseVideoOff = 27;
                constexpr int concealOff = 28;
                constexpr int reveal = concealOff;
                constexpr int strikeOff = 29;
                constexpr int fgColorBlack = foreground_base + colorBlack;
                constexpr int fgColorRed = foreground_base + colorRed;
                constexpr int fgColorGreen = foreground_base + colorGreen;
                constexpr int fgColorYellow = foreground_base + colorYellow;
                constexpr int fgColorBlue = foreground_base + colorBlue;
                constexpr int fgColorMagenta = foreground_base + colorMagenta;
                constexpr int fgColorCyan = foreground_base + colorCyan;
                constexpr int fgColorWhite = foreground_base + colorWhite;
                constexpr int setForeColor = 38;
                constexpr int defaultForeColor = 39;
                constexpr int fgColorDefault = defaultForeColor;
                constexpr int bgColorBlack = background_base + colorBlack;
                constexpr int bgColorRed = background_base + colorRed;
                constexpr int bgColorGreen = background_base + colorGreen;
                constexpr int bgColorYellow = background_base + colorYellow;
                constexpr int bgColorBlue = background_base + colorBlue;
                constexpr int bgColorMagenta = background_base + colorMagenta;
                constexpr int bgColorCyan = background_base + colorCyan;
                constexpr int bgColorWhite = background_base + colorWhite;
                constexpr int setBackColor = 48;
                constexpr int defaultBackColor = 49;
                constexpr int bgColorDefault = defaultBackColor;
                constexpr int framed = 51;
                constexpr int encircled = 52;
                constexpr int overlined = 53;
                constexpr int framedEncircledOff = 54;
                constexpr int framedOff = framedEncircledOff;
                constexpr int encircledOff = framedEncircledOff;
                constexpr int overlinedOff = 55;
                constexpr int setUnderlineColor = 58;
                constexpr int defaultUnderlineColor = 59;
                constexpr int super = 73;
                constexpr int sub = 74;
                constexpr int superSubOff = 75;
                constexpr int superOff = superSubOff;
                constexpr int subOff = superSubOff;
                constexpr int fgColorBrightBlack = brightForeground_base + colorBlack;
                constexpr int fgColorBrightRed = brightForeground_base + colorRed;
                constexpr int fgColorBrightGreen = brightForeground_base + colorGreen;
                constexpr int fgColorBrightYellow = brightForeground_base + colorYellow;
                constexpr int fgColorBrightBlue = brightForeground_base + colorBlue;
                constexpr int fgColorBrightMagenta = brightForeground_base + colorMagenta;
                constexpr int fgColorBrightCyan = brightForeground_base + colorCyan;
                constexpr int fgColorBrightWhite = brightForeground_base + colorWhite;
                constexpr int bgColorBrightBlack = brightBackground_base + colorBlack;
                constexpr int bgColorBrightRed = brightBackground_base + colorRed;
                constexpr int bgColorBrightGreen = brightBackground_base + colorGreen;
                constexpr int bgColorBrightYellow = brightBackground_base + colorYellow;
                constexpr int bgColorBrightBlue = brightBackground_base + colorBlue;
                constexpr int bgColorBrightMagenta = brightBackground_base + colorMagenta;
                constexpr int bgColorBrightCyan = brightBackground_base + colorCyan;
                constexpr int bgColorBrightWhite = brightBackground_base + colorWhite;
                /// @}

                //! \name Arguments
                //! Used as <b><tt>arg0</tt></b> in the seq() functions.
                /// @{
                constexpr int setColor_8bit = 5;
                constexpr int setColor_rgb = 2;
                /// @}

                inline omw::string seq(const omw::string& args = "") { return omw::ansiesc::csi::seq(omw::ansiesc::csi::SGR, args); }
                inline omw::string seq(int param) { return omw::ansiesc::csi::sgr::seq(omw::to_string(param)); }
                inline omw::string seq(int param, int arg0, int arg1)
                {
                    return omw::ansiesc::csi::sgr::seq(omw::to_string(param) + omw::ansiesc::argSepChar + omw::to_string(arg0) + omw::ansiesc::argSepChar + omw::to_string(arg1));
                }
                omw::string seq(int param, int arg0, int arg1, int arg2, int arg3);
                omw::string seq(const int* argv, size_t argc);
                inline omw::string seq(const std::vector<int>& args) { return omw::ansiesc::csi::sgr::seq(args.data(), args.size()); }

                //! \name 8-bit Colors
                //! See <a href="https://en.wikipedia.org/wiki/ANSI_escape_code#8-bit" target="_blank">color table</a> on Wikipedia.
                /// @{
                constexpr int col8bit_standardBlack = 0;
                constexpr int col8bit_standardBlue = 1;
                constexpr int col8bit_standardCyan = 2;
                constexpr int col8bit_standardGreen = 3;
                constexpr int col8bit_standardMagenta = 4;
                constexpr int col8bit_standardRed = 5;
                constexpr int col8bit_standardWhite = 6;
                constexpr int col8bit_standardYellow = 7;
                constexpr int col8bit_brightBlack = 8;
                constexpr int col8bit_brightBlue = 9;
                constexpr int col8bit_brightCyan = 10;
                constexpr int col8bit_brightGreen = 11;
                constexpr int col8bit_brightMagenta = 12;
                constexpr int col8bit_brightRed = 13;
                constexpr int col8bit_brightWhite = 14;
                constexpr int col8bit_brightYellow = 15;
                constexpr int col8bit_grayscale26[26] = { 16, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255, 231 };

                //int to8bitColor(uint8_t r, uint8_t g, uint8_t b);
                //int to8bitColor(const omw::Color& color);
                //int to8bitGray(uint8_t value);
                //int to8bitGray(double normValue);
                /// @}
            }
        }
    }

#pragma region ostream-manip
    //! \name Out Stream Manipulators
    /// @{
    inline omw::ostream_manip_t backColor(int color8bit) { return omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::setBackColor, omw::ansiesc::csi::sgr::setColor_8bit, color8bit); }
    inline omw::ostream_manip_t backColor(uint8_t r, uint8_t g, uint8_t b) { return omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::setBackColor, omw::ansiesc::csi::sgr::setColor_rgb, r, g, b); }
    inline omw::ostream_manip_t backColor(const omw::Color& color) { return omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::setBackColor, omw::ansiesc::csi::sgr::setColor_rgb, color.r(), color.g(), color.b()); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& bgBlack(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::bgColorBlack)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& bgBlue(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::bgColorBlue)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& bgBrightBlack(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::bgColorBrightBlack)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& bgBrightBlue(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::bgColorBrightBlue)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& bgBrightCyan(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::bgColorBrightCyan)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& bgBrightGreen(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::bgColorBrightGreen)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& bgBrightMagenta(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::bgColorBrightMagenta)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& bgBrightRed(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::bgColorBrightRed)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& bgBrightWhite(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::bgColorBrightWhite)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& bgBrightYellow(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::bgColorBrightYellow)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& bgCyan(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::bgColorCyan)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& bgDefault(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::bgColorDefault)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& bgGreen(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::bgColorGreen)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& bgMagenta(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::bgColorMagenta)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& bgRed(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::bgColorRed)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& bgWhite(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::bgColorWhite)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& bgYellow(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::bgColorYellow)); }

    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& blinkFast(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::blinkFast)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& blinkOff(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::blinkOff)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& blinkSlow(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::blinkSlow)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& bold(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::bold)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& boldOff(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::boldOff)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& conceal(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::conceal)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& concealOff(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::concealOff)); }

    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& defaultBackColor(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::defaultBackColor)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& defaultColors(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::defaultBackColor, omw::ansiesc::csi::sgr::defaultForeColor, omw::ansiesc::csi::sgr::defaultUnderlineColor)); }

    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& defaultFont(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::defaultFont)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& defaultForeColor(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::defaultForeColor)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& defaultUnderlineColor(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::defaultUnderlineColor)); }

    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& encircled(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::encircled)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& encircledOff(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::encircledOff)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& faint(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::faint)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& faintOff(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::faintOff)); }

    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& fgBlack(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::fgColorBlack)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& fgBlue(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::fgColorBlue)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& fgBrightBlack(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::fgColorBrightBlack)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& fgBrightBlue(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::fgColorBrightBlue)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& fgBrightCyan(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::fgColorBrightCyan)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& fgBrightGreen(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::fgColorBrightGreen)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& fgBrightMagenta(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::fgColorBrightMagenta)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& fgBrightRed(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::fgColorBrightRed)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& fgBrightWhite(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::fgColorBrightWhite)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& fgBrightYellow(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::fgColorBrightYellow)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& fgCyan(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::fgColorCyan)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& fgDefault(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::fgColorDefault)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& fgGreen(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::fgColorGreen)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& fgMagenta(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::fgColorMagenta)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& fgRed(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::fgColorRed)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& fgWhite(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::fgColorWhite)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& fgYellow(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::fgColorYellow)); }

    inline omw::ostream_manip_t font(int index) { return omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::font_base + index); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& font0(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::font0)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& font1(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::font1)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& font2(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::font2)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& font3(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::font3)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& font4(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::font4)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& font5(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::font5)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& font6(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::font6)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& font7(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::font7)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& font8(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::font8)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& font9(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::font9)); }
    inline omw::ostream_manip_t foreColor(int color8bit) { return omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::setForeColor, omw::ansiesc::csi::sgr::setColor_8bit, color8bit); }
    inline omw::ostream_manip_t foreColor(uint8_t r, uint8_t g, uint8_t b) { return omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::setForeColor, omw::ansiesc::csi::sgr::setColor_rgb, r, g, b); }
    inline omw::ostream_manip_t foreColor(const omw::Color& color) { return omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::setForeColor, omw::ansiesc::csi::sgr::setColor_rgb, color.r(), color.g(), color.b()); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& fraktur(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::fraktur)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& frakturOff(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::frakturOff)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& framed(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::framed)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& framedOff(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::framedOff)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& italic(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::italic)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& italicOff(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::italicOff)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& normal(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::reset)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& overlined(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::overlined)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& overlinedOff(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::overlinedOff)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& reveal(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::reveal)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& reverseVideo(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::reverseVideo)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& reverseVideoOff(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::reverseVideoOff)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& strike(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::strike)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& strikeOff(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::strikeOff)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& sub(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::sub)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& subOff(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::subOff)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& super(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::super)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& superOff(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::superOff)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& underline(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::underline)); }
    inline omw::ostream_manip_t underlineColor(int color8bit) { return omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::setUnderlineColor, omw::ansiesc::csi::sgr::setColor_8bit, color8bit); }
    inline omw::ostream_manip_t underlineColor(uint8_t r, uint8_t g, uint8_t b) { return omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::setUnderlineColor, omw::ansiesc::csi::sgr::setColor_rgb, r, g, b); }
    inline omw::ostream_manip_t underlineColor(const omw::Color& color) { return omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::setUnderlineColor, omw::ansiesc::csi::sgr::setColor_rgb, color.r(), color.g(), color.b()); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& underlineOff(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::underlineOff)); }
    /// @}
#pragma endregion ostream-manip


    /*! @} */
}

#endif // IG_OMW_CLI_H
