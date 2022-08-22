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
#include "../../omw/string.h"


namespace omw
{
    namespace io
    {
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
            omw::string& preKey() { return m_preKey; }
            const omw::string& preKey() const { return m_preKey; }
            omw::string& key() { return m_key; }
            const omw::string& key() const { return m_key; }
            omw::string& delimiter() { return m_delimiter; }
            const omw::string& delimiter() const { return m_delimiter; }
            omw::string& value() { return m_value; }
            const omw::string& value() const { return m_value; }
            omw::string& commentDelimiter() { return m_commentDelim; }
            const omw::string& commentDelimiter() const { return m_commentDelim; }
            omw::string& comment() { return m_comment; }
            const omw::string& comment() const { return m_comment; }
            /// @}

            //! \name Classification
            /// @{
            bool isComment() const;
            bool isEmpty() const;
            bool isUndef() const;
            /// @}

        private:
            omw::string m_preKey;
            omw::string m_key;
            omw::string m_preValue;
            omw::string m_value;
            omw::string m_preComment;
            omw::string m_comment;
        };

        class ConfigFile
        {
        public:
            ConfigFile();
            ConfigFile(const std::string& filename, int wrLineEnd = omw::io::LE_AUTO, bool wrUtf8Bom = false);
            virtual ~ConfigFile() {}

            const omw::string& getValue(const std::string& key) const;
            const omw::string& getValue(const std::string& key, const std::string& defaultValue) const;

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
    }
}


#endif // IG_OMW_IO_CONFIGFILE_H
