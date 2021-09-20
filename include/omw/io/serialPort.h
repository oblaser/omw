/*
author         Oliver Blaser
date           20.09.2021
copyright      MIT - Copyright (c) 2021 Oliver Blaser
*/

#ifndef IG_OMW_IO_SERIALPORT_H
#define IG_OMW_IO_SERIALPORT_H

#include <cstdint>
#include <string>

namespace omw
{
    namespace io
    {
        enum NDATABITS
        {
            NDATABITS_5 = 5,
            NDATABITS_6 = 6,
            NDATABITS_7 = 7,
            NDATABITS_8 = 8
        };

        enum NSTOPBITS
        {
            NSTOPBITS_1 = 1,     // 1
            NSTOPBITS_15 = 100,  // 1.5
            NSTOPBITS_2 = 2      // 2
        };

        enum PARITY
        {
            PARITY_NONE = 0,
            PARITY_ODD,
            PARITY_EVEN
        };

        class SerialPort
        {
        public:
            SerialPort();
            SerialPort(const std::string& port, int32_t baudRate, int32_t dataBits = 8, int32_t stopBits = 1, int32_t parity = omw::io::PARITY_NONE);
            virtual ~SerialPort() {}

            int32_t config(const std::string& port, int32_t baudRate, int32_t dataBits = 8, int32_t stopBits = 1, int32_t parity = omw::io::PARITY_NONE);

            int32_t getBaudRate() const;
            int32_t getDataBits() const;
            int32_t getParity() const;
            std::string getPort() const;
            int32_t getStopBits() const;

            int32_t setBaudRate(int32_t baudRate);
            int32_t setDataBits(int32_t dataBits);
            int32_t setParity(int32_t parity);
            int32_t setPort(const std::string& port);
            int32_t setStopBits(int32_t stopBits);

            int32_t open();
            int32_t close();

            bool isOpen() const;

        private:
            int32_t baudRate;
            int32_t dataBits;
            int32_t parity;
            std::string port;
            int32_t stopBits;
        };
    }
}

#endif // IG_OMW_IO_SERIALPORT_H
