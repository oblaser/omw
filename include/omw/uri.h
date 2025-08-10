/*
author          Oliver Blaser
date            09.06.2025
copyright       MIT - Copyright (c) 2025 Oliver Blaser
*/

#ifndef IG_OMW_URI_H
#define IG_OMW_URI_H

#include <cstdint>
#include <string>
#include <vector>


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
 * - querry only supports delimiter `&`, not `;`
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

    static std::string encodeScheme(const std::string& str);
    static std::string encodeAuthority(const std::string& str);
    static std::string encodePath(const std::string& str);
    static std::string encodePathSegment(const std::string& str);
    static std::string encodeQuery(const std::string& str);
    static std::string encodeQueryField(const std::string& str);
    static std::string encodeFragment(const std::string& str);

public:
    class Authority
    {
    public:
        Authority()
            : m_validity(false), m_isIPv6(false), m_user(), m_pass(), m_host(), m_port(-1)
        {}

        explicit Authority(const char* str_encoded)
            : m_validity(false), m_isIPv6(false), m_user(), m_pass(), m_host(), m_port(-1)
        {
            this->parse(str_encoded);
        }

        explicit Authority(const std::string& str_encoded)
            : m_validity(false), m_isIPv6(false), m_user(), m_pass(), m_host(), m_port(-1)
        {
            this->parse(str_encoded);
        }

        virtual ~Authority() {}

        void parse(const std::string& str_encoded);
        void clear();

        const std::string& user() const { return m_user; }
        const std::string& pass() const { return m_pass; }
        const std::string& host() const { return m_host; }
        uint16_t port() const { return (uint16_t)m_port; }

        bool hasUserinfo() const { return (!m_user.empty() || !m_pass.empty()); }
        bool hasPort() const { return (m_port >= 0); }
        bool empty() const { return (!hasUserinfo() && m_host.empty() && !hasPort()); }

        void setUser(const std::string& user_decoded) { m_user = user_decoded; }
        void setPass(const std::string& pass_decoded) { m_pass = pass_decoded; }
        void setHost(const std::string& host_decoded);
        void setPort(int port) { m_port = port; }

        /**
         * Serialise the percent encoded authority string.
         */
        std::string serialise() const;

        bool isValid() const { return m_validity; }

    private:
        bool m_validity;
        bool m_isIPv6;
        std::string m_user;
        std::string m_pass;
        std::string m_host;
        int m_port; // negative to denote not set
    };

    class PathSegment
    {
    public:
        PathSegment()
            : m_data()
        {}

        explicit PathSegment(const char* str_encoded)
            : m_data()
        {
            this->parse(str_encoded);
        }

        explicit PathSegment(const std::string& str_encoded)
            : m_data()
        {
            this->parse(str_encoded);
        }

        virtual ~PathSegment() {}

        void parse(const std::string& str_encoded) { m_data = omw::URI::decode(str_encoded); }
        void clear() { m_data.clear(); }

        const std::string& data() const { return m_data; }
        std::string& data() { return m_data; }

        bool empty() const { return m_data.empty(); }

        void set(const std::string& data_decoded) { m_data = data_decoded; }

        /**
         * Serialise the percent encoded path segment.
         */
        std::string serialise() const { return omw::URI::encodePathSegment(m_data); }

    private:
        std::string m_data;
    };

    class Path
    {
    public:
        Path()
            : m_isAbs(false), m_segments()
        {}

        explicit Path(const char* str_encoded)
            : m_isAbs(false), m_segments()
        {
            this->parse(str_encoded);
        }

        explicit Path(const std::string& str_encoded)
            : m_isAbs(false), m_segments()
        {
            this->parse(str_encoded);
        }

        virtual ~Path() {}

        void parse(const std::string& str_encoded);

        void clear()
        {
            m_isAbs = false;
            m_segments.clear();
        }

        const std::vector<omw::URI::PathSegment>& segments() const { return m_segments; }
        std::vector<omw::URI::PathSegment>& segments() { return m_segments; }

        bool empty() const { return (m_segments.empty() || ((m_segments.size() == 1) && (m_segments[0].empty()))); }

        /**
         * Serialise the percent encoded path.
         */
        std::string serialise() const;

    private:
        bool m_isAbs;
        std::vector<omw::URI::PathSegment> m_segments;
    };

    class QueryParameter
    {
    public:
        QueryParameter()
            : m_key(), m_value()
        {}

        explicit QueryParameter(const char* str_encoded)
            : m_key(), m_value()
        {
            this->parse(str_encoded);
        }

        explicit QueryParameter(const std::string& str_encoded)
            : m_key(), m_value()
        {
            this->parse(str_encoded);
        }

        QueryParameter(const std::string& key_decoded, const std::string& value_decoded)
            : m_key(key_decoded), m_value(value_decoded)
        {}

        virtual ~QueryParameter() {}

        void parse(const std::string& str_encoded);
        void clear()
        {
            m_key.clear();
            m_value.clear();
        }

        const std::string& key() const { return m_key; }
        const std::string& value() const { return m_value; }

        void setKey(const std::string& key_decoded) { m_key = key_decoded; }
        void setValue(const std::string& value_decoded) { m_value = value_decoded; }
        void set(const std::string& key_decoded, const std::string& value_decoded)
        {
            m_key = key_decoded;
            m_value = value_decoded;
        }

        /**
         * Serialise the percent encoded key value pair.
         */
        std::string serialise() const;

    private:
        std::string m_key;
        std::string m_value;
    };

    class Query
    {
    public:
        Query()
            : m_parameters()
        {}

        explicit Query(const char* str_encoded)
            : m_parameters()
        {
            this->parse(str_encoded);
        }

        explicit Query(const std::string& str_encoded)
            : m_parameters()
        {
            this->parse(str_encoded);
        }

        Query(const std::vector<omw::URI::QueryParameter>& parameters)
            : m_parameters(parameters)
        {}

        virtual ~Query() {}

        void parse(const std::string& str_encoded);
        void clear() { m_parameters.clear(); }

        void set(const std::vector<omw::URI::QueryParameter>& parameters) { m_parameters = parameters; }
        void set(const omw::URI::QueryParameter& parameter) { m_parameters = { parameter }; }
        void set(const std::string& key, const std::string& value) { m_parameters = { omw::URI::QueryParameter(key, value) }; }

        void add(const omw::URI::QueryParameter& parameter) { m_parameters.push_back(parameter); }
        void add(const std::string& key, const std::string& value) { m_parameters.push_back(omw::URI::QueryParameter(key, value)); }

        const std::vector<omw::URI::QueryParameter>& parameters() const { return m_parameters; }
        std::vector<omw::URI::QueryParameter>& parameters() { return m_parameters; }

        bool empty() const { return m_parameters.empty(); }

        /**
         * Serialise the percent encoded query string.
         */
        std::string serialise() const;

    private:
        std::vector<omw::URI::QueryParameter> m_parameters;
    };



public:
    URI()
        : m_validity(false), m_scheme(), m_authority(), m_path(), m_query(), m_fragment()
    {}

    URI(const char* uri_encoded)
        : m_validity(false), m_scheme(), m_authority(), m_path(), m_query(), m_fragment()
    {
        parse(uri_encoded);
    }

    URI(const std::string& uri_encoded)
        : m_validity(false), m_scheme(), m_authority(), m_path(), m_query(), m_fragment()
    {
        parse(uri_encoded);
    }

    virtual ~URI() {}

    void parse(const std::string& uri_encoded);
    void clear();

    const std::string& scheme() const { return m_scheme; }
    void setScheme(const std::string& scheme_decoded);

    omw::URI::Authority& authority() { return m_authority; }
    const omw::URI::Authority& authority() const { return m_authority; }
    void setAuthority(const omw::URI::Authority& authority) { m_authority = authority; }
    void setUser(const std::string& user) { m_authority.setUser(user); }
    void setPass(const std::string& pass) { m_authority.setPass(pass); }
    void setHost(const std::string& host) { m_authority.setHost(host); }
    void setPort(int port) { m_authority.setPort(port); }

    omw::URI::Path& path() { return m_path; }
    const omw::URI::Path& path() const { return m_path; }
    void setPath(const omw::URI::Path& path) { m_path = path; }

    omw::URI::Query& query() { return m_query; }
    const omw::URI::Query& query() const { return m_query; }
    void setQuery(const omw::URI::Query& query) { m_query = query; }

    const std::string& fragment() const { return m_fragment; }
    void setFragment(const std::string& fragment_decoded) { m_fragment = fragment_decoded; }

    /**
     * Serialise the percent encoded URI.
     */
    std::string serialise() const;

    bool isValid() const { return (m_validity && (m_authority.isValid() || m_authority.empty())); }

private:
    bool m_validity;
    std::string m_scheme;
    omw::URI::Authority m_authority;
    omw::URI::Path m_path;
    omw::URI::Query m_query;
    std::string m_fragment;
};


//! \name Operators
/// @{

static inline bool operator==(const omw::URI::PathSegment& a, const omw::URI::PathSegment& b) { return (a.data() == b.data()); }
static inline bool operator!=(const omw::URI::PathSegment& a, const omw::URI::PathSegment& b) { return (a.data() != b.data()); }
static inline bool operator<(const omw::URI::PathSegment& a, const omw::URI::PathSegment& b) { return (a.data() < b.data()); }
static inline bool operator>(const omw::URI::PathSegment& a, const omw::URI::PathSegment& b) { return (a.data() > b.data()); }
static inline bool operator<=(const omw::URI::PathSegment& a, const omw::URI::PathSegment& b) { return (a.data() <= b.data()); }
static inline bool operator>=(const omw::URI::PathSegment& a, const omw::URI::PathSegment& b) { return (a.data() >= b.data()); }

static inline bool operator==(const omw::URI::PathSegment& a, const std::string& b) { return (a.data() == b); }
static inline bool operator!=(const omw::URI::PathSegment& a, const std::string& b) { return (a.data() != b); }
static inline bool operator<(const omw::URI::PathSegment& a, const std::string& b) { return (a.data() < b); }
static inline bool operator>(const omw::URI::PathSegment& a, const std::string& b) { return (a.data() > b); }
static inline bool operator<=(const omw::URI::PathSegment& a, const std::string& b) { return (a.data() <= b); }
static inline bool operator>=(const omw::URI::PathSegment& a, const std::string& b) { return (a.data() >= b); }

static inline bool operator==(const omw::URI::PathSegment& a, const char* b) { return (a.data() == b); }
static inline bool operator!=(const omw::URI::PathSegment& a, const char* b) { return (a.data() != b); }
static inline bool operator<(const omw::URI::PathSegment& a, const char* b) { return (a.data() < b); }
static inline bool operator>(const omw::URI::PathSegment& a, const char* b) { return (a.data() > b); }
static inline bool operator<=(const omw::URI::PathSegment& a, const char* b) { return (a.data() <= b); }
static inline bool operator>=(const omw::URI::PathSegment& a, const char* b) { return (a.data() >= b); }

static inline bool operator==(const std::string& a, const omw::URI::PathSegment& b) { return (a == b.data()); }
static inline bool operator!=(const std::string& a, const omw::URI::PathSegment& b) { return (a != b.data()); }
static inline bool operator<(const std::string& a, const omw::URI::PathSegment& b) { return (a < b.data()); }
static inline bool operator>(const std::string& a, const omw::URI::PathSegment& b) { return (a > b.data()); }
static inline bool operator<=(const std::string& a, const omw::URI::PathSegment& b) { return (a <= b.data()); }
static inline bool operator>=(const std::string& a, const omw::URI::PathSegment& b) { return (a >= b.data()); }

static inline bool operator==(const char* a, const omw::URI::PathSegment& b) { return (a == b.data()); }
static inline bool operator!=(const char* a, const omw::URI::PathSegment& b) { return (a != b.data()); }
static inline bool operator<(const char* a, const omw::URI::PathSegment& b) { return (a < b.data()); }
static inline bool operator>(const char* a, const omw::URI::PathSegment& b) { return (a > b.data()); }
static inline bool operator<=(const char* a, const omw::URI::PathSegment& b) { return (a <= b.data()); }
static inline bool operator>=(const char* a, const omw::URI::PathSegment& b) { return (a >= b.data()); }

/// @}


/*! @} */

} // namespace omw


#endif // IG_OMW_URI_H
