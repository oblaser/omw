/*
author          Oliver Blaser
date            13.08.2021
copyright       MIT - Copyright (c) 2021 Oliver Blaser
*/

/*!
\file
\brief Resource definitions.

This file has to be included by the resource file(s). It does not have to be
included by the source code, unless one of the
\ref omw::windows::getResource() "getResource()" functions is used, which is
not recommended. Speciffic get resource functions (e.g.
\ref omw::windows::getTextResource() "getTextResource()") should be used
instead.

*/

#ifndef IG_OMW_WINDOWS_RESOURCETYPES_H
#define IG_OMW_WINDOWS_RESOURCETYPES_H


/*! \addtogroup grp_windows
 * @{
 */

#define OMW_RCT__BASE_   20000 /*!< custom resource types base value*/
#define OMW_RCT_BINFILE  20001 /*!< Binary file resource type */
#define OMW_RCT_TEXTFILE 20002 /*!< Text file resource type */

/*! @} */


#endif // IG_OMW_WINDOWS_RESOURCETYPES_H
