/*
author          Oliver Blaser
date            28.01.2022
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
//! Can be compared to `OMW_VERSION_ID_..`
//! 
//! | Version | Version ID |
//! |:---:|:---:|
//! | v0.2.0 | 1 |
//! | v0.2.1-alpha | 2 |
//! | v0.2.1-alpha.1 | 3 |
//! | v0.2.1-alpha.2 | 4 |
//! 
#define OMW_VERSION_ID (4)
#define OMW_VERSION_MAJ (0)
#define OMW_VERSION_MIN (2)
#define OMW_VERSION_PAT (1)
#define OMW_VERSION_PRSTR ("alpha.2")

#define OMW_VERSION_ID_0_2_0 (1)
#define OMW_VERSION_ID_0_2_1_ALPHA (2)
#define OMW_VERSION_ID_0_2_1_ALPHA_1 (3)
#define OMW_VERSION_ID_0_2_1_ALPHA_2 (4)

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
