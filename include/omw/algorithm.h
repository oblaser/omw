/*
author          Oliver Blaser
date            13.12.2021
copyright       MIT - Copyright (c) 2021 Oliver Blaser
*/

#ifndef IG_OMW_ALGORITHM_H
#define IG_OMW_ALGORITHM_H

#include <cstdint>
#include <vector>

#include "../omw/int.h"

namespace omw
{
    /*! \addtogroup grp_algorithm
    * @{
    */

    //! \name Double Dabble
    /// @{
    std::vector<uint8_t> doubleDabble128(const uint8_t* data, size_t count);
    std::vector<uint8_t> doubleDabble128(uint32_t valueHH, uint32_t valueLH, uint32_t valueHL, uint32_t valueLL);
    std::vector<uint8_t> doubleDabble128(uint64_t valueH, uint64_t valueL);

    std::vector<uint8_t> doubleDabble(const omw::uint128_t& value);
    /// @}


    /*! @} */
}

#endif // IG_OMW_ALGORITHM_H
