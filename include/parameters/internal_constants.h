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
    static const uint8_t Al = 1;  // symbol alignment parameter

    static const uint32_t ESI_min = 0;  // minimum encoding symbol ID
    static const uint32_t ESI_max = 16777215;  // maximum encoding symbol ID

    static const uint16_t K_min = 1;  // minimum number of source symbols
    static const uint16_t K_max = 56403;  // maximum number of source symbols

    static const uint16_t K_prime_min =
        10;  // the first K' value in the systematic indices table

    static const uint16_t N_min = 1;  // minimum number of sub-blocks
    // TODO(olanmatt): Enable interleaving.
    static const uint16_t N_max = 1;  // maximum number of sub-blocks

    static const uint8_t SBN_min = 0;  // minimum source block number
    static const uint8_t SBN_max = 255;  // maximum source block number

    static const uint8_t T_min = Al;  // minimum symbol size
    static const uint16_t T_max = (65535 / Al) *Al;   // maximum symbol size

    static const uint16_t Z_min = 1;  // minimum number of source blocks
    static const uint16_t Z_max = 256;  // maximum number of source blocks

    static const uint32_t Kt_max = K_max * Z_max;  // max total number of symbols

    static const uint64_t F_min = 1;  // minimum transfer length
    static const uint64_t F_max = ((uint64_t)Kt_max) * T_max;  // max transfer length

    // third octet is reserved bits
    static const uint64_t common_oti_reserved_inverse_mask = 0xFFFFFFFFFF00FFFFLLU;

}  // namespace internal_constants

#endif  // INCLUDE_PARAMETERS_INTERNAL_CONSTANTS_H_
