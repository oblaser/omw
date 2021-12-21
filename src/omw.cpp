/*
author          Oliver Blaser
date            20.12.2021
copyright       MIT - Copyright (c) 2021 Oliver Blaser
*/

#include <sstream>
#include <string>

#include "omw/defs.h"
#include "omw/omw.h"



//! @return The version of the library
omw::Version omw::info::version()
{
    return omw::Version(0, 2, 0, "alpha.2");
}

//! 
//! The info text contains version, copyright and a link to the project webpage.
//! 
omw::string omw::info::infoTxt()
{
    std::stringstream s;

    s << OMWi_DISPSTR("OMW v") << omw::info::version().toString();
#ifdef OMW_DEBUG
    s << OMWi_DISPSTR(" - DEBUG");
#endif
    s << std::endl;

    s << OMWi_DISPSTR("Copyright (c) 2021 Oliver Blaser.") << std::endl;
    s << OMWi_DISPSTR("License: MIT <https://opensource.org/licenses/MIT>.") << std::endl;
    s << OMWi_DISPSTR("This is free software. There is NO WARRANTY.") << std::endl;
    s << OMWi_DISPSTR("See <https://github.com/oblaser/omw> for further information.");

    return s.str();
}
