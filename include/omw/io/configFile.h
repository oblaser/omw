/*
author          Oliver Blaser
date            05.02.2022
copyright       MIT - Copyright (c) 2022 Oliver Blaser
*/

#ifndef IG_OMW_IO_CONFIGFILE_H
#define IG_OMW_IO_CONFIGFILE_H

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "../../omw/io/file.h"
#include "../../omw/string.h"


namespace omw
{
    namespace io
    {
        /*! \addtogroup grp_ioLib
        * @{
        */



        class ConfigFile
        {
        public:
            ConfigFile();
            virtual ~ConfigFile() {}
        };
        
        /*! @} */
    }
}


#endif // IG_OMW_IO_CONFIGFILE_H
