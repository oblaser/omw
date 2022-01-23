# Release Notes

> _Pre-Releases_
> The main page of the documentation describes which parts are in
> a pre-release (maybe not tested) state.



### v0.2.0-alpha.4

Implementation changed
 - `omw::sepHexStr(const std::string&, char)` may prepend a "0"
 - Shift right operators of 128-bit types (see  _Utility Library_ > _Language Support_ > _Bitwise Shift Operators_)
 - `omw::Version` member type changed to `int32_t`

Refactor
- moved `omw::string::toUrlEncoded()` to encoding.h

New
 - `omw::Color::to_wxW()`
 - `omw::string::std()`
 - `omw::toHexStr()` with 128-bit
 - `omw::bcd` (encoding.h)
 - `omw::bigEndian` (encoding.h)
 - `omw::convertByteVector()` (utility.h)
 - `omw::shiftLeft()` (utility.h)
 - `omw::shiftRight()` (utility.h)
 - `omw::shiftLeftAssign()` (utility.h)
 - `omw::shiftRightAssign()` (utility.h)
 - Version macros (omw.h)



### v0.2.0-alpha.2

First Release to be used.
 - Changed some function parameters
