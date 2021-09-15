/*
author         Oliver Blaser
date           15.09.2021
copyright      MIT - Copyright (c) 2021 Oliver Blaser
*/

#ifndef IG_TESTUTIL_H
#define IG_TESTUTIL_H

#include <iostream>


#define TESTUTIL_TRYCATCH_DECLARE_VAL(valueType, initialValue)  \
bool tu_trycatch_correctCatch;                                  \
const valueType tu_trycatch_initVal = initialValue;             \
valueType tu_trycatch_val = tu_trycatch_initVal;                \
// end TESTUTIL_TRYCATCH_DECLARE_VAL

#define TESTUTIL_TRYCATCH_CHECK(call, exType)                                               \
try { tu_trycatch_val = call; tu_trycatch_correctCatch = false; }                           \
catch (exType& ex) { const char* const msg = ex.what(); tu_trycatch_correctCatch = true; }  \
catch (std::exception& ex) { std::cout << "testUtil catch: " << ex.what() <<std::endl; tu_trycatch_correctCatch = false; } \
catch (...) { tu_trycatch_correctCatch = false; }                                           \
CHECK(tu_trycatch_correctCatch);                                                            \
CHECK(tu_trycatch_val == tu_trycatch_initVal);                                              \
// end TESTUTIL_TRYCATCH_CHECK()


#endif // IG_TESTUTIL_H
