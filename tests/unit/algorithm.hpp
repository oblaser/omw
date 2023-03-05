/*
author          Oliver Blaser
date            05.03.2023
copyright       MIT - Copyright (c) 2023 Oliver Blaser
*/

#ifndef TEST_OMW_ALGORITHM_H
#define TEST_OMW_ALGORITHM_H

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include "catch2/catch.hpp"

#include <omw/algorithm.h>
#include <omw/cli.h>
#include <omw/int.h>
#include <omw/string.h>



class DoubleDabbleTestRecord
{
public:
    DoubleDabbleTestRecord(const omw::string& expectedResult, uint64_t valueH, uint64_t valueL)
        : value128(valueH, valueL), value64H(valueH), value64L(valueL), expResult(expectedResult)
    {
        value32H = (uint32_t)((valueH >> 32) & (uint64_t)0xFFFFFFFF);
        value32HM = (uint32_t)(valueH & (uint64_t)0xFFFFFFFF);
        value32LM = (uint32_t)((valueL >> 32) & (uint64_t)0xFFFFFFFF);
        value32L = (uint32_t)(valueL & (uint64_t)0xFFFFFFFF);
    }
    virtual ~DoubleDabbleTestRecord() {}

    omw::uint128_t value128;
    uint32_t value32H;
    uint32_t value32HM;
    uint32_t value32LM;
    uint32_t value32L;
    uint64_t value64H;
    uint64_t value64L;

    omw::string expResult;
};

TEST_CASE("algorithm.h doubleDabble() 128 bit")
{
    // https://www.convzone.com/hex-to-decimal/

    std::vector<DoubleDabbleTestRecord> testRecords =
    {
        DoubleDabbleTestRecord("0000000000000000000000000000000000000001", 0x00, 0x01),
        DoubleDabbleTestRecord("0000000000000000000009223372036854775808", 0x00, INT64_MIN),
        DoubleDabbleTestRecord("00000000000000000000000000000000000" + omw::to_string(0xFFFF), 0x00, 0xFFFF),
        DoubleDabbleTestRecord("000000000000000000000000000000" + omw::to_string(INT32_MAX), 0x00, INT32_MAX),
        DoubleDabbleTestRecord("0000000000000001208925819614629174706175", 0xFFFF, 0xFFFFFFFFFFFFFFFF),
        DoubleDabbleTestRecord("0000000000000000604462909807314587354597", 0x8000, 0x00000000000005E5),
        DoubleDabbleTestRecord("0340282366920938463463374607431768211455", 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF),
        DoubleDabbleTestRecord("0001512366075204170929049582354406559215", 0x0123456789abcdef, 0x0123456789abcdef),
        DoubleDabbleTestRecord("0000000000000000000000000000000000000000", 0x00, 0x00)
    };

    bool stdOut = false;

    for (size_t i = 0; i < testRecords.size(); ++i)
    {
        const DoubleDabbleTestRecord& tr = testRecords[i];

        const omw::string ovrld_a = omw::toHexStr(omw::doubleDabble128(tr.value32H, tr.value32HM, tr.value32LM, tr.value32L), 0);
        const omw::string ovrld_b = omw::toHexStr(omw::doubleDabble128(tr.value64H, tr.value64L), 0);
        const omw::string ovrld_c = omw::toHexStr(omw::doubleDabble(tr.value128), 0);

        const bool resEqExpres = (ovrld_a == tr.expResult);
        const bool allOverloadsEq = (
            (ovrld_a == ovrld_b) &&
            (ovrld_a == ovrld_c));

        CHECK(ovrld_a == tr.expResult);
        CHECK(allOverloadsEq);

        if (!(resEqExpres && allOverloadsEq))
        {
            std::cout << omw::fgBrightCyan << "double dabble test record #" << i << omw::normal << "\n" << std::endl;
            stdOut = true;
        }
    }

    if (stdOut) std::cout << std::endl;
}



class LevenshteinStrTestRecord
{
public:
    LevenshteinStrTestRecord() : m_a(""), m_b("-"), m_r(-1) {}
    LevenshteinStrTestRecord(const char* a, const char* b, size_t r) : m_a(a), m_b(b), m_r(r) {}

    const char* a() const { return m_a; }
    const char* b() const { return m_b; }
    size_t aLen() const { return std::strlen(m_a); }
    size_t bLen() const { return std::strlen(m_b); }
    std::string aStr() const { return m_a; }
    std::string bStr() const { return m_b; }

    size_t r() const { return m_r; }

private:
    const char* const m_a;
    const char* const m_b;
    size_t m_r;
};

template <typename T>
class LevenshteinTestRecord
{
public:
    LevenshteinTestRecord() : m_a(), m_b(), m_r(-1) {}
    LevenshteinTestRecord(const std::vector<T>& a, const std::vector<T>& b, size_t r) : m_a(a), m_b(b), m_r(r) {}

    const std::vector<T>& a() const { return m_a; }
    const std::vector<T>& b() const { return m_b; }

    size_t r() const { return m_r; }

private:
    std::vector<T> m_a;
    std::vector<T> m_b;
    size_t m_r;
};

TEST_CASE("algorithm.h levenshteinDistance() nullptr")
{
    const char* const n = nullptr;
    CHECK(omw::levenshteinDistance(n, 1, n, 2) == SIZE_MAX);
    CHECK(omw::levenshteinDistance(n, 1, "asdf", 4) == SIZE_MAX);
    CHECK(omw::levenshteinDistance("asdf", 4, n, 2) == SIZE_MAX);

    CHECK(omw::levenshteinDistance(nullptr, nullptr) == SIZE_MAX);
    CHECK(omw::levenshteinDistance(nullptr, "asdf") == SIZE_MAX);
    CHECK(omw::levenshteinDistance("asdf", nullptr) == SIZE_MAX);
}

TEST_CASE("algorithm.h levenshteinDistance() strings")
{
    CHECK(omw::levenshteinDistance("kitten", 6, "sitting", 7) == 3);
    CHECK(omw::levenshteinDistance("kitten", "sitting") == 3);
    
    std::vector<LevenshteinStrTestRecord> testRecords =
    {
        LevenshteinStrTestRecord("Levenshtein", "Levenshtein", 0),
        LevenshteinStrTestRecord("asdf", "asdf", 0),
        LevenshteinStrTestRecord("", "", 0),
        LevenshteinStrTestRecord("Lewenstein", "Levenshtein", 2),
        LevenshteinStrTestRecord("kitten", "sitting", 3),
        LevenshteinStrTestRecord("sitting", "kitten", 3),
        LevenshteinStrTestRecord("Sunday", "Saturday", 3),
        LevenshteinStrTestRecord("Meilenstein", "Levenshtein", 4),
        LevenshteinStrTestRecord("Tier", "Tor", 2),
        LevenshteinStrTestRecord("Fest", "Test", 1),
        LevenshteinStrTestRecord("Apfel", "Pferd", 4),
        LevenshteinStrTestRecord("apfel", "pferd", 3),
        LevenshteinStrTestRecord("asdf", "qwertz", 6),
        LevenshteinStrTestRecord("", "abcd", 4),
        LevenshteinStrTestRecord("Abcd", "abcd", 1)
    };

    for (size_t i = 0; i < testRecords.size(); ++i)
    {
        const auto& x = testRecords[i];
        //std::cout << x.a() << " " << x.b() << " " << x.r() << " - " << omw::levenshteinDistance(x.a(), x.b()) << std::endl;
        CHECK(omw::levenshteinDistance(x.a(), x.aLen(), x.b(), x.bLen()) == x.r());
        CHECK(omw::levenshteinDistance(x.a(), x.b()) == x.r());
        CHECK(omw::levenshteinDistance(x.aStr(), x.bStr()) == x.r());
    }
}

TEST_CASE("algorithm.h levenshteinDistance() empty vector")
{
    std::vector<LevenshteinTestRecord<int>> testRecords =
    {
        LevenshteinTestRecord<int>({}, {}, 0),
        LevenshteinTestRecord<int>({}, { 1, 2, 3 }, 3),
        LevenshteinTestRecord<int>({ 1, 2, 3 }, {}, 3)
    };

    for (size_t i = 0; i < testRecords.size(); ++i)
    {
        const auto& x = testRecords[i];
        CHECK(omw::levenshteinDistance(x.a(), x.b()) == x.r());
    }
}

TEST_CASE("algorithm.h levenshteinDistance() vector")
{
    std::vector<LevenshteinTestRecord<int>> testRecords =
    {
        LevenshteinTestRecord<int>({ 1, 2, 3 }, { 1, 2, 3 }, 0),
        LevenshteinTestRecord<int>({ -2, 2, -123456, 1, 0, 3 }, { -2, 2, -123456, 1, 0, 3 }, 0),
        LevenshteinTestRecord<int>({ 1, 2, 3 }, { 1, 2, 3, 4 }, 1),
        LevenshteinTestRecord<int>({ 1, 2, 3 }, { 1, 2, 4 }, 1),
        LevenshteinTestRecord<int>({ -2, 2, -123456, 1, 0, 3 }, { -2, 2, -123, 1, 5, 3 }, 2)
    };

    for (size_t i = 0; i < testRecords.size(); ++i)
    {
        const auto& x = testRecords[i];
        CHECK(omw::levenshteinDistance(x.a().data(), x.a().size(), x.b().data(), x.b().size()) == x.r());
        CHECK(omw::levenshteinDistance(x.a(), x.b()) == x.r());
    }
}


#endif // TEST_OMW_ALGORITHM_H
