# OMW

A C++ middleware library with my often used units.

 - [doc](https://static.oblaser.ch/omw/doc/)
 - [download](https://static.oblaser.ch/omw/download/)



## Conventions

### Naming
Names like `OMWi_...` or similar are for library internal use only. There is no need to
call or read them.

### Strings
According to [UTF-8 Everywhere](http://utf8everywhere.org/) strings are of type `char`
(`std::string` respectively) and formatted as UTF-8. If the Windows API is called, the
`foobarW()` (neither `foobarA()` nor `foobar()`) functions and Microsofts `WCHAR` types
should be used. The conversion functions in `omw/windows/string.h` can be used to convert
between the two string types.

### Translation
At the moment english is the only language available. But the strings wich can be
translated are passed through the `OMWi_DISPSTR(x)` macro to make it easier to find them
in future edits.
