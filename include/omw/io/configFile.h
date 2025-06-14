/*
author          Oliver Blaser
date            01.03.2022
copyright       MIT - Copyright (c) 2022 Oliver Blaser
*/

#ifndef IG_OMW_IO_CONFIGFILE_H
#define IG_OMW_IO_CONFIGFILE_H

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "../../omw/io/file.h"


namespace omw {
namespace io {

    /*! \addtogroup grp_ioLib
     * @{
     */

#if 0
    class ConfigFileLine
    {
    public:
        ConfigFileLine();
        ConfigFileLine(const char* p);
        ConfigFileLine(std::string& preKey, std::string& key, std::string& delimiter, std::string& value, std::string& commentDelimiter, std::string& comment);
        virtual ~ConfigFileLine() {}

        void clear();
        void parse(const char* p);

        //! \name Getters
        /// @{
        std::string& preKey() { return m_preKey; }
        const std::string& preKey() const { return m_preKey; }
        std::string& key() { return m_key; }
        const std::string& key() const { return m_key; }
        std::string& delimiter() { return m_delimiter; }
        const std::string& delimiter() const { return m_delimiter; }
        std::string& value() { return m_value; }
        const std::string& value() const { return m_value; }
        std::string& commentDelimiter() { return m_commentDelim; }
        const std::string& commentDelimiter() const { return m_commentDelim; }
        std::string& comment() { return m_comment; }
        const std::string& comment() const { return m_comment; }
        /// @}

        //! \name Classification
        /// @{
        bool isComment() const;
        bool isEmpty() const;
        bool isUndef() const;
        /// @}

    private:
        std::string m_preKey;
        std::string m_key;
        std::string m_preValue;
        std::string m_value;
        std::string m_preComment;
        std::string m_comment;
    };

    class ConfigFile
    {
    public:
        ConfigFile();
        ConfigFile(const std::string& filename, int wrLineEnd = omw::io::LE_AUTO, bool wrUtf8Bom = false);
        virtual ~ConfigFile() {}

        const std::string& getValue(const std::string& key) const;
        const std::string& getValue(const std::string& key, const std::string& defaultValue) const;

        void setValue(const std::string& key, const std::string& value);

        void insertAfter(size_t idx, const omw::io::ConfigFileLine& data);
        void insertAfter(const std::string& key, const omw::io::ConfigFileLine& data);
        void insertBefore(size_t idx, const omw::io::ConfigFileLine& data);
        void insertBefore(const std::string& key, const omw::io::ConfigFileLine& data);

        void minimize();
        void minimizeLight();
        void rmComments();

        std::vector<omw::io::ConfigFileLine>& lines() { return m_lines; }
        const std::vector<omw::io::ConfigFileLine>& lines() const { return m_lines; }

        void readFile();
        void writeFile() const;

    private:
        char m_lineEnd[3];
        bool m_writeUtf8Bom;
        std::vector<omw::io::ConfigFileLine> m_lines;
    };
#endif

    /*! @} */

} // namespace io
} // namespace omw


#endif // IG_OMW_IO_CONFIGFILE_H
