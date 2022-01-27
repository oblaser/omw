/*
author          Oliver Blaser
date            27.01.2022
copyright       MIT - Copyright (c) 2022 Oliver Blaser
*/

#ifndef IG_OMW_IO_FILE_H
#define IG_OMW_IO_FILE_H

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "../../omw/string.h"
#include "../../omw/vector.h"

namespace omw
{
    namespace io
    {
        /*! \addtogroup grp_ioLib
        * @{
        */

        class FileInterface_Base
        {
        public:
            FileInterface_Base();
            virtual ~FileInterface_Base();

        protected:
            omw::string m_filename;
        };

        class BinFileInterface
        {
        public:
            BinFileInterface();
            virtual ~BinFileInterface();
        };

        class TxtFileInterface
        {
        public:
            TxtFileInterface();
            virtual ~TxtFileInterface();
        };

        //int readBytes(const std::string& filename, std::vector<uint8_t>& buffer);
        //int writeBytes(const std::string& filename, const std::vector<uint8_t>& data);

        //int readString(const std::string& filename, std::string& buffer);
        //int writeString(const std::string& filename, const std::string& str);

        /*! @} */
    }
}

#endif // IG_OMW_IO_FILE_H
