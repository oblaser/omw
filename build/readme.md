# Build Scripts

The scripts must have this directory as working directory.

`dep_*` files are dependencies of the scripts and should not be called directly.


### `*.sh` Scripts

They return __0__ on success and __1__ on error.
Eexcept the `pack_*` scripts, they are stupid.


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



---

### files to edit on release

See [Contributing > Versioning > Files](../contributing.md#files)
