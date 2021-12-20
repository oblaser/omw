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

## Tools
- cmake and make
- doxygen
- [potoroo](https://github.com/oblaser/potoroo) (0.2.0-pre-release or newer) see `/web`
- Visual Studio
- Visual Studio Code (used to write and create/deploy/build the contents of the `/doc` and `/web` directories)
