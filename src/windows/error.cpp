/*
author      Oliver Blaser
date        13.08.2021
copyright   MIT - Copyright (c) 2021 Oliver Blaser
*/

#include "omw/windows/error.h"

#ifdef OMW_PLAT_WIN

//! @brief Default ctor.
//! 
//! Initializes the code with `0` and the message string with `OK`.
//! 
omw::windows::ErrorCode::ErrorCode()
    : errorCode(0), errorMsg(OMWi_DISPSTR("OK"))
{
}

//! @brief Ctor to initialize the attributes.
//! @param code The actual error code
//! @param message The codes message string
omw::windows::ErrorCode::ErrorCode(int code, const std::string& message)
    : errorCode(code), errorMsg(message)
{
}

omw::windows::ErrorCode::~ErrorCode()
{
}

//! @brief Getter for the error code.
//! @return The error code
int omw::windows::ErrorCode::code() const
{
    return errorCode;
}

//! @brief Getter for the message.
//! @return  Message string
const std::string& omw::windows::ErrorCode::msg() const
{
    return errorMsg;
}

//! @brief 
//! @return  `true` if `code() == omw::windows::EC_OK`
//! 
bool omw::windows::ErrorCode::good() const
{
    return (code() == omw::windows::EC_OK);
}

std::string omw::windows::ErrorCode::toString() const
{
    return std::to_string(code()) + OMWi_DISPSTR(" - ") + msg();
}

std::ostream& omw::windows::operator<<(std::ostream& os, const ErrorCode& ec)
{
    os << ec.toString();
    return os;
}

#endif // OMW_PLAT_WIN
