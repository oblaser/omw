/*
author      Oliver Blaser
date        09.06.2021
copyright   MIT - Copyright (c) 2021 Oliver Blaser
*/

#ifndef OMW_WINDOWS_EXCEPTION_H
#define OMW_WINDOWS_EXCEPTION_H

#include "../../omw/defs.h"
#if OMW_PLAT_WIN

#include <stdexcept>
#include <string>

namespace omw
{
    namespace windows
    {
        class envVar_not_found : public std::runtime_error
        {
        public:
            envVar_not_found() = delete;
            explicit envVar_not_found(const std::string& message) : std::runtime_error(message) {}
            explicit envVar_not_found(const char* message) : std::runtime_error(message) {}
            virtual ~envVar_not_found() {}
        };

        class invalid_unicode : public std::runtime_error
        {
        public:
            invalid_unicode() = delete;
            explicit invalid_unicode(const std::string& message) : std::runtime_error(message) {}
            explicit invalid_unicode(const char* message) : std::runtime_error(message) {}
            virtual ~invalid_unicode() {}
        };
    }
}

#endif // OMW_PLAT_WIN
#endif // OMW_WINDOWS_EXCEPTION_H
