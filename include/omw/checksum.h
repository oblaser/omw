/*
author          Oliver Blaser
date            25.01.2022
copyright       MIT - Copyright (c) 2022 Oliver Blaser
*/

#ifndef IG_OMW_CHECKSUM_H
#define IG_OMW_CHECKSUM_H

#include <cstddef>
#include <cstdint>
#include <vector>

//#define OMWi_CHECKSUM_CRC_PREVIEW (1) // def/undef

namespace omw
{
    /*! \addtogroup grp_checksumLib
    * @{
    */

#ifdef OMWi_CHECKSUM_CRC_PREVIEW
    template <class UI>
    class CrcParameter
    {
    public:
        constexpr CrcParameter(UI init, UI poly, bool refIn, bool refOut, UI xorOut)
            : m_init(init), m_poly(poly), m_refIn(refIn), m_refOut(refOut), m_xorOut(xorOut)
        {}

        constexpr UI init() const { return m_init; }
        constexpr UI poly() const { return m_poly; }
        constexpr bool refIn() const { return m_refIn; }
        constexpr bool refOut() const { return  m_refOut; }
        constexpr UI xorOut() const { return  m_xorOut; }

    private:
        UI m_init;
        UI m_poly;
        bool m_refIn;
        bool m_refOut;
        UI m_xorOut;
    };

    namespace crc16
    {
        constexpr omw::CrcParameter<uint16_t> kermitParam(0x0000, 0x1021, true, true, 0x0000);
        constexpr omw::CrcParameter<uint16_t> modbusParam(0xFFFF, 0x8005, true, true, 0x0000);

        constexpr size_t tableSize = 256;
        extern const uint16_t tableKermit[tableSize];
        extern const uint16_t tableModbus[tableSize];

        uint16_t kermit(const uint8_t* data, size_t count);
        uint16_t kermit(const std::vector<uint8_t>& data, std::vector<uint8_t>::size_type pos = 0, std::vector<uint8_t>::size_type count = -1);

        uint16_t modbus(const uint8_t* data, size_t count);
        uint16_t modbus(const std::vector<uint8_t>& data, std::vector<uint8_t>::size_type pos = 0, std::vector<uint8_t>::size_type count = -1);
    }
#endif // OMWi_CHECKSUM_CRC_PREVIEW

    uint8_t parityWord(const uint8_t* data, size_t count);
    //uint8_t parityWord(const uint8_t* data, size_t count, uint8_t init);
    uint8_t parityWord(const std::vector<uint8_t>& data, std::vector<uint8_t>::size_type pos = 0, std::vector<uint8_t>::size_type count = -1);
    //uint8_t parityWord(const std::vector<uint8_t>& data, std::vector<uint8_t>::size_type pos = 0, std::vector<uint8_t>::size_type count = -1, uint8_t init);

    /*! @} */
}

#endif // IG_OMW_CHECKSUM_H
