/*
author          Oliver Blaser
date            28.01.2022
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
    const char* const binFilename = "bin-if.omwsystestfile-bin";
    const char* const txtFilename = "txt-if.omwsystestfile-txt";

    int readBin(std::vector<uint8_t>& buffer)
    {
        const BinFileInterface file(binFilename);
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
        BinFileInterface file(binFilename);
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
        const TxtFileInterface file(txtFilename);
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
        TxtFileInterface file(txtFilename);
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

    int readBin_null(std::vector<uint8_t>& buffer)
    {
        const BinFileInterface file(binFilename);
        int r;

        try
        {
            file.open(BinFileInterface::rd);
            const size_t sz = 0; // file.size();
            buffer.resize(sz);
            file.read(buffer.data(), sz);
            buffer.shrink_to_fit();
            r = 0;
        }
        catch (const std::exception& ex)
        {
            r = 1;
            cout << "readBin_null(): " << ex.what() << endl;
        }

        try { file.close(); }
        catch (...) { if (!r) r = 2; }

        return r;
    }
    int readTxt_null(std::string& buffer)
    {
        const TxtFileInterface file(txtFilename);
        int r;

        try
        {
            file.open(TxtFileInterface::rd);
            const size_t sz = 0;
            char p[10] = "abcd";
            file.read(p, sz);
            p[sz] = 0;
            buffer = std::string(p);
            r = 0;
        }
        catch (const std::exception& ex)
        {
            r = 1;
            cout << "readTxt_null(): " << ex.what() << endl;
        }

        try { file.close(); }
        catch (...) { if (!r) r = 2; }

        return r;
    }
}



int main()
{
    std::vector<bool> check(1, true);
    int r;

    std::srand((unsigned int)std::time(nullptr));

    const std::vector<uint8_t> wrData = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, (uint8_t)std::rand(), (uint8_t)std::rand(), (uint8_t)std::rand(), (uint8_t)std::rand() };
    const std::string wrStr = "test string\nrandom number: " + std::to_string(std::rand()) + "\n";
    std::vector<uint8_t> rdData;
    std::string rdStr;



    r = readBin_null(rdData);
    if (r)
    {
        check.push_back(false);
        cout << "read count null data error: " << r << endl;
    }
    if (rdData.size() != 0)
    {
        check.push_back(false);
        cout << "read count null data error: data size != 0" << endl;
    }

    r = readTxt_null(rdStr);
    if (r)
    {
        check.push_back(false);
        cout << "read count null text error: " << r << endl;
    }
    if (rdStr.length() != 0)
    {
        check.push_back(false);
        cout << "read count null text error: string len != 0" << endl;
    }



    r = writeBin(wrData);
    if (r)
    {
        check.push_back(false);
        cout << "write data error: " << r << endl;
    }

    r = writeTxt(wrStr);
    if (r)
    {
        check.push_back(false);
        cout << "write text error: " << r << endl;
    }



    r = readBin(rdData);
    if (r)
    {
        check.push_back(false);
        cout << "read data error: " << r << endl;
    }

    r = readTxt(rdStr);
    if (r)
    {
        check.push_back(false);
        cout << "read text error: " << r << endl;
    }



    const bool dataResult = (wrData == rdData);
    const bool textResult = (wrStr == rdStr);

    if (!dataResult) cout << "wrData == rdData  failed" << endl;
    if (!textResult) cout << "wrStr == rdStr    failed" << endl;

    check.push_back(dataResult);
    check.push_back(textResult);



    const std::vector<bool> checkCmp(check.size(), true);
    r = (checkCmp == check ? 0 : 1);

    cout << "================================\n";
    cout << "File I/O System Test " << (r ? "FAILED" : "Passed") << endl;

#if defined(OMW_DEBUG) && 1
    cout << "===============\nreturn " << r << endl << "press enter..." << endl;
    int dbg___getc = getc(stdin);
#endif

    return r;
}
