/*
author          Oliver Blaser
date            06.12.2021
copyright       MIT - Copyright (c) 2021 Oliver Blaser
*/

#include <bitset>

#include "omw/algorithm.h"

namespace
{
    namespace doubleDabble
    {
        void dd_add3(std::vector<uint8_t>& bcd)
        {
            for (size_t i = 0; i < bcd.size(); ++i)
            {
                uint8_t h = bcd[i] >> 4;
                uint8_t l = bcd[i] & 0x0F;

                if (h >= 5) h += 3;
                if (l >= 5) l += 3;

#if 0 // proof that add 3 operation never overflows a BCD digit
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
        void dd_leftShift(std::vector<uint8_t>& bcd, std::bitset<N>& bin)
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
                ::doubleDabble::dd_add3(bcd);
                ::doubleDabble::dd_leftShift(bcd, bin);
            }
        }
    }
}



//! @param data big-endian right aligned
//! @param count 
//! @return 
std::vector<uint8_t> omw::doubleDabble128(const uint8_t* data, size_t count)
{
    constexpr size_t bitWidth = 128;
    using chunk_t = uint8_t;
    constexpr size_t chunkWidth = 8;
    constexpr size_t nChunks = bitWidth / chunkWidth;

    std::vector<uint8_t> bcd(20);
    std::bitset<bitWidth> bin;

    //init
    if (data)
    {
        for (size_t i = 0; i < nChunks; ++i)
        {
            chunk_t chunkValue = 0;
            if (i < count) chunkValue = data[count - 1 - i];

            chunk_t chunkMask = 1;

            for (size_t j = 0; j < chunkWidth; ++j)
            {
                const size_t pos = i * chunkWidth + j;
                bin.set(pos, ((chunkValue & chunkMask) != 0));
                chunkMask <<= 1;
            }
        }
    }
    // else nop / initialized with 0

    ::doubleDabble::dd(bcd, bin);

    return bcd;
}

std::vector<uint8_t> omw::doubleDabble128(uint32_t valueH, uint32_t valueHM, uint32_t valueLM, uint32_t valueL)
{
    uint64_t value64H = valueH;
    value64H <<= 32;
    value64H |= valueHM;

    uint64_t value64L = valueLM;
    value64L <<= 32;
    value64L |= valueL;

    return omw::doubleDabble128(value64H, value64L);
}

std::vector<uint8_t> omw::doubleDabble128(uint64_t valueH, uint64_t valueL)
{
    constexpr size_t bitWidth = 128;
    using chunk_t = uint64_t;
    constexpr size_t chunkWidth = 64;

    std::vector<uint8_t> bcd(20);
    std::bitset<bitWidth> bin;

    //init
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
