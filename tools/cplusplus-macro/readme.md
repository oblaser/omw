# C++ macro `__cplusplus`

```
$ ./gcc.sh
g++ (Debian 8.3.0-6) 8.3.0
#define __cplusplus 199711L  C++98
#define __cplusplus 199711L  C++03
#define __cplusplus 201103L  C++11
#define __cplusplus 201402L  C++14
#define __cplusplus 201703L  C++17
#define __cplusplus 201709L  C++2a
g++: error: unrecognized command line option ‘-std=c++20’; did you mean ‘-std=c++2a’?
  C++20
g++: error: unrecognized command line option ‘-std=c++23’; did you mean ‘-std=c++03’?
  C++23
$ 
```

## Links
- https://stackoverflow.com/a/7132549
- https://renenyffenegger.ch/notes/development/languages/C-C-plus-plus/preprocessor/macros/predefined/__cplusplus
- `_MSVC_LANG` https://docs.microsoft.com/en-us/cpp/preprocessor/predefined-macros

`__cplusplus` is not generally safe to use with MSVC:
https://devblogs.microsoft.com/cppblog/msvc-now-correctly-reports-__cplusplus/
