# Release Notes

> _Pre-Releases_
> The main page of the documentation describes which parts are in
> a pre-release (maybe not tested) state.



### v0.2.0-alpha.3

Implementation changed
 - `omw::sepHexStr(const std::string&, char)` may prepend a "0", check doc

Refactor
- moved `omw::string::toUrlEncoded()` to encoding.h

New
 - `omw::Color::to_wxW()`
 - `omw::string::std()`
 - `omw::toHexStr()` with 128-bit
 - `omw::bcd` (encoding.h)
 - `omw::bigEndian` (encoding.h)
 - `omw::convertByteVector()` (utility.h)
 - `omw::toVector()` (utility.h)



### v0.2.0-alpha.2

First Release to be used.
 - Changed some function parameters
