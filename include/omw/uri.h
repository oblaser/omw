/*
author          Oliver Blaser
date            09.06.2025
copyright       MIT - Copyright (c) 2025 Oliver Blaser
*/

#ifndef IG_OMW_URI_H
#define IG_OMW_URI_H

#include <cstdint>
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
 * - detection IPv6 in authority is done by simply checking front and back for the brackets without the actual IP string
 * - path segments containing `/` or `%2F`, path class needed similar to `URI::Authority`
 * - querry keys or values containing reserved characters, querry class needed similar to `URI::Authority`
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
    class Authority
    {
    public:
        Authority()
            : m_validity(false), m_isIPv6(false), m_user(), m_pass(), m_host(), m_port(-1)
        {}

        Authority(const char* str)
            : m_validity(false), m_isIPv6(false), m_user(), m_pass(), m_host(), m_port(-1)
        {
            parse(str);
        }

        Authority(const std::string& str)
            : m_validity(false), m_isIPv6(false), m_user(), m_pass(), m_host(), m_port(-1)
        {
            parse(str);
        }

        virtual ~Authority() {}

        void parse(const std::string& str);
        void clear();

        const std::string& user() const { return m_user; }
        const std::string& pass() const { return m_pass; }
        const std::string& host() const { return m_host; }
        uint16_t port() const { return (uint16_t)m_port; }

        bool hasUserinfo() const { return (!m_user.empty() || !m_pass.empty()); }
        bool hasPort() const { return (m_port >= 0); }
        bool empty() const { return (!hasUserinfo() && m_host.empty() && !hasPort()); }

        void setUser(const std::string& user) { m_user = user; }
        void setPass(const std::string& pass) { m_pass = pass; }
        void setHost(const std::string& host);
        void setPort(int port) { m_port = port; }

        /**
         * @brief Serialize the percent encoded URI.
         */
        std::string string() const;

        bool isValid() const { return m_validity; }

    private:
        bool m_validity;
        bool m_isIPv6;
        std::string m_user;
        std::string m_pass;
        std::string m_host;
        int m_port; // negative to denote not set
    };



public:
    URI()
        : m_validity(false), m_scheme(), m_authority(), m_path(), m_query(), m_fragment()
    {}

    URI(const char* uri)
        : m_validity(false), m_scheme(), m_authority(), m_path(), m_query(), m_fragment()
    {
        parse(uri);
    }

    URI(const std::string& uri)
        : m_validity(false), m_scheme(), m_authority(), m_path(), m_query(), m_fragment()
    {
        parse(uri);
    }

    virtual ~URI() {}

    void parse(const std::string& uri);
    void clear();

    const std::string& scheme() const { return m_scheme; }
    const omw::URI::Authority& authority() const { return m_authority; }
    const std::string& path() const { return m_path; }
    const std::string& query() const { return m_query; }
    const std::string& fragment() const { return m_fragment; }

    void setScheme(const std::string& scheme);

    void setAuthority(const omw::URI::Authority& authority) { m_authority = authority; }
    void setUser(const std::string& user) { m_authority.setUser(user); }
    void setPass(const std::string& pass) { m_authority.setPass(pass); }
    void setHost(const std::string& host) { m_authority.setHost(host); }
    void setPort(int port) { m_authority.setPort(port); }

    void setPath(const std::string& path) { m_path = path; }
    void setQuery(const std::string& query) { m_query = query; }
    void setFragment(const std::string& fragment) { m_fragment = fragment; }

    /**
     * @brief Serialize the percent encoded URI.
     */
    std::string string() const;

    bool isValid() const { return (m_validity && (m_authority.isValid() || m_authority.empty())); }

private:
    bool m_validity;
    std::string m_scheme;
    omw::URI::Authority m_authority;
    std::string m_path;
    std::string m_query;
    std::string m_fragment;
};



/*! @} */

} // namespace omw


#endif // IG_OMW_URI_H
