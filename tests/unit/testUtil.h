/*
author          Oliver Blaser
date            07.12.2021
copyright       MIT - Copyright (c) 2021 Oliver Blaser
*/

#ifndef IG_TESTUTIL_H
#define IG_TESTUTIL_H

#include <iostream>
#include <stdexcept>
#include <string>

#include <omw/string.h>


#define TESTUTIL_TRYCATCH_DECLARE_VAL(valueType, initialValue)  \
bool tu_trycatch_correctCatch;                                  \
const valueType tu_trycatch_initVal = initialValue;             \
valueType tu_trycatch_val = tu_trycatch_initVal                 \
// end TESTUTIL_TRYCATCH_DECLARE_VAL

#define TESTUTIL_TRYCATCH_CHECK(call, exType)                                               \
try { tu_trycatch_val = call; tu_trycatch_correctCatch = false; }                           \
catch (exType& ex) { const char* const msg = ex.what(); tu_trycatch_correctCatch = true; }  \
catch (std::exception& ex) { std::cout << "testUtil catch: " << ex.what() <<std::endl; tu_trycatch_correctCatch = false; } \
catch (...) { tu_trycatch_correctCatch = false; }                                           \
CHECK(tu_trycatch_correctCatch);                                                            \
CHECK(tu_trycatch_val == tu_trycatch_initVal)                                               \
// end TESTUTIL_TRYCATCH_CHECK()


namespace tu
{
    int strcmp(const omw::string& a, const char* b) { return std::strcmp(a.c_str(), b); }
    int strcmp(const char* a, const omw::string& b) { return std::strcmp(a, b.c_str()); }
    int strcmp(const omw::string& a, const omw::string& b) { return std::strcmp(a.c_str(), b.c_str()); }
}

#endif // IG_TESTUTIL_H
