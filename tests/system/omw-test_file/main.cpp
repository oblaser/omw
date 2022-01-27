/*
author          Oliver Blaser
date            27.01.2022
copyright       MIT - Copyright (c) 2022 Oliver Blaser
*/

#include <cstdlib>
#include <ctime>
#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include <omw/io/file.h>
#include <omw/string.h>


using std::cout;
using std::endl;
using omw::io::BinFileInterface;
using omw::io::TxtFileInterface;

namespace
{
    int readBin(std::vector<uint8_t>& buffer)
    {
        const BinFileInterface file("bin-interface.omwsystestfile-bin");
        int r;

        try
        {
            file.open(BinFileInterface::rd);
            const size_t sz = file.size();
            buffer.resize(sz);
            file.read(buffer.data(), sz);
            buffer.shrink_to_fit();
            r = 0;
        }
        catch (const std::exception& ex)
        {
            r = 1;
            cout << "readBin(): " << ex.what() << endl;
        }

        try { file.close(); }
        catch (...) { if (!r) r = 2; }

        return r;
    }
    int writeBin(const std::vector<uint8_t>& data)
    {
        BinFileInterface file("bin-interface.omwsystestfile-bin");
        int r;

        try
        {
            file.open(BinFileInterface::wr);
            file.write(data.data(), data.size());
            r = 0;
        }
        catch (const std::exception& ex)
        {
            r = 1;
            cout << "writeBin(): " << ex.what() << endl;
        }

        try { file.close(); }
        catch (...) { if (!r) r = 2; }

        return r;
    }

    int readTxt(std::string& buffer)
    {
        TxtFileInterface file("txt-interface.omwsystestfile-txt");
        int r;

        char* p = nullptr;

        try
        {
            file.open(TxtFileInterface::rd);
            const size_t sz = file.size();
            p = new char[sz + 1];
            file.read(p, sz);
            p[sz] = 0;
            buffer = std::string(p);
            r = 0;
        }
        catch (const std::exception& ex)
        {
            r = 1;
            cout << "readBin(): " << ex.what() << endl;
        }

        delete[] p;
        p = nullptr;

        try { file.close(); }
        catch (...) { if (!r) r = 2; }

        return r;
    }
    int writeTxt(const std::string& str)
    {
        TxtFileInterface file("txt-interface.omwsystestfile-txt");
        int r;

        try
        {
            file.open(TxtFileInterface::wr);
            file.write(str.c_str());
            r = 0;
        }
        catch (const std::exception& ex)
        {
            r = 1;
            cout << "writeTxt(): " << ex.what() << endl;
        }

        try { file.close(); }
        catch (...) { if (!r) r = 2; }

        return r;
    }
}



int main()
{
    int r;

    std::srand((unsigned int)std::time(nullptr));

    const std::vector<uint8_t> wrData = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, (uint8_t)std::rand(), (uint8_t)std::rand(), (uint8_t)std::rand(), (uint8_t)std::rand() };
    const std::string wrStr = "test string\nrandom number: " + std::to_string(std::rand()) + "\n";
    std::vector<uint8_t> rdData;
    std::string rdStr;



    r = writeBin(wrData);
    if (r) cout << "write data error: " << r << endl;

    r = writeTxt(wrStr);
    if (r) cout << "write text error: " << r << endl;



    r = readBin(rdData);
    if (r) cout << "read data error: " << r << endl;

    r = readTxt(rdStr);
    if (r) cout << "read text error: " << r << endl;



    const bool dataResult = (wrData == rdData);
    const bool textResult = (wrStr == rdStr);

    cout << "wrData == rdData  " << (dataResult ? "OK" : "failed") << endl;
    cout << "wrStr == rdStr    " << (textResult ? "OK" : "failed") << endl;



    r = (dataResult && textResult ? 0 : 1);

#if defined(OMW_DEBUG) && 1
    cout << "===============\nreturn " << r << endl << "press enter..." << endl;
    int dbg___getc = getc(stdin);
#endif

    return r;
}
