/*
author          Oliver Blaser
date            07.01.2022
copyright       MIT - Copyright (c) 2022 Oliver Blaser
*/

#include <cmath>

#include "omw/cli.h"
#include "omw/defs.h"


#ifdef OMW_PLAT_WIN
#define OMWi_ANSIESC_MODE_DEFAULT_IS_EN (0) // disabled
#else
#define OMWi_ANSIESC_MODE_DEFAULT_IS_EN (1) // endabled
#endif


namespace csi = omw::ansiesc::csi;
namespace sgr = csi::sgr;

namespace {

int OMWi_ansiescMode = omw::ansiesc::MODE_DEFAULT;
#if OMWi_ANSIESC_MODE_DEFAULT_IS_EN
bool OMWi_ansiescSeqBuildEn = true;
#else
bool OMWi_ansiescSeqBuildEn = false;
#endif

void OMWi_set_ansiescSeqBuildEn()
{
    if (OMWi_ansiescMode == omw::ansiesc::MODE_ENABLED) { OMWi_ansiescSeqBuildEn = true; }
    else if (OMWi_ansiescMode == omw::ansiesc::MODE_DISABLED) { OMWi_ansiescSeqBuildEn = false; }
    else
    {
#if OMWi_ANSIESC_MODE_DEFAULT_IS_EN
        OMWi_ansiescSeqBuildEn = true;
#else
        OMWi_ansiescSeqBuildEn = false;
#endif
    }
}

} // namespace


//! @brief Root of all sequence builders.
//! @param type Escape sequence type
//! @param argstr The arguments of the sequence
//!
//! Builds an escape sequence: <b><tt>ESC \<type\> \<argstr\></tt></b>.
//!
//! As the root sequence builder, it takes care of the \ref ns_omw_ansiesc_section_ansiEscMode.
//!
omw::string omw::ansiesc::seq(char type, const omw::string& argstr)
{
    if (omw::ansiesc::isEnabled()) { return (omw::string(1, omw::ansiesc::escChar) + type + argstr); }
    else return omw::string();
}

//! @param mode One of `omw::ansiesc::MODE`
//!
//! See \ref ns_omw_ansiesc_section_ansiEscMode.
//!
void omw::ansiesc::setMode(int mode)
{
    if ((mode == omw::ansiesc::MODE_ENABLED) || (mode == omw::ansiesc::MODE_DISABLED)) { OMWi_ansiescMode = mode; }
    else { OMWi_ansiescMode = omw::ansiesc::MODE_DEFAULT; }

    OMWi_set_ansiescSeqBuildEn();
}

//! @return The current mode. One of `omw::ansiesc::MODE`
//!
//! See \ref ns_omw_ansiesc_section_ansiEscMode.
//!
int omw::ansiesc::getMode() { return OMWi_ansiescMode; }

//!
//! \ref omw::ansiesc::setMode() "Sets the mode" to `omw::ansiesc::MODE_ENABLED` or `omw::ansiesc::MODE_DISABLED`.
//!
void omw::ansiesc::enable(bool state)
{
    if (state) omw::ansiesc::setMode(omw::ansiesc::MODE_ENABLED);
    else omw::ansiesc::setMode(omw::ansiesc::MODE_DISABLED);
}

//!
//! \ref omw::ansiesc::setMode() "Sets the mode" to `omw::ansiesc::MODE_DISABLED`.
//!
void omw::ansiesc::disable() { omw::ansiesc::enable(false); }

bool omw::ansiesc::isEnabled() { return OMWi_ansiescSeqBuildEn; }



//! @param ctrlSeqType Control sequence type
//! @param argstr The argument(s) of the sequence
//!
//! Builds a CSI escape sequence: <b><tt>ESC [ \<argstr\> \<ctrlSeqType\></tt></b>.
//!
omw::string omw::ansiesc::csi::seq(char ctrlSeqType, const omw::string& argstr) { return omw::ansiesc::seq(omw::ansiesc::CSI, argstr + ctrlSeqType); }

//! @param ctrlSeqType Control sequence type
//! @param arg The argument of the sequence
//!
//! Builds a CSI escape sequence with one argument: <b><tt>ESC [ \<arg\> \<ctrlSeqType\></tt></b>.
//!
omw::string omw::ansiesc::csi::seq(char ctrlSeqType, int arg) { return omw::ansiesc::csi::seq(ctrlSeqType, omw::to_string(arg)); }

//! @param ctrlSeqType Control sequence type
//! @param arg0 The 1st argument of the sequence
//! @param arg1 The 2nd argument of the sequence
//!
//! Builds a CSI escape sequence with two argument: <b><tt>ESC [ \<arg0\> ; \<arg1\> \<ctrlSeqType\></tt></b>.
//!
omw::string omw::ansiesc::csi::seq(char ctrlSeqType, int arg0, int arg1)
{
    return omw::ansiesc::csi::seq(ctrlSeqType, omw::to_string(arg0) + omw::ansiesc::argDelimiter + omw::to_string(arg1));
}



//! @param argstr The argument(s) of the sequence
//!
//! Builds a SGR escape sequence: <b><tt>ESC [ \<argstr\> m</tt></b>.
//!
//! An empty argument string is allowed, it is treated as the reset sequence by the terminal.
//!
omw::string omw::ansiesc::csi::sgr::seq(const omw::string& argstr) { return omw::ansiesc::csi::seq(omw::ansiesc::csi::SGR, argstr); }

//! @param param The SGR parameter
//!
//! Builds a SGR escape sequence: <b><tt>ESC [ \<param\> m</tt></b>.
//!
omw::string omw::ansiesc::csi::sgr::seq(int param) { return omw::ansiesc::csi::sgr::seq(omw::to_string(param)); }

//! @param param The SGR parameter
//! @param arg0 The 1st argument of the sequence
//! @param arg1 The 2nd argument of the sequence
//!
//! Builds a SGR escape sequence: <b><tt>ESC [ \<param\> ; \<arg0\> ; \<arg1\> m</tt></b>.
//!
omw::string omw::ansiesc::csi::sgr::seq(int param, int arg0, int arg1)
{
    return omw::ansiesc::csi::sgr::seq(omw::to_string(param) + omw::ansiesc::argDelimiter + omw::to_string(arg0) + omw::ansiesc::argDelimiter +
                                       omw::to_string(arg1));
}

//! @param param The SGR parameter
//! @param arg0 The 1st argument of the sequence
//! @param arg1 The 2nd argument of the sequence
//! @param arg2 The 3rd argument of the sequence
//! @param arg3 The 4th argument of the sequence
//!
//! Builds a SGR escape sequence: <b><tt>ESC [ \<param\> ; \<arg0\> ; \<arg1\> ; \<arg2\> ; \<arg3\> m</tt></b>.
//!
omw::string omw::ansiesc::csi::sgr::seq(int param, int arg0, int arg1, int arg2, int arg3)
{
    return omw::ansiesc::csi::sgr::seq(omw::to_string(param) + omw::ansiesc::argDelimiter + omw::to_string(arg0) + omw::ansiesc::argDelimiter +
                                       omw::to_string(arg1) + omw::ansiesc::argDelimiter + omw::to_string(arg2) + omw::ansiesc::argDelimiter +
                                       omw::to_string(arg3));
}

//! @param argv Parameters and arguments of the sequence
//! @param argc Number of elemets
//!
//! Builds a composed SGR escape sequence: <b><tt>ESC [ \<argv[0]\> ; \<argv[1]\> ; ... ; \<argv[argc - 1]\> m</tt></b>.
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
            if (i > 0) args += omw::ansiesc::argDelimiter;
            args += omw::to_string(argv[i]);
        }
    }

    return omw::ansiesc::csi::sgr::seq(args);
}

//! @param args Parameters and arguments of the sequence
//!
//! Builds a composed SGR escape sequence: <b><tt>ESC [ \<args[0]\> ; \<args[1]\> ; ... ; \<args[args.size() - 1]\> m</tt></b>.
//!
//! See seq(const int*, size_t).
//!
omw::string omw::ansiesc::csi::sgr::seq(const std::vector<int>& args) { return omw::ansiesc::csi::sgr::seq(args.data(), args.size()); }



// int omw::ansiesc::csi::sgr::to8bitGray(uint8_t value)
//{
//     return sgr::to8bitGray((double)value / 255.0);
// }
//
// int omw::ansiesc::csi::sgr::to8bitGray(double normValue)
//{
//     if ((normValue < 0) || (normValue > 1)) normValue -= std::floor(normValue);
//     return col8bit_grayscale26[std::lround(normValue * (sizeof(sgr::col8bit_grayscale26) / sizeof(sgr::col8bit_grayscale26[0])))];
// }
