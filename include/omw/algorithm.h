/*
author          Oliver Blaser
date            06.12.2021
copyright       MIT - Copyright (c) 2021 Oliver Blaser
*/

#ifndef IG_OMW_ALGORITHM_H
#define IG_OMW_ALGORITHM_H

#include <vector>

#include "../omw/defs.h"

namespace omw
{
    /*! \addtogroup grp_algorithm
    * @{
    */


    //! \name Double Dabble
    /// @{
    std::vector<uint8_t> doubleDabble128(const uint8_t* data, size_t count = 16);
    std::vector<uint8_t> doubleDabble128(const uint16_t* data, size_t count = 8);
    std::vector<uint8_t> doubleDabble128(const uint32_t* data, size_t count = 4);
    std::vector<uint8_t> doubleDabble128(const uint64_t* data, size_t count = 2);
    std::vector<uint8_t> doubleDabble128(uint32_t valueH, uint32_t valueHM, uint32_t valueLM, uint32_t valueL);
    std::vector<uint8_t> doubleDabble128(uint64_t valueH, uint64_t valueL);
    /// @}


    // grp_algorithm
    /*! @} */
}

#endif // IG_OMW_ALGORITHM_H
