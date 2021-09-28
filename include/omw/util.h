/*
author         Oliver Blaser
date           28.09.2021
copyright      MIT - Copyright (c) 2021 Oliver Blaser
*/

#ifndef IG_OMW_UTIL_H
#define IG_OMW_UTIL_H

namespace omw
{
    //! @param value The value to toggle
    //! 
    //! Toggles a boolean value.
    //! 
    inline void toggle(bool& value) { value = !value; }
}

#endif // IG_OMW_UTIL_H
