/*
author          Oliver Blaser
date            08.12.2021
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

#ifdef OMW_PLAT_WIN
#define TESTING_WIN_CODE_PAGE_CHANGES (0) // set accordingly 0/1
#else
#define TESTING_WIN_CODE_PAGE_CHANGES (0)
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

#ifdef OMW_PLAT_WIN
    void setCpBack(uint32_t cpIn, uint32_t cpOut)
    {
        if (!omw::windows::consoleSetInCodePage(cpIn)) cout << "faild to set in code page back to " << cpIn << endl;
        if (!omw::windows::consoleSetOutCodePage(cpOut)) cout << "faild to set out code page back to " << cpOut << endl;
    }
#endif
}



#if !TESTING_WIN_CODE_PAGE_CHANGES

int main(int argc, char** argv)
{
    int r = 0;

#ifdef OMW_PLAT_WIN
    const uint32_t cpIn = omw::windows::consoleGetInCodePage();
    const uint32_t cpOut = omw::windows::consoleGetOutCodePage();

    if (!omw::windows::consoleSetCodePageUTF8())
    {
        cout << "faild to set code page to UTF-8" << endl;
        setCpBack(cpIn, cpOut);
    }

    if (!omw::windows::consoleEnVirtualTermProc()) cout << "faild to enable VT100" << endl;
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
    cout << omw::fgBrightWhite << "bright" << omw::fgWhite << "white" << omw::normal << endl;
    cout << omw::bgBrightWhite;
    cout << omw::fgBrightBlack << "bright" << omw::fgBlack << "black" << endl;
    cout << omw::fgBrightRed << "bright" << omw::fgRed << "red" << endl;
    cout << omw::fgBrightGreen << "bright" << omw::fgGreen << "green" << endl;
    cout << omw::fgBrightYellow << "bright" << omw::fgYellow << "yellow" << endl;
    cout << omw::fgBrightBlue << "bright" << omw::fgBlue << "blue" << endl;
    cout << omw::fgBrightMagenta << "bright" << omw::fgMagenta << "magenta" << endl;
    cout << omw::fgBrightCyan << "bright" << omw::fgCyan << "cyan" << endl;
    cout << omw::fgBrightWhite << "bright" << omw::fgWhite << "white" << omw::normal << endl;

    {
        cout << "\n";
        std::wcout << omw::backColor(0b100) << omw::fgBrightWhite << "SGR and char string to std::" << omw::bold << "w" << omw::boldOff << "cout" << omw::normal << endl;
        std::wcout << omw::backColor(0b101) << omw::fgBrightYellow << L"SGR and wchar_t string to std::" << omw::bold << "w" << omw::boldOff << "cout" << omw::normal << endl;
    }

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
        cout << omw::font9 << "font 9: The quick brown fox jumps over the lazy dog." << omw::normal << endl;
    }

    cout << "\n";
    cout << "the q" << omw::underline << "uick b" << omw::bold << "rown" << sgr::seq(sgr::underlineOff, sgr::boldOff, sgr::fgColorGreen) << " fox jumps" << omw::normal << endl;
    cout << "the" << omw::underline << omw::underlineColor(sgr::col8bit_brightMagenta) << " qu" << omw::fgBrightYellow << "ick br" << omw::bgBrightBlack << "own" <<
        omw::underlineColor(sgr::col8bit_standardCyan) << "fox" << omw::defaultColors << " jumps" << omw::normal << endl;

    {
        const omw::string colorTableChar = "  ";

        cout << endl;

        for (int i = 0; i <= 7; ++i) cout << omw::backColor(i) << colorTableChar;

        cout << omw::normal << endl;

        for (int i = 8; i <= 15; ++i) cout << omw::backColor(i) << colorTableChar;

        cout << omw::normal << "\n\n";

#if 0
        constexpr int startIndexes[12] = { 16, 52, 88, 124, 160, 196, 34, 70, 106, 142, 178, 214 };
        for (int i = 0; i < 12; ++i)
        {
            for (int j = 0; j < 18; ++j) cout << omw::backColor(startIndexes[i] + j) << colorTableChar;
            cout << omw::normal << endl;
        }
#else
        constexpr int startIndexes[6] = { 16, 52, 88, 124, 160, 196 };
        for (int i = 0; i < 6; ++i)
        {
            for (int j = 0; j < 36; ++j) cout << omw::backColor(startIndexes[i] + j) << colorTableChar;
            cout << omw::normal << endl;
        }
#endif

        cout << omw::normal << "\n";

        cout << omw::backColor(16) << colorTableChar;
        for (int i = 232; i <= 255; ++i) cout << omw::backColor(i) << colorTableChar;
        cout << omw::backColor(231) << colorTableChar;

        cout << omw::normal << "\n\n";

        constexpr int incStep = 3;
        int barWidth = 0;
        for (int i = 0; i <= 255; i += incStep) { cout << omw::backColor(i, 0, 0) << " "; ++barWidth; } cout << omw::normal << endl;
        for (int i = 0; i <= 255; i += incStep) { cout << omw::backColor(i, i, 0) << " "; } cout << omw::normal << endl;
        for (int i = 0; i <= 255; i += incStep) { cout << omw::backColor(0, i, 0) << " "; } cout << omw::normal << endl;
        for (int i = 0; i <= 255; i += incStep) { cout << omw::backColor(0, i, i) << " "; } cout << omw::normal << endl;
        for (int i = 0; i <= 255; i += incStep) { cout << omw::backColor(0, 0, i) << " "; } cout << omw::normal << endl;
        for (int i = 0; i <= 255; i += incStep) { cout << omw::backColor(i, 0, i) << " "; } cout << omw::normal << endl;
        for (int i = 0; i <= 255; i += incStep) { cout << omw::backColor(i, i, i) << " "; } cout << omw::normal << endl;
        for (int i = 0; i < barWidth; ++i) cout << omw::backColor(intToColor(std::lround((double)0x5FF * (double)i / (double)barWidth))) << " ";

        cout << omw::normal << endl;
    }

#pragma endregion sgr





    cout << endl;

#ifdef OMW_PLAT_WIN
    setCpBack(cpIn, cpOut);
#endif

#if defined(OMW_DEBUG) && 1
    cout << "===============\nreturn " << r << endl << "press enter..." << endl;
    int ___dbg_getc = getc(stdin);
#endif

    return r;
}

#else // !TESTING_WIN_CODE_PAGE_CHANGES

const char* const testStringChp = "\xCE\xB1\xCE\xB2\xCE\xB3\xCE\xB4\xCE\xB5\xCE\xB6\xCE\xB7\xCE\xB8\xCE\xB9\xCE\xBA\xCE\xBB\xCE\xBC\xCE\xBD\xCE\xBE\xCE\xBF\xCF\x80\xCF\x81\xCF\x82\xCF\x83\xCF\x8\xCF\x85\xCF\x86\xCF\x87\xCF\x88\xCF\x89";
const std::string testStringStd = "\xCE\xB1\xCE\xB2\xCE\xB3\xCE\xB4\xCE\xB5\xCE\xB6\xCE\xB7\xCE\xB8\xCE\xB9\xCE\xBA\xCE\xBB\xCE\xBC\xCE\xBD\xCE\xBE\xCE\xBF\xCF\x80\xCF\x81\xCF\x82\xCF\x83\xCF\x8\xCF\x85\xCF\x86\xCF\x87\xCF\x88\xCF\x89";
const omw::string testStringOmw = "\xCE\xB1\xCE\xB2\xCE\xB3\xCE\xB4\xCE\xB5\xCE\xB6\xCE\xB7\xCE\xB8\xCE\xB9\xCE\xBA\xCE\xBB\xCE\xBC\xCE\xBD\xCE\xBE\xCE\xBF\xCF\x80\xCF\x81\xCF\x82\xCF\x83\xCF\x8\xCF\x85\xCF\x86\xCF\x87\xCF\x88\xCF\x89";
const omw::string testStringComposed = "composed string " + omw::string(omw::UTF8CP_2580) + omw::UTF8CP_2584 + std::string(omw::UTF8CP_2588) + " " +
omw::string(omw::UTF8CP_auml) + omw::UTF8CP_ouml + omw::string(omw::UTF8CP_uuml) + omw::UTF8CP_Auml + omw::string(omw::UTF8CP_Ouml) + omw::UTF8CP_Uuml;

static void normal();
static void utf8(uint32_t, uint32_t);


int main(int argc, char** argv)
{
    int r = 0;

    const char* const invArg = "invalid arguments";

    const uint32_t cpIn = omw::windows::consoleGetInCodePage();
    const uint32_t cpOut = omw::windows::consoleGetOutCodePage();

    cout << "in code page:  " << cpIn << endl;
    cout << "out code page: " << cpOut << endl;

    if (argc == 1) normal();
    else if (argc == 2)
    {
        if (omw::string(argv[1]) == "-u8") utf8(cpIn, cpOut);
        else { cout << invArg << endl; r = -1; }
    }
    else { cout << invArg << endl; r = -1; }

    return r;
}


void normal()
{
    cout << testStringChp << endl;
    cout << testStringStd << endl;
    cout << testStringOmw << endl;
}

void utf8(uint32_t cpIn, uint32_t cpOut)
{
    if (!omw::windows::consoleSetCodePageUTF8()) cout << "faild to set code page to UTF-8" << endl;

    normal();

#if 1 // set to 0 only for R&D
    setCpBack(cpIn, cpOut);
#endif
}

#endif // !TESTING_WIN_CODE_PAGE_CHANGES
