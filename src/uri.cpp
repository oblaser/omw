/*
author          Oliver Blaser
date            28.12.2025
copyright       MIT - Copyright (c) 2025 Oliver Blaser
*/

#include <cctype>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

#include "omw/defs.h"
#include "omw/string.h"
#include "omw/uri.h"

#if (OMW_CPPSTD >= OMW_CPPSTD_17)
#include <filesystem>
#endif



// explicitly unreserved characters
#define PERCENT_ENCODE_BASE_FILTER omw::isAlnum(*p) || (*p == '-') || (*p == '.') || (*p == '_') || (*p == '~')

// ok in authority, path, query and fragment
#define PERCENT_ENCODE_FILTER_GRP0                                                                                                                         \
    (*p == '+') || (*p == '!') || (*p == '$') || (*p == '&') || (*p == '\'') || (*p == '(') || (*p == ')') || (*p == '*') || (*p == ',') || (*p == ';') || \
        (*p == '=')

// ok in query key and value (and authority, path and fragment)
#define PERCENT_ENCODE_FILTER_GRP0A (*p == '!') || (*p == '$') || (*p == '\'') || (*p == '(') || (*p == ')') || (*p == '*') || (*p == ',') || (*p == ';')

// ok in path, query and fragment
#define PERCENT_ENCODE_FILTER_GRP1 (*p == ':') || (*p == '@') || (*p == '/')

// ok in path segment (and query and fragment)
#define PERCENT_ENCODE_FILTER_GRP1A (*p == ':') || (*p == '@')

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
std::string omw::URI::encodeScheme(const std::string& str) { IMPL_PERCENT_ENCODE(PERCENT_ENCODE_BASE_FILTER || (*p == '+')); }
std::string omw::URI::encodeAuthority(const std::string& str) { IMPL_PERCENT_ENCODE(PERCENT_ENCODE_BASE_FILTER || PERCENT_ENCODE_FILTER_GRP0); }
std::string omw::URI::encodePath(const std::string& str)
{
    IMPL_PERCENT_ENCODE(PERCENT_ENCODE_BASE_FILTER || PERCENT_ENCODE_FILTER_GRP0 || PERCENT_ENCODE_FILTER_GRP1);
}
std::string omw::URI::encodePathSegment(const std::string& str)
{
    IMPL_PERCENT_ENCODE(PERCENT_ENCODE_BASE_FILTER || PERCENT_ENCODE_FILTER_GRP0 || PERCENT_ENCODE_FILTER_GRP1A);
}
std::string omw::URI::encodeQuery(const std::string& str)
{
    IMPL_PERCENT_ENCODE(PERCENT_ENCODE_BASE_FILTER || PERCENT_ENCODE_FILTER_GRP0 || PERCENT_ENCODE_FILTER_GRP1 || (*p == '?'));
}
std::string omw::URI::encodeQueryField(const std::string& str)
{
    IMPL_PERCENT_ENCODE(PERCENT_ENCODE_BASE_FILTER || PERCENT_ENCODE_FILTER_GRP0A || PERCENT_ENCODE_FILTER_GRP1 || (*p == '?'));
}
std::string omw::URI::encodeFragment(const std::string& str)
{
    IMPL_PERCENT_ENCODE(PERCENT_ENCODE_BASE_FILTER || PERCENT_ENCODE_FILTER_GRP0 || PERCENT_ENCODE_FILTER_GRP1 || (*p == '?'));
}



void omw::URI::Authority::parse(const std::string& str_encoded)
{
    const char* p = str_encoded.c_str();
    const char* const pEnd = p + str_encoded.length();

    clear();
    m_validity = true;

    if (omw::contains(str_encoded, '@'))
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

        static_assert(sizeof(m_port) >= 2, "port member type has to be at least 16bit wide");

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
    m_user = omw::URI::decode(m_user);
    m_pass = omw::URI::decode(m_pass);
    m_host = omw::URI::decode(m_host);
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

std::string omw::URI::Authority::serialise() const
{
    std::string r;

    if (!m_user.empty()) { r += omw::URI::encodeAuthority(m_user); }
    if (!m_pass.empty()) { r += ':' + omw::URI::encodeAuthority(m_pass); }
    if (!r.empty()) { r += '@'; }

    if (m_isIPv6) { r += m_host; }
    else { r += omw::URI::encodeAuthority(m_host); }

    if (m_port >= 0) { r += ':' + omw::toString(m_port); }

    return r;
}



void omw::URI::Path::parse(const std::string& str_encoded)
{
    const char* p = str_encoded.c_str();
    const char* const pEnd = p + str_encoded.length();

    clear();

    if (*p == '/')
    {
        m_isAbs = true;
        ++p;
    }
    else { m_isAbs = false; }

    std::string segmentStr;

    while (p < pEnd)
    {
        if (*p != '/') { segmentStr.push_back(*p); }
        else
        {
            m_segments.push_back(omw::URI::PathSegment(segmentStr));
            segmentStr.clear();
        }

        ++p;
    }

    if (m_isAbs || !segmentStr.empty()) { m_segments.push_back(omw::URI::PathSegment(segmentStr)); }
}

void omw::URI::Path::parse(const char* str_encoded)
{
    if (str_encoded) { this->parse(std::string(str_encoded)); }
    else { this->clear(); }
}

#if (OMW_CPPSTD >= OMW_CPPSTD_17)

void omw::URI::Path::set(const std::filesystem::path& path)
{
#if 1 // use omw::split()

#if OMW_PLAT_WIN
    constexpr char segmentDelimiter = '\\';
#else
    constexpr char segmentDelimiter = '/';
#endif

    clear();

    std::string pathString = path.u8string();

    m_isAbs = (!pathString.empty() && (pathString[0] == segmentDelimiter));

    if (!pathString.empty())
    {
        const auto segments = omw::split(pathString.substr(m_isAbs ? 1 : 0), segmentDelimiter);

        for (size_t i = 0; i < segments.size(); ++i)
        {
            PathSegment tmp;
            tmp.set(segments[i]);

            m_segments.push_back(tmp);
        }
    }

#else // use fs::path utility

    clear();

    const bool hasRootName = path.has_root_name();
    const std::string rootDir = path.root_directory();

    m_isAbs = (((rootDir == "/") || (rootDir == "\\")) && // is effectively absolute
               !hasRootName                               // but absolute paths with a root name are treated as relative
    );                                                    // by the internal `m_isAbs` logic

    auto consume = path;
    while (!consume.empty())
    {
#error "not finished implementing"

        PathSegment tmp;
        tmp.set(consume.filename().u8string());

        m_segments.insert(m_segments.begin(), tmp);

        consume = consume.parent_path();
    }

    if (hasRootName)
    {
        PathSegment tmp;
        tmp.set(path.root_name().u8string());

        m_segments.insert(m_segments.begin(), tmp);
    }
#endif // implementation variant
}

#endif // C++17

std::string omw::URI::Path::serialise() const
{
    std::string r;

    if (m_isAbs) { r += '/'; }

    for (size_t i = 0; i < m_segments.size(); ++i)
    {
        if (i != 0) { r += '/'; }
        r += m_segments[i].serialise();
    }

    return r;
}

#if (OMW_CPPSTD >= OMW_CPPSTD_17)

std::filesystem::path omw::URI::Path::toStdPath() const
{
    std::filesystem::path path;

    if (m_segments.empty())
    {
        if (m_isAbs) { path = "/"; }
        // else nop
    }
    else
    {
        if (m_isAbs) { path = "/" + m_segments[0].data(); }
        else { path = m_segments[0].data(); }

        for (size_t i = 1; i < m_segments.size(); ++i) { path /= m_segments[i].data(); }
    }

    return path;
}

#endif // C++17



void omw::URI::QueryParameter::parse(const std::string& str_encoded)
{
    const char* p = str_encoded.c_str();
    const char* const pEnd = p + str_encoded.length();

    clear();

    // copy key
    while (p < pEnd)
    {
        if (*p != '=')
        {
            m_key.push_back(*p == '+' ? 0x20 : *p);
            ++p;
        }
        else { break; }
    }

    // if present, copy value
    if (*p == '=')
    {
        ++p; // skip fragment delimiter

        while (p < pEnd)
        {
            m_value.push_back(*p == '+' ? 0x20 : *p);
            ++p;
        }
    }

    // could be implemented inline above
    m_key = omw::URI::decode(m_key);
    m_value = omw::URI::decode(m_value);
}

std::string omw::URI::QueryParameter::serialise() const
{
    std::string r = omw::URI::encodeQueryField(m_key);

    if (!m_value.empty()) { r += '=' + omw::URI::encodeQueryField(m_value); }

    return r;
}



void omw::URI::Query::parse(const std::string& str_encoded)
{
    const char* p = str_encoded.c_str();
    const char* const pEnd = p + str_encoded.length();

    clear();

    std::string parameterStr;

    while (p < pEnd)
    {
        if (*p != '&') { parameterStr.push_back(*p); }
        else
        {
            m_parameters.push_back(omw::URI::QueryParameter(parameterStr));
            parameterStr.clear();
        }

        ++p;
    }

    if (!parameterStr.empty()) { m_parameters.push_back(omw::URI::QueryParameter(parameterStr)); }
}

std::string omw::URI::Query::serialise() const
{
    std::string r;

    for (size_t i = 0; i < m_parameters.size(); ++i)
    {
        if (i != 0) { r += '&'; }
        r += m_parameters[i].serialise();
    }

    return r;
}



void omw::URI::parse(const std::string& uri_encoded)
{
    const char* p = uri_encoded.c_str();
    const char* const pEnd = p + uri_encoded.length();

    clear();

    // copy scheme and make canonical
    while (p < pEnd)
    {
        if (*p != ':')
        {
            m_scheme.push_back(*p);
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

        m_authority = omw::URI::Authority(authorityStr);
    }

    // copy path, skip if empty
    {
        std::string pathStr;

        while (p < pEnd)
        {
            if ((*p != '?') && (*p != '#'))
            {
                pathStr.push_back(*p);
                ++p;
            }
            else { break; }
        }

        m_path = omw::URI::Path(pathStr);
    }

    // if present, copy querry
    if (*p == '?')
    {
        ++p; // skip querry delimiter

        std::string queryStr;

        while (p < pEnd)
        {
            if (*p != '#')
            {
                queryStr.push_back(*p);
                ++p;
            }
            else { break; }
        }

        m_query = omw::URI::Query(queryStr);
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
    m_scheme = omw::URI::decode(m_scheme);
    m_fragment = omw::URI::decode(m_fragment);

    m_check();
}

void omw::URI::parse(const char* uri_encoded)
{
    if (uri_encoded) { this->parse(std::string(uri_encoded)); }
    else { this->clear(); }
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

void omw::URI::setScheme(const std::string& scheme_decoded)
{
    m_scheme = scheme_decoded;
    m_check();
}

void omw::URI::setAuthority(const omw::URI::Authority& authority)
{
    m_authority = authority;
    m_check();
}

void omw::URI::setUser(const std::string& user)
{
    m_authority.setUser(user);
    m_check();
}

void omw::URI::setPass(const std::string& pass)
{
    m_authority.setPass(pass);
    m_check();
}

void omw::URI::setHost(const std::string& host)
{
    m_authority.setHost(host);
    m_check();
}

void omw::URI::setPort(int port)
{
    m_authority.setPort(port);
    m_check();
}

void omw::URI::setPath(const omw::URI::Path& path)
{
    m_path = path;
    m_check();
}

#if (OMW_CPPSTD >= OMW_CPPSTD_17) || defined(OMWi_DOXYGEN_PREDEFINE)

void omw::URI::setPath(const std::filesystem::path& path)
{
    m_path = omw::URI::Path(path);
    m_check();
}

#endif

void omw::URI::setQuery(const omw::URI::Query& query)
{
    m_query = query;
    m_check();
}

void omw::URI::setFragment(const std::string& fragment_decoded)
{
    m_fragment = fragment_decoded;
    m_check();
}

void omw::URI::addQueryParameter(const omw::URI::QueryParameter& parameter)
{
    m_query.add(parameter);
    m_check();
}

void omw::URI::addQueryParameter(const std::string& key, const std::string& value)
{
    m_query.add(key, value);
    m_check();
}

std::string omw::URI::serialise() const
{
    std::string r;

    r = omw::URI::encodeScheme(m_scheme) + ':';
    if (!m_authority.empty() || (m_scheme == "file")) { r += "//" + m_authority.serialise(); }
    r += m_path.serialise();
    if (!m_query.empty()) { r += '?' + m_query.serialise(); }
    if (!m_fragment.empty()) { r += '#' + omw::URI::encodeFragment(m_fragment); }

    return r;
}

void omw::URI::m_check()
{
    m_validity = true;



    if (m_scheme.empty()) { m_validity = false; }
    else
    {
        // scheme must start with a letter
        if (!omw::isAlpha(m_scheme[0])) { m_validity = false; }

        for (const auto& c : m_scheme)
        {
            if (!isSchemeChar(c)) { m_validity = false; }
        }
    }



    const std::string path = m_path.serialise();

    // if an authority is specified the path must start with `/`
    if (!m_authority.empty() && !path.empty() && (path[0] != '/')) { m_validity = false; }

    // if no authority is specified the path must not start with `//`
    if (m_authority.empty() && !path.empty() && (path.substr(0, 2) == "//")) { m_validity = false; }
}
