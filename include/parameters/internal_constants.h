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

#ifndef INTERNAL_CONSTANTS_H
#define INTERNAL_CONSTANTS_H

#include <cstdint>

namespace internal_constants
{

    static const uint8_t Al = 1;
    // "maximum number of symbols in each source block"
    static const uint16_t K_max = 56403;
    // "maximum number of source blocks"
    static const uint16_t Z_max = 256;
    // static const int Kt_max = K_max * Z_max;
    // "maximum number of symbols"
    static const uint32_t Kt_max = 14439168;
    // static const int T_max = (65535 / Al) * Al;
    // "maximum symbol size, in octets"
    static const uint16_t T_max = 65535;
    // static const uint64_t F_max = Kt_max * T_max;
    // "maximum transfer length of the object, in octets"
    static const uint64_t F_max = 946270874880LLU;
    // "maximum interleaver length, in number of sub-blocks"
    static const uint16_t N_max = 1 /* K_max */;
    // TODO enable interleaving

    static const uint16_t K_min = 1;
    // the first K' value in the systematic indices table
    static const uint16_t K_prime_min = 10;
    static const uint16_t Z_min = 1;
    static const uint8_t T_min = Al;
    // RFC 6330 defines F as a non-negative value, but we force a positive value here
    static const uint64_t F_min = 1;
    static const uint16_t N_min = 1;

    static const uint8_t SBN_max = 255;
    static const uint32_t ESI_max = 16777215;

    static const uint8_t SBN_min = 0;
    static const uint32_t ESI_min = 0;

    // TODO convert to stdint.h
    static const int F_num_bytes = 5;
    static const int ESI_num_bytes = 3;

    // third octet is reserved bits
    static const uint64_t common_oti_reserved_inverse_mask = 0xFFFFFFFFFF00FFFF;
};

#endif
