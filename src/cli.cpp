/*
author          Oliver Blaser
date            02.02.2026
copyright       MIT - Copyright (c) 2026 Oliver Blaser
*/

#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

#include "omw/cli.h"
#include "omw/string.h"



size_t omw::cli::choice(const std::string& question, char opt0, char opt1, int def)
{
    int r = -1;
    const std::string a = omw::toLower_asciiExt(std::string(1, opt0));
    const std::string b = omw::toLower_asciiExt(std::string(1, opt1));
    std::string data;

    do {
        std::cout << question << " [" << (def == 0 ? omw::toUpper_asciiExt(a) : a) << "/" << (def == 1 ? omw::toUpper_asciiExt(b) : b) << "] ";
        std::getline(std::cin, data);

        if (omw::toLower_asciiExt(data) == a) { r = 0; }
        else if (omw::toLower_asciiExt(data) == b) { r = 1; }
        else if (data.length() == 0) { r = def; }
        else { r = -1; }
    }
    while ((r != 0) && (r != 1));

    return r;
}
