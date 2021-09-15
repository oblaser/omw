/*
author         Oliver Blaser
date           15.09.2021
copyright      MIT - Copyright (c) 2021 Oliver Blaser
*/

#ifndef OMW_H
#define OMW_H

#include <string>

#include "../omw/defs.h"
#include "../omw/string.h"
#include "../omw/version.h"

namespace omw
{
    namespace info
    {
        omw::Version version();
        omw::string infoTxt();
    }
}

#endif // OMW_H
