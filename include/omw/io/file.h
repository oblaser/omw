/*
author          Oliver Blaser
date            01.03.2022
copyright       MIT - Copyright (c) 2022 Oliver Blaser
*/

#ifndef IG_OMW_IO_FILE_H
#define IG_OMW_IO_FILE_H

#include <cstddef>
#include <cstdint>
#include <fstream>
#include <string>
#include <vector>

#include "../../omw/defs.h"
#include "../../omw/vector.h"

namespace omw {
namespace io {

    /*! \addtogroup grp_ioLib
     * @{
     */

    enum LINE_END
    {
        LE_LF = 0,
        LE_CR,
        LE_CRLF,

#if defined(OMW_PLAT_WIN)
        LE_AUTO = LE_CRLF
#elif defined(OMW_PLAT_APPLE)
        LE_AUTO = LE_CR
#else
        LE_AUTO = LE_LF
#endif
    };

    class FileInterface_Base
    {
    public:
        using fstream = std::fstream;
        using iostate = fstream::iostate;   /*!< Stream state type */
        using openmode = fstream::openmode; /*!< Open mode type */

        static constexpr iostate good = fstream::goodbit;
        static constexpr iostate badbit = fstream::badbit;
        static constexpr iostate failbit = fstream::failbit;
        static constexpr iostate eofbit = fstream::eofbit;

        static constexpr openmode rd = fstream::in;  /*!< Open file in read mode */
        static constexpr openmode wr = fstream::out; /*!< Open file in write mode */


    public:
        FileInterface_Base();
        FileInterface_Base(const std::string& filename);
        virtual ~FileInterface_Base();

        const std::string& filename() const { return m_filename; }

        void setFileName(const std::string& filename) { m_filename = filename; }

        void open(openmode mode) const;
        void openRead() const { open(FileInterface_Base::rd); }
        void openWrite() { open(FileInterface_Base::wr); }
        void close() const;

        size_t size() const;

        void read(char* buffer, size_t count) const;
        void write(const char* data);
        void write(const char* data, size_t count);

        iostate getState() const;

    private:
        std::string m_filename;
        mutable fstream m_fs;
    };

    class BinFileInterface : public omw::io::FileInterface_Base
    {
    public:
        BinFileInterface();
        BinFileInterface(const std::string& filename);
        virtual ~BinFileInterface();

        void read(uint8_t* buffer, size_t count) const;
        void write(const uint8_t* data, size_t count);
    };

    //!
    //! `#include <omw/io/file.h>`
    //!
    //! Text file interface.
    //!
    using TxtFileInterface = omw::io::FileInterface_Base;



    std::streamsize size_to_streamsize(size_t val);
    size_t streampos_to_size(const std::streampos& val);
    inline std::streamoff streampos_to_streamoff(const std::streampos& val) { return static_cast<std::streamoff>(val); }



    // int readBytes(const std::string& filename, std::vector<uint8_t>& buffer);
    // int writeBytes(const std::string& filename, const std::vector<uint8_t>& data);

    // int readString(const std::string& filename, std::string& buffer);
    // int writeString(const std::string& filename, const std::string& str);

    /*! @} */

} // namespace io
} // namespace omw

#endif // IG_OMW_IO_FILE_H
