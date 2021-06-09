/*
author         Oliver Blaser
date           09.06.2021
copyright      MIT - Copyright (c) 2021 Oliver Blaser
*/

#include <sstream>
#include <string>

#include "defs.h"
#include "omw.h"



omw::Version omw::info::version()
{
    return omw::Version(0, 0, 0);
}

std::string omw::info::infoTxt()
{
    std::stringstream s;

    s << OMWi_DISPSTR("OMW v") << omw::info::version() << std::endl;
    s << OMWi_DISPSTR("Copyright (c) 2021 Oliver Blaser.") << std::endl;
    s << OMWi_DISPSTR("License: MIT <https://opensource.org/licenses/MIT>.") << std::endl;
    s << OMWi_DISPSTR("This is free software. There is NO WARRANTY.") << std::endl;
    s << OMWi_DISPSTR("See <https://github.com/oblaser/omw> for further information.") << std::endl;

    return s.str();
}
