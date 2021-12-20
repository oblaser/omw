# Contributing

> Before contributing you should also read the contents on the projects webpage and the readme. Also be familiar with the documentation.



## Naming
Names are in lower camel case and normally don't use the underscore `_`.

Classes however are in upper camel case. Exception classes are in lowercase and use the underscore.
> For basse classes I don't have a clear idea. It may differ from case to case.

Macros are in uppercase and start with `OMW_`.



## Translation/Language
At the moment english is the only language available. But the strings wich can be
translated are passed through the `OMWi_DISPSTR(x)` macro to make it easier to find them
in future edits, wich may support multiple languages.



## Versioning
### Phase 0 or General Pre-Release
Releases with the major version `0` are actually pre-releases with the scheme `0.<major>.<minpat>`.
Where `<minpat>` is incremented every time `<minor>` or `<patch>` would be incremented.

### Files
Edit the version in the following files before releasing:
- `build/dep_omw_globals.sh`
- `build/dep_readme.txt`
- `doc/Doxyfile`
- `src/omw.cpp`
- `tests/unit/main.cpp`

### Scheme
#### Since `v0.2.0-a`
https://semver.org/

`1.0.0-alpha < 1.0.0-alpha.1 < 1.0.0-alpha.beta < 1.0.0-beta < 1.0.0-beta.2 < 1.0.0-beta.11 < 1.0.0-rc.1 < 1.0.0`

#### Until `v0.2.0-a`
Something else. Revision (patch) > 999 have been pre-releases.



## Tools
- Build on Linux: `cmake` and `build-essential`
- Build on Windows: `Visual Studio`
- `doxygen`
- [`potoroo`](https://github.com/oblaser/potoroo) (0.2.0-pre-release or later) see `web` directory
- `Visual Studio Code` (used to write and create/deploy/build the contents of the `doc` and `web` directories)
