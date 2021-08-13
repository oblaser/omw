/*
author      Oliver Blaser
date        13.08.2021
copyright   MIT - Copyright (c) 2021 Oliver Blaser
*/

#ifndef OMW_WINDOWS_ERROR_H
#define OMW_WINDOWS_ERROR_H

#include "../../omw/defs.h"
#ifdef OMW_PLAT_WIN

#include <iostream>
#include <string>

namespace omw
{
    namespace windows
    {
        enum ERRORCODE
        {
            EC_OK = 0,                      /*!< No error occured */
            EC_ERROR,                       /*!< General error */
            EC_INV_ARG,                     /*!< Invalid arguments */
            EC_INV_UNICODE,                 /*!< Invalid unicode codepoints are present */
            EC_INTERNAL,                    /*!< A linbrary internal error occured (bugfix in source needed) */
            EC_UNKNOWN_WIN,                 /*!< An unspecified Windows API error occurred */
            
            EC_ENVVAR_NOT_FOUND,            /*!< The specified environment variable could not be found */

            EC_RESOURCE_NOT_FOUND,          /*!< The specified resource could not be found */
            EC_RESOURCE_NOT_LOADED,         /*!< The resource could not be loaded */
            
            EC_STRCONV_DEST_BUFFER_SIZE     /*!< `dest` buffer is too small */
        };

        class ErrorCode
        {
        public:
            ErrorCode();
            ErrorCode(int code, const std::string& message = "");
            virtual ~ErrorCode();

            virtual int code() const;
            virtual const std::string& msg() const;

            virtual bool good() const;

            std::string toString() const;

            friend std::ostream& operator<<(std::ostream& os, const ErrorCode& ec);

        private:
            int errorCode;
            std::string errorMsg;
        };
    }
}

#endif // OMW_PLAT_WIN
#endif // OMW_WINDOWS_ERROR_H
