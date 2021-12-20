/*
author          Oliver Blaser
date            20.12.2021
copyright       MIT - Copyright (c) 2021 Oliver Blaser
*/

#include <sstream>
#include <string>

#include "omw/defs.h"
#include "omw/omw.h"



//! @brief Returns the version of the this library.
omw::Version omw::info::version()
{
    return omw::Version(0, 2, 0, "a");
}

//! @brief Returns an info text.
//! 
//! The info text contains version, copyright and a link to the project webpage.
//! 
omw::string omw::info::infoTxt()
{
    std::stringstream s;

    s << OMWi_DISPSTR("OMW v") << omw::info::version();
    if (omw::info::version().rev() > 999) s << " - pre-release " << __DATE__ << " " << __TIME__;
#ifdef OMW_DEBUG
    s << " - DEBUG";
#endif
    s << std::endl;
    
    s << OMWi_DISPSTR("Copyright (c) 2021 Oliver Blaser.") << std::endl;
    s << OMWi_DISPSTR("License: MIT <https://opensource.org/licenses/MIT>.") << std::endl;
    s << OMWi_DISPSTR("This is free software. There is NO WARRANTY.") << std::endl;
    s << OMWi_DISPSTR("See <https://github.com/oblaser/omw> for further information.");

    return s.str();
}
