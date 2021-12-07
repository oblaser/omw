/*
author          Oliver Blaser
date            07.12.2021
copyright       MIT - Copyright (c) 2021 Oliver Blaser
*/

#include <iostream>
#include <string>

#include <omw/cli.h>
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

    const omw::string block = omw::string(omw::UTF8CP_2588) + omw::string(omw::UTF8CP_2588);
    cout << "\n" << omw::fgBrightRed << block << omw::fgBrightYellow << block << omw::fgBrightGreen << block <<
        omw::fgBrightCyan << block << omw::fgBrightBlue << block << omw::fgBrightMagenta << block << omw::fgBrightRed << block <<
        " " << omw::fgBlack << block << omw::fgBrightBlack << block << omw::fgWhite << block << omw::fgBrightWhite << block << endl;

    cout << omw::normal;
#pragma endregion sgr





    cout << endl;

#if defined(OMW_DEBUG) && 1
    cout << "===============\nreturn " << r << endl << "press enter..." << endl;
    int ___dbg_getc = getc(stdin);
#endif

    return r;
}
