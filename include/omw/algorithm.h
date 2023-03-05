/*
author          Oliver Blaser
date            28.02.2023
copyright       MIT - Copyright (c) 2023 Oliver Blaser
*/

#ifndef IG_OMW_ALGORITHM_H
#define IG_OMW_ALGORITHM_H

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "../omw/int.h"

namespace omw
{
    /*! \addtogroup grp_algorithm
    * @{
    */

    //! \name Double Dabble
    /// @{
    std::vector<uint8_t> doubleDabble128(uint32_t valueHH, uint32_t valueLH, uint32_t valueHL, uint32_t valueLL);
    std::vector<uint8_t> doubleDabble128(uint64_t valueH, uint64_t valueL);

    std::vector<uint8_t> doubleDabble(const omw::uint128_t& value);
    /// @}

    //! \name Levenshtein Distance
    /// @{
    template <typename T>
    inline size_t levenshteinDistance(const T* a, size_t aCount, const T* b, size_t bCount)
    {
        size_t r;

        if (a && b)
        {
            std::vector<std::vector<size_t>> m(aCount + 1, std::vector<size_t>(bCount + 1, 0));

            for (size_t j = 1; j < m[0].size(); ++j) m[0][j] = j;

            for (size_t i = 1; i < m.size(); ++i)
            {
                m[i][0] = i;

                for (size_t j = 1; j < m[i].size(); ++j)
                {
                    const size_t sub = m[i - 1][j - 1] + (*(a + i - 1) == *(b + j - 1) ? 0 : 1); // substitution
                    const size_t ins = m[i][j - 1] + 1; // insertion
                    const size_t del = m[i - 1][j] + 1; // deletion

                    m[i][j] = std::min(std::min(sub, ins), del);
                }
            }

            r = m[aCount][bCount];
        }
        else r = SIZE_MAX;

        return r;
    }

    inline size_t levenshteinDistance(const char* a, const char* b)
    {
        size_t r;
        if (a && b) r = levenshteinDistance(a, std::strlen(a), b, std::strlen(b));
        else r = SIZE_MAX;
        return r;
    }

    inline size_t levenshteinDistance(const std::string& a, const std::string& b) { return levenshteinDistance(a.data(), a.size(), b.data(), b.size()); }
    
    template <typename T>
    inline size_t levenshteinDistance(const std::vector<T>& a, const std::vector<T>& b)
    {
        size_t r;

        if (a.empty() && b.empty()) r = 0;
        else if (a.empty()) r = levenshteinDistance<T>(b.data(), 0, b.data(), b.size());
        else if (b.empty()) r = levenshteinDistance<T>(a.data(), a.size(), a.data(), 0);
        else r = levenshteinDistance<T>(a.data(), a.size(), b.data(), b.size());

        return r;
    }
    /// @}

    /*! @} */
}

#endif // IG_OMW_ALGORITHM_H
