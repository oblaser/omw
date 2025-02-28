/*
author          Oliver Blaser
date            13.03.2023
copyright       MIT - Copyright (c) 2023 Oliver Blaser
*/

#include <sstream>
#include <string>

#include "omw/defs.h"
#include "omw/omw.h"



//!
//! Returns the version of the library
//!
omw::Version omw::info::version() { return omw::Version(OMW_VERSION_MAJ, OMW_VERSION_MIN, OMW_VERSION_PAT, OMW_VERSION_PRSTR); }

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

    s << OMWi_DISPSTR("Copyright (c) 2025 Oliver Blaser.") << std::endl;
    s << OMWi_DISPSTR("License: MIT <https://opensource.org/licenses/MIT>.") << std::endl;
    s << OMWi_DISPSTR("This is free software. There is NO WARRANTY.") << std::endl;
    s << OMWi_DISPSTR("See <https://github.com/oblaser/omw> for further information.");

    return s.str();
}
