/*
author          Oliver Blaser
date            07.12.2021
copyright       MIT - Copyright (c) 2021 Oliver Blaser
*/

#include <cmath>
#include <iostream>
#include <string>

#include <omw/cli.h>
#include <omw/color.h>
#include <omw/omw.h>
#ifdef OMW_PLAT_WIN
#include <omw/windows/windows.h>
#endif

using std::cout;
using std::endl;

namespace csi = omw::ansiesc::csi;
namespace sgr = csi::sgr;

namespace
{
    omw::Color intToColor(uint32_t value) // color circle 0 .. 0x5FF
    {
        uint32_t col_value;
        uint32_t state;

        col_value = (value & 0x00FF);
        state = (value >> 8);

        switch (state)
        {
            case 0: // red full ; + green
                col_value = (0xFF0000 | (col_value << 8));
                break;

            case 1: // green full ; - red
                col_value = (0x00FF00 | ((255 - col_value) << 16));
                break;

            case 2: // green full ; + blue
                col_value = (0x00FF00 | (col_value << 0));
                break;

            case 3: // blue full ; - green
                col_value = (0x0000FF | ((255 - col_value) << 8));
                break;

            case 4: // blue full ; + red
                col_value = (0x0000FF | (col_value << 16));
                break;

            case 5: // red full ; -blue
                col_value = (0xFF0000 | ((255 - col_value) << 0));
                break;

            default:
                break;
        }

        return col_value;
    }
}



int main(int argc, char** argv)
{
    int r = 0;

#ifdef OMW_PLAT_WIN
    if (!omw::windows::consoleEnVirtualTermProc()) cout << "faild to enable VT100" << endl;
    if (!omw::windows::consoleSetCodePageUTF8()) cout << "faild to set code page to UTF-8" << endl;
#endif

#pragma region sgr
    cout << "\n  --======# SGR #======--" << endl;

    cout << omw::fgBrightBlack << "bright" << omw::fgBlack << "black" << endl;
    cout << omw::fgBrightRed << "bright" << omw::fgRed << "red" << endl;
    cout << omw::fgBrightGreen << "bright" << omw::fgGreen << "green" << endl;
    cout << omw::fgBrightYellow << "bright" << omw::fgYellow << "yellow" << endl;
    cout << omw::fgBrightBlue << "bright" << omw::fgBlue << "blue" << endl;
    cout << omw::fgBrightMagenta << "bright" << omw::fgMagenta << "magenta" << endl;
    cout << omw::fgBrightCyan << "bright" << omw::fgCyan << "cyan" << endl;
    cout << omw::fgBrightWhite << "bright" << omw::fgWhite << "white" << endl;
    cout << omw::normal << omw::bgBrightWhite;
    cout << omw::fgBrightBlack << "bright" << omw::fgBlack << "black" << endl;
    cout << omw::fgBrightRed << "bright" << omw::fgRed << "red" << endl;
    cout << omw::fgBrightGreen << "bright" << omw::fgGreen << "green" << endl;
    cout << omw::fgBrightYellow << "bright" << omw::fgYellow << "yellow" << endl;
    cout << omw::fgBrightBlue << "bright" << omw::fgBlue << "blue" << endl;
    cout << omw::fgBrightMagenta << "bright" << omw::fgMagenta << "magenta" << endl;
    cout << omw::fgBrightCyan << "bright" << omw::fgCyan << "cyan" << endl;
    cout << omw::fgBrightWhite << "bright" << omw::fgWhite << "white" << omw::normal << endl;

    {
        const omw::string colorTableChar = omw::string(omw::UTF8CP_2588) + omw::string(omw::UTF8CP_2588);

        cout << endl;

        for (int i = 0; i <= 7; ++i) cout << omw::foreColor(i) << colorTableChar;

        cout << endl;

        for (int i = 8; i <= 15; ++i) cout << omw::foreColor(i) << colorTableChar;

        cout << "\n\n";

#if 0
        constexpr int startIndexes[12] = { 16, 52, 88, 124, 160, 196, 34, 70, 106, 142, 178, 214 };
        for (int i = 0; i < 12; ++i)
        {
            for (int j = 0; j < 18; ++j) cout << omw::foreColor(startIndexes[i] + j) << colorTableChar;
            cout << endl;
        }
#else
        constexpr int startIndexes[6] = { 16, 52, 88, 124, 160, 196 };
        for (int i = 0; i < 6; ++i)
        {
            for (int j = 0; j < 36; ++j) cout << omw::foreColor(startIndexes[i] + j) << colorTableChar;
            cout << endl;
        }
#endif

        cout << "\n";

        cout << omw::foreColor(16) << colorTableChar;
        for (int i = 232; i <= 255; ++i) cout << omw::foreColor(i) << colorTableChar;
        cout << omw::foreColor(231) << colorTableChar;

        cout << "\n\n";

        constexpr int incStep = 3;
        int barWidth = 0;
        for (int i = 0; i <= 255; i += incStep) { cout << omw::foreColor(i, 0, 0) << omw::UTF8CP_2588; ++barWidth; } cout << endl;
        for (int i = 0; i <= 255; i += incStep) { cout << omw::foreColor(i, i, 0) << omw::UTF8CP_2588; } cout << endl;
        for (int i = 0; i <= 255; i += incStep) { cout << omw::foreColor(0, i, 0) << omw::UTF8CP_2588; } cout << endl;
        for (int i = 0; i <= 255; i += incStep) { cout << omw::foreColor(0, i, i) << omw::UTF8CP_2588; } cout << endl;
        for (int i = 0; i <= 255; i += incStep) { cout << omw::foreColor(0, 0, i) << omw::UTF8CP_2588; } cout << endl;
        for (int i = 0; i <= 255; i += incStep) { cout << omw::foreColor(i, 0, i) << omw::UTF8CP_2588; } cout << endl;
        for (int i = 0; i <= 255; i += incStep) { cout << omw::foreColor(i, i, i) << omw::UTF8CP_2588; } cout << endl;
        for (int i = 0; i < barWidth; ++i) cout << omw::foreColor(intToColor(std::lround((double)0x5FF * (double)i / (double)barWidth))) << omw::UTF8CP_2588;

        cout << omw::normal << endl;
    }

    cout << "\nnormal " << omw::bold << "bold" << omw::normal << " " << omw::underline << "un" << omw::underlineColor(13) << "derli" << omw::defaultUnderlineColor << "ne" <<
        omw::normal << " " << omw::strike << "strike" << omw::normal << " " << omw::italic << "italic" << omw::normal << " " << omw::fraktur << "fraktur" << omw::normal << endl;

    cout << omw::fgBrightCyan << "\nnormal " << omw::reverseVideo << " reversed " << omw::fgDefault << " video " << omw::reverseVideoOff << " normal" << omw::normal << endl;

    {
        cout << "\n";
        cout << omw::font0 << "font 0: The quick brown fox jumps over the lazy dog." << endl;
        cout << omw::font1 << "font 1: The quick brown fox jumps over the lazy dog." << endl;
        cout << omw::font2 << "font 2: The quick brown fox jumps over the lazy dog." << endl;
        cout << omw::font3 << "font 3: The quick brown fox jumps over the lazy dog." << endl;
        cout << omw::font4 << "font 4: The quick brown fox jumps over the lazy dog." << endl;
        cout << omw::font5 << "font 5: The quick brown fox jumps over the lazy dog." << endl;
        cout << omw::font6 << "font 6: The quick brown fox jumps over the lazy dog." << endl;
        cout << omw::font7 << "font 7: The quick brown fox jumps over the lazy dog." << endl;
        cout << omw::font8 << "font 8: The quick brown fox jumps over the lazy dog." << endl;
        cout << omw::font9 << "font 9: The quick brown fox jumps over the lazy dog." << endl;
        cout << omw::normal;
    }

    cout << "\n";
    cout << "the q" << omw::underline << "uick b" << omw::bold << "rown" << sgr::seq(sgr::underlineOff, sgr::boldOff, sgr::fgColorGreen) << " fox jumps" << endl;
    cout << omw::normal;
    cout << "the" << omw::underline << omw::underlineColor(sgr::col8bit_brightMagenta) << " qu" << omw::fgBrightYellow << "ick br" << omw::bgBrightBlack << "own" <<
        omw::underlineColor(sgr::col8bit_standardCyan) << "fox" << omw::defaultColors << " jumps" << endl;
    cout << omw::normal;

    {
        const omw::string colorTableChar = "  ";

        cout << endl;

        for (int i = 0; i <= 7; ++i) cout << omw::backColor(i) << colorTableChar;

        cout << endl;

        for (int i = 8; i <= 15; ++i) cout << omw::backColor(i) << colorTableChar;

        cout << "\n\n";

#if 0
        constexpr int startIndexes[12] = { 16, 52, 88, 124, 160, 196, 34, 70, 106, 142, 178, 214 };
        for (int i = 0; i < 12; ++i)
        {
            for (int j = 0; j < 18; ++j) cout << omw::backColor(startIndexes[i] + j) << colorTableChar;
            cout << endl;
        }
#else
        constexpr int startIndexes[6] = { 16, 52, 88, 124, 160, 196 };
        for (int i = 0; i < 6; ++i)
        {
            for (int j = 0; j < 36; ++j) cout << omw::backColor(startIndexes[i] + j) << colorTableChar;
            cout << endl;
        }
#endif

        cout << "\n";

        cout << omw::backColor(16) << colorTableChar;
        for (int i = 232; i <= 255; ++i) cout << omw::backColor(i) << colorTableChar;
        cout << omw::backColor(231) << colorTableChar;

        cout << "\n\n";

        constexpr int incStep = 3;
        int barWidth = 0;
        for (int i = 0; i <= 255; i += incStep) { cout << omw::backColor(i, 0, 0) << " "; ++barWidth; } cout << endl;
        for (int i = 0; i <= 255; i += incStep) { cout << omw::backColor(i, i, 0) << " "; } cout << endl;
        for (int i = 0; i <= 255; i += incStep) { cout << omw::backColor(0, i, 0) << " "; } cout << endl;
        for (int i = 0; i <= 255; i += incStep) { cout << omw::backColor(0, i, i) << " "; } cout << endl;
        for (int i = 0; i <= 255; i += incStep) { cout << omw::backColor(0, 0, i) << " "; } cout << endl;
        for (int i = 0; i <= 255; i += incStep) { cout << omw::backColor(i, 0, i) << " "; } cout << endl;
        for (int i = 0; i <= 255; i += incStep) { cout << omw::backColor(i, i, i) << " "; } cout << endl;
        for (int i = 0; i < barWidth; ++i) cout << omw::backColor(intToColor(std::lround((double)0x5FF * (double)i / (double)barWidth))) << " ";

        cout << omw::normal << endl;
    }

#pragma endregion sgr





    cout << endl;

#if defined(OMW_DEBUG) && 1
    cout << "===============\nreturn " << r << endl << "press enter..." << endl;
    int ___dbg_getc = getc(stdin);
#endif

    return r;
}
