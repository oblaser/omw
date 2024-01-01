# Release Notes

> _Pre-Releases_
> The main page of the documentation describes which parts are in
> a pre-release (maybe not tested) state.



### v0.2.1

Implementation changed
 - `omw::windows::getEnvironmentVariable()` watch new exceptions

New
 - `omw::windows::u8tows()` and `omw::windows::wstou8()` (note that the exceptions differ from the old functions)

Removed
 - Nullable, use `std::optional`
 - moved `omw::windows::utf8_to_wstr()` and `omw::windows::wstr_to_utf8()` to deprecated namespace



### v0.2.1-beta

New
 - "omw::vector Implementation Functions" in Module "Containers Library" (*grp_containersLib*)
 - added overloads of `omw::split` and `omw::splitLen`
 - `omw::isNull()`
 - `omw::replaceFirst()` and `omw::replaceAll()` for `std::string`

Improved
 - `omw::isHex()`



### v0.2.1-alpha.1

New
 - `omw::levenshteinDistance()`
 - `omw::stoz()`
 - `omw::string::reverse()` and `reversed()`
 - "omw::string Implementation Functions" in Module "Strings Library" (*grp_stringLib*)
 - `omw::Base_Nullable` and `omw::Nullable<T>`
 - `omw::io::FileInterface_Base::openRead()`
 - `omw::io::FileInterface_Base::openWrite()`
 - `omw::io::SerialPort`

Removed
 - `omw::isWhitespace()`



### v0.2.1-alpha

Refactor
 - moved `omw::getSerialPortList()` and `omw::sortSerialPortList()` to `omw::preview`

New
 - `omw::preview::crc16_kermit()` (checksum.h)
 - File interface classes (file.h)
 - `omw::io::ConfigFile` and `omw::io::IniFileM2M` (configFile.h)



### v0.2.0

Functionality changed
 - `omw::sepHexStr(const std::string&, char)` may prepend a "0"
 - Shift right operators of 128-bit types (see  _Utility Library_ > _Language Support_ > _Bitwise Shift Operators_)
 - `omw::Version` member type changed to `int32_t`

Refactor
- moved `omw::string::toUrlEncoded()` to encoding.h

New
 - `omw::Color::to_wxW()`
 - `omw::string::std()`
 - `omw::toHexStr()` with 128-bit
 - `omw::bigEndian` (encoding.h)
 - `omw::readString()` (string.h)
 - `omw::writeString()` (string.h)
 - `omw::shiftLeft()` (utility.h)
 - `omw::shiftRight()` (utility.h)
 - `omw::shiftLeftAssign()` (utility.h)
 - `omw::shiftRightAssign()` (utility.h)
 - Version macros (omw.h)
 - Checksum Library
 - Containers Library
 - `OMW_CXX_...` `OMW_PLAT_...` `OMW_PARCH_...` `OMW_CPPSTD_...` (defs.h)



### v0.2.0-alpha.2

First Release to be used.
 - Changed some function parameters
