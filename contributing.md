# Contributing

> Before contributing you should also read the contents on the projects webpage and the readme. Also be familiar with the documentation.



## Naming
> It's a mix between the C++ standard and the conventions I was tought.
> Classes and functions more related to the standard have a more std like naming.

Names are in lower camel case and normally don't use the underscore `_`.

Classes however are in upper camel case. Exception classes are in lowercase and use the underscore.
> For base classes I don't have a clear idea. Maybe something like a `_Base` suffix.
> It may differ from case to case.

Macros and defines are in uppercase and begin with `OMW_`.



## Translation/Language
At the moment english is the only language available. But the strings wich can be
translated are passed through the `OMWi_DISPSTR(x)` macro to make it easier to find them
in future edits, wich may support multiple languages.



## Versioning
### Scheme
Since `v0.2.0-alpha`: [semver 2.0.0](https://semver.org/)

Before: Something else. Revision (patch) > 999 have been pre-releases.

### Major Version 0
In development. May not be backwards compatible.

### Files
The version must be consistent in the following files:
- `build/dep_vstr.txt`
- `doc/Doxyfile`
- `include/omw/omw.h`
- `tests/unit/main.cpp`
- `web/doc/index.html`
- `release-notes.md`

Copyright year showing up in binaries or packages:
- `build/dep_globals.sh`
- `src/omw.cpp`



## Tools
- Build on Linux: `cmake` and `build-essential`
- Build on Windows: `Visual Studio`
- `doxygen`
- [`potoroo`](https://github.com/oblaser/potoroo) (0.2.0-pre-release or later) see `web` directory
- `Visual Studio Code` (used to write and create/deploy/build the contents of the `doc` and `web` directories)
