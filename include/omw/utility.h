/*
author          Oliver Blaser
date            17.12.2023
copyright       MIT - Copyright (c) 2023 Oliver Blaser
*/

#ifndef IG_OMW_UTILITY_H
#define IG_OMW_UTILITY_H

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>



/*! \addtogroup grp_utility_langSupport
* @{
*/

#define OMW_SIZEOF_ARRAY(_array) (sizeof(_array) / sizeof(_array[0]))

#ifndef SIZEOF_ARRAY
#define SIZEOF_ARRAY(_array) OMW_SIZEOF_ARRAY(_array)
#endif

// grp_utility_langSupport
/*! @} */



namespace omw
{
    /*! \addtogroup grp_utility_langSupport
    * @{
    */

    void shiftLeftAssign(int8_t& value, unsigned int n);
    void shiftLeftAssign(int16_t& value, unsigned int n);
    void shiftLeftAssign(int32_t& value, unsigned int n); /*!< See \ref grp_utility_langSupport_section_bitShiftOp in \ref grp_utility_langSupport. */
    void shiftLeftAssign(int64_t& value, unsigned int n);
    void shiftLeftAssign(uint8_t& value, unsigned int n);
    void shiftLeftAssign(uint16_t& value, unsigned int n);
    void shiftLeftAssign(uint32_t& value, unsigned int n);
    void shiftLeftAssign(uint64_t& value, unsigned int n);
    void shiftRightAssign(int8_t& value, unsigned int n);
    void shiftRightAssign(int16_t& value, unsigned int n);
    void shiftRightAssign(int32_t& value, unsigned int n); /*!< See \ref grp_utility_langSupport_section_bitShiftOp in \ref grp_utility_langSupport. */
    void shiftRightAssign(int64_t& value, unsigned int n);
    void shiftRightAssign(uint8_t& value, unsigned int n);
    void shiftRightAssign(uint16_t& value, unsigned int n);
    void shiftRightAssign(uint32_t& value, unsigned int n);
    void shiftRightAssign(uint64_t& value, unsigned int n);
    int8_t shiftLeft(int8_t value, unsigned int n);
    int16_t shiftLeft(int16_t value, unsigned int n);
    int32_t shiftLeft(int32_t value, unsigned int n); /*!< See \ref grp_utility_langSupport_section_bitShiftOp in \ref grp_utility_langSupport. */
    int64_t shiftLeft(int64_t value, unsigned int n);
    uint8_t shiftLeft(uint8_t value, unsigned int n);
    uint16_t shiftLeft(uint16_t value, unsigned int n);
    uint32_t shiftLeft(uint32_t value, unsigned int n);
    uint64_t shiftLeft(uint64_t value, unsigned int n);
    int8_t shiftRight(int8_t value, unsigned int n);
    int16_t shiftRight(int16_t value, unsigned int n);
    int32_t shiftRight(int32_t value, unsigned int n); /*!< See \ref grp_utility_langSupport_section_bitShiftOp in \ref grp_utility_langSupport. */
    int64_t shiftRight(int64_t value, unsigned int n);
    uint8_t shiftRight(uint8_t value, unsigned int n);
    uint16_t shiftRight(uint16_t value, unsigned int n);
    uint32_t shiftRight(uint32_t value, unsigned int n);
    uint64_t shiftRight(uint64_t value, unsigned int n);

    // grp_utility_langSupport
    /*! @} */



    /*! \addtogroup grp_utility_gpUtil
    * @{
    */

    static inline void toggle(bool& value) { value = !value; }
    static inline void toggle(int& value) { value = (value ? 0 : 1); }

    // grp_utility_gpUtil
    /*! @} */
}

#endif // IG_OMW_UTILITY_H
