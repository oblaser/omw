/*
author          Oliver Blaser
date            28.12.2025
copyright       MIT - Copyright (c) 2025 Oliver Blaser
*/

#ifndef IG_OMW_URI_H
#define IG_OMW_URI_H

#include <cstdint>
#include <string>
#include <vector>

#include "../omw/defs.h"

#if (OMW_CPPSTD >= OMW_CPPSTD_17)
#include <filesystem>
#endif



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
 * Basic URI implementation. Performs percent-decoding after separating components, and percent-encoding while
 * serializing.
 * Some cases are not properly handled:
 * - detection of IPv6 in authority is done by simply checking front and back for the brackets
 * - querry only supports delimiter `&`, not `;`
 * - present but empty userinfo in authority is marked as valid but other return values are undefined
 *
 * Getters and setters are returning and expecting decoded strings.
 *
 * Constructors are `explicit` to rise the awareness of the (mis)use of encoded and decoded strings.
 *
 * Serialisers just do their job. If an object is invalid, the serialised output will likely differ from the
 * original/desired encoded string.
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
    class Scheme;

    static inline omw::URI::Scheme canonical(const omw::URI::Scheme& scheme) { return omw::URI::Scheme(scheme).makeCanonical(); }



public:
    class Scheme
    {
    public:
        Scheme()
            : m_validity(false), m_value()
        {}

        explicit Scheme(const char* str_encoded)
            : m_validity(false), m_value()
        {
            if (str_encoded) { this->parse(str_encoded); }
        }

        explicit Scheme(const std::string& str_encoded)
            : m_validity(false), m_value()
        {
            this->parse(str_encoded);
        }

        virtual ~Scheme() {}

        void parse(const std::string& str_encoded);
        void clear();
        omw::URI::Scheme& makeCanonical();

        const std::string& value() const { return m_value; }

        void set(const std::string& value_decoded)
        {
            m_value = value_decoded;
            m_check();
        }

        /**
         * Serialise the percent encoded path segment.
         */
        std::string serialise() const { return omw::URI::encodeScheme(m_value); }

        bool empty() const { return m_value.empty(); }
        bool valid() const { return m_validity; }

        bool isFtp() const { return (canonical(*this).value() == "ftp"); }
        bool isFile() const { return (canonical(*this).value() == "file"); }
        bool isHttp() const { return (canonical(*this).value() == "http"); }
        bool isHttps() const { return (canonical(*this).value() == "https"); }
        bool isAnyHttp() const { return (isHttp() || isHttps()); }
        bool isIrc() const { return (canonical(*this).value() == "irc"); }
        bool isMailto() const { return (canonical(*this).value() == "mailto"); }
        bool isNews() const { return (canonical(*this).value() == "news"); }
        bool isUrn() const { return (canonical(*this).value() == "urn"); }

        /**
         * Case sensitive comparsion.
         */
        bool equals(const omw::URI::Scheme& other) const { return (m_value == other.value()); }

        /**
         * Canonical comparsion.
         */
        bool equivalent(const omw::URI::Scheme& other) const { return canonical(*this).equals(canonical(other)); }

    private:
        bool m_validity;
        std::string m_value;

        void m_check();
    };

    class Authority
    {
    private:
        enum
        {
            portMin = 0,
            portMax = UINT16_MAX,
            portNone = (-1),
            portInvalid = (-2),
        };

    public:
        Authority()
            : m_validity(false), m_isIPv6(false), m_validIPv6(false), m_user(), m_pass(), m_host(), m_port(portNone)
        {}

        explicit Authority(const char* str_encoded)
            : m_validity(false), m_isIPv6(false), m_validIPv6(false), m_user(), m_pass(), m_host(), m_port(portNone)
        {
            if (str_encoded) { this->parse(str_encoded); }
        }

        explicit Authority(const std::string& str_encoded)
            : m_validity(false), m_isIPv6(false), m_validIPv6(false), m_user(), m_pass(), m_host(), m_port(portNone)
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
        bool hasPort() const { return ((m_port >= portMin) && (m_port <= portMax)); }
        bool empty() const { return (!hasUserinfo() && m_host.empty() && !hasPort()); }

        void setUser(const std::string& user_decoded);
        void setPass(const std::string& pass_decoded);
        void setHost(const std::string& host_decoded);
        void setHostIPv6(const std::string& ipv6);
        void setPort(uint16_t port);
        void clearPort() { m_port = portNone; }

        /**
         * Serialise the percent encoded authority string.
         */
        std::string serialise() const;

        bool valid() const { return m_validity; }

    private:
        bool m_validity;
        bool m_isIPv6;
        bool m_validIPv6;
        std::string m_user;
        std::string m_pass;
        std::string m_host;
        int m_port; // see private enum for special values

        void m_check();
    };

    class PathSegment
    {
    public:
        PathSegment()
            : m_value()
        {}

        explicit PathSegment(const char* str_encoded)
            : m_value()
        {
            if (str_encoded) { this->parse(str_encoded); }
        }

        explicit PathSegment(const std::string& str_encoded)
            : m_value()
        {
            this->parse(str_encoded);
        }

        virtual ~PathSegment() {}

        void parse(const std::string& str_encoded) { m_value = omw::URI::decode(str_encoded); }
        void clear() { m_value.clear(); }

        const std::string& value() const { return m_value; }

        bool empty() const { return m_value.empty(); }

        void set(const std::string& value_decoded) { m_value = value_decoded; }

        /**
         * Serialise the percent encoded path segment.
         */
        std::string serialise() const { return omw::URI::encodePathSegment(m_value); }

    private:
        std::string m_value;
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
            if (str_encoded) { this->parse(str_encoded); }
        }

        explicit Path(const std::string& str_encoded)
            : m_isAbs(false), m_segments()
        {
            this->parse(str_encoded);
        }

#if (OMW_CPPSTD >= OMW_CPPSTD_17) || defined(OMWi_DOXYGEN_PREDEFINE)

        /**
         * This constructor is only available for C++ versions &ge;17.
         *
         * @param path `std::filesystem::path` in decoded string format
         */
        explicit Path(const std::filesystem::path& path)
            : m_isAbs(false), m_segments()
        {
            this->set(path);
        }

#endif // C++17

        virtual ~Path() {}

        void parse(const std::string& str_encoded);
        void parse(const char* str_encoded);

#if (OMW_CPPSTD >= OMW_CPPSTD_17) || defined(OMWi_DOXYGEN_PREDEFINE)

        /**
         * This function is only available for C++ versions &ge;17.
         *
         * @param path `std::filesystem::path` in decoded string format
         */
        void set(const std::filesystem::path& path);

#endif // C++17

        void clear()
        {
            m_isAbs = false;
            m_segments.clear();
        }

        const std::vector<omw::URI::PathSegment>& segments() const { return m_segments; }

        bool empty() const { return (m_segments.empty() || ((m_segments.size() == 1) && (m_segments[0].empty()) && !m_isAbs)); }

        /**
         * Serialise the percent encoded path.
         */
        std::string serialise() const;

#if (OMW_CPPSTD >= OMW_CPPSTD_17) || defined(OMWi_DOXYGEN_PREDEFINE)

        /**
         * This function is only available for C++ versions &ge;17.
         *
         * CAUTION:
         * If any path segment contains `/` this function will return a path that differs from the original path.
         *
         * CAUTION:
         * If any path segment contains `\`, on Windows this function will return a path that differs from the original
         * path. Other platforms should be fine since they allow `\` in directory enry names.
         *
         * Seeing any slash in the path is not as absurd as it might seem (although rarely seen). On *nix systems, `\`
         * is allowed in directory entry names. Since, depending on the server application, the path is not necessarily
         * a filesystem path, a `/` encoded as `%2F` could be possible within a path segment.
         *
         * @return `std::filesystem::path` in decoded string format
         */
        std::filesystem::path toStdPath() const;

        /**
         * IMPORTANT: See `toStdPath()`!
         */
        explicit operator std::filesystem::path() const { return this->toStdPath(); }

#endif // C++17

    private:
        // Not publicly available, internal use only. Is invalid for paths with root names, but this is still ok for
        // internal use (serialiser). E.g. the path `C:\asdf` is treated as relative.
        bool m_isAbs;

        std::vector<omw::URI::PathSegment> m_segments;

    private:
#if (OMW_CPPSTD >= OMW_CPPSTD_17)
        // explicitly disable these overloads, use `set()`
        void parse(const std::filesystem::path&) const;
        void parse(const std::filesystem::path&);
#endif
    };

    class QueryParameter
    {
    public:
        /**
         * @brief Creates a flag type `QueryParameter`.
         *
         * Creates a flag type `QueryParameter`  but is explicitly not a constructor.
         *
         * See also `omw::URI::QueryParameter::isFlag()`.
         *
         * @param key_decoded Decoded key name
         */
        static QueryParameter flag(const std::string& key_decoded);

    public:
        QueryParameter()
            : m_isFlag(false), m_key(), m_value()
        {}

        explicit QueryParameter(const char* str_encoded)
            : m_isFlag(false), m_key(), m_value()
        {
            if (str_encoded) { this->parse(str_encoded); }
        }

        explicit QueryParameter(const std::string& str_encoded)
            : m_isFlag(false), m_key(), m_value()
        {
            this->parse(str_encoded);
        }

        QueryParameter(const std::string& key_decoded, const std::string& value_decoded)
            : m_isFlag(false), m_key(key_decoded), m_value(value_decoded)
        {}

        virtual ~QueryParameter() {}

        void parse(const std::string& str_encoded);
        void clear()
        {
            m_isFlag = false;
            m_key.clear();
            m_value.clear();
        }

        const std::string& key() const { return m_key; }
        const std::string& value() const { return m_value; }

        void setKey(const std::string& key_decoded)
        {
            m_isFlag = false;
            m_key = key_decoded;
        }

        void setValue(const std::string& value_decoded)
        {
            m_isFlag = false;
            m_value = value_decoded;
        }

        void set(const std::string& key_decoded, const std::string& value_decoded)
        {
            m_isFlag = false;
            m_key = key_decoded;
            m_value = value_decoded;
        }

        /**
         * @brief Converts the parameter to a flag.
         *
         * @param key_decoded Decoded flag name
         */
        void makeFlag(const std::string& key_decoded)
        {
            m_isFlag = true;
            m_key = key_decoded;
            m_value.clear();
        }

        /**
         * Serialise the percent encoded key value pair.
         */
        std::string serialise() const;

        /**
         * - normal parameter: `...?key=value&...`
         * - normal parameter with no/empty value: `...?key=&...`
         * - flag parameter: `...?flag&...`
         */
        bool isFlag() const { return m_isFlag; }

        bool equals(const omw::URI::QueryParameter& other) const
        {
            return ((m_isFlag == other.isFlag()) && (m_key == other.key()) && (m_value == other.value()));
        }

    private:
        bool m_isFlag;
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
            if (str_encoded) { this->parse(str_encoded); }
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

        /**
         * Tests if `other` is an exact match.
         */
        bool equals(const omw::URI::Query& other) const { return (m_parameters == other.parameters()); }

        /**
         * Same as `omw::URI::Query::equals()` but the order of the parameters is ignored.
         */
        bool equivalent(const omw::URI::Query& other) const;

    private:
        std::vector<omw::URI::QueryParameter> m_parameters;
    };



public:
    URI()
        : m_validity(false), m_scheme(), m_authority(), m_path(), m_query(), m_hasFragment(false), m_fragment()
    {}

    URI(const char* uri_encoded)
        : m_validity(false), m_scheme(), m_authority(), m_path(), m_query(), m_hasFragment(false), m_fragment()
    {
        parse(uri_encoded);
    }

    URI(const std::string& uri_encoded)
        : m_validity(false), m_scheme(), m_authority(), m_path(), m_query(), m_hasFragment(false), m_fragment()
    {
        parse(uri_encoded);
    }

    virtual ~URI() {}

    void parse(const std::string& uri_encoded);
    void parse(const char* uri_encoded);
    void clear();

    const omw::URI::Scheme& scheme() const { return m_scheme; }
    const omw::URI::Authority& authority() const { return m_authority; }
    const omw::URI::Path& path() const { return m_path; }
    const omw::URI::Query& query() const { return m_query; }
    const std::string& fragment() const { return m_fragment; }

    void setScheme(const omw::URI::Scheme& scheme);
    void setScheme(const std::string& scheme_decoded);
    void setAuthority(const omw::URI::Authority& authority);
    void setUser(const std::string& user_decoded);
    void setPass(const std::string& pass_decoded);
    void setHost(const std::string& host_decoded);
    void setPort(uint16_t port);
    void setPath(const omw::URI::Path& path);

#if (OMW_CPPSTD >= OMW_CPPSTD_17) || defined(OMWi_DOXYGEN_PREDEFINE)

    /**
     * This function is only available for C++ versions &ge;17.
     *
     * @param path `std::filesystem::path` in decoded string format
     */
    void setPath(const std::filesystem::path& path);

#endif // C++17

    void setQuery(const omw::URI::Query& query);
    void setFragment(const std::string& fragment_decoded);

    /**
     * Removes the fragment, `hasFragment()` returns `false` after this call. To set an empty fragament use
     * `setFragment("")`.
     */
    void clearFragment();

    void addQueryParameter(const omw::URI::QueryParameter& parameter);
    void addQueryParameter(const std::string& key, const std::string& value);

    /**
     * Serialise to the percent encoded string.
     */
    std::string serialise() const;

    /**
     * Compares the canonical schemes, ignores the validity. The path has to be exatly the same, no canonicalisation is
     * performed prior to the comparsion.
     *
     * The query is compared by `omw::URI::Query::equivalent()` for `http[s]`, and with `omw::URI::Query::equals()` for
     * all other schemes.
     */
    bool equals(const omw::URI& other) const;

    bool hasFragment() const { return m_hasFragment; }

    bool valid() const { return m_validity; }

private:
    bool m_validity;
    omw::URI::Scheme m_scheme;
    omw::URI::Authority m_authority;
    omw::URI::Path m_path;
    omw::URI::Query m_query;
    bool m_hasFragment;
    std::string m_fragment;

    void m_check();

private:
    // explicitly disable these overloads, so that calls don't wrongly fall back to
    // `void setPath(const std::filesystem::path&)`.
    void setPath(const char*);
    void setPath(const std::string&);
};



static inline omw::URI::Scheme canonical(const omw::URI::Scheme& scheme) { return omw::URI::canonical(scheme); }

static inline bool equals(const omw::URI::Scheme& a, const omw::URI::Scheme& b) { return a.equals(b); }
static inline bool equals(const omw::URI::Query& a, const omw::URI::Query& b) { return a.equals(b); }

static inline bool equivalent(const omw::URI::Scheme& a, const omw::URI::Scheme& b) { return a.equivalent(b); }
static inline bool equivalent(const omw::URI::Query& a, const omw::URI::Query& b) { return a.equivalent(b); }



//! \name Operators
/// @{

// Operators `==` and `!=` are not declared for `omw::URI::Scheme` to omit confusion. Most likely `equivalent()` will be
// prefered over `equals()`.



static inline bool operator==(const omw::URI::PathSegment& a, const omw::URI::PathSegment& b) { return (a.value() == b.value()); }
static inline bool operator!=(const omw::URI::PathSegment& a, const omw::URI::PathSegment& b) { return (a.value() != b.value()); }
static inline bool operator<(const omw::URI::PathSegment& a, const omw::URI::PathSegment& b) { return (a.value() < b.value()); }
static inline bool operator>(const omw::URI::PathSegment& a, const omw::URI::PathSegment& b) { return (a.value() > b.value()); }
static inline bool operator<=(const omw::URI::PathSegment& a, const omw::URI::PathSegment& b) { return (a.value() <= b.value()); }
static inline bool operator>=(const omw::URI::PathSegment& a, const omw::URI::PathSegment& b) { return (a.value() >= b.value()); }

static inline bool operator==(const omw::URI::PathSegment& a, const std::string& b) { return (a.value() == b); }
static inline bool operator!=(const omw::URI::PathSegment& a, const std::string& b) { return (a.value() != b); }
static inline bool operator<(const omw::URI::PathSegment& a, const std::string& b) { return (a.value() < b); }
static inline bool operator>(const omw::URI::PathSegment& a, const std::string& b) { return (a.value() > b); }
static inline bool operator<=(const omw::URI::PathSegment& a, const std::string& b) { return (a.value() <= b); }
static inline bool operator>=(const omw::URI::PathSegment& a, const std::string& b) { return (a.value() >= b); }

static inline bool operator==(const omw::URI::PathSegment& a, const char* b) { return (a.value() == b); }
static inline bool operator!=(const omw::URI::PathSegment& a, const char* b) { return (a.value() != b); }
static inline bool operator<(const omw::URI::PathSegment& a, const char* b) { return (a.value() < b); }
static inline bool operator>(const omw::URI::PathSegment& a, const char* b) { return (a.value() > b); }
static inline bool operator<=(const omw::URI::PathSegment& a, const char* b) { return (a.value() <= b); }
static inline bool operator>=(const omw::URI::PathSegment& a, const char* b) { return (a.value() >= b); }

static inline bool operator==(const std::string& a, const omw::URI::PathSegment& b) { return (a == b.value()); }
static inline bool operator!=(const std::string& a, const omw::URI::PathSegment& b) { return (a != b.value()); }
static inline bool operator<(const std::string& a, const omw::URI::PathSegment& b) { return (a < b.value()); }
static inline bool operator>(const std::string& a, const omw::URI::PathSegment& b) { return (a > b.value()); }
static inline bool operator<=(const std::string& a, const omw::URI::PathSegment& b) { return (a <= b.value()); }
static inline bool operator>=(const std::string& a, const omw::URI::PathSegment& b) { return (a >= b.value()); }

static inline bool operator==(const char* a, const omw::URI::PathSegment& b) { return (a == b.value()); }
static inline bool operator!=(const char* a, const omw::URI::PathSegment& b) { return (a != b.value()); }
static inline bool operator<(const char* a, const omw::URI::PathSegment& b) { return (a < b.value()); }
static inline bool operator>(const char* a, const omw::URI::PathSegment& b) { return (a > b.value()); }
static inline bool operator<=(const char* a, const omw::URI::PathSegment& b) { return (a <= b.value()); }
static inline bool operator>=(const char* a, const omw::URI::PathSegment& b) { return (a >= b.value()); }



static inline bool operator==(const omw::URI::QueryParameter& a, const omw::URI::QueryParameter& b) { return a.equals(b); }
static inline bool operator!=(const omw::URI::QueryParameter& a, const omw::URI::QueryParameter& b) { return !(a == b); }



// Operators `==` and `!=` are not declared for `omw::URI::Query` to omit confusion. Depending on the context,
// `equivalent()` is prefered over `equals()`.



/**
 * see `omw::URI::equals()`
 */
static inline bool operator==(const omw::URI& a, const omw::URI& b) { return a.equals(b); }

/**
 * see `omw::URI::equals()`
 */
static inline bool operator!=(const omw::URI& a, const omw::URI& b) { return !(a == b); }

/// @}



/*! @} */

} // namespace omw


#endif // IG_OMW_URI_H
