/*
author          Oliver Blaser
date            19.01.2023
copyright       MIT - Copyright (c) 2023 Oliver Blaser
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
            using baud_type = uint32_t;

        public:
            SerialPort();
            virtual ~SerialPort() {}

            int open(const std::string& port, baud_type baud/*, nDataBits, parity, nStopBits*/);
#if defined(OMW_PLAT_WIN)
            int open(const std::string& port, void* DCB_customDcb, const void* COMMTIMEOUTS_customTmo = nullptr);
#elif defined(OMW_PLAT_UNIX)
#endif
            int close();

            int read(uint8_t* buffer, size_t bufferSize, size_t* nBytesRead);
            int read(char* buffer, size_t bufferSize, size_t* nBytesRead) { return read(reinterpret_cast<uint8_t*>(buffer), bufferSize, nBytesRead); }
            int readByte(uint8_t* byte, size_t* nBytesRead) { return read(byte, 1, nBytesRead); }
            int write(const uint8_t* data, size_t count, size_t* nBytesWritten = nullptr);
            int write(const char* data, size_t count, size_t* nBytesWritten = nullptr) { return write(reinterpret_cast<const uint8_t*>(data), count, nBytesWritten); }

            bool isOpen() const { return m_isOpen; }
            bool good() const { return m_good; }

#if defined(OMW_PLAT_WIN)
            static void initDcb(void* DCB_customDcb, baud_type baud);
#elif defined(OMW_PLAT_UNIX)
#endif

        private:
            //std::string m_port;
            //baud_type m_baud;
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
