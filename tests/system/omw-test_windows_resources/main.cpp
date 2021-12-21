/*
author          Oliver Blaser
date            13.08.2021
copyright       MIT - Copyright (c) 2021 Oliver Blaser
*/

#include <cstdio>
#include <iostream>
#include <string>

#include "resources/resources.h"

#include <omw/windows/resources.h>
#include <omw/windows/string.h>
#include <Windows.h>


using std::cout;
using std::endl;



int main()
{
    {
        cout << "  --===# begin myTextFile (plain) #===--" << endl;
        cout << omw::windows::getTextResource(IDR_MYTEXTFILE) << endl;
        cout << "  --===# end myTextFile (plain) #===--" << endl;
    }

    cout << endl;

    {
        cout << "  --===# begin myTextFile (converted) #===--" << endl;

        try
        {
            const auto resData = omw::windows::getTextResource(IDR_MYTEXTFILE);
            const std::string resStr(resData.begin() + 3, resData.end());

            constexpr size_t tmpStrLen = 255;
            WCHAR wStr[tmpStrLen];

            omw::windows::utf8_to_wstr(resStr, wStr, tmpStrLen);

            std::wcout << wStr << endl; // you may have to look to `wStr` in the debugger or change the consoles charset to see the correct non-ASCII chars.
        }
        catch (std::exception& ex) { cout << "failed: " << ex.what() << endl; }
        catch (...) { cout << "failed!" << endl; }

        cout << "  --===# end myTextFile (converted) #===--" << endl;
    }

    cout << endl;

    {
        cout << "  --===# begin myBinaryFile #===--" << endl;

        const auto data = omw::windows::getBinaryResource(IDR_MYBINARYFILE);

        for (size_t i = 0; i < data.size(); ++i)
        {
            if (i > 0) cout << " ";
            cout << std::to_string(data[i]);
        }
        cout << endl;

        for (size_t i = 0; i < (data.size() - 1); ++i)
        {
            if (i > 0) cout << " ";
            cout << std::to_string((double)data[i + 1] / data[i]);
        }
        cout << endl;

        cout << "  --===# end myBinaryFile #===--" << endl;
    }

    cout << endl;

    {
        cout << "  --===# begin invalid resource #===--" << endl;
        try { cout << omw::windows::getTextResource(2000) << endl; }
        catch (std::exception& ex) { cout << ex.what() << endl; }
        cout << "  --===# end invalid resource #===--" << endl;
    }

    cout << endl;

    cout << "press enter to exit..." << endl;
    int garbage = getchar();

    return 0;
}
