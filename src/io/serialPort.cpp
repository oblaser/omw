/*
author          Oliver Blaser
date            22.08.2022
copyright       MIT - Copyright (c) 2022 Oliver Blaser
*/

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "omw/defs.h"
#include "omw/io/serialPort.h"
#include "omw/string.h"
#include "omw/version.h"
#include "omw/windows/windows.h"

#if defined(OMW_PLAT_WIN)
#include <Windows.h>
#elif defined(OMW_PLAT_UNIX)
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#endif



namespace
{
#ifdef OMW_PLAT_WIN
    bool isCom0com(const std::string& device)
    {
        const omw::string tmpDevice = (omw::string(device)).toLower_asciiExt();
        const std::vector<omw::string> info = omw::windows::queryDosDevice(device);

        for (size_t i = 0; i < info.size(); ++i)
        {
            const omw::string tmpInfo = info[i].toLower_asciiExt();

            if (tmpInfo.contains("com0com") && !tmpDevice.contains("com0com#port#"))
            {
                return true;
            }
        }

        return false;
    }
#endif // OMW_PLAT_WIN

#if defined(OMW_PLAT_WIN)
#elif defined(OMW_PLAT_UNIX)

    speed_t getUnixBaud(omw::io::SerialPort::baud_t baud, int* error)
    {
        int e = 0;
        speed_t r;

        switch (baud)
        {
        case 0:
            r = B0;
            break;

        case 50:
            r = B50;
            break;

        case 75:
            r = B75;
            break;

        case 110:
            r = B110;
            break;

        case 134:
            r = B134;
            break;

        case 150:
            r = B150;
            break;

        case 200:
            r = B200;
            break;

        case 300:
            r = B300;
            break;

        case 600:
            r = B600;
            break;

        case 1200:
            r = B1200;
            break;

        case 1800:
            r = B1800;
            break;

        case 2400:
            r = B2400;
            break;

        case 4800:
            r = B4800;
            break;

        case 9600:
            r = B9600;
            break;

        case 19200:
            r = B19200;
            break;

        case 38400:
            r = B38400;
            break;

        case 57600:
            r = B57600;
            break;

        case 115200:
            r = B115200;
            break;

        case 230400:
            r = B230400;
            break;

        case 460800:
            r = B460800;
            break;

#if defined(OMW_PLAT_LINUX)
        case 500000:
            r = B500000;
            break;

        case 576000:
            r = B576000;
            break;

        case 921600:
            r = B921600;
            break;

        case 1000000:
            r = B1000000;
            break;

        case 1152000:
            r = B1152000;
            break;

        case 1500000:
            r = B1500000;
            break;

        case 2000000:
            r = B2000000;
            break;

        case 2500000:
            r = B2500000;
            break;

        case 3000000:
            r = B3000000;
            break;

        case 3500000:
            r = B3500000;
            break;

        case 4000000:
            r = B4000000;
            break;
#endif

        default:
            e = 1;
            break;
        };

        if (error) *error = e;

        return r;
    }

#endif
}



omw::io::SerialPort::SerialPort()
    :
#if defined(OMW_PLAT_WIN)
    m_handle(INVALID_HANDLE_VALUE),
#elif defined(OMW_PLAT_UNIX)
    m_fd(-1),
#endif
    //m_port(),
    //m_baud(-1),
    m_isOpen(false),
    m_good(true)
{}

int omw::io::SerialPort::open(const std::string& port, baud_t baud/*, nDataBits, parity, nStopBits*/)
{
    int r = 0;

    if (m_isOpen) r = __LINE__;
    else
    {

#if defined(OMW_PLAT_WIN)

        DCB dcb;
        COMMTIMEOUTS tout;

        m_handle = CreateFileA(
            ("\\\\.\\" + port).c_str(),
            GENERIC_READ | GENERIC_WRITE,
            0,
            NULL,
            OPEN_EXISTING,
            0,
            NULL);

        if (m_handle == INVALID_HANDLE_VALUE) r = __LINE__;
        else
        {
            memset(&dcb, 0, sizeof(dcb));
            dcb.DCBlength = sizeof(dcb);

            // see https://docs.microsoft.com/en-us/windows/win32/api/winbase/ns-winbase-dcb
            dcb.BaudRate = baud;
            dcb.fBinary = TRUE;
            dcb.fParity = FALSE; // parity
            dcb.fOutxCtsFlow = FALSE;
            dcb.fOutxDsrFlow = FALSE;
            dcb.fDtrControl = DTR_CONTROL_ENABLE;
            dcb.fDsrSensitivity = FALSE;
            dcb.fTXContinueOnXoff = TRUE;
            dcb.fOutX = FALSE;
            dcb.fInX = FALSE;
            dcb.fErrorChar = FALSE; // parity
            dcb.fNull = FALSE;
            dcb.fRtsControl = RTS_CONTROL_ENABLE;
            dcb.fAbortOnError = FALSE;
            dcb.XonLim = 0;
            dcb.XoffLim = 1;
            dcb.ByteSize = 8; // nDataBits
            dcb.Parity = NOPARITY; // parity
            dcb.StopBits = ONESTOPBIT; // nStopBits

            if (!SetCommState(m_handle, &dcb)) r = __LINE__;
            else
            {
                tout.ReadIntervalTimeout = MAXDWORD;
                tout.ReadTotalTimeoutMultiplier = 0;
                tout.ReadTotalTimeoutConstant = 0;
                tout.WriteTotalTimeoutMultiplier = 0;
                tout.WriteTotalTimeoutConstant = 0;

                if (!SetCommTimeouts(m_handle, &tout)) r = __LINE__;
            }

            if (r == 0) m_isOpen = true;
            else
            {
                if (!CloseHandle(m_handle)) r += (__LINE__ * 10000);
                else m_handle = INVALID_HANDLE_VALUE;
            }
        }

#elif defined(OMW_PLAT_UNIX)

        m_fd = open(port.c_str(), O_RDWR);

        if (!(m_fd >= 0)) r = __LINE__;
        else
        {
            struct termios tty;
            if (tcgetattr(m_fd, &tty) == 0)
            {
                tty.c_cflag &= ~PARENB; // no parity
                tty.c_cflag &= ~CSTOPB; // clear stop field => one stop bit
                tty.c_cflag &= ~CSIZE;
                tty.c_cflag |= CS8 TODO mask zeros; // 8bit data word
                tty.c_cflag &= ~CRTSCTS; // disable RTS/CTS hardware flow control
                tty.c_cflag |= CREAD | CLOCAL; // turn on READ & ignore ctrl lines (CLOCAL = 1)

                tty.c_lflag &= ~ICANON; // non-canonical mode
                tty.c_lflag &= ~ECHO; // disable echo
                tty.c_lflag &= ~ECHOE; // disable erasure
                tty.c_lflag &= ~ECHONL; // disable new-line echo
                tty.c_lflag &= ~ISIG; // disable interpretation of INTR, QUIT and SUSP

                tty.c_iflag &= ~(IXON | IXOFF | IXANY); // turn off s/w flow ctrl
                tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL); // disable any special handling of received bytes

                tty.c_oflag &= ~OPOST; // prevent special interpretation of output bytes (e.g. newline chars)
                tty.c_oflag &= ~ONLCR; // prevent conversion of newline to carriage return/line feed
                //tty.c_oflag &= ~OXTABS; // prevent conversion of tabs to spaces (NOT PRESENT IN LINUX)
                //tty.c_oflag &= ~ONOEOT; // prevent removal of C-d chars (0x004) in output (NOT PRESENT IN LINUX)

                // non blocking read
                tty.c_cc[VTIME] = 0;
                tty.c_cc[VMIN] = 0;

                int unixBaudErr;
                const speed_t unixBaud = ::getUnixBaud(baud, &unixBaudErr);

                if (unixBaudErr == 0)
                {
                    if (cfsetispeed(&tty, unixBaud) == 0)
                    {
                        if (cfsetospeed(&tty, unixBaud) == 0)
                        {
                            if (tcsetattr(m_fd, TCSANOW, &tty) != 0)
                            {
                                r = __LINE__;
                            }
                            // else nop, set to OK above
                        }
                        else r = __LINE__;
                    }
                    else r = __LINE__;
                }
                else r = __LINE__;
            }
            else r = __LINE__;

            if (r == 0) m_isOpen = true;
            else
            {
                if (close(m_fd) != 0) r += (__LINE__ * 10000);
                else m_fd = -1;
            }
        }

#else
#error "platform not supported"
#endif

    }

    m_good = (r == 0);
    return r;
}

int omw::io::SerialPort::close()
{
    int r = 0;

#if defined(OMW_PLAT_WIN)

    if (!CloseHandle(m_handle)) r = __LINE__;
    else
    {
        m_isOpen = false;
        m_handle = INVALID_HANDLE_VALUE;
    }

#elif defined(OMW_PLAT_UNIX)

    if (close(m_fd) != 0) r = __LINE__;
    else
    {
        m_isOpen = false;
        m_fd = -1;
    }

#else
#error "platform not supported"
#endif

    m_good = (r == 0);
    return r;
}

int omw::io::SerialPort::read(uint8_t* buffer, size_t bufferSize, size_t* nBytesRead)
{
    int r = 0;

#if defined(OMW_PLAT_WIN)

#if defined(OMW_PLAT_WIN64)
    constexpr size_t dword_max = MAXDWORD;
    if (bufferSize > dword_max) r = __LINE__;
#endif

    if (r == 0)
    {
        DWORD dwBufSize = (DWORD)bufferSize;
        DWORD dwNBytesRead = 0;

        if (ReadFile(m_handle, buffer, dwBufSize, &dwNBytesRead, NULL))
        {
            if (nBytesRead) *nBytesRead = dwNBytesRead;
        }
        else r = __LINE__;
    }

#elif defined(OMW_PLAT_UNIX)

    const ssize_t rdres = read(m_fd, buffer, bufferSize);

    if (rdres < 0) r = __LINE__;
    else
    {
        if (nBytesRead) *nBytesRead = (size_t)rdres;
    }

#else
#error "platform not supported"
#endif

    m_good = (r == 0);
    return r;
}

int omw::io::SerialPort::write(const uint8_t* data, size_t count, size_t* nBytesWritten)
{
    int r = 0;

#if defined(OMW_PLAT_WIN)

#if defined(OMW_PLAT_WIN64)
    constexpr size_t dword_max = MAXDWORD;
    if (count > dword_max) r = __LINE__;
#endif

    if (r == 0)
    {
        DWORD dwCount = (DWORD)count;
        DWORD dwNBytesWritten = 0;

        if (WriteFile(m_handle, data, dwCount, &dwNBytesWritten, NULL))
        {
            if (nBytesWritten) *nBytesWritten = dwNBytesWritten;

            if (count != (size_t)dwNBytesWritten) r = __LINE__;
        }
        else r = __LINE__;
    }

#elif defined(OMW_PLAT_UNIX)

    const ssize_t wrres = write(m_fd, data, count);

    if (wrres < 0) r = __LINE__;
    else
    {
        if (nBytesWritten) *nBytesWritten = (size_t)wrres;

        if (count != (size_t)wrres) r = __LINE__;
    }

#else
#error "platform not supported"
#endif

    m_good = (r == 0);
    return r;
}



omw::vector<omw::string> omw::preview::getSerialPortList(bool onlyCOMx)
{
    std::vector<omw::string> serialPorts;

#ifdef OMW_PLAT_WIN
    const std::vector<omw::string> devices = omw::windows::getAllDosDevices();

    for (size_t i = 0; i < devices.size(); ++i)
    {
        bool isC0C = false;

        if (!onlyCOMx) isC0C = ::isCom0com(devices[i]);

        if ((devices[i].compare(0, 3, "COM") == 0) || (!onlyCOMx && isC0C))
        {
            serialPorts.push_back(devices[i]);
        }
    }
#endif // OMW_PLAT_WIN

    return serialPorts;
}

void omw::preview::sortSerialPortList(std::vector<omw::string>& ports)
{
#ifdef OMW_PLAT_WIN

#if /*simple*/ 0
    std::sort(ports.begin(), ports.end());
#else
    const char* const comStr = "COM";
    std::vector<int> comPorts;
    std::vector<omw::string> otherPorts;

    for (size_t i = 0; i < ports.size(); ++i)
    {
        try
        {
            omw::string port = ports[i];

            if (port.compare(0, 3, comStr) == 0)
            {
                const omw::string intStr = port.substr(3);

                if (omw::isUInteger(intStr)) comPorts.push_back(std::stoi(intStr));
                else throw (-1);
            }
            else throw (-1);
        }
        catch (...) { otherPorts.push_back(ports[i]); }
    }

    std::sort(comPorts.begin(), comPorts.end());
    std::sort(otherPorts.begin(), otherPorts.end());

    ports.clear();
    ports.reserve(comPorts.size() + otherPorts.size());

    for (size_t i = 0; i < comPorts.size(); ++i)
    {
        ports.push_back(comStr + std::to_string(comPorts[i]));
    }

    for (size_t i = 0; i < otherPorts.size(); ++i)
    {
        ports.push_back(otherPorts[i]);
    }
#endif

#else // OMW_PLAT_WIN

    std::sort(ports.begin(), ports.end());

#endif // OMW_PLAT_WIN
}

void omw::preview::sortSerialPortList(std::vector<std::string>& ports)
{
    omw::stringVector_t tmpPorts = omw::stringVector(ports);
    omw::preview::sortSerialPortList(tmpPorts);
    ports = omw::stdStringVector(tmpPorts);
}
