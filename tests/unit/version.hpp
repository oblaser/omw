/*
author         Oliver Blaser
date           23.01.2022
copyright      MIT - Copyright (c) 2022 Oliver Blaser
*/

#ifndef TEST_OMW_VERSION_H
#define TEST_OMW_VERSION_H

#include <cstdint>
#include <string>
#include <vector>

#include "catch2/catch.hpp"

#include <omw/version.h>



TEST_CASE("omw::Version ctor")
{
    omw::Version v;

    v = omw::Version();
    CHECK(v.major() == 0);
    CHECK(v.minor() == 0);
    CHECK(v.patch() == 0);
    CHECK(v.preRelease() == "");
    CHECK(v.preReleaseIdentifiers().size() == 0);
    CHECK(v.build() == "");
    CHECK(v.buildIdentifiers().size() == 0);
    CHECK(v.toString() == "0.0.0");
    CHECK(v.hasBuild() == false);
    CHECK(v.isPreRelease() == false);

    v = omw::Version(1, 2, 3);
    CHECK(v.major() == 1);
    CHECK(v.minor() == 2);
    CHECK(v.patch() == 3);
    CHECK(v.preRelease() == "");
    CHECK(v.preReleaseIdentifiers().size() == 0);
    CHECK(v.build() == "");
    CHECK(v.buildIdentifiers().size() == 0);
    CHECK(v.toString() == "1.2.3");
    CHECK(v.hasBuild() == false);
    CHECK(v.isPreRelease() == false);

    v = omw::Version(-1, -2, -3);
    CHECK(v.major() == -1);
    CHECK(v.minor() == -2);
    CHECK(v.patch() == -3);
    CHECK(v.preRelease() == "");
    CHECK(v.preReleaseIdentifiers().size() == 0);
    CHECK(v.build() == "");
    CHECK(v.buildIdentifiers().size() == 0);
    CHECK(v.toString() == "-1.-2.-3");
    CHECK(v.hasBuild() == false);
    CHECK(v.isPreRelease() == false);

    v = omw::Version(2, 4, 8, "beta.3.a#b");
    CHECK(v.major() == 2);
    CHECK(v.minor() == 4);
    CHECK(v.patch() == 8);
    CHECK(v.preRelease() == "beta.3.a#b");
    REQUIRE(v.preReleaseIdentifiers().size() == 3);
    CHECK(v.preReleaseIdentifiers()[0] == "beta");
    CHECK(v.preReleaseIdentifiers()[1] == "3");
    CHECK(v.preReleaseIdentifiers()[2] == "a#b");
    CHECK(v.build() == "");
    CHECK(v.buildIdentifiers().size() == 0);
    CHECK(v.toString() == "2.4.8-beta.3.a#b");
    CHECK(v.hasBuild() == false);
    CHECK(v.isPreRelease() == true);

    v = omw::Version(2, 4, 8, "", "000123.abcd$54987");
    CHECK(v.major() == 2);
    CHECK(v.minor() == 4);
    CHECK(v.patch() == 8);
    CHECK(v.preRelease() == "");
    CHECK(v.preReleaseIdentifiers().size() == 0);
    CHECK(v.build() == "000123.abcd$54987");
    REQUIRE(v.buildIdentifiers().size() == 2);
    CHECK(v.buildIdentifiers()[0] == "000123");
    CHECK(v.buildIdentifiers()[1] == "abcd$54987");
    CHECK(v.toString() == "2.4.8+000123.abcd$54987");
    CHECK(v.hasBuild() == true);
    CHECK(v.isPreRelease() == false);

    v = "1.5.9";
    CHECK(v.major() == 1);
    CHECK(v.minor() == 5);
    CHECK(v.patch() == 9);
    CHECK(v.preRelease() == "");
    CHECK(v.preReleaseIdentifiers().size() == 0);
    CHECK(v.build() == "");
    CHECK(v.buildIdentifiers().size() == 0);
    CHECK(v.toString() == "1.5.9");
    CHECK(v.hasBuild() == false);
    CHECK(v.isPreRelease() == false);

    v = "1.5.9-ab.%&(";
    CHECK(v.major() == 1);
    CHECK(v.minor() == 5);
    CHECK(v.patch() == 9);
    CHECK(v.preRelease() == "ab.%&(");
    REQUIRE(v.preReleaseIdentifiers().size() == 2);
    CHECK(v.preReleaseIdentifiers()[0] == "ab");
    CHECK(v.preReleaseIdentifiers()[1] == "%&(");
    CHECK(v.build() == "");
    CHECK(v.buildIdentifiers().size() == 0);
    CHECK(v.toString() == "1.5.9-ab.%&(");
    CHECK(v.hasBuild() == false);
    CHECK(v.isPreRelease() == true);

    v = "1.5.9+bld.00456$.asdf@";
    CHECK(v.major() == 1);
    CHECK(v.minor() == 5);
    CHECK(v.patch() == 9);
    CHECK(v.preRelease() == "");
    CHECK(v.preReleaseIdentifiers().size() == 0);
    CHECK(v.build() == "bld.00456$.asdf@");
    REQUIRE(v.buildIdentifiers().size() == 3);
    CHECK(v.buildIdentifiers()[0] == "bld");
    CHECK(v.buildIdentifiers()[1] == "00456$");
    CHECK(v.buildIdentifiers()[2] == "asdf@");
    CHECK(v.toString() == "1.5.9+bld.00456$.asdf@");
    CHECK(v.hasBuild() == true);
    CHECK(v.isPreRelease() == false);

    v = "45.67.89-rc.5+00789";
    CHECK(v.major() == 45);
    CHECK(v.minor() == 67);
    CHECK(v.patch() == 89);
    CHECK(v.preRelease() == "rc.5");
    REQUIRE(v.preReleaseIdentifiers().size() == 2);
    CHECK(v.preReleaseIdentifiers()[0] == "rc");
    CHECK(v.preReleaseIdentifiers()[1] == "5");
    CHECK(v.build() == "00789");
    REQUIRE(v.buildIdentifiers().size() == 1);
    CHECK(v.buildIdentifiers()[0] == "00789");
    CHECK(v.toString() == "45.67.89-rc.5+00789");
    CHECK(v.hasBuild() == true);
    CHECK(v.isPreRelease() == true);
}

TEST_CASE("omw::Version::set()")
{
    omw::Version v;

    v.set(1, 2, 3);
    CHECK(v.major() == 1);
    CHECK(v.minor() == 2);
    CHECK(v.patch() == 3);
    CHECK(v.preRelease() == "");
    CHECK(v.preReleaseIdentifiers().size() == 0);
    CHECK(v.build() == "");
    CHECK(v.buildIdentifiers().size() == 0);
    CHECK(v.toString() == "1.2.3");
    CHECK(v.hasBuild() == false);
    CHECK(v.isPreRelease() == false);

    v.set(-1, -2, -3);
    CHECK(v.major() == -1);
    CHECK(v.minor() == -2);
    CHECK(v.patch() == -3);
    CHECK(v.preRelease() == "");
    CHECK(v.preReleaseIdentifiers().size() == 0);
    CHECK(v.build() == "");
    CHECK(v.buildIdentifiers().size() == 0);
    CHECK(v.toString() == "-1.-2.-3");
    CHECK(v.hasBuild() == false);
    CHECK(v.isPreRelease() == false);

    v.set(2, 4, 8, "beta.3.a#b");
    CHECK(v.major() == 2);
    CHECK(v.minor() == 4);
    CHECK(v.patch() == 8);
    CHECK(v.preRelease() == "beta.3.a#b");
    REQUIRE(v.preReleaseIdentifiers().size() == 3);
    CHECK(v.preReleaseIdentifiers()[0] == "beta");
    CHECK(v.preReleaseIdentifiers()[1] == "3");
    CHECK(v.preReleaseIdentifiers()[2] == "a#b");
    CHECK(v.build() == "");
    CHECK(v.buildIdentifiers().size() == 0);
    CHECK(v.toString() == "2.4.8-beta.3.a#b");
    CHECK(v.hasBuild() == false);
    CHECK(v.isPreRelease() == true);

    v.set(2, 4, 8, "", "000123.abcd$54987");
    CHECK(v.major() == 2);
    CHECK(v.minor() == 4);
    CHECK(v.patch() == 8);
    CHECK(v.preRelease() == "");
    CHECK(v.preReleaseIdentifiers().size() == 0);
    CHECK(v.build() == "000123.abcd$54987");
    REQUIRE(v.buildIdentifiers().size() == 2);
    CHECK(v.buildIdentifiers()[0] == "000123");
    CHECK(v.buildIdentifiers()[1] == "abcd$54987");
    CHECK(v.toString() == "2.4.8+000123.abcd$54987");
    CHECK(v.hasBuild() == true);
    CHECK(v.isPreRelease() == false);

    v.set("1.5.9");
    CHECK(v.major() == 1);
    CHECK(v.minor() == 5);
    CHECK(v.patch() == 9);
    CHECK(v.preRelease() == "");
    CHECK(v.preReleaseIdentifiers().size() == 0);
    CHECK(v.build() == "");
    CHECK(v.buildIdentifiers().size() == 0);
    CHECK(v.toString() == "1.5.9");
    CHECK(v.hasBuild() == false);
    CHECK(v.isPreRelease() == false);

    v.set("1.5.9-ab.%&(");
    CHECK(v.major() == 1);
    CHECK(v.minor() == 5);
    CHECK(v.patch() == 9);
    CHECK(v.preRelease() == "ab.%&(");
    REQUIRE(v.preReleaseIdentifiers().size() == 2);
    CHECK(v.preReleaseIdentifiers()[0] == "ab");
    CHECK(v.preReleaseIdentifiers()[1] == "%&(");
    CHECK(v.build() == "");
    CHECK(v.buildIdentifiers().size() == 0);
    CHECK(v.toString() == "1.5.9-ab.%&(");
    CHECK(v.hasBuild() == false);
    CHECK(v.isPreRelease() == true);

    v.set("1.5.9+bld.00456$.asdf@");
    CHECK(v.major() == 1);
    CHECK(v.minor() == 5);
    CHECK(v.patch() == 9);
    CHECK(v.preRelease() == "");
    CHECK(v.preReleaseIdentifiers().size() == 0);
    CHECK(v.build() == "bld.00456$.asdf@");
    REQUIRE(v.buildIdentifiers().size() == 3);
    CHECK(v.buildIdentifiers()[0] == "bld");
    CHECK(v.buildIdentifiers()[1] == "00456$");
    CHECK(v.buildIdentifiers()[2] == "asdf@");
    CHECK(v.toString() == "1.5.9+bld.00456$.asdf@");
    CHECK(v.hasBuild() == true);
    CHECK(v.isPreRelease() == false);

    v.set("45.67.89-rc.5+00789.d.q");
    CHECK(v.major() == 45);
    CHECK(v.minor() == 67);
    CHECK(v.patch() == 89);
    CHECK(v.preRelease() == "rc.5");
    REQUIRE(v.preReleaseIdentifiers().size() == 2);
    CHECK(v.preReleaseIdentifiers()[0] == "rc");
    CHECK(v.preReleaseIdentifiers()[1] == "5");
    CHECK(v.build() == "00789.d.q");
    REQUIRE(v.buildIdentifiers().size() == 3);
    CHECK(v.buildIdentifiers()[0] == "00789");
    CHECK(v.buildIdentifiers()[1] == "d");
    CHECK(v.buildIdentifiers()[2] == "q");
    CHECK(v.toString() == "45.67.89-rc.5+00789.d.q");
    CHECK(v.hasBuild() == true);
    CHECK(v.isPreRelease() == true);
}

TEST_CASE("omw::Version::isValid()")
{
    omw::Version v;

    v = "1.2.3";
    CHECK(v.isValid());

    v = "-1.2.3";
    CHECK_FALSE(v.isValid());

    v = "1.-2.3";
    CHECK_FALSE(v.isValid());

    v = "1.2.-3";
    CHECK_FALSE(v.isValid());

    v = "1a.2.3";
    CHECK_FALSE(v.isValid());

    v = "1.a2.3";
    CHECK_FALSE(v.isValid());

    v = "1.2.3y";
    CHECK_FALSE(v.isValid());

    v = ".2.3";
    CHECK_FALSE(v.isValid());

    v = "1..3";
    CHECK_FALSE(v.isValid());

    v = "1.2.";
    CHECK_FALSE(v.isValid());



    v = "1.2.3-beta.5";
    CHECK(v.isValid());

    v = "1.2.3--beta.5";
    CHECK(v.isValid());

    v = "1.2.3-beta.05";
    CHECK_FALSE(v.isValid());

    v = "1.2.3-beta.-5";
    CHECK(v.isValid());

    v = "1.2.3-beta$.5";
    CHECK_FALSE(v.isValid());



    v = "1.2.3+00123.bld";
    CHECK(v.isValid());

    v = "1.2.3+-00123.bld";
    CHECK(v.isValid());

    v = "1.2.3+00123.bl@d";
    CHECK_FALSE(v.isValid());



    v = "1.2.3-beta.5+00123.bld";
    CHECK(v.isValid());

    v = "1.2.3+00123.bld-beta.5";
    CHECK(v.isValid());
}

TEST_CASE("omw::Version compare operators")
{
    const omw::Version v000(0, 0, 0, "5");
    const omw::Version v001(0, 0, 1, "1");
    const omw::Version v010(0, 1, 0, "beta");
    const omw::Version v011(0, 1, 1, "0");
    const omw::Version v011_2(0, 1, 1, "0");
    const omw::Version v100(1, 0, 0, "alpha");
    const omw::Version v101(1, 0, 1, "12");
    const omw::Version v110(1, 1, 0, "rc.1");
    const omw::Version v111(1, 1, 1, "rc");

    CHECK_FALSE(v011 == v000);
    CHECK_FALSE(v011 == v001);
    CHECK_FALSE(v011 == v010);
    CHECK(v011 == v011_2);
    CHECK_FALSE(v011 == v100);
    CHECK_FALSE(v011 == v101);
    CHECK_FALSE(v011 == v110);
    CHECK_FALSE(v011 == v111);

    CHECK(v011 != v000);
    CHECK(v011 != v001);
    CHECK(v011 != v010);
    CHECK_FALSE(v011 != v011_2);
    CHECK(v011 != v100);
    CHECK(v011 != v101);
    CHECK(v011 != v110);
    CHECK(v011 != v111);

    CHECK_FALSE(v011 < v000);
    CHECK_FALSE(v011 < v001);
    CHECK_FALSE(v011 < v010);
    CHECK_FALSE(v011 < v011_2);
    CHECK(v011 < v100);
    CHECK(v011 < v101);
    CHECK(v011 < v110);
    CHECK(v011 < v111);

    CHECK_FALSE(v011 <= v000);
    CHECK_FALSE(v011 <= v001);
    CHECK_FALSE(v011 <= v010);
    CHECK(v011 <= v011_2);
    CHECK(v011 <= v100);
    CHECK(v011 <= v101);
    CHECK(v011 <= v110);
    CHECK(v011 <= v111);

    CHECK(v011 > v000);
    CHECK(v011 > v001);
    CHECK(v011 > v010);
    CHECK_FALSE(v011 > v011_2);
    CHECK_FALSE(v011 > v100);
    CHECK_FALSE(v011 > v101);
    CHECK_FALSE(v011 > v110);
    CHECK_FALSE(v011 > v111);

    CHECK(v011 >= v000);
    CHECK(v011 >= v001);
    CHECK(v011 >= v010);
    CHECK(v011 >= v011_2);
    CHECK_FALSE(v011 >= v100);
    CHECK_FALSE(v011 >= v101);
    CHECK_FALSE(v011 >= v110);
    CHECK_FALSE(v011 >= v111);
}

TEST_CASE("omw::Version compare operators pre-release")
{
    const omw::Version v00(1, 2, 3, "alpha");
    const omw::Version v01(1, 2, 3, "alpha.1");
    const omw::Version v02(1, 2, 3, "aplha.test");
    const omw::Version v03(1, 2, 3, "beta");
    const omw::Version v04(1, 2, 3, "beta.3");
    const omw::Version v05(1, 2, 3, "beta.10");
    const omw::Version v06(1, 2, 3, "beta.10abc");
    const omw::Version v07(1, 2, 3, "beta.3abc");
    const omw::Version v08(1, 2, 3, "rc");
    const omw::Version vMax(1, 2, 3);
    omw::Version v;

    v = v00;
    CHECK(((v == v00) && !(v == v01) && !(v == v02) && !(v == v03) && !(v == v04) && !(v == v05) && !(v == v06) && !(v == v07) && !(v == v08) && !(v == vMax)));
    CHECK((!(v != v00) && (v != v01) && (v != v02) && (v != v03) && (v != v04) && (v != v05) && (v != v06) && (v != v07) && (v != v08) && (v != vMax)));
    CHECK((!(v < v00) && (v < v01) && (v < v02) && (v < v03) && (v < v04) && (v < v05) && (v < v06) && (v < v07) && (v < v08) && (v < vMax)));
    CHECK((!(v > v00) && !(v > v01) && !(v > v02) && !(v > v03) && !(v > v04) && !(v > v05) && !(v > v06) && !(v > v07) && !(v > v08) && !(v > vMax)));
    CHECK(((v <= v00) && (v <= v01) && (v <= v02) && (v <= v03) && (v <= v04) && (v <= v05) && (v <= v06) && (v <= v07) && (v <= v08) && (v <= vMax)));
    CHECK(((v >= v00) && !(v >= v01) && !(v >= v02) && !(v >= v03) && !(v >= v04) && !(v >= v05) && !(v >= v06) && !(v >= v07) && !(v >= v08) && !(v >= vMax)));

    v = v01;
    CHECK((!(v == v00) && (v == v01) && !(v == v02) && !(v == v03) && !(v == v04) && !(v == v05) && !(v == v06) && !(v == v07) && !(v == v08) && !(v == vMax)));
    CHECK(((v != v00) && !(v != v01) && (v != v02) && (v != v03) && (v != v04) && (v != v05) && (v != v06) && (v != v07) && (v != v08) && (v != vMax)));
    CHECK((!(v < v00) && !(v < v01) && (v < v02) && (v < v03) && (v < v04) && (v < v05) && (v < v06) && (v < v07) && (v < v08) && (v < vMax)));
    CHECK(((v > v00) && !(v > v01) && !(v > v02) && !(v > v03) && !(v > v04) && !(v > v05) && !(v > v06) && !(v > v07) && !(v > v08) && !(v > vMax)));
    CHECK((!(v <= v00) && (v <= v01) && (v <= v02) && (v <= v03) && (v <= v04) && (v <= v05) && (v <= v06) && (v <= v07) && (v <= v08) && (v <= vMax)));
    CHECK(((v >= v00) && (v >= v01) && !(v >= v02) && !(v >= v03) && !(v >= v04) && !(v >= v05) && !(v >= v06) && !(v >= v07) && !(v >= v08) && !(v >= vMax)));

    v = v02;
    CHECK((!(v == v00) && !(v == v01) && (v == v02) && !(v == v03) && !(v == v04) && !(v == v05) && !(v == v06) && !(v == v07) && !(v == v08) && !(v == vMax)));
    CHECK(((v != v00) && (v != v01) && !(v != v02) && (v != v03) && (v != v04) && (v != v05) && (v != v06) && (v != v07) && (v != v08) && (v != vMax)));
    CHECK((!(v < v00) && !(v < v01) && !(v < v02) && (v < v03) && (v < v04) && (v < v05) && (v < v06) && (v < v07) && (v < v08) && (v < vMax)));
    CHECK(((v > v00) && (v > v01) && !(v > v02) && !(v > v03) && !(v > v04) && !(v > v05) && !(v > v06) && !(v > v07) && !(v > v08) && !(v > vMax)));
    CHECK((!(v <= v00) && !(v <= v01) && (v <= v02) && (v <= v03) && (v <= v04) && (v <= v05) && (v <= v06) && (v <= v07) && (v <= v08) && (v <= vMax)));
    CHECK(((v >= v00) && (v >= v01) && (v >= v02) && !(v >= v03) && !(v >= v04) && !(v >= v05) && !(v >= v06) && !(v >= v07) && !(v >= v08) && !(v >= vMax)));

    v = v03;
    CHECK((!(v == v00) && !(v == v01) && !(v == v02) && (v == v03) && !(v == v04) && !(v == v05) && !(v == v06) && !(v == v07) && !(v == v08) && !(v == vMax)));
    CHECK(((v != v00) && (v != v01) && (v != v02) && !(v != v03) && (v != v04) && (v != v05) && (v != v06) && (v != v07) && (v != v08) && (v != vMax)));
    CHECK((!(v < v00) && !(v < v01) && !(v < v02) && !(v < v03) && (v < v04) && (v < v05) && (v < v06) && (v < v07) && (v < v08) && (v < vMax)));
    CHECK(((v > v00) && (v > v01) && (v > v02) && !(v > v03) && !(v > v04) && !(v > v05) && !(v > v06) && !(v > v07) && !(v > v08) && !(v > vMax)));
    CHECK((!(v <= v00) && !(v <= v01) && !(v <= v02) && (v <= v03) && (v <= v04) && (v <= v05) && (v <= v06) && (v <= v07) && (v <= v08) && (v <= vMax)));
    CHECK(((v >= v00) && (v >= v01) && (v >= v02) && (v >= v03) && !(v >= v04) && !(v >= v05) && !(v >= v06) && !(v >= v07) && !(v >= v08) && !(v >= vMax)));

    v = v04;
    CHECK((!(v == v00) && !(v == v01) && !(v == v02) && !(v == v03) && (v == v04) && !(v == v05) && !(v == v06) && !(v == v07) && !(v == v08) && !(v == vMax)));
    CHECK(((v != v00) && (v != v01) && (v != v02) && (v != v03) && !(v != v04) && (v != v05) && (v != v06) && (v != v07) && (v != v08) && (v != vMax)));
    CHECK((!(v < v00) && !(v < v01) && !(v < v02) && !(v < v03) && !(v < v04) && (v < v05) && (v < v06) && (v < v07) && (v < v08) && (v < vMax)));
    CHECK(((v > v00) && (v > v01) && (v > v02) && (v > v03) && !(v > v04) && !(v > v05) && !(v > v06) && !(v > v07) && !(v > v08) && !(v > vMax)));
    CHECK((!(v <= v00) && !(v <= v01) && !(v <= v02) && !(v <= v03) && (v <= v04) && (v <= v05) && (v <= v06) && (v <= v07) && (v <= v08) && (v <= vMax)));
    CHECK(((v >= v00) && (v >= v01) && (v >= v02) && (v >= v03) && (v >= v04) && !(v >= v05) && !(v >= v06) && !(v >= v07) && !(v >= v08) && !(v >= vMax)));

    v = v05;
    CHECK((!(v == v00) && !(v == v01) && !(v == v02) && !(v == v03) && !(v == v04) && (v == v05) && !(v == v06) && !(v == v07) && !(v == v08) && !(v == vMax)));
    CHECK(((v != v00) && (v != v01) && (v != v02) && (v != v03) && (v != v04) && !(v != v05) && (v != v06) && (v != v07) && (v != v08) && (v != vMax)));
    CHECK((!(v < v00) && !(v < v01) && !(v < v02) && !(v < v03) && !(v < v04) && !(v < v05) && (v < v06) && (v < v07) && (v < v08) && (v < vMax)));
    CHECK(((v > v00) && (v > v01) && (v > v02) && (v > v03) && (v > v04) && !(v > v05) && !(v > v06) && !(v > v07) && !(v > v08) && !(v > vMax)));
    CHECK((!(v <= v00) && !(v <= v01) && !(v <= v02) && !(v <= v03) && !(v <= v04) && (v <= v05) && (v <= v06) && (v <= v07) && (v <= v08) && (v <= vMax)));
    CHECK(((v >= v00) && (v >= v01) && (v >= v02) && (v >= v03) && (v >= v04) && (v >= v05) && !(v >= v06) && !(v >= v07) && !(v >= v08) && !(v >= vMax)));

    v = v06;
    CHECK((!(v == v00) && !(v == v01) && !(v == v02) && !(v == v03) && !(v == v04) && !(v == v05) && (v == v06) && !(v == v07) && !(v == v08) && !(v == vMax)));
    CHECK(((v != v00) && (v != v01) && (v != v02) && (v != v03) && (v != v04) && (v != v05) && !(v != v06) && (v != v07) && (v != v08) && (v != vMax)));
    CHECK((!(v < v00) && !(v < v01) && !(v < v02) && !(v < v03) && !(v < v04) && !(v < v05) && !(v < v06) && (v < v07) && (v < v08) && (v < vMax)));
    CHECK(((v > v00) && (v > v01) && (v > v02) && (v > v03) && (v > v04) && (v > v05) && !(v > v06) && !(v > v07) && !(v > v08) && !(v > vMax)));
    CHECK((!(v <= v00) && !(v <= v01) && !(v <= v02) && !(v <= v03) && !(v <= v04) && !(v <= v05) && (v <= v06) && (v <= v07) && (v <= v08) && (v <= vMax)));
    CHECK(((v >= v00) && (v >= v01) && (v >= v02) && (v >= v03) && (v >= v04) && (v >= v05) && (v >= v06) && !(v >= v07) && !(v >= v08) && !(v >= vMax)));

    v = v07;
    CHECK((!(v == v00) && !(v == v01) && !(v == v02) && !(v == v03) && !(v == v04) && !(v == v05) && !(v == v06) && (v == v07) && !(v == v08) && !(v == vMax)));
    CHECK(((v != v00) && (v != v01) && (v != v02) && (v != v03) && (v != v04) && (v != v05) && (v != v06) && !(v != v07) && (v != v08) && (v != vMax)));
    CHECK((!(v < v00) && !(v < v01) && !(v < v02) && !(v < v03) && !(v < v04) && !(v < v05) && !(v < v06) && !(v < v07) && (v < v08) && (v < vMax)));
    CHECK(((v > v00) && (v > v01) && (v > v02) && (v > v03) && (v > v04) && (v > v05) && (v > v06) && !(v > v07) && !(v > v08) && !(v > vMax)));
    CHECK((!(v <= v00) && !(v <= v01) && !(v <= v02) && !(v <= v03) && !(v <= v04) && !(v <= v05) && !(v <= v06) && (v <= v07) && (v <= v08) && (v <= vMax)));
    CHECK(((v >= v00) && (v >= v01) && (v >= v02) && (v >= v03) && (v >= v04) && (v >= v05) && (v >= v06) && (v >= v07) && !(v >= v08) && !(v >= vMax)));

    v = v08;
    CHECK((!(v == v00) && !(v == v01) && !(v == v02) && !(v == v03) && !(v == v04) && !(v == v05) && !(v == v06) && !(v == v07) && (v == v08) && !(v == vMax)));
    CHECK(((v != v00) && (v != v01) && (v != v02) && (v != v03) && (v != v04) && (v != v05) && (v != v06) && (v != v07) && !(v != v08) && (v != vMax)));
    CHECK((!(v < v00) && !(v < v01) && !(v < v02) && !(v < v03) && !(v < v04) && !(v < v05) && !(v < v06) && !(v < v07) && !(v < v08) && (v < vMax)));
    CHECK(((v > v00) && (v > v01) && (v > v02) && (v > v03) && (v > v04) && (v > v05) && (v > v06) && (v > v07) && !(v > v08) && !(v > vMax)));
    CHECK((!(v <= v00) && !(v <= v01) && !(v <= v02) && !(v <= v03) && !(v <= v04) && !(v <= v05) && !(v <= v06) && !(v <= v07) && (v <= v08) && (v <= vMax)));
    CHECK(((v >= v00) && (v >= v01) && (v >= v02) && (v >= v03) && (v >= v04) && (v >= v05) && (v >= v06) && (v >= v07) && (v >= v08) && !(v >= vMax)));

    v = vMax;
    CHECK((!(v == v00) && !(v == v01) && !(v == v02) && !(v == v03) && !(v == v04) && !(v == v05) && !(v == v06) && !(v == v07) && !(v == v08) && (v == vMax)));
    CHECK(((v != v00) && (v != v01) && (v != v02) && (v != v03) && (v != v04) && (v != v05) && (v != v06) && (v != v07) && (v != v08) && !(v != vMax)));
    CHECK((!(v < v00) && !(v < v01) && !(v < v02) && !(v < v03) && !(v < v04) && !(v < v05) && !(v < v06) && !(v < v07) && !(v < v08) && !(v < vMax)));
    CHECK(((v > v00) && (v > v01) && (v > v02) && (v > v03) && (v > v04) && (v > v05) && (v > v06) && (v > v07) && (v > v08) && !(v > vMax)));
    CHECK((!(v <= v00) && !(v <= v01) && !(v <= v02) && !(v <= v03) && !(v <= v04) && !(v <= v05) && !(v <= v06) && !(v <= v07) && !(v <= v08) && (v <= vMax)));
    CHECK(((v >= v00) && (v >= v01) && (v >= v02) && (v >= v03) && (v >= v04) && (v >= v05) && (v >= v06) && (v >= v07) && (v >= v08) && (v >= vMax)));
}



#endif // TEST_OMW_VERSION_H
