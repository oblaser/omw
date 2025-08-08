/*
author          Oliver Blaser
date            09.06.2025
copyright       MIT - Copyright (c) 2025 Oliver Blaser
*/

#ifndef TEST_OMW_URI_H
#define TEST_OMW_URI_H

#include <cctype>
#include <cstddef>
#include <cstdint>

#include "catch2/catch.hpp"

#include <omw/string.h>
#include <omw/uri.h>



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

These tests are very basic. The constructor uses the `set()` function directly, which uses `clear()`. So these two are
not explicitly tested. Getters are implicitly tested.
Also could the existing test cases be more thorough.

*/

TEST_CASE("uri.h parsing")
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
    CHECK(uri.query() == "");
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
    CHECK(uri.query() == "");
    CHECK(uri.fragment() == "");
    CHECK(uri.serialise() == str);

    str = "http://example.com/";
    uri = str;
    CHECK(uri.isValid() == true);
    CHECK(uri.scheme() == "http");
    CHECK(uri.authority().empty() == false);
    CHECK(uri.authority().user() == "");
    CHECK(uri.authority().pass() == "");
    CHECK(uri.authority().host() == "example.com");
    CHECK(uri.authority().hasPort() == false);
    CHECK(uri.path().empty() == true);
    REQUIRE(uri.path().segments().size() == 1);
    CHECK(uri.path().segments()[0] == "");
    CHECK(uri.path().segments()[0].empty() == true);
    CHECK(uri.query() == "");
    CHECK(uri.fragment() == "");
    CHECK(uri.serialise() == str);

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
    CHECK(uri.query() == "");
    CHECK(uri.fragment() == "");
    CHECK(uri.serialise() == str);

    str = "https://hans.meier@www.example.com:8080/view/system-b/?value=123&tag=test#overview";
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
    CHECK(uri.query() == "value=123&tag=test");
    CHECK(uri.fragment() == "overview");
    CHECK(uri.serialise() == str);

    str = "htTps://annek\xC3\xA4thi:geheim23@api.example.com/colour/today?token=%23j734bol";
    uri = str;
    CHECK(uri.isValid() == true);
    CHECK(uri.scheme() == "https");
    CHECK(uri.authority().user() == "annek\xC3\xA4thi");
    CHECK(uri.authority().pass() == "geheim23");
    CHECK(uri.authority().host() == "api.example.com");
    CHECK(uri.authority().hasPort() == false);
    REQUIRE(uri.path().segments().size() == 2);
    CHECK(uri.path().segments()[0] == "colour");
    CHECK(uri.path().segments()[1] == "today");
    CHECK(uri.query() == "token=#j734bol");
    CHECK(uri.fragment() == "");
    CHECK(uri.serialise() == "https://annek%C3%A4thi:geheim23@api.example.com/colour/today?token=%23j734bol");

    str = "mailto:flip@example.com";
    uri = str;
    CHECK(uri.isValid() == true);
    CHECK(uri.scheme() == "mailto");
    CHECK(uri.authority().empty() == true);
    REQUIRE(uri.path().segments().size() == 1);
    CHECK(uri.path().segments()[0] == "flip@example.com");
    CHECK(uri.query() == "");
    CHECK(uri.fragment() == "");
    CHECK(uri.serialise() == str);

    str = "ftp://vreni.hubacher:br-bue@[2600:1406:3a00:21::173e:2e65]:1234/path/to/file.txt";
    uri = str;
    CHECK(uri.isValid() == true);
    CHECK(uri.scheme() == "ftp");
    CHECK(uri.authority().user() == "vreni.hubacher");
    CHECK(uri.authority().pass() == "br-bue");
    CHECK(uri.authority().host() == "[2600:1406:3a00:21::173e:2e65]");
    CHECK(uri.authority().port() == 1234);
    REQUIRE(uri.path().segments().size() == 3);
    CHECK(uri.path().segments()[0] == "path");
    CHECK(uri.path().segments()[1] == "to");
    CHECK(uri.path().segments()[2] == "file.txt");
    CHECK(uri.query() == "");
    CHECK(uri.fragment() == "");
    CHECK(uri.serialise() == str);

    str = "tel:+41441234567";
    uri = str;
    CHECK(uri.isValid() == true);
    CHECK(uri.scheme() == "tel");
    CHECK(uri.authority().empty() == true);
    REQUIRE(uri.path().segments().size() == 1);
    CHECK(uri.path().segments()[0] == "+41441234567");
    CHECK(uri.query() == "");
    CHECK(uri.fragment() == "");
    CHECK(uri.serialise() == str);

    str = "news:comp.lang.c";
    uri = str;
    CHECK(uri.isValid() == true);
    CHECK(uri.scheme() == "news");
    CHECK(uri.authority().empty() == true);
    REQUIRE(uri.path().segments().size() == 1);
    CHECK(uri.path().segments()[0] == "comp.lang.c");
    CHECK(uri.query() == "");
    CHECK(uri.fragment() == "");
    CHECK(uri.serialise() == str);

    str = "urn:ietf:rfc:9226";
    uri = str;
    CHECK(uri.isValid() == true);
    CHECK(uri.scheme() == "urn");
    CHECK(uri.authority().empty() == true);
    REQUIRE(uri.path().segments().size() == 1);
    CHECK(uri.path().segments()[0] == "ietf:rfc:9226");
    CHECK(uri.query() == "");
    CHECK(uri.fragment() == "");
    CHECK(uri.serialise() == str);

    str = "doi:10.3390/ani11010145";
    uri = str;
    CHECK(uri.isValid() == true);
    CHECK(uri.scheme() == "doi");
    CHECK(uri.authority().empty() == true);
    REQUIRE(uri.path().segments().size() == 2);
    CHECK(uri.path().segments()[0] == "10.3390");
    CHECK(uri.path().segments()[1] == "ani11010145");
    CHECK(uri.query() == "");
    CHECK(uri.fragment() == "");
    CHECK(uri.serialise() == str);

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
    CHECK(uri.query() == "");
    CHECK(uri.fragment() == "");
    CHECK(uri.serialise() == "file:///home/martha/Downloads/Bestellschein%20Knabber%20Knack.pdf");



    str = "http://example.com/as%2Fdf/";
    uri = str;
    CHECK(uri.isValid() == true);
    CHECK(uri.scheme() == "http");
    CHECK(uri.authority().user() == "");
    CHECK(uri.authority().pass() == "");
    CHECK(uri.authority().host() == "example.com");
    CHECK(uri.authority().hasPort() == false);
    REQUIRE(uri.path().segments().size() == 2);
    CHECK(uri.path().segments()[0] == "as/df");
    CHECK(uri.path().segments()[1] == "");
    CHECK(uri.query() == "");
    CHECK(uri.fragment() == "");
    CHECK(uri.serialise() == str);

    uri.setHost("\xC3\xB6.example.com");
    uri.setQuery("val0=1234&val1=a&b=c"); // where val1 is the string "a&b=c"
    CHECK(uri.isValid() == true);
    CHECK(uri.scheme() == "http");
    CHECK(uri.authority().user() == "");
    CHECK(uri.authority().pass() == "");
    CHECK(uri.authority().host() == "\xC3\xB6.example.com");
    CHECK(uri.authority().hasPort() == false);
    REQUIRE(uri.path().segments().size() == 2);
    CHECK(uri.path().segments()[0] == "as/df");
    CHECK(uri.path().segments()[1] == "");
    CHECK(uri.query() == "val0=1234&val1=a&b=c");
    CHECK(uri.fragment() == "");
    WARN("`omw::URI` is not fully implemented, see doc");
    // CHECK(uri.serialise() == "http://%C3%B6.example.com/as%2Fdf/?val0=1234&val1=a%26b%3Dc"); // path and query classes needed as described in doc of
    // `omw::URI`



    /*
    str = "";
    uri = str;
    CHECK(uri.isValid() == );
    CHECK(uri.scheme() == "");
    CHECK(uri.authority() == "");
    REQUIRE(uri.path().segments().size() == );
    CHECK(uri.path().segments()[0] == "");
    CHECK(uri.query() == "");
    CHECK(uri.fragment() == "");
    CHECK(uri.serialise() == str);
    */
}



#endif // TEST_OMW_URI_H
