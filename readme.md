# omw

A C++ middleware library with my often used units.

The user information is on the [projects webpage](https://static.oblaser.ch/omw/)
and the documentation, found on the webpage.



# Build
Either the repo is cloned in to the SDK directory and the library is built there.
Or it is built elsewhere, and the output of the `build/pack_.._bin...` scripts
is then copied to the SDK directory.

## Linux
Required software: `cmake` and `build-essential`
```
$ cd build
$ ./cmake_[re]build.sh
$ ./run_tests.sh [-s]
$ [./pack_bin.sh]
```

## Windows
Required software: `Visual Studio`
1. Build
    1. Open `build/vs/omw.sln`
    0. Batch build `Debug | x86` and `Release | x86`
0. Test
    1. Open `tests/unit/vs/omw-tests-unit.sln`
    0. Batch build `Debug | x86` and `Release | x86`
    0. Run the debug and release executables from the command line
0. _optionally_ Run `pack_bin.bat` in the `build` directory.



---



### Versioning
See [contributing.md / Versioning](https://github.com/oblaser/omw/blob/master/contributing.md#versioning)
