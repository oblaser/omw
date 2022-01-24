# C++ macro `__cplusplus`



## Links
- https://stackoverflow.com/a/7132549
- https://renenyffenegger.ch/notes/development/languages/C-C-plus-plus/preprocessor/macros/predefined/__cplusplus
- `_MSVC_LANG` https://docs.microsoft.com/en-us/cpp/preprocessor/predefined-macros

`__cplusplus` is not generally safe to use with MSVC:
https://devblogs.microsoft.com/cppblog/msvc-now-correctly-reports-__cplusplus/



# Script Outputs
## g++
### 11.1.0
```
$ sh ./gcc.sh
g++ (GCC) 11.1.0
#define __cplusplus 199711L  C++98
#define __cplusplus 199711L  C++03
#define __cplusplus 201103L  C++11
#define __cplusplus 201402L  C++14
#define __cplusplus 201703L  C++17
#define __cplusplus 202002L  C++2a
#define __cplusplus 202002L  C++20
#define __cplusplus 202100L  C++23
$ 
```
