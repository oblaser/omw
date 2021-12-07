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

#include "../omw/defs.h"
#include "../omw/string.h"


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
                constexpr int defaultFont = 10;
                constexpr int font0 = defaultFont;
                constexpr int font1 = 11;
                constexpr int font2 = 12;
                constexpr int font3 = 13;
                constexpr int font4 = 14;
                constexpr int font5 = 15;
                constexpr int font6 = 16;
                constexpr int font7 = 17;
                constexpr int font8 = 18;
                constexpr int font9 = 19;
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
            }
        }
    }

    //! \name Out Stream Manipulators
    /// @{
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& bold(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::bold)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& boldOff(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::boldOff)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& fgBrightBlack(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::fgColorBrightBlack)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& fgBrightCyan(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::fgColorBrightCyan)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& fgBrightYellow(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::fgColorBrightYellow)); }
    template<class CharT, class Traits = std::char_traits<CharT>>
    inline std::basic_ostream<CharT, Traits>& normal(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::reset)); }
    //template<class CharT, class Traits = std::char_traits<CharT>>
    //inline std::basic_ostream<CharT, Traits>& name(std::basic_ostream<CharT, Traits>& os) { return (os << omw::ansiesc::csi::sgr::seq(omw::ansiesc::csi::sgr::param)); }
    /// @}


    /*! @} */
}

#endif // IG_OMW_CLI_H
