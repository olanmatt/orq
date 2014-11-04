/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 Matt Olan
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef INCLUDE_PARAMETERS_INTERNAL_CONSTANTS_H_
#define INCLUDE_PARAMETERS_INTERNAL_CONSTANTS_H_

#include <cstdint>

namespace internal_constants
{
    const std::uint8_t Al = 1;  // symbol alignment parameter

    // encoding symbol ID
    const std::uint32_t ESI_min = 0;
    const std::uint32_t ESI_max = 16777215;

    // source block number
    const std::uint8_t SBN_min = 0;
    const std::uint8_t SBN_max = 255;

    // number of sub-blocks
    const std::uint16_t N_min = 1;
    const std::uint16_t N_max = 1;  // TODO(olanmatt): Enable interleaving.

    // number of source blocks
    const std::uint16_t Z_min = 1;
    const std::uint16_t Z_max = 256;

    // source symbols
    const std::uint16_t K_min = 1;
    const std::uint16_t K_max = 56403;

    const std::uint32_t Kt_max = K_max *Z_max;  // max total number of symbols
    // the first K' value in the systematic indices table
    const std::uint16_t K_prime_min = 10;

    // symbol size
    const std::uint16_t T_min = Al;
    const std::uint16_t T_max = (65535 / Al) *Al;

    // Transfer length
    const std::uint64_t F_min = 1;
    const std::uint64_t F_max = ((uint64_t)Kt_max) *T_max;

    // third octet is reserved bits
    const std::uint64_t common_oti_reserved_inverse_mask = 0xFFFFFFFFFF00FFFFLLU;

}  // namespace internal_constants

#endif  // INCLUDE_PARAMETERS_INTERNAL_CONSTANTS_H_
