/*
author          Oliver Blaser
date            11.12.2021
copyright       MIT - Copyright (c) 2021 Oliver Blaser
*/

#include "omw/math.h"


#define IMPLEMENT_FLOAT_SIGNUM() \
int r = 0;                  \
if (value < 0) r = -1;      \
else if (value > 0) r = 1;  \
return r                    \
// end IMPLEMENT_SIGNUM


namespace
{
}



int omw::sign(float value)
{
    IMPLEMENT_FLOAT_SIGNUM();
}

int omw::sign(double value)
{
    IMPLEMENT_FLOAT_SIGNUM();
}

int omw::sign(long double value)
{
    IMPLEMENT_FLOAT_SIGNUM();
}

int omw::sign(const omw::int128_t& value)
{
    int r = 1;

    if (value.isNegative()) r = -1;
    else if ((value.hi() == 0) && (value.lo() == 0)) r = 0;

    return r;
}
