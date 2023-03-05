/*
author          Oliver Blaser
date            01.03.2022
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
* The constness of the member functions is to let the file (because of this interface class) act like a C++ object.
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

//! @param mode Either `FileInterface_Base::rd` or `FileInterface_Base::wr`
//! 
//! \b Exceptions
//! - `fstream::failure` if an error occures
//! 
void omw::io::FileInterface_Base::open(openmode mode) const
{
    m_fs.open(m_filename, mode | std::ios::binary);
    if (getState() != good) throw fstream::failure("omw::io::FileInterface_Base::open");
}

/*!
* \fn omw::io::FileInterface_Base::openRead()
* 
* Opens the file in read mode.
* 
* \b Exceptions
* - `fstream::failure` if an error occures
*/

/*!
* \fn omw::io::FileInterface_Base::openWrite()
* 
* Opens the file in write mode.
* 
* \b Exceptions
* - `fstream::failure` if an error occures
*/

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
//! - `std::out_of_range` if the file is too big (file size can't be represented by `size_t`)
//! - `std::runtime_error` if the evaluated file size (`std::streampos`) was negative
//! - `std::ios::failure` thrown by
//!    - <tt><a href="https://en.cppreference.com/w/cpp/io/basic_istream/seekg" target="_blank">std::istream::seekg()</a></tt>
//!    - <tt><a href="https://en.cppreference.com/w/cpp/io/basic_istream/tellg" target="_blank">std::istream::tellg()</a></tt>
//! 
size_t omw::io::FileInterface_Base::size() const
{
    const char* const fnName = "omw::io::FileInterface_Base::size";

    m_fs.seekg(0, std::ios::end);
    const std::fstream::pos_type sposEnd = m_fs.tellg();



    // 
    // std::istream::pos_type => std::char_traits<char>::pos_type => std::streampos =>
    //      std::fpos<State> (which has an to std::streamoff conversion operator)
    // 
    // ==# MSW #==
    // https://docs.microsoft.com/en-us/cpp/standard-library/ios-typedefs
    // https://docs.microsoft.com/en-us/cpp/standard-library/fpos-class
    // x86: int32 // well, in fact it is also int64
    // x64: int64
    // 



    if (omw::io::streampos_to_streamoff(sposEnd) < 0) throw std::runtime_error(fnName);

    // // If the sizes would be the same, size_t could represent every positive value
    // // of std::istream::pos_type.
    // // 
    // // If std::istream::pos_type is grater than size_t, throw an exception if the
    // // value can not be represented by size_t.
    // // 
    // // If it's a negative value, an exception is thrown above.
    // // 
    // // 
    // // Can't use sizeof operator since std::streamsize is a class.
    // // 
    // // "if sizeof(std::streamsize) > sizeof(size_t)"
    // if (std::istream::pos_type(static_cast<size_t>(-1)) > 0)
    // {
    //     // if ifsPosEnd > size_t_max
    //     if (ifsPosEnd > std::istream::pos_type(static_cast<size_t>(-1)))
    //     {
    //         throw std::out_of_range(fnName);
    //     }
    // }

    size_t r;
    try { r = omw::io::streampos_to_size(sposEnd); }
    catch (...) { throw std::out_of_range(fnName); }

    return r;
}

//! 
//! Allways starts reading at stream position 0.
//! 
//! \b Exceptions
//! - `std::invalid_argument` if buffer is _null_
//! - `std::out_of_range` see `omw::io::size_to_streamsize()`
//! - `std::ios::failure` thrown by
//!    - <tt><a href="https://en.cppreference.com/w/cpp/io/basic_istream/seekg" target="_blank">std::istream::seekg()</a></tt>
//!    - <tt><a href="https://en.cppreference.com/w/cpp/io/basic_istream/read" target="_blank">std::istream::read()</a></tt>
//! 
void omw::io::FileInterface_Base::read(char* buffer, size_t count) const
{
    if (count) // needed on some platforms
    {
        const char* const fnName = "omw::io::FileInterface_Base::read";

        if (!buffer) throw std::invalid_argument(fnName);

        m_fs.seekg(0, std::ios::beg);

        const std::streamsize sz = omw::io::size_to_streamsize(count);
        m_fs.read(buffer, sz);
    }
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
    while ((str[len] != 0) && (len < omw::size_max)) ++len;

    write(str, len);
}

//! 
//! Allways starts writing at stream position 0.
//! 
//! \b Exceptions
//! - `std::invalid_argument` if data is _null_
//! - `std::out_of_range` see `omw::io::size_to_streamsize()`
//! - `std::ios::failure` thrown by
//!    - <tt><a href="https://en.cppreference.com/w/cpp/io/basic_ostream/seekp" target="_blank">std::ostream::seekp()</a></tt>
//!    - <tt><a href="https://en.cppreference.com/w/cpp/io/basic_ostream/write" target="_blank">std::ostream::write()</a></tt>
//! 
void omw::io::FileInterface_Base::write(const char* data, size_t count)
{
    if (count) // needed on some platforms
    {
        const char* const fnName = "omw::io::FileInterface_Base::write";

        if (!data) throw std::invalid_argument(fnName);

        m_fs.seekp(0, std::ios::beg);

        const std::streamsize sz = omw::io::size_to_streamsize(count);
        m_fs.write(data, sz);
    }
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

//! 
//! See `omw::io::FileInterface_Base::read()`.
//! 
void omw::io::BinFileInterface::read(uint8_t* buffer, size_t count) const
{
    FileInterface_Base::read(reinterpret_cast<char*>(buffer), count);
}

//! 
//! See `omw::io::FileInterface_Base::write(const char*, size_t)`.
//! 
void omw::io::BinFileInterface::write(const uint8_t* data, size_t count)
{
    FileInterface_Base::write(reinterpret_cast<const char*>(data), count);
}



//! 
//! \b Exceptions
//! - `std::out_of_range` if the value is too big to be represented by `std::streamsize` (usually never occures, because `std::streamsize` is defined as `long long` in most implementations)
//! 
std::streamsize omw::io::size_to_streamsize(size_t val)
{
    const char* const fnName = "omw::io::size_to_streamsize";

    std::streamsize r;

    // constexpr size_t streamSize = sizeof(std::streamsize);
    // constexpr size_t sizeSize = sizeof(size_t);
    // 
    // if (streamSize > sizeSize) r = static_cast<std::streamsize>(val);
    // else if (streamSize == sizeSize)
    // {
    //     r = static_cast<std::streamsize>(val);
    //     if (r < 0) throw std::out_of_range(fnName);
    // }
    // // should never happen by definition
    // //else // streamSize < sizeSize
    // //{
    // //
    // //}
    // 
    // since it never happens, we simply can do:

    r = static_cast<std::streamsize>(val);

    if (r < 0) // is only a problem if the sizes are equal
    {
        throw std::out_of_range(fnName);
    }

    return r;
}

//! 
//! \b Exceptions
//! - `std::invalid_argument` if the value is negative
//! - `std::out_of_range` if the value is too big to be represented by `size_t`
//! 
size_t omw::io::streampos_to_size(const std::streampos& val)
{
    const char* const fnName = "omw::io::streampos_to_size";

    const std::streamoff im = omw::io::streampos_to_streamoff(val); // intermediate value

    if (im < 0) throw std::invalid_argument(fnName);
    if (static_cast<uint64_t>(im) > static_cast<uint64_t>(omw::size_max)) throw std::out_of_range(fnName);

    return static_cast<size_t>(im);
}

/*!
* \fn omw::io::streampos_to_streamoff(const std::streampos& val)
* 
* The to `std::streamoff` conversion operator of the `std::streampos` class may be explicit.
* This function is a wrapper for the static cast from `std::streampos` to `std::streamoff`.
*/
