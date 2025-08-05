/*
author          Oliver Blaser
date            09.06.2025
copyright       MIT - Copyright (c) 2025 Oliver Blaser
*/

#ifndef IG_OMW_URI_H
#define IG_OMW_URI_H

#include <string>


namespace omw {

/*! \addtogroup grp_utility_gpUtil
 * @{
 */

/**
 * @class omw::URI
 * @brief Uniform Resource Identifier
 *
 * `#include <omw/uri.h>`
 *
 * Basic URI implementation. Performs percent-decoding after parsing components, and percent-encoding while serializing.
 * Some cases are not properly handled:
 * - userinfo in authority
 * - IPv6 in authority
 * - path segments containing `/` or `%2F`
 *
 * Getters and setters operate in decoded mode.
 *
 * The parser makes the scheme canonical.
 */
class URI
{
public:
    /**
     * @brief Decodes a percent-encoded string.
     */
    static std::string decode(const std::string& str);

    /**
     * @brief Encodes a string using percent-encoding.
     *
     * Encodes any character but the explicitly unreserved. These beeing letters, digits, `-`, `.`, `_` and `~`.
     */
    static std::string encode(const std::string& str);

public:
    URI()
        : m_validity(false), m_scheme(), m_authority(), m_path(), m_query(), m_fragment()
    {}

    URI(const char* uri)
        : m_validity(false), m_scheme(), m_authority(), m_path(), m_query(), m_fragment()
    {
        set(uri);
    }

    URI(const std::string& uri)
        : m_validity(false), m_scheme(), m_authority(), m_path(), m_query(), m_fragment()
    {
        set(uri);
    }

    virtual ~URI() {}

    void set(const std::string& uri);
    void clear();

    const std::string& scheme() const { return m_scheme; }
    const std::string& authority() const { return m_authority; }
    const std::string& path() const { return m_path; }
    const std::string& query() const { return m_query; }
    const std::string& fragment() const { return m_fragment; }

    void setScheme(const std::string& scheme);
    void setAuthority(const std::string& authority) { m_authority = authority; }
    void setPath(const std::string& path) { m_path = path; }
    void setQuery(const std::string& query) { m_query = query; }
    void setFragment(const std::string& fragment) { m_fragment = fragment; }

    /**
     * @brief Serialize the percent encoded URI.
     */
    std::string string() const;

    bool isValid() const { return m_validity; }

private:
    bool m_validity;
    std::string m_scheme;
    std::string m_authority;
    std::string m_path;
    std::string m_query;
    std::string m_fragment;
};



/*! @} */

} // namespace omw


#endif // IG_OMW_URI_H
