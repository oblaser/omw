/*
author          Oliver Blaser
date            27.01.2022
copyright       MIT - Copyright (c) 2022 Oliver Blaser
*/

#include <stdexcept>
#include <fstream>
#include <string>
#include <vector>

#include "omw/defs.h"
#include "omw/io/file.h"
#include "omw/intdef.h"
#include "omw/string.h"



namespace
{
}



/*!
* \class omw::io::FileInterface_Base
*
* `#include <omw/io/file.h>`
*
* Wrapper class for `std::fstream`.
* 
* Alldought this method of reading and writing a file is not very efficient, it's convenient, easy to use and fine for small files.
* 
* The constness of the member functions is to let the file act like a C++ object.
*/

omw::io::FileInterface_Base::FileInterface_Base()
    : m_filename(), m_fs()
{
    m_fs.exceptions(std::ios::badbit | std::ios::eofbit | std::ios::failbit);
}

omw::io::FileInterface_Base::FileInterface_Base(const std::string& filename)
    : m_filename(filename), m_fs()
{
    m_fs.exceptions(std::ios::badbit | std::ios::eofbit | std::ios::failbit);
}

omw::io::FileInterface_Base::~FileInterface_Base()
{}

const omw::string& omw::io::FileInterface_Base::filename() const
{
    return m_filename;
}

//! @param mode Either `FileInterface_Base::rd` or `FileInterface_Base::wr`
//! 
//! \b Exceptions
//! - `fstream::failure` if an error occures
//! 
void omw::io::FileInterface_Base::open(openmode mode) const
{
    m_fs.open(m_filename,  mode | std::ios::binary);
    if (getState() != good) throw fstream::failure("omw::io::FileInterface_Base::open");
}

//! 
//! \b Exceptions
//! - `fstream::failure` if an error occures
//! 
void omw::io::FileInterface_Base::close() const
{
    m_fs.close();
    if (getState() != good) throw fstream::failure("omw::io::FileInterface_Base::close");
}

//! 
//! \b Exceptions
//! - `std::out_of_range` if the file is too big
//! - `std::runtime_error` if the scanned file size was negative
//! - `std::ios::failure` thrown by
//!    - <tt><a href="https://en.cppreference.com/w/cpp/io/basic_istream/seekg" target="_blank">std::istream::seekg()</a></tt>
//!    - <tt><a href="https://en.cppreference.com/w/cpp/io/basic_istream/tellg" target="_blank">std::istream::tellg()</a></tt>
//! 
size_t omw::io::FileInterface_Base::size() const
{
    const char* const fnName = "omw::io::FileInterface_Base::size";

    m_fs.seekg(0, std::ios::end);
    const std::istream::pos_type ifsPosEnd = m_fs.tellg();
    


    // 
    // std::istream::pos_type => std::char_traits<char>::pos_type => std::streampos =>
    //      std::fpos<State> (which has an to std::streamoff conversion operator)
    // 
    // ==# MSW #==
    // x86: int32
    // x64: int64
    // https://docs.microsoft.com/en-us/cpp/standard-library/ios-typedefs
    // https://docs.microsoft.com/en-us/cpp/standard-library/fpos-class
    // 



    if (ifsPosEnd < 0) throw std::runtime_error(fnName);

    // If the sizes would be the same, size_t could represent every positive value
    // of std::istream::pos_type.
    // 
    // If std::istream::pos_type is grater than size_t, throw an exception if the
    // value can not be represented by size_t.
    // 
    // If it's a negative value, an exception is thrown above.
    // 
    // 
    // Can't use sizeof operator since std::streamsize is a class.
    // 
    // "if sizeof(std::streamsize) > sizeof(size_t)"
    if (std::istream::pos_type(static_cast<size_t>(-1)) > 0)
    {
        // if ifsPosEnd > size_t_max
        if (ifsPosEnd > std::istream::pos_type(static_cast<size_t>(-1)))
        {
            throw std::out_of_range(fnName);
        }
    }

    

    //const size_t dataSize = static_cast<size_t>(ifsPosEnd);
    //const std::streamsize ifsSize = static_cast<std::streamsize>(ifsPosEnd);

    return static_cast<size_t>(ifsPosEnd);
}

//! 
//! Allways starts reading at stream position 0.
//! 
//! \b Exceptions
//! - `std::invalid_argument` if buffer is _null_
//! - `std::ios::failure` thrown by
//!    - <tt><a href="https://en.cppreference.com/w/cpp/io/basic_istream/seekg" target="_blank">std::istream::seekg()</a></tt>
//!    - <tt><a href="https://en.cppreference.com/w/cpp/io/basic_istream/read" target="_blank">std::istream::read()</a></tt>
//! 
void omw::io::FileInterface_Base::read(char* buffer, size_t count) const
{
    const char* const fnName = "omw::io::FileInterface_Base::read";

    if (!buffer) throw std::invalid_argument(fnName);

    m_fs.seekg(0, std::ios::beg);

    //
    // A size check like in size() could be done here, but because count is typically
    // the value returned by size() (or less), the additional check is omitted.
    //

    const std::streamsize sz = static_cast<std::streamsize>(count);
    m_fs.read(buffer, sz);
}

//! @param str Null terminated string
//! 
//! Examines the string length and then passes both to `omw::io::FileInterface_Base::write(const char* data, size_t count)`.
//! 
void omw::io::FileInterface_Base::write(const char* str)
{
    const char* const fnName = "omw::io::FileInterface_Base::write";

    if (!str) throw std::invalid_argument(fnName);

    size_t len = 0;
    while ((str[len] != 0) && (len < OMW_SIZE_MAX)) ++len;

    write(str, len);
}

//! 
//! Allways starts writing at stream position 0.
//! 
//! \b Exceptions
//! - `std::invalid_argument` if data is _null_
//! - `std::out_of_range` if `count` is too big
//! - `std::ios::failure` thrown by
//!    - <tt><a href="https://en.cppreference.com/w/cpp/io/basic_ostream/seekp" target="_blank">std::ostream::seekp()</a></tt>
//!    - <tt><a href="https://en.cppreference.com/w/cpp/io/basic_ostream/write" target="_blank">std::ostream::write()</a></tt>
//! 
void omw::io::FileInterface_Base::write(const char* data, size_t count)
{
    const char* const fnName = "omw::io::FileInterface_Base::write";

    if (!data) throw std::invalid_argument(fnName);

    m_fs.seekp(0, std::ios::beg);

    std::streamsize sz;

    constexpr size_t streamSize = sizeof(std::streamsize);
    constexpr size_t sizeSize = sizeof(size_t);

    if (streamSize > sizeSize) sz = count;
    else if (streamSize == sizeSize)
    {
        constexpr size_t sizeMsb = 1 << ((sizeSize * 8) - 1);
        if (count && sizeMsb) throw std::out_of_range(fnName);
        sz = static_cast<std::streamsize>(count);
    }
    // should never happen by definition
    //else // streamSize < sizeSize
    //{
    //
    //}

    m_fs.write(data, sz);
}

//! 
//! Returns the state flags of the file stream.
//! 
//! See also <tt><a href="https://en.cppreference.com/w/cpp/io/basic_ios/rdstate" target="_blank">std::ios::rdstate()</a></tt>
//! and <tt><a href="https://en.cppreference.com/w/cpp/io/ios_base/iostate" target="_blank">std::ios::iostate</a></tt>.
//! 
omw::io::FileInterface_Base::iostate omw::io::FileInterface_Base::getState() const
{
    return m_fs.rdstate();
}



/*!
* \class omw::io::BinFileInterface
*
* `#include <omw/io/file.h>`
*
* Binary file interface.
*/

omw::io::BinFileInterface::BinFileInterface()
    : omw::io::FileInterface_Base()
{}

omw::io::BinFileInterface::BinFileInterface(const std::string& filename)
    : omw::io::FileInterface_Base(filename)
{}

omw::io::BinFileInterface::~BinFileInterface()
{}

void omw::io::BinFileInterface::read(uint8_t* buffer, size_t count) const
{
    FileInterface_Base::read(reinterpret_cast<char*>(buffer), count);
}

void omw::io::BinFileInterface::write(const uint8_t* data, size_t count)
{
    FileInterface_Base::write(reinterpret_cast<const char*>(data), count);
}











// something like omw::io::BinFile::read()
// 
// this->data; // of type omw::vector<uint8_t> 
// const size_t sz = omw::io::BinFileInterface::size();
// data.resize(sz, 0);
// omw::io::BinFileInterface::read(data.data(), sz);
// data.shrink_to_fit();
