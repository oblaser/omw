/*
author          Oliver Blaser
date            28.01.2022
copyright       MIT - Copyright (c) 2022 Oliver Blaser
*/

/* !
* \file
* \brief Integer Definitions.
*
* See also \ref grp_utility_langSupport_typeSupport.
*/

#ifndef IG_OMW_INTDEF_H
#define IG_OMW_INTDEF_H

#include <cstddef>
#include <cstdint>



/*! \addtogroup grp_utility_langSupport_typeSupport
* @{
*/

#define OMW_8BIT_LSB (0x01)
#define OMW_8BIT_MSB (0x80)
#define OMW_8BIT_ALL (0xFF)

#define OMW_16BIT_LSB (0x0001)
#define OMW_16BIT_MSB (0x8000)
#define OMW_16BIT_ALL (0xFFFF)

#define OMW_32BIT_LSB (0x00000001)
#define OMW_32BIT_MSB (0x80000000)
#define OMW_32BIT_ALL (0xFFFFFFFF)

#define OMW_64BIT_LSB (0x0000000000000001)
#define OMW_64BIT_MSB (0x8000000000000000)
#define OMW_64BIT_ALL (0xFFFFFFFFFFFFFFFF)

#define OMW_SIZE_MAX (omw::size_max)

/*! @} */


namespace omw
{
    /*! \addtogroup grp_utility_langSupport_typeSupport
    * @{
    */

    constexpr size_t size_max = static_cast<size_t>(-1);

    /*! @} */
}


#endif // IG_OMW_INTDEF_H
