/*
author          Oliver Blaser
date            23.01.2022
copyright       MIT - Copyright (c) 2022 Oliver Blaser
*/

#ifndef IG_OMW_CHECKSUM_H
#define IG_OMW_CHECKSUM_H

#include <cstddef>
#include <cstdint>
#include <vector>

namespace omw
{
    /*! \addtogroup grp_checksumLib
    * @{
    */

    namespace crc16
    {
        uint16_t kermit(const uint8_t* data, size_t count);
        uint16_t kermit(const std::vector<uint8_t>& data, std::vector<uint8_t>::size_type pos = 0, std::vector<uint8_t>::size_type count = -1);

        uint16_t modbus(const uint8_t* data, size_t count);
        uint16_t modbus(const std::vector<uint8_t>& data, std::vector<uint8_t>::size_type pos = 0, std::vector<uint8_t>::size_type count = -1);
    }

    /*! @} */
}

#endif // IG_OMW_CHECKSUM_H
