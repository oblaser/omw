/*
author          Oliver Blaser
date            15.12.2021
copyright       MIT - Copyright (c) 2021 Oliver Blaser
*/

#ifndef IG_OMW_MATH_H
#define IG_OMW_MATH_H

#include <cstdint>

#include "../omw/int.h"


namespace omw {

/*! \addtogroup grp_numerics
 * @{
 */

template <class T> const constexpr T& max(const T& a, const T& b) { return (a > b ? a : b); }
template <class T> const constexpr T& max(const T& a, const T& b, const T& c) { return omw::max(omw::max(a, b), c); }
template <class T> const constexpr T& max(const T& a, const T& b, const T& c, const T& d) { return omw::max(omw::max(a, b), c, d); }

template <class T> const constexpr T& min(const T& a, const T& b) { return (a < b ? a : b); }
template <class T> const constexpr T& min(const T& a, const T& b, const T& c) { return omw::min(omw::min(a, b), c); }
template <class T> const constexpr T& min(const T& a, const T& b, const T& c, const T& d) { return omw::min(omw::min(a, b), c, d); }

// int sign(int value) { return ((0 < value) - (value < 0)); }
// int sign(int64_t value) { return ((0 < value) - (value < 0)); }
// int sign(float value);
// int sign(double value);
// int sign(long double value);
// int sign(const omw::int128_t& value);
// int sgn(int value) { return omw::sign(value); }
// int sgn(int64_t value) { return omw::sign(value); }
// int sgn(float value) { return omw::sign(value); }
// int sgn(double value) { return omw::sign(value); }
// int sgn(long double value) { return omw::sign(value); }
// int sgn(const omw::int128_t& value) { return omw::sign(value); }

/*! @} */

} // namespace omw


#endif // IG_OMW_MATH_H
