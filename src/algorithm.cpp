/*
author          Oliver Blaser
date            20.12.2021
copyright       MIT - Copyright (c) 2021 Oliver Blaser
*/

#include <bitset>

#include "omw/algorithm.h"

namespace
{
    namespace doubleDabble
    {
        void add3(std::vector<uint8_t>& bcd)
        {
            for (size_t i = 0; i < bcd.size(); ++i)
            {
                uint8_t h = bcd[i] >> 4;
                uint8_t l = bcd[i] & 0x0F;

                if (h >= 5) h += 3;
                if (l >= 5) l += 3;

#if 0 // proof that add3 operation never overflows a BCD digit
                static bool overflow = false;
                static bool cntOverflow = false;
                static uint64_t cntH = 0;
                static uint64_t cntM = 0;
                static uint64_t cntL = 0;
                if ((h & 0xF0) || (l & 0xF0))
                {
                    overflow = true;

                    if (cntH == 0xFFFFFFFFFFFFFFFF) cntOverflow = true;
                    if (cntM == 0xFFFFFFFFFFFFFFFF) ++cntH;
                    if (cntL == 0xFFFFFFFFFFFFFFFF) ++cntM;
                    ++cntL;
                }
#endif

                bcd[i] = h;
                bcd[i] <<= 4;
                bcd[i] |= l;
            }
        }

        template <size_t N>
        void leftShift(std::vector<uint8_t>& bcd, std::bitset<N>& bin)
        {
            for (size_t i = 0; i < (bcd.size() - 1); ++i)
            {
                bcd[i] <<= 1;
                if (bcd[i + 1] & 0x80)  bcd[i] |= 0x01;
            }

            bcd[bcd.size() - 1] <<= 1;
            if (bin.test(N - 1))  bcd[bcd.size() - 1] |= 0x01;

            bin <<= 1;
        }

        template <size_t N>
        void dd(std::vector<uint8_t>& bcd, std::bitset<N>& bin)
        {
            for (size_t i = 0; i < N; ++i)
            {
                ::doubleDabble::add3(bcd);
                ::doubleDabble::leftShift(bcd, bin);
            }
        }
    }
}



std::vector<uint8_t> omw::doubleDabble128(uint32_t valueHH, uint32_t valueLH, uint32_t valueHL, uint32_t valueLL)
{
    uint64_t value64H = valueHH;
    value64H <<= 32;
    value64H |= valueLH;

    uint64_t value64L = valueHL;
    value64L <<= 32;
    value64L |= valueLL;

    return omw::doubleDabble128(value64H, value64L);
}

std::vector<uint8_t> omw::doubleDabble128(uint64_t valueH, uint64_t valueL)
{
    constexpr size_t bitWidth = 128;
    using chunk_t = uint64_t;
    constexpr size_t chunkWidth = 64;

    std::vector<uint8_t> bcd(20);
    std::bitset<bitWidth> bin;

    // init
    {
        chunk_t chunkValue;
        chunk_t chunkMask;

        // i = 0
        chunkValue = valueL;
        chunkMask = 1;
        for (size_t j = 0; j < chunkWidth; ++j)
        {
            bin.set(j, ((chunkValue & chunkMask) != 0));
            chunkMask <<= 1;
        }

        // i = 1
        chunkValue = valueH;
        chunkMask = 1;
        for (size_t j = 0; j < chunkWidth; ++j)
        {
            bin.set(chunkWidth + j, ((chunkValue & chunkMask) != 0));
            chunkMask <<= 1;
        }
    }

    ::doubleDabble::dd(bcd, bin);

    return bcd;
}

std::vector<uint8_t> omw::doubleDabble(const omw::uint128_t& value)
{
    std::vector<uint8_t> bcd(20);
    std::bitset<128> bin;

    // init
    {
        omw::uint128_t chunkMask = 1;

        for (size_t i = 0; i < 128; ++i)
        {
            bin.set(i, static_cast<bool>(value & chunkMask));
            chunkMask <<= 1;
        }
    }

    ::doubleDabble::dd(bcd, bin);

    return bcd;
}
