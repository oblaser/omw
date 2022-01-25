/*
author          Oliver Blaser
date            24.01.2022
copyright       MIT - Copyright (c) 2022 Oliver Blaser
*/

/*!
* \file
*
* See also \ref grp_macro.
*/

#ifndef IG_OMW_H
#define IG_OMW_H

#include "../omw/defs.h"
#include "../omw/string.h"
#include "../omw/version.h"


/*! \addtogroup grp_macro
* @{
*/

//! \name OMW Info
//! `#include <omw/omw.h>`
/// @{

//! 
//! Uniqe version ID, always greater than the ID of the last version.
//! 
//! | Version | Version ID |
//! |:---:|:---:|
//! | v0.2.0-alpha.4 | 1 |
//! 
#define OMW_VERSION_ID (1)

#define OMW_VERSION_MAJ (0)
#define OMW_VERSION_MIN (2)
#define OMW_VERSION_PAT (0)
#define OMW_VERSION_PRSTR ("alpha.4")

/// @}

/*! @} */


namespace omw
{
    namespace info
    {
        omw::Version version();
        omw::string infoTxt();
    }
}

#endif // IG_OMW_H
