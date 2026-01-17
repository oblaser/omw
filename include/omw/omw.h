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

#include <string>

#include "../omw/defs.h"
#include "../omw/version.h"


/*! \addtogroup grp_macro
 * @{
 */

//! \name OMW Info
//! `#include <omw/omw.h>`
/// @{

/**
 * Uniqe version ID, always greater than the ID of the previous version.
 * Might get increased in steps due to relevant changes before the next release.
 *
 * Can be compared to `OMW_VERSION_ID_..` constants.
 *
 * | Version           | Version ID |
 * |:-----------------:|:----------:|
 * | v0.3.0            |   251230   |
 * | v0.2.1            |      6     |
 * | v0.2.1-beta       |      5     |
 * | v0.2.1-alpha.2    |      4     |
 * | v0.2.1-alpha.1    |      3     |
 * | v0.2.1-alpha      |      2     |
 * | v0.2.0            |      1     |
 */
#define OMW_VERSION_ID (260117)

#define OMW_VERSION_MAJ   (0)
#define OMW_VERSION_MIN   (3)
#define OMW_VERSION_PAT   (1)
#define OMW_VERSION_PRSTR ("alpha")

#define OMW_VERSION_ID_0_2_0         (1)
#define OMW_VERSION_ID_0_2_1_ALPHA   (2)
#define OMW_VERSION_ID_0_2_1_ALPHA_1 (3)
#define OMW_VERSION_ID_0_2_1_ALPHA_2 (4)
#define OMW_VERSION_ID_0_2_1_BETA    (5)
#define OMW_VERSION_ID_0_2_1         (6)
// new format: `YYMMnn` where `nn` is mostly the day of the month but not limited to that, hence _n_ and not _D_
#define OMW_VERSION_ID_0_3_0         (251230)

/// @}

/*! @} */


namespace omw {

namespace info {
    omw::Semver version();
    std::string infoTxt();
}

} // namespace omw


#endif // IG_OMW_H
