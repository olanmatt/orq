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

#ifndef INTERNALCONSTANTS_H
#define INTERNALCONSTANTS_H

#include <stdint.h>

class InternalConstants {
	
	public:
    static const int Al = 1;

    static const int K_max = 56403;                 // "maximum number of symbols in each source block"
    static const int Z_max = 256;                    // "maximum number of source blocks"
    static const int Kt_max = K_max * Z_max;         // "maximum number of symbols"
    static const int T_max = (65535 / Al) * Al;     // "maximum symbol size, in octets"
    static const long F_max = Kt_max * T_max; // "maximum transfer length of the object, in octets"
    static const int N_max = 1/* K_max */;           // "maximum interleaver length, in number of sub-blocks"
    // TODO enable interleaving

    static const int K_min = 1;
    static const int K_prime_min = 10;  // the first K' value in the systematic indices table
    static const int Z_min = 1;
    static const int T_min = Al;
    static const int F_min = 1; // RFC 6330 defines F as a non-negative value, but we force a positive value here
    static const int N_min = 1;

    static const int SBN_max = 255;
    static const int ESI_max = 16777215;

    static const int SBN_min = 0;
    static const int ESI_min = 0;

    static const int F_num_bytes = 5;
    static const int ESI_num_bytes = 3;

    static const long common_OTI_reserved_inverse_mask = 0xFFFFFFFFFF00FFFF; // third octet is reserved bits

	private:
};

#endif
