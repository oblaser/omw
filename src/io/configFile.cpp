/*
author          Oliver Blaser
date            01.03.2022
copyright       MIT - Copyright (c) 2022 Oliver Blaser
*/

#include <algorithm>
#include <string>
#include <vector>

#include "omw/io/configFile.h"



namespace {}



#if 0

/*!
 * \class omw::io::ConfigFileLine
 *
 * Used by `omw::io::ConfigFile`.
 */

omw::io::ConfigFileLine::ConfigFileLine()
    : m_preKey(), m_key(), m_preValue(), m_value(), m_preComment(), m_comment()
{}



/*!
 * \class omw::io::ConfigFile
 *
 * `#include <omw/io/configFile.h>`
 *
 * \section class_omw__io_ConfigFile_section_fileSpec File Specification
 *
 * ...
 */

omw::io::ConfigFile::ConfigFile()
    : m_lineEnd{ 0x0A, 0, 0 }, m_writeUtf8Bom(false), m_lines(0)
{}

void omw::io::ConfigFile::minimize()
{
    for (size_t i = 0; i < m_lines.size();)
    {
        if (m_lines[i].isEmpty()) { m_lines.erase(); }
        else
        {
            m_lines[i].preKey().clear();
            m_lines[i].preValue() = " ";
            m_lines[i].preComment().clear();
            m_lines[i].comment().clear();
            ++i;
        }
    }
}

#endif
