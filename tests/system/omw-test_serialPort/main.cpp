/*
author          Oliver Blaser
date            19.01.2023
copyright       MIT - Copyright(c) 2023 Oliver Blaser
*/

#include <array>
#include <cstdlib>
#include <cstdint>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

#include <omw/defs.h>
#include <omw/io/serialPort.h>
#include <omw/string.h>
#include <omw/utility.h>

#ifdef OMW_PLAT_WIN
#include <Windows.h>
#endif


using std::cout;
using std::endl;

namespace
{
    void appendChecksum(std::vector<uint8_t>& data)
    {
        uint8_t cs = 0;
        for (size_t i = 0; i < data.size(); ++i) cs ^= data[i];
        data.push_back(cs);
    }

    int write(omw::io::SerialPort& port, std::vector<uint8_t> data)
    {
        appendChecksum(data);
        int r = port.write(data.data(), 3 + data.at(2));
        cout << "write \"" << omw::toHexStr(data) << "\": " << r << endl;
        return r;
    }
}



int main(int argc, char** argv)
{
    int r = 0;

    cout << "omw serial port system test" << endl;
    cout << "using /tools/arduinoSerial" << endl;

    std::string portName;
#if defined(OMW_DEBUG)
    portName = "COM7";
#else
    if (argc >= 2) portName = argv[1];
    else
    {
        cout << "please specify port:" << endl;
        cout << "  " << argv[0] << " PORT" << endl;
        return (-1);
    }
#endif

    omw::io::SerialPort port;

    constexpr omw::io::SerialPort::baud_type baud = 19200;
#ifdef OMW_PLAT_WIN
    DCB dcb;
    omw::io::SerialPort::initDcb(&dcb, baud);

    // DTR to disable, so that Arduino does not get reset after a connect.
    // https://electronics.stackexchange.com/a/61257
    // https://electronics.stackexchange.com/a/24747
    
    dcb.fDtrControl = DTR_CONTROL_DISABLE;

    r = port.open(portName, &dcb);
    //r = port.open(portName, baud);

    Sleep(100);
#else
    r = port.open(portName, baud);
    usleep(100 * 1000);
#endif
    cout << "open \"" << portName << "\": " << r << endl;

    r = write(port, { 0x04, 0x01, 50 }); // enable periodic counter report

    time_t tNow, tOld;
    bool state = false;
    constexpr size_t rxBufferSize = 20;
    std::array<uint8_t, rxBufferSize> rxBuffer;
    size_t rxIndex = 0;

    tOld = time(nullptr);
    while (r == 0)
    {
        tNow = time(nullptr);

        if ((tNow - tOld) >= 2)
        {
            tOld = tNow;

            omw::toggle(state);
            const auto x = uint8_t(state);
            r = write(port, { 0x01, 0x01, x });
        }
        
        if (r == 0)
        {
            size_t nBytesRead = 0;
            uint8_t rxByte;
            r = port.readByte(&rxByte, &nBytesRead);
            if (r == 0)
            {
                if (nBytesRead) // if received a byte
                {
                    rxBuffer[rxIndex] = rxByte;
                    ++rxIndex;
                }
            }
            else cout << "readByte failed: " << r << endl;
        }

        if ((rxIndex == (rxBuffer[2] + 4)) && (rxIndex > 2))
        {
            cout << "received: \"";

            for (size_t i = 0; i < rxIndex; ++i)
            {
                if (i > 0) cout << " ";
                cout << omw::toHexStr(rxBuffer[i]);
            }

            cout << "\"" << endl;

            rxIndex = 0;
        }
    }

#if defined(OMW_DEBUG)
    cout << "===============\nreturn: " << r << "\npress enter..." << endl;
    int dbg___getc_ = getc(stdin);
#endif

    return r;
}
