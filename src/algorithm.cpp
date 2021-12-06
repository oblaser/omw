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

