/*
author          Oliver Blaser
date            27.01.2022
copyright       MIT - Copyright (c) 2022 Oliver Blaser
*/

#ifndef IG_OMW_IO_CONFIGFILE_H
#define IG_OMW_IO_CONFIGFILE_H

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace omw
{
    namespace io
    {
        /*! \addtogroup grp_ioLib
        * @{
        */

        class IniFileM2M
        {
        public:
            IniFileM2M();
            virtual ~IniFileM2M();
        };

        /*! @} */
    }
}

#endif // IG_OMW_IO_CONFIGFILE_H
