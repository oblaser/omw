/*
author          Oliver Blaser
date            28.12.2025
copyright       MIT - Copyright (c) 2025 Oliver Blaser
*/

#ifndef TEST_OMW_URI_H
#define TEST_OMW_URI_H

#include <cctype>
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "catch2/catch.hpp"

#include <omw/defs.h>
#include <omw/string.h>
#include <omw/uri.h>

#if (OMW_CPPSTD >= OMW_CPPSTD_17)
#include <filesystem>
namespace fs = std::filesystem;
#endif



TEST_CASE("uri.h percent-encoding")
{
    std::string message;
    std::string encoded;
    std::string fullyEncoded;

    for (int i = 1; i < 256; ++i)
    {
        message.push_back((char)i);

        if (std::isalnum(i) || (i == '-') || (i == '_') || (i == '~') || (i == '.')) { encoded.push_back((char)i); }
        else { encoded += '%' + omw::toHexStr((uint8_t)i); }

        fullyEncoded += '%' + omw::toHexStr((uint8_t)i);
    }

    CHECK(omw::URI::encode(message) == encoded);
    CHECK(omw::URI::decode(encoded) == message);
    CHECK(omw::URI::decode(fullyEncoded) == message);



    CHECK(omw::URI::encode("") == "");
    CHECK(omw::URI::decode("") == "");



    message = "0123 ThE QuIcK BrOwN FoX JuMpS OvEr tHe lAzY DoG. 456 =\xC3\x84-\xC3\x96 * \xC3\x9C 789 \xC3\xA4\xC3\xB6\xC3\xBC#";
    encoded = "0123%20ThE%20QuIcK%20BrOwN%20FoX%20JuMpS%20OvEr%20tHe%20lAzY%20DoG.%20456%20%3D%C3%84-%C3%96%20%2A%20%C3%9C%20789%20%C3%A4%C3%B6%C3%BC%23";

    CHECK(omw::URI::encode(message) == encoded);
    CHECK(omw::URI::decode(encoded) == message);
    CHECK(omw::URI::decode("%30%31%32%33%20ThE%20QuIcK%20BrOwN%20FoX%20JuMpS%20OvEr%20tHe%20lAzY%20DoG.%20456%20%3D%C3%84-%C3%96%20%2A%20%C3%9C%20789%20%C3%A4%"
                           "C3%B6%C3%BC%23") == message);



    message = "+\"*%&/()=asdf(fdsf)";
    encoded = "%2B%22%2A%25%26%2F%28%29%3Dasdf%28fdsf%29";

    CHECK(omw::URI::encode(message) == encoded);
    CHECK(omw::URI::encode(omw::URI::encode(message)) == "%252B%2522%252A%2525%2526%252F%2528%2529%253Dasdf%2528fdsf%2529");
    CHECK(omw::URI::decode(encoded) == message);
}



/*
    These tests are somewhat basic, not really thorough.
    Not all functions and edge cases and/or combinations thereof are explicitly tested.
*/

TEST_CASE("uri.h parsing and serialising URI")
{
    std::string str;
    omw::URI uri;

    uri = "";
    CHECK(uri.isValid() == false);
    CHECK(uri.scheme() == "");
    CHECK(uri.authority().empty() == true);
    CHECK(uri.authority().user() == "");
    CHECK(uri.authority().pass() == "");
    CHECK(uri.authority().host() == "");
    CHECK(uri.authority().hasPort() == false);
    CHECK(uri.path().empty() == true);
    CHECK(uri.path().serialise() == "");
    CHECK(uri.query().empty() == true);
    CHECK(uri.fragment() == "");

    str = "http://example.com";
    uri = str;
    CHECK(uri.isValid() == true);
    CHECK(uri.scheme() == "http");
    CHECK(uri.authority().empty() == false);
    CHECK(uri.authority().user() == "");
    CHECK(uri.authority().pass() == "");
    CHECK(uri.authority().host() == "example.com");
    CHECK(uri.authority().hasPort() == false);
    CHECK(uri.path().empty() == true);
    CHECK(uri.path().segments().size() == 0);
    CHECK(uri.path().serialise() == "");
    CHECK(uri.query().empty() == true);
    CHECK(uri.fragment() == "");
    CHECK(uri.serialise() == str);
    CHECK(omw::URI(uri.serialise()) == uri);

    str = "http://example.com/";
    uri = str;
    CHECK(uri.isValid() == true);
    CHECK(uri.scheme() == "http");
    CHECK(uri.authority().empty() == false);
    CHECK(uri.authority().user() == "");
    CHECK(uri.authority().pass() == "");
    CHECK(uri.authority().host() == "example.com");
    CHECK(uri.authority().hasPort() == false);
    CHECK(uri.path().empty() == false);
    REQUIRE(uri.path().segments().size() == 1);
    CHECK(uri.path().segments()[0] == "");
    CHECK(uri.path().segments()[0].empty() == true);
    CHECK(uri.path().serialise() == "/");
    CHECK(uri.query().empty() == true);
    CHECK(uri.fragment() == "");
    CHECK(uri.serialise() == str);
    CHECK(omw::URI(uri.serialise()) == uri);

    str = "http://example.com/path/to/index.php";
    uri = str;
    CHECK(uri.isValid() == true);
    CHECK(uri.scheme() == "http");
    CHECK(uri.authority().user() == "");
    CHECK(uri.authority().pass() == "");
    CHECK(uri.authority().host() == "example.com");
    CHECK(uri.authority().hasPort() == false);
    REQUIRE(uri.path().segments().size() == 3);
    CHECK(uri.path().segments()[0] == "path");
    CHECK(uri.path().segments()[1] == "to");
    CHECK(uri.path().segments()[2] == "index.php");
    CHECK(uri.path().serialise() == "/path/to/index.php");
    CHECK(uri.query().empty() == true);
    CHECK(uri.fragment() == "");
    CHECK(uri.serialise() == str);
    CHECK(omw::URI(uri.serialise()) == uri);

    str = "https://hans.meier@www.example.com:8080/view/system-b/?value=123&tag=test&u=&a&=98&b=#overview";
    uri = str;
    CHECK(uri.isValid() == true);
    CHECK(uri.scheme() == "https");
    CHECK(uri.authority().user() == "hans.meier");
    CHECK(uri.authority().pass() == "");
    CHECK(uri.authority().host() == "www.example.com");
    CHECK(uri.authority().port() == 8080);
    REQUIRE(uri.path().segments().size() == 3);
    CHECK(uri.path().segments()[0] == "view");
    CHECK(uri.path().segments()[1] == "system-b");
    CHECK(uri.path().segments()[2] == "");
    CHECK(uri.path().serialise() == "/view/system-b/");
    REQUIRE(uri.query().parameters().size() == 6);
    CHECK(uri.query().parameters()[0].key() == "value");
    CHECK(uri.query().parameters()[0].value() == "123");
    CHECK(uri.query().parameters()[0].isFlag() == false);
    CHECK(uri.query().parameters()[1].key() == "tag");
    CHECK(uri.query().parameters()[1].value() == "test");
    CHECK(uri.query().parameters()[1].isFlag() == false);
    CHECK(uri.query().parameters()[2].key() == "u");
    CHECK(uri.query().parameters()[2].value() == "");
    CHECK(uri.query().parameters()[2].isFlag() == false);
    CHECK(uri.query().parameters()[3].key() == "a");
    CHECK(uri.query().parameters()[3].value() == "");
    CHECK(uri.query().parameters()[3].isFlag() == true);
    CHECK(uri.query().parameters()[4].key() == "");
    CHECK(uri.query().parameters()[4].value() == "98");
    CHECK(uri.query().parameters()[4].isFlag() == false);
    CHECK(uri.query().parameters()[5].key() == "b");
    CHECK(uri.query().parameters()[5].value() == "");
    CHECK(uri.query().parameters()[5].isFlag() == false);
    CHECK(uri.fragment() == "overview");
    CHECK(uri.serialise() == str);
    CHECK(omw::URI(uri.serialise()) == uri);

    str = "https://hans.meier@www.example.com:3333invalid?value=123&tag=test#overview";
    uri = str;
    CHECK(uri.isValid() == false);

    str = "htTps://annek\xC3\xA4thi:geheim23@api.example.com/colour/today?token=%23j734bol&name%20id=abcd+1234#top";
    uri = str;
    CHECK(uri.isValid() == true);
    CHECK(uri.scheme() == "htTps");
    CHECK(uri.authority().user() == "annek\xC3\xA4thi");
    CHECK(uri.authority().pass() == "geheim23");
    CHECK(uri.authority().host() == "api.example.com");
    CHECK(uri.authority().hasPort() == false);
    REQUIRE(uri.path().segments().size() == 2);
    CHECK(uri.path().segments()[0] == "colour");
    CHECK(uri.path().segments()[1] == "today");
    CHECK(uri.path().serialise() == "/colour/today");
    REQUIRE(uri.query().parameters().size() == 2);
    CHECK(uri.query().parameters()[0].key() == "token");
    CHECK(uri.query().parameters()[0].value() == "#j734bol");
    CHECK(uri.query().parameters()[1].key() == "name id");
    CHECK(uri.query().parameters()[1].value() == "abcd 1234");
    CHECK(uri.fragment() == "top");
    CHECK(uri.serialise() == "htTps://annek%C3%A4thi:geheim23@api.example.com/colour/today?token=%23j734bol&name%20id=abcd%201234#top");
    CHECK(omw::URI(uri.serialise()) == uri);

    str = "mailto:flip@example.com";
    uri = str;
    CHECK(uri.isValid() == true);
    CHECK(uri.scheme() == "mailto");
    CHECK(uri.authority().empty() == true);
    REQUIRE(uri.path().segments().size() == 1);
    CHECK(uri.path().segments()[0] == "flip@example.com");
    CHECK(uri.query().empty() == true);
    CHECK(uri.fragment() == "");
    CHECK(uri.serialise() == str);
    CHECK(omw::URI(uri.serialise()) == uri);

    str = "FTP://vreni.hubacher:br-bue@[2600:1406:3a00:21::173e:2e65]:1234/path/to/file.txt";
    uri = str;
    CHECK(uri.isValid() == true);
    CHECK(uri.scheme() == "FTP");
    CHECK(uri.authority().user() == "vreni.hubacher");
    CHECK(uri.authority().pass() == "br-bue");
    CHECK(uri.authority().host() == "2600:1406:3a00:21::173e:2e65");
    CHECK(uri.authority().port() == 1234);
    REQUIRE(uri.path().segments().size() == 3);
    CHECK(uri.path().segments()[0] == "path");
    CHECK(uri.path().segments()[1] == "to");
    CHECK(uri.path().segments()[2] == "file.txt");
    CHECK(uri.query().empty() == true);
    CHECK(uri.fragment() == "");
    CHECK(uri.serialise() == str);
    CHECK(omw::URI(uri.serialise()) == uri);

    str = "Tel:+41441234567";
    uri = str;
    CHECK(uri.isValid() == true);
    CHECK(uri.scheme() == "Tel");
    CHECK(uri.authority().empty() == true);
    REQUIRE(uri.path().segments().size() == 1);
    CHECK(uri.path().segments()[0] == "+41441234567");
    CHECK(uri.query().empty() == true);
    CHECK(uri.fragment() == "");
    CHECK(uri.serialise() == str);
    CHECK(omw::URI(uri.serialise()) == uri);

    str = "news:comp.lang.c";
    uri = str;
    CHECK(uri.isValid() == true);
    CHECK(uri.scheme() == "news");
    CHECK(uri.authority().empty() == true);
    REQUIRE(uri.path().segments().size() == 1);
    CHECK(uri.path().segments()[0] == "comp.lang.c");
    CHECK(uri.query().empty() == true);
    CHECK(uri.fragment() == "");
    CHECK(uri.serialise() == str);
    CHECK(omw::URI(uri.serialise()) == uri);

    str = "urn:ietf:rfc:9226";
    uri = str;
    CHECK(uri.isValid() == true);
    CHECK(uri.scheme() == "urn");
    CHECK(uri.authority().empty() == true);
    REQUIRE(uri.path().segments().size() == 1);
    CHECK(uri.path().segments()[0] == "ietf:rfc:9226");
    CHECK(uri.query().empty() == true);
    CHECK(uri.fragment() == "");
    CHECK(uri.serialise() == str);
    CHECK(omw::URI(uri.serialise()) == uri);

    str = "doi:10.3390/ani11010145";
    uri = str;
    CHECK(uri.isValid() == true);
    CHECK(uri.scheme() == "doi");
    CHECK(uri.authority().empty() == true);
    REQUIRE(uri.path().segments().size() == 2);
    CHECK(uri.path().segments()[0] == "10.3390");
    CHECK(uri.path().segments()[1] == "ani11010145");
    CHECK(uri.query().empty() == true);
    CHECK(uri.fragment() == "");
    CHECK(uri.serialise() == str);
    CHECK(omw::URI(uri.serialise()) == uri);

    str = "file:///home/martha/Downloads/Bestellschein%20Knabber Knack.pdf";
    uri = str;
    CHECK(uri.isValid() == true);
    CHECK(uri.scheme() == "file");
    CHECK(uri.authority().empty() == true);
    REQUIRE(uri.path().segments().size() == 4);
    CHECK(uri.path().segments()[0] == "home");
    CHECK(uri.path().segments()[1] == "martha");
    CHECK(uri.path().segments()[2] == "Downloads");
    CHECK(uri.path().segments()[3] == "Bestellschein Knabber Knack.pdf");
    CHECK(uri.query().empty() == true);
    CHECK(uri.fragment() == "");
    CHECK(uri.serialise() == "file:///home/martha/Downloads/Bestellschein%20Knabber%20Knack.pdf");
    CHECK(omw::URI(uri.serialise()) == uri);



    uri = "http://example.com/as%2Fdf/?a%3Da=asdf&b=123+456";
    CHECK(uri.isValid() == true);
    CHECK(uri.scheme() == "http");
    CHECK(uri.authority().user() == "");
    CHECK(uri.authority().pass() == "");
    CHECK(uri.authority().host() == "example.com");
    CHECK(uri.authority().hasPort() == false);
    REQUIRE(uri.path().segments().size() == 2);
    CHECK(uri.path().segments()[0] == "as/df");
    CHECK(uri.path().segments()[1] == "");
    REQUIRE(uri.query().parameters().size() == 2);
    CHECK(uri.query().parameters()[0].key() == "a=a");
    CHECK(uri.query().parameters()[0].value() == "asdf");
    CHECK(uri.query().parameters()[1].key() == "b");
    CHECK(uri.query().parameters()[1].value() == "123 456");
    CHECK(uri.fragment() == "");
    CHECK(uri.serialise() == "http://example.com/as%2Fdf/?a%3Da=asdf&b=123%20456");
    CHECK(omw::URI(uri.serialise()) == uri);

    uri.setHost("\xC3\xB6.example.com");
    uri.setQuery(std::vector<omw::URI::QueryParameter>({
        omw::URI::QueryParameter("val0", "12 34 ab"),
        omw::URI::QueryParameter("val1", "a&b=c"),
    }));
    CHECK(uri.isValid() == true);
    CHECK(uri.scheme() == "http");
    CHECK(uri.authority().user() == "");
    CHECK(uri.authority().pass() == "");
    CHECK(uri.authority().host() == "\xC3\xB6.example.com");
    CHECK(uri.authority().hasPort() == false);
    REQUIRE(uri.path().segments().size() == 2);
    CHECK(uri.path().segments()[0] == "as/df");
    CHECK(uri.path().segments()[1] == "");
    REQUIRE(uri.query().parameters().size() == 2);
    CHECK(uri.query().parameters()[0].key() == "val0");
    CHECK(uri.query().parameters()[0].value() == "12 34 ab");
    CHECK(uri.query().parameters()[1].key() == "val1");
    CHECK(uri.query().parameters()[1].value() == "a&b=c");
    CHECK(uri.fragment() == "");
    CHECK(uri.serialise() == "http://%C3%B6.example.com/as%2Fdf/?val0=12%2034%20ab&val1=a%26b%3Dc");
    CHECK(omw::URI(uri.serialise()) == uri);

    uri.addQueryParameter("val2", "1+2+3=6");
    CHECK(uri.isValid() == true);
    REQUIRE(uri.query().parameters().size() == 3);
    CHECK(uri.query().parameters()[0].key() == "val0");
    CHECK(uri.query().parameters()[0].value() == "12 34 ab");
    CHECK(uri.query().parameters()[1].key() == "val1");
    CHECK(uri.query().parameters()[1].value() == "a&b=c");
    CHECK(uri.query().parameters()[2].key() == "val2");
    CHECK(uri.query().parameters()[2].value() == "1+2+3=6");
    CHECK(uri.serialise() == "http://%C3%B6.example.com/as%2Fdf/?val0=12%2034%20ab&val1=a%26b%3Dc&val2=1%2B2%2B3%3D6");
    CHECK(omw::URI(uri.serialise()) == uri);
}

TEST_CASE("uri.h URI equals")
{
    CHECK(omw::URI("http://example.com/") == omw::URI("hTtP://example.com/"));

    CHECK(omw::URI("http://example.com/") != omw::URI("http://example.com"));
    CHECK(omw::URI("http://example.com/asdf/") != omw::URI("http://example.com/asdf"));

    CHECK(omw::URI("http://example.com/asdf?a=0&b=&c") == omw::URI("http://example.com/asdf?b=&c&a=0"));
    CHECK(omw::URI("http://example.com/asdf?a=0&b=&c&z") != omw::URI("http://example.com/asdf?b=&c&a=0"));
    CHECK(omw::URI("http://example.com/asdf?a=0&b=&c") != omw::URI("http://example.com/asdf?a=0&b=&c#"));

    CHECK(omw::URI("asdf://example.com/asdf?a=0&b=&c") == omw::URI("asdf://example.com/asdf?a=0&b=&c"));
    CHECK(omw::URI("asdf://example.com/asdf?a=0&b=&c") != omw::URI("asdf://example.com/asdf?b=&c&a=0"));
    CHECK(omw::URI("asdf://example.com/asdf?a=0&b=&c") != omw::URI("asdf://example.com/asdf?a=0&b=&c#"));
}

TEST_CASE("uri.h validity after setter")
{
    std::string str, str2;
    omw::URI uri;



    // setting an authority on a relative path URI makes it invalid

    str = "asdf:path/file.txt";
    uri = str;
    CHECK(uri.isValid() == true);
    CHECK(uri.authority().empty() == true);
    REQUIRE(uri.path().segments().size() == 2);
    CHECK(uri.path().segments()[0] == "path");
    CHECK(uri.path().segments()[1] == "file.txt");
    CHECK(uri.path().serialise() == "path/file.txt");
    CHECK(uri.serialise() == str);
    CHECK(omw::URI(uri.serialise()) == uri);

    uri.setHost("server");
    CHECK(uri.isValid() == false);
    CHECK(uri.authority().isValid() == true);
    CHECK(uri.authority().serialise() == "server");
    REQUIRE(uri.path().segments().size() == 2);
    CHECK(uri.path().segments()[0] == "path");
    CHECK(uri.path().segments()[1] == "file.txt");
    CHECK(uri.path().serialise() == "path/file.txt");
    CHECK(uri.serialise() == "asdf://serverpath/file.txt");
    CHECK(omw::URI(uri.serialise()) != uri);

    str2 = uri.serialise();
    uri = str2;
    CHECK(uri.isValid() == true);
    CHECK(uri.authority().isValid() == true);
    CHECK(uri.authority().serialise() == "serverpath");
    REQUIRE(uri.path().segments().size() == 1);
    CHECK(uri.path().segments()[0] == "file.txt");
    CHECK(uri.path().serialise() == "/file.txt");
    CHECK(uri.serialise() == str2);
    CHECK(str != str2);
    CHECK(omw::URI(uri.serialise()) == uri);



    // setting an authority on an absolute path URI is fine

    str = "asdf:/path/file.txt";
    uri = str;
    CHECK(uri.isValid() == true);
    CHECK(uri.authority().empty() == true);
    REQUIRE(uri.path().segments().size() == 2);
    CHECK(uri.path().segments()[0] == "path");
    CHECK(uri.path().segments()[1] == "file.txt");
    CHECK(uri.path().serialise() == "/path/file.txt");
    CHECK(uri.serialise() == str);
    CHECK(omw::URI(uri.serialise()) == uri);

    uri.setHost("server");
    CHECK(uri.isValid() == true);
    CHECK(uri.authority().isValid() == true);
    CHECK(uri.authority().serialise() == "server");
    REQUIRE(uri.path().segments().size() == 2);
    CHECK(uri.path().segments()[0] == "path");
    CHECK(uri.path().segments()[1] == "file.txt");
    CHECK(uri.path().serialise() == "/path/file.txt");
    CHECK(uri.serialise() == "asdf://server/path/file.txt");
    CHECK(omw::URI(uri.serialise()) == uri);

    str2 = uri.serialise();
    uri = str2;
    CHECK(uri.isValid() == true);
    CHECK(uri.authority().isValid() == true);
    CHECK(uri.authority().serialise() == "server");
    REQUIRE(uri.path().segments().size() == 2);
    CHECK(uri.path().segments()[0] == "path");
    CHECK(uri.path().segments()[1] == "file.txt");
    CHECK(uri.path().serialise() == "/path/file.txt");
    CHECK(uri.serialise() == str2);
    CHECK(str != str2);
    CHECK(omw::URI(uri.serialise()) == uri);



    // clearing an authority on an URI with a path starting with `//` makes it invalid

    str = "asdf://server//path/service";
    uri = str;
    CHECK(uri.isValid() == true);
    CHECK(uri.authority().isValid() == true);
    CHECK(uri.authority().serialise() == "server");
    REQUIRE(uri.path().segments().size() == 3);
    CHECK(uri.path().segments()[0] == "");
    CHECK(uri.path().segments()[1] == "path");
    CHECK(uri.path().segments()[2] == "service");
    CHECK(uri.path().serialise() == "//path/service");
    CHECK(uri.serialise() == str);
    CHECK(omw::URI(uri.serialise()) == uri);

    uri.setAuthority(omw::URI::Authority());
    CHECK(uri.isValid() == false);
    CHECK(uri.authority().empty() == true);
    REQUIRE(uri.path().segments().size() == 3);
    CHECK(uri.path().segments()[0] == "");
    CHECK(uri.path().segments()[1] == "path");
    CHECK(uri.path().segments()[2] == "service");
    CHECK(uri.path().serialise() == "//path/service");
    CHECK(uri.serialise() == "asdf://path/service");
    CHECK(omw::URI(uri.serialise()) != uri);

    str2 = uri.serialise();
    uri = str2;
    CHECK(uri.isValid() == true);
    CHECK(uri.authority().isValid() == true);
    CHECK(uri.authority().serialise() == "path");
    REQUIRE(uri.path().segments().size() == 1);
    CHECK(uri.path().segments()[0] == "service");
    CHECK(uri.path().serialise() == "/service");
    CHECK(uri.serialise() == str2);
    CHECK(str != str2);
    CHECK(omw::URI(uri.serialise()) == uri);



    // clearing an authority on a valid URI with a path not starting with `//` is fine

    str = "asdf://server/path/service";
    uri = str;
    CHECK(uri.isValid() == true);
    CHECK(uri.authority().isValid() == true);
    CHECK(uri.authority().serialise() == "server");
    REQUIRE(uri.path().segments().size() == 2);
    CHECK(uri.path().segments()[0] == "path");
    CHECK(uri.path().segments()[1] == "service");
    CHECK(uri.path().serialise() == "/path/service");
    CHECK(uri.serialise() == str);
    CHECK(omw::URI(uri.serialise()) == uri);

    uri.setAuthority(omw::URI::Authority());
    CHECK(uri.isValid() == true);
    CHECK(uri.authority().empty() == true);
    REQUIRE(uri.path().segments().size() == 2);
    CHECK(uri.path().segments()[0] == "path");
    CHECK(uri.path().segments()[1] == "service");
    CHECK(uri.path().serialise() == "/path/service");
    CHECK(uri.serialise() == "asdf:/path/service");
    CHECK(omw::URI(uri.serialise()) == uri);

    str2 = uri.serialise();
    uri = str2;
    CHECK(uri.isValid() == true);
    CHECK(uri.authority().empty() == true);
    REQUIRE(uri.path().segments().size() == 2);
    CHECK(uri.path().segments()[0] == "path");
    CHECK(uri.path().segments()[1] == "service");
    CHECK(uri.path().serialise() == "/path/service");
    CHECK(uri.serialise() == str2);
    CHECK(str != str2);
    CHECK(omw::URI(uri.serialise()) == uri);
}

TEST_CASE("uri.h authority")
{
    std::string str;
    omw::URI uri;



    str = "http://example.com/";
    uri = str;
    CHECK(uri.isValid() == true);
    CHECK(uri.authority().isValid() == true);
    CHECK(uri.authority().hasUserinfo() == false);
    CHECK(uri.authority().host() == "example.com");
    CHECK(uri.authority().hasPort() == false);
    CHECK(uri.serialise() == str);
    CHECK(omw::URI(uri.serialise()) == uri);

    str = "http://example.com:80/";
    uri = str;
    CHECK(uri.isValid() == true);
    CHECK(uri.authority().isValid() == true);
    CHECK(uri.authority().hasUserinfo() == false);
    CHECK(uri.authority().host() == "example.com");
    CHECK(uri.authority().hasPort() == true);
    CHECK(uri.authority().port() == 80);
    CHECK(uri.serialise() == str);
    CHECK(omw::URI(uri.serialise()) == uri);

    str = "http://user:pass@[2600:1406:3a00:21::173e:2e65]:65535/";
    uri = str;
    CHECK(uri.isValid() == true);
    CHECK(uri.authority().isValid() == true);
    CHECK(uri.authority().hasUserinfo() == true);
    CHECK(uri.authority().user() == "user");
    CHECK(uri.authority().pass() == "pass");
    CHECK(uri.authority().host() == "2600:1406:3a00:21::173e:2e65");
    CHECK(uri.authority().hasPort() == true);
    CHECK(uri.authority().port() == 0xFFFF);
    CHECK(uri.serialise() == str);
    CHECK(omw::URI(uri.serialise()) == uri);

    str = "http://user:pass@t%5Bes%5Dt:3333/";
    uri = str;
    CHECK(uri.isValid() == true);
    CHECK(uri.authority().isValid() == true);
    CHECK(uri.authority().hasUserinfo() == true);
    CHECK(uri.authority().user() == "user");
    CHECK(uri.authority().pass() == "pass");
    CHECK(uri.authority().host() == "t[es]t");
    CHECK(uri.authority().hasPort() == true);
    CHECK(uri.authority().port() == 3333);
    CHECK(uri.serialise() == str);
    CHECK(omw::URI(uri.serialise()) == uri);

    str = "http://user@host:8080/";
    uri = str;
    CHECK(uri.isValid() == true);
    CHECK(uri.authority().isValid() == true);
    CHECK(uri.authority().hasUserinfo() == true);
    CHECK(uri.authority().user() == "user");
    CHECK(uri.authority().pass() == "");
    CHECK(uri.authority().host() == "host");
    CHECK(uri.authority().hasPort() == true);
    CHECK(uri.authority().port() == 8080);
    CHECK(uri.serialise() == str);
    CHECK(omw::URI(uri.serialise()) == uri);

    str = "http://user:@host:8080/";
    uri = str;
    CHECK(uri.isValid() == true);
    CHECK(uri.authority().isValid() == true);
    CHECK(uri.authority().hasUserinfo() == true);
    CHECK(uri.authority().user() == "user");
    CHECK(uri.authority().pass() == "");
    CHECK(uri.authority().host() == "host");
    CHECK(uri.authority().hasPort() == true);
    CHECK(uri.authority().port() == 8080);
    CHECK(uri.serialise() == "http://user@host:8080/"); // "`:` precedes an optional password", so no password = no `:`
                                                        // the parser has to be tolerant
    CHECK(omw::URI(uri.serialise()) == uri);

    // incomplete authority that gets parsed correctly, the invalid result is not detected, which is correct from the
    // viewpoint of the parser
    str = "http://user:1234/";
    uri = str;
    CHECK(uri.isValid() == true);
    CHECK(uri.authority().isValid() == true);
    CHECK(uri.authority().hasUserinfo() == false);
    CHECK(uri.authority().host() == "user");
    CHECK(uri.authority().hasPort() == true);
    CHECK(uri.authority().port() == 1234);
    CHECK(uri.serialise() == str);
    CHECK(omw::URI(uri.serialise()) == uri);



    // the userinfo is not hardly defined ("may consist") so a parser shall not fail on these

    str = "http://:pass@host:8080/";
    uri = str;
    CHECK(uri.isValid() == true);
    CHECK(uri.authority().isValid() == true);
    CHECK(uri.authority().hasUserinfo() == true);
    CHECK(uri.authority().user() == "");
    CHECK(uri.authority().pass() == "pass");
    CHECK(uri.authority().host() == "host");
    CHECK(uri.authority().hasPort() == true);
    CHECK(uri.authority().port() == 8080);
    CHECK(uri.serialise() == str);
    CHECK(omw::URI(uri.serialise()) == uri);

    str = "http://:@host:8080/";
    uri = str;
    CHECK(uri.isValid() == true);
    CHECK(uri.authority().isValid() == true);
    // CHECK(uri.authority().hasUserinfo() == ?); undefined
    CHECK(uri.authority().user() == "");
    CHECK(uri.authority().pass() == "");
    CHECK(uri.authority().host() == "host");
    CHECK(uri.authority().hasPort() == true);
    CHECK(uri.authority().port() == 8080);
    // CHECK(uri.serialise() == ?); undefined
    CHECK(omw::URI(uri.serialise()) == uri);

    str = "http://@host:8080/";
    uri = str;
    CHECK(uri.isValid() == true);
    CHECK(uri.authority().isValid() == true);
    // CHECK(uri.authority().hasUserinfo() == ?); undefined
    CHECK(uri.authority().user() == "");
    CHECK(uri.authority().pass() == "");
    CHECK(uri.authority().host() == "host");
    CHECK(uri.authority().hasPort() == true);
    CHECK(uri.authority().port() == 8080);
    // CHECK(uri.serialise() == ?); undefined
    CHECK(omw::URI(uri.serialise()) == uri);



    // missing host

    str = "http://user:pass@:8080/";
    uri = str;
    CHECK(uri.isValid() == false);
    CHECK(uri.authority().isValid() == false);
    CHECK(uri.authority().hasUserinfo() == true);
    CHECK(uri.authority().user() == "user");
    CHECK(uri.authority().pass() == "pass");
    CHECK(uri.authority().hasPort() == true);
    CHECK(uri.authority().port() == 8080);

    str = "http://user:pass@/";
    uri = str;
    CHECK(uri.isValid() == false);
    CHECK(uri.authority().isValid() == false);
    CHECK(uri.authority().hasUserinfo() == true);
    CHECK(uri.authority().user() == "user");
    CHECK(uri.authority().pass() == "pass");
    CHECK(uri.authority().hasPort() == false);

    str = "http://:8080/";
    uri = str;
    CHECK(uri.isValid() == false);
    CHECK(uri.authority().isValid() == false);
    CHECK(uri.authority().hasUserinfo() == false);
    CHECK(uri.authority().hasPort() == true);
    CHECK(uri.authority().port() == 8080);



    // invalid IPv6

    str = "http://user:pass@[2600:1406:3a00:21::173e:2e65:65535/";
    uri = str;
    CHECK(uri.isValid() == false);
    CHECK(uri.authority().isValid() == false);
    CHECK(uri.authority().hasUserinfo() == true);
    CHECK(uri.authority().user() == "user");
    CHECK(uri.authority().pass() == "pass");

    str = "http://user:pass@2600:1406:3a00:21::173e:2e65]/";
    uri = str;
    CHECK(uri.isValid() == false);
    CHECK(uri.authority().isValid() == false);
    CHECK(uri.authority().hasUserinfo() == true);
    CHECK(uri.authority().user() == "user");
    CHECK(uri.authority().pass() == "pass");
    CHECK(uri.authority().host() == "2600");
    CHECK(uri.authority().hasPort() == false);

    str = "http://user:pass@2600:1406:3a00:21::173e:2e65]:65535/";
    uri = str;
    CHECK(uri.isValid() == false);
    CHECK(uri.authority().isValid() == false);
    CHECK(uri.authority().hasUserinfo() == true);
    CHECK(uri.authority().user() == "user");
    CHECK(uri.authority().pass() == "pass");
    CHECK(uri.authority().host() == "2600");
    CHECK(uri.authority().hasPort() == false);



    // invalid port

    str = "http://example.com:-80/";
    uri = str;
    CHECK(uri.isValid() == false);
    CHECK(uri.authority().isValid() == false);
    CHECK(uri.authority().hasUserinfo() == false);
    CHECK(uri.authority().host() == "example.com");
    CHECK(uri.authority().hasPort() == false);

    str = "http://example.com:8080a/";
    uri = str;
    CHECK(uri.isValid() == false);
    CHECK(uri.authority().isValid() == false);
    CHECK(uri.authority().hasUserinfo() == false);
    CHECK(uri.authority().host() == "example.com");
    CHECK(uri.authority().hasPort() == false);

    str = "http://example.com:65536/";
    uri = str;
    CHECK(uri.isValid() == false);
    CHECK(uri.authority().isValid() == false);
    CHECK(uri.authority().hasUserinfo() == false);
    CHECK(uri.authority().host() == "example.com");
    CHECK(uri.authority().hasPort() == false);
}

TEST_CASE("uri.h \\ and / in path segment")
{
    std::string str;
    omw::URI uri;

#if (OMW_CPPSTD >= OMW_CPPSTD_17)
    fs::path path;
#if OMW_PLAT_WIN
    fs::path winPath;
#endif
#endif // C++17



    str = "http://example.com/path/t%5Co/strange\\file.txt";
    uri = str;
    REQUIRE(uri.path().segments().size() == 3);
    CHECK(uri.path().segments()[0] == "path");
    CHECK(uri.path().segments()[1] == "t\\o");
    CHECK(uri.path().segments()[2] == "strange\\file.txt");
    CHECK(uri.serialise() == "http://example.com/path/t%5Co/strange%5Cfile.txt");
    CHECK(omw::URI(uri.serialise()) == uri);

#if (OMW_CPPSTD >= OMW_CPPSTD_17)
#if OMW_PLAT_WIN
    winPath = fs::path("/") / "path" / "t" / "o" / "strange" / "file.txt";
    CHECK(uri.path().toStdPath() == winPath);
#else  // OMW_PLAT_WIN
    path = fs::path("/") / "path" / "t\\o" / "strange\\file.txt";
    CHECK(uri.path().toStdPath() == path);
#endif // OMW_PLAT_WIN
#endif // C++17



    str = "http://example.com/path/t%2fo/strange%2Ffile.txt";
    uri = str;
    REQUIRE(uri.path().segments().size() == 3);
    CHECK(uri.path().segments()[0] == "path");
    CHECK(uri.path().segments()[1] == "t/o");
    CHECK(uri.path().segments()[2] == "strange/file.txt");
    CHECK(uri.serialise() == "http://example.com/path/t%2Fo/strange%2Ffile.txt");
    CHECK(omw::URI(uri.serialise()) == uri);

#if (OMW_CPPSTD >= OMW_CPPSTD_17)
    path = fs::path("/") / "path" / "t" / "o" / "strange" / "file.txt";
    CHECK(uri.path().toStdPath() == path);
#endif // C++17
}

#if (OMW_CPPSTD >= OMW_CPPSTD_17)

TEST_CASE("uri.h std::filesystem::path basics")
{
    fs::path stdPath;
    omw::URI uri;

    const omw::URI startUri = "https://hans.meier@www.example.com:8080/view/system-b/?value=123&tag=test#overview";

    uri = startUri;
    CHECK(uri.isValid() == true);
    CHECK(uri.path().segments().empty() == false);
    REQUIRE(uri.path().segments().size() == 3);
    CHECK(uri.path().segments()[0] == "view");
    CHECK(uri.path().segments()[1] == "system-b");
    CHECK(uri.path().segments()[2] == "");
    CHECK(uri.path().serialise() == "/view/system-b/");
#if !OMW_PLAT_WIN
    CHECK(uri.path().toStdPath().is_absolute() == true);
#endif
    CHECK((fs::path)(uri.path()) == fs::path("/view/system-b/"));



    stdPath = "";
    uri = startUri;
    uri.setPath(stdPath);
    CHECK(uri.isValid() == true);
    CHECK(uri.path().segments().empty() == true);
    CHECK(uri.path().segments().size() == 0);
    CHECK(uri.path().serialise() == "");
#if !OMW_PLAT_WIN
    CHECK(uri.path().toStdPath().is_absolute() == false);
#endif
    CHECK((fs::path)(uri.path()) == stdPath);
    CHECK(uri.serialise() == "https://hans.meier@www.example.com:8080?value=123&tag=test#overview");



    stdPath = "/";
    uri = startUri;
    uri.setPath(stdPath);
    CHECK(uri.isValid() == true);
    CHECK(uri.path().segments().empty() == false);
    REQUIRE(uri.path().segments().size() == 1);
    CHECK(uri.path().segments()[0] == "");
    CHECK(uri.path().serialise() == "/");
#if !OMW_PLAT_WIN
    CHECK(uri.path().toStdPath().is_absolute() == true);
#endif
    CHECK((fs::path)(uri.path()) == stdPath);
    CHECK(uri.serialise() == "https://hans.meier@www.example.com:8080/?value=123&tag=test#overview");



    stdPath = "/asdf/qwertz";
    uri = startUri;
    uri.setPath(stdPath);
    CHECK(uri.isValid() == true);
    CHECK(uri.path().segments().empty() == false);
    REQUIRE(uri.path().segments().size() == 2);
    CHECK(uri.path().segments()[0] == "asdf");
    CHECK(uri.path().segments()[1] == "qwertz");
    CHECK(uri.path().serialise() == "/asdf/qwertz");
#if !OMW_PLAT_WIN
    CHECK(uri.path().toStdPath().is_absolute() == true);
#endif
    CHECK((fs::path)(uri.path()) == stdPath);
    CHECK(uri.serialise() == "https://hans.meier@www.example.com:8080/asdf/qwertz?value=123&tag=test#overview");



#if OMW_PLAT_WIN

    stdPath = "\\";
    uri = startUri;
    uri.setPath(stdPath);
    CHECK(uri.isValid() == true);
    CHECK(uri.path().segments().empty() == false);
    REQUIRE(uri.path().segments().size() == 1);
    CHECK(uri.path().segments()[0] == "");
    CHECK(uri.path().serialise() == "/");
    CHECK((fs::path)(uri.path()) == stdPath);
    CHECK(uri.serialise() == "https://hans.meier@www.example.com:8080/?value=123&tag=test#overview");

    stdPath = "\\asdf\\qwertz";
    uri = startUri;
    uri.setPath(stdPath);
    CHECK(uri.isValid() == true);
    CHECK(uri.path().segments().empty() == false);
    REQUIRE(uri.path().segments().size() == 2);
    CHECK(uri.path().segments()[0] == "asdf");
    CHECK(uri.path().segments()[1] == "qwertz");
    CHECK(uri.path().serialise() == "/asdf/qwertz");
    CHECK((fs::path)(uri.path()) == stdPath);
    CHECK(uri.serialise() == "https://hans.meier@www.example.com:8080/asdf/qwertz?value=123&tag=test#overview");

#endif // OMW_PLAT_WIN



    stdPath = "asdf";
    uri = startUri;
    uri.setPath(stdPath);
    CHECK(uri.isValid() == false);
    CHECK(uri.path().segments().empty() == false);
    REQUIRE(uri.path().segments().size() == 1);
    CHECK(uri.path().segments()[0] == "asdf");
    CHECK(uri.path().serialise() == "asdf");
#if !OMW_PLAT_WIN
    CHECK(uri.path().toStdPath().is_absolute() == false);
#endif
    CHECK((fs::path)(uri.path()) == stdPath);
    CHECK(uri.serialise() == "https://hans.meier@www.example.com:8080asdf?value=123&tag=test#overview");
}



#define ___BASE_URI_PATH_CHECK(_pathStr, ...) \
    stdPath = (_pathStr);                     \
    uriPath = omw::URI::Path(stdPath);        \
    CHECK(uriPath.segments() == std::vector<omw::URI::PathSegment>(__VA_ARGS__));

#define URI_PATH_CHECK(_pathStr, ...)              \
    ___BASE_URI_PATH_CHECK(_pathStr, __VA_ARGS__); \
    CHECK(uriPath.serialise() == (_pathStr));

#define URI_PATH_CHECK_WIN(_pathStr, _serialised, ...) \
    ___BASE_URI_PATH_CHECK(_pathStr, __VA_ARGS__);     \
    CHECK(uriPath.serialise() == (_serialised));

TEST_CASE("uri.h omw::URI::Path specific std::filesystem::path")
{
    using Segment = omw::URI::PathSegment;

    fs::path stdPath;
    omw::URI::Path uriPath;

#if OMW_PLAT_WIN
    URI_PATH_CHECK_WIN("C:\\asdf\\qwer", "C:/asdf/qwer", { Segment("C:"), Segment("asdf"), Segment("qwer") });
    URI_PATH_CHECK_WIN("C:\\asdf\\qwer\\", "C:/asdf/qwer/", { Segment("C:"), Segment("asdf"), Segment("qwer"), Segment() });
    URI_PATH_CHECK_WIN("C:\\asdf\\file.txt", "C:/asdf/file.txt", { Segment("C:"), Segment("asdf"), Segment("file.txt") });
    URI_PATH_CHECK_WIN("C:\\file.txt", "C:/file.txt", { Segment("C:"), Segment("file.txt") });
    URI_PATH_CHECK_WIN("C:file.txt", "C:file.txt", { Segment("C:file.txt") });
    URI_PATH_CHECK_WIN("C:\\", "C:/", { Segment("C:"), Segment() });
    URI_PATH_CHECK_WIN("C:", "C:", { Segment("C:") });
#endif // OMW_PLAT_WIN

    URI_PATH_CHECK("C:/asdf/qwer", { Segment("C:"), Segment("asdf"), Segment("qwer") });
    URI_PATH_CHECK("C:/asdf/qwer/", { Segment("C:"), Segment("asdf"), Segment("qwer"), Segment() });
    URI_PATH_CHECK("C:/asdf/file.txt", { Segment("C:"), Segment("asdf"), Segment("file.txt") });
    URI_PATH_CHECK("C:/file.txt", { Segment("C:"), Segment("file.txt") });
    URI_PATH_CHECK("C:file.txt", { Segment("C:file.txt") });
    URI_PATH_CHECK("C:/", { Segment("C:"), Segment() });
    URI_PATH_CHECK("C:", { Segment("C:") });

    URI_PATH_CHECK("/asdf/qwer", { Segment("asdf"), Segment("qwer") });
    URI_PATH_CHECK("/asdf/qwer/", { Segment("asdf"), Segment("qwer"), Segment() });
    URI_PATH_CHECK("/asdf/index.html", { Segment("asdf"), Segment("index.html") });
    URI_PATH_CHECK("/index.html", { Segment("index.html") });
    URI_PATH_CHECK("index.html", { Segment("index.html") });
    URI_PATH_CHECK("/", { Segment() });
    URI_PATH_CHECK("", {});
}

#endif // C++17



#endif // TEST_OMW_URI_H
