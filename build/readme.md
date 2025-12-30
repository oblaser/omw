# Build Scripts

The scripts must have this directory as working directory.

`dep_*` files are dependencies of the scripts and should not be called directly.


### `*.sh` Scripts

They return __0__ on success and __1__ on error.
Eexcept the `pack_*` scripts, they don't return error codes.


## Build
### Linux
Required software: `cmake` and `build-essential`
```sh
$ ./build.sh [cleanAll] cmake make
```

### Windows
Required software: `Visual Studio 2019`
- Build
    1. Open `./vs/omw.sln`
    0. Batch build `Debug | x86` and `Release | x86`
- Test
    1. Open `../tests/unit/vs/omw-tests-unit.sln`
    0. Batch build `Debug | x86` and `Release | x86`
    0. Run the debug and release executables from the command line

Or simply run `build.bat` in this directory.



---



## Versioning
### Scheme
Since `v0.2.0-alpha`: [semver 2.0.0](https://semver.org/)
> __old:__ Something else. Revision (patch) > 999 have been pre-releases.

### Major Version 0
In development. May not be backwards compatible.

### Files
The version must be consistent in the following files:
- `build/dep_vstr.txt`
- `doc/Doxyfile`
- `include/omw/omw.h`
- `release-notes.md`
- `tests/unit/main.cpp`
- `web/doc/index.html`

Copyright year showing up in binaries or packages:
- `build/dep_globals.sh`
- `src/omw.cpp`
- `license.txt`
