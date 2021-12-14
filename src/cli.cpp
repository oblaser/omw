/*
author          Oliver Blaser
date            10.12.2021
copyright       MIT - Copyright (c) 2021 Oliver Blaser
*/

#include <cmath>

#include "omw/cli.h"

namespace csi = omw::ansiesc::csi;
namespace sgr = csi::sgr;

namespace
{
}



/*!
* \fn inline omw::string omw::ansiesc::csi::seq(char cs, const omw::string& arg = "")
* \param cs Control sequence type
* \param arg The argument(s) of the sequence
*
* Builds an CSI escape sequence: <b><tt>ESC [ \<arg\> \<cs\></tt></b>.
*/

/*!
* \fn inline omw::string omw::ansiesc::csi::seq(char cs, int arg)
* \param cs Control sequence type
* \param arg The argument of the sequence
*
* Builds an CSI escape sequence with one argument: <b><tt>ESC [ \<arg\> \<cs\></tt></b>.
*/

/*!
* \fn inline omw::string omw::ansiesc::csi::seq(char cs, int arg0, int arg1)
* \param cs Control sequence type
* \param arg0 The 1st argument of the sequence
* \param arg1 The 2nd argument of the sequence
*
* Builds an CSI escape sequence with two argument: <b><tt>ESC [ \<arg0\> ; \<arg1\> \<cs\></tt></b>.
*/



/*!
* \fn inline omw::string omw::ansiesc::csi::sgr::seq(const omw::string& args = "")
* \param args The argument(s) of the sequence
*
* Builds an SGR escape sequence: <b><tt>ESC [ \<args\> m</tt></b>.
*/

/*!
* \fn inline omw::string omw::ansiesc::csi::sgr::seq(int param)
* \param param The SGR parameter
*
* Builds an SGR escape sequence: <b><tt>ESC [ \<param\> m</tt></b>.
*/

/*!
* \fn inline omw::string omw::ansiesc::csi::sgr::seq(int param, int arg0, int arg1)
* \param param The SGR parameter
* \param arg0 The 1st argument of the sequence
* \param arg1 The 2nd argument of the sequence
*
* Builds an SGR escape sequence: <b><tt>ESC [ \<param\> ; \<arg0\> ; \<arg1\> m</tt></b>.
*/

//! @param param The SGR parameter
//! @param arg0 The 1st argument of the sequence
//! @param arg1 The 2nd argument of the sequence
//! @param arg2 The 3rd argument of the sequence
//! @param arg3 The 4th argument of the sequence
//! 
//! Builds an SGR escape sequence: <b><tt>ESC [ \<param\> ; \<arg0\> ; \<arg1\> ; \<arg2\> ; \<arg3\> m</tt></b>.
//! 
omw::string omw::ansiesc::csi::sgr::seq(int param, int arg0, int arg1, int arg2, int arg3)
{
    return omw::ansiesc::csi::sgr::seq(omw::to_string(param) + omw::ansiesc::argSepChar +
        omw::to_string(arg0) + omw::ansiesc::argSepChar +
        omw::to_string(arg1) + omw::ansiesc::argSepChar +
        omw::to_string(arg2) + omw::ansiesc::argSepChar +
        omw::to_string(arg3));
}

//! @param argv Parameters and arguments of the sequence
//! @param argc Number of elemets
//! 
//! Builds an composed SGR escape sequence: <b><tt>ESC [ \<argv[0]\> ; \<argv[1]\> ; ... ; \<argv[argc - 1]\> m</tt></b>.
//! 
//! Examples:
//! ```
//! const int sgr1[] = { 38, 5, 33, 1 };
//! std::cout << omw::ansiesc::csi::sgr::seq(sgr1, 4) << "this text will be bold and light blue" << std::endl;
//! 
//! const int sgr2[] = { 0, 96, 7 };
//! std::cout << omw::ansiesc::csi::sgr::seq(sgr2, 3) << "this text will be black on bright cyan" << omw::normal << std::endl;
//! ```
//! 
omw::string omw::ansiesc::csi::sgr::seq(const int* argv, size_t argc)
{
    omw::string args = "";

    if (argv && argc)
    {
        for (size_t i = 0; i < argc; ++i)
        {
            if (i > 0) args += omw::ansiesc::argSepChar;
            args += omw::to_string(argv[i]);
        }
    }

    return omw::ansiesc::csi::sgr::seq(args);
}

/*!
* \fn inline omw::string omw::ansiesc::csi::sgr::seq(const std::vector<int>& args)
* \param args Parameters and arguments of the sequence
*
* Builds an composed SGR escape sequence: <b><tt>ESC [ \<args[0]\> ; \<args[1]\> ; ... ; \<args[args.size() - 1]\> m</tt></b>.
* 
* See seq(const int*, size_t).
*/

//int omw::ansiesc::csi::sgr::to8bitGray(uint8_t value)
//{
//    return sgr::to8bitGray((double)value / 255.0);
//}
//
//int omw::ansiesc::csi::sgr::to8bitGray(double normValue)
//{
//    if ((normValue < 0) || (normValue > 1)) normValue -= std::floor(normValue);
//    return col8bit_grayscale26[std::lround(normValue * (sizeof(sgr::col8bit_grayscale26) / sizeof(sgr::col8bit_grayscale26[0])))];
//}
