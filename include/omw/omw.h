/*
author          Oliver Blaser
date            08.12.2021
copyright       MIT - Copyright (c) 2021 Oliver Blaser
*/

#ifndef IG_OMW_H
#define IG_OMW_H

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

#endif // IG_OMW_H
