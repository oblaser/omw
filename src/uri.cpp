/*
author          Oliver Blaser
date            09.06.2025
copyright       MIT - Copyright (c) 2025 Oliver Blaser
*/

#include <cctype>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

#include "omw/string.h"
#include "omw/uri.h"


// explicitly unreserved characters
#define PERCENT_ENCODE_BASE_FILTER omw::isAlnum(*p) || (*p == '-') || (*p == '.') || (*p == '_') || (*p == '~')

// ok in authority, path, query and fragment
#define PERCENT_ENCODE_FILTER_GRP0                                                                                                                         \
    (*p == '+') || (*p == '!') || (*p == '$') || (*p == '&') || (*p == '\'') || (*p == '(') || (*p == ')') || (*p == '*') || (*p == ',') || (*p == ';') || \
        (*p == '=')

// ok in path, query and fragment
#define PERCENT_ENCODE_FILTER_GRP1 (*p == ':') || (*p == '@') || (*p == '/')

#define IMPL_PERCENT_ENCODE(_nenc_filter)            \
    const char* p = str.c_str();                     \
    const char* const pEnd = p + str.length();       \
    std::string r;                                   \
    r.reserve(str.length() * 2);                     \
    while (p < pEnd)                                 \
    {                                                \
        if ((_nenc_filter))                          \
        {                                            \
            r.push_back(*p);                         \
            ++p;                                     \
        }                                            \
        else                                         \
        {                                            \
            r += '%' + omw::toHexStr((uint8_t)(*p)); \
            ++p;                                     \
        }                                            \
    }                                                \
    r.shrink_to_fit();                               \
    return r
// end IMPL_PERCENT_ENCODE



static bool isSchemeChar(char c) { return (omw::isAlnum(c) || (c == '+') || (c == '.') || (c == '-')); }
static inline bool isIPv6(const std::string& host) { return ((host.front() == '[') && (host.back() == ']')); }

static std::string encodeScheme(const std::string& str) { IMPL_PERCENT_ENCODE(PERCENT_ENCODE_BASE_FILTER || (*p == '+')); }
static std::string encodeAuthority(const std::string& str) { IMPL_PERCENT_ENCODE(PERCENT_ENCODE_BASE_FILTER || PERCENT_ENCODE_FILTER_GRP0); }
static std::string encodePath(const std::string& str)
{
    IMPL_PERCENT_ENCODE(PERCENT_ENCODE_BASE_FILTER || PERCENT_ENCODE_FILTER_GRP0 || PERCENT_ENCODE_FILTER_GRP1);
}
static std::string encodeQuery(const std::string& str)
{
    IMPL_PERCENT_ENCODE(PERCENT_ENCODE_BASE_FILTER || PERCENT_ENCODE_FILTER_GRP0 || PERCENT_ENCODE_FILTER_GRP1 || (*p == '?'));
}
static std::string encodeFragment(const std::string& str)
{
    IMPL_PERCENT_ENCODE(PERCENT_ENCODE_BASE_FILTER || PERCENT_ENCODE_FILTER_GRP0 || PERCENT_ENCODE_FILTER_GRP1 || (*p == '?'));
}



std::string omw::URI::decode(const std::string& str)
{
    const char* p = str.c_str();
    const char* const pEnd = p + str.length();

    std::string r;
    r.reserve(str.length());

    while (p < pEnd)
    {
        if ((*p == '%') && ((pEnd - p) >= 3) && omw::isHex(*(p + 1)) && omw::isHex(*(p + 2)))
        {
            r.push_back((char)omw::hexstoi(std::string(p + 1, 2)));
            p += 3;
        }
        else
        {
            r.push_back(*p);
            ++p;
        }
    }

    return r;
}

std::string omw::URI::encode(const std::string& str) { IMPL_PERCENT_ENCODE(PERCENT_ENCODE_BASE_FILTER); }



void omw::URI::Authority::parse(const std::string& str)
{
    const char* p = str.c_str();
    const char* const pEnd = p + str.length();

    clear();
    m_validity = true;

    if (omw::contains(str, '@'))
    {
        // copy username
        while (p < pEnd)
        {
            if ((*p != ':') && (*p != '@'))
            {
                m_user.push_back(*p);
                ++p;
            }
            else { break; }
        }

        // if present, copy password
        if (*p == ':')
        {
            ++p; // skip password delimiter

            while (p < pEnd)
            {
                if (*p != '@')
                {
                    m_pass.push_back(*p);
                    ++p;
                }
                else { break; }
            }
        }

        ++p; // skip userinfo delimiter
    }

    // copy host
    if (*p != '[') // not IPv6
    {
        while (p < pEnd)
        {
            if (*p != ':')
            {
                m_host.push_back(*p);
                ++p;
            }
            else { break; }
        }

        m_isIPv6 = false;
    }
    else // IPv6
    {
        while (p < pEnd)
        {
            if (*p != ']')
            {
                m_host.push_back(*p);
                ++p;
            }
            else { break; }
        }

        if (*p == ']')
        {
            m_host.push_back(*p);
            ++p;

            m_isIPv6 = true;
        }
        else { m_validity = false; }
    }

    // if present, parse port
    if (*p == ':')
    {
        ++p; // skip port delimiter

        std::string portStr;

        while (p < pEnd)
        {
            portStr.push_back(*p);
            ++p;
        }

        try
        {
            m_port = std::stoi(portStr);
            if (!omw::isUInteger(portStr) || (m_port > UINT16_MAX)) { throw -(__LINE__); }
        }
        catch (...)
        {
            m_validity = false;
            m_port = -1;
        }
    }

    // could be implemented inline above, would improve readability of the results because special cases can be covered better
    m_user = URI::decode(m_user);
    m_pass = URI::decode(m_pass);
    m_host = URI::decode(m_host);
}

void omw::URI::Authority::clear()
{
    m_validity = false;
    m_isIPv6 = false;

    m_user.clear();
    m_pass.clear();
    m_host.clear();
    m_port = -1;
}

void omw::URI::Authority::setHost(const std::string& host)
{
    m_isIPv6 = isIPv6(host);
    m_host = host;
}

std::string omw::URI::Authority::string() const
{
    std::string r;

    if (!m_user.empty()) { r += encodeAuthority(m_user); }
    if (!m_pass.empty()) { r += ':' + encodeAuthority(m_pass); }
    if (!r.empty()) { r += '@'; }

    if (m_isIPv6) { r += m_host; }
    else { r += encodeAuthority(m_host); }

    if (m_port >= 0) { r += ':' + omw::toString(m_port); }

    return r;
}



void omw::URI::parse(const std::string& uri)
{
    const char* p = uri.c_str();
    const char* const pEnd = p + uri.length();

    clear();
    m_validity = omw::isAlpha(*p); // scheme must start with a letter

    // copy scheme and make canonical
    while (p < pEnd)
    {
        if (*p != ':')
        {
            m_validity &= isSchemeChar(*p);
            m_scheme.push_back(std::tolower((unsigned char)(*p)));
            ++p;
        }
        else
        {
            ++p; // skip scheme delimiter
            break;
        }
    }

    // if present, copy authority
    if (((pEnd - p) >= 2) && (std::strncmp(p, "//", 2) == 0))
    {
        p += 2; // skip authority delimiter

        std::string authorityStr;

        while (p < pEnd)
        {
            if (*p != '/')
            {
                authorityStr.push_back(*p);
                ++p;
            }
            else { break; }
        }

        m_authority = authorityStr;
    }

    // copy path, skip if empty
    while (p < pEnd)
    {
        if ((*p != '?') && (*p != '#'))
        {
            m_path.push_back(*p);
            ++p;
        }
        else { break; }
    }

    // if present, copy querry
    if (*p == '?')
    {
        ++p; // skip querry delimiter

        while (p < pEnd)
        {
            if (*p != '#')
            {
                m_query.push_back(*p);
                ++p;
            }
            else { break; }
        }
    }

    // if present, copy fragment
    if (*p == '#')
    {
        ++p; // skip fragment delimiter

        while (p < pEnd)
        {
            m_fragment.push_back(*p);
            ++p;
        }
    }

    // could be implemented inline above, would improve readability of the results because special cases can be covered better
    m_scheme = URI::decode(m_scheme);
    m_path = URI::decode(m_path);
    m_query = URI::decode(m_query);
    m_fragment = URI::decode(m_fragment);
}

void omw::URI::clear()
{
    m_validity = false;

    m_scheme.clear();
    m_authority.clear();
    m_path.clear();
    m_query.clear();
    m_fragment.clear();
}

void omw::URI::setScheme(const std::string& scheme) { m_scheme = omw::toLower_ascii(scheme); }

std::string omw::URI::string() const
{
    std::string r;

    r = encodeScheme(m_scheme) + ':';
    if (!m_authority.empty() || (m_scheme == "file")) { r += "//" + m_authority.string(); }
    r += encodePath(m_path);
    if (!m_query.empty()) { r += '?' + encodeQuery(m_query); }
    if (!m_fragment.empty()) { r += '#' + encodeFragment(m_fragment); }

    return r;
}
