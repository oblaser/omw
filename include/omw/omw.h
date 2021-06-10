/*
author         Oliver Blaser
date           09.06.2021
copyright      MIT - Copyright (c) 2021 Oliver Blaser
*/

#ifndef OMW_H
#define OMW_H

#include <string>

#include "omw/defs.h"
#include "omw/version.h"

namespace omw
{
    namespace info
    {
        omw::Version version();
        std::string infoTxt();
    }
}

#endif // OMW_H
