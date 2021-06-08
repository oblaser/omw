# OMW

A C++ middleware library with my often used units.

Since I'm working with Windows and Linux I try to keep it as portable as possible.

[doc](https://static.oblaser.ch/omw/doc/)



## Conventions

### Strings
According to [UTF-8 Everywhere](http://utf8everywhere.org/) strings inside the library are of type `char`
(`std::string` respectively) and formatted as UTF-8. If you call functions on the Windows API you
should use the `foobarW()` functions and Microsofts `WCHAR` types to call the API and
use the conversion functions in `omw::windows` to cenvert between the two string types.

### Translation
At the moment english is the only language available. But the strings wich can be translated are passed through the `_OMW_DISPSTR(x)` macro to make it easier to find them in future edits.
