/*
author          Oliver Blaser
date            22.08.2022
copyright       MIT - Copyright (c) 2022 Oliver Blaser
*/

#ifndef IG_OMW_IO_SERIALPORT_H
#define IG_OMW_IO_SERIALPORT_H

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "../../omw/defs.h"
#include "../../omw/string.h"
#include "../../omw/vector.h"

namespace omw
{
    namespace io
    {
        /*! \addtogroup grp_ioLib
        * @{
        */

        class SerialPort
        {
        public:
            using baud_t = uint32_t;

        public:
            SerialPort();
            virtual ~SerialPort();

            int open(const std::string& port, baud_t baud/*, nDataBits, parity, nStopBits*/, const void* DCB_customDcb = nullptr);
            int close();

            int read(uint8_t* buffer, size_t bufferSize, size_t* nBytesRead);
            int read(char* buffer, size_t bufferSize, size_t* nBytesRead) { return read(reinterpret_cast<uint8_t*>(buffer), bufferSize, nBytesRead); }
            int readByte(uint8_t* byte, size_t* nBytesRead) { return read(byte, 1, nBytesRead); }
            int write(const uint8_t* data, size_t count, size_t* nBytesWritten = nullptr);
            int write(const char* data, size_t count, size_t* nBytesWritten = nullptr) { return write(reinterpret_cast<const uint8_t*>(data), count, nBytesWritten); }

            bool isOpen() const { return m_isOpen; }
            bool good() const { return m_good; }

        private:
            //std::string m_port;
            //baud_t m_baud;
            // m_nDataBits
            // m_parity;
            // m_nStopBits;

            bool m_isOpen;
            bool m_good;

        private: // platform specific
#if defined(OMW_PLAT_WIN)
            void* m_handle;
#elif defined(OMW_PLAT_UNIX)
            int m_fd;
#endif
            void* m_implementation;
        };

        /*! @} */
    }

    namespace preview
    {
        /*! \addtogroup grp_ioLib
        * @{
        */
        omw::vector<omw::string> getSerialPortList(bool onlyCOMx = true);
        void sortSerialPortList(std::vector<omw::string>& ports);
        void sortSerialPortList(std::vector<std::string>& ports);
        /*! @} */
    }
}

#endif // IG_OMW_IO_SERIALPORT_H
